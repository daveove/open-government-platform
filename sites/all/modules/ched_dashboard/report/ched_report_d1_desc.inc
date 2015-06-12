<?php


/**
* Manage legend for dashboard one.
* @param $pillar_id the pillar identifier
*/
function dashboard_one_legend($pillar_id){
$legend = '';
	switch($pillar_id){
		case '1':
		case '2':
		case '3':
		case '4':
		$legend = "
		<div class='row legend'>
		     <div class='large-12 columns legend'>
		       <div class='legent-container'>
			    <div class='legend-heading'>LEGEND</div>
				<p>The Higher Education is collecting data annually from all higher education institutions (HEIs) in the country. The collected data contains the HEI profile including their enrolment and graduate data per program.</p>
				<p>A program refers to a degree, which leads to a specific academic credential such as a bachelor's degree, a master's degree, or doctorate degree. (Source : The Revised Data Element Manual - March 2005)</p>
				<p>A higher education institution (HEI) refers to an institution of higher learning that primarily offers degree programs classified as follows:</p>
				<p><b>State University/College (SUCs) - </b> State University/College (SUCs) - a chartered public higher education institution established by law, administered, and financially subsidized by the government.</p>
				<p><b>Supervised Institution (CSI) - </b> a non-chartered public post secondary education institution established by law, administered, supervised and financially supported by the government.</p>
				<p><b>Local University and College (LUCs) - </b> a public higher education institution established by the local government through an appropriate resolution/ordinance and financially supported by the local government concerned.</p>
				<p><b>Other Government School (OGS) - </b> any public secondary and post-secondary education institution, which is usually a technical-vocational education institution that offers higher education programs.</p>
				<p><b>Private Non-Sectarian (PN) - </b> any private higher education institution duly incorporated, owned and operated by private entities, which are not affiliated to any religious organization.</p>
				<p><b>Private Sectarian (PS) - </b> any private higher education institution, usually non-stock, non-profit, duly incorporated, owned and operated by a religious organization.</p>
				<p><b>Special Public HEI (SP) - </b> a category of public organizations offering higher education programs related to public service in pursuance of the basic mandates of their parent agencies and are operated and controlled in accordance with special laws that created them. They provide special academic, research and technical assistance programs, such as public/business management, internal security, military science and national defense.</p>
				<p><b>Discipline - </b> fields of study </p>
				<p>Enrollment data refers to the total number of students who register/enlist in a school year. (Source : 2006 Glossary of Commonly Used Terms in Education Statistics)</p>
				<p>Graduates data refers to the total number of students who have completed the requirements of a particular program. (Source : 2006 Glossary of Commonly Used Terms in Education Statistics)</p>
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
function dashboard_one_left_content($pillar_id, $year){
$left_content = '';
	switch($pillar_id){
		case '1':

		if($pillar_id==1){
			$pillar_class = 'active';
			$year_heading = 'Compare By Academic Years(AY)'; 
		} else { 
			$pillar_class = '';
			$year_heading = 'Choose Academic Year(AY)'; 
		}

		$cmp_10	= '';
		$cmp_11	= '';
		$cmp_12	= '';

		$ch_cmp = arg(4);

		if(arg(4)) $cmp_12 = arg(4);
		
		if(arg(6)=='cmp' && arg(7)=='2010') $cmp_10 = arg(7);
		if(arg(6)=='cmp' && arg(7)=='2011') $cmp_11 = arg(7);

		if(arg(8)=='cmp' && arg(9)=='2010') $cmp_10 = arg(9);
		if(arg(8)=='cmp' && arg(9)=='2011') $cmp_11 = arg(9);


		// choose by year selection
		//if(arg(6)=='choose') $cmp_10 = arg(4);
		//if(arg(6)=='choose') $cmp_11 = arg(4);
		if(arg(6)=='choose') $cmp_12 = '2012';

		if(arg(6)=='cmp') $ch_cmp = '';


		$defIndex = 0;
		if(arg(3)>1) $defIndex = 1;
		if(arg(6)) $defIndex = 3;
		if(arg(6)=='choose') $defIndex = 2;

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<input type='hidden' id='cmp' value='$cmp_10'>
		<input type='hidden' id='cmp1' value='$cmp_11'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>DASHBOARDS</h3>
			<div>
				".l('Labor Supply From Higher Education', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array('active') )) )."
				".l('What Program To Enroll (Oversubscribed And Undersubscribed)', 'infographics/ched-higher-education/d2/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('Higher Education Licensure Performance', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array('') )) )."


			</div>
			<h3 class='left-ui-accordion-header'>Choose Pillar</h3>
			<div>
				".l('Distribution of Higher Education Institutions', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array($pillar_class))) )."
				".l('Distribution of Higher Education Institutions By Region', 'infographics/ched-higher-education/d1/2/2012/2013')."
				".l('Distribution of higher Education Enrollment by Sector and Region', 'infographics/ched-higher-education/d1/3/2012/2013')."
				".l('Distribution of Higher Education Graduates By Sector and Region', 'infographics/ched-higher-education/d1/4/2012/2013')."
			</div>
                        <h3 class='left-ui-accordion-header'>Choose Academic Year(AY)</h3>
			<div>
			<form class='custom dash1pill1choose'>
				<label for='total_q1' class='blue'><input type='checkbox' name='total' dash1-p1='2010/2011' style='display: none;' ".((2010==$ch_cmp) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;AY 2010/11</label>
				<label for='total_q1' class='yello'><input type='checkbox' name='total' dash1-p1='2011/2012' style='display: none;' ".((2011==$ch_cmp) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2011/12</label>				
				<label for='total_q1' class='green'><input type='checkbox' name='total' dash1-p1='2012/2013' style='display: none;' ".((2012==$ch_cmp) ?  "checked='checked'" : "")."><span value='3' class='custom checkbox'></span>&nbsp;&nbsp;AY 2012/13</label>
			</form>
			</div>
			<h3 class='left-ui-accordion-header'>".$year_heading."</h3>
			<div>
			<form class='custom dash1pill1'>
				<label for='total_q1' class='blue'><input type='checkbox' name='total' dash1-p1='2010' value='2010' style='display: none;' ".((2010==$cmp_10) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;AY 2010/11</label>
				<label for='total_q1' class='yello'><input type='checkbox' name='total' dash1-p1='2011' value='2011' style='display: none;' ".((2011==$cmp_11) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2011/12</label>				
				<label for='total_q1' class='green'><input type='checkbox' name='total' dash1-p1='2012' value='2012' style='display: none;' ".((2012==$cmp_12) ?  "checked='checked'" : "")."><span value='3' class='custom checkbox'></span>&nbsp;&nbsp;AY 2012/13</label>
			</form>
			</div>
		</div>
		";
		break;

		case '2':
		if($pillar_id==1){
			$pillar_class = 'active';
			$year_heading = 'Compare By Academic Years(AY)'; 
		} else { 
			$pillar_class = '';
			$year_heading = 'Choose Academic Year(AY)'; 
		}

		$psc = '';
		if(arg(4)==2010) $psc	= 1;
		if(arg(4)==2011) $psc	= 2;
		if(arg(4)==2012) $psc	= 3;
		if(arg(4)) {
		   $defIndex = 2;
		} else {
		   $defIndex = 1;
		}

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>DASHBOARDS</h3>
			<div>
				".l('Labor Supply From Higher Education', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array('active') )) )."
				".l('What Program To Enroll (Oversubscribed And Undersubscribed)', 'infographics/ched-higher-education/d2/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('Higher Education Licensure Performance', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array('') )) )."


			</div>
			<h3 class='left-ui-accordion-header'>Choose Pillar</h3>
			<div>
				".l('Distribution of Higher Education Institutions', 'infographics/ched-higher-education/d1/1/2012/2013')."
				".l('Distribution of Higher Education Institutions By Region', 'infographics/ched-higher-education/d1/2/2012/2013', array('attributes' => array('class' => array('active'))) )."
				".l('Distribution of higher Education Enrollment by Sector and Region', 'infographics/ched-higher-education/d1/3/2012/2013')."
				".l('Distribution of Higher Education Graduates By Sector and Region', 'infographics/ched-higher-education/d1/4/2012/2013')."
			</div>
			<h3 class='left-ui-accordion-header'>".$year_heading."</h3>
			<div>
			<form class='custom dash1pill2'>
				<label for='total_q1'><input type='checkbox' name='total' dash1-p2='2010/2011' style='display: none;' ".((1==$psc) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;AY 2010/11</label>
				<label for='total_q1'><input type='checkbox' name='total' dash1-p2='2011/2012' style='display: none;' ".((2==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2011/12</label>
				<label for='total_q1'><input type='checkbox' name='total' dash1-p2='2012/2013' style='display: none;' ".((3==$psc) ?  "checked='checked'" : "")."><span value='3' class='custom checkbox'></span>&nbsp;&nbsp;AY 2012/13</label>
			</form>
			</div>
		</div>
		";
		break;

		case '3':

		if($pillar_id==1){
			$pillar_class = 'active';
			$year_heading = 'Compare By Academic Years(AY)'; 
		} else { 
			$pillar_class = '';
			$year_heading = 'Choose Academic Year(AY)'; 
		}

		$psc = '';
		if(arg(4)==2010) $psc	= 1;
		if(arg(4)==2011) $psc	= 2;
		if(arg(4)==2012) $psc	= 3;
		if(arg(4)) {
		   $defIndex = 2;
		} else {
		   $defIndex = 1;
		}

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>DASHBOARDS</h3>
			<div>
				".l('Labor Supply From Higher Education', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array('active') )) )."
				".l('What Program To Enroll (Oversubscribed And Undersubscribed)', 'infographics/ched-higher-education/d2/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('Higher Education Licensure Performance', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array('') )) )."


			</div>
			<h3 class='left-ui-accordion-header'>Choose Pillar</h3>
			<div>
				".l('Distribution of Higher Education Institutions', 'infographics/ched-higher-education/d1/1/2012/2013')."
				".l('Distribution of Higher Education Institutions By Region', 'infographics/ched-higher-education/d1/2/2012/2013')."
				".l('Distribution of higher Education Enrollment by Sector and Region', 'infographics/ched-higher-education/d1/3/2012/2013', array('attributes' => array('class' => array('active'))) )."
				".l('Distribution of Higher Education Graduates By Sector and Region', 'infographics/ched-higher-education/d1/4/2012/2013')."
			</div>
			<h3 class='left-ui-accordion-header'>".$year_heading."</h3>
			<div>
			<form class='custom dash1pill3'>
				<label for='total_q1' class='blue'><input type='checkbox' name='total' dash1-p3='2010/2011' style='display: none;' ".((1==$psc) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;AY 2010/11</label>
				<label for='total_q1' class='yello'><input type='checkbox' name='total' dash1-p3='2011/2012' style='display: none;' ".((2==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2011/12</label>
				<label for='total_q1' class='green'><input type='checkbox' name='total' dash1-p3='2012/2013' style='display: none;' ".((3==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2012/13</label>
			</form>
			</div>
		</div>
		";
		break;

		case '4':

		if($pillar_id==1){
			$pillar_class = 'active';
			$year_heading = 'Compare By Academic Years(AY)'; 
		} else { 
			$pillar_class = '';
			$year_heading = 'Choose Academic Year(AY)'; 
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
				".l('Labor Supply From Higher Education', 'infographics/ched-higher-education/d1/1/2012/2013', array('attributes' => array('class' => array('active') )) )."
				".l('What Program To Enroll (Oversubscribed And Undersubscribed)', 'infographics/ched-higher-education/d2/1/2012/2013', array('attributes' => array('class' => array('') )) )."
				".l('Higher Education Licensure Performance', 'infographics/ched-higher-education/d3/1/2012/2013', array('attributes' => array('class' => array('') )) )."


			</div>
			<h3 class='left-ui-accordion-header'>Choose Pillar</h3>
			<div>
				".l('Distribution of Higher Education Institutions', 'infographics/ched-higher-education/d1/1/2012/2013')."
				".l('Distribution of Higher Education Institutions By Region', 'infographics/ched-higher-education/d1/2/2012/2013')."
				".l('Distribution of higher Education Enrollment by Sector and Region', 'infographics/ched-higher-education/d1/3/2012/2013')."
				".l('Distribution of Higher Education Graduates By Sector and Region', 'infographics/ched-higher-education/d1/4/2012/2013', array('attributes' => array('class' => array('active'))) )."
			</div>
			<h3 class='left-ui-accordion-header'>".$year_heading."</h3>
			<div>
			<form class='custom dash1pill4'>
				<label for='total_q1' class='blue'><input type='checkbox' name='total' dash1-p4='2010/2011' style='display: none;' ".((1==$psc) ?  "checked='checked'" : "")."><span value='1' class='custom checkbox'></span>&nbsp;&nbsp;AY 2010/11</label>
				<label for='total_q1' class='yello'><input type='checkbox' name='total' dash1-p4='2011/2012' style='display: none;' ".((2==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2011/12</label>
				<label for='total_q1' class='green'><input type='checkbox' name='total' dash1-p4='2012/2013' style='display: none;' ".((3==$psc) ?  "checked='checked'" : "")."><span value='2' class='custom checkbox'></span>&nbsp;&nbsp;AY 2012/13</label>
			</form>
			</div>
		</div>
		";
		break;
	}

return $left_content;
}