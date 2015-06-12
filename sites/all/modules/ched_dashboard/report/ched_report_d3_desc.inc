<?php


/**
* Manage legend for dashboard three.
* @param $pillar_id the pillar identifier
*/
function dashboard_three_legend($pillar_id){
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
				<p>National Passing Percentage refers to the number of passers over the number of takers.</p>
			</div>
		     </div>
		</div>
		";
		break;		
	}

return $legend;
}


/**
* Manage left content for dashboard three.
* @param $pillar_id the pillar identifier
*/
function dashboard_three_left_content($pillar_id, $year){
$left_content = '';
	switch($pillar_id){
		case '1':

		$pillar_class1 = '';
		$pillar_class2 = '';

		if($pillar_id==1){
		   $pillar_class1 = 'active';
		   $year_heading = 'Choose Year'; 
		} elseif($pillar_id==2) {
		   $pillar_class2 = 'active';
		   $year_heading = 'Choose Year'; 
		} else {
		   $year_heading = 'Choose Year'; 
		}


		$psc = '';
		if(arg(4)==2010) $psc	= 1;
		if(arg(4)==2011) $psc	= 2;
		if(arg(4)==2012) $psc	= 3;

		$defIndex = 0;
		if(arg(4)) $defIndex = 1;
		if(arg(6)) $defIndex = 2;
		 

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>DASHBOARDS</h3>
			<div>
				".l('Labor Supply From Higher Education', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('What Program To Enroll (Oversubscribed And Undersubscribed)', 'infographics/ched-higher-education/d2/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('Higher Education Licensure Performance', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array('active') )) )."

			</div>
			<h3 class='left-ui-accordion-header'>Choose Pillar</h3>
			<div>
				".l('National Passing Percentage By Licensure Examination', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array($pillar_class1))) )."
				".l('National Passing Percentage By Region', 'infographics/ched-higher-education/d3/2/2012/2013', array('attributes' => array('class' => array($pillar_class2))) )."				
			</div>
			<h3 class='left-ui-accordion-header'>".$year_heading."</h3>
			<div>
			<form class='custom dash3pill1'>
				<label for='total_q1'><input type='checkbox' name='total' dash3-p1='2010/2011' style='display: none;' ".((1==$psc) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;2010/11</label>
				<label for='total_q1'><input type='checkbox' name='total' dash3-p1='2011/2012' style='display: none;' ".((2==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;2011/12</label>
				<label for='total_q1'><input type='checkbox' name='total' dash3-p1='2012/2013' style='display: none;' ".((3==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;2012/13</label>
			</form>
			</div>
		</div>
		";
		break;

		case '2':

		$pillar_class1 = '';
		$pillar_class2 = '';

		if($pillar_id==1){
		   $pillar_class1 = 'active';
		   $year_heading = 'Choose Academic Year (AY)'; 
		} elseif($pillar_id==2) {
		   $pillar_class2 = 'active';
		   $year_heading = 'Choose Year'; 
		} else {
		   $year_heading = 'Choose Year'; 
		}


		$psc = '';
		if(arg(4)==2010) $psc	= 1;
		if(arg(4)==2011) $psc	= 2;
		if(arg(4)==2012) $psc	= 3;

		$defIndex = 0;
		if(arg(4)) $defIndex = 1;
		if(arg(6)) $defIndex = 2;

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>DASHBOARDS</h3>
			<div>
				".l('Labor Supply From Higher Education', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('What Program To Enroll (Oversubscribed And Undersubscribed)', 'infographics/ched-higher-education/d2/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('Higher Education Licensure Performance', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array('active') )) )."

			</div>
			<h3 class='left-ui-accordion-header'>Choose Pillar</h3>
			<div>
				".l('National Passing Percentage By Licensure Examination', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array($pillar_class1))) )."
				".l('National Passing Percentage By Region', 'infographics/ched-higher-education/d3/2/2012/2013', array('attributes' => array('class' => array($pillar_class2))) )."				
			</div>
			<h3 class='left-ui-accordion-header'>".$year_heading."</h3>
			<div>
			<form class='custom dash3pill2'>
				<label for='total_q1'><input type='checkbox' name='total' dash3-p2='2010/2011' style='display: none;' ".((1==$psc) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;AY 2010/11</label>
				<label for='total_q1'><input type='checkbox' name='total' dash3-p2='2011/2012' style='display: none;' ".((2==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2011/12</label>
				<label for='total_q1'><input type='checkbox' name='total' dash3-p2='2012/2013' style='display: none;' ".((3==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2012/13</label>
			</form>
			</div>
		</div>
		";
	}

return $left_content;
}