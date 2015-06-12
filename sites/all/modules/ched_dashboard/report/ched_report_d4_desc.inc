<?php


/**
* Manage legend for dashboard four.
* @param $pillar_id the pillar identifier
*/
function dashboard_four_legend($pillar_id){
$legend = '';
	switch($pillar_id){
		case '1':
		case '2':
		case '3':
		$legend = "
		<div class='row legend'>
		     <div class='large-12 columns legend'>
		       <div class='legent-container'>
			    <div class='legend-heading'>LEGEND</div>
				<p>Appropriations, General - An authorization for incurring obligations during a specified budget year pertains to the annual appropriations under the General Appropriations Act which are presented by Programs, Activities, and Projects (Source: Organizational Performance Indicator Framework (OPIF) Reference Guide)</p>
				<p>Personal Services (PS) are provisions for the payment of salaries, wages and other compensation. Source: Organizational Performance Indicator Framework (OPIF) Reference Guide)</p>
				<p>Maintenance and Other Operating Expenses (MOOE) refers to expenditures to support the operations of government agencies, such as expenses for supplies and materials; transportation and travel utilities (water, power, etc.) and repairs, etc. Source: Organizational Performance Indicator Framework (OPIF) Reference Guide)</p>
				<p>Capital Outlay (CO) refers to appropriations for the purchase of goods and services, the benefits of which extend beyond the fiscal year and which add to the assets of the Government, including investments in the capital stock of GOCCs and their subsidiaries. Source: Organizational Performance Indicator Framework (OPIF) Reference Guide)</p>
				<p>The Cost per Student is computed by dividing the sum of PS and MOOE to the Weighted Enrolment which is equal to the enrolment headcount multiplied by weight  (Pre-Sch+Elem+HE = 0.50; Voc-Tech = 0.75; Pre-Bacc+Bacc = 1.00; Post-Bacc+Master = 1.50; Doctorate = 2.00)</p>
				<p>The Tuition Fee per Unit is the total amount per unit, which a student has to pay to enroll in the subject. </p>
			    </div>
		     </div>
		</div>
		";
		break;		
	}

return $legend;
}


/**
* Manage left content for dashboard four.
* @param $pillar_id the pillar identifier
*/
function dashboard_four_left_content($pillar_id, $year){

$modPath = drupal_get_path('module', 'ched_report');
drupal_add_js($modPath.'/js/ched_dashboard.js');

$left_content = '';
	switch($pillar_id){
		case '1':
		case '2':
		case '3':

		if($pillar_id==1){
			$pillar_class1 = 'active';
		} else { 
			$pillar_class1 = '';
		}

		$region= (isset($_GET['region'])) ? $_GET['region']: '';
		$suc   = (isset($_GET['suc'])) ? $_GET['suc']: '';
		$total = (isset($_GET['tot'])) ? $_GET['tot']: '';
		$psc = (isset($_GET['psc'])) ? $_GET['psc']: '';

		$defIndex = 0;

		if($region){ $defIndex = 1; }
		if($suc)  { $defIndex = 2; }
		if($total){ $defIndex = 3; }
		if($psc)  { $defIndex = 4; }
                
                $yidx = 3;
		if(arg(4)==2010) $yidx	= 1;
		if(arg(4)==2011) $yidx	= 2;
		
		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>DASHBOARDS</h3>
			<div>
				".l('Labor Supply From Higher Education', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('What Program To Enroll (Oversubscribed And Undersubscribed)', 'infographics/ched-higher-education/d2/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('Higher Education Licensure Performance', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array('') )) )."
			</div>
			<h3 class='left-ui-accordion-header'>Region</h3>
			<div>
				".dashboard4_region_search($year)."
				
			</div>
			<h3 class='left-ui-accordion-header'>State Universities and Colleges</h3>
			<div>				
				".dashboard4_college_university_search($year)."				
			</div>
			<h3 class='left-ui-accordion-header'>Total Gaa Budget</h3>
			<div>
			<form class='custom dash4total'>
				<label for='total_q1'><input type='checkbox' name='total' quarter-id='1' style='display: none;' ".((1==$total) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;0 - 10,000</label>
				<label for='total_q1'><input type='checkbox' name='total' quarter-id='2' style='display: none;' ".((2==$total) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;10,000 - 20,000</label>
				<label for='total_q1'><input type='checkbox' name='total' quarter-id='3' style='display: none;' ".((3==$total) ?  "checked='checked'" : "")."><span value='3' class='custom checkbox'></span>&nbsp;&nbsp;20,000 - 50,000</label>
				<label for='total_q1'><input type='checkbox' name='total' quarter-id='4' style='display: none;' ".((4==$total) ?  "checked='checked'" : "")."><span value='4' class='custom checkbox'></span>&nbsp;&nbsp;50,000 - 100,000</label>
				<label for='total_q1'><input type='checkbox' name='total' quarter-id='5' style='display: none;' ".((5==$total) ?  "checked='checked'" : "")."><span value='5' class='custom checkbox'></span>&nbsp;&nbsp;100,000 - 200,000</label>
				<label for='total_q1'><input type='checkbox' name='total' quarter-id='6' style='display: none;' ".((6==$total) ?  "checked='checked'" : "")."><span value='6' class='custom checkbox'></span>&nbsp;&nbsp;200,000 - 500,000</label>
				<label for='total_q1'><input type='checkbox' name='total' quarter-id='7' style='display: none;' ".((7==$total) ?  "checked='checked'" : "")."><span value='7' class='custom checkbox'></span>&nbsp;&nbsp;500,000 - 10,00,000</label>
				<label for='total_q1'><input type='checkbox' name='total' quarter-id='8' style='display: none;' ".((8==$total) ?  "checked='checked'" : "")."><span value='8' class='custom checkbox'></span>&nbsp;&nbsp;10,00,000 - 5,000,000</label>
				<label for='total_q1'><input type='checkbox' name='total' quarter-id='9' style='display: none;' ".((9==$total) ?  "checked='checked'" : "")."><span value='9' class='custom checkbox'></span>&nbsp;&nbsp;5,000,000 - 10,000,000</label>								
			</form>
			</div>
			<h3 class='left-ui-accordion-header'>Per Student Cost</h3>
			<div>
			<form class='custom dash4psc'>
				<label for='total_q1'><input type='checkbox' name='total' psc-id='1' style='display: none;' ".((1==$psc) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;0 - 5,000</label>
				<label for='total_q1'><input type='checkbox' name='total' psc-id='2' style='display: none;' ".((2==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;5,001 - 10,000</label>
				<label for='total_q1'><input type='checkbox' name='total' psc-id='3' style='display: none;' ".((3==$psc) ?  "checked='checked'" : "")."><span value='3' class='custom checkbox'></span>&nbsp;&nbsp;10,001 - 20,000</label>
				<label for='total_q1'><input type='checkbox' name='total' psc-id='4' style='display: none;' ".((4==$psc) ?  "checked='checked'" : "")."><span value='4' class='custom checkbox'></span>&nbsp;&nbsp;20,001 - 30,000</label>
				<label for='total_q1'><input type='checkbox' name='total' psc-id='5' style='display: none;' ".((5==$psc) ?  "checked='checked'" : "")."><span value='5' class='custom checkbox'></span>&nbsp;&nbsp;30,001 - 40,000</label>
				<label for='total_q1'><input type='checkbox' name='total' psc-id='6' style='display: none;' ".((6==$psc) ?  "checked='checked'" : "")."><span value='6' class='custom checkbox'></span>&nbsp;&nbsp;40,001 - 50,000</label>
				<label for='total_q1'><input type='checkbox' name='total' psc-id='7' style='display: none;' ".((7==$psc) ?  "checked='checked'" : "")."><span value='7' class='custom checkbox'></span>&nbsp;&nbsp;Greater than 50,000</label>
			</form>
			</div>
                        <h3 class='left-ui-accordion-header'>Choose Year</h3>
			<div>
			<form class='custom dash4pill1'>
				<label for='year_1'><input type='checkbox' name='total' dash4-p1='2010/2011' style='display: none;' ".((1==$yidx) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;2010/11</label>
				<label for='year_2'><input type='checkbox' name='total' dash4-p1='2011/2012' style='display: none;' ".((2==$yidx) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;2011/12</label>
				<label for='year_3'><input type='checkbox' name='total' dash4-p1='2012/2013' style='display: none;' ".((3==$yidx) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;2012/13</label>
			</form>
			</div>
	
		</div>
		";
	}

return $left_content;
}


/**
* Search Range based on total field.
*/
function dash4total(){
	$result = array(
		1=>array(0, 10000),
		2=>array(10000, 20000),
		3=>array(20000, 50000),
		4=>array(50000, 100000),
		5=>array(100000, 200000),
		6=>array(200000, 500000),
		7=>array(500000, 1000000),
		8=>array(1000000, 5000000),
		9=>array(5000000, 10000000)		
	);
	
return $result;
}

/**
* Search Range based on PSC
*/
function dash4psc(){
	$result = array(
		1=>array(0, 5000),
		2=>array(5001, 10000),
		3=>array(10001, 20000),
		4=>array(20001, 30000),
		5=>array(30001, 40000),
		6=>array(40001, 50000),
		7=>array(50001, 5000000000)
	);
	
return $result;
}



/**
* Manage left content for dashboard four.
* @param $pillar_id the pillar identifier
* collecting region for dashboard 4 search
*/
function dashboard4_region_search($year){

$region_selected = (isset($_GET['region'])) ? $_GET['region']: '';

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb4_pillar1', 'pillar1')
                        ->fields('pillar1', array('id', 'region'))

                    ->orderBy('pillar1.id');
		    
       $res = $query->execute();
       $region  = array();
       foreach($res as $row) {
	   if(!in_array ($row->region, $region)) {
	      $region[] = $row->region;
	   }
       }

       $data = '<select class="region">';
       $data.= '<option value="0">Select</option>';
       foreach($region as $i=>$region1){
          if($region_selected == ($i+1)){
	     $data.= '<option value="'.($i+1).'" selected>'.$region1.'</option>';
	  } else {
	     $data.= '<option value="'.($i+1).'">'.$region1.'</option>';
	  }
       }
       $data.= '</select>';


       return $data;
}


/**
* Return region key
*/
function dashboard4_region_key_return(){

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb4_pillar1', 'pillar1')
                        ->fields('pillar1', array('id', 'region'))

                    ->orderBy('pillar1.id');
		    
       $res = $query->execute();
       $region  = array();
       foreach($res as $row) {
	   if(!in_array ($row->region, $region)) {
	      $region[] = $row->region;
	   }
       }

       return $region;
}



/**
* Manage left content for dashboard four.
* @param $pillar_id the pillar identifier
* collecting region for dashboard 4 search
*/
function dashboard4_college_university_search($year){

$region_selected = (isset($_GET['region'])) ? $_GET['region']: '';

if($region_selected && $region_selected!=0){

$suc = (isset($_GET['suc'])) ? $_GET['suc']: '';

$region = dashboard4_region_key_return();

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb4_pillar1', 'pillar1')
                        ->fields('pillar1', array('id', 'suc_name'));
       $query->condition('pillar1.region', $region[$region_selected-1])
                    ->orderBy('pillar1.id');
		    
       $res = $query->execute();
       $college_uni  = array();
       foreach($res as $row) {
	   if(!in_array ($row->suc_name, $college_uni)) {
	      $college_uni[] = $row->suc_name;
	   }
       }

       $data = '<select class="college_university">';
       $data.= '<option value="0">Select</option>';
       foreach($college_uni as $i=>$college_uni1){
          if($suc == ($i+1)){
	     $data.= '<option value="'.($i+1).'" selected>'.$college_uni1.'</option>';
	  } else {
	     $data.= '<option value="'.($i+1).'">'.$college_uni1.'</option>';
	  }          
       }
       $data.= '</select>';


} else {
       $data = 'Please select Region first.';
}

       return $data;
}


/**
* Return college university key
*/
function dashboard4_college_university_key_return($region){

$region_list = dashboard4_region_key_return();

       // gets averages for all agencies and pillars
       $query = db_select('ched_mini_dashb4_pillar1', 'pillar1')
                        ->fields('pillar1', array('id', 'suc_name'));
       $query->condition('pillar1.region', $region_list[$region-1])
                    ->orderBy('pillar1.id');
		    
       $res = $query->execute();
       $college_uni  = array();
       foreach($res as $row) {
	   if(!in_array ($row->suc_name, $college_uni)) {
	      $college_uni[] = $row->suc_name;
	   }
       }

       return $college_uni;
}