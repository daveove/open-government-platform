<?php

/**
* Build the higher education infographics
* @param $year the reference year of the report)
* @param pillarId the pillar identifier, or <code>0</code> to get the average scores report for the specified agency
*/
function ched_infographics_higher_education_d3($pillar_id = 1, $year = '2010/2011') {
drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
drupal_set_title('Infographics');

$modPath = drupal_get_path('module', 'ched_report');
drupal_add_js($modPath.'/js/ched_dashboard.js');

	if(arg(3)) $pillar_id   = arg(3);
	if(arg(4)) $year	= arg(4).'/'.arg(5);

	$code = '';
        switch($pillar_id) {
            case 1:             // Dashboard three Pillar	1	        
                $code .= ched_get_dashb3_pillar1($pillar_id, $year);
                break;
            case 2:             // Dashboard three Pillar	2
                $code .= ched_get_dashb3_pillar2($pillar_id, $year);
                break;
        }
        return $code;

}

/**
* Build the dashboard three pillar 1 report
* @param @year the report year
* @return the pillar 1 report
*/
function ched_get_dashb3_pillar1($pillar_id, $year) {

// gets link to dashboard data
$year1 = explode("/", $year);
$dashbUploadUri = infographics_get_dashboard_datafile(DASHB_CHED, $year1[0]);
$dash_ched_download = '';
if (!empty($dashbUploadUri)) {    
    $dash_ched_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
}

	$code  = '';
	$code .= "<div class='row dashboard-header'>
		      <div class='large-9 columns sub-heading'>
		         <h3>Open Higher Education Dashboard</h3>
			 <div class='description'>Use this dashboard to get information regarding the higher education data on labor supply, oversubscribed and undersubscribed programs, licensure examination performance and State Universities and Colleges (SUCs) budget for planning, decision making and developmental initiatives.</div>
		      </div>
                      <div class='large-3 columns'>
                        <div class='year-con'>
                            <div class='year'><span>$year</span></div>
                        </div>
                      </div>
		  </div>

		  <div class='row dashboard-content dashboard3-content'>

		      <div class='large-3 columns leftsides datarequest choosePillar'>
			".dashboard_three_left_content($pillar_id, $year)."
		      </div>

		      <div class='large-9 columns works'>
			  <div class='row dashboard-container-header'>
				<div class='large-10 columns container-ritle'>
				    <h2>Higher Education Institutional Performance</h2>
				</div>
				<div class='large-2 columns container-social'>
				    <ul class='social-icon apcpi-social-icon'>
					<li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-11.png'></a></li>
                                <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-20.png'></a></li>

				    </ul>
				</div>
			  </div>

			  <div class='row dashboard-container-description'>
				<div class='large-12 columns'>
					<p>This dashboard contains information on the Passing Percentage of higher education institutions by licensure examination and region as compiled by based on the data of the Professional Regulation Commission - Educational Statistics Task Force.</p>
					<h4>PROFESSIONAL REGULATION COMMISSION NATIONAL PASSING PERCENTAGE BY LICENSURE EXAMINATION</h4>
				</div>
			  </div>
			  
			  <div class='row dashboard-container-graph'>
				<div class='large-12 columns container-graph'>
					<table cellpadding='0' cellspacing='0' border='0' width='100%'>
					<tr class='dash1-pillar2-table-header'>
					    <th class='first'>REGION</th>
					    <th>PUBLIC</th>
					    <th>PRIVATE</th>				
					    <th>BOTH SECTORS</th>
					</tr>
					
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>01</td>
                       <td>48.01</td>
                       <td>32.40</td>
                       <td class='last-col'>38.31</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>02</td>
                       <td>47.69</td>
                       <td>39.24</td>
                       <td class='last-col'>42.02</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>03</td>
                       <td>46.12</td>
                       <td>38.35</td>
                       <td class='last-col'>41.79</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>04</td>
                       <td>50.77</td>
                       <td>41.43</td>
                       <td class='last-col'>44.87</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>05</td>
                       <td>49.80</td>
                       <td>31.86</td>
                       <td class='last-col'>40.28</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>06</td>
                       <td>50.06</td>
                       <td>45.14</td>
                       <td class='last-col'>47.07</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>07</td>
                       <td>57.31</td>
                       <td>45.68</td>
                       <td class='last-col'>48.25</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>08</td>
                       <td>41.49</td>
                       <td>33.51</td>
                       <td class='last-col'>38.59</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>09</td>
                       <td>38.75</td>
                       <td>26.22</td>
                       <td class='last-col'>31.93</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>10</td>
                       <td>53.63</td>
                       <td>40.54</td>
                       <td class='last-col'>44.64</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>11</td>
                       <td>55.85</td>
                       <td>41.73</td>
                       <td class='last-col'>43.81</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>12</td>
                       <td>36.76</td>
                       <td>28.78</td>
                       <td class='last-col'>31.35</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>13</td>
                       <td>61.16</td>
                       <td>47.68</td>
                       <td class='last-col'>50.68</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>14</td>
                       <td>49.36</td>
                       <td>49.06</td>
                       <td class='last-col'>49.14</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>15</td>
                       <td>20.90</td>
                       <td>12.72</td>
                       <td class='last-col'>16.87</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>16</td>
                       <td>46.10</td>
                       <td>33.65</td>
                       <td class='last-col'>38.26</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>17</td>
                       <td>44.98</td>
                       <td>39.25</td>
                       <td class='last-col'>43.12</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>18</td>
                       <td>47.40</td>
                       <td>39.97</td>
                       <td class='last-col'>42.61</td>
                    </tr>
					</table>
			  

		      </div>
		  </div>
		  <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>
		";

return $code;
}



   /**
    * Build the dashboard three pillar 1 report
    * @param @year the report year
    * @return the pillar 1 report
    */
    function ched_collect_data_dashb3_pillar1($year) {

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb3_pillar1', 'pillar1')
                        ->fields('pillar1', array('id', 'discipline', 'passing_precentage'));      
       $query->condition('pillar1.financial_year', $year)
                    ->orderBy('pillar1.discipline');
       $res = $query->execute();
       $data  = array();
       $label = array();
       foreach($res as $row) {   
            $data[]  = floatval($row->passing_precentage);
	    $label[] = $row->discipline;
       }

       $chartCode = ched_d3_p1_build_bar_chart($data, $label, array('legend'=>$year, 'max'=>100));
        
       return $chartCode;
    }


/**
* Build the dashboard three pillar 2 report
* @param @year the report year
* @return the pillar 2 report
*/
function ched_get_dashb3_pillar2($pillar_id, $year) {

// gets link to dashboard data
$year1 = explode("/", $year);
$dashbUploadUri = infographics_get_dashboard_datafile(DASHB_CHED, $year1[0]);
$dash_ched_download = '';
if (!empty($dashbUploadUri)) {    
    $dash_ched_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
}

	$code  = '';
	$code .= "<div class='row dashboard-header'>
		      <div class='large-9 columns sub-heading'>
		         <h3>Open Higher Education Dashboard</h3>
			 <div class='description'>Use this dashboard to get information regarding the higher education data on labor supply, oversubscribed and undersubscribed programs, licensure examination performance and State Universities and Colleges (SUCs) budget for planning, decision making and developmental initiatives.</div>
		      </div>
                      <div class='large-3 columns'>
                        <div class='year-con'>
                            <div class='year'><span>$year</span></div>
                        </div>
                      </div>
		  </div>

		  <div class='row dashboard-content dashboard3-content'>

		      <div class='large-3 columns leftsides datarequest choosePillar'>
			".dashboard_three_left_content($pillar_id, $year)."
		      </div>

		      <div class='large-9 columns works'>
			  <div class='row dashboard-container-header'>
				<div class='large-10 columns container-ritle'>
				    <h2>Higher Education Institutional Performance</h2>
				</div>
				<div class='large-2 columns container-social'>
				    <ul class='social-icon apcpi-social-icon'>
					<li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-11.png'></a></li>
                                <li><a><img src='".base_path()."sites/all/themes/dgph/images/icon-20.png'></a></li>

				    </ul>
				</div>
			  </div>

			  <div class='row dashboard-container-description ".arg(6)."'>
				<div class='large-12 columns'>				        
					<p>This dashboard contains information on the Passing Percentage of higher education institutions by licensure examination and region as compiled by based on the data of the Professional Regulation Commission - Educational Statistics Task Force.</p>
					<h4>PROFESSIONAL REGULATION COMMISSION NATIONAL PASSING PERCENTAGE BY LICENSURE EXAMINATION</h4>
				</div>
			  </div>
			  
			  <div class='row dashboard-container-graph'>
        <div class='large-12 columns container-graph'>
          <table cellpadding='0' cellspacing='0' border='0' width='100%'>
          <tr class='dash1-pillar2-table-header'>
              <th class='first'>REGION</th>
              <th>PUBLIC</th>
              <th>PRIVATE</th>        
              <th>BOTH SECTORS</th>
          </tr>
          
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>01</td>
                       <td>48.01</td>
                       <td>32.40</td>
                       <td class='last-col'>38.31</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>02</td>
                       <td>47.69</td>
                       <td>39.24</td>
                       <td class='last-col'>42.02</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>03</td>
                       <td>46.12</td>
                       <td>38.35</td>
                       <td class='last-col'>41.79</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>04</td>
                       <td>50.77</td>
                       <td>41.43</td>
                       <td class='last-col'>44.87</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>05</td>
                       <td>49.80</td>
                       <td>31.86</td>
                       <td class='last-col'>40.28</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>06</td>
                       <td>50.06</td>
                       <td>45.14</td>
                       <td class='last-col'>47.07</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>07</td>
                       <td>57.31</td>
                       <td>45.68</td>
                       <td class='last-col'>48.25</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>08</td>
                       <td>41.49</td>
                       <td>33.51</td>
                       <td class='last-col'>38.59</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>09</td>
                       <td>38.75</td>
                       <td>26.22</td>
                       <td class='last-col'>31.93</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>10</td>
                       <td>53.63</td>
                       <td>40.54</td>
                       <td class='last-col'>44.64</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>11</td>
                       <td>55.85</td>
                       <td>41.73</td>
                       <td class='last-col'>43.81</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>12</td>
                       <td>36.76</td>
                       <td>28.78</td>
                       <td class='last-col'>31.35</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>13</td>
                       <td>61.16</td>
                       <td>47.68</td>
                       <td class='last-col'>50.68</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>14</td>
                       <td>49.36</td>
                       <td>49.06</td>
                       <td class='last-col'>49.14</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>15</td>
                       <td>20.90</td>
                       <td>12.72</td>
                       <td class='last-col'>16.87</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>16</td>
                       <td>46.10</td>
                       <td>33.65</td>
                       <td class='last-col'>38.26</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>17</td>
                       <td>44.98</td>
                       <td>39.25</td>
                       <td class='last-col'>43.12</td>
                    </tr>
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>18</td>
                       <td>47.40</td>
                       <td>39.97</td>
                       <td class='last-col'>42.61</td>
                    </tr>
          </table>
        

          </div>
		  </div>
		  <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>
		";

return $code;
}


   /**
    * Build the dashboard three pillar 2 report
    * @param @year the report year
    * @return the pillar 2 report
    */
    function ched_collect_data_dashb3_pillar2($year) {

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb3_pillar2', 'pillar2')
                        ->fields('pillar2', array('id', 'region', 'public', 'private', 'both_sector'));      
       $query->condition('pillar2.financial_year', $year)
                    ->orderBy('pillar2.id');
       $res = $query->execute();

       $code = "
            <tr class='enrolment-text'>
               <td colspan='7' class='last-col'><h2>There is no data available for the selected criteria!</h2></td>
            </tr>";
       foreach($res as $i=>$row) {
           if($i==0) $code = "";
                $code.= "
                    <tr class='dash1-pillar2'>
                       <td class='first-col region'>".$row->region."</td>
                       <td>".number_format($row->public, 2)."</td>
                       <td>".number_format($row->private, 2)."</td>
                       <td class='last-col'>".number_format($row->both_sector, 2)."</td>
                    </tr>";
       }
       
       return $code;
    }





