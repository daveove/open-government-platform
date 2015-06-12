<?php
    /**
     * Build the budget visualization interface
     */
    function dgph_infographics_budget_visualization() {
        return theme('dgph_infographics_budget_visualization');
    }
    /**
     * Theme for budget visualization interface
     */
    function theme_dgph_infographics_budget_visualization(&$vars) {
        $modPath = drupal_get_path('module', 'dgph_infographics');
        drupal_add_css($modPath.'/include/budget/css/budget.css');
        drupal_add_js($modPath.'/include/budget/js/amcharts/amcharts.js');
        drupal_add_js($modPath.'/include/budget/js/amcharts/serial.js');
        drupal_add_js($modPath.'/include/budget/js/amcharts/pie.js');
        drupal_add_js($modPath.'/include/budget/js/am-yeartoyear-chart.js');
        drupal_add_js($modPath.'/include/budget/js/am-sector-chart.js');
        drupal_add_js($modPath.'/include/budget/js/am-sector-chart-ecserv.js');
        drupal_add_js($modPath.'/include/budget/js/am-sector-chart-socserv.js');
        drupal_add_js($modPath.'/include/budget/js/am-sector-chart-domsec.js');
        drupal_add_js($modPath.'/include/budget/js/am-sector-chart-genpubserv.js');
        drupal_add_js($modPath.'/include/budget/js/am-sector-chart-debt.js');
        drupal_add_js($modPath.'/include/budget/js/am-allotment-capout-chart2.js');
        drupal_add_js($modPath.'/include/budget/js/am-topten-chart.js');
        drupal_add_js($modPath.'/include/budget/js/am-regional-chart.js');
        drupal_add_js($modPath.'/include/budget/js/am-regional-ncr-chart.js');
        drupal_add_js($modPath.'/include/budget/js/am-regional-luzon-chart.js');
        drupal_add_js($modPath.'/include/budget/js/am-regional-visayas-chart.js');
        drupal_add_js($modPath.'/include/budget/js/am-regional-mindanao-chart.js');
        drupal_add_js($modPath.'/include/budget/js/am-regional-regionalized-chart.js');
        drupal_add_js($modPath.'/include/budget/js/common.js');
        drupal_set_title('Infographics - Budget Visualization');
        $code = "
                    <div id='page-nav'>
                        <div class='row'>
                            <div class='large-12 columns'>
                                    <ul>
                                    <li><a href='#year'>Year-On-Year</a></li>
                                    <li><a href='#sector'>Budget by Sector</a></li>
                                    <li><a href='#allotment'>Budget by Allotment</a></li>
                                    <li><a href='#top10'>Top 10</a></li>
                                    <li><a href='#regional'>Regional</a></li>
                                </ul>
                            </div>
                        </div>
                    </div>
                    <div id='intro'>
                            <div class='row'>
                            <div class='large-6 columns'>
                                <p>The Budget is the financial expression of approved plans and programs to be supported by revenues. It consists of the estimated income and planned expenditures in a given year. Budgeting enables the manage its scarce financial resources to support priority programs and projects for promoting economic growth and providing public services.</p>
                                <p>The annual preparation of Budget ensures that all spending is reviewed and justified anew each year. The also adopts a three-year perspective, which ensures that remains strategic in managing its resources.</p>
                            </div>
                            <div class='large-6 columns'>
                                <p>The formulation of the Budget is done through four phases: Preparation, Legislation, Execution and Accountability. These four phases overlap in continuing cycles every year. For instance, while the Executive implements the budget for the current year, it also prepares the budget for the next fiscal year or defends it before Congress. Meanwhile, the Execution and Accountability phases are implemented simultaneously year-round.</p>
                                <p>In this budget visualization, you will see the Budget in a given year. Also featured are the different representations on how the Budget is allocated. The allocation of the Budget is divided among Economic Services, Social Services, Defense, General Public Services, and Debt Burden. Another representation is the allocation of the Budget by Allotment Class, which is composed of Personnel Services (PS), Maintenance and Other Operating Expenses (MOOE), and Capital Outlays (CO). Finally, the allocation of the Budget by Region is divided among Central, Nationwide, and Regional Offices of agencies.</p>
                            </div>
                        </div>
                    </div>  
                    <div id='year'>
                        <div class='row'>
                            <div class='large-12 columns header'>
                                    <h1>Year-On-Year Budget Program, 2010-2013 </h1>
                                
                            </div>
                        </div>
                        <div class='row'>
                            <div class='large-12 columns chart'>
                                <div id='yeartoyear-chart'></div>
                            </div>
                        </div>
                    </div>
                    <div id='sector'>
                        <div class='row header'>
                            <div class='large-12 columns'>
                                <h1>GOVERNMENT EXPENDITURES, OBLIGATION BASIS, BY SECTOR</h1>
                            </div>
                            <div class='row'>
                                <div class='large-2 columns offset-by-four'>
                                    <select onchange='onChange2nd(this)'>
                                        <option>2010</option>
                                        <option>2011</option>
                                        <option>2012</option>
                                        <option>2013</option>
                                    </select>
                                </div>
                                <div class='large-2 columns million'>
                                    <span>in millions</span>
                                </div>
                            </div>
                            <div class='row'>
                                <p class='instructions'>Hover over the graphic to see the Sector and amount. Click graphic to see the breakdown.</p>
                            </div>
                        </div>
                        <div class='row'>
                            <div class='chart' style='position:relative;'>
                                <div id='sector-chart'></div>
                                <div id='sector-chart-ecserv'></div>
                                <div id='sector-chart-socserv'></div>
                                <div id='sector-chart-domsec'></div>
                                <div id='sector-chart-genpubserv'></div>
                                <div id='sector-chart-debt'></div>
                            </div>
                        </div>
                        <div class='row blurb'>
                            <div class='large-12 columns'>
                                <h3>budget sector</h3>
                                <p><b>Economic Services</b> are government expenditures that are intended to support economic development, including agriculture, transport infrastructure, tourism, among others.</p>
                                <p><b>Social Services</b> represent government spending to improve the living conditions of citizens, particularly the poor, through education, health, social security and others.</p>
                                <p><b>Defense</b> refers to expenditures that support the general effort to ensure national security, stability and peace.</p>
                                <p><b>General Public Services</b> are expenditures for general administration (such as fiscal management, foreign affairs, lawmaking, etc.) and public order and safety.</p>
                                <p><b>Debt Burden</b> includes interest payments on national government's domestic and foreign debt, as well as net lending to government corporations for their debt that are guaranteed by the national government.</p>
                            </div>
                        </div>
                    </div>
                    <div id='allotment'>
                        <div class='row header'>
                            <div class='large-12 columns'>
                                <h1>budget program by allotment class, 2010-2013</h1>
                            </div>
                            <div class='row'>
                                <p>Hover over the graphic to see the year and amount.</p>
                            </div>
                        </div>
                        <div class='row'>
                            <div class='chart' style='position:relative; height:500px;'>
                                <div id='capout-chart-2010' style='width:100%'></div>
                                 <div id='totals'></div>
                            </div>
                        </div>
                        <div class='row blurb'>
                            <div class='large-12 columns'>
                                <h3>BUDGET BY ALLOTMENT CLASS</h3>
                                <p><b>Allotment by Year</b> Allotment will change per year, as such there needs to be a selection/dropbox menu which allows users to select the year (2010, 2011, 2013 etc). </p>
                                <p><b>Personnel Services</b> are for the payment of salaries, wages and other compensation of permanent, temporary, contractual, and casual employees of the government.</p>
                                <p><b>Maintenance and Other Operating Expenditures</b> or MOOEs are for the purchase of goods and services (e.g. supplies, maintenance, utilities, professional services, etc.)
                                for the conduct of normal government operations as well as the implementation of programs.</p>
                                <p><b>Capital Outlays</b> or CO refer to appropriations for purchasing goods and services that add to the Government's assets,  including investments in the capital stock of 
                                GOCCs and their subsidiaries,  and produce long-term benefits (e.g., the acquisition of buildings, land, motor vehicles, equipment).</p>
                            </div>
                        </div>
                    </div>
                    <div id='top10'>
                        <div class='row'>
                            <div class='header large-12 columns'>
                                <h1>Top ten departments, 2010-2013</h1>
                                <div class='row'>
                                    <div class='large-2 columns offset-by-four'>
                                        <select onchange='onChange4th(this)'>
                                            <option>2013</option>
                                            <option>2012</option>
                                            <option>2011</option>
                                            <option>2010</option>
                                        </select>
                                    </div>
                                    <div class='million large-2 columns'>
                                        <span>in thousands</span>
                                    </div>
                                </div>
                            </div>
                        </div>
                        <div class='row'>
                            <div class='large-12 columns chart'>
                                <div id='topten-chart'></div>
                            </div>
                        </div>
                        <div class='row blurb'>
                            <div class='large-12 columns'>
                                <p>Pertains to the specific budget of the department only (does not include  other sources, i.e., Special Purpose Fund and Automatic Appropriations.)</p>
                            </div>
                        </div>
                    </div>
                    <div id='regional'>
                            <div class='row header'>
                                <div class='large-12 columns'>
                                    <h1>Regional Allocation of the Expenditure Program</h1>
                                </div>
                                <div class='row'>
                                    <div class='large-2 columns offset-by-four'>
                                        <select onchange='onChange5nd(this)'>
                                            <option>2010</option>
                                            <option>2011</option>
                                            <option>2012</option>
                                            <option>2013</option>
                                        </select>
                                    </div>
                                    <div class='million large-2 columns'>
                                        <span>in thousands</span>
                                    </div>
                                </div>
                                <div class='row'>
                                    <p>Click the graphic to see the breakdown. Hover over graphic to see the amount.</p>
                                </div>
                            </div>
                            <div class='row'>
                                <div class='large-12 columns chart' id='divGroup' style='position:relative; height:500px;'>
                                    <div class='offset-by-four' style='position:absolute; left: 30%; top: 90%;opacity:0;' id='divEconomics'><img src='/wb-dgph/sites/all/modules/dgph_infographics/include/budget/images/legend-economics.png' /></div>
                                    <div class='offset-by-four' style='position:absolute; left: 30%; top: 90%;opacity:0;' id='divSocial'><img src='/wb-dgph/sites/all/modules/dgph_infographics/include/budget/images/legend-social.png' /></div>
                                    <div id='whole-pies'>
                                    <div id='regional-chart'></div>
                                    <img src='/wb-dgph/sites/all/modules/dgph_infographics/include/budget/images/whole-pies.gif' id='test_close' onClick='bigMap()'/>
                                </div>
                                <div id='regional-ncr-chart'></div>
                                <div id='regional-luzon-chart'></div>
                                <div id='regional-visayas-chart'></div>
                                <div id='regional-mindanao-chart'></div>
                                <div id='regional-regionalized-chart'></div>
                            </div>
                        </div>
                        <div class='row blurb'>
                            <div class='chart large-12 columns'>
                                <h3>allocation of the expenditure program</h3>
                                <p><b>Central Office</b> For central offices of agencies.</p>
                                <p><b>Nationwide</b> For nationwide agencies that do not have offices.</p>
                                <p><b>2003-2004 Adjusted Figures</b> Budget Technical Service.</p>
                                <p><b>2005-2006 & 2009 Proposed Figures</b> Budget of Expenditures and Sources of Financing.</p>
                                <p><b>2008-2010 GAA Figures</b> Budget Technical Service.</p>
                                <p><b>2011-2013 BESF Figures</b> Budget of Expenditures and Sources of Financing.</p>
                            </div>
                        </div>
                    </div>";
        return $code;
   }
?>