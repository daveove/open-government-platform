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
		$legend = "
		<div class='row legend'>
		     <div class='large-12 columns legend'>
		       <div class='legent-container'>
				<div class='legend-heading'>LEGEND</div>
				<p>The Higher Education is collecting data annually from all higher education institutions (HEIs) in the country. The collected data contains the HEI profile including their enrolment and graduate data per program. </p>
				<p>A program refers to a degree, which leads to a specific academic credential such as a bachelor�s degree, a master�s degree, or doctorate degree. (Source : The Revised Data Element  Manual � March 2005)</p>
				<p>A higher education institution (HEI) refers to an institution of higher learning that primarily offers degree programs classified as follows:</p>
				<p><b>State University/College (SU/SC) - </b> a chartered public higher education institution established by law, administered, and financially subsidized by the government.</p>
				<p><b>Supervised Institution (CSI) - </b> a non-chartered public post secondary education institution established by law, administered, supervised and financially supported by the government.</p>
				<p><b>Local University and College (LU/LC) - </b> a public higher education institution established by the local government through an appropriate resolution/ordinance and financially supported by the local government concerned.</p>
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
		case '2':
		case '3':

		if($pillar_id==1){
			$pillar_class = 'active';
			$year_heading = 'Compare By Academic Years (AY)'; 
		} else { 
			$pillar_class = '';
			$year_heading = 'Choose Academic Year(AY)'; 
		}

		$left_content = "
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>DASHBOARDS</h3>
			<div>
				<a href='' class='active'>Labor Supply From Higher Education</a>
				<a href=''>What Program To Enroll (Oversubscribed And Undersubscribed)</a>
				<a href=''>Higher Institutional Performance</a>
				<a href=''>State Universities And College Budget Data And Capacity</a>
			</div>
			<h3 class='left-ui-accordion-header'>Choose Pillar</h3>
			<div>
				".l('Distribution of Higher Education Institutions', 'infographics/ched-higher-education/1'.'/'.$year, array('attributes' => array('class' => array($pillar_class))) )."
				".l('Distribution of Higher Education Institutions By Region', 'infographics/ched-higher-education/2'.'/'.$year)."
				".l('Distribution of higher Education Enrollment by Sector and Region', 'infographics/ched-higher-education/3'.'/'.$year)."
			</div>
			<h3 class='left-ui-accordion-header'>".$year_heading."</h3>
			<div>
                            <form class='custom cd_year'>
                                <label for='cd_year1'><input type='checkbox' style='display: none;' id='cd_year1' disabled='disabled'><span class='custom checkbox'></span> AY 2010/11 <div class='blue'></div></label> 
                                <label for='cd_year2'><input type='checkbox' style='display: none;' id='cd_year2' disabled='disabled'><span class='custom checkbox'></span> AY 2011/12 <div class='yellow'></div></label>
                                <label for='cd_year3'><input type='checkbox' style='display: none;' id='cd_year3' disabled='disabled'><span class='custom checkbox'></span> AY 2012/13 <div class='green'></div></label>
                            </form>
			</div>
		</div>
		";
	}

return $left_content;
}