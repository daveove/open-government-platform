<?php

/**
* Build the commodity import infographics
* @param $year the reference year of the report)
* @param pillarId the pillar identifier, or <code>0</code> to get the average scores report for the specified agency
*/
function dof_commodity_report_motor_importers($pillar_id = 1, $year = '2013') {
    drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
    drupal_set_title('Infographics');

    $modPath = drupal_get_path('module', 'dof_report');
    drupal_add_js($modPath.'/js/dof_dashboard.js');

    $modPath = drupal_get_path('module', 'dgph_infographics');
    drupal_add_css($modPath.'/css/dgph_infographics_common.css');
    drupal_add_css($modPath.'/css/dgph_infographics_notices.css');

    $code = '';
    switch($pillar_id) {
        case 1:             // Dashboard two Pillar	2.3
            $code .= dof_get_commodity_report_motor_importers($pillar_id, $year);
            break;
    }
    return $code;
}

/**
* Build the dashboard two pillar 2.3 report
* @param @year the report year
* @return the pillar 1 report
*/
function dof_get_commodity_report_motor_importers($pillar_id, $year) {

// gets link to dashboard data
$dashbUploadUri = '';
$dashbUploadUri = infographics_get_dashboard_datafile(DASHB_DOF, $year);
$dash_dof_download = '';
if (!empty($dashbUploadUri)) {
    $dash_dof_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
}

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
			".dof_commodity_report_motor_importers_left_content($pillar_id, $year, $month)."
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
					<li><a><img alt='' src='/sites/all/themes/dgph/images/icon-20.png'></a></li>
				    </ul>
				</div>
			  </div>
		  
			  <div class='row dashboard-container'>
				<div class='large-12 columns'>
				    ".dof_collect_data_commodity_report_motor_importers($year, $month)."
				</div>
			  </div>
				".dof_commodity_report_motor_importers_legend()."

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
    function dof_collect_data_commodity_report_motor_importers($year, $month) {

       if(arg(5)){
	switch(arg(5)){
	    case 'CIF':
	    $order = 'cif_value';
	    break;
	    case 'VOLUME':
	    $order = 'volume';
	    break;
	    case 'TCP':
	    $order = 'cud_paid';
	    break;
	}
       } else {
	  $order = 'cif_value';
       }

	$result	= "<div id='motor-importers-heading'><h2>TOP MOTOR VEHICLE IMPORTERS</h2></div>";
        $result.= "<div id='dofaccording'>";

        $hs_code_sql   = "SELECT DISTINCT (hs_code_description) as hs_code FROM dof_dashb2_pillar2_3";
        $hs_code_query = db_query($hs_code_sql);

	foreach($hs_code_query as $i=>$hs_code) {
	     $idx = ($i+1);
	     $result.= dof_get_data_commodity_report_motor_importers($year, $month, $order, $hs_code->hs_code, $idx);
	}

	$result.= "</div>";

	return $result;
    }


   /**
    * Build the dashboard one pillar 1 report
    * @param @year the report year
    * @return the pillar 1 report
    */
    function dof_get_data_commodity_report_motor_importers($year, $month, $order, $hs_code, $idx) {
        $dash1_sql = "SELECT id, year, month, rank, hs_code_description, importer, cif_value, volume, cud_paid
                        FROM dof_dashb2_pillar2_3 WHERE year = $year AND hs_code_description = '$hs_code'";
        if($month && $month!='all'){
            $dash1_sql.= " AND month = '".$month."'";
        }
        //$dash1_sql.= " ORDER BY $order";
        $res = db_query($dash1_sql);

        $def_class = (arg(5)) ? '' : 'active';

        $no_data				= 0;
        $modPath = drupal_get_path('module', 'dof_report');
        $hcodeEnd = strpos($hs_code, "-");
        $hcode = intval(trim(substr($hs_code, 0, $hcodeEnd)));
        $hname = trim(substr($hs_code, $hcodeEnd+1));
        $hdescr = "<img id='mv$hcode' src='/$modPath/images/mv$hcode.png'><div class='hs-description'>$hname</div>";
        $code = "<h3>$hdescr</h3>
                 <div>
                      <div class='dof-dash1-pillar1-table'>
                         <table cellpadding='0' cellspacing='0' border='0' width='100%'>
                                 <tr class='dash1-pillar1-table-header'>
                                         <th class='first'>RANK</th>
                                         <th>TYPE OF VEHICLE</th>                                        
                                         <th>VOLUME (Kg)</th>
                                         <th><a href='javascript:void(0)' title='Cost of Goods, Insurance, and Freight' class='has-tip information-tip'><img src='/sites/all/themes/dgph/images/info.png'>CIF VALUE (PHP)</a></th>				
                                         <th><a href='javascript:void(0)' title='Customs Duties' class='has-tip information-tip'><img src='/sites/all/themes/dgph/images/info.png'>TOTAL CUD PAID (PHP)</a></th>
                                 </tr>";

        foreach($res as $i=>$row) {
        $no_data++;

                $rank			= ($row->rank) ? number_format($row->rank): "--";
                $hs_code_description	= ($row->hs_code_description) ? $row->hs_code_description: "--";
                $importer		= ($row->importer) ? $row->importer: "--";
                $cif_value		= ($row->cif_value) ? number_format($row->cif_value): "--";
                $volume			= ($row->volume) ? number_format($row->volume): "--";
                $cud_paid		= ($row->cud_paid=='-') ? "--" : number_format($row->cud_paid);

                 $code.= "
                   <tr class='blank-row'>
                     <td colspan='5'></td>
                   </tr>
                   <tr class='data-row'>
                     <td rowspan='2'><div class='rank-bigtxt'>".$rank."</div></td>
                     <td class='numeric_val dcel1'>Type</td>
                     <td class='numeric_val dcel2'>".$volume."</td>
                     <td class='numeric_val dcel3'>".$cif_value."</td>
                     <td class='numeric_val dce14'>".$cud_paid."</td>
                   </tr>
                   <tr class='description'>
                     <td colspan='4' class='dcel7'>".$importer."</td>
                   </tr>";

        }

                $code.= "
                   </table>
                 </div>
                 </div>";


         if($no_data==0){
                $code = "<h3>".$hs_code."</h3>
                         <div>
                             <div class='dof-dash1-pillar1-table'>
                                 <p><b>There is no data available for the selected criteria!</b></p>
                             <div>
                         </div>";
         }

        return $code;
    }



