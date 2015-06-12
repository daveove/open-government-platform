<?php

/**
* Build the commodity import infographics
* @param $year the reference year of the report)
* @param pillarId the pillar identifier, or <code>0</code> to get the average scores report for the specified agency
*/
function dof_commodity_report_rice($pillar_id = 1, $year = '2013') {
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
                $code .= dof_get_commodity_report_rice($pillar_id, $year);
                break;
        }
        return $code;
}

/**
* Build the dashboard one pillar 1 report
* @param @year the report year
* @return the pillar 1 report
*/
function dof_get_commodity_report_rice($pillar_id, $year) {

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
			".dof_commodity_report_rice_left_content($pillar_id, $year, $month, $port)."
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
				    ".dof_collect_data_commodity_report_rice($year, $month, $port)."
				</div>
			  </div>
				".dof_commodity_report_rice_legend()."

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
    function dof_collect_data_commodity_report_rice($year, $month, $port) {
	$result = '<p><b>There is no data available for the selected criteria!</b></p>';

	$result	= dof_get_data_commodity_report_rice($year, $month, $port);

	return $result;
    }


   /**
    * Build the dashboard one pillar 1 report
    * @param @year the report year
    * @return the pillar 1 report
    */
    function dof_get_data_commodity_report_rice($year, $month, $port) {

       $dash1_sql = "SELECT id, year, month, port, cif_value, distribution, volume, distribution1, cud_collected, distribution2, import_entries, distribution3
				FROM dof_dashb2_pillar1
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

       //$res = $query->execute();

       $res = db_query($dash1_sql);

       $def_class = (arg(6)) ? '' : 'active';

       $no_data				= 0;
       
       $arg6 = arg(6);
       $distCIF = (empty($arg6) || $arg6=='CIF') ? 'active' : '';
       $distVOL = ($arg6=='VOLUME') ? 'active' : '';
       $distENT = ($arg6=='IMPORTENTRIES') ? 'active' : '';
       
       $code = "<div class='dof-dash1-pillar1-table'>
		<h4 class='accord-heading'>RICE IMPORTS PER PORT</h4>
			<table cellpadding='0' cellspacing='0' border='0' width='100%'>
				<tr class='dash1-pillar1-table-header'>
					<th class='first'>PORT</th>
					<th><a href='#' title='Cost of Goods, Insurance, and Freight' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'></a>".l('CIF VALUE (PHP)', 'infographics/commodity-report-rice/1/'.$year.'/'.$month.'/'.$port.'/CIF', array('attributes' => array('class' => array('clickable-item', $def_class) )) )."<br />
					".l('VOLUME (Kg)', 'infographics/commodity-report-rice/1/'.$year.'/'.$month.'/'.$port.'/VOLUME', array('attributes' => array('class' => array('clickable-item') )))."<br />
					".l('NO. OF IMPORT ENTRIES', 'infographics/commodity-report-rice/1/'.$year.'/'.$month.'/'.$port.'/IMPORTENTRIES', array('attributes' => array('class' => array('clickable-item') )))."</th>
					<th>% DISTRIBUTION OF<br /><br /><span class='$distCIF'>CIF VALUE</span><br /><br /><span class='$distVOL'>VOLUME</span><br /><br /><span class='$distENT'>NO. OF IMPORT ENTRIES</span></th>
					<th><a href='#' title='Customs Duties' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'></a>CUD<br />COLLECTED (PHP)</th>
					<th><a href='#' title='Customs Duties' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'></a>% DISTRIBUTION<br />OF CUD COLLECTED</th>
				</tr>";

       foreach($res as $i=>$row) {
       $no_data++;

	       $cud_collected	= ($row->cud_collected=='-') || ($row->cud_collected=='0') ? "--" : number_format(floatval($row->cud_collected));
	       $distribution2	= ($row->distribution2=='-') || ($row->distribution2=='0') ? "--" : number_format((float)$row->distribution2, 1, '.', '');
	       
       if(arg(6)){
	switch(arg(6)){
	    case 'CIF':
	    $cif_vol_imp      = ($row->cif_value=='-') || ($row->cif_value=='0') ? "--" : number_format($row->cif_value);
	    $distribution_all = ($row->distribution=='-') || ($row->distribution=='0') ? "--" : number_format((float)$row->distribution, 1, '.', '');
	    break;
	    case 'VOLUME':
	    $cif_vol_imp      = ($row->volume=='-') || ($row->volume=='0') ? "--" : number_format($row->volume);
	    $distribution_all = ($row->distribution1=='-') || ($row->distribution1=='0') ? "--" : number_format((float)$row->distribution1, 1, '.', '');
	    break;
	    case 'IMPORTENTRIES':
	    $cif_vol_imp      = ($row->import_entries=='-') || ($row->import_entries=='0') ? "--" : number_format($row->import_entries);
	    $distribution_all = ($row->distribution3=='-') || ($row->distribution3=='0') ? "--" : number_format((float)$row->distribution3, 1, '.', '');
	    break;

	}

       } else {
	    $cif_vol_imp      = ($row->cif_value=='-') || ($row->cif_value=='0') ? "--" : number_format($row->cif_value);
	    $distribution_all = ($row->distribution=='-') || ($row->distribution=='0') ? "--" : number_format((float)$row->distribution, 1, '.', '');
       }

                $code.= "
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><b>".$row->port."</b></td>
		    <td class='numeric_val col2'>".$cif_vol_imp."</td>
		    <td class='numeric_val col3'>".$distribution_all."</td>
		    <td class='numeric_val col4'>".$cud_collected."</td>
		    <td class='numeric_val col5'>".$distribution2."</td>
		  </tr>";

       }

               $code.= "
		  </table>
		</div>";


	if($no_data==0){
	       $code = "<div class='dof-dash1-pillar1-table'>
			<h4 class='accord-heading'>RICE IMPORTS PER PORT</h4>
			<p><b>There is no data available for the selected criteria!</b></p>
			</div>";
	}
       
       return $code;
    }



