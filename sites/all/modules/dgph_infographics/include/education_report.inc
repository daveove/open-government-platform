<?php
    /**
     * Gets the national summary data from the database
     * @param $year the school year
     * @param $schoolType the school type (es = elementary school; hs = high school)
     */
    function edu_get_national_summary($year, $schoolType) {
        $ns = array();
        // total number of regions
        $query = db_select('t_education', 'edu')
                    ->fields('edu', array('region'))
                    ->distinct()
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like');
        $ns['total_regions'] = $query->countQuery()->execute()->fetchField();
        // total schools
        $query = db_select('t_education', 'edu')
                    ->fields('edu', array('school_id'))
                    ->distinct()
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like');
        $ns['total_schools'] = $query->countQuery()->execute()->fetchField();
        // total males
        $query = db_select('t_education', 'edu')
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like');
        $query->addExpression("sum(y1m)+sum(y2m)+sum(y3m)+sum(y4m)+sum(y5m)+sum(y6m)", 'total_males');
        $ns['total_males'] = $query->execute()->fetchField();
        // total females
        $query = db_select('t_education', 'edu')
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like');
        $query->addExpression("sum(y1f)+sum(y2f)+sum(y3f)+sum(y4f)+sum(y5f)+sum(y6f)", 'total_females');
        $ns['total_females'] = $query->execute()->fetchField();
        return $ns;
    }
    /**
     * Gets the national breakdown data from the database
     * @param $year the school year
     * @param $schoolType the school type (es = elementary school; hs = high school)
     */
    function edu_get_national_breakdown($year, $schoolType) {
        $nbs = array();
        // total schools by region
        $query = db_select('t_education', 'edu')
                    ->fields('edu', array('region'))
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like')
                    ->groupBy('region');
        $query->addExpression("count(distinct school_id)", 'total_schools');
        $res = $query->execute();
        foreach($res as $row) {
            $region = $row->region;
            $totalSchools = $row->total_schools;
            $nbs[$region]['total_schools'] = $totalSchools;
        }
        // total males by region
        $query = db_select('t_education', 'edu')
                    ->fields('edu', array('region'))
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like')
                    ->groupBy('region');
        $query->addExpression("sum(y1m)+sum(y2m)+sum(y3m)+sum(y4m)+sum(y5m)+sum(y6m)", 'total_males');
        $res = $query->execute();
        foreach($res as $row) {
            $region = $row->region;
            $totalMales = $row->total_males;
            $nbs[$region]['total_males'] = $totalMales;
        }
        // total females by region
        $query = db_select('t_education', 'edu')
                    ->fields('edu', array('region'))
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like')
                    ->groupBy('region');
        $query->addExpression("sum(y1f)+sum(y2f)+sum(y3f)+sum(y4f)+sum(y5f)+sum(y6f)", 'total_females');
        $res = $query->execute();
        foreach($res as $row) {
            $region = $row->region;
            $totalFemales = $row->total_females;
            $nbs[$region]['total_females'] = $totalFemales;
        }
        return $nbs;
    }
    /**
     * Build the national report
     * @param $vars the input variables
     */
    function edu_build_national_report($vars) {
        $year = $vars['year'];
        $schoolType = $vars['school_type'];
        // gets national summary
        $ns = edu_get_national_summary($year, $schoolType);
        $code = "
                    <div class='enrolment-con enrolment-con3'>
                        <table cellpadding='0' cellspacing='0' border='0' width='100%'>
                        <tr class='enrolment-title enrolment-header'>
                            <td colspan='5'><h3>SUMMARY</h3></td>
                        </tr>
                        <tr class='enrolment-text'>
                            <td width='20%'><h2>".$ns['total_regions']."<span>REGIONS</span></h2></td>
                            <td width='20%'><h2>".number_format($ns['total_schools'])."<span>TOTAL SCHOOLS</span></h2></td>
                            <td width='20%'><h2>".number_format($ns['total_males'])."<span>MALE</span></h2></td>
                            <td width='20%'><h2>".number_format($ns['total_females'])."<span>FEMALE</span></h2></td>
                            <td width='20%' class='last-col'><h2>".number_format($ns['total_males']+$ns['total_females'])."<span>TOTAL ENROLEES</span></h2></td>
                        </tr>
                        </table>
                    </div>
                    <div class='enrolment-con'>
                        <table cellpadding='0' cellspacing='0' border='0' width='100%' style='margin:20px 0 5px; border-bottom:0px;'>
                        <tr class='enrolment-title enrolment-header'>
                            <td colspan='5'><h3>BREAKDOWN</h3></td>
                        </tr>
                        </table>
                    </div>
                    <div class='enrolment-con enrolment-con2'>
                        <table cellpadding='0' cellspacing='0' border='0' width='100%'>
                        <tr class='enrolment-title'>
                            <td class='first'>REGION</td>
                            <td>TOTAL SCHOOLS</td>
                            <td><span class='male'>MALE</span></td>
                            <td><span class='female'>FEMALE</span></td>
                            <td>Grand Total</td>
                        </tr>";
        // gets national breakdown
        $nbs = edu_get_national_breakdown($year, $schoolType);
        if (!empty($nbs)) {
            $regs = $vars['regions'];
            foreach($regs as $reg) {
                $nb = $nbs[$reg];
                $totalSchools = number_format($nb['total_schools']);
                $totalMales = number_format($nb['total_males']);
                $totalFemales = number_format($nb['total_females']);
                $totalEnrolles = number_format($nb['total_males']+$nb['total_females']);
                $regUri = "/infographics/education/$year/$schoolType/reg/".str_replace(' ', '+', $reg);
                $code .= "
                            <tr class='enrolment-text'>
                                <td width='20%'><h2 class='first'><a href='$regUri'>$reg</a></h2></td>
                                <td width='20%'><h2>$totalSchools</h2></td>
                                <td width='20%'><h2>$totalMales</h2></td>
                                <td width='20%'><h2>$totalFemales</h2></td>
                                <td width='20%' class='last-col'><h2>$totalEnrolles</h2></td>
                            </tr>";
            }
        }
        else {
            $code .= "
                            <tr class='enrolment-text'>
                                <td colspan='5' class='last-col'><h2>There is no data available for the selected criteria!</h2></td>
                            </tr>";
        }
        $code .= "
                        </table>
                    </div>";
        return $code;
    }
    /**
     * Gets the regional summary data from the database
     * @param $year the school year
     * @param $schoolType the school type (es = elementary school; hs = high school)
     * @param $region the region name
     */
    function edu_get_regional_summary($year, $schoolType, $region) {
        $rs = array();
        // total number of provinces
        $query = db_select('t_education', 'edu')
                    ->fields('edu', array('province'))
                    ->distinct()
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like')
                    ->condition('region', $region, 'like');
        $rs['total_provinces'] = $query->countQuery()->execute()->fetchField();
        // total schools
        $query = db_select('t_education', 'edu')
                    ->fields('edu', array('school_id'))
                    ->distinct()
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like')
                    ->condition('region', $region, 'like');
        $rs['total_schools'] = $query->countQuery()->execute()->fetchField();
        // total enrolment by grade level
        $grandTotal = 0;
        for($level=1; $level<=6; $level++) {
            // fetch total for this level
            $levelField = 'y'.$level;
            $query = db_select('t_education', 'edu')
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like')
                    ->condition('region', $region, 'like');
            $query->addExpression("sum(".$levelField."f)+sum(".$levelField."m)", 'total_level');
            $rs['enrolees']["total_$levelField"] = $query->execute()->fetchField();
            $grandTotal += $rs['enrolees']["total_$levelField"];
        }
        $rs['enrolees']['total'] = $grandTotal;
        return $rs;
    }
    /**
     * Gets the regional breakdown data from the database
     * @param $year the school year
     * @param $schoolType the school type (es = elementary school; hs = high school)
     * @param $region the region name
     */
    function edu_get_regional_breakdown($year, $schoolType, $region) {
        $rbs = array();
        // total schools by province
        $query = db_select('t_education', 'edu')
                    ->fields('edu', array('province'))
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like')
                    ->condition('region', $region, 'like')
                    ->groupBy('province');
        $query->addExpression("count(distinct school_id)", 'total_schools');
        $res = $query->execute();
        foreach($res as $row) {
            $province = $row->province;
            $totalSchools = $row->total_schools;
            $rbs[$province]['total_schools'] = $totalSchools;
        }
        // enrolments by province and grade level
        $query = db_select('t_education', 'edu')
                ->fields('edu', array('province'))
                ->condition('year', $year)
                ->condition('school_type', $schoolType, 'like')
                ->condition('region', $region, 'like')
                ->groupBy('province');
        $query->addExpression("sum(y1m)", 'total_y1m');
        $query->addExpression("sum(y1f)", 'total_y1f');
        $query->addExpression("sum(y2m)", 'total_y2m');
        $query->addExpression("sum(y2f)", 'total_y2f');
        $query->addExpression("sum(y3m)", 'total_y3m');
        $query->addExpression("sum(y3f)", 'total_y3f');
        $query->addExpression("sum(y4m)", 'total_y4m');
        $query->addExpression("sum(y4f)", 'total_y4f');
        $query->addExpression("sum(y5m)", 'total_y5m');
        $query->addExpression("sum(y5f)", 'total_y5f');
        $query->addExpression("sum(y6m)", 'total_y6m');
        $query->addExpression("sum(y6f)", 'total_y6f');
        $res = $query->execute();
        foreach($res as $row) {
            $province = $row->province;
            $rbs[$province]["total_y1m"] = $row->total_y1m;
            $rbs[$province]["total_y1f"] = $row->total_y1f;
            $rbs[$province]["total_y2m"] = $row->total_y2m;
            $rbs[$province]["total_y2f"] = $row->total_y2f;
            $rbs[$province]["total_y3m"] = $row->total_y3m;
            $rbs[$province]["total_y3f"] = $row->total_y3f;
            $rbs[$province]["total_y4m"] = $row->total_y4m;
            $rbs[$province]["total_y4f"] = $row->total_y4f;
            $rbs[$province]["total_y5m"] = $row->total_y5m;
            $rbs[$province]["total_y5f"] = $row->total_y5f;
            $rbs[$province]["total_y6m"] = $row->total_y6m;
            $rbs[$province]["total_y6f"] = $row->total_y6f;
        }
        return $rbs;
    }
    /**
     * Format an enrolment count value
     * @param value the value to be formatted
     * @return the formatted value
     */
    function format_enrolment_count($value) {
        $fv = $value;
        if (is_numeric($value)) {
            if (intval($value)>0) {
                $fv = number_format($value);
            }
            else {
                $fv = '--';
            }
        }
        return $fv;
    }
    /**
     * Build the regional report
     * @param $vars the input variables
     */
    function edu_build_regional_report($vars) {
        $year = $vars['year'];
        $schoolType = $vars['school_type'];
        $region = $vars['region'];
        // gets regional summary
        $rs = edu_get_regional_summary($year, $schoolType, $region);
        $sl = ($schoolType=='hs' ? 7 : 1);
        $code = "
                    <div class='enrolment-con enrolment-con3'>
                        <table cellpadding='0' cellspacing='0' border='0' width='100%'>
                        <tr class='enrolment-title enrolment-header'>
                            <td colspan='4'><h3>SUMMARY</h3></td>
                        </tr>
                        <tr class='enrolment-text'>
                            <td width='15%'><h2>".$rs['total_provinces']."<span>PROVINCES</span></h2></td>
                            <td width='25%'><h2>".number_format($rs['total_schools'])."<span>TOTAL SCHOOLS</span></h2></td>
                            <td width='45%'>
                                <table width='100%' cellpadding='0' cellspacing='0'>
                                <tr class='title-table'>
                                    <td colspan='6' ><h2>total per grade level</h2></td>
                                </tr>
                                <tr>
                                    <td class='grade-level grade-level-first'><span>$sl</span></td>
                                    <td class='grade-level'><span>".($sl+1)."</span></td>
                                    <td class='grade-level'><span>".($sl+2)."</span></td>
                                    <td class='grade-level'><span>".($sl+3)."</span></td>
                                    <td class='grade-level'><span>".($sl+4)."</span></td>
                                    <td class='grade-level grade-level-last'><span>".($sl+5)."</span></td>
                                </tr>
                                <tr>
                                    <td class='first-row'><span>".format_enrolment_count($rs['enrolees']['total_y1'])."</span></td>
                                    <td><span>".format_enrolment_count($rs['enrolees']['total_y2'])."</span></td>
                                    <td><span>".format_enrolment_count($rs['enrolees']['total_y3'])."</span></td>
                                    <td><span>".format_enrolment_count($rs['enrolees']['total_y4'])."</span></td>
                                    <td><span>".format_enrolment_count($rs['enrolees']['total_y5'])."</span></td>
                                    <td><span>".format_enrolment_count($rs['enrolees']['total_y6'])."</span></td>
                                </tr>
                                </table>
                            </td>
                            <td width='15%' class='last-col'><h2>".number_format($rs['enrolees']['total'])."<span>TOTAL ENROLEES</span></h2></td>
                        </tr>
                        </table>
                    </div>
                    <div class='enrolment-con'>
                       <table cellpadding='0' cellspacing='0' border='0' width='100%' style='margin:20px 0 5px; border-bottom:0px;'>
                       <tr class='enrolment-title enrolment-header'>
                           <td colspan='5'><h3>BREAKDOWN</h3></td>
                       </tr>
                       </table>
                    </div>
                    <div class='enrolment-con enrolment-con3'>
                        <table cellpadding='0' cellspacing='0' border='0' width='100%'>
                        <tr class='enrolment-text title-con'>
                            <td width='15%' class='sigal_text'><h2><span>PROVINCE</span></h2></td>
                            <td width='25%' class='sigal_text'><h2><span>TOTAL SCHOOLS</span></h2></td>
                            <td width='45%'>
                                <table width='100%' cellpadding='0' cellspacing='0'>
                                <tr class='title-table'>
                                    <td colspan='6' ><h2>GRADE LEVEL</h2></td>
                                </tr>
                                <tr>
                                    <td class='first-row' width='16.67%'><span>$sl</span></td>
                                    <td width='16.67%'><span>".($sl+1)."</span></td>
                                    <td width='16.67%'><span>".($sl+2)."</span></td>
                                    <td width='16.67%'><span>".($sl+3)."</span></td>
                                    <td width='16.67%'><span>".($sl+4)."</span></td>
                                    <td width='16.67%'><span>".($sl+5)."</span></td>
                                </tr>
                                </table>
                            </td>
                            <td width='15%' class='last-col  sigal_text'><h2><span>GRAND TOTAL</span></h2></td>
                        </tr>
                        </table>";
        // gets regional breakdown
        $rbs = edu_get_regional_breakdown($year, $schoolType, $region);
        $regUri = str_replace(' ', '+', $region);
        $baseUri = "/infographics/education/$year/$schoolType/reg/$regUri";
        foreach($rbs as $province => $rb) {
            $prvUri = str_replace(' ', '+', $province);
            $uri = "$baseUri/$prvUri";
            $totalSchools = number_format($rb['total_schools']);
            $code .= "
                        <table cellpadding='0' cellspacing='0' border='0' width='100%' class='margin-line'>
                        <tr class='enrolment-text enrolment-text3'>
                            <td width='15%' class='sigal_text1 expandable-item'><a href='$uri'><h2>$province</h2></a></td>
                            <td width='25%' class='sigal_text1'><h2>$totalSchools</h2></td>
                            <td width='45%'>
                                <table width='100%' cellpadding='0' cellspacing='0' class='count'>
                                <tr>";
            $malesTotal = 0;
            $femalesTotal = 0;
            for($level=1; $level<=6; $level++) {
                $males = number_format($rb["total_y".$level."m"]);
                $females = number_format($rb["total_y".$level."f"]);
                $total = number_format($rb["total_y".$level."m"]+$rb["total_y".$level."f"]);
                $malesTotal += $rb["total_y".$level."m"];
                $femalesTotal += $rb["total_y".$level."f"];
                $styleClass = ($level>1) ? 'sigal_text2' : 'first-row sigal_text2';
                $code .= "<td class='$styleClass' width='16.67%'><h2><a href='#' title='male: $males female: $females'>".format_enrolment_count($total)."</a></h2></td>";
            }
            $grandTotal = number_format($malesTotal+$femalesTotal);
            $malesTotal = number_format($malesTotal);
            $femalesTotal = number_format($femalesTotal);
            $code .= "      
                                </tr>
                                </table>
                            </td>
                            <td width='15%' class='last-col  sigal_text2'><h4 class='total'><a href='#' title='male: $malesTotal female: $femalesTotal'>$grandTotal</a></h4></td>
                        </tr>
                        </table>";
        }
        $code .= "
                    </div>";
        return $code;
    }
    /**
     * Gets the provincial summary data from the database
     * @param $year the school year
     * @param $schoolType the school type (es = elementary school; hs = high school)
     * @param $region the region name
     * @param $province the province name
     * @param $municipality the municipality name, or <code>null</code> to get info about all municipalities in this province
     */
    function edu_get_provincial_summary($year, $schoolType, $region, $province, $municipality = null) {
        $rs = array();
        $rs['total_municipalities'] = 1;
        if (empty($municipality)) {
            // total number of municipalities
            $query = db_select('t_education', 'edu')
                        ->fields('edu', array('municipality'))
                        ->distinct()
                        ->condition('year', $year)
                        ->condition('school_type', $schoolType, 'like')
                        ->condition('region', $region, 'like')
                        ->condition('province', $province, 'like');
            $rs['total_municipalities'] = $query->countQuery()->execute()->fetchField();
        }
        // total schools
        $query = db_select('t_education', 'edu')
                    ->fields('edu', array('school_id'))
                    ->distinct()
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like')
                    ->condition('region', $region, 'like')
                    ->condition('province', $province, 'like');
        if (!empty($municipality)) {
            $query->condition('municipality', $municipality, 'like');
        }
        $rs['total_schools'] = $query->countQuery()->execute()->fetchField();
        // total enrolment by grade level
        $grandTotal = 0;
        for($level=1; $level<=6; $level++) {
            // fetch total for this level
            $levelField = 'y'.$level;
            $query = db_select('t_education', 'edu')
                    ->condition('year', $year)
                    ->condition('school_type', $schoolType, 'like')
                    ->condition('region', $region, 'like')
                    ->condition('province', $province, 'like');
            if (!empty($municipality)) {
                $query->condition('municipality', $municipality, 'like');
            }
            $query->addExpression("sum(".$levelField."f)+sum(".$levelField."m)", 'total_level');
            $rs['enrolees']["total_$levelField"] = $query->execute()->fetchField();
            $grandTotal += $rs['enrolees']["total_$levelField"];
        }
        $rs['enrolees']['total'] = $grandTotal;
        return $rs;
    }
    /**
     * Gets the provincial breakdown data from the database
     * @param $year the school year
     * @param $schoolType the school type (es = elementary school; hs = high school)
     * @param $region the region name
     * @param $province the province name
     * @param $municipality the municipality name, or <code>null</code> to get info about all municipalities in this province
     */
    function edu_get_provincial_breakdown($year, $schoolType, $region, $province, $municipality = null) {
        $pbs = array();
        // loads schools info by province and municipality
        $more = isset($_GET['more']);
        $limit = isset($_SESSION['range_limit']) ? intval($_SESSION['range_limit']) : 10;
        if ($more) {
            $limit += 10;
        }
        else {
            $limit = 10;
        }
        $_SESSION['range_limit'] = $limit;
        $query = db_select('t_education', 'edu')
                ->fields('edu', array('municipality', 'school_id', 'school_name', 'y1m', 'y1f', 'y2m', 'y2f',
                                        'y3m', 'y3f', 'y4m', 'y4f', 'y5m', 'y5f', 'y6m', 'y6f'))
                ->condition('year', $year)
                ->condition('school_type', $schoolType, 'like')
                ->condition('region', $region, 'like')
                ->condition('province', $province, 'like')
                ->orderBy('municipality')
                ->orderBy('school_name')
                ->range(0, $limit);
        if (!empty($municipality)) {
            // add the municipality filter
            $query->condition('municipality', $municipality, 'like');
        }
        $schoolFilter = isset($_GET['school']) ? $_GET['school'] : null;
        if (!empty($schoolFilter)) {
            // get search key
            $searchKey = isset($_GET['key']) ? $_GET['key'] : 'school_name';
            // filter by school name
            $query->condition($searchKey, $schoolFilter.'%', 'like');
        }
        $res = $query->execute();
        foreach($res as $row) {
            $municipality = $row->municipality;
            $schoolId = $row->school_id;
            $pbs[$municipality][$schoolId]['school_name'] = $row->school_name;
            $pbs[$municipality][$schoolId]['y1m'] = $row->y1m;
            $pbs[$municipality][$schoolId]['y1f'] = $row->y1f;
            $pbs[$municipality][$schoolId]['y2m'] = $row->y2m;
            $pbs[$municipality][$schoolId]['y2f'] = $row->y2f;
            $pbs[$municipality][$schoolId]['y3m'] = $row->y3m;
            $pbs[$municipality][$schoolId]['y3f'] = $row->y3f;
            $pbs[$municipality][$schoolId]['y4m'] = $row->y4m;
            $pbs[$municipality][$schoolId]['y4f'] = $row->y4f;
            $pbs[$municipality][$schoolId]['y5m'] = $row->y5m;
            $pbs[$municipality][$schoolId]['y5f'] = $row->y5f;
            $pbs[$municipality][$schoolId]['y6m'] = $row->y6m;
            $pbs[$municipality][$schoolId]['y6f'] = $row->y6f;
        }
        return $pbs;
    }
    /**
     * Build the provincial report
     * @param $vars the input variables
     */
    function edu_build_provincial_report($vars) {
        $year = $vars['year'];
        $schoolType = $vars['school_type'];
        $region = $vars['region'];
        $province = $vars['province'];
        $municipality = $vars['municipality'];
        // gets provincial summary
        $ps = edu_get_provincial_summary($year, $schoolType, $region, $province, $municipality);
        $reqUri = strtok($_SERVER["REQUEST_URI"], '?');
        $sl = ($schoolType=='hs' ? 7 : 1);
        $code = "
                    <div class='enrolment-con enrolment-con3'>
                        <table cellpadding='0' cellspacing='0' border='0' width='100%'>
                        <tr class='enrolment-title'>
                            <td colspan='4'><h3>SUMMARY</h3></td>
                        </tr>
                        <tr class='enrolment-text'>
                            <td width='15%'><h2>".$ps['total_municipalities']."<span>MUNICIPALITIES</span></h2></td>
                            <td width='25%'><h2>".number_format($ps['total_schools'])."<span>TOTAL SCHOOLS</span></h2></td>
                            <td width='45%'>
                                <table width='100%' cellpadding='0' cellspacing='0'>
                                <tr class='title-table'>
                                    <td colspan='6' ><h2>total per grade level</h2></td>
                                </tr>
                                <tr>
                                    <td class='grade-level grade-level-first'><span>$sl</span></td>
                                    <td class='grade-level'><span>".($sl+1)."</span></td>
                                    <td class='grade-level grade-level-first'><span>".($sl+2)."</span></td>
                                    <td class='grade-level grade-level-first'><span>".($sl+3)."</span></td>
                                    <td class='grade-level grade-level-first'><span>".($sl+4)."</span></td>
                                    <td class='grade-level grade-level-last'><span>".($sl+5)."</span></td>
                                </tr>
                                <tr>
                                    <td class='first-row'><span>".format_enrolment_count($ps['enrolees']['total_y1'])."</span></td>
                                    <td><span>".format_enrolment_count($ps['enrolees']['total_y2'])."</span></td>
                                    <td><span>".format_enrolment_count($ps['enrolees']['total_y3'])."</span></td>
                                    <td><span>".format_enrolment_count($ps['enrolees']['total_y4'])."</span></td>
                                    <td><span>".format_enrolment_count($ps['enrolees']['total_y5'])."</span></td>
                                    <td><span>".format_enrolment_count($ps['enrolees']['total_y6'])."</span></td>
                                </tr>
                                </table>
                            </td>
                            <td width='15%' class='last-col'><h2>".number_format($ps['enrolees']['total'])."<span>TOTAL ENROLEES</span></h2></td>
                        </tr>
                        </table>
                    </div>
                    <div class='alphabetically'>
		 	<h2>View Schools Alphabetically:</h2>
			<ul>
                            <li><a href='#'>#</a></li>
                            <li><a href='$reqUri?school=a'>A</a></li>
                            <li><a href='$reqUri?school=b'>B</a></li>
                            <li><a href='$reqUri?school=c'>C</a></li>
                            <li><a href='$reqUri?school=d'>D</a></li>
                            <li><a href='$reqUri?school=e'>E</a></li>
                            <li><a href='$reqUri?school=f'>F</a></li>
                            <li><a href='$reqUri?school=g'>G</a></li>
                            <li><a href='$reqUri?school=h'>H</a></li>
                            <li><a href='$reqUri?school=i'>I</a></li>
                            <li><a href='$reqUri?school=j'>J</a></li>
                            <li><a href='$reqUri?school=k'>K</a></li>
                            <li><a href='$reqUri?school=l'>L</a></li>
                            <li><a href='$reqUri?school=m'>M</a></li>
                            <li><a href='$reqUri?school=n'>N</a></li>
                            <li><a href='$reqUri?school=o'>O</a></li>
                            <li><a href='$reqUri?school=p'>P</a></li>
                            <li><a href='$reqUri?school=q'>Q</a></li>
                            <li><a href='$reqUri?school=r'>R</a></li>
                            <li><a href='$reqUri?school=s'>S</a></li>
                            <li><a href='$reqUri?school=t'>T</a></li>
                            <li><a href='$reqUri?school=u'>U</a></li>
                            <li><a href='$reqUri?school=v'>V</a></li>
                            <li><a href='$reqUri?school=w'>W</a></li>
                            <li><a href='$reqUri?school=x'>X</a></li>
                            <li><a href='$reqUri?school=y'>Y</a></li>
                            <li><a href='$reqUri?school=z'>Z</a></li>
                            <li><a href='$reqUri'><span>ALL</span></a></li>
                        </ul>
                    </div>
                    <div class='enrolment-con'>
                        <table cellpadding='0' cellspacing='0' border='0' width='100%' style='margin:20px 0 5px; border-bottom:0px;'>
                        <tr class='enrolment-title'>
                            <td colspan='5'><h3>BREAKDOWN</h3></td>
                        </tr>
                        </table>
                    </div>
                    <div class='enrolment-con enrolment-con3'>
                        <table cellpadding='0' cellspacing='0' border='0' width='100%'>
                        <tr class='enrolment-text title-con'>
                            <td width='15%' class='sigal_text'><h2><span>MUNICIPALITY<br/>and SCHOOL ID #</span></h2></td>
                            <td width='25%' class='sigal_text'><h2><span>SCHOOL NAME</span></h2></td>
                            <td width='45%'>
                                <table width='100%' cellpadding='0' cellspacing='0'>
                                <tr class='title-table'>
                                    <td colspan='6' ><h2>GRADE LEVEL</h2></td>
                                </tr>
                                <tr>
                                    <td class='first-row' width='16.67%'><span>$sl</span></td>
                                    <td width='16.67%'><span>".($sl+1)."</span></td>
                                    <td width='16.67%'><span>".($sl+2)."</span></td>
                                    <td width='16.67%'><span>".($sl+3)."</span></td>
                                    <td width='16.67%'><span>".($sl+4)."</span></td>
                                    <td width='16.67%'><span>".($sl+5)."</span></td>
                                </tr>
                                </table>
                            </td>
                            <td width='15%' class='last-col  sigal_text'><h2><span>GRAND TOTAL</span></h2></td>
                        </tr>
                        </table>";
        // gets provincial breakdown
        $pbs = edu_get_provincial_breakdown($year, $schoolType, $region, $province, $municipality);
        $regUri = str_replace(' ', '+', $region);
        $prvUri = str_replace(' ', '+', $province);
        $baseUri = "/infographics/education/$year/$schoolType/reg/$regUri/$prvUri";
        foreach($pbs as $mun => $pb) {
            $munUri = str_replace(' ', '+', $mun);
            $uri = "$baseUri/$munUri";
            foreach($pb as $schoolId => $schoolInfo) {
                $schoolName = $schoolInfo['school_name'];
                $code .= "
                            <table cellpadding='0' cellspacing='0' border='0' width='100%' class='margin-line'>
                            <tr class='enrolment-text enrolment-text3'>
                                <td width='15%' class='sigal_text1 expandable-item'><a href='$uri'><h2>$mun<br/><b>$schoolId</b></h2></a></td>
                                <td width='25%' class='sigal_text1'><h2 class='school_name'>$schoolName</h2></td>
                                <td width='45%'>
                                    <table width='100%' cellpadding='0' cellspacing='0' class='count'>
                                    <tr>";
                $malesTotal = 0;
                $femalesTotal = 0;
                for($level=1; $level<=6; $level++) {
                    $males = number_format($schoolInfo["y".$level."m"]);
                    $females = number_format($schoolInfo["y".$level."f"]);
                    $total = number_format($schoolInfo["y".$level."m"]+$schoolInfo["y".$level."f"]);
                    $malesTotal += $schoolInfo["y".$level."m"];
                    $femalesTotal += $schoolInfo["y".$level."f"];
                    $styleClass = ($level>1) ? 'sigal_text2' : 'first-row sigal_text2';
                    $code .= "<td class='$styleClass' width='16.67%'><h2><a href='#' title='male: $males female: $females'>".format_enrolment_count($total)."</a></h2></td>";
                }
                $grandTotal = number_format($malesTotal+$femalesTotal);
                $malesTotal = number_format($malesTotal);
                $femalesTotal = number_format($femalesTotal);
                $code .= "      
                                    </tr>
                                    </table>
                                </td>
                                <td width='15%' class='last-col  sigal_text2'><h4 class='total'><a href='#' title='male: $malesTotal female: $femalesTotal'>$grandTotal</a></h4></td>
                            </tr>
                            </table>";
            }
        }
        $code .= "
                    </div>
                    <div class='more'><a style='float:left;' href='$reqUri?more'>more</a></div>";
        return $code;
    }
    /**
     * Build the Education infographics report
     * @param $year the reference year of the report, or <code>null</code> to get data for the past year
     * @param $schoolType the school type (es = elementary school; hs = high school)
     * @param $category (nat = national; reg = regional)
     * @param $region the region name (ignored if $category == 'nat')
     * @param $province the province name (ignored if $category == 'nat')
     * @param $municipality the municipality name (ignored if $category == 'nat')
    */
    function dgph_infographics_education_report($year = null, $schoolType = 'es', $category = 'nat', 
                                                $region = null, $province = null, $municipality = null) {
        $backIcon = false;
        if (null==$year) {
           // set to the past year
           $year = date('Y')-1;
        }
        else {
            $backIcon = true;
        }
        if ('reg'==$category) {
            if (null==$region) {
                // set default region
                $region = 'ARMM';
            }
        }
        $regs = array('ARMM', 'CAR', 'Caraga', 'NCR', 'Region I', 'Region II', 'Region III', 'Region IV-A', 'Region IV-B', 'Region V',
                      'Region VI', 'Region VII', 'Region VIII', 'Region IX', 'Region X', 'Region XI', 'Region XII');
        $rep = array('year' => $year, 'school_type' => $schoolType, 'category' => $category,
                     'region' => $region, 'province' => $province, 'municipality' => $municipality,
                     'back_icon' => $backIcon, 'regions' => $regs);
        return theme('dgph_infographics_education_report', $rep);
   }
   /**
    * Theme for Education infographics report
    */
    function theme_dgph_infographics_education_report(&$vars) {
        $modPath = drupal_get_path('module', 'dgph_infographics');
        drupal_add_css($modPath.'/css/dgph_infographics_common.css');
        drupal_add_css($modPath.'/css/dgph_infographics_education.css');
        drupal_add_js($modPath.'/js/dgph_infographics_education.js');
        $year = $vars['year'];
        $nextYear = $year+1;
        $schoolType = $vars['school_type'];
        $category = $vars['category'];
        $province = $vars['province'];
        $backIcon = $vars['back_icon'];
        $code = "
                    <div class='row dashboard-header'>
                        <div class='large-6 columns agency'>
                            <h2>INFOGRAPHICS</h2>
                            <h3>OPEN EDUCATION</h3>
                            <p>The Department is responsible for ensuring access to, promoting equity in, and improving the quality of basic education. Believes that education is the business of everyone. Through open data, stakeholders are given the opportunity to study and understand the education situation in the country and contribute to its growth.</p>
                            <p>Please use the search tool to find enrolments by region and by specific school. You can select specific enrolment data by clicking on the name in the table.</p>
                        </div>        
                        <div class='large-6 columns edu-select-year'>
                            <div class='infographics-education-year-con'>
                                <span>STATISTICS FOR SCHOOL YEAR</span>
                                <div class='year'><a href='#' data-dropdown='#select-year'>$year-$nextYear</a></div>
                            </div>";
        $maxYear = date('Y')-1;
        $code .= "
                            <span id='selected-year' style='display:none'>$year</span>
                            <div id='select-year' class='dropdown dropdown-tip dropdown-relative'>
                                <ul class='dropdown-menu'>
                                    <li><a>2013-2014</a></li>
                                    <li><a>2012-2013</a></li>
                                    <li><a>2011-2012</a></li>
                                </ul>
                            </div>
                        </div> 
                    </div>
                    <div class='row dashboard-content'>
                        <div class='large-3 columns national-rightside choosePillar'>
                            <div class='search-con'>
                                <h3>SEARCH SCHOOL</h3>
                                <div class='search-area'>
                                    <input id='lookup-school' type='image' class='clander-btn' src='".base_path()."/$modPath/images/search-icon.png' name=''> <input id='edu_free_search' type='text' class='clander-search' name='' onkeydown='lookupSchoolsKeydown(event)'>
                                </div>
                                <div id='lookup-category' class='school-con'>
                                    <span class='schoolId'><a>School ID</a></span>
                                    <span class='schoolName'><a>School Name</a></span>
                                </div>
                            </div>
                            <div class='clear'></div>
                            <div class='sort-title'>Sort Schools</div>
                            <div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
                                <h3 class='left-ui-accordion-header left-ui-accordion-header-first'>BASIC EDUCATION LEVEL</h3>
                                <div>
                                    <a>ELEMENTARY</a>
                                    <a>SECONDARY</a>
                                </div>";
        if ('reg'==$category) {
            // load regions
            $regs = $vars['regions'];
            // add regions menu
            $code .= "
                                <h3 class='left-ui-accordion-header'>REGION</h3>
                                <div>";
            $region = $vars['region'];
            foreach($regs as $reg) {
                $regUri = str_replace(' ', '+', $reg);
                $code .= "<a href='/infographics/education/$year/$schoolType/reg/$regUri'".(($regUri==$region) ?  " class='current'" : "")."'>$reg</a>";
            }                                       
            $code .= "
                                </div>";
        }
        $code .= "
                            </div>
                            <div class='clear'></div>
                            <div class='sort-info'></div>
                        </div>";
        if ('nat'==$category) {
            // gets national report
            $catCode = edu_build_national_report($vars);
        }
        else if (empty($province)) {
            // gets regional report
            $catCode = edu_build_regional_report($vars);
        }
        else {
            // gets provincial report
            $catCode = edu_build_provincial_report($vars);
        }
        $code .= "
                        <div class='large-9 columns education-content'>
                            <div class='social-title'>
                                <h2>TOTAL PUBLIC SCHOOL ENROLMENT</h2>
                                <ul class='social-icon'>";
        if ($backIcon) {
            // add back icon
            $code .= "<li><a href='/infographics/education'><img alt='' src='".base_path()."/$modPath/images/go-back-icon.png' title='Return to home of Education dashboard'></a></li>";
        }
        $code .= "
                                    <li><a><img alt='' src='".base_path()."sites/all/themes/dgph/images/icon-11.png'></a></li>
                 <li><a><img alt='' src='".base_path()."sites/all/themes/dgph/images/icon-19.png'></a></li>
        
                                    <li><a ><img alt='' src='".base_path()."sites/all/themes/dgph/images/icon-20.png'></a></li>
                                </ul>
                            </div>
                            $catCode
                            <div class='clear'></div>
                            <div class='table-legend'>
                                <p>Since 2011, enrolment data in schools have been gathered through the individual reports of all school heads in the Enhanced Basic Education.</p>
                            </div>
                        </div>
                    </div>
                  <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>";
        return $code;
   }
?>