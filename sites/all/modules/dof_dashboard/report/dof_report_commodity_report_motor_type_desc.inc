<?php


/**
* Manage legend for dof dashboard pillar 2.2
* @param $pillar_id the pillar identifier
*/
function dof_commodity_report_motor_type_legend(){

	$legend = "
		<div class='row legend'>
		     <div class='large-12 columns legend'>
		       <div class='legent-container'>
			    <div class='legend-heading'>LEGEND</div>
				<p><strong>Motor vehicle imports: Top motor vehicle imports sorted by type</strong></p>
				<p>This section contains a list of top types of motor vehicle imports (i.e. imports with HS codes 8701 to 8716) based on CIF value imported sorted by type of HS code. Other information such as HS code, volume imported, number of import entries processed, and customs duty collected are also indicated. Only motor vehicle imports processed in BOC main district ports are covered.</p>
				<p>Data is extracted from the BOC Electronic-to-Mobile (E2M) database and hence, does not include manual assessments.</p>
				<p><strong>HS Code</strong> - According to the Trade Atlas, it is a standardized numerical method of classifying traded products developed and maintained by the World Customs Organization. It can be defined as the “identification number” of all products in customs procedures.<br><br>Click <a href='http://www.dof.gov.ph/customsngbayan/?page_id=8051' target='_blank'>here</a> to see technical definitions of these HS codes, as the ones presented in this dashboard are simplified descriptions.</p>
				<p><strong>CIF value</strong> - total cost of goods, insurance, and freight of the imported motor vehicle</p>
				<p><strong>Volume</strong> - Gross weight of the imported motor vehicle</p>
				<p><strong>No. of import entries</strong> - Total number of motor vehicle import transactions</p>
				<p><strong>CUD collected</strong> - Customs duty levied on motor vehicle imports entering the BOC main district ports; derived by multiplying the dutiable value with duty rate and converted to peso value (using the applicable foreign exchange rate). Duty rate varies depending on the classification of goods under the 2012 ASEAN Harmonized Tariff Nomenclature (AHTN) and various Philippines Trade Agreements.</p>
			    </div>
		     </div>
		</div>
		";

return $legend;
}


/**
* Manage left content for dashboard one.
* @param $pillar_id the pillar identifier
*/
function dof_commodity_report_motor_type_left_content($pillar_id, $year, $month){
$left_content = '';
	switch($pillar_id){
		case '1':

		$short = '';

		$defIndex = 0;
		if(arg(4)) $defIndex = 1;		
		if(arg(5)) $short = '/'.arg(5);

		$def_class = (arg(4)) ? '' : 'active';

		$month	   = (arg(4)) ? arg(4) : '';
		$order     = (arg(5)) ? arg(5) : '';

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<input type='hidden' id='month' value='$month'>
		<input type='hidden' id='order' value='$order'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>CATEGORY</h3>
			<div>
				".l('Commodity Imports', 'infographics/commodity-import', array('attributes' => array('class' => array('') )) )."


			</div>	
			<h3 class='left-ui-accordion-header'>VIEW BY MONTH</h3>
			<div>
				".l('All Month', 'infographics/commodity-report-motor-by-type/1/'.$year.'/all'.$short)."
				".l('January', 'infographics/commodity-report-motor-by-type/1/'.$year.'/January'.$short, array('attributes' => array('class' => array($def_class))) )."
				".l('February', 'infographics/commodity-report-motor-by-type/1/'.$year.'/February'.$short)."
				".l('March', 'infographics/commodity-report-motor-by-type/1/'.$year.'/March'.$short)."
				".l('April', 'infographics/commodity-report-motor-by-type/1/'.$year.'/April'.$short)."
				".l('May', 'infographics/commodity-report-motor-by-type/1/'.$year.'/May'.$short)."
				".l('June', 'infographics/commodity-report-motor-by-type/1/'.$year.'/June'.$short)."
				".l('July', 'infographics/commodity-report-motor-by-type/1/'.$year.'/July'.$short)."
				".l('August', 'infographics/commodity-report-motor-by-type/1/'.$year.'/August'.$short)."
				".l('September', 'infographics/commodity-report-motor-by-type/1/'.$year.'/September'.$short)."
				".l('October', 'infographics/commodity-report-motor-by-type/1/'.$year.'/October'.$short)."
				".l('November', 'infographics/commodity-report-motor-by-type/1/'.$year.'/November'.$short)."
				".l('December', 'infographics/commodity-report-motor-by-type/1/'.$year.'/December'.$short)."
			</div>

		</div>
		";
		break;


	}

return $left_content;
}



