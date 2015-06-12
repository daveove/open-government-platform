<?php

/**
* Build the commodity import infographics
* @param $year the reference year of the report)
* @param pillarId the pillar identifier, or <code>0</code> to get the average scores report for the specified agency
*/
function dof_commodity_import($pillar_id = 1, $year = '2013') {
drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
drupal_set_title('Infographics');

$modPath = drupal_get_path('module', 'dof_report');
drupal_add_js($modPath.'/js/dof_dashboard.js');

        $modPath = drupal_get_path('module', 'dgph_infographics');
        drupal_add_css($modPath.'/css/dgph_infographics_common.css');
        drupal_add_css($modPath.'/css/dgph_infographics_notices.css');
	$code = '';
        switch($pillar_id) {
            case 1:             // Dashboard One Pillar	1
                $code .= dof_get_dashb1_pillar1($pillar_id, $year);
                break;
        }
        return $code;
}

/**
* Build the dashboard one pillar 1 report
* @param @year the report year
* @return the pillar 1 report
*/
function dof_get_dashb1_pillar1($pillar_id, $year) {

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

$def_class = 'active';
if(arg(5)){
$def_class = '';
   switch(arg(5)){
	case 'CIF':
	$category = 'CIF value';
	break;
	case 'VOLUME':
	$category = 'Volume';
	break;
	case 'TDTC':
	$category = 'Total duties and taxes collected';
	break;
	case 'IMPORTENTRIES':
	$category = 'Import Entries';
	break;
	default:
	$category = '';
	break;
   }
   
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
			".dof_one_left_content($pillar_id, $year)."
		      </div>

		      <div class='large-9 columns works'>
			  <div class='row dashboard-container-header'>
				<div class='large-9 columns container-ritle'>
				    <h2>Commodity Imports</h2>
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
				    <h4 class='accord-heading'>Top 20 Commodity Imports</h4>
					<table cellpadding='0' cellspacing='0' border='0' width='100%'>
					<tr class='dash1-pillar1-table-header'>
					    <th class='first'>RANK</th>
					    <th><a href='javascript:void(0)' title='Harmonized System Commodity Code' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'></a><span>HS CODE</span></th>
					    <th><a href='javascript:void(0)' title='Cost of Goods, Insurance, and Freight' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'></a>".l('CIF VALUE', 'infographics/commodity-import/1/'.$year.'/'.$month.'/CIF', array('attributes' => array('class' => array($def_class) )) )."</th>
					    <th>".l('VOLUME (Kg)', 'infographics/commodity-import/1/'.$year.'/'.$month.'/VOLUME')."</th>
					    <th>".l('TOTAL DUTIES AND TAXES COLLECTED', 'infographics/commodity-import/1/'.$year.'/'.$month.'/TDTC')."</th>
					    <th>".l('NO. OF IMPORT ENTRIES', 'infographics/commodity-import/1/'.$year.'/'.$month.'/IMPORTENTRIES')."</th>
					    <th>TOTAL COLLECTION AS % OF CIF VALUE</th>
					</tr>
					".dof_collect_data_dashb1_pillar1($year, $month, $category)."

					</table>
				    </div>
				</div>
			  </div>
				".dof_commodity_import_legend()."

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
    function dof_collect_data_dashb1_pillar1($year, $month, $category) {

       $dash1_sql = "SELECT id, year, month, rank, port, category, hs_code, description, cif_value, volume, import_entries, total_duties_taxes_collected, collection_cif_value
				FROM dof_dashb1_pillar1
				WHERE 
				year = $year
				";
       // Adding Month condition
       if($month){
	   $dash1_sql.= " AND month = '".$month."'";
       }

       // Adding Category condition
       if($category){
	switch($category){
	    case 'CIF':
	    $category = 'CIF value';
	    break;
	    case 'VOLUME':
	    $category = 'Volume';
	    break;
	    case 'TDTC':
	    $category = 'Total duties and taxes collected';
	    break;
	    case 'IMPORTENTRIES':
	    $category = 'Import Entries';
	    break;
	}
	  if($category){
	   $dash1_sql.= " AND category = '".$category."'";
	  }
       } else {
	   $category = 'CIF value';
	   $dash1_sql.= " AND category = '".$category."'";
       }

       //$res = $query->execute();

       $res = db_query($dash1_sql);

       $rank				= 0;
       $hs_code				= 0;
       $cif_value			= 0;
       $volume				= 0;
       $total_duties_taxes_collected	= 0;
       $import_entries			= 0;
       $collection_cif_value		= 0;

       $code = "
            <tr class='no-data-row'>
               <td colspan='7'><p><b>There is no data available for the selected criteria!</b></p></td>
            </tr>";
       foreach($res as $i=>$row) {
           if($i==0) $code = "";

	       $rank				= ($row->rank) ? number_format($row->rank): "XX";
	       $hs_code				= ($row->hs_code) ? $row->hs_code: "XX";
	       $cif_value			= ($row->cif_value) ? number_format($row->cif_value): "XX";
	       $volume				= ($row->volume) ? number_format($row->volume): "XX";
	       $total_duties_taxes_collected	= ($row->total_duties_taxes_collected) ? number_format($row->total_duties_taxes_collected): "XX";
	       $import_entries			= ($row->import_entries) ? number_format($row->import_entries): "XX";
	       $collection_cif_value		= ($row->collection_cif_value=='-') ? "--" : number_format((float)$row->collection_cif_value, 1);

                $code.= "
		  <tr class='blank-row'>
		    <td colspan='7'></td>
		  </tr>
		  <tr class='data-row'>
		    <td rowspan='2'><div class='rank-bigtxt'>".$rank."</div></td>
		    <td class='numeric_val dcel1'>".$hs_code."</td>
		    <td class='numeric_val dcel2'>".$cif_value."</td>
		    <td class='numeric_val dcel3'>".$volume."</td>
		    <td class='numeric_val dce14'>".$total_duties_taxes_collected."</td>
		    <td class='numeric_val dcel5'>".$import_entries."</td>
		    <td class='numeric_val dcel6'>".$collection_cif_value."</td>
		  </tr>
		  <tr class='description'>
		    <td colspan='6' class='dcel7'>".$row->description."</td>
		  </tr>";
       }
       
       return $code;
    }





