<?php

/**
* Build the commodity import infographics
* @param $year the reference year of the report)
* @param pillarId the pillar identifier, or <code>0</code> to get the average scores report for the specified agency
*/
function dof_trade_activity($pillar_id = 1, $year = '2013') {
drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
drupal_set_title('Infographics');

$modPath = drupal_get_path('module', 'dof_report');
drupal_add_js($modPath.'/js/dof_dashboard.js');

        $modPath = drupal_get_path('module', 'dgph_infographics');
        drupal_add_css($modPath.'/css/dgph_infographics_common.css');
        drupal_add_css($modPath.'/css/dgph_infographics_notices.css');
        //drupal_add_js($modPath.'/js/dgph_infographics_scripts.js');
        //drupal_add_js($modPath.'/js/dgph_infographics_notices.js');

	$code = '';
        switch($pillar_id) {
            case 1:             // Dashboard One Pillar	1
                $code .= dof_get_trade_activity($pillar_id, $year);
                break;
        }
        return $code;
}

/**
* Build the dashboard one pillar 1 report
* @param @year the report year
* @return the pillar 1 report
*/
function dof_get_trade_activity($pillar_id, $year) {

// gets link to dashboard data
$dashbUploadUri = '';
$dashbUploadUri = infographics_get_dashboard_datafile(DASHB_DOF, $year);
$dash_dof_download = '';
if (!empty($dashbUploadUri)) {    
    $dash_dof_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
}
$port = '/all';
if(arg(5)) $port = '/'.arg(5);

if(arg(4)){
   $month = arg(4);
} else {
   $month = 'January';
}

$def_class = 'active';
if(arg(6)){ $def_class = ''; }

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
			".dof_trade_activity_left_content($pillar_id, $year, $month)."
		      </div>

		      <div class='large-9 columns works'>
			  <div class='row dashboard-container-header'>
				<div class='large-9 columns container-ritle'>
				    <h2>Trade Activity Per Port</h2>
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
				    <div class='dof-dash1-pillar1-table'>
				    <h4 class='accord-heading'>Trade Activity Per Port</h4>
					<table cellpadding='0' cellspacing='0' border='0' width='100%'>
					<tr class='dash1-pillar1-table-header'>
					    <th class='first'>PORT</th>
					    <th class='cif'><a href='#' title='Cost of Goods, Insurance, and Freight' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'></a>".l('CIF VALUE (PHP)', 'infographics/trade-activity/1/'.$year.'/'.$month.$port.'/CIF', array('attributes' => array('class' => array('clickable-item', $def_class) )) )."<br />
					    ".l('VOLUME (Kg)', 'infographics/trade-activity/1/'.$year.'/'.$month.$port.'/VOLUME', array('attributes' => array('class' => array('clickable-item'))))."<br />
					    ".l('NO. OF IMPORT ENTRIES', 'infographics/trade-activity/1/'.$year.'/'.$month.$port.'/IMPORTENTRIES', array('attributes' => array('class' => array('clickable-item'))))."</th>
					    <th>% DISTRIBUTION OF<br /><br />CIF VALUE<br /><br />VOLUME<br /><br />NO. OF IMPORT ENTRIES</th>
					    <th>TOTAL DUTIES AND TAXES COLLECTED (PHP)</th>
					    <th>% DISTRIBUTION OF<br />TOTAL DUTIES AND TAXES<br />COLLECTED</th>
					</tr>
					".dof_collect_data_trade_activity($year, $month)."

					</table>
				    </div>
				</div>
			  </div>
				".dof_trade_activity_legend()."

		      </div>
		  </div>
		  <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>
		";

return $code;
}


   /**
    * Build the dashboard one pillar 1 report
    * @param @year the report year
    * @return the pillar 1 report
    */
    function dof_collect_data_trade_activity($year, $month) {

       $dash1_sql = "SELECT id, year, month, port, cif_value, distribution, volume, distribution1, total_duties_taxes_collected, distribution2, import_entries, share_total_import_entries
				FROM dof_dashb3_pillar1
				WHERE 
				year = $year
				";
       // Adding Month condition
       if($month && $month!='all'){
	   $dash1_sql.= " AND month = '".$month."'";
       }

       // Adding Month condition
       if(arg(5) && arg(5)!='all'){
	   $dash1_sql.= " AND port = '".arg(5)."'";
       }


       //$res = $query->execute();

       $res = db_query($dash1_sql);

       $port				= '';       
       $cif_value			= 0;
       $distribution			= 0;
       $volume				= 0;
       $distribution1			= 0;
       $total_duties_taxes_collected	= 0;
       $distribution2			= 0;
       $import_entries			= 0;
       $share_total_import_entries	= 0;

       $code = "
            <tr class='no-data-row'>
               <td colspan='5'><p><b>There is no data available for the selected criteria!</b></p></td>
            </tr>";
       foreach($res as $i=>$row) {
           if($i==0) $code = "";

	       $port				= ($row->port) ? $row->port: "--";
	       $cif_value			= ($row->cif_value) ? number_format($row->cif_value): "--";
	       $distribution			= ($row->distribution) ? number_format($row->distribution, 1): "--";
	       $volume				= ($row->volume) ? number_format($row->volume) : "--";
	       $distribution1			= ($row->distribution1) ? number_format($row->distribution1, 1): "--";
	       $total_duties_taxes_collected	= ($row->total_duties_taxes_collected) ? number_format($row->total_duties_taxes_collected): "--";
	       $distribution2			= ($row->distribution2) ? number_format($row->distribution2, 1): "--";
	       $import_entries			= ($row->import_entries) ? number_format(intval($row->import_entries)): "--";
	       $share_total_import_entries	= ($row->share_total_import_entries) ? number_format($row->share_total_import_entries, 1): "--";

       if(arg(6)){
	switch(arg(6)){
	    case 'CIF':
	    $cif_vol_imp      = $cif_value;
	    $distribution_all = $distribution;
	    break;
	    case 'VOLUME':
	    $cif_vol_imp = $volume;
	    $distribution_all = $distribution1;
	    break;
	    case 'IMPORTENTRIES':
	    $cif_vol_imp = $import_entries;
	    $distribution_all = $distribution2;
	    break;
	}
       } else {
       	    $cif_vol_imp = $cif_value;
	    $distribution_all = $distribution;
       }
	       

                $code.= "
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'>".$port."</td>
		    <td class='numeric_val col2'>".$cif_vol_imp."</td>
		    <td class='numeric_val col3'>".$distribution_all."</td>
		    <td class='numeric_val col4'>".$total_duties_taxes_collected."</td>
		    <td class='numeric_val col5'>".$share_total_import_entries."</td>
		  </tr>";

       }
       
       return $code;
    }





