<?php


/**
* Manage legend for dashboard one.
* @param $pillar_id the pillar identifier
*/
function dof_trade_activity_legend(){

	$legend = "
		<div class='row legend'>
		     <div class='large-12 columns legend'>
		       <div class='legent-container'>
			    <div class='legend-heading'>LEGEND</div>
				<p><strong>TRADE ACTIVITY PER PORT</strong></p>
				<p>This section shows the following information pertaining to imports processed in each of the BOC main district ports: CIF value imported, volume imported, number of import entries processed, and total duties and taxes collected.</p>
				<p>Data is extracted from the BOC Electronic-to-Mobile (E2M) database and hence, does not include manual assessments.</p>
				<p><strong>CIF value</strong> - total cost of goods, insurance, and freight of imports</p>
				<p><strong>Volume</strong> - gross weight of imports</p>
				<p><strong>No. of import entries</strong> - total number of processed import transactions</p>
				<p><strong>Total duties and taxes collected</strong> - ad valorem taxes, excise taxes, VAT, fines and penalties, and customs duties (CUD) collected from imports</p>
				<p><strong>% distribution</strong> - port's CIF value, volume, total duties and taxes, or number of import entries for a certain month as a percentage of the total CIF value, volume, total duties and taxes, or number of import entries for all BOC main district ports for that month</p>
                                <p><i>Certain commodities and importers are exempt from customs duties or paid.</i></p>
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
function dof_trade_activity_left_content($pillar_id, $year, $month){
$left_content = '';
	switch($pillar_id){
		case '1':

		$port = '';

		$defIndex = 0;
		if(arg(4)) $defIndex = 2;
		if(arg(5)) $defIndex = 1;

		if(arg(5)) $port = '/'.arg(5);
		if(arg(6)) $port.= '/'.arg(6);

		$def_class = (arg(4)) ? '' : 'active';

		$month	   = (arg(4)) ? arg(4) : '';
		$port_url  = (arg(5)) ? arg(5) : '';
		$order     = (arg(6)) ? arg(6) : '';

		$left_content = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<input type='hidden' id='month' value='$month'>
		<input type='hidden' id='port_url' value='$port_url'>
		<input type='hidden' id='order' value='$order'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
			<h3 class='left-ui-accordion-header'>CATEGORY</h3>
			<div>
				".l('Commodity Imports', 'infographics/commodity-import', array('attributes' => array('class' => array('') )) )."
				".l('Commodity Report', 'infographics/commodity-report-rice', array('attributes' => array('class' => array('') )) )."
				".l('Trade Activity Per Port', 'infographics/trade-activity', array('attributes' => array('class' => array('active') )) )."
				".l('Brokers and Importers', 'infographics/brokers-importers', array('attributes' => array('class' => array('') )) )."

			</div>
			<h3 class='left-ui-accordion-header'>VIEW BY PORT</h3>
			<div>	
				".collect_unique_port($year, $month)."
			</div>
			<h3 class='left-ui-accordion-header'>VIEW BY MONTH</h3>
			<div>
				".l('All Month', 'infographics/trade-activity/1/'.$year.'/all'.$port)."
				".l('January', 'infographics/trade-activity/1/'.$year.'/January'.$port, array('attributes' => array('class' => array($def_class) )) )."
				".l('February', 'infographics/trade-activity/1/'.$year.'/February'.$port)."
				".l('March', 'infographics/trade-activity/1/'.$year.'/March'.$port)."
				".l('April', 'infographics/trade-activity/1/'.$year.'/April'.$port)."
				".l('May', 'infographics/trade-activity/1/'.$year.'/May'.$port)."
				".l('June', 'infographics/trade-activity/1/'.$year.'/June'.$port)."
				".l('July', 'infographics/trade-activity/1/'.$year.'/July'.$port)."
				".l('August', 'infographics/trade-activity/1/'.$year.'/August'.$port)."
				".l('September', 'infographics/trade-activity/1/'.$year.'/September'.$port)."
				".l('October', 'infographics/trade-activity/1/'.$year.'/October'.$port)."
				".l('November', 'infographics/trade-activity/1/'.$year.'/November'.$port)."
				".l('December', 'infographics/trade-activity/1/'.$year.'/December'.$port)."
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
function collect_unique_port($year, $month){
       // gets averages for all agencies and pillars
       $query = db_select('dof_dashb3_pillar1', 'pillar1')
                        ->fields('pillar1', array('id', 'port'))

                    ->orderBy('pillar1.id');
		    
       $res = $query->execute();
       $port  = array();
       $type = '';
       if(arg(6)) $type = '/'.arg(6);

       $def_class = 'active';
       if(arg(4)){ $def_class = ''; }

       $result= l('All Ports', 'infographics/trade-activity/1/'.$year.'/'.$month.'/all'.$type, array('attributes' => array('class' => array($def_class) )) );
       foreach($res as $row) {
	   if(!in_array ($row->port, $port)) {
	      $port[] = $row->port;
	      $result.= l($row->port, 'infographics/trade-activity/1/'.$year.'/'.$month.'/'.$row->port.$type);
	   }
       }

       return $result;
}