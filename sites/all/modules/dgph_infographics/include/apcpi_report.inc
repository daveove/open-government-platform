<?php
    /**
     * Get items information
     * @param $year the year
     * @param $deptId the department identifier
     * @param $pillarId the pillar identifier
     * @return list of items information
     */
    function apcpi_get_items($year, $deptId, $pillarId) {
        $items = array();
        if ($pillarId>0) {
            // get pillar items
            $query = db_select('t_procurement_indicators', 'pi')
                        ->fields('pi', array('indicator_id', 'indicator', 'item_id', 'item', 'benchmark', 'average_all_results'));
            $query->join('t_procurement_indicators_departments', 'pid', 'pi.id = pid.procurement_indicator_id');
            $query->join('t_departments', 'dept', 'pid.department_code = dept.code');
            $query->fields('pid', array('result'))
                    ->condition('pi.year', $year)
                    ->condition('pi.pillar_id', $pillarId)
                    ->condition('dept.id', $deptId)
                    ->orderBy('pi.indicator_id');
            $res = $query->execute();
            foreach($res as $row) {
                // add this item
                $item['iid'] = $row->indicator_id;
                $item['indicator_title'] = $row->indicator;
                $item['item_id'] = $row->item_id;
                $item['item_title'] = $row->item;
                $item['recommended_benchmark'] = $row->benchmark;
                $item['average_result'] = $row->average_all_results;
                $item['department_result'] = $row->result;
                $items[] = $item;
            }
        }
        else if ($deptId>0) {
            // gets averages for this agency
            $query = db_select('t_procurement_indicators_averages', 'pav')
                        ->fields('pav', array('pillar_id', 'average_rating'));
            $query->join('t_departments', 'dept', 'pav.department_code = dept.code');
            $query->condition('pav.year', $year)
                    ->condition('dept.id', $deptId)
                    ->orderBy('pav.pillar_id');
            $res = $query->execute();
            foreach($res as $row) {
                // add this item
                $item['dept_id'] = $deptId;
                $item['pillar_id'] = $row->pillar_id;
                $item['average_rating'] = $row->average_rating;
                $items[] = $item;
            }
        }
        else {     
            // gets total averages by pillar
            $query = db_select('t_procurement_indicators', 'pi')
                        ->fields('pi', array('pillar_id', 'average_all_ratings'));
            $query->condition('pi.year', $year)
                  ->condition('pi.pillar', 'Pillar Total Average', 'like')
                  ->orderBy('pi.pillar_id');
            $res = $query->execute();
            foreach($res as $row) {
                // add this item
                $item['dept_id'] = $deptId;
                $item['pillar_id'] = $row->pillar_id;
                $item['average_rating'] = $row->average_all_ratings;
                $items[] = $item;
            }
        }
        return $items;
    }
    /**
     * Build the agency procurement compliance infographics
     * @param $depId identifier of department we are going to build the report for, or <code>0</code> to get the average scores for all departments
     * @param $year the reference year of the report) 
     * @param pillarId the pillar identifier, or <code>0</code> to get the average scores report for the specified agency
     */
    function dgph_infographics_procurement_compliance($deptId = 0, $year = 2011, $pillarId = 0) {
        $rep = array('year' => $year, 'department_id' => $deptId, 'pillar_id' => $pillarId);
        if (($deptId==0) && ($pillarId>0)) {
            // redirect to default department
            drupal_goto("infographics/procurement-compliance/1/$year/$pillarId");
        }
        else if (($pillarId==0) && ($deptId>0)) {
            // redirect to default pillar
            drupal_goto("infographics/procurement-compliance/$deptId/$year/1");
        }
        // gets items information
        $rep['items'] = apcpi_get_items($year, $deptId, $pillarId);
        return theme('dgph_infographics_procurement_compliance', $rep);
    }
   
    /**
     * Gets information about a given set of items into the APCPI report
     * @param $items the report items to look for
     * @param $indicatorId the item indicator identifier
     * @param $itemId the item identifier, or <code>null</code> to get all the items for this indicator
     * @return the item(s) information, or <code>null</code> if not found
     */
    function apcpi_find_items($items, $iid, $itemId = null) {
        $resItems = null;
        foreach($items as $curItem) {
            if ($curItem['iid']==$iid) {
                if (null==$itemId) {
                    // add this item to the result
                    if (null==$resItems) {
                        $resItems = array();
                    }
                    $resItems[] = $curItem;
                }
                else if ($curItem['item_id']==$itemId) {
                    //found
                    $resItems = $curItem;
                    break;
                }
            }
        }
        return $resItems;
    }
    /**
     * Build the report for pillar 1
     * @param @year the report year
     * @param $items the report items
     * @return the pillar 1 report
     */
    function apcpi_get_pillar1_code($year, $items) {
        $i11 = apcpi_find_items($items, 1, 'a');
        $i2 = apcpi_find_items($items, 2);
        $i3 = apcpi_find_items($items, 3);
        $fmt = new NumberFormatter('en_US', NumberFormatter::PERCENT);
        // build alternative methods of procurement chart
        $chart11Data = array(floatval($i2[0]['department_result'])*100.0, floatval($i2[1]['department_result'])*100.0,
                      floatval($i2[2]['department_result'])*100.0, floatval($i2[3]['department_result'])*100.0,
                      floatval($i2[4]['department_result'])*100.0);
        $chart11Labels = array($i2[0]['item_title'], $i2[1]['item_title'], $i2[2]['item_title'], $i2[3]['item_title'], $i2[4]['item_title']);
        $chart11Code = dgph_build_bar_chart($chart11Data, $chart11Labels, array('legend'=>$year));
        // build competitiveness of bidding process chart
        $chart12Data = array(floatval($i3[0]['department_result']), floatval($i3[1]['department_result']), floatval($i3[2]['department_result']));
        $chart12Labels =  array($i3[0]['item_title'], $i3[1]['item_title'], $i3[2]['item_title']);
        $chart12Code = dgph_build_bar_chart($chart12Data, $chart12Labels, array('legend'=>$year));
        $code = "
                    <h4>LEGISLATIVE & REGULATORY FRAMEWORK</h4>
                    <h1>Competitive Bidding as Default Procurement Method</h1>
                    <br><br>
                    <div class='geps-con geps-con-p1'>
                        <div class='geps-left'>
                            <div class='geps left-heading'>
                                <p>% of public bidding contracts<br>in terms of amount of total<br>procurement</p>
                            </div>
                            <div class='geps recommended-benchmark'>
                                <h1>Recommended Benchmark</h1>
                                <p class='value'>".$fmt->format($i11['recommended_benchmark'])."</p>
                            </div>
                            <div class='geps average-result'>
                                <h1>Average Result</h1>
                                <p class='value'>".$fmt->format($i11['average_result'])."</p>
                            </div>
                        </div>
                        <div class='geps-right'>
                            <div class='geps result'>
                                <h1>Result</h1>
                                <p class='value'>".$fmt->format($i11['department_result'])."</p>
                            </div>
                        </div>
                    </div>  	
                    <h1>Limited Use of Alternative Methods of Procurement</h1>
                    <div class='icg-con'>$chart11Code</div>	
                    <h1>Competitiveness of the Bidding Process</h1>
                    <div class='icg-con icg-con-last'>$chart12Code</div>";
        return $code;
    }
    /**
     * Extract percent value from string
     * @param str source string
     * @return the percent value (0-100)
     */
    function apcpi_extract_percent($str) {
        $perc = 0;
        $str = trim($str);
        $pos = strpos($str, '%');
        if ($pos>-1) {
            $perc = substr($str, 0, $pos);
        }
        return $perc;
    }
   /**
    * Build the report for pillar 2
    * @param @year the report year
    * @param $items the report items
    * @return the pillar 2 report
    */
    function apcpi_get_pillar2_code($year, $items) {
        $i62 = apcpi_find_items($items, 6, 'b');
        $i63 = apcpi_find_items($items, 6, 'c');
        // build chart
        $chart16Data = array(floatval($i62['department_result'])*100.0, floatval($i63['department_result'])*100.0);
        $chart16Labels = array($i62['item_title'], $i63['item_title']);
        $chart16Code = dgph_build_bar_chart($chart16Data, $chart16Labels, array('legend'=>$year, 'max'=>100));
        $code = "
                    <h4>INSTITUTIONAL FRAMEWORK AND MANAGEMENT CAPACITY</h4>
                    <h1>Use of Government Electronic Procurement System</h1>
                    <br><br>
                    <div class='icg-con icg-con-last'>$chart16Code</div>";
        return $code;
    }
    
   /** 
    * Formats a CDS label
    * @param $label the label
    * @return the formatted label
    */
    function apcpi_format_cds($label) {
        $label = str_replace("CDs", "<div class='calendar_days'>Calendar Days</div>", $label);
        $label = str_replace("NLT", "<div class='not_less_than'>Not Less Than Calendar Days</div>", $label);
        $label = str_replace("LT", "<div class='less_than'>Less Than Calendar Days</div>", $label);
        $label = str_replace("MT", "<div class='not_less_than'>More Than Calendar Days</div>", $label);
        return $label;
    }
    
   /**
    * Build the report for pillar 3
    * @param @year the report year
    * @param $items the report items
    * @return the pillar 3 report
    */
    function apcpi_get_pillar3_code($year, $items) {
        $i9 = apcpi_find_items($items, 9);
        $i10a = apcpi_find_items($items, 10, 'a');
        // build chart
        $chartData = array();
        $chartLabels = array();
        for($i=0;$i<3;$i++) {
            $deptRes = $i9[$i]['department_result'];
            if (!empty($deptRes) && ($deptRes!='n/a')) {
                $chartData[] = intval($deptRes*100);
            }
            else {
                $chartData[] = 0;
            }
            $chartLabels[] = $i9[$i]['item_title'];
        }
        $chartCode = dgph_build_bar_chart($chartData, $chartLabels, array('legend'=>$year, 'max'=>100));
        $code = "
                    <h4>PROCUREMENT OPERATIONS AND MARKET PRACTICES</h4>
                    <h1>Compliance with Procurement Timeframes</h1>
                    <br><br>
                    <div class='icg-con icg-con-last'>$chartCode</div>	
                    <h4 class='payments-released'>Timely Payment of Procurement Contracts</h4>
                    <div class='geps-con geps-con-p3'>
                        <div class='geps-left'>
                            <div class='geps'>
                            </div>
                            <div class='geps phil-geps-recommended-benchmark'>
                                <h1>Recommended Benchmark</h1>
                                <h2 class='cds'>".apcpi_format_cds($i10a['recommended_benchmark'])."</h4>
                            </div>
                            <div class='geps phil-geps-average-result'>
                                <h1>Average Result</h1>
                                <h2 class='cds'>".apcpi_format_cds($i10a['average_result'])."</h4>
                            </div>
                        </div>
                        <div class='geps-right geps-right-cds'>
                            <div class='geps phil-geps-result'>
                                <h1>Agency Result</h1>
                                <h2 class='cds'>".apcpi_format_cds($i10a['department_result'])."</h4>
                            </div>
                        </div>
                    </div>";
        return $code;
    }
   /**
    * Build the report for pillar 4
    * @param @year the report year
    * @param $items the report items
    * @return the pillar 4 report
    */
    function apcpi_get_pillar4_code($year, $items) {
        $i14a = apcpi_find_items($items, 14, 'a');
        $i14b = apcpi_find_items($items, 14, 'b');
        // build chart
        $chart = array(
                '#type' => 'chart',
                '#chart_type' => 'pie',
                '#title' => $year,
                '#legend' => true,
                '#legend_position' => 'bottom',
                '#colors' => array('#1984C7', '#FF9E1D', '#E3E3E3'),
                '#height' => '400px'
        );
        $deptRes = floatval($i14b['department_result'])*100.0;
        $chart['chart_yaxis'] = array(
            '#type' => 'chart_data',
            '#data' => array(array('Attendance', $deptRes), array('No Attendance', (100-$deptRes)))
        );
        $chartCode = drupal_render($chart);
        $code = "
                    <h4>INTEGRITY AND TRANSPARENCY OF THE AGENCY PROCUREMENT SYSTEM</h4>
                    <h1 class='payments-released'>Observers are invited to all stages of every public bidding activity</h1>
                    <div class='geps-con geps-con-p4'>
                        <div class='geps-left'>
                            <div class='geps'>
                            </div>
                            <div class='geps phil-geps-recommended-benchmark'>
                                <h1>Recommended Benchmark</h1>
                                <h2>".$i14a['recommended_benchmark']."</h4>
                            </div>
                            <div class='geps phil-geps-average-result'>
                                <h1>Average Result</h1>
                                <h2>".$i14a['average_result']."</h4>
                            </div>
                        </div>
                        <div class='geps-right geps-right'>
                            <div class='geps phil-geps-result'>
                                <h1>Agency Result</h1>
                                <h2>".$i14a['department_result']."</h4>
                            </div>
                        </div>
                    </div>
                    <h1>Percentage of Attendance of Observers in Public Bidding Activities</h1>
                    <br><br>
                    <div class='icg-con icg-con-last icg-con-p4'>$chartCode</div>
                    <div class='row graph-legend'>
                        <p><span class='header'>Note</span>: To enhance the transparency of the procurement process, RA 9184 and it revised IRR requires the Bids and Awards Committee to invite observers in all stages of the procurement process. However, the absence of observers will not nullify the BAC proceedings, provided that they have been duly invited in writing.</p>
                    </div>";
        return $code;
    }
   /**
    * Build the agency averages report
    * @param @year the report year
    * @param $items the report items
    * @return the pillar 4 report
    */
    function apcpi_get_averages_code($year, $items) {
        // build chart
        $chartData = array();
        foreach($items as $item) {
            $chartData[] = floatval($item['average_rating']);
        }
        $chartLabels = array('Average', 'Pillar I', 'Pillar II', 'Pillar III', 'Pillar IV');
        $chartCode = dgph_build_bar_chart($chartData, $chartLabels, array('legend'=>$year, 'max'=>3));
        $deptId = !empty($items) ? $items[0]['dept_id'] : 0;
        $title = ($deptId>0) ? 'Agency Average Ratings' : 'Average Rating of 18 Agencies';
        $code = "
                    <h4>$title</h4>
                    <br><br>
                    <div class='icg-con'>$chartCode</div>
                    <div class='clear'></div>
                    <div class='large-12 columns legend'>
                        <h1>Legend</h1>
                        <div class='row'>
                            <h2>Pillar I. Regulatory Framework</h2>
                            <p>Pillar I looks at the agency compliance to key legal requirements and its associated issuances as it relates to competitiveness in the procurement process.</p>
                        </div>
                        <div class='row'>
                            <h2>Pillar II. Agency Institutional Framework and Management Capacity</h2>
                            <p>Pillar II looks at the operations of the procurement system through the management systems of the agency. This Pillar consists of indicators verifying the planning and monitoring mechanism of the agency as well as the number of postings made.</p>
                        </div>
                        <div class='row'>
                            <h2>PILLAR III. Procurement Operations and Market Practices</h2>
                            <p>Pillar III looks into the operational effectiveness and efficiency of the procurement system at the agency level. This includes indicators relating to timely payment of contracts and compliance with procurement timeframes.</p>
                        </div>
                        <div class='row'>
                            <h2>PILLAR IV. Integrity and Transparency of the Agency Procurement System</h2>
                            <p>Pillar IV comprises indicators that check the integrity and transparency of the procurement system such as the agency’s compliance with the requirement of inviting observers to all stages of every public bidding activity.</p>
                        </div>
                        <div class='row'>
                            <h2>Scoring</h2>
                            <p>The scoring system uses a four-point rating scale based on the recommended benchmark or a set of conditions. Performance above the threshold will merit a satisfactory or very satisfactory rating and performance below will receive an acceptable or poor score. For indicators with a scoring criteria based on a set of conditions, the rating varies depending on the number of conditions met.</p>
                        </div>
                    </div>";
        return $code;
    }
   /**
    * Build the report for any given pillar
    * @param $pillarId the pillar identifier
    * @param $year the year this report is for
    * @param $items the report items
    * @return the report code
    */ 
    function apcpi_get_pillar_code($pillarId, $year, $items) {
        $code = '';
        switch($pillarId) {
            case 0:             // AGENCY AVERAGES
                $code .= apcpi_get_averages_code($year, $items);
                break;
            case 1:             // COMPLIANCE WITH LEGISLATIVE AND REGULATORY FRAMEWORK
                $code .= apcpi_get_pillar1_code($year, $items);
                break;
            case 2:             // AGENCY INSTITUTIONAL FRAMEWORK AND MANAGEMENT CAPACITY
                $code .= apcpi_get_pillar2_code($year, $items);
                break;
            case 3:             // PROCUREMENT OPERATIONS AND MARKET PRACTICES
                $code .= apcpi_get_pillar3_code($year, $items);
                break;
            case 4:             // INTEGRITY AND TRANSPARENCY OF AGENCY PROCUREMENT SYSTEM
                $code .= apcpi_get_pillar4_code($year, $items);
                break;
        }
        return $code;
    }
    /**
     * Theme for agency procurement compliance infographics
     */
    function theme_dgph_infographics_procurement_compliance(&$vars) {
        $modPath = drupal_get_path('module', 'dgph_infographics');
        drupal_add_css($modPath.'/css/dgph_infographics_common.css');
        drupal_add_css($modPath.'/css/dgph_infographics_apcpi.css');
        drupal_add_js($modPath.'/js/dgph_infographics_scripts.js');
        drupal_set_title('Infographics');
        $deptId = $vars['department_id'];
        $year = $vars['year'];
        $pillarId = $vars['pillar_id'];
        $items = $vars['items'];
        $deptName = ($deptId>0) ? get_department_name($deptId) : 'Agency Averages';
        $code = "<link href='".base_path()."/sites/all/themes/dgph/css/procurement.css' rel='stylesheet' type='text/css'>";
        $code .= "<div class='row dashboard-header'>
                    <div class='large-6 columns agency'>
                        <h2>Infographics</h2>
                        <h3>OPEN PROCUREMENT: PROCUREMENT COMPLIANCE AND PERFORMANCE INDICATOR SYSTEM RESULTS AND RATINGS</h3>
			<p>The system is a procurement monitoring, assessment and evaluation tool developed to determine, in a qualitative and quantitative manner, procurement strengths and weaknesses of agencies, and formulate a reasonable action plan to address identified risks while adopting measures to sustain strengths alongside a competitive, transparent, economical, efficient and accountable public procurement regime.</p>
                        <p>The results of the assessment were submitted by the procuring entities and were duly confirmed with their authorized representatives. The final ratings were approved and submitted by the Head of the Procuring Entity or the latter was duly notified of the confirmed results.</p>
                    </div>       
                    <div class='large-6 columns'>
                        <div class='year-con'>
                            <div class='year'><a href='#' data-dropdown='#select-year'><span>$year</span></a></div>
                            <div id='accordion' class='procurement-accordion' data-dropdown='#select-agency' data-vertical-offset='-25'>
                                <h3><div class='title-line'>Select an Agency</div></h3>
                                <div>
                                    <div class='home-cat'><p>$deptName</p></div>
                                </div> 
                            </div>
                            <span id='selected-year' style='display:none'>$year</span>
                            <span id='selected-agency-id' style='display:none'>$deptId</span>
                            <span id='selected-pillar-id' style='display:none'>$pillarId</span>
                            <div id='select-year' class='dropdown dropdown-tip dropdown-relative'>
                                <ul class='dropdown-menu'>
                                    <li><a>2012 - COMING SOON</a></li>
                                    <li><a>2011</a></li>
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
                        </div>";
        if ($pillarId==0) {
            // agency averages
            $code .= "
                        <div class='know-more-about'>
                            <div class='know-text'>To learn more about procurement and click on the links below:</div>
                            <div class='know-buttons'>
                                <ul class='procurement-buttons'>
                                    <li><a href='#'>Know More About Procurement</a></li>
                                    <li><a href='#'>Know More About</a></li>
                                </ul>
                            </div>
                        </div>";
        }
        $code .= "
                    </div> 
                </div>
                <div class='row dashboard-content'>
                    <div class='large-3 columns rightside datarequest choosePillar'>
                        <div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
                            <h3 class='left-ui-accordion-header'>Choose Pillar</h3>
                            <div>
                                <a>Legislative & Regulatory Framework</a>
                                <a>Institutional Framework & Management Capacity</a>
                                <a>Procurement operations & market practices</a>
                                <a>Integrity & transparency of the procurement system</a>
                            </div> 
                            <h3 class='left-ui-accordion-header'>Compare by year</h3>
                            <div>
                                <form class='custom'>
                                    <label for='checkbox2'><input type='checkbox' style='display: none;' id='checkbox2' disabled='disabled'><span class='custom checkbox'></span> 2012 - COMING SOON</label> 
                                    <label for='checkbox3' checked='checked'><input type='checkbox' style='display: none;' id='checkbox3' checked='checked' disabled='disabled'><span class='custom checkbox'></span> 2011 [Default] </label> 
                                </form>
                            </div> 
                        </div>
                        <a href='#' class='procurement apcpi-proc'>Go to Procurement Notices & Details</a>
                    </div>
                    <div class='large-9 columns works'>
                        <h2>$deptName</h2>
                        <ul class='social-icon apcpi-social-icon'>
                           <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-11.png'></a></li>
                                <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-19.png'></a></li>
                                <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-20.png'></a></li>
                        </ul>
                        <div class='clear'></div>";
        $code .= apcpi_get_pillar_code($pillarId, $year, $items);
        $code .= "
                    </div>
                </div>
                <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>";
        return $code;
    }
?>