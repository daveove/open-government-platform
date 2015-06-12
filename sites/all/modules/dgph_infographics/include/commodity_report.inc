<?php
    /**
     * View By
     */
    define('VIEW_BY_MONTH', 1);
    define('VIEW_BY_YEAR', 2);
    
    /**
     * Get the name of a macro - category
     * @param $mid the macro - category identifier
     * @return the name of the macro - category
     */
    function cd_get_macro_category_name($mid) {
        $macroCats = array('GAS & FUEL', 'CONSUMER GOODS', 'AGRICULTURAL PRODUCTS', 'BASIC MEDICINES');
        return ($mid>=1 && $mid<=count($macroCats)) ? $macroCats[$mid-1] : '';
    }
    /**
     * Get the list of categories in a macro-category
     * @param $mid the macro-category identifier
     * @return the category names
     */
    function cd_get_category_names($mid) {
        $cats = array();
        switch($mid) {
            case 1: // GAS & FUEL
                $cats = array('oil products');
                break;
            case 2: // CONSUMER GOODS
                $cats = array('canned sardines', 'instant noodles', 'processed milk', 'bread');
                break;
            case 3: // AGRICULTURAL PRODUCTS
                $cats = array('commercial rice', 'sugar', 'cooking oil', 'meat and poultry', 'fish', 'vegetables');
                break;
            case 4: // BASIC MEDICINES
                $cats = array('cardiovascular', 'anti-bacterial', 'anti-asthma', 'anti-diabetes', 'anti-hypercholesterolemia', 'anti-cancer');
                break;
        }
        return $cats;
    }
    
    /**
     * Get categories within a given macro category
     * @param mid the macro - category identifier
     * @return the list of category identifiers
     */
    function cd_get_categories($mid) {
        $cids = array();
        $cats = cd_get_category_names($mid);
        foreach($cats as $cat) {
            $query = db_select('pm_categories', 'cat')
                        ->fields('cat', array('cid'))
                        ->condition('cat.title', $cat, 'like');
            $cids[$cat] = $query->execute()->fetchColumn();
        }
        return $cids;
    }
    /**
     * Gets sub-categories of a given category
     * @param cid the category identifier
     * @return the list of sub-category identifiers
     */
    function cd_get_sub_categories($cid) {
        $subCids = array();
        $query = db_select('pm_categories', 'cat')
                        ->fields('cat', array('cid'))
                        ->condition('cat.parent', $cid);
        $res = $query->execute();
        foreach($res as $row) {
            $subCids[] = $row->cid;
        }
        if (empty($subCids)) {
            // no sub-categories
            $subCids[] = $cid;
        }
        return $subCids;
    }
    /**
     * Load a monthly view of the products prices information from the database
     * @param $year the reference year
     * @param $mid macro-category identifier
     * @param $month the month number (1 = January, 2 = February, etc ...)
     */
    function cd_get_prices_by_month($year, $mid, $month) {
        $pinfo = array();
        // load category identifiers
        $cids = cd_get_categories($mid);
        foreach($cids as $cat => $cid) {
            // gets sub-categories
            $subCids = cd_get_sub_categories($cid);
            foreach($subCids as $subCid) {
                $query = db_select('pm_products', 'p')
                            ->fields('p', array('pid', 'title', 'price_unit'));
                $query->join('pm_categories', 'cat', 'p.cid = cat.cid');
                $query->join('pm_product_price', 'pp', 'p.pid = pp.pid');
                $query  ->fields('pp', array('price', 'dated'))
                        ->condition('p.cid', $subCid)
                        ->where("year(pp.dated) = $year")
                        ->where("month(pp.dated) = $month");
                $res = $query->execute();
                foreach($res as $row) {
                    // add this item
                    $ptitle = $row->title;
                    $pdate = $row->dated;
                    $price = $row->price;
                    $priceUnit = !empty($row->price_unit) ? $row->price_unit : '';
                    $pinfo[$cat][$pdate][$ptitle] = array('price'=>$price, 'unit'=>$priceUnit);
                }
            }
        }
        return $pinfo;
    }
    /**
     * Load a yearly view of the prices information about a given product
     * @param $pname the product name
     * @param $year the reference year
     * @return array the product prices information
     */
    function cd_get_product_prices_by_year($pname, $year) {
        $MONTHS = array(1=>'Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec');
        $chartData = array();
        foreach ($MONTHS as $idx=>$month) {
            $query = db_select('pm_products', 'p');
            $query->addExpression("avg(cast(pp.price as decimal(10,2)))", "avg_price");
            $query->join('pm_product_price', 'pp', 'p.pid = pp.pid');
            $query->condition('p.title', $pname, 'like')
                  ->where("year(pp.dated) = $year")
                  ->where("month(pp.dated) = $idx");
            $avgPrice = $query->execute()->fetchColumn();
            $customCategory = date('F Y', strtotime("$month $year"));
            $chartData[] = array('y'=>floatval($avgPrice), 'customCategory'=>$customCategory);
        }
        return $chartData;
    }
    /**
     * Load a yearly view of the products prices information from the database
     * @param $year the reference year
     * @param $mid macro-category identifier
     * @return the product prices information
     */
    function cd_get_prices_by_year($year, $mid) {
        $pinfo = array();
        // load category identifiers
        $cids = cd_get_categories($mid);
        foreach($cids as $cat => $cid) {
            // gets sub-categories
            $subCids = cd_get_sub_categories($cid);
            foreach($subCids as $subCid) {
                for ($month=1; $month<=12; $month++) {
                    $query = db_select('pm_products', 'p')
                            ->fields('p', array('pid', 'title', 'price_unit'));
                    $query->addExpression("avg(cast(pp.price as decimal(10,2)))", "avg_price");
                    $query->join('pm_categories', 'cat', 'p.cid = cat.cid');
                    $query->join('pm_product_price', 'pp', 'p.pid = pp.pid');
                    $query  ->condition('p.cid', $subCid)
                            ->where("year(pp.dated) = $year")
                            ->where("month(pp.dated) = $month")
                            ->groupBy('p.title');
                    $res = $query->execute();
                    foreach($res as $row) {
                        // add this item
                        $ptitle = $row->title;
                        $avgPrice = $row->avg_price;
                        $priceUnit = !empty($row->price_unit) ? $row->price_unit : '';
                        $pinfo[$cat][$month][$ptitle] = array('price'=>$avgPrice, 'unit'=>$priceUnit);
                    }
                }
            }
        }
        return $pinfo;
    }
    /**
     * Load products prices information from the database
     * @param $year the reference year
     * @param $mid macro-category identifier
     * @param $viewBy view mode (1 = month, 2 = year)
     * @param $month if viewing by month, this is the month number (1 = January, 2 = February, etc ...)
     */
    function cd_get_prices($year, $mid, $viewBy, $month = 1) {
        $pinfo = array();
        if ($viewBy==VIEW_BY_MONTH) {
            // load monthly prices
            $pinfo = cd_get_prices_by_month($year, $mid, $month);
        }
        else {
            // load yearly prices
            $pinfo = cd_get_prices_by_year($year, $mid);
        }
        return $pinfo;
    }
    /**
     * Build the commodity report
     * @param $year reference year of the report
     * @param $mid macro-category identifier
     * @param $viewBy view mode (1 = month, 2 = year)
     * @param $month if viewing by month, this is the month number (1 = January, 2 = February, etc ...)
     */
    function dgph_infographics_commodity_report($year = 2013, $mid = 1, $viewBy = 1, $month = 1) {
        $rep = array('year' => $year, 'macro_category_id' => $mid, 'view_by' => $viewBy, 'month' => $month);
        $pinfo = cd_get_prices($year, $mid, $viewBy, $month);
        $rep['prices'] = $pinfo;
        return theme('dgph_infographics_commodity_report', $rep);
    }
   
    /**
     * Extract dates from a category monthly set
     * @param $catInfo the category monthly set
     * @return the reference dates
     */
    function cd_extract_dates($catInfo) {
        $dts = array();
        // gets the set of different available dates
        foreach($catInfo as $dt => $pinfo) {
            if (!in_array($dt, $dts)) {
                // add this element to the result
                $dts[] = $dt;
            }
        }
        return $dts;
    }
    /**
     * Extract product names from a category monthly set
     * @param $catInfo the category monthly set
     * @return the product names
     */
    function cd_extract_products($catInfo) {
        $pnames = array();
        // gets the set of different available dates
        foreach($catInfo as $dt => $pinfo) {
            foreach($pinfo as $pname => $price) {
                if (!in_array($pname, $pnames)) {
                    // add this element to the result
                    $pnames[] = $pname;
                }
            }
        }
        return $pnames;
    }
    /**
     * Build the code for a given category in a monthly view
     * @param $cname the category name
     * @param $pinfo the pricing information
     * @param $idx the container (category) index
     * @param $mid identifier of the macro - category this category belongs to
     * @param $active indicates if this container is active or not
     * @return the category pricing code
     */
    function cd_build_monthly_category_code($cname, $pinfo, $idx, $mid, $active = false) {
        $activeClass = $active ? 'ui-accordion-content-active' : 'visible-none';
        $subClass = $active ? "" : " class='asubc'";
        $pluClass = $active ? "" : " class='aplusc'";
        $cnameId = str_replace(' ', '_', $cname);
        $code = "
                    <h3 id='state$idx' onClick='cd_category_changed($idx, $mid)' class='$cnameId right-accro ui-accordion-header ui-helper-reset ui-state-default ui-corner-all ui-accordion-icons background-none'>".strtoupper($cname)."<span id='sub$idx'$subClass></span><span id='plus$idx'$pluClass></span></h3>
                    <div id='visibility-state$idx' class='ui-accordion-content ui-helper-reset ui-widget-content ui-corner-bottom $activeClass'>
                        <div class='category-container'>
                            <table width='100%' border='0' cellpadding='0' cellspacing='0'>
                                <tr class='title-row'>
                                    <td width='20%' class='title'><h3>Item</h3></td>
                                    <td width='20%' class='title'><h3>Check 1 JAN 10</h3></td>
                                    <td width='20%' class='title'><h3>Check 2 JAN 18</h3></td>
                                    <td width='20%' class='title'><h3>Check 3 JAN 25</h3></td>
                                </tr>
                                <tr class='text-row'>
                                    <td class='text-title-row'><h4>Oil </h4></td>
                                    <td><p class='range'>48.20-54.49 <span>per liter</span></p></td>
                                    <td><p class='range'>48.10-54.09 <span>per liter</span></p></td>
                                    <td><p class='range'>47.55-54.09 <span>per liter</span></p></td>
                                </tr>
                                <tr class='text-row'>
                                    <td class='text-title-row'><h4>Natural Gas </h4></td>
                                    <td><p class='range'>39.55-42.50 <span>per liter</span></p></td>
                                    <td><p class='range'>39.80-42.75 <span>per liter</span></p></td>
                                    <td><p class='range'>39.55-42.30 <span>per liter</span></p></td>
                                </tr>
                                <tr class='text-row'>
                                    <td class='text-title-row'><h4>Gasoline </h4></td>
                                    <td><p class='range'>30.90-33.50 <span>per liter</span></p></td>
                                    <td><p class='range'>30.50-32.50 <span>per liter</span></p></td>
                                    <td><p class='range'>30.50-32.50 <span>per liter</span></p></td>
                                </tr>
                                <tr class='text-row'>
                                    <td class='text-title-row'><h4>Crude </h4></td>
                                    <td><p class='range'>665.00-810.00 <span>per 11 kg cylinder</span></p></td>
                                    <td><p class='range'>660.00-810.00 <span>per 11 kg cylinder</span></p></td>
                                    <td><p class='range'>660.00-810.00 <span>per 11 kg cylinder</span></p></td>
                                </tr>
                            </table>
                        </div>
                    </div>";
        return $code;
    }
    /**
     * Return the color corresponding to a given year's dataset
     * @param $year the input year
     * @return the color code
     */
    function cd_get_year_color($year) {
        $COLORS = array(2012=>'#ffc425', 2013=>'#d63333', 2014=>'#333385');
        $color = '#000000';
        if (array_key_exists($year, $COLORS)) {
            $color = $COLORS[$year];
        }
        return $color;
    }
    /**
     * Normalize a set of data for the presentation
     * @param array chartData the source data
     */
    function cd_normalize_chart_data(&$chartData) {
        $len = count($chartData);
        $missing = true;
        for($i=$len-1; $i>-1; $i--) {
            if ($chartData[$i]['y']<=0) {
                if ($missing) { 
                    $chartData[$i] = null;
                }
                else {
                    $chartData[$i]['y'] = $chartData[$i+1]['y'];
                }
            }
            else if ($missing) {
                $missing = false;
            }
        }
    }
    /**
     * Build the yearly prices chart for a product
     * @param $pname the product name
     * @param $pinfo the pricing information
     * @param year the year data refers to
     * @return the chart code
     */
    function cd_build_product_chart($pname, $pinfo, $year) {
        // gets chart data
        $MONTHS = array('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec');
        foreach ($MONTHS as $idx => $month) {
            $priceArr = isset($pinfo[$idx+1][$pname]) ? $pinfo[$idx+1][$pname] : null;
            $avgPrice = ($priceArr!=null) ? number_format($priceArr['price'], 2) : 0;
            $customCategory = date('F Y', strtotime("$month $year"));
            $chartData[] = array('y'=>floatval($avgPrice), 'customCategory'=>$customCategory);
        }
        cd_normalize_chart_data($chartData);
        // build chart
        $chart = array(
                '#type' => 'chart',
                '#chart_type' => 'line',
                '#legend' => false,
                '#legend_position' => 'none',
                '#colors' => array(cd_get_year_color($year)),
                '#width' => '600px',
                '#height' => '130px',
                '#font' => 'Roboto',
                '#chart_library' => 'highcharts'
        );
        $chart['chart_xaxis'] = array(
            '#type' => 'chart_xaxis',
            '#title' => '',
            '#labels' => $MONTHS,
            '#labels_rotation' => 0,
            '#labels_font_size' => '10px',
            '#labels_font_weight' => 'normal',
            '#labels_font_style' => 'normal'
        );
        $chart['chart_yaxis'] = array(
            '#type' => 'chart_yaxis',
            '#min' => 0
        );
        $chart['chart_data'] = array(
            '#type' => 'chart_data',
            '#legend' => false,
            '#legend_position' => 'none',
            '#data' => $chartData
        );
        // check wheter a comparison has been requested
        $cmpYear = isset($_GET['cmp']) ? $_GET['cmp'] : $year;
        if ($cmpYear!=$year) {
            // load data for year to compare to
            $chartDataCmp = cd_get_product_prices_by_year($pname, $cmpYear);
            cd_normalize_chart_data($chartDataCmp);
            // add the new data set to the chart
            $chart['chart_data_cmp'] = array(
                '#type' => 'chart_data',
                '#legend' => false,
                '#legend_position' => 'none',
                '#data' => $chartDataCmp
            );
            $chart['#colors'] = array(cd_get_year_color($year), cd_get_year_color($cmpYear));
        }
        return drupal_render($chart);
    }
    /**
     * Build the code for a given category in a yearly view
     * @param $cname the category name
     * @param $idx the container (category) index
     * @param $vars configuration variables
     * @param $active indicates if this container is active or not
     * @return the category pricing code
     */
    function cd_build_yearly_category_code($cname, $idx, $vars, $active = false) {
        $pinfo = $vars['prices'];
        $mid = $vars['macro_category_id'];
        $year = $vars['year'];
        $activeClass = $active ? 'ui-accordion-content-active' : 'visible-none';
        $subClass = $active ? "" : " class='asubc'";
        $pluClass = $active ? "" : " class='aplusc'";
        $cnameId = str_replace(' ', '_', $cname);
        $catInfo = array_key_exists($cname, $pinfo) ? $pinfo[$cname] : array();
        $code = "
                    <h3 id='state$idx' onClick='cd_category_changed($idx, $mid)' class='$cnameId right-accro ui-accordion-header ui-helper-reset ui-state-default ui-corner-all ui-accordion-icons background-none'>".strtoupper($cname)."<span id='sub$idx'$subClass></span><span id='plus$idx'$pluClass></span></h3>
                    <div id='visibility-state$idx' class='ui-accordion-content ui-helper-reset ui-widget-content ui-corner-bottom $activeClass'>
                        <div class='category-container'>";
        $pnames = cd_extract_products($catInfo);
        foreach($pnames as $pname) {
            // build product chart
            $chartCode = cd_build_product_chart($pname, $catInfo, $year);
            $code .= "
                            <div class='yearly-con'>
                                <div class='yearly-left'>".ucwords($pname)."</div>
                                <div class='yearly-right'>$chartCode</div>
                            </div>";
        }
        $code .= "
                        </div>
                    </div>";
        return $code;
    }
    /**
     * Get report code for a macro - category
     * @param $cfg the report configuration parameters
     * @return the report code
     */
    function cd_get_macro_code($vars) {
        $modPath = drupal_get_path('module', 'dgph_infographics');
        $pinfo = $vars['prices'];
        $mid = $vars['macro_category_id'];
        $viewBy = $vars['view_by'];
        $macroName = cd_get_macro_category_name($mid);
        $code = "
                    <div id='for_css_class'><style>#state1 { background: url(/$modPath/images/m".$mid."c1-big.png) no-repeat scroll 10px 50% #FFC425 !important; font-family: 'Roboto', sans-serif; font-weight: bold; font-size: 30px !important; height: 55px;}</style></div>
                    <h2 class='title'>$macroName</h2>
                    <div class='clear'></div>
                    <div class='weekly-right-con'>
                        <div class='ui-accordion ui-widget ui-helper-reset accordion3'  role='tablist'>";
        $cats = cd_get_category_names($mid);
        foreach($cats as $idx=>$cat) {
            if ($viewBy==VIEW_BY_MONTH) {
                $code .= cd_build_monthly_category_code($cat, $pinfo, $idx+1, $mid, (0==$idx));
            }
            else if ($viewBy==VIEW_BY_YEAR) {
                $code .= cd_build_yearly_category_code($cat, $idx+1, $vars, (0==$idx));
            }
        }
        $code .= "
                        </div>
                        <div class='separator'></div>
                        <div class='legend-con'>
                            <h3>LEGEND</h3>
                            <p><span class='header'>These prices are monitored and submitted by:</span></p>
                            <p>The Department One;<br>
                            The Department Two;<br>
                            The Department Three;<br>
                            The Department Four.</p>
                        </div>
                    </div>";
        return $code;
    }
    /**
     * Theme for commodity infographics report
     */
    function theme_dgph_infographics_commodity_report(&$vars) {
        $modPath = drupal_get_path('module', 'dgph_infographics');
        drupal_add_css($modPath.'/css/dgph_infographics_common.css');
        drupal_add_css($modPath.'/css/dgph_infographics_commodities.css');
        drupal_add_js($modPath.'/js/dgph_infographics_scripts.js');
        drupal_add_js($modPath.'/js/dgph_infographics_commodity.js');
        drupal_set_title('Infographics');
        $year = $vars['year'];
        $mid = $vars['macro_category_id'];
        $viewBy = $vars['view_by'];
        $month = $vars['month'];
        $code =    "<div class='row dashboard-header'>
                        <div class='large-6 columns agency'>
                            <h2>Infographics</h2>
                            <h3>PRICE MONITORING DASHBOARD</h3>
                            <p>Use this dashboard to compare the average prices of basic commodities on a weekly, monthly, and yearly basis. These commodities include staple food items such as rice and vegetables, and goods such as fuel. The data is collected weekly and published every Friday.</p>
                        </div>        
                        <div class='large-6 columns'>
                            <div class='year-con dbapc'>
                                <div class='year'><a href='#' data-dropdown='#select-year'><span>$year</span></a></div>
                            </div>
                        </div> 
                    </div>
                    <div class='row'>
                        <div class='large-3 columns rightside datarequest choosePillar'>
                            <div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
                                <h3>Choose Product</h3>
                                <div>
                                    <a href='#'>GAS AND FUEL</a>
                                    <a href='#'>CONSUMER GOODS</a>
                                    <a href='#'>AGRICULTURAL PRODUCTS</a>
                                    <a href='#'>BASIC MEDICINES</a>
                                </div>
                                <h3>View By</h3>
                                <div>
                                    <a href='#'>MONTH</a>
                                    <a href='#'>YEAR</a>
                                </div>";
        if ($viewBy==VIEW_BY_MONTH) {
            $code .= "
                                <h3>Select Month</h3>
                                <div>
                                    <form class='custom cd_month'>
                                        <label for='cd_month1'><input type='checkbox' ><span class='custom checkbox'></span>JANUARY</label>
                                        <label for='cd_month2'><input type='checkbox'><span class='custom checkbox'></span>FEBRUARY</label>
                                        <label for='cd_month3'><input type='checkbox'><span class='custom checkbox'></span>MARCH</label>
                                        <label for='cd_month4'><input type='checkbox'><span class='custom checkbox'></span>APRIL</label>                                        
                                        <label for='cd_month5'><input type='checkbox'><span class='custom checkbox'></span>MAY</label>
                                        <label for='cd_month6'><input type='checkbox'><span class='custom checkbox'></span>JUNE</label>
                                        <label for='cd_month7'><input type='checkbox'><span class='custom checkbox'></span>JULY</label>
                                        <label for='cd_month8'><input type='checkbox'><span class='custom checkbox'></span>AUGUST</label>
                                        <label for='cd_month9'><input type='checkbox'><span class='custom checkbox'></span>SEPTEMBER</label>
                                        <label for='cd_month10'><input type='checkbox'><span class='custom checkbox'></span>OCTOBER</label>
                                        <label for='cd_month11'><input type='checkbox'><span class='custom checkbox'></span>NOVEMBER</label>
                                        <label for='cd_month12'><input type='checkbox'><span class='custom checkbox'></span>DECEMBER</label>
                                    </form>
                                </div>";
        }
        else {
            $cmpYear = isset($_GET['cmp']) ? $_GET['cmp'] : 0;
            $code .= "
                                <h3>Compare by year</h3>
                                <div>
                                    <form class='custom cd_year'>
                                        <label for='cd_year1'><input type='checkbox'><span class='custom checkbox'></span> 2012 <div class='yellow'></div></label> 
                                        <label for='cd_year2'><input type='checkbox' style='display: none;' id='cd_year2'".(($year=='2013') ? " disabled='disabled'" : "").(($cmpYear==2013) ?  "checked='checked'" : "")."><span class='custom checkbox'></span> 2013 <div class='red'></div></label>
                                        <label for='cd_year3'><input type='checkbox' style='display: none;' id='cd_year3' disabled='disabled'><span class='custom checkbox'></span> 2014 <div class='blue'></div></label>
                                    </form>
                                </div>";
        }
        $code .=    "
                            </div>
                        </div>
                        <div class='large-9 columns works works2'>
                            <ul class='social-icon'>
                                <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-11.png'></a></li>
                                <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-19.png'></a></li>
                                <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-20.png'></a></li>
                            </ul>
                            <div class='clear'></div>";
        $code .= cd_get_macro_code($vars);
        $code .= "
                        </div>
                    </div>
                </div>";
        $code .= "
                  <span id='selected-year' style='display:none'>$year</span>
                  <span id='selected-macro-category' style='display:none'>$mid</span>
                  <div id='select-year' class='dropdown dropdown-tip'>
                    <ul class='dropdown-menu'>
                        <li><a href='#'>2014</a></li>
                        <li><a href='#'>2013</a></li>
                        <li><a href='#'>2012</a></li>
                    </ul>
                  </div>
                  <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>";
        return $code;
   }
?>