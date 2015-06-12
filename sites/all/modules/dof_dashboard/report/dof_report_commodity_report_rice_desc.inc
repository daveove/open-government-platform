<?php


/**
* Manage legend for dashboard one.
* @param $pillar_id the pillar identifier
*/
function dof_commodity_report_rice_legend(){

	$legend = "
		<div class='row legend'>
		     <div class='large-12 columns legend'>
		       <div class='legent-container'>
			    <div class='legend-heading'>LEGEND</div>
				<p><strong>Rice Imports: Rice imports per port</strong></p>
				<p>This section shows the following information pertaining to rice imports (i.e. imports with HS Code 1006) processed in each of BOC main district ports: CIF value imported, volume imported, number of import entries processed, and customs duty collected.</p>
                                <p>Data is extracted from the BOC Electronic-to-Mobile (E2M) database and hence, does not include manual assessments.</p>
				<p><strong>CIF value</strong> - total cost of goods, insurance, and freight of the imported rice</p>
				<p><strong>Volume</strong> - gross weight of the imported rice</p>
				<p><strong>No. of import entries</strong> - total number of rice import transactions processed</p>
				<p><strong>Volume</strong> - gross weight of the imported rice</p>
				<p><strong>CUD collected</strong> - Customs duty levied on rice imports entering the BOC main district ports; derived by multiplying the dutiable value with duty rate and converted to peso value (using the applicable foreign exchange rate). Duty rate varies depending on the classification of goods under the 2012 ASEAN Harmonized Tariff Nomenclature (AHTN) and various Philippines Trade Agreements.</p>
                                <p><strong>%  distribution</strong> - the port's CIF value, volume, total duties and taxes, or no. of import entries for a certain month as a percentage of the total CIF value, volume, total duties and taxes, or no. of import entries for all BOC main district ports for that month</p>
                                <p>A blank entry means no rice imports were processed in that port for that month.</p>
                                <p><i>Certain commodities and importers are exempt from customs duties customs duties collected or paid.</i></p>
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
function dof_commodity_report_rice_left_content($pillar_id, $year, $month, $port2){
$left_content = '';
	switch($pillar_id){
		case '1':

		$port  = '';
		$short = '';

		$defIndex = 0;
		if(arg(4)) $defIndex = 2;
		if(arg(5)) $defIndex = 1;
		if(arg(5)) $port  = '/'.arg(5);
		if(arg(6)) $short = '/'.arg(6);

		$def_class = (arg(4)) ? '' : 'active';

		$month1	   = (arg(4)) ? arg(4) : '';
		$port_url  = (arg(5)) ? arg(5) : '';
		$order     = (arg(6)) ? arg(6) : '';

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<input type='hidden' id='month' value='$month1'>
		<input type='hidden' id='port_url' value='$port_url'>
		<input type='hidden' id='order' value='$order'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>CATEGORY</h3>
			<div>
				".l('Commodity Imports', 'infographics/commodity-import', array('attributes' => array('class' => array('') )) )."


			</div>
			<h3 class='left-ui-accordion-header'>VIEW BY PORT</h3>
			<div>	
				".collect_unique_port_commodity_report_rice($year, $month, $short)."
			</div>
			<h3 class='left-ui-accordion-header'>VIEW BY MONTH</h3>
			<div>
				".l('All Month', 'infographics/commodity-report-rice/1/'.$year.'/all'.$port.$short)."
				".l('January', 'infographics/commodity-report-rice/1/'.$year.'/January'.$port.$short, array('attributes' => array('class' => array($def_class) )) )."
				".l('February', 'infographics/commodity-report-rice/1/'.$year.'/February'.$port.$short)."
				".l('March', 'infographics/commodity-report-rice/1/'.$year.'/March'.$port.$short)."
				".l('April', 'infographics/commodity-report-rice/1/'.$year.'/April'.$port.$short)."
				".l('May', 'infographics/commodity-report-rice/1/'.$year.'/May'.$port.$short)."
				".l('June', 'infographics/commodity-report-rice/1/'.$year.'/June'.$port.$short)."
				".l('July', 'infographics/commodity-report-rice/1/'.$year.'/July'.$port.$short)."
				".l('August', 'infographics/commodity-report-rice/1/'.$year.'/August'.$port.$short)."
				".l('September', 'infographics/commodity-report-rice/1/'.$year.'/September'.$port.$short)."
				".l('October', 'infographics/commodity-report-rice/1/'.$year.'/October'.$port.$short)."
				".l('November', 'infographics/commodity-report-rice/1/'.$year.'/November'.$port.$short)."
				".l('December', 'infographics/commodity-report-rice/1/'.$year.'/December'.$port.$short)."
			</div>

		</div>
		";
		break;


	}

return $left_content;
}



/**
* Collect unique port for according menu
*/
function collect_unique_port_commodity_report_rice($year, $month, $short){
       // gets averages for all agencies and pillars
       $query = db_select('dof_dashb2_pillar1', 'pillar1')
                        ->fields('pillar1', array('id', 'port'))

                    ->orderBy('pillar1.id');
		    
       $res = $query->execute();
       $port  = array();

       $def_class = 'active';
       if(arg(5)){ $def_class = ''; }

       $result= l('All Ports', 'infographics/commodity-report-rice/1/'.$year.'/'.$month.'/all'.$short, array('attributes' => array('class' => array($def_class) )));
       foreach($res as $row) {
	   if(!in_array ($row->port, $port)) {
	      $port[] = $row->port;
	      $result.= l($row->port, 'infographics/commodity-report-rice/1/'.$year.'/'.$month.'/'.$row->port.$short);
	   }
       }

       return $result;
}