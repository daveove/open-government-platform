<?php


/**************************
 * PLASTIC RESINS - PORTS *
 **************************/

/**
 * Handler for "plastic resins by port" report
 * @param $year the reference year of the report
 */
function dof_plasticresins_ports($year = '2013') {
    drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
    drupal_set_title('Infographics');

    $modPath = drupal_get_path('module', 'dof_report');
    drupal_add_js($modPath.'/js/dof_dashboard.js');
    $modPath = drupal_get_path('module', 'dgph_infographics');
    drupal_add_css($modPath.'/css/dgph_infographics_common.css');
    drupal_add_css($modPath.'/css/dgph_infographics_notices.css');
    return dof_get_plasticresins_ports($year);
}

/**
 * Get supported ports
 */
function get_plasticresins_ports($year, $month, $sort){
    $query = db_select('customs_plasticresins_ports', 't')
                    ->fields('t', array('id', 'port'))
                    ->groupBy('t.port')
                    ->orderBy('t.id');
    $res = $query->execute();
    $def_class = 'active';
    if(arg(6)) { 
        $def_class = '';
    }
    $portsCode = l('All Ports', 'infographics/commodities/plasticresins/ports/'.$year.'/'.$month.'/all'.$sort, array('attributes' => array('class' => array($def_class))) );
    foreach($res as $row) {
        $port = $row->port;
        $portsCode .= l($port, 'infographics/commodities/plasticresins/ports/'.$year.'/'.$month.'/'.$port.$sort);
    }
    return $portsCode;
}

/**
 * Build sidebar for "plastic resins by port" report
 */
function dof_report_plasticresins_ports_sidebar($year, $month, $port) {
    $port  = '';
    $sort = '';
    $defIndex = 0;
    if(arg(5)) {
        $defIndex = 2;
    }
    if(arg(6)) { 
        $defIndex = 1;
        $port = '/'.arg(6);
    }   
    if(arg(7)) {
        $sort = '/'.arg(7);
    }
    $def_class = arg(5) ? '' : 'active';
    $month = arg(5) ? arg(5) : '';
    $port_url = arg(6) ? arg(6) : '';
    $order = arg(7) ? arg(7) : '';

    $sidebar = "
                <input type='hidden' id='default-active' value='$defIndex'>
                <input type='hidden' id='month' value='$month'>
                <input type='hidden' id='port_url' value='$port_url'>
                <input type='hidden' id='order' value='$order'>
                <div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
                        <h3 class='left-ui-accordion-header'>CATEGORY</h3>
                        <div>
                                ".l('Commodity Imports', 'infographics/commodity-import', array('attributes' => array('class' => array('') )) )."

                                ".l('Brokers and Importers', 'infographics/brokers-importers', array('attributes' => array('class' => array('') )) )."

                        </div>
                        <h3 class='left-ui-accordion-header'>VIEW BY PORT</h3>
                        <div>	
                                ".get_plasticresins_ports($year, $month, $sort)."
                        </div>
                        <h3 class='left-ui-accordion-header'>VIEW BY MONTH</h3>
                        <div>
                                ".l('All Month', 'infographics/commodities/plasticresins/ports/'.$year.'/all'.$port.$sort)."
                                ".l('January', 'infographics/commodities/plasticresins/ports/'.$year.'/January'.$port.$sort, array('attributes' => array('class' => array($def_class))) )."
                                ".l('February', 'infographics/commodities/plasticresins/ports/'.$year.'/February'.$port.$sort)."
                                ".l('March', 'infographics/commodities/plasticresins/ports/'.$year.'/March'.$port.$sort)."
                                ".l('April', 'infographics/commodities/plasticresins/ports/'.$year.'/April'.$port.$sort)."
                                ".l('May', 'infographics/commodities/plasticresins/ports/'.$year.'/May'.$port.$sort)."
                                ".l('June', 'infographics/commodities/plasticresins/ports/'.$year.'/June'.$port.$sort)."
                                ".l('July', 'infographics/commodities/plasticresins/ports/'.$year.'/July'.$port.$sort)."
                                ".l('August', 'infographics/commodities/plasticresins/ports/'.$year.'/August'.$port.$sort)."
                                ".l('September', 'infographics/commodities/plasticresins/ports/'.$year.'/September'.$port.$sort)."
                                ".l('October', 'infographics/commodities/plasticresins/ports/'.$year.'/October'.$port.$sort)."
                                ".l('November', 'infographics/commodities/plasticresins/ports/'.$year.'/November'.$port.$sort)."
                                ".l('December', 'infographics/commodities/plasticresins/ports/'.$year.'/December'.$port.$sort)."
                        </div>
                </div>";
    return $sidebar;
}

/**
 * Builds the "plastic resins by port" report
 * @param @year the report year
 * @return the report
 */
function dof_get_plasticresins_ports($year) {
    // gets link to dashboard data
    $dashbUploadUri = '';
    $dashbUploadUri = infographics_get_dashboard_datafile(DASHB_DOF, $year);
    $dash_dof_download = '';
    if (!empty($dashbUploadUri)) {
        $dash_dof_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
    }
    $port = 'all';
    if(arg(6)) $port = arg(6);
    if(arg(5)){
       $month = arg(5);
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
                            </ul>
                        </div>
                     </div>		         
                  </div>
              </div>
              <div class='row dashboard-content'>
                  <div class='large-3 columns leftsides datarequest choosePillar'>
                    ".dof_report_plasticresins_ports_sidebar($year, $month, $port)."
                  </div>
                  <div class='large-9 columns works'>
                      <div class='row dashboard-container-header'>
                            <div class='large-9 columns container-ritle'>
                                <h2>Commodity Report</h2>
                            </div>
                            <div class='large-3 columns container-social'>
                                <ul class='social-icon apcpi-social-icon'>
                                    <li><a href='#' title='Print'><img alt='' src='/sites/all/themes/dgph/images/icon-11.png'></a></li>
                                    ".$dash_dof_download."
                                    <li><a href='http://www.addtoany.com/share_save'><img alt='' src='/sites/all/themes/dgph/images/icon-20.png'></a></li>
                                </ul>
                            </div>
                      </div>
                      <div class='row dashboard-container'>
                            <div class='large-12 columns'>
                                ".dof_collect_data_plasticresins_port($year, $month, $port)."
                            </div>
                      </div>
                      <div class='row legend'>
                        <div class='large-12 columns legend'>
                            <div class='legent-container'>
                                <div class='legend-heading'>LEGEND</div>
                                    <p><strong>Plastic Resins imports: Plastic Resins imports per port</strong></p>
                                    <p>This section shows the following information pertaining to plastic resins imports (i.e. commodities with HS codes 8701 to 8716) processed in each of the BOC main district ports: CIF value imported, volume imported, number of import entries processed, and customs duty collected.</p>
                                    <p>Data is extracted from the BOC Electronic-to-Mobile (E2M) database and hence, does not include manual assessments.</p>
                                    <p><strong>CIF value</strong> - total cost of goods, insurance, and freight of the imported rice</p>
                                    <p><strong>Volume</strong> - gross weight of the imported rice</p>
                                    <p><strong>No. of import entries</strong> - total number of rice import transactions processed</p>
                                    <p><strong>Volume</strong> - gross weight of the imported rice</p>
                                    <p><strong>CUD collected</strong> - Customs duty levied on rice imports entering the BOC main district ports; derived by multiplying the dutiable value with duty rate and converted to peso value (using the applicable foreign exchange rate). Duty rate varies depending on the classification of goods under the 2012 ASEAN Harmonized Tariff Nomenclature (AHTN) and various Philippines Trade Agreements (see <a href='http://finder.tariffcommission.gov.ph' target='_blank'>http://finder.tariffcommission.gov.ph</a>).</p>
                                    <p><strong>%  distribution</strong> - the port's CIF value, volume, total duties and taxes, or no. of import entries for a certain month as a percentage of the total CIF value, volume, total duties and taxes, or no. of import entries for all BOC main district ports for that month</p>
                                    <p>A blank entry means no rice imports were processed in that port for that month.</p>
                                    <p><i>Certain commodities and importers are exempt from customs duties collected or paid.</i></p>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>";
    return $code;
}


/**
 * Build the "plastic resins by port" report data collection
 * @param @year the report year
 */
function dof_collect_data_plasticresins_port($year, $month, $port) {
    $query = "select * from customs_plasticresins_ports where year = $year";
    if($month && $month!='all'){
        $query .= " and month = '$month'";
    }
    if ($port && $port!='all'){
        $query .= " and port = '$port'";
    }
    $res = db_query($query);
    $def_class = arg(7) ? '' : 'active';
    $no_data				= 0;
    $arg8 = arg(7);
    $distCIF = (empty($arg8) || $arg8=='CIF') ? 'active' : '';
    $distVOL = ($arg8=='VOLUME') ? 'active' : '';
    $distENT = ($arg8=='IMPORTENTRIES') ? 'active' : '';
    $code = "<div class='dof-dash1-pillar1-table'>
             <h4 class='accord-heading'>PLASTIC RESINS IMPORTS PER PORT</h4>
                <table cellpadding='0' cellspacing='0' border='0' width='100%'>
                    <tr class='dash1-pillar1-table-header'>
                        <th class='first'>PORT</th>
                        <th><a href='#' title='Cost of Goods, Insurance, and Freight' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'></a>".l('CIF VALUE (PHP)', 'infographics/commodities/plasticresins/ports/'.$year.'/'.$month.'/'.$port.'/CIF', array('attributes' => array('class' => array('clickable-item', $def_class) )) )."<br />
                        ".l('VOLUME (Kg)', 'infographics/commodities/plasticresins/ports/'.$year.'/'.$month.'/'.$port.'/VOLUME', array('attributes' => array('class' => array('clickable-item'))))."<br />
                        ".l('NO. OF IMPORT ENTRIES', 'infographics/commodities/plasticresins/ports/'.$year.'/'.$month.'/'.$port.'/IMPORTENTRIES', array('attributes' => array('class' => array('clickable-item'))))."</th>
                        <th>% DISTRIBUTION OF<br /><br /><span class='$distCIF'>CIF VALUE</span><br /><br /><span class='$distVOL'>VOLUME</span><br /><br /><span class='$distENT'>NO. OF IMPORT ENTRIES</span></th>
                        <th><a href='#' title='Customs Duties' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'></a>CUD<br />COLLECTED (PHP)</th>					
                        <th><a href='#' title='Customs Duties' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'></a>% DISTRIBUTION<br />OF CUD COLLECTED</th>
                    </tr>";
    foreach($res as $row) {
         $no_data++;
         if(arg(7)){
             switch(arg(7)){
                 case 'CIF':
                     $cif_vol_imp      = ($row->cif=='-') ? "--" : number_format($row->cif);
                     $distribution_all = ($row->cif_distribution=='-') ? "--" : number_format((float)$row->cif_distribution, 1, '.', '');
                 break;
                 case 'VOLUME':
                     $cif_vol_imp      = ($row->volume=='-') ? "--" : number_format($row->volume);
                     $distribution_all = ($row->volume_distribution=='-') ? "--" : number_format((float)$row->volume_distribution, 1, '.', '');
                 break;
                 case 'IMPORTENTRIES':
                     $cif_vol_imp      = ($row->entries=='-') ? "--" : number_format($row->entries);
                     $distribution_all = ($row->entries_distribution=='-') ? "--" : number_format((float)$row->entries_distribution, 1, '.', '');
                 break;
             }
         }
         else {
             $cif_vol_imp      = ($row->cif=='-') ? "--" : number_format($row->cif);
             $distribution_all = ($row->cif_distribution=='-') ? "--" : number_format((float)$row->cif_distribution, 1, '.', '');
         }
         $port = $row->port;
         $cud_collected	= (($row->cud=='-') || ($row->cud=='0')) ? "--" : number_format($row->cud);
         $cudDistr = (($row->cud_distribution=='-') || ($row->cud_distribution=='0')) ? "--" : number_format((float)$row->cud_distribution, 1, '.', '');
         $code.= "
             <tr class='blank-row'>
                 <td colspan='5'></td>
             </tr>
             <tr class='data-row'>		
                 <td class='description col1'><b>$port</b></td>
                 <td class='numeric_val col2'>$cif_vol_imp</td>
                 <td class='numeric_val col3'>$distribution_all</td>
                 <td class='numeric_val col4'>$cud_collected</td>
                 <td class='numeric_val col5'>$cudDistr</td>
             </tr>";
    }
     $code.= "
        </table>
      </div>";
     if($no_data==0){
         $code = "<div class='dof-dash1-pillar1-table'>
                  <h4 class='accord-heading'>PLASTIC RESINS IMPORTS PER PORT</h4>
                  <p><b>There is no data available for the selected criteria!</b></p>
                  </div>";
     }
     return $code;
 }
 
 
/**************************
 * PLASTIC RESINS - TYPES *
 **************************/
 
 /**
  * Build the "plastic resins by type" report
  * @param $year the reference year of the report)
  */
function dof_plasticresins_types($year = '2013') {
    drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
    drupal_set_title('Infographics');

    $modPath = drupal_get_path('module', 'dof_report');
    drupal_add_js($modPath.'/js/dof_dashboard.js');

    $modPath = drupal_get_path('module', 'dgph_infographics');
    drupal_add_css($modPath.'/css/dgph_infographics_common.css');
    drupal_add_css($modPath.'/css/dgph_infographics_notices.css');
    return dof_get_plasticresins_types($year);
}

 /**
  * Build the report code for "plastic resins by type"
  * @param @year the report year
  * @return the report code
  */
function dof_get_plasticresins_types($year) {
    // gets link to dashboard data
    $dashbUploadUri = '';
    $dashbUploadUri = infographics_get_dashboard_datafile(DASHB_DOF, $year);
    $dash_dof_download = '';
    if (!empty($dashbUploadUri)) {
        $dash_dof_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
    }
    if(arg(5)){
        $month = arg(5);
    } 
    else {
        $month = 'January';
    }
    $code = "<div class='row dashboard-header'>
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
                            </ul>
                        </div>
                     </div>		         
                  </div>
              </div>
              <div class='row dashboard-content'>
                  <div class='large-3 columns leftsides datarequest choosePillar'>
                    ".dof_report_plasticresins_types_sidebar($year, $month)."
                  </div>
                  <div class='large-9 columns works'>
                      <div class='row dashboard-container-header'>
                            <div class='large-9 columns container-ritle'>
                                <h2>Commodity Report</h2>
                            </div>
                            <div class='large-3 columns container-social'>
                                <ul class='social-icon apcpi-social-icon'>
                                    <li><a href='#' title='Print'><img alt='' src='/sites/all/themes/dgph/images/icon-11.png'></a></li>
                                    ".$dash_dof_download."
                                    <li><a href='http://www.addtoany.com/share_save'><img alt='' src='/sites/all/themes/dgph/images/icon-20.png'></a></li>
                                </ul>
                            </div>
                      </div>
                      <div class='row dashboard-container'>
                            <div class='large-12 columns'>
                                ".dof_collect_data_plasticresins_type($year, $month)."
                            </div>
                      </div>
                      <div class='row legend'>
                        <div class='large-12 columns legend'>
                            <div class='legent-container'>
                                   <div class='legend-heading'>LEGEND</div>
                                       <p><strong>Plastic Resins Imports: top plastic resins sorted by type</strong></p>
                                       <p>This section contains a list of top types of plastic resins imports (i.e. imports with HS codes 8701 to 8716) based on CIF value imported sorted by type of HS code. Other information such as HS code, volume imported, number of import entries processed, and customs duty collected are also indicated. Only plastic resins imports processed in BOC main district ports are covered.</p>
                                       <p>Data is extracted from the BOC Electronic-to-Mobile (E2M) database and hence, does not include manual assessments.</p>
                                       <p><strong>HS Code</strong> - According to the Trade Atlas, it is a standardized numerical method of classifying traded products developed and maintained by the World Customs Organization. It can be defined as the “identification number” of all products in customs procedures.<br><br>Click <a href='http://www.dof.gov.ph/customsngbayan/?page_id=8051' target='_blank'>here</a> to see technical definitions of these HS codes, as the ones presented in this dashboard are simplified descriptions.</p>
                                       <p><strong>CIF value</strong> - total cost of goods, insurance, and freight of the imported plastic resins</p>
                                       <p><strong>Volume</strong> - Gross weight of the imported plastic resins</p>
                                       <p><strong>No. of import entries</strong> - Total number of plastic resins import transactions</p>
                                       <p><strong>CUD collected</strong> - Customs duty levied on plastic resins imports entering the BOC main district ports; derived by multiplying the dutiable value with duty rate and converted to peso value (using the applicable foreign exchange rate). Duty rate varies depending on the classification of goods under the 2012 ASEAN Harmonized Tariff Nomenclature (AHTN) and various Philippines Trade Agreements.</p>
                                   </div>
                            </div>
                      </div>
                  </div>
              </div>
              <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>";
    return $code;
}

/**
 * Gets "plastic resins by type" data
 * @param @year the report year
 */
function dof_collect_data_plasticresins_type($year, $month) {
    if(arg(6)){
	switch(arg(6)){
	    case 'CIF':
                $order = '(cif+0)';
	    break;
	    case 'VOLUME':
                $order = '(volume+0)';
	    break;
	    case 'CUDC':
                $order = '(cud+0)';
	    break;
	}
    }
    else {
        $order = '(cif+0)';
    }
    $query = "select * from customs_plasticresins_types where rank>0 and year = $year";
    if($month && $month!='all'){
        $query .= " and month = '".$month."'";
    }
    $query .= " order by $order desc";
    $res = db_query($query);
    $def_class = (arg(6)) ? '' : 'active';
    $no_data = 0;
    $code = "<div class='dof-dash1-pillar1-table'>
             <h4 class='accord-heading'>TOP PLASTIC RESINS IMPORTS BY TYPE</h4>
                     <table cellpadding='0' cellspacing='0' border='0' width='100%'>
                             <tr class='dash1-pillar1-table-header'>
                                     <th class='first'>RANK</th>
                                     <th><a href='javascript:void(0)' title='Harmonized System Commodity Code' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'>HS CODE</a></th>
                                     <th><a href='javascript:void(0)' title='Cost of Goods, Insurance, and Freight' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'>CIF VALUE (PHP)</a></th>
                                     <th>VOLUME (Kg)</th>
                                     <th><a href='javascript:void(0)' title='Customs Duties' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'>CUD COLLECTED (PHP)</a></th>
                                     <th>NO. OF IMPORT<br />ENTRIES</th>
                                     <th>CUD COLLECTED AS<br />% OF CIF VALUE</th>
                             </tr>";
    foreach($res as $row) {
        $no_data++;
        $rank = ($row->rank) ? number_format($row->rank): "--";
        $hs_code = ($row->hs_code) ? $row->hs_code: "--";
        $cif_value = ($row->cif) ? number_format($row->cif): "--";
        $volume = ($row->volume) ? number_format($row->volume): "--";
        $cud_collected = ($row->cud) ? number_format($row->cud): "--";
        $no_import_entries = ($row->entries) ? number_format($row->entries): "--";
        $cud_as_of_cif_value  = ($row->cud_to_cif_perc=='-') ? "--" : number_format((float)$row->cud_to_cif_perc, 1, '.', '');
        $code.= "
		  <tr class='blank-row'>
		    <td colspan='7'></td>
		  </tr>
		  <tr class='data-row'>
		    <td rowspan='2'><div class='rank-bigtxt'>".$rank."</div></td>
		    <td class='numeric_val dcel1'>".$hs_code."</td>
		    <td class='numeric_val dcel2'>".$cif_value."</td>
		    <td class='numeric_val dcel3'>".$volume."</td>
		    <td class='numeric_val dce14'>".$cud_collected."</td>
		    <td class='numeric_val dcel5'>".$no_import_entries."</td>
		    <td class='numeric_val dcel6'>".$cud_as_of_cif_value."</td>
		  </tr>
		  <tr class='description'>
		    <td colspan='6' class='dcel7'>".$row->description."</td>
		  </tr>";
        }
        $code.= "
                  </table>
		</div>";
	if($no_data==0){
            $code = "<div class='dof-dash1-pillar1-table'>
                        <h4 class='accord-heading'>TOP PLASTIC RESINS IMPORTS BY TYPE</h4>
                        <p><b>There is no data available for the selected criteria!</b></p>
                     </div>";
	}
       return $code;
}

/**
 * Build sidebar for "plastic resins by types" report
 */
function dof_report_plasticresins_types_sidebar($year, $month) {
    $sort = '';
    $defIndex = 0;
    if(arg(5)) { 
        $defIndex = 1;
    }
    if(arg(6)) {
        $sort = '/'.arg(6);
    }
    $def_class = (arg(5)) ? '' : 'active';
    $month = (arg(5)) ? arg(5) : '';
    $order = (arg(6)) ? arg(6) : '';
    $sidebar = "
		<input type='hidden' id='default-active' value='$defIndex'>
		<input type='hidden' id='month' value='$month'>
		<input type='hidden' id='order' value='$order'>
		<div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
                    <h3 class='left-ui-accordion-header'>CATEGORY</h3>
                    <div>
                           
                            ".l('Brokers and Importers', 'infographics/brokers-importers', array('attributes' => array('class' => array('') )) )."

                    </div>	
                    <h3 class='left-ui-accordion-header'>VIEW BY MONTH</h3>
                    <div>
                            ".l('All Month', 'infographics/commodities/plasticresins/types/'.$year.'/all'.$sort)."
                            ".l('January', 'infographics/commodities/plasticresins/types/'.$year.'/January'.$sort, array('attributes' => array('class' => array($def_class))) )."
                            ".l('February', 'infographics/commodities/plasticresins/types/'.$year.'/February'.$sort)."
                            ".l('March', 'infographics/commodities/plasticresins/types/'.$year.'/March'.$sort)."
                            ".l('April', 'infographics/commodities/plasticresins/types/'.$year.'/April'.$sort)."
                            ".l('May', 'infographics/commodities/plasticresins/types/'.$year.'/May'.$sort)."
                            ".l('June', 'infographics/commodities/plasticresins/types/'.$year.'/June'.$sort)."
                            ".l('July', 'infographics/commodities/plasticresins/types/'.$year.'/July'.$sort)."
                            ".l('August', 'infographics/commodities/plasticresins/types/'.$year.'/August'.$sort)."
                            ".l('September', 'infographics/commodities/plasticresins/types/'.$year.'/September'.$sort)."
                            ".l('October', 'infographics/commodities/plasticresins/types/'.$year.'/October'.$sort)."
                            ".l('November', 'infographics/commodities/plasticresins/types/'.$year.'/November'.$sort)."
                            ".l('December', 'infographics/commodities/plasticresins/types/'.$year.'/December'.$sort)."
                    </div>
		</div>";
    return $sidebar;
}

/******************************
 * PLASTIC RESINS - IMPORTERS *
 ******************************/

/**
 * Handler for "top plastic resins importers" report
 * @param $year the reference year of the report
 */
function dof_plasticresins_importers($year = '2013') {
    drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
    drupal_set_title('Infographics');
    $modPath = drupal_get_path('module', 'dof_report');
    drupal_add_js($modPath.'/js/dof_dashboard.js');
    $modPath = drupal_get_path('module', 'dgph_infographics');
    drupal_add_css($modPath.'/css/dgph_infographics_common.css');
    drupal_add_css($modPath.'/css/dgph_infographics_notices.css');
    return dof_get_plasticresins_importers($year);
}

/**
 * Build sidebar for "top plastic resins importers" report
 */
function dof_report_plasticresins_importers_sidebar($year, $month, $port) {
    $port  = '';
    $sort = '';
    $defIndex = 0;
    if(arg(5)) {
        $defIndex = 1;
    }
    if(arg(6)) {
        $sort = '/'.arg(6);
    }
    $def_class = arg(5) ? '' : 'active';
    $month = arg(5) ? arg(5) : '';
    $order = arg(6) ? arg(6) : '';

    $sidebar = "
                <input type='hidden' id='default-active' value='$defIndex'>
                <input type='hidden' id='month' value='$month'>
                <input type='hidden' id='order' value='$order'>
                <div id='accordion2' class='ui-accordion ui-widget ui-helper-reset sidebar-accordion' role='tablist'>
                        <h3 class='left-ui-accordion-header'>CATEGORY</h3>
                        <div>
                                ".l('Commodity Imports', 'infographics/commodity-import', array('attributes' => array('class' => array('') )) )."
                                ".l('Commodity Report', 'infographics/commodity-report-rice', array('attributes' => array('class' => array('active') )) )."
                                <div class='child_menu'>
                                    ".l('Rice Imports By Port', 'infographics/commodity-report-rice', array('attributes' => array('class' => array('') )) )."
                                    ".l('Top Rice Importers', 'infographics/commodity-report-top-rice', array('attributes' => array('class' => array('') )) )."
                                    ".l('Motor Vehicle Imports By Port', 'infographics/commodity-report-motor', array('attributes' => array('class' => array('') )) )."
                                    ".l('Motor Vehicle Imports By Type', 'infographics/commodity-report-motor-by-type', array('attributes' => array('class' => array('') )) )."
                                    ".l('Top Motor Vehicle Importers', 'infographics/commodity-report-motor-importers', array('attributes' => array('class' => array('') )) )."
                                    ".l('Plastic Resins By Port', 'infographics/commodities/plasticresins/ports', array('attributes' => array('class' => array('') )) )."
                                    ".l('Plastic Resins By Type', 'infographics/commodities/plasticresins/types', array('attributes' => array('class' => array('') )) )."
                                    ".l('Top Plastic Resins Importers', 'infographics/commodities/plasticresins/importers', array('attributes' => array('class' => array('active') )) )."
                                    ".l('Tobacco By Port', 'infographics/commodities/tobacco/ports', array('attributes' => array('class' => array('') )) )."
                                    ".l('Tobacco By Type', 'infographics/commodities/tobacco/types', array('attributes' => array('class' => array('') )) )."
                                    ".l('Top Tobacco Importers', 'infographics/commodities/tobacco/importers', array('attributes' => array('class' => array('') )) )."
                                    ".l('Iron And Steel By Port', 'infographics/commodities/ironandsteel/ports', array('attributes' => array('class' => array('') )) )."
                                    ".l('Iron And Steel By Type', 'infographics/commodities/ironandsteel/types', array('attributes' => array('class' => array('') )) )."
                                    ".l('Top Iron And Steel Importers', 'infographics/commodities/ironandsteel/importers', array('attributes' => array('class' => array('') )) )."
                                </div>
                                ".l('Trade Activities By Port', 'infographics/trade-activity', array('attributes' => array('class' => array('') )) )."
                                ".l('Brokers and Importers', 'infographics/brokers-importers', array('attributes' => array('class' => array('') )) )."

                        </div>
                        <h3 class='left-ui-accordion-header'>VIEW BY MONTH</h3>
                        <div>
                                ".l('All Month', 'infographics/commodities/plasticresins/importers/'.$year.'/all'.$port.$sort)."
                                ".l('January', 'infographics/commodities/plasticresins/importers/'.$year.'/January'.$port.$sort, array('attributes' => array('class' => array($def_class))) )."
                                ".l('February', 'infographics/commodities/plasticresins/importers/'.$year.'/February'.$port.$sort)."
                                ".l('March', 'infographics/commodities/plasticresins/importers/'.$year.'/March'.$port.$sort)."
                                ".l('April', 'infographics/commodities/plasticresins/importers/'.$year.'/April'.$port.$sort)."
                                ".l('May', 'infographics/commodities/plasticresins/importers/'.$year.'/May'.$port.$sort)."
                                ".l('June', 'infographics/commodities/plasticresins/importers/'.$year.'/June'.$port.$sort)."
                                ".l('July', 'infographics/commodities/plasticresins/importers/'.$year.'/July'.$port.$sort)."
                                ".l('August', 'infographics/commodities/plasticresins/importers/'.$year.'/August'.$port.$sort)."
                                ".l('September', 'infographics/commodities/plasticresins/importers/'.$year.'/September'.$port.$sort)."
                                ".l('October', 'infographics/commodities/plasticresins/importers/'.$year.'/October'.$port.$sort)."
                                ".l('November', 'infographics/commodities/plasticresins/importers/'.$year.'/November'.$port.$sort)."
                                ".l('December', 'infographics/commodities/plasticresins/importers/'.$year.'/December'.$port.$sort)."
                        </div>
                </div>";
    return $sidebar;
}

/**
 * Builds the "top plastic resins importers" report
 * @param @year the report year
 * @return the report
 */
function dof_get_plasticresins_importers($year) {
    // gets link to dashboard data
    $dashbUploadUri = '';
    $dashbUploadUri = infographics_get_dashboard_datafile(DASHB_DOF, $year);
    $dash_dof_download = '';
    if (!empty($dashbUploadUri)) {
        $dash_dof_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
    }
    $month = 'January';
    if(arg(5)){
       $month = arg(5);
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
                            </ul>
                        </div>
                     </div>		         
                  </div>
              </div>
              <div class='row dashboard-content'>
                  <div class='large-3 columns leftsides datarequest choosePillar'>
                    ".dof_report_plasticresins_importers_sidebar($year, $month)."
                  </div>
                  <div class='large-9 columns works'>
                      <div class='row dashboard-container-header'>
                            <div class='large-9 columns container-ritle'>
                                <h2>Commodity Report</h2>
                            </div>
                            <div class='large-3 columns container-social'>
                                <ul class='social-icon apcpi-social-icon'>
                                    <li><a href='#' title='Print'><img alt='' src='/sites/all/themes/dgph/images/icon-11.png'></a></li>
                                    ".$dash_dof_download."
                                    <li><a href='http://www.addtoany.com/share_save'><img alt='' src='/sites/all/themes/dgph/images/icon-20.png'></a></li>
                                </ul>
                            </div>
                      </div>
                      <div class='row dashboard-container'>
                            <div class='large-12 columns'>
                                ".dof_collect_data_plasticresins_importers($year, $month)."
                            </div>
                      </div>
                      <div class='row legend'>
                        <div class='large-12 columns legend'>
                            <div class='legent-container'>
                                <div class='legend-heading'>LEGEND</div>
                                    <p><strong>Plastic resin imports: Top plastic resin importers sorted by type</strong></p>
                                    <p>This section contains a list of the top 10 importers of plastic resins (i.e. importers of commodities with HS codes 3901, 3902, 3903, 3905, 3908, 3911) based on the CIF value of plastic resin they imported, and sorted by the type of plastic resin they imported. Volume imported and customs duty paid by the importer are also indicated. Only plastic resin imports processed in BOC main district ports are covered.</p>
                                    <p>Data is extracted from the BOC Electronic-to-Mobile (E2M) database and hence, does not include manual assessments.</p>
                                    <p><strong>HS Code (or the Harmonized System Commodity Code)</strong> - According to the Trade Atlas, it is a standardized numerical method of classifying traded products developed and maintained by the World Customs Organization. It can be defined as the “identification number” of all products in customs procedures.</p>
                                    <p><strong>Importer</strong> - The party who makes the import declaration.</p>
                                    <p><strong>CIF value</strong> - total cost of goods, insurance, and freight of the imported plastic resin</p>
                                    <p><strong>Volume</strong> - gross weight of the imported plastic resin</p>
                                    <p><strong>Customs duty (CUD) paid</strong> – Customs duty on the imported plastic resin that is paid by the importer. Customs duty is levied on goods entering the country, and is derived by multiplying the dutiable value with duty rate and converted to peso value (using the applicable foreign exchange rate). Duty rate varies depending on the classification of goods under the 2012 ASEAN Harmonized Tariff Nomenclature (AHTN) and various Philippines Trade Agreements.</p>
                                </div>
                            </div>
                       </div>
                  </div>
              </div>
              <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>
            ";
    return $code;
}


/**
 * Gets importer data for "top plastic resins importers" report
 */
function dof_collect_data_plasticresins_importer($year, $month, $order, $hsCode, $hsDescr, $idx) {
    $query = "select * from customs_plasticresins_importers where rank>0 and year = $year and hs_code = '$hsCode'";
    if($month && $month!='all'){
        $query .= " and month = '$month'";
    }
    $res = db_query($query);
    $def_class = (arg(5)) ? '' : 'active';
    $no_data = 0;
    $code = "
                <h3><div class='hs-code'>$hsCode -</div><div class='hs-description'>$hsDescr</div></h3>
                <div>
                    <div class='dof-dash1-pillar1-table'>
                        <table cellpadding='0' cellspacing='0' border='0' width='100%'>
                            <tr class='dash1-pillar1-table-header'>
                                <th class='first'>RANK</th>                                     
                                <th>VOLUME (Kg)</th>
                                <th><a href='javascript:void(0)' title='Cost of Goods, Insurance, and Freight' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'>CIF VALUE (PHP)</a></th>
                                <th><a href='javascript:void(0)' title='Customs Duties' class='has-tip information-tip left-tip'><img src='/sites/all/themes/dgph/images/info.png'>TOTAL CUD PAID (PHP)</a></th>
                            </tr>";
    foreach($res as $row) {
        $no_data++;
        $rank = ($row->rank) ? number_format($row->rank): "--";
        $importer = ($row->importer) ? $row->importer: "--";
        $cif_value = ($row->cif) ? number_format($row->cif): "--";
        $volume	= ($row->volume) ? number_format($row->volume): "--";
        $cud_paid = (($row->cud=='-') || ($row->cud=='0')) ? "--" : number_format($row->cud);
        $code.= "
                            <tr class='blank-row'>
                                <td colspan='4'></td>
                            </tr>
                            <tr class='data-row'>
                                <td rowspan='2'><div class='rank-bigtxt'>$rank</div></td>
                                <td class='numeric_val dcel2'>$volume</td>
                                <td class='numeric_val dcel3'>$cif_value</td>
                                <td class='numeric_val dce14'>$cud_paid</td>
                            </tr>
                            <tr class='description'>
                                <td colspan='4' class='dcel7'>$importer</td>
                            </tr>";
    }
    $code.= "
                        </table>
                    </div>
                </div>";
    if ($no_data==0) {
        $code = "";
    }
    return $code;
}

/**
 * Gets "top plastic resins importers" data
 * @param @year the report year
 */
function dof_collect_data_plasticresins_importers($year, $month) {
    $order = '(cif+0)';
    if(arg(6)){
	switch(arg(6)){
	    case 'CIF':
                $order = '(cif+0)';
	    break;
	    case 'VOLUME':
                $order = '(volume+0)';
	    break;
	    case 'TCP':
                $order = '(cud+0)';
	    break;
	}
    }
    $code = "<div id='motor-importers-heading'><h2>TOP PLASTIC RESINS IMPORTERS</h2></div>
                <div id='dofaccording'>";
    $hsQuery   = "select distinct hs_code, description from customs_plasticresins_importers where rank>0";
    $res = db_query($hsQuery);
    foreach($res as $i=>$row) {
        $idx = ($i+1);
        $hsCode = $row->hs_code;
        $hsDescr = $row->description;
        $code .= dof_collect_data_plasticresins_importer($year, $month, $order, $hsCode, $hsDescr, $idx);
    }
    $code .=  "</div>";
    return $code;
}