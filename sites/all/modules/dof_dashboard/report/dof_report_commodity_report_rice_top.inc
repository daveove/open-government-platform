<?php

/**
* Build the commodity import infographics
* @param $year the reference year of the report)
* @param pillarId the pillar identifier, or <code>0</code> to get the average scores report for the specified agency
*/
function dof_commodity_report_rice_top($pillar_id = 1, $year = '2013') {
drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
drupal_set_title('Infographics');

$modPath = drupal_get_path('module', 'dof_report');
drupal_add_js($modPath.'/js/dof_dashboard.js');

        $modPath = drupal_get_path('module', 'dgph_infographics');
        drupal_add_css($modPath.'/css/dgph_infographics_common.css');
        drupal_add_css($modPath.'/css/dgph_infographics_notices.css');

	$code = '';
        switch($pillar_id) {
            case 1:             // Dashboard two Pillar	1.2
                $code .= dof_get_commodity_report_rice_top($pillar_id, $year);
                break;
        }
        return $code;
}

/**
* Build the dashboard two pillar 2.2 report
* @param @year the report year
* @return the pillar 1 report
*/
function dof_get_commodity_report_rice_top($pillar_id, $year) {

// gets link to dashboard data
$dashbUploadUri = '';
$dashbUploadUri = infographics_get_dashboard_datafile(DASHB_DOF, $year);
$dash_dof_download = '';
if (!empty($dashbUploadUri)) {
    $dash_dof_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
}
$port = 'all';
if(arg(5)) $port = arg(5);

if(arg(4)){
   $month = arg(4);
} else {
   $month = 'January';
}

	$code  = '';
	$code .= "<div class='row dashboard-header'>
		      <div class='large-6 columns sub-heading'>
		         <h3>Customs Dashboard</h3>
			 <div class='description'>".dof_dashboard_description()."
                                                          
                         </div>
		      </div>
		      <div class='large-6 columns'>
			 <div class='year-con'>
			    <div class='year'><a href='#' data-dropdown='#select-year'><span>$year</span></a></div>
			    <span id='selected-year' style='display:none;'>$year</span>
			    <div id='select-year' class='dropdown dropdown-tip dropdown-relative'>
				<ul class='dropdown-menu'>
                                    <li><a href='javascript:void(0)' class='year-ref'>2013</a></li>
                                    <li><a href='javascript:void(0)' class='year-ref'>2012</a></li>
                                    <li><a href='javascript:void(0)' class='year-ref'>2011</a></li>
                                    <li><a href='javascript:void(0)' class='year-ref'>2010</a></li>
				</ul>
			    </div>
			 </div>		         
		      </div>
		  </div>

		  <div class='row dashboard-content'>

		      <div class='large-3 columns leftsides datarequest choosePillar'>
			".dof_commodity_report_rice_top_left_content($pillar_id, $year, $month, $port)."
		      </div>

		      <div class='large-9 columns works'>
			  <div class='row dashboard-container-header'>
				<div class='large-9 columns container-ritle'>
				    <h2>Commodity Report</h2>
				</div>
				<div class='large-3 columns container-social'>
				    <ul class='social-icon apcpi-social-icon'>
					<li><a href='javascript:infographics_print()' class='has-tip print' title='Print'><img alt='' src='/sites/all/themes/dgph/images/icon-11.png'></a></li>
					".$dash_dof_download."
					<li><a class='a2a_dd' href='http://www.addtoany.com/share_save'><img alt='' src='/sites/all/themes/dgph/images/icon-20.png'></a></li>
				    </ul>
				</div>
			  </div>
		  
			  <div class='row dashboard-container'>
				<div class='large-12 columns'>
				    ".dof_collect_data_commodity_report_rice_top($year, $month, $port)."
				</div>
			  </div>
				".dof_commodity_report_rice_top_legend()."

		      </div>
		  </div>
		  <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>
		";

return $code;
}


   /**
    * Build the Brokers Importers data collection
    * @param @year the report year
    */
    function dof_collect_data_commodity_report_rice_top($year, $month, $port) {

       if(arg(6)){
	switch(arg(6)){
	    case 'CIF':
	    $order = 'cif_value';
	    break;
	    case 'VOLUME':
	    $order = 'volume';
	    break;
	    case 'CDP':
	    $order = 'cud_paid';
	    break;
	}
       } else {
	  $order = 'cif_value';
       }
	
	$result	= dof_get_data_commodity_report_rice_top($year, $month, $order, $port);

	return $result;
    }


   /**
    * Build the dashboard two pillar 1.2 report
    * @param @year the report year
    * @return the pillar 1 report
    */
    function dof_get_data_commodity_report_rice_top($year, $month, $order, $port) {

       $dash1_sql = "SELECT id, year, month, rank, port, importer, cif_value, volume, cud_paid, cud_as_of_cif_value
				FROM dof_dashb2_pillar1_2
				WHERE 
				year = $year
				";

       // Adding Month condition
       if($month && $month!='all'){
	   $dash1_sql.= " AND month = '".$month."'";
       }

       // Adding Month condition
       if($port && $port!='all'){
	   $dash1_sql.= " AND port = '".$port."'";
       }

       $dash1_sql.= " ORDER BY $order desc";

       //$res = $query->execute();

       $res = db_query($dash1_sql);

       $def_class = (arg(6)) ? '' : 'active';

       $no_data	  = 0;
       
       $code = "<div class='dof-dash1-pillar1-table'>
		<h4 class='accord-heading'>TOP RICE IMPORTERS</h4>
			<table cellpadding='0' cellspacing='0' border='0' width='100%'>
				<tr class='dash1-pillar1-table-header'>
					<th class='first'>RANK</th>
					<th><a href='javascript:void(0)' title='Cost of Goods, Insurance, and Freight' class='has-tip information-tip'><img src='/sites/all/themes/dgph/images/info.png'>CIF VALUE (PHP)</a></th>
					<th>VOLUME (Kg)</th>
					<th><a href='javascript:void(0)' title='Customs Duties' class='has-tip information-tip'><img src='/sites/all/themes/dgph/images/info.png'>CUD PAID (PHP)</a></th>					
					<th>CUSTOMS DUTY AS<br />% OF CIF VALUE</th>
				</tr>";

       foreach($res as $i=>$row) {
       $no_data++;

	       $rank			= ($row->rank) ? number_format($row->rank): "--";
	       $port			= ($row->port) ? $row->port: "--";
	       $importer		= ($row->importer) ? $row->importer: "--";
	       $cif_value 		= ($row->cif_value) ? number_format($row->cif_value): "--";
	       $volume 			= ($row->volume) ? number_format($row->volume): "--";
	       $cud_paid		= ($row->cud_paid) ? number_format($row->cud_paid): "--";
	       $cud_as_of_cif_value	= ($row->cud_as_of_cif_value) ? number_format((float)$row->cud_as_of_cif_value, 1, '.', '') : "--";
       
                $code.= "
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>
		    <td rowspan='2'><div class='rank-bigtxt'>".$rank."</div></td>
		    <td class='numeric_val dcel1'>".$cif_value."</td>
		    <td class='numeric_val dcel2'>".$volume."</td>
		    <td class='numeric_val dcel3'>".$cud_paid."</td>
		    <td class='numeric_val dce14'>".$cud_as_of_cif_value."</td>	    
		  </tr>
		  <tr class='description'>
		    <td colspan='4' class='dcel7'>".$importer."</td>
		  </tr>";

       }

               $code.= "
		  </table>
		</div>";


	if($no_data==0){
	       $code = "<div class='dof-dash1-pillar1-table'>
			<h4 class='accord-heading'>TOP RICE IMPORTERS</h4>
			<p><b>There is no data available for the selected criteria!</b></p>
			</div>";
	}
       
       return $code;
    }



