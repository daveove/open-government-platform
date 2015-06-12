<?php

/**
* Build the higher education infographics
* @param $year the reference year of the report)
* @param pillarId the pillar identifier, or <code>0</code> to get the average scores report for the specified agency
*/
function ched_infographics_higher_education_d4($pillar_id = 1, $year = '2012/2013') {
drupal_add_css(drupal_get_path('theme', 'dgph') . '/css/procurement.css', array ('group' => CSS_THEME));
drupal_set_title('Infographics');

	if(arg(3)) $pillar_id   = arg(3);
	if(arg(4)) $year	= arg(4).'/'.arg(5);

	$code = '';
        switch($pillar_id) {
            case 1:             // Dashboard three Pillar	1	        
                $code .= ched_get_dashb4_pillar1($pillar_id, $year);
                break;
        }
        return $code;

}

/**
* Build the dashboard four pillar 1 report
* @param @year the report year
* @return the pillar 1 report
*/
function ched_get_dashb4_pillar1($pillar_id, $year) {

// gets link to dashboard data
$year1 = explode("/", $year);
$dashbUploadUri = infographics_get_dashboard_datafile(DASHB_CHED, $year1[0]);
$dash_ched_download = '';
if (!empty($dashbUploadUri)) {    
    $dash_ched_download = "<li><a href='$dashbUploadUri' class='has-tip download' title='Download'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>";
}

	$code  = '';
	$code .= "<div class='row dashboard-header'>
		      <div class='large-9 columns sub-heading'>
		         <h3>Open Higher Education Dashboard</h3>
			 <div class='description'>Use this dashboard to get information regarding the higher education data on labor supply, oversubscribed and undersubscribed programs, licensure examination performance and State Universities and Colleges (SUCs) budget for planning, decision making and developmental initiatives.</div>
		      </div>
                      <div class='large-3 columns'>
                        <div class='year-con'>
                            <div class='year'><span>$year</span></div>
                        </div>
                      </div>
		  </div>

		  <div class='row dashboard-content dashboard4-content'>

		      <div class='large-3 columns leftsides datarequest choosePillar'>
			".dashboard_four_left_content($pillar_id, $year)."
		      </div>

		      <div class='large-9 columns works'>
			  <div class='row dashboard-container-header'>
				<div class='large-10 columns container-ritle'>
				    <h2>State Universities and Colleges (SUCs) Budget Data</h2>
				</div>
				<div class='large-2 columns container-social'>
				    <ul class='social-icon apcpi-social-icon'>
					<li><a href='javascript:infographics_print()' class='has-tip print' title='Print'><img alt='' src='/sites/all/themes/dgph/images/icon-11.png'></a></li>
					".$dash_ched_download."
					<li><a class='a2a_dd' href='http://www.addtoany.com/share_save'><img alt='' src='/sites/all/themes/dgph/images/icon-20.png'></a></li>
				    </ul>
				</div>
			  </div>

			  <div class='row dashboard-container-description'>
				<div class='large-12 columns'>
					<p>This dashboard contains information on the total appropriations of State Universities and Colleges (SUC) as well as the per student cost and the tution fee per unit of each SUC.</p>					
				</div>
			  </div>
			  
			  <div class='row dashboard-container-graph'>
				<div class='large-12 columns container-graph'>				
					".ched_collect_data_dashb4_pillar1($year)."
				</div>
			  </div>
			  ".dashboard_four_legend($pillar_id)."

		      </div>
		  </div>
		  <script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>
		";

return $code;
}



   /**
    * Build the dashboard three pillar 1 report
    * @param @year the report year
    * @return the pillar 1 report
    */
    function ched_collect_data_dashb4_pillar1($year) {    

	$dash4_sql = "SELECT id, financial_year, region, suc_name, ps, mood, co, total, psc, ba_bs, ma_ms, phd 
				FROM ched_mini_dashb4_pillar1
				WHERE 
				financial_year = '$year'				
				";

       $region = (isset($_GET['region'])) ? $_GET['region']: '';
       if($region && $region!=0){
           $region_se = dashboard4_region_key_return();

	   $selected_region = $region_se[$region-1];

	   $dash4_sql.= " AND region = '$selected_region'";
       }

       $suc = (isset($_GET['suc'])) ? $_GET['suc']: '';
       if($suc && $suc!=0){
	   $suc_list = dashboard4_college_university_key_return($region);
	   
	   $selected_suc = $suc_list[$suc-1];

	   $dash4_sql.= " AND suc_name = '$selected_suc'";
       }


       $total = (isset($_GET['tot'])) ? $_GET['tot']: '';
       if($total){
	  $tot_array = dash4total();
          $tot_range = $tot_array[$total];

	  $tot_from = $tot_range[0];
	  $tot_to   = $tot_range[1];

	  $dash4_sql.= " AND (total BETWEEN $tot_from  AND $tot_to)";
       }

       $psc = (isset($_GET['psc'])) ? $_GET['psc']: '';
       if($psc){
	  $psc_array = dash4psc();
          $psc_range = $psc_array[$psc];

	  $psc_from = $psc_range[0];
	  $psc_to   = $psc_range[1];

	  $dash4_sql.= " AND (psc BETWEEN $psc_from  AND $psc_to)";
       }

       $res = db_query($dash4_sql);

       $code = "
            <b>There is no data available for the selected criteria!</b>";
       foreach($res as $i=>$row) {
           if($i==0) $code = "";

	   $ba_bs = ($row->ba_bs) ? "<img src='/sites/all/themes/dgph/images/p-icon.png' alt=''>&nbsp;".$row->ba_bs: "--";
	   $ma_ms = ($row->ma_ms) ? "<img src='/sites/all/themes/dgph/images/p-icon.png' alt=''>&nbsp;".$row->ma_ms: "--";
	   $phd   = ($row->phd) ? "<img src='/sites/all/themes/dgph/images/p-icon.png' alt=''>&nbsp;".$row->phd: "--";
                $code.= "
		<div class='dashboard1-pillar2-table'>
		<h4>".$row->suc_name."</h4>
		<table cellpadding='0' cellspacing='0' border='0' width='100%' class='table-one'>
                    <tr class='dash1-pillar2-table-header'>
                       <th class='first'>TOTAL GAA<br />BUDGET<br /> (IN '000 PESOS)</th>
                       <th>PERSONAL SERVICES<br />(IN '000 PESOS)</th>
                       <th>MAINTENANCE & OTHER<br />OPERATING EXPENSES<br />(IN '000 PESOS)</th>
                       <th>CAPITAL OUTLAY<br />(IN '000 PESOS)</th>
                       <th>PER STUDENT<br />COST</th>
                    </tr>";

                $code.= "
                    <tr class='dash4-pillar1-rowone'>
                       <td class='first-col region'><img src='/sites/all/themes/dgph/images/p-icon.png' alt=''>&nbsp;".number_format($row->total)."</td>
                       <td><img src='/sites/all/themes/dgph/images/p-icon.png' alt=''>&nbsp;".number_format($row->ps)."</td>
                       <td><img src='/sites/all/themes/dgph/images/p-icon.png' alt=''>&nbsp;".number_format($row->mood)."</td>
                       <td><img src='/sites/all/themes/dgph/images/p-icon.png' alt=''>&nbsp;".number_format($row->co)."</td>
                       <td class='last-col'><img src='/sites/all/themes/dgph/images/p-icon.png' alt=''>&nbsp;".number_format($row->psc)."</td>
                    </tr>";

                $code.= "
                    </table>";

                $code.= "
		<table cellpadding='0' cellspacing='0' border='0' width='100%' class='table-tution-fee'>
                    <tr class='dash1-pillar2-table-header'>
			<th colspan='3' class='tution-fee-perunit'>TUITION FEE PER UNIT</th>
                    </tr>";

                $code.= "
                    <tr class='dash4-pillar1-rowtwo'>                       
                       <td class='numeric_val'><lable>BA/BS</lable><br />".$ba_bs."</td>
                       <td class='numeric_val'><lable>MA/MS</lable><br />".$ma_ms."</td>
                       <td class='last-col numeric_val'><lable>PHD</lable><br />".$phd."</td>
                    </tr>";

                $code.= "
                    </table>
		    </div>";

       }
       
       return $code;
    }

