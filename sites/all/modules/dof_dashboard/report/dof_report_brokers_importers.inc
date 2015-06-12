<?php

/**
* Build the Brokers Importers infographics
* @param $year the reference year of the report)
* @param pillarId the pillar identifier, or <code>0</code> to get the average scores report for the specified agency
*/
function dof_brokers_importers($pillar_id = 1, $year = '2013') {
    drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
    drupal_set_title('Infographics');

    $modPath = drupal_get_path('module', 'dof_report');
    drupal_add_js($modPath.'/js/dof_dashboard.js');

    $modPath = drupal_get_path('module', 'dgph_infographics');
    drupal_add_css($modPath.'/css/dgph_infographics_common.css');
    drupal_add_css($modPath.'/css/dgph_infographics_notices.css');

    $code = '';
    switch($pillar_id) {
        case 1:             // Dashboard Brokers Importers
            $code .= dof_get_brokers_importers($pillar_id, $year);
            break;
    }
    return $code;
}

/**
* Build the Brokers Importers report
* @param @year the report year
*/
function dof_get_brokers_importers($pillar_id, $year) {

// gets link to dashboard data
$dashbUploadUri = '';
$dashbUploadUri = infographics_get_dashboard_datafile(DASHB_DOF, $year);
$dash_dof_download = '';
if (!empty($dashbUploadUri)) {    
    $dash_dof_download = "<li><a><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
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
                                  <li><a href='#'>2013</a></li>
                                  <li><a href='#'>2012</a></li>
                                  <li><a href='#'>2011</a></li>
                                  <li><a href='#'>2010</a></li>
                              </ul>
                          </div>
                       </div>		         
                    </div>
		  </div>

		  <div class='row dashboard-content'>

		      <div class='large-3 columns leftsides datarequest choosePillar'>
			".dof_brokers_importers_left_content($pillar_id, $year)."
		      </div>

		      <div class='large-9 columns works'>
			  <div class='row dashboard-container-header'>
				<div class='large-9 columns container-ritle'>
				    <h2>Brokers and Importers</h2>
				</div>
				<div class='large-3 columns container-social'>
				    <ul class='social-icon apcpi-social-icon'>
					<li><a><img alt='' src='/sites/all/themes/dgph/images/icon-11.png'></a></li>
					".$dash_dof_download."
					<li><a><img alt='' src='/sites/all/themes/dgph/images/icon-20.png'></a></li>
				    </ul>
				</div>
			  </div>
		  
			  <div class='row dashboard-container'>
				<div class='large-12 columns'>
				   <table cellpadding='0' cellspacing='0' border='0' width='100%'>
				<tr class='dash1-pillar1-table-header'>
					<th class='first'>RANK</th>
					<th>BROKER</th>
					<th><a href='#' title='Cost of Goods, Insurance, and Freight' class='has-tip information-tip'><img src='/sites/all/themes/dgph/images/info.png'>CIF VALUE</a></th>
					<th>VOLUME (Kg)</th>
					<th><a href='#' title='Customs Duties' class='has-tip information-tip'><img src='/sites/all/themes/dgph/images/info.png'>CUD PAID</a></th>
				</tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>1</div></td>
		    <td class='numeric_val col2'>Broker 1</td>
		    <td class='numeric_val col3'>186,562,889,848</td>
		    <td class='numeric_val col4'>5,446,715,081</td>
		    <td class='numeric_val col5'>14,001,866</td>
		  </tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>2</div></td>
		    <td class='numeric_val col2'>Broker 2</td>
		    <td class='numeric_val col3'>132,111,742,363</td>
		    <td class='numeric_val col4'>3,702,096,445</td>
		    <td class='numeric_val col5'>33,466,093</td>
		  </tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>3</div></td>
		    <td class='numeric_val col2'>Broker 3</td>
		    <td class='numeric_val col3'>67,511,662,662</td>
		    <td class='numeric_val col4'>625,318,248</td>
		    <td class='numeric_val col5'>2,003,783,295</td>
		  </tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>4</div></td>
		    <td class='numeric_val col2'>Broker 4</td>
		    <td class='numeric_val col3'>66,267,018,162</td>
		    <td class='numeric_val col4'>1,451,732,990</td>
		    <td class='numeric_val col5'>204,729,354</td>
		  </tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>5</div></td>
		    <td class='numeric_val col2'>Broker 5</td>
		    <td class='numeric_val col3'>47,114,061,302</td>
		    <td class='numeric_val col4'>2,996,156,252</td>
		    <td class='numeric_val col5'>990,737,781</td>
		  </tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>6</div></td>
		    <td class='numeric_val col2'>Broker 6</td>
		    <td class='numeric_val col3'>37,664,280,055</td>
		    <td class='numeric_val col4'>80,416,789</td>
		    <td class='numeric_val col5'>721,854,238</td>
		  </tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>7</div></td>
		    <td class='numeric_val col2'>Broker 17</td>
		    <td class='numeric_val col3'>28,791,404,507</td>
		    <td class='numeric_val col4'>88,791,626</td>
		    <td class='numeric_val col5'>369,029,589</td>
		  </tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>8</div></td>
		    <td class='numeric_val col2'>Broker 8</td>
		    <td class='numeric_val col3'>28,524,546,125</td>
		    <td class='numeric_val col4'>1,072,061</td>
		    <td class='numeric_val col5'>233,485,289</td>
		  </tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>9</div></td>
		    <td class='numeric_val col2'>Broker 9</td>
		    <td class='numeric_val col3'>24,790,601,455</td>
		    <td class='numeric_val col4'>777,973,164</td>
		    <td class='numeric_val col5'>20,880,667</td>
		  </tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>10</div></td>
		    <td class='numeric_val col2'>Broker 10</td>
		    <td class='numeric_val col3'>23,397,983,627</td>
		    <td class='numeric_val col4'>28,321,365</td>
		    <td class='numeric_val col5'>364,027,390</td>
		  </tr>
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  
		  </table>
				</div>
			  </div>
				".dof_brokers_importers_legend()."
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
    function dof_collect_data_brokers_importers($year) {
	$result = '<p><b>There is no data available for the selected criteria!</b></p>';

       if(arg(5)){
	switch(arg(5)){
	    case 'CIF':
	    $order = 'cif_value';
	    break;
	    case 'VOLUME':
	    $order = 'volume';
	    break;
	    case 'CUDPAID':
	    $order = 'cud_paid';
	    break;
	}
       } else {
	  $order = 'cif_value';
       }


	if(arg(4)){
	   switch(arg(4)){
		case 'all':
			$result	= dof_top_brokers_importers($year, 'all', '', $order);
			$result.= '<br />';
			$result.= dof_top_brokers_importers($year, 'all', 'sec', $order);
		break;
		case 'brokers':
			$result	= dof_top_brokers_importers($year, 'brokers', '', $order);
		break;
		case 'importers':
			$result	= dof_top_brokers_importers($year, 'importers', '', $order);
		break;
	   }
	} else {
		$result	= dof_top_brokers_importers($year, 'all', '', $order);
		$result.= '<br />';
		$result.= dof_top_brokers_importers($year, 'all', 'sec', $order);
	}

	return $result;
    }


   /**
    * Build the dashboard one pillar 1 report
    * @param @year the report year
    * @return the pillar 1 report
    */
    function dof_top_brokers_importers($year, $type, $sec, $order) {

       $dash1_sql = "SELECT id, year, category, importers_brokers, cif_value, volume, cud_paid
				FROM dof_dashb4_pillar1
				WHERE 
				year = $year
				";
       $heading = '';
       switch($type){
	  case 'all':	        
		$heading   = ($sec=='sec')? 'Top Importers': 'Top Brokers';

		$dash1_sql.= ($sec=='sec') ? " AND category = 'Importer'" : " AND category = 'Broker'";		
		$dash1_sql.= " ORDER BY $order desc LIMIT 0 , 20";
	  break;
	  case 'brokers':
		$heading   = 'Top Brokers';
		$dash1_sql.= " AND category = 'Broker'";
		$dash1_sql.= " ORDER BY $order desc LIMIT 0 , 20";
	  break;
	  case 'importers':
		$heading   = 'Top Importers';
		$dash1_sql.= " AND category = 'Importer'";
		$dash1_sql.= " ORDER BY $order desc LIMIT 0 , 20";
	  break;
       }

       //print $dash1_sql;

       //$res = $query->execute();

       $res = db_query($dash1_sql);

       $category			= 0;
       $importers_brokers		= 0;
       $cif_value			= 0;
       $volume				= 0;
       $cud_paid			= 0;

       $no_data				= 0;

       $def_class = (arg(5)) ? '' : 'active';
       
       $code = "<div class='dof-dash1-pillar1-table'>
		<h4 class='accord-heading'>".$heading."</h4>
			<table cellpadding='0' cellspacing='0' border='0' width='100%'>
				<tr class='dash1-pillar1-table-header'>
					<th class='first'>RANK</th>
					<th>BROKER</th>
					<th><a href='#' title='Cost of Goods, Insurance, and Freight' class='has-tip information-tip'><img src='/sites/all/themes/dgph/images/info.png'>CIF VALUE (PHP)</a></th>
					<th>VOLUME (Kg)</th>
					<th><a href='#' title='Customs Duties' class='has-tip information-tip'><img src='/sites/all/themes/dgph/images/info.png'>CUD PAID (PHP)</a></th>
				</tr>";

       foreach($res as $i=>$row) {
       $no_data++;
           if($i==0) 

	       $category		= ($row->category) ? $row->category: "--";
	       $importers_brokers	= ($row->importers_brokers) ? $row->importers_brokers: "--";
	       $cif_value		= ($row->cif_value) ? number_format($row->cif_value): "--";
	       $volume			= ($row->volume) ? number_format($row->volume): "--";
	       $cud_paid		= ($row->cud_paid) ? number_format($row->cud_paid): "--";	       

               $code.= "
		  <tr class='blank-row'>
		    <td colspan='5'></td>
		  </tr>
		  <tr class='data-row'>		
		    <td class='description col1'><div class='rank-bigtxt'>".($i+1)."</div></td>
		    <td class='numeric_val col2'>".$importers_brokers."</td>
		    <td class='numeric_val col3'>".$cif_value."</td>
		    <td class='numeric_val col4'>".$volume."</td>
		    <td class='numeric_val col5'>".$cud_paid."</td>
		  </tr>";

       }

               $code.= "
		  </table>
		</div>";


	if($no_data==0){
	       $code = "<div class='dof-dash1-pillar1-table'>
			<h4 class='accord-heading'>".$heading."</h4>
			<p><b>There is no data available for the selected criteria!</b></p>
			</div>";
	}
       
       return $code;
    }





