<?php


/**
* Manage legend for dashboard one.
* @param $pillar_id the pillar identifier
*/
function dof_brokers_importers_legend(){

	$legend = "
		<div class='row legend'>
		     <div class='large-12 columns legend'>
		       <div class='legent-container'>
			    <div class='legend-heading'>LEGEND</div>
                                <p><strong>Top Brokers</strong></p>
				<p>This section contains a list of the top 50 Customs brokers based on the CIF value imported under their authority. Only imports processed in BOC main district ports are covered.</p>
				<p>Data is extracted from the BOC Electronic-to-Mobile (E2M) database and hence, does not include manual assessments.</p>
				<p><strong>Broker</strong> - an agent authorized to transact business with the BOC in the name of the importing party</p>
				<p><strong>CIF value</strong> - total cost of goods, insurance, and freight of commodities imported under the broker's authority</p>
				<p><strong>Volume</strong> - Gross weight of commodities imported under the broker's authority</p>
				<p><strong>CUD paid</strong> - Customs duty on the importers brokered by these brokers. Customs duty is levied on goods entering the country, and is derived by multiplying the dutiable value with duty rate and converted to peso value (using the applicable foreign exchange rate). Duty rate varies depending on the classification of goods under the 2012 ASEAN Harmonized Tariff Nomenclature (AHTN) and various Philippines Trade Agreements.</p>
                                <p><strong>Top Importers</strong></p>
				<p>This section contains lists of the top 50 importers based on CIF value imported. Only imports processed in BOC main district ports are covered.</p>
				<p>Data is extracted from the BOC Electronic-to-Mobile (E2M) database and hence, does not include manual assessments.</p>
				<p><strong>Importer</strong> - The party who makes the import declaration</p>
				<p><strong>CIF value</strong> - total cost of goods, insurance, and freight of commodities imported by the importer</p>
				<p><strong>Volume</strong> - Gross weight of commodities imported by the importer</p>
				<p><strong>CUD paid</strong> - Customs duty on the imported goods as paid by the importer. Customs duty is levied on goods entering the country, and is derived by multiplying the dutiable value with duty rate and converted to peso value (using the applicable foreign exchange rate).</p>
                                <p><i>Certain commodities and importers are exempt from customs duties, as specified. Hence, some commodities and importers may have 0 corresponding customs duties collected or paid.</i></p>
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
function dof_brokers_importers_left_content($pillar_id, $year){
$left_content = '';
	switch($pillar_id){
		case '1':

		$defIndex = 0;
		if(arg(4)) $defIndex = 1;

		$group = (arg(4)) ? arg(4) : '';
		$short = (arg(5)) ? arg(5) : '';

		$def_class = (arg(4)) ? '' : 'active';

		$short_l   = (arg(5)) ? '/'.arg(5) : '/CIF';

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<input type='hidden' id='group' value='$group'>
		<input type='hidden' id='short' value='$short'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>CATEGORY</h3>
			<div>
				".l('Commodity Imports', 'infographics/commodity-import', array('attributes' => array('class' => array('') )) )."
				".l('Commodity Report', 'infographics/', array('attributes' => array('class' => array('') )) )."
				

			</div>
			<h3 class='left-ui-accordion-header'>VIEW BY GROUP</h3>
			<div>
				".l('All Group', 'infographics/brokers-importers/1/'.$year.'/all'.$short_l, array('attributes' => array('class' => array($def_class) )) )."
				".l('Brokers', 'infographics/brokers-importers/1/'.$year.'/brokers'.$short_l)."
				".l('Importers', 'infographics/brokers-importers/1/'.$year.'/importers'.$short_l)."
			</div>

		</div>
		";
		break;


	}

return $left_content;
}


