<?php


/**
* Manage legend for dashboard one.
* @param $pillar_id the pillar identifier
*/
function dashboard_two_legend($pillar_id){
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
				<p>The oversubscribed program refers to a program offered by a big number and/or with big number of enrollees that produce skills declared by the labor market as oversupply and less demand. While the undersubscribed program refers to a program identified as priority program based on offered by limited number and/or with few enrollees that produce skills declared by the labor market as in-demand.</p>
				<p>Prioritizes programs to guide students, parents and leaders towards programs that are in-demand and market-responsive including the government agencies in making efficient use of scarce resources to maximize the higher education sector's contribution to national development efforts. The prioritization of programs is determined through market signals, Key Demand-supply studies and tracer studies.</p>
			</div>
		     </div>
		</div>
		";
		break;		
	}

return $legend;
}


/**
* Manage left content for dashboard one.
* @param $pillar_id the pillar identifier
*/
function dashboard_two_left_content($pillar_id, $year){
$left_content = '';
	switch($pillar_id){
		case '1':

		$pillar_class1 = '';
		$pillar_class2 = '';
		$pillar_class3 = '';

		if($pillar_id==1){
		   $pillar_class1 = 'active';
		   $year_heading = 'Choose Academic Year (AY)'; 
		} elseif($pillar_id==2) {
		   $pillar_class2 = 'active';
		   $year_heading = 'Compare By Academic Years'; 
		} elseif($pillar_id==3) {
		   $pillar_class3 = 'active';
		   $year_heading = 'Compare by Year'; 
		} else {
		   $year_heading = 'Choose Year'; 
		}

		$psc = '';
		if(arg(4)==2010) $psc	= 1;
		if(arg(4)==2011) $psc	= 2;
		if(arg(4)==2012) $psc	= 3;

		$defIndex = 0;
		if(arg(6)) $defIndex = 1;
		if(arg(7)) $defIndex = 2;

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>DASHBOARDS</h3>
			<div>
				".l('Labor Supply From Higher Education', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('What Program To Enroll (Oversubscribed And Undersubscribed)', 'infographics/ched-higher-education/d2/1/2012/2013', array('attributes' => array('class' => array('active') )) )."
				".l('Higher Education Licensure Performance', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array('') )) )."
		</div>
			<h3 class='left-ui-accordion-header'>Choose Pillar</h3>
			<div>
				".l('Totals By Discipline', 'infographics/ched-higher-education/d2/1/2012/2013/enrollment', array('attributes' => array('class' => array($pillar_class1))) )."
				".l('Oversubscribed Programs', 'infographics/ched-higher-education/d2/2/2012/2013/enrollment', array('attributes' => array('class' => array($pillar_class2))) )."
				".l('Undersubscribed Programs', 'infographics/ched-higher-education/d2/3/2012/2013/enrollment', array('attributes' => array('class' => array($pillar_class3))) )."
			</div>
			<h3 class='left-ui-accordion-header'>".$year_heading."</h3>
			<div>
			<form class='custom dash2pill1'>
				<label for='total_q1'><input type='checkbox' name='total' dash2-p1='2010/2011".(arg(6) ? "/".arg(6): "")."' style='display: none;' ".((1==$psc) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;AY 2010/11</label>
				<label for='total_q1'><input type='checkbox' name='total' dash2-p1='2011/2012".(arg(6) ? "/".arg(6): "")."' style='display: none;' ".((2==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2011/12</label>
				<label for='total_q1'><input type='checkbox' name='total' dash2-p1='2012/2013".(arg(6) ? "/".arg(6): "")."' style='display: none;' ".((3==$psc) ?  "checked='checked'" : "")."><span value='3' class='custom checkbox'></span>&nbsp;&nbsp;AY 2012/13</label>
			</form>
			</div>
		</div>
		";
		break;

		case '2':

		$pillar_class1 = '';
		$pillar_class2 = '';
		$pillar_class3 = '';

		if($pillar_id==1){
		   $pillar_class1 = 'active';
		   $year_heading = 'Choose Academic Year(AY)'; 
		} elseif($pillar_id==2) {
		   $pillar_class2 = 'active';
		   $year_heading = 'Compare By Academic Years(AY)'; 
		} elseif($pillar_id==3) {
		   $pillar_class3 = 'active';
		   $year_heading = 'Compare by Year(AY)'; 
		} else {
		   $year_heading = 'Choose Year'; 
		}

		$cmp_10	= '';
		$cmp_11	= '';
		$cmp_12	= '';

		$ch_cmp = arg(4);

		if(arg(4)) $cmp_12 = arg(4);
		
		if(arg(7)=='cmp' && arg(8)=='2010') $cmp_10 = arg(8);
		if(arg(7)=='cmp' && arg(8)=='2011') $cmp_11 = arg(8);

		if(arg(9)=='cmp' && arg(10)=='2010') $cmp_10 = arg(10);
		if(arg(9)=='cmp' && arg(10)=='2011') $cmp_11 = arg(10);

		// choose by year selection
		//if(arg(7)=='choose') $cmp_10 = arg(4);
		//if(arg(7)=='choose') $cmp_11 = arg(4);
		if(arg(7)=='choose') $cmp_12 = '2012';

		if(arg(7)=='cmp') $ch_cmp = '';

		$defIndex = 0;
		if(arg(6)) $defIndex = 1;
		if(arg(7)) $defIndex = 3;
		if(arg(7)=='choose') $defIndex = 2;

		$en_gr = (arg(6)) ? arg(6) : '';

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<input type='hidden' id='en-gr' value='$en_gr'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>DASHBOARDS</h3>
			<div>
				".l('Labor Supply From Higher Education', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('What Program To Enroll (Oversubscribed And Undersubscribed)', 'infographics/ched-higher-education/d2/1/2012/2013', array('attributes' => array('class' => array('active') )) )."
				".l('Higher Education Licensure Performance', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array('') )) )."
		</div>
			<h3 class='left-ui-accordion-header'>Choose Pillar</h3>
			<div>
				".l('Totals By Discipline', 'infographics/ched-higher-education/d2/1/2012/2013/enrollment', array('attributes' => array('class' => array($pillar_class1))) )."
				".l('Oversubscribed Programs', 'infographics/ched-higher-education/d2/2/2012/2013/enrollment', array('attributes' => array('class' => array($pillar_class2))) )."
				".l('Undersubscribed Programs', 'infographics/ched-higher-education/d2/3/2012/2013/enrollment', array('attributes' => array('class' => array($pillar_class3))) )."
			</div>
                        <h3 class='left-ui-accordion-header'>Choose Academic Year(AY)</h3>
			<div>
			<form class='custom dash2pill2choose'>
				<label for='total_q1' class='blue'><input type='checkbox' name='total' ><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;AY 2010/11</label>
				<label for='total_q1' class='yello'><input type='checkbox' name='total' ><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2011/12</label>
				<label for='total_q1' class='green'><input type='checkbox' name='total' ><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2012/13</label>				
			</form>
			</div>
			<h3 class='left-ui-accordion-header'>".$year_heading."</h3>
			<div>
			<form class='custom dash2pill2'>
				<label for='total_q1' class='blue'><input type='checkbox' name='total' ><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;AY 2010/11</label>
				<label for='total_q1' class='yello'><input type='checkbox' name='total'><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2011/12</label>
				<label for='total_q1' class='green'><input type='checkbox' name='total' ><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2012/13</label>				
			</form>
			</div>
		</div>
		";
		break;


		case '3':

		$pillar_class1 = '';
		$pillar_class2 = '';
		$pillar_class3 = '';

		if($pillar_id==1){
		   $pillar_class1 = 'active';
		   $year_heading = 'Choose Academic Year (AY)'; 
		} elseif($pillar_id==2) {
		   $pillar_class2 = 'active';
		   $year_heading = 'Compare By Academic Years'; 
		} elseif($pillar_id==3) {
		   $pillar_class3 = 'active';
		   $year_heading = 'Compare by Year'; 
		} else {
		   $year_heading = 'Choose Year'; 
		}

		$cmp_10	= '';
		$cmp_11	= '';
		$cmp_12	= '';

		$ch_cmp = arg(4);

		if(arg(4)) $cmp_12 = arg(4);
		
		if(arg(7)=='cmp' && arg(8)=='2010') $cmp_10 = arg(8);
		if(arg(7)=='cmp' && arg(8)=='2011') $cmp_11 = arg(8);

		if(arg(9)=='cmp' && arg(10)=='2010') $cmp_10 = arg(10);
		if(arg(9)=='cmp' && arg(10)=='2011') $cmp_11 = arg(10);

		// choose by year selection
		//if(arg(7)=='choose') $cmp_10 = arg(4);
		//if(arg(7)=='choose') $cmp_11 = arg(4);		
		if(arg(7)=='choose') $cmp_12 = '2012';

		if(arg(7)=='cmp') $ch_cmp = '';

		$defIndex = 0;
		if(arg(6)) $defIndex = 1;
		if(arg(7)) $defIndex = 2;
		if(arg(7)=='choose') $defIndex = 3;

		$en_gr = (arg(6)) ? arg(6) : '';

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<input type='hidden' id='en-gr' value='$en_gr'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>DASHBOARDS</h3>
			<div>
				".l('Labor Supply From Higher Education', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('What Program To Enroll (Oversubscribed And Undersubscribed)', 'infographics/ched-higher-education/d2/1/2012/2013', array('attributes' => array('class' => array('active') )) )."
				".l('Higher Education Licensure Performance', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array('') )) )."
		</div>
			<h3 class='left-ui-accordion-header'>Choose Pillar</h3>
			<div>
				".l('Totals By Discipline', 'infographics/ched-higher-education/d2/1/2012/2013/enrollment', array('attributes' => array('class' => array($pillar_class1))) )."
				".l('Oversubscribed Programs', 'infographics/ched-higher-education/d2/2/2012/2013/enrollment', array('attributes' => array('class' => array($pillar_class2))) )."
				".l('Undersubscribed Programs', 'infographics/ched-higher-education/d2/3/2012/2013/enrollment', array('attributes' => array('class' => array($pillar_class3))) )."
			</div>
			<h3 class='left-ui-accordion-header'>".$year_heading."</h3>
			<div>
			<form class='custom dash2pill3'>
				<label for='total_q1' class='blue'><input type='checkbox' name='total' dash2-p3='2010' style='display: none;' ".((2010==$cmp_10) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;2010/11</label>
				<label for='total_q1' class='yello'><input type='checkbox' name='total' dash2-p3='2011' style='display: none;' ".((2011==$cmp_11) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;2011/12</label>
				<label for='total_q1' class='green'><input type='checkbox' name='total' dash2-p3='2012' style='display: none;' ".((2012==$cmp_12) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;2012/13</label>				
			</form>
			</div>
			<h3 class='left-ui-accordion-header'>Choose By Year</h3>
			<div>
			<form class='custom dash2pill3choose'>
				<label for='total_q1' class='blue'><input type='checkbox' name='total' dash2-p3='2010/2011' style='display: none;' ".((2010==$ch_cmp) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;2010/11</label>
				<label for='total_q1' class='yello'><input type='checkbox' name='total' dash2-p3='2011/2012' style='display: none;' ".((2011==$ch_cmp) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;2011/12</label>
				<label for='total_q1' class='green'><input type='checkbox' name='total' dash2-p3='2012/2013' style='display: none;' ".((2012==$ch_cmp) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;2012/13</label>				
			</form>
			</div>
		</div>
		";
	}

return $left_content;
}
