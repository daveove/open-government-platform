<?php

/**
* Build the higher education infographics
* @param $year the reference year of the report)
* @param pillarId the pillar identifier, or <code>0</code> to get the average scores report for the specified agency
*/
function ched_infographics_higher_education_d2($pillar_id = 1, $year = '2010/2011') {
drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
drupal_set_title('Infographics');

$modPath = drupal_get_path('module', 'ched_report');
drupal_add_js($modPath.'/js/ched_dashboard.js');

	if(arg(3)) $pillar_id   = arg(3);
	if(arg(4)) $year	= arg(4).'/'.arg(5);

	$code = '';
        switch($pillar_id) {
            case 1:             // Dashboard two Pillar	1	        
                $code .= ched_get_dashb2_pillar1($pillar_id, $year);
                break;
            case 2:             // Dashboard two Pillar	2
                $code .= ched_get_dashb2_pillar2($pillar_id, $year);
                break;
            case 3:             // Dashboard two Pillar	3
                $code .= ched_get_dashb2_pillar3($pillar_id, $year);
                break;
        }
        return $code;

}

/**
* Build the dashboard two pillar 1 report
* @param @year the report year
* @return the pillar 1 report
*/
function ched_get_dashb2_pillar1($pillar_id, $year) {

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
			 <div class='description'>Use this dashboard to get information regarding the higher education data on labor supply, oversubscribed and undersubscribed programs, licensure examination performance and state universities and colleges budget for planning, decision making and developmental initiatives.</div>
		      </div>
                      <div class='large-3 columns'>
                        <div class='year-con'>
                            <div class='year'><span>$year</span></div>
                        </div>
                      </div>
		  </div>

		  <div class='row dashboard-content dashboard2-content'>

		      <div class='large-3 columns leftsides datarequest choosePillar'>
			".dashboard_two_left_content($pillar_id, $year)."
		      </div>

		      <div class='large-9 columns works'>
			  <div class='row dashboard-container-header'>
				<div class='large-10 columns container-ritle'>
				    <h2>What Program To Enroll (Oversubscribed and Undersubcribed Programs)</h2>
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
					<p>This dashboard shows the identified oversubscribed and undersubscribed programs with corresponding enrolment/graduates data that will serve as a guide for students/parents on what program to enroll, for school administrators on what programs to offer and for other stakeholders for developmental initiatives/interventions.</p>
					<h4>ENROLLMENT BY DISCIPLINE &nbsp;&nbsp;".l('ENROLLMENT', 'infographics/ched-higher-education/d2/1'.'/'.$year.'/enrollment', array('attributes' => array('class' => array('enrollment'))))."&nbsp;&nbsp; - &nbsp;&nbsp;".l('GRADUATES', 'infographics/ched-higher-education/d2/1'.'/'.$year.'/graduates', array('attributes' => array('class' => array('graduates'))))."</h4>
				</div>
			  </div>
			  
			  <div class='row dashboard-container-graph'>
				<div class='large-12 columns container-graph'>	
				     <div class='dashboard3pillar1graph'>
					".ched_collect_data_dashb2_pillar1($year)."
				     </div>
				</div>
			  </div>
			  ".dashboard_two_legend($pillar_id)."

		      </div>
		  </div>
		  <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>
		";

return $code;
}



   /**
    * Build the dashboard two pillar 1 report
    * @param @year the report year
    * @return the pillar 1 report
    */
    function ched_collect_data_dashb2_pillar1($year) {

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb2_pillar1', 'pillar1')
                        ->fields('pillar1', array('id', 'discipline_group', 'enrolment', 'graduates'));      
       $query->condition('pillar1.financial_year', $year)
                    ->orderBy('pillar1.id');
       $res = $query->execute();
       $data  = array();
       $label = array();

       foreach($res as $row) {
	 if(arg(6)=='graduates'){
	    $max_val = '200000';
            $data[]  = floatval($row->graduates);
	 } else {
	    $max_val = '1000000';
	    $data[]  = floatval($row->enrolment);
	 }
	 $label[] = $row->discipline_group;
       }

       $chartCode = ched_d2_p1_build_bar_chart($data, $label, array('legend'=>$year, 'max'=>$max_val));
        
       return $chartCode;
    }


/**
* Build the dashboard one pillar 2 report
* @param @year the report year
* @return the pillar 2 report
*/
function ched_get_dashb2_pillar2($pillar_id, $year) {

// gets link to dashboard data
$year1 = explode("/", $year);
$dashbUploadUri = infographics_get_dashboard_datafile(DASHB_CHED, $year1[0]);
$dash_ched_download = '';
if (!empty($dashbUploadUri)) {    
    $dash_ched_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
}

$choose = (arg(7)=='choose') ? '/choose' : '';

	$code  = '';
	$code .= "<div class='row dashboard-header'>
		      <div class='large-9 columns sub-heading'>
		         <h3>Open Higher Education Dashboard</h3>
			 <div class='description'>Use this dashboard to get information regarding the higher education data on labor supply, oversubscribed and undersubscribed programs, licensure examination performance and state universities and colleges budget for planning, decision making and developmental initiatives.</div>
		      </div>
                      <div class='large-3 columns'>
                        <div class='year-con'>
                            <div class='year'><span>$year</span></div>
                        </div>
                      </div>
		  </div>

		  <div class='row dashboard-content dashboard2-content pillar2'>

		      <div class='large-3 columns leftsides datarequest choosePillar'>
			".dashboard_two_left_content($pillar_id, $year)."
		      </div>

		      <div class='large-9 columns works'>
			  <div class='row dashboard-container-header'>
				<div class='large-10 columns container-ritle'>
				    <h2>What Program To Enroll (Oversubscribed and Undersubcribed Programs)</h2>
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
				        <h4>INFORMATION ON OVERSUBSCRIBED PROGRAMS WITH NUMBER OF ENROLLEES AND GRADUATES OF THE RECENT ACADEMIC YEAR</h4>
					<p>This dashboard shows the CHED identified oversubscribed/undersubscribed programs enrolment/graduate which will serve as a  guide for students/parrents on what program to enroll and for school administrators on what programs to offer.</p>
					<h4>OVERSUBSCRIBED PROGRAM &nbsp;&nbsp;".l('ENROLLMENT', 'infographics/ched-higher-education/d2/2'.'/'.$year.'/enrollment'.$choose, array('attributes' => array('class' => array('enrollment'))))."&nbsp;&nbsp; - &nbsp;&nbsp;".l('GRADUATES', 'infographics/ched-higher-education/d2/2'.'/'.$year.'/graduates'.$choose, array('attributes' => array('class' => array('graduates'))))."</h4>
				</div>
			  </div>
			  
			  <div class='row dashboard-container-graph'>
				<div class='large-12 columns container-graph'>				
					".ched_collect_data_dashb2_pillar2($year)."
					<div class='' style='text-align:center;'><b>Program</b></div>
				</div>
			  </div>
			  ".dashboard_two_legend($pillar_id)."

		      </div>
		  </div>
		  <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>
		";

return $code;
}


   /**
    * Build the dashboard two pillar 2 report
    * @param @year the report year
    * @return the pillar 2 report
    */
    function ched_collect_data_dashb2_pillar2($year) {

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb2_pillar2', 'pillar2')
                        ->fields('pillar2', array('id', 'oversubscribed_program', 'enrolment', 'graduates'));
       $query->condition('pillar2.financial_year', $year)
                    ->orderBy('pillar2.id');
       $res = $query->execute();

       $data  = array();
       $label = array();
       foreach($res as $row) {
	 if(arg(6)=='graduates'){
	    $max_val = '30000';
            $data[]  = floatval($row->graduates);
	 } else {
	    $max_val = '400000';
	    $data[]  = floatval($row->enrolment);
	 }
	    $label[] = $row->oversubscribed_program;
       }

       $chartCode = ched_d2_p2_build_bar_chart($data, $label, array('legend'=>$year, 'max'=>$max_val));
        
       return $chartCode;
    }


   /**
    * Build the dashboard two pillar 2 report return result based on year, compare with other year.
    * @param @year the report year
    * @return the pillar 2 report
    */
    function ched_collect_data_dashb2_pillar2_compare($year) {

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb2_pillar2', 'pillar2')
                        ->fields('pillar2', array('id', 'oversubscribed_program', 'enrolment', 'graduates'));
       $query->condition('pillar2.financial_year', $year)
                    ->orderBy('pillar2.id');
       $res = $query->execute();

       $data  = array();
       $label = array();
       foreach($res as $row) {
	 if(arg(6)=='graduates'){
	    $max_val = '30000';
            $data[]  = floatval($row->graduates);
	 } else {
	    $max_val = '400000';
	    $data[]  = floatval($row->enrolment);
	 }
	    $label[] = $row->oversubscribed_program;
       }
               
       return $data;
    }




/**
* Build the dashboard one pillar 3 report
* @param @year the report year
* @return the pillar 3 report
*/
function ched_get_dashb2_pillar3($pillar_id, $year) {

// gets link to dashboard data
$year1 = explode("/", $year);
$dashbUploadUri = infographics_get_dashboard_datafile(DASHB_CHED, $year1[0]);
$dash_ched_download = '';
if (!empty($dashbUploadUri)) {    
    $dash_ched_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
}
$choose = (arg(7)=='choose') ? '/choose' : '';

	$code  = '';
	$code .= "<div class='row dashboard-header'>
		      <div class='large-9 columns sub-heading'>
		         <h3>Open Higher Education Dashboard</h3>
			 <div class='description'>Use this dashboard to get information regarding the higher education data on labor supply, oversubscribed and undersubscribed programs, licensure examination performance and state universities and colleges budget for planning, decision making and developmental initiatives.</div>
		      </div>
                      <div class='large-3 columns'>
                        <div class='year-con'>
                            <div class='year'><span>$year</span></div>
                        </div>
                      </div>
		  </div>

		  <div class='row dashboard-content dashboard2-content pillar2'>

		      <div class='large-3 columns leftsides datarequest choosePillar'>
			".dashboard_two_left_content($pillar_id, $year)."
		      </div>

		      <div class='large-9 columns works'>
			  <div class='row dashboard-container-header'>
				<div class='large-10 columns container-ritle'>
				    <h2>What Program To Enroll (Oversubscribed and Undersubcribed Programs)</h2>
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
				        <h4>INFORMATION ON UNDERSUBSCRIBED PROGRAMS WITH NUMBER OF ENROLLEES AND GRADUATES OF THE RECENT ACADEMIC YEAR</h4>
					<p>This dashboard shows the CHED identified oversubscribed/undersubscribed programs enrolment/graduate which will serve as a  guide for students/parrents on what program to enroll and for school administrators on what programs to offer.</p>
					<h4>UNDERSUBSCRIBED PROGRAM &nbsp;&nbsp;".l('ENROLLMENT', 'infographics/ched-higher-education/d2/3'.'/'.$year.'/enrollment'.$choose, array('attributes' => array('class' => array('enrollment'))))."&nbsp;&nbsp; - &nbsp;&nbsp;".l('GRADUATES', 'infographics/ched-higher-education/d2/3'.'/'.$year.'/graduates'.$choose, array('attributes' => array('class' => array('graduates'))))."</h4>
				</div>
			  </div>
			  
			  <div class='row dashboard-container-graph'>
				<div class='large-12 columns container-graph'>				
					".ched_collect_data_dashb2_pillar3($year)."
					<div class='' style='text-align:center;'><b>Program</b></div>
				</div>
			  </div>
			  ".dashboard_two_legend($pillar_id)."

		      </div>
		  </div>
		  <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>
		";

return $code;
}


   /**
    * Build the dashboard one pillar 3 report
    * @param @year the report year
    * @return the pillar 3 report
    */
    function ched_collect_data_dashb2_pillar3($year) {

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb2_pillar3', 'pillar3')
                        ->fields('pillar3', array('id', 'undersubscribed_program', 'enrolment', 'graduates'));
       $query->condition('pillar3.financial_year', $year)
                    ->orderBy('pillar3.id');
       $res = $query->execute();

       $data  = array();
       $label = array();
       foreach($res as $row) {
	 if(arg(6)=='graduates'){
	    $max_val = '40000';
            $data[]  = floatval($row->graduates);
	 } else {
	    $max_val = '300000';
	    $data[]  = floatval($row->enrolment);
	 }
	    $label[] = $row->undersubscribed_program;
       }

       $chartCode = ched_d2_p3_build_bar_chart($data, $label, array('legend'=>$year, 'max'=>$max_val));
        
       return $chartCode;
    }



   /**
    * Build the dashboard two pillar 3 report return result based on year, compare with other year.
    * @param @year the report year
    * @return the pillar 3 report
    */
    function ched_collect_data_dashb2_pillar3_compare($year) {

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb2_pillar3', 'pillar3')
                        ->fields('pillar3', array('id', 'undersubscribed_program', 'enrolment', 'graduates'));
       $query->condition('pillar3.financial_year', $year)
                    ->orderBy('pillar3.id');
       $res = $query->execute();

       $data  = array();
       foreach($res as $row) {
	 if(arg(6)=='graduates'){
	    $max_val = '40000';
            $data[]  = floatval($row->graduates);
	 } else {
	    $max_val = '300000';
	    $data[]  = floatval($row->enrolment);
	 }	    
       }       
        
       return $data;
    }







