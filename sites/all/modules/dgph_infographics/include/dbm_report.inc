<?php
    /**
     * Load budget information from the database
     * @param $deptId department identifier
     * @param $year year we need data for
     * @param $quarter quarter we need data for
     * @return budget information
     */
    function dbm_fetch_budget($deptId, $year, $quarter) {
        $items = array();
        $query = db_select('t_budget_data', 'bd')
                    ->fields('bd', array('record', 'approp'));
        $query->join('t_departments', 'dept', 'bd.agency like dept.name');
        $query->condition('bd.year', $year)
                ->condition('bd.quarter', $quarter)
                ->condition('dept.id', $deptId);
        $res = $query->execute();
        foreach($res as $row) {
            // add this item
            $items[$row->record] = $row->approp;
        }
        return $items;
    }
    /**
     * Load budget information for a given record
     * @param $deptId department identifier
     * @param $year year we need data for
     * @param $quarter quarter we need data for
     * @param $record the name of the specific record to fetch
     * @return budget information
     */
    function dbm_fetch_budget_record($deptId, $year, $quarter, $record) {
        $query = db_select('t_budget_data', 'bd')
                    ->fields('bd');
        $query->join('t_departments', 'dept', 'bd.agency like dept.name');
        $query->condition('bd.year', $year)
                ->condition('bd.quarter', $quarter)
                ->condition('dept.id', $deptId)
                ->condition('bd.record', $record)
                ->range(0, 1);
        $rec = $query->execute()->fetchAssoc();
        return $rec;
    }
    /**
     * Build the budget report
     * @param $cfg report configuration parameters
     * @return the report code
     */
    function dbm_build_budget_report($cfg) {
        // build chart
        $deptId = $cfg['department_id'];
        $year = $cfg['year'];
        $quarter = $cfg['quarter'];
        $budget = dbm_fetch_budget($deptId, $year, $quarter);
        $chartCode = "<div class='graph-no-data'>No data available at this time</div>";
        if (isset($budget['budget'])) {
            $chartData = array(floatval($budget['budget'])/1000, floatval($budget['budget_curr'])/1000, floatval($budget['budget_agency'])/1000,
                               floatval($budget['budget_spf'])/1000, floatval($budget['budget_automatic'])/1000, floatval($budget['contappro'])/1000);
            $chartLabels = array(
                        'Total Approved Budget',
                        'Current Year Budget',
                        'Agency Specific Budget',
                        'Special Purpose Fund',
                        'Automatic Appropriation',
                        'Carry-Over Budget (Continuing Appropriation)'
                    );
            $chartLegend = "Q$quarter";
            $chartCode = dgph_build_bar_chart($chartData, $chartLabels, array('legend'=>$chartLegend));
        }
        $code = "
                    <h4>PERFORMANCE RATES</h4>
                    <br><br>
                    <div class='icg-con'>$chartCode</div>";
        return $code;
    }
    /**
     * Build the report for trend #1
     * @param $cfg report configuration parameters
     * @return the report code
     */
    function dbm_build_trend1_report($cfg) {
        // gets budget data
        $deptId = $cfg['department_id'];
        $year = $cfg['year'];
        $quarter = $cfg['quarter'];
        $chartCode = "<div class='graph-no-data'>No data available at this time</div>";
        $budget = dbm_fetch_budget_record($deptId, $year, $quarter, 'budget_curr');
        if (isset($budget['approp'])) {
            // build chart
            $chartData = array( floatval($budget['approp'])/1000, floatval($budget['allot_tot'])/1000, 
                                floatval($budget['oblig_tot'])/1000);
            $chartLabels = array('Approved', 'Released', 'Utilized');
            $chartLegend = "Q$quarter";
            $chartCode = dgph_build_bar_chart($chartData, $chartLabels, array('legend'=>$chartLegend));
        }
        $code = "
                    <h4>ALLOTMENT RELEASE RATE</h4>
                    <br><br>
                    <div class='icg-con'>$chartCode</div>
                    <div class='row graph-legend'>
                        <p><span class='header'>Approved vs Released vs Utilized Budget</span>: this compares the approved budget (Appropriation) of each agency with the budget released to them (Allotment) by the DBM, and with the budget actually used by the agency (Obligation) during the period. 
                        Obligations are a good gauce of an agency's budget performance as it indicates the magnitude of programs and projects that is able to mobilize given its approved budget. The ratio of agency obligations against the budgets released to it (Obligation Rate)
                        is also a good gauge of an agency's capacity to implement programs and projects (Absorptive Capacity)</p>
                    </div>";
        return $code;
    }
    /**
     * Load agency abbreviations from the database
     * @return array the agency abbreviations, keyed by agency name
     */
    function dbm_load_agency_abbreviations() {
        $abbrs = array();
        try {
            $query = db_select('t_departments', 'dept')
                        ->fields('dept', array('code', 'name'))
                        ->orderBy('dept.name');
            $res = $query->execute();
            foreach($res as $row) {
                $abbrs[trim($row->name)] = trim($row->code);
            }
        }
        catch(Exception $e) {}
        return $abbrs;
    }
    
    /**
     * Build the report for trend #2
     * @param $cfg report configuration parameters
     * @return the report code
     */
    function dbm_build_trend2_report($cfg) {
        // gets top 10 agencies by budget
        $year = $cfg['year'];
        $quarter = $cfg['quarter'];
        $query = db_select('t_budget_data', 'bd')
                    ->fields('bd', array('agency', 'approp'));
        $query->condition('bd.year', $year)
                ->condition('bd.quarter', $quarter)
                ->condition('bd.record', 'budget')
                ->orderBy('approp', 'desc')
                ->range(0, 10);
        $res = $query->execute();
        // build chart
        $chartData = array();
        $chartLabels = array();
        // load agency abbreviations
        $abbrs = dbm_load_agency_abbreviations();
        foreach($res as $row) {
            // add this item
            $chartData[] = array('y'=>floatval($row->approp)/1000, 'dept'=>$row->agency);
            $chartLabels[] = array_key_exists($row->agency, $abbrs) ? $abbrs[$row->agency] : $row->agency;
        }
        // build chart
        $chartCode = "<div class='graph-no-data'>No data available at this time</div>";
        if (!empty($chartData)) {
            $chartLegend = "Q$quarter";
            $chartCode = dgph_build_bar_chart($chartData, $chartLabels,  array('legend'=>$chartLegend));
        }
        $code = "
                    <h4>BIGGEST BUDGET AGENCIES</h4>
                    <br><br>
                    <div class='icg-con'>$chartCode</div>
                    <div class='row graph-legend'>
                        <p><b>Agencies with Biggest Budgets</b>: this shows the government departments which have the biggest budgetary alloations for the fiscal year</p>
                    </div>";
        return $code;
    }
    /**
     * Build the report for trend #3
     * @param $cfg report configuration parameters
     * @return the report code
     */
    function dbm_build_trend3_report($cfg) {
        // gets top 10 agencies by obligrate
        $year = $cfg['year'];
        $quarter = $cfg['quarter'];
        $query = db_select('t_budget_data', 'bd')
                    ->fields('bd', array('agency', 'approp', 'obligrate'));
        $query->condition('bd.year', $year)
                ->condition('bd.quarter', $quarter)
                ->condition('bd.record', 'budget')
                ->orderBy('obligrate', 'desc')
                ->range(0, 10);
        $res = $query->execute();
        // build chart
        $chartData = array();
        $chartLabels = array();
        $abbrs = dbm_load_agency_abbreviations();
        foreach($res as $row) {
            // add this item
            $chartData[] = array('y'=>floatval($row->approp)/1000, 'dept'=>$row->agency);
            $chartLabels[] = array_key_exists($row->agency, $abbrs) ? $abbrs[$row->agency] : $row->agency;
        }
        // build chart
        $chartCode = "<div class='graph-no-data'>No data available at this time</div>";
        if (!empty($chartData)) {
            array_multisort($chartData, SORT_DESC, $chartLabels);
            $chartLegend = "Q$quarter";
            $chartCode = dgph_build_bar_chart($chartData, $chartLabels,  array('legend'=>$chartLegend));
        }
        $code = "
                    <h4>TOP 10 AGENCIES WITH BEST BUDGET UTILIZATION</h4>
                    <br><br>
                    <div class='icg-con'>$chartCode</div>
                    <div class='row graph-legend'>
                        <p><b>Top 10 Agencies with Best Budget Utilization</b>: this shows the agencies which have the best budget utilization rates (i.e. budgets obligated divided by the budgets released to them by the Department of Budget and Management</p>
                    </div>";
        return $code;
    }
    /**
     * Build the trends report
     * @param $cfg report configuration parameters
     * @return the report code
     */
    function dbm_build_trends_report($cfg) {
        $code = '';
        $trendId = $cfg['trend_id'];
        switch($trendId) {
            case 1:             // Approved vs. Released vs. Utilized Budget
                $code .= dbm_build_trend1_report($cfg);
                break;
            case 2:             // Agencies with Biggest Budgets
                $code .= dbm_build_trend2_report($cfg);
                break;
            case 3:             // Top 10 Agencies with Best Budget Utilization
                $code .= dbm_build_trend3_report($cfg);
                break;
        }
        return $code;
    }
    /**
     * Build the compliance report
     * @param $cfg report configuration parameters
     * @return the report code
     */
    function dbm_build_compliance_report($cfg) {
        // load compliance information
        $cpls = array();
        $year = $cfg['year'];
        $deptId = $cfg['department_id'];
        $query = db_select('t_budget_data', 'bd')
                    ->fields('bd', array('quarter', 'compliance'))
                    ->condition('bd.year', $year)
                    ->condition('bd.compliance', '', '<>');
        $query->join('t_departments', 'dept', 'bd.agency=dept.name');
        $query->condition('dept.id', $deptId)
                ->orderBy('bd.quarter');
        $res = $query->execute();
        foreach($res as $row) {
            $quarterId = $row->quarter;
            $compliance = strtolower($row->compliance);
            if ($compliance=='compliant') {
                $cpls[$quarterId] = 'compliant';
            }
            else if ($compliance=='partial') {
                $cpls[$quarterId] = 'partial-compliant';
            }
            else {
                $cpls[$quarterId] = 'non-compliant';
            }
        }
        $code = "
                    <h4>QUARTERLY REPORTING OF AGENCIES</h4>
                    <br><br>
                    <div class='icg-con'>
                        <ul class='compliance'>";
        for($idx=1; $idx<=4; $idx++) {
            $cplClass = isset($cpls[$idx]) ? $cpls[$idx] : 'not-available';
            $code .= "<li class='$cplClass'><span>Q$idx</span></li>";
        }
        $code .= "
                        </ul>
                    </div>
                    <div class='row graph-legend'>
                        <p><span class='header'>Compliance</span>: this shows the agencies quarterly submission of their Statement of Allotments, Obligations and Balances (SAOBs) to the DBM. The list of agencies which failed to submit their SAOBs during a given quarter can also be seen on this page.</p>
                        <ul class='compliance-legend'>
                            <li class='compliant'><span>Compliant</span> - Submitted SAOBs on time.</li>
                            <li class='partial-compliant'><span>Partial Compliant</span> - Line agencies and departments whose attached agencies have not submitted the SAOBs.</li>
                            <li class='non-compliant'><span>Non Compliant</span> - The entire line agency that have not submitted the SAOB.</li>
                        </ul>
                    </div>";
        return $code;
    }
    /**
     * Build the report for a given pillar
     * @param $pillarId pillar identifier
     * @param $cfg report configuration parameters
     * @return the report code
     */
    function dbm_build_pillar_report($pillarId, $cfg) {
        $code = '';
        switch($pillarId) {
            case 1:             // BUDGET
                $code .= dbm_build_budget_report($cfg);
                break;
            case 2:             // PERFORMANCE TRENDS
                $code .= dbm_build_trends_report($cfg);
                break;
            case 3:             // COMPLIANCE
                $code .= dbm_build_compliance_report($cfg);
                break;
        }
        return $code;
    }
    /**
     * Build the DBM infographics report
     * @param $depId identifier of department we are going to build the report for
     * @param $year the reference year of the report
     * @param $quarter the reference quarter of the report
     * @param $pillarId the pillar identifier
     * @param $trendId the trend identifier
    */
    function dgph_infographics_dbm_report($deptId = 1, $year = 2013, $quarter = 1, $pillarId = 1, $trendId = 1) {
       $rep = array('year' => $year, 'quarter' => $quarter, 'department_id' => $deptId, 'pillar_id' => $pillarId, 'trend_id' => $trendId);
       return theme('dgph_infographics_dbm_report', $rep);
   }
   /**
    * Theme for DBM infographics report
    */
    function theme_dgph_infographics_dbm_report(&$vars) {
        $modPath = drupal_get_path('module', 'dgph_infographics');
        drupal_add_css($modPath.'/css/dgph_infographics_common.css');
        drupal_add_css($modPath.'/css/dgph_infographics_budget.css');
        drupal_add_js($modPath.'/js/dgph_infographics_scripts.js');
        drupal_set_title('Infographics');
        $deptId = $vars['department_id'];
        $year = $vars['year'];
        $quarterId = $vars['quarter'];
        $pillarId = $vars['pillar_id'];
        $trendId = $vars['trend_id'];
        $deptName = get_department_name($deptId);
        $code = "<link href='/sites/all/themes/dgph/css/report.css' rel='stylesheet' type='text/css'>";
        $code .= "<div class='row dashboard-header'>
                    <div class='large-6 columns agency'>
                        <h2>Infographics</h2>
                        <h3>GOVERNMENT BUDGET PERFORMANCE</h3>
			<p>How well do departments use their approved budgets? This dashboard presents data on the financial performance of agencies: how much budgets have been approved and released to them, and how much of these are they able to utilize during a year. This dashboard also presents agencies’ compliance to accountability reporting requirements.</p>
                    </div>       
                    <div class='large-6 columns'>
                        <div class='year-con'>
                            <div class='year'><a href='#' data-dropdown='#select-year'><span>$year</span></a></div>
                            <div id='accordion' class='report-accordion' data-dropdown='#select-agency' data-vertical-offset='-25'>
                                <h3><div class='title-line'>Select an Agency</div></h3>
                                <div>
                                    <div class='home-cat'><p>Departments</p></div>
                                </div> 
                            </div>
                            <div id='select-year' class='dropdown dropdown-tip dropdown-relative'>
                                <ul class='dropdown-menu'>
                                    <li><a href='#'>2013</a></li>
                                    <li><a href='#'>2012</a></li>
                                    <li><a href='#'>2011</a></li>
                                    <li><a href='#'>2010</a></li>
                                </ul>
                            </div>
                            <div id='select-agency' class='dropdown dropdown-tip dropdown-scroll dropdown-relative'>
                                <ul class='dropdown-menu'> 
                                    <li>Department 1</li>
                                    <li>Department 2</li>
                                    <li>Department 3</li>
                                    <li>Department 4</li>
                                    <li>Department 5</li>
                                    <li>Department 6</li>
                                    <li>Department 7</li>
                                    <li>Department 8</li>
                                    <li>Department 9</li>
                                    <li>Department 10</li>
                                </ul>
                            </div>
                        </div>
                    </div> 
                </div>
                <div class='row dashboard-content'>
                    <div class='large-3 columns rightside datarequest choosePillar'>
                        <div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
                            <h3 class='left-ui-accordion-header'>Choose Pillar</h3>
                            <div>
                                <a>Budget</a>
                                <a>Performance Trends</a>
                                <a>Compliance</a>
                            </div>";
        if ($pillarId==2) {
            $code .= "
                            <h3 class='left-ui-accordion-header'>Select Trend</h3>
                            <div>
                                <a>Approved vs. Released vs. Utilized Budget</a>
                                <a>Agencies with Biggest Budgets</a>
                                <a>Top 10 Agencies with Best Budget Utilization</a>
                            </div>";
        }
        if ($pillarId!=3) {
            $code .= "
                            <h3 class='left-ui-accordion-header'>Select Quarter</h3>
                            <div>
                                <form class='custom'>
                                    <label for='dbm_q1'><span class='custom checkbox'></span>QUARTER 1</label> 
                                    <label for='dbm_q2'><span class='custom checkbox'></span>QUARTER 2</label> 
                                    <label for='dbm_q3'><span class='custom checkbox'></span>QUARTER 3</label> 
                                    <label for='dbm_q4'><span class='custom checkbox'></span>QUARTER 4</label>
                                </form>
                            </div>";
        }
        $code .= "
                        </div>
                      </div>
                    <div class='large-9 columns works'>
                        <h2>Department 1</h2>
                        <ul class='social-icon dbm-social-icon'>
                            <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-11.png'></a></li>
                                <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-19.png'></a></li>
                                <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-20.png'></a></li>
                        </ul>
                        <div class='clear'></div>";
        $code .= dbm_build_pillar_report($pillarId, $vars);
        $code .= "
                        <div class='clear'></div>
                        <div class='row'>
                            <div class='large-12 columns legend'>
                                <h1>Legend</h1>
                                <div class='row'>
                                    <h2>Total Approved Budget (Appropriations)</h2>
                                    <p>The total approved budget for an agency includes their budget for the current year as well as carry-over budgets from the previous years.</p><br>
                                    <p>It is an authorization pursuant to law or other legislative enactment directing the payment of goods and services from government funds under specific conditions for the specified purposes.
                                    Government annually prepares and legislates a General Appropriations Act (GAA). There are also automatic appropriations which are covered by special laws and need not be included in GAA to be authorized.</p>
                                </div>
                                <div class='row'>
                                    <h2>Current Year Budget</h2>
                                    <p>The current year budget for an agency includes the agency-specific budget under the General Appropriations Act (GAA, the National Budget) for the current year, its shares from Special Purpose Funds in the GAA, as well as automatic appropriations.</p>
                                </div>
                                <div class='row'>
                                    <h2>Agency Specific Budget</h2>
                                    <p>Under the GAA, each agency is directly allocated with budgetary allocations to be used for their various programs, activities and projects.</p>
                                </div>
                                <div class='row'>
                                    <h2>Special Purpose Funds</h2>
                                    <p>In addition to agency-specific budgets, each agency has a share in the Special Purpose Funds (SPFs) authorized in the GAA.These SPFs cover expenditures for specific purposes for which recipient agencies have not yet been identified during budget preparation. These SPFs include the Calamity Fund, Contingent Fund, Priority Development Assistance Fund and Pension.</p>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <span id='selected-year' style='display:none'>$year</span>
                <span id='selected-agency-id' style='display:none'>$deptId</span>
                <span id='selected-pillar-id' style='display:none'>$pillarId</span>
                <span id='selected-trend-id' style='display:none'>$trendId</span>
                <span id='selected-quarter-id' style='display:none'>$quarterId</span>
                <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>";
        return $code;
   }
?>