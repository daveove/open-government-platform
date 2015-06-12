<?php


/**
* Manage legend for dashboard one.
* @param $pillar_id the pillar identifier
*/
function dof_commodity_import_legend(){

	$legend = "
		<div class='row legend'>
		     <div class='large-12 columns legend'>
		       <div class='legent-container'>
			    <div class='legend-heading'>LEGEND</div>
				<p><strong>Top 20 Commodity Imports</strong></p>
				<p>This section contains lists of the top 20 commodity imports based on CIF value imported, volume imported, number of import entries processed, or total taxes and duties collected. The top commodities found in this dashboard only cover commodities as processed in BOC main district ports.</p>
				<p>Data is extracted from the BOC Electronic-to-Mobile (E2M) database and hence, does not include manual assessments.</p>
				<p><strong>HS Code (or the Harmonized System Commodity Code)</strong> - According to the Trade Atlas, it is a standardized numerical method of classifying traded products developed and maintained by the World Customs Organization. It can be defined as the 'identification number' of all products in customs procedures. <a href='#' target='_blank'>Click here</a> to see technical definitions of these HS codes, as the ones presented here are simplified descriptions.</p>
				<p><strong>CIF value</strong> - total cost of goods, insurance, and freight of the imported commodity</p>
				<p><strong>Volume</strong> - gross weight of the imported commodity</p>
				<p><strong>No. of import entries</strong> - total number of processed import transactions</p>
				<p><strong>Total duties and taxes collected</strong> - ad valorem taxes, excise taxes, VAT, fines and penalties, and customs duties (CUD) collected from the imported commodity</p>
				<p><strong>% distribution</strong> - commodity's CIF value, volume, total duties and taxes, or number of import entries for a certain month as a percentage of the total CIF value, volume, total duties and taxes, or number of import entries for all commodities for that month</p>
                                <p><i>Certain commodities and importers are collected or paid.</i></p>
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
function dof_one_left_content($pillar_id, $year){
$left_content = '';
	switch($pillar_id){
		case '1':

		$cat_path = '';

		$defIndex = 0;
		if(arg(4)) $defIndex = 1;
		if(arg(5)) $cat_path = '/'.arg(5);

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
				".l('Commodity Imports', 'infographics/commodity-import', array('attributes' => array('class' => array('active') )) )."

				".l('Brokers and Importers', 'infographics/brokers-importers', array('attributes' => array('class' => array('') )) )."

			</div>
			<h3 class='left-ui-accordion-header'>VIEW BY MONTH</h3>
			<div>				
				".l('January', 'infographics/commodity-import/1/'.$year.'/January'.$cat_path, array('attributes' => array('class' => array($def_class) )) )."
				".l('February', 'infographics/commodity-import/1/'.$year.'/February'.$cat_path)."
				".l('March', 'infographics/commodity-import/1/'.$year.'/March'.$cat_path)."
				".l('April', 'infographics/commodity-import/1/'.$year.'/April'.$cat_path)."
				".l('May', 'infographics/commodity-import/1/'.$year.'/May'.$cat_path)."
				".l('June', 'infographics/commodity-import/1/'.$year.'/June'.$cat_path)."
				".l('July', 'infographics/commodity-import/1/'.$year.'/July'.$cat_path)."
				".l('August', 'infographics/commodity-import/1/'.$year.'/August'.$cat_path)."
				".l('September', 'infographics/commodity-import/1/'.$year.'/September'.$cat_path)."
				".l('October', 'infographics/commodity-import/1/'.$year.'/October'.$cat_path)."
				".l('November', 'infographics/commodity-import/1/'.$year.'/November'.$cat_path)."
				".l('December', 'infographics/commodity-import/1/'.$year.'/December'.$cat_path)."
			</div>

		</div>
		";
		break;


	}

return $left_content;
}