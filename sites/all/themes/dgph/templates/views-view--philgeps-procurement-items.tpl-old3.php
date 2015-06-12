<?php/** * @file * Template to display the procurement items view. * Contextual Filters: *  - agency identifier (default: 137 - Departement of Agriculture) *  - year posted (default: 2013) *  - bid classification *  - approved budget *  - procurement mode *  - bid status * @ingroup views_templates */?><?php    $vars = get_defined_vars();    $agencyId = arg(2) ? arg(2) : 1433;    $region = arg(9) ? arg(9) : 'all';    $year = arg(3) ? arg(3) : 2014;    $agencyNode = node_load($agencyId);    $agencyName = $agencyNode->title;    $agencies = dgph_philgeps_api_get_agencies();    $view = $vars['view'];    $rows = $view->result;    $map = openlayers_map_load('philgeps_kml_viewer');    $mapCode = openlayers_render_map($map->data,$map->name);    global $user;    $roles = $user->roles;?><link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/chosen/1.4.1/chosen.min.css"><style type="text/css">    .twitter-typeahead {        width: 100%;        text-transform: uppercase;    }    #org_biglist {        text-transform: uppercase;        margin: 0;    }    .tt-dropdown-menu {        background-color: #FFFFFF;        border: solid 1px #CECECE;        border-top: none;        margin-top: 0;        width: 100%;        max-height: 300px;        overflow-y: scroll;    }    .tt-suggestion {        margin: 0!important;        padding: 0 10px;    }    .tt-suggestion.tt-cursor {        color: #fff;        background-color: #0097cf;    }</style><input type="hidden" id="current_org_id" value="<?php echo $agencyId ?>" /><input type="hidden" id="current_region" value="<?php echo $region ?>" /><div class='row dashboard-header'>    <div class='large-6 columns agency'>        <h2 class='title'>Infographics</h2>        <h3 class='title'>PHILGEPS: PROCUREMENT NOTICES AND AWARDS</h3>        <p>The Procurement Notices and Details contain information on the procurement activities of an agency which is hosted in the Philippine Government Electronic Procurement System (PhilGEPS) website, the single portal that serves as the primary and definitive source of information on government procurement, as mandated by R.A. 9184. Note that PhilGEPS only displays information provided for by the agencies and is not responsible for any typographical errors or misinformation presented.</p>        <p>To learn more about the Philippine Procurement Process, and understand the relation between budgeting and the procurement process, <a href="http://data.gov.ph/visualizations/understanding-procurement" target="_blank">click here</a>.</p>    </div>    <div class='large-6 columns'>        <div class='year-con' style="overflow: visible;">            <div class='year'><a href='#' data-dropdown='#philgeps-select-year'><span><?php echo $year ?></span></a></div>            <div id='accordion' class='procurement-accordion' data-dropdown='#philgeps-select-agency' data-vertical-offset='-25'>                <h3><div class='title-line'>Select an Agency</div></h3>                <div>                    <div class='home-cat'><p><?php echo $agencyName ?></p></div>                </div>             </div>            <span id='philgeps-selected-year' style='display:none'><?php echo $year ?></span>            <span id='philgeps-selected-agency-id' style='display:none'><?php echo $agencyId ?></span>            <div id='philgeps-select-year' class='dropdown dropdown-tip dropdown-relative'>                <ul class='dropdown-menu'><?php        $thisYear = date('Y');        for($selYear = $thisYear; $selYear>=2010; $selYear--) {?>                    <li><a href='javascript:void(0)' class='philgeps-year-ref'><?php echo $selYear ?></a></li><?php   } ?>                </ul>            </div>            <div id='philgeps-select-agency' class='dropdown dropdown-tip dropdown-relative'>                <ul class='dropdown-menu' style="max-width: 450px;">                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1514">Office of the President (OP)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1583">Office of the Vice-President (OVP)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1224">Department of Agrarian Reform (DAR)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1433">Department of Agriculture (DA)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1635">Department of Budget and Management (DBM)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1591">Department of Education (DepEd)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1771">Department of Energy (DOE)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="2057">Department of Environment and Natural Resources (DENR)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1805">Department of Finance (DOF)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1928">Department of Foreign Affairs (DFA)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1641">Department of Health (DOH)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1075">Department of the Interior and Local Government (DILG)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1280">Department of Justice (DOJ)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1275">Department of Labor and Employment (DOLE)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1155">Department of National Defense (DND)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1058">Department of Public Works and Highways (DPWH)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1329">Department of Science and Technology (DOST)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1059">Department of Social Welfare and Development (DSWD)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1251">Department of Tourism (DOT)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1191">Department of Trade and Industry (DTI)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1184">Department of Transportation and Communications (DOTC)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1493">National Economic and Development Authority (NEDA)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="2172">Presidential Communications Operations Office (PCOO)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="2268">Autonomous Region in Muslim Mindanao (ARMM)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1136">Civil Service Commission (CSC)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1182">Commission on Audit (COA)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1838">Commission on Elections (COMELEC)</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1526">Office of the Ombudsman</a></li>                    <li><a href='javascript:void(0)' class='philgeps-agency-ref' dept-id="1057">Commission on Human Rights (CHR</a></li>                </ul>            </div>            <div>                <h3 style="font-size: 20px; text-transform: uppercase;">Select a Procuring Entity</h3>                <div>                    <input id="org_biglist" class="twitter-typeahead" type="text" placeholder="Enter a Procuring Entity" disabled="disabled" />                </div>            </div>        </div>    </div></div><div class='row'>    <div class='large-3 columns rightside datarequest choosePillar'>        <div class='search-con'>            <h3 class='left-ui-accordion-header'>Search By</h3>            <div class='search-area'>                <input id='lookup-philgeps' type='image' class='clander-btn' src='/sites/all/modules/dgph_infographics/images/search-icon.png' name=''> <input id='philgeps_free_search' type='text' class='clander-search' name=''>            </div>            <div id='lookup-category' class='bid-con'>                <span class='bidnum'><a href="javascript:philgeps_free_search('bid_number')">Bid Number</a></span>                <span class='funding'><a href="javascript:philgeps_free_search('funding_source')">Funding Source</a></span>                <span class='keyword'><a href="javascript:philgeps_free_search()">Keyword</a></span>                </div>        </div>        <div id='accordion-notices-search' class='procurement-accordion ui-accordion ui-widget ui-helper-reset' role='tablist'>            <h3 class='left-ui-accordion-header'>Bid Classification</h3>            <div>                <form class='custom'>                    <?php                        $curBc = arg(4) ? arg(4) : 'all';                        $bcs = philgeps_get_bid_classifications();                        foreach($bcs as $idx => $bc) {                            $optId = "philgeps_bc_".($idx+1);                            $checked = ($bc==$curBc) ? " checked='checked'" : "";                            $clsChecked = ($bc==$curBc) ? " checked" : "";                            echo "<label for='$optId' class='philgeps_bc'><input type='radio' style='display: none;' id='$optId' name='philgeps_bc' value='$bc'$checked><div class='philgeps-filter-label'>$bc</div></label>";                        }                    ?>                </form>            </div>             <h3 class='left-ui-accordion-header'>Approved Budget (Pesos)</h3>            <div>                <form class='custom'>                    <?php                        $curAb = arg(5) ? arg(5) : 'all';                        $abs = philgeps_get_approved_budget_ranges();                        foreach($abs as $idx => $ab) {                            $optId = "philgeps_ab_".($idx+1);                            $from = $ab['from'];                            $to = ($ab['to']!=-1) ? $ab['to'] : '';                            $label = "";                            if (!empty($to)) {                                $label = number_format($from)." - ".number_format($to);                            }                            else {                                $label = "Above ".number_format($from);                            }                            $abFilter = "$from--$to";                            $checked = ($abFilter==$curAb) ? " checked='checked'" : "";                            $clsChecked = ($abFilter==$curAb) ? " checked" : "";                            echo "<label for='$optId' class='philgeps_ab'><input type='radio' style='display: none;' id='$optId' name='philgeps_ab' value='$abFilter'$checked><div class='philgeps-label'>$label</div></label>";                        }                    ?>                </form>            </div>             <h3 class='left-ui-accordion-header'>Procurement Mode</h3>            <div>                <form class='custom'>                    <?php                        $curPm = arg(6) ? arg(6) : 'all';                        $pms = philgeps_get_procurement_modes();                        foreach($pms as $idx => $pm) {                            $optId = "philgeps_pm_".($idx+1);                            $checked = ($pm==$curPm) ? " checked='checked'" : "";                            $clsChecked = ($pm==$curPm) ? " checked" : "";                            $pmLabel = preg_replace('/\(sec\. (\d+)(\.(\d+))?(\.[AB])?\)/i', '', $pm);                            echo "<label for='$optId' class='philgeps_pm'><input type='radio' style='display: none;' id='$optId' name='philgeps_pm' value='$pm'$checked><div class='philgeps-filter-label'>$pmLabel</div></label>";                        }                    ?>                </form>            </div>             <h3 class='left-ui-accordion-header'>Status</h3>            <div>                <form class='custom'>                     <?php                        $curSt = arg(7) ? arg(7) : 'all';                        $sts = philgeps_get_statuses();                        foreach($sts as $idx => $st) {                            $optId = "philgeps_st_".($idx+1);                            $checked = ($st==$curSt) ? " checked='checked'" : "";                            $clsChecked = ($st==$curSt) ? " checked" : "";                            echo "<label for='$optId' class='philgeps_st'><input type='radio' style='display: none;' id='$optId' name='philgeps_st' value='$st'$checked><div class='philgeps-filter-label'>$st</div></label>";                        }                    ?>                </form>            </div>             <h3 class='left-ui-accordion-header'>Select a Month</h3>            <div>                <form class='custom'>                     <?php                        $curMid = arg(8) ? arg(8) : 'all';                        $months = array("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December");                        foreach($months as $idx => $mn) {                            $mid = $idx + 1;                            $optId = "philgeps_mn_$mid";                            $checked = ($mid==$curMid) ? " checked='checked'" : "";                            $clsChecked = ($mid==$curMid) ? " checked" : "";                            echo "<label for='$optId' class='philgeps_mn'><input type='radio' style='display: none;' id='$optId' name='philgeps_mn' value='$mid'$checked><div class='philgeps-filter-label'>$mn</div></label>";                        }                    ?>                </form>            </div>             <h3 class='left-ui-accordion-header'>Location</h3>            <div>                <form>                     <div>                        <select id="select-region-id" name="select-region">                            <option value='all'>Select Region</option>                            <option value='CAR'>CAR</option>                            <option value='NCR'>Caraga</option>                            <option value='NCR'>NCR</option>                            <option value='Region I'>Region I</option>                            <option value='Region II'>Region II</option>                            <option value='Region III'>Region III</option>                            <option value='Region IV-A'>Region IV-A</option>                            <option value='Region IV-B'>Region IV-B</option>                            <option value='Region V'>Region V</option>                            <option value='Region VI'>Region VI</option>                            <option value='Region VII'>Region VII</option>                            <option value='Region VIII'>Region VIII</option>                            <option value='Region IX'>Region IX</option>                            <option value='Region X'>Region X</option>                            <option value='Region XI'>Region XI</option>                            <option value='Region XII'>Region XII</option>                            <option value='ARMM'>ARMM</option>                        </select>                    </div>                </form>            </div>         </div>        <div class="apply-filters-container">            <input id="apply-filters" class="form-submit philgeps-apply-filters" type="button" value="Apply" name="">            <input id="clear-filters" class="form-submit philgeps-clear-filters" type="button" value="Clear" name="">        </div>    </div>    <div class='large-9 columns works'>        <h2 id="agency_title"></h2>        <ul class='social-icon'>            <li><img alt='' src='/sites/all/themes/dgph/images/icon-11.png'></li>            <?php                $dashbUploadUri = infographics_get_dashboard_datafile(DASHB_NOTICES, $year);                if (!empty($dashbUploadUri)) {            ?>            <li><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></li>            <?php                }            ?>            <li><img alt='' src='/sites/all/themes/dgph/images/icon-20.png'></li>            <?php                if (in_array('administrator', $roles) || in_array('agency', $roles)) {            ?>            <li><img alt='Stats' src='/sites/all/modules/dgph_infographics/images/stats.png'></li>            <?php                 }             ?>        </ul>        <div class='clear'></div>        <div class='public-works-con'>            <div class='cell-2'>Date Posted</div>            <div class='cell-3'>BID #</div>            <div class='cell-4'>Funding source</div>            <div class='cell-5'>B.C <a href='#' title='Bid Classification' class='has-tip'>info</a></div>            <div class='cell-6'>P.M <a href='#' title='Procurement Mode' class='has-tip'>info</a></div>            <div class='cell-7'>Approved Budget</div>            <div class='cell-8'>Contract Amount</div>            <div class='cell-15'>Bid Status</div>        </div>        <div class='clear'></div>        <div id='accordion-notices'>            <?php                foreach($rows as $row) {                    $nid = $row->nid;                    $bidNo = $row->field_field_bid_reference_number[0]['raw']['value'];                    $orgID = $row->field_field_orgid[0]['raw']['value'];                    $bidTitle = $row->node_title;                    $projectName = $row->node_title;                    $dt = strtotime($row->field_field_date_posted[0]['raw']['value']);                    $bc = $row->field_field_bid_classification[0]['raw']['value'];                    $pm = $row->field_field_procurement_mode[0]['raw']['value'];                    $status = strtolower($row->field_field_bid_status[0]['raw']['value']);                    $dtBid = ($status!='closed') ? $row->field_field_bid_status_date[0]['raw']['value'] : '';                    if (strpos($dtBid,' 1970') !== false) {                        $dtBid = '';                    }                    $source = $row->field_field_funding_source[0]['raw']['value'];                    $sourceSize = (strlen($source)>35) ? 'large' : 'regular';                    $budget = number_format($row->field_field_approved_budget[0]['raw']['value']);                    $amount = '';                    $ca = $row->field_field_contract_amount[0]['raw']['value'];                    if (is_numeric($ca)) {                        if (intval($ca)>0) {                            $amount = "<img src='/sites/all/themes/dgph/images/p-icon.png' alt=''>&nbsp;".number_format($ca);                        }                        else {                            $amount = '--';                        }                    }                    else {                         $amount = $ca;                    }                    $bcIcon = strtolower(str_replace(' ', '-', $bc));                    $pmIcon = philgeps_get_pm_icon_name($pm);                    $emptyClass = "";                    $noOfBiddersCode = "";                    $bidStatusTitle = "";                    $bidStatusReason = "";                    if ($status=='awarded') {                        $bidStatusTitle = "Awardee";                        $bidStatusReason = $row->field_field_awardee[0]['raw']['value'];                        $noOfBidders = $row->field_field_number_of_bidders[0]['raw']['value'];                        $noOfBiddersCode = "<span># OF BIDDERS</span><br><p>$noOfBidders</p><p class='small-footnote'>*See No. of Bidders Description</p>";                    }                    else {                        $emptyClass = "cell-12-empty";                        $bidStatusTitle = "Bid Status Reason";                        $bidStatusReason = $row->field_field_bid_status_reason[0]['raw']['value'];                    }                    $kmlLayerNames = philgeps_get_kml($nid);            ?>            <h3>                <div class='public-works-con-2 close-con'>                    <div class='cell-2'>                        <span><?php echo date('M', $dt) ?></span>                        <p><?php echo date('d', $dt) ?></p>                        <span><?php echo date('Y', $dt) ?></span>                    </div>                    <div class='cell-3'><span><?php echo $bidNo ?></span></div>                    <div class='cell-4 cell-4-<?php echo $sourceSize ?>'><?php echo $source ?></div>                    <div class='cell-5'><img src='/sites/all/modules/dgph_infographics/images/notices/<?php echo $bcIcon ?>.png' title='<?php echo $bc ?>' alt=''></div>                    <div class='cell-6'><img src='/sites/all/modules/dgph_infographics/images/notices/<?php echo $pmIcon ?>.png' title='<?php echo $pm ?>' alt=''></div>                    <div class='cell-7'><img src='/sites/all/themes/dgph/images/p-icon.png' alt=''>&nbsp;<?php echo $budget ?></div>                    <div class='cell-8'><?php echo $amount ?></div>                    <div class='cell-15 cell-15-<?php echo $status ?>'><?php echo $status ?><br><span><?php echo $dtBid ?></span></div>                    <div class='cell-9'><span class='h1'><?php echo $bidTitle ?></span></div>                    <div class='cell-16'>Details&nbsp;<img src='/sites/all/themes/dgph/images/show-details.png' alt=''></div>                </div>            </h3>            <div class='apnd-ui-accordion-content'>                <div class='clear'></div>                <div class='cell-13'>                    <h1><?php echo $bidStatusTitle ?></h1>                    <p><?php echo $bidStatusReason ?></p>                </div>                <div class='cell-12 <?php echo $emptyClass ?>'><?php echo $noOfBiddersCode ?></div>                <div class='clear'></div>                                                <div class="accordion4">                    <h3><img src='/sites/all/modules/dgph_infographics/images/procurement-bid-icon.png'> Procurement Bid Notice</h3>                    <div class="procurement-document-container">                        <?php                            $bidNotice = isset($row->field_field_procurement_bid_notice[0]) ? $row->field_field_procurement_bid_notice[0]['raw']['value'] : '';                            if (in_array('administrator', $roles) || in_array('agency', $roles)) {                        ?>                                <div class='pi-instructions'>                                    <textarea id="bid-notice-<?php echo $nid ?>" class="bid-notice" rows="5"><?php echo $bidNotice ?></textarea>                                    <a href="javascript:void(0)" class="bid-notice-update" onclick="philgeps_update_notice(<?php echo $nid ?>, 'bid')">Update</a>                                    <div class="philgeps-ajax-loading"></div>                                </div>                        <?php                            }                            else if (!empty($bidNotice)) {                                print "<div class='pi-instructions'>$bidNotice</div>";                            }                        ?>                        <div class="procurement-document"><a href="https://philgeps.gov.ph/GEPSNONPILOT/Tender/PrintableBidNoticeAbstractUI.aspx?refid=<?php echo $bidNo ?>" target='_blank' class='view-procurement-bid'>View Procurement Bid</a></div>                    </div>                    <h3><img src='/sites/all/modules/dgph_infographics/images/procurement-contract-icon.png'> Procurement Award Notice</h3>                    <div class="procurement-document-container">                        <?php                            $awardNotice = isset($row->field_field_award_notice_abstract[0]) ? $row->field_field_award_notice_abstract[0]['raw']['value'] : '';                            if (in_array('administrator', $roles) || in_array('agency', $roles)) {                        ?>                                <div class='pi-instructions'>                                    <textarea id="award-notice-<?php echo $nid ?>" class="award-notice" rows="5"><?php echo $awardNotice ?></textarea>                                    <a href="javascript:void(0)" class="award-notice-update" onclick="philgeps_update_notice(<?php echo $nid ?>, 'award')">Update</a>                                    <div class="philgeps-ajax-loading"></div>                                </div>                        <?php                            }                            else if (!empty($awardNotice)) {                                print "<div class='pi-instructions'>$awardNotice</div>";                            }                            $showAwardDocs = (($status!='closed') && ($status!='cancelled') && ($status!='failed') && ($status!='shortlisted'));                            $awardID = is_numeric($row->field_field_award_id[0]['raw']['value']) ? intval($row->field_field_award_id[0]['raw']['value']) : 0;                        ?>                        <?php if ($showAwardDocs && ($awardID>0)) { ?>                         <div class="procurement-document"><a href="https://philgeps.gov.ph/GEPSNONPILOT/Tender/printableAwardNoticeAbstractPopUI.aspx?awardID=<?php echo $awardID ?>" target='_blank' class='view-procurement-bid'>View Award Notice Abstract</a></div>                        <?php } ?>                    </div>                    <h3><img src='/sites/all/modules/dgph_infographics/images/procurement-contract-icon.png'> Procurement Award Contract</h3>                    <div class="procurement-document-container">                        <div class='pi-instructions'>This contains the Award Contract and other related documents (Notice of Award, BAC Resolution, Notice of Proceed, Signed Contract, etc ...)</div>                        <div class="procurement-document">                    <?php                        if ($showAwardDocs) {                            $cinfo = isset($row->field_field_contract_info[0]) ? $row->field_field_contract_info[0]['raw']['value'] : '';                            $cdocs = philgeps_extract_award_contract($cinfo);                            if (!empty($cdocs)) {                    ?>                            <ul class='contract-docs'>                    <?php                                foreach($cdocs as $docType => $docs) {                    ?>                                <li><?php echo $docType ?>                                    <ul class='contract-type-docs'>                                    <?php                                         foreach($docs as $doc) {                                            $fileExists = $doc[PHILGEPS_CONTRACT_FILE_EXISTS];                                            $docName = $doc[PHILGEPS_CONTRACT_DOCUMENT_NAME];                                            if ($fileExists) {                                                $docUrl = $doc[PHILGEPS_CONTRACT_DOCUMENT_URL];                                    ?>                                        <li><a href='<?php echo $docUrl ?>' target='_blank'><?php echo $docName ?></a></li>                                    <?php                                            }                                            else {                                    ?>                                        <li><?php echo $docName ?> (document not available)</li>                                    <?php                                            }                                        }                                    ?>                                    </ul>                                </li>                    <?php                                 }                    ?>                            </ul>                    <?php                            }                             else {                     ?>                            <p class='not-avail'>No document available at the moment.</p>                    <?php                               }                         }                    ?>                        </div>                    </div>                    <?php foreach($kmlLayerNames as $idx => $kmlLayerName) { ?>                    <input type="hidden" id="kml-layer-filename-<?php echo $nid.'-'.$idx ?>" value="<?php echo $kmlLayerName ?>">                    <?php } ?>                    <h3 id="view-map-<?php echo $nid ?>"><img src='/sites/all/modules/dgph_infographics/images/viewmap-icon.png'> View Map</h3>                    <div id="map-container-<?php echo $nid ?>" class="procurement-map-container">                    </div>                    <h3><img src='/sites/all/modules/dgph_infographics/images/view-feedback-icon.png'> View Feedback</h3>                    <div class="procurement-feedback-container">                        <iframe src="http://open-data-network.appspot.com/iframes/v1/comments?dgph_node_id=<?php echo $nid ?>&philgeps_bid_reference_number=<?php echo $bidNo ?>&philgeps_org_id=<?php echo $orgID ?>&philgeps_project_name=<?php echo rawurlencode($projectName) ?>" style="border: none; background: none; width: 100%; min-height: 550px;"></iframe>                    </div>                </div>            </div>            <?php } ?>        </div>        <div id="map-placeholder-container"><div id="map-placeholder"><?php echo $mapCode ?></div></div>        <?php print $view->query->render_pager() ?>        <div class='clear'></div>        <div class='large-12 columns legend'>            <h1 class='notices'>Legend</h1>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>Bid #</div></div>                <div class='large-9 columns'><div class='field-value'>PhilGEPS system-generated number</div></div>            </div>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>Date Posted</div></div>                <div class='large-9 columns'><div class='field-value'>Date of publication in PhilGEPS</div></div>            </div>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>Bid Classification</div></div>                <div class='large-9 columns'><div class='field-value'>General classification of goods, civil works & consulting services</div></div>            </div>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>Procurement Mode</div></div>                <div class='large-9 columns'>                    <div class='field-value'>                        <p>Chosen method of procurement<br>**Alternative Methods of Procurement - the procuring entity may use these methods only in highly exceptional cases as provided for in RA 9184:</p>                        <ol class='alpha'>                            <li><b>Limited Source Bidding</b> otherwise known as selective bidding, involves direct invitation to bid by procuring entity from the list of pre-selected suppliers or consultants with known experience and proven capability</li>                            <li><b>Direct Contracting</b> or single source procurement, may be used in the procurement of goods which can be obtained only from proprietary source, exclusive dealer or manufacturers</li>                            <li><b>Repeat Order</b> may be used in the procurement of goods from the winning bidder but shall not exceed 25% of the quantity of each item in the original contract</li>                            <li><b>Shopping</b> is used when a procuring entity simply requests for submission of price quotations for readily available off-the-shelf goods or regular equipment</li>                            <li><b>Negotiated Procurement</b> is used when procuring entity directly negotiates a contract with a technically, legally, and financially capable supplier. Below is a list of the types of negotiated procurement as provided for in the IRR of RA 9184:                                <ol class='roman'>                                    <li>Two Failed Biddings (Sec 53.1)</li>                                    <li>Emergency Cases (Sec 53.2)</li>                                    <li>Take-Over of Contracts (Sec 53.3)</li>                                    <li>Adjacent or Contiguous (Sec 53.4)</li>                                    <li>Agency-to-Agency (Sec. 53.5)</li>                                    <li>Procurement Agent (Sec 53.6)</li>                                    <li>Highly Technical Consultants (Sec 53.7)</li>                                    <li>Defense Cooperation Agreement (53.8)</li>                                    <li>Small Value Procurement (53.9)</li>                                    <li>Lease of Real Property (53.10)</li>                                    <li>NGO Participation (53.11)</li>                                    <li>Community Participation (53.12)</li>                                    <li>United Nations Agencies (53.13)</li>                                </ol>                            </li>                        </ol>                    </div>                </div>            </div>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>Bid Title</div></div>                <div class='large-9 columns'><div class='field-value'>Title of bid opportunity</div></div>            </div>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>Approved Budget</div></div>                <div class='large-9 columns'><div class='field-value'>Budget for the contract as approved by the head of the procuring entity; or the Estimated Contract Cost in the case of Foreign-funded Procurement</div></div>            </div>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>Bid Status</div></div>                <div class='large-9 columns'>                    <div class='field-value'>                        <ul>                            <li><b>Awarded</b> - The Notice of Award is posted in PhilGEPS</li>                            <li><b>Cancelled</b> - When there is incorrect/insufficient information provided in the Bid Notice</li>                            <li><b>Closed</b> - The Bid Notice has reached the Deadline of bid submission and the bid result is not yet posted</li>                            <li><b>Failed</b> - The Bidding is declared as failed</li>                            <li><b>Shortlisted</b> - The shortlisted consultants and the 2nd stage notice are posted in PhilGEPS. Also indicated is the date of current bid status in PhilGEPS.</li>                        </ul>                        <p class="bid-status">Some Bid Notices with <b>*Closed*</b> status in PhilGEPS that are displayed as <b>*Awarded*</b> in the dashboard, reflects projects with at least one Awarded line item.</p>                    </div>                </div>            </div>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>No. of Bidders</div></div>                <div class='large-9 columns'>                    <div class='field-value'>                        Refers to the number of bidders who submitted bids. If no. of bidders is 1, the following conditions are to be considered:                        <ol class='alpha'>                            <li>There is a Single Calculated/Rated and Responsive Bid where only one bidder submitted a bid as specified under Section 36 of RA 9184</li>                            <li>The procurement mode used is Alternative Methods of Procurement under Rule XVI (Secs. 48-54) of the IRR of RA 9184</li>                            <li>Only the winning bidder was posted</li>                        </ol>                    </div>                </div>            </div>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>Awardee</div></div>                <div class='large-9 columns'><div class='field-value'>Name of the bidder that was awarded the contract</div></div>            </div>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>Contract Amount</div></div>                <div class='large-9 columns'><div class='field-value'>Amount of the contract as approved by the head of the procuring entity</div></div>            </div>            <div class='row'>                <div class='large-3 columns'><div class='field-name'>Funding Source</div></div>                <div class='large-9 columns'><div class='field-value'>Source of the funds</div></div>            </div>        </div>     </div></div><?php    $activeIndex = "";    if ($curBc!='all') {        $activeIndex = "0";    }    else if ($curAb!='all') {        $activeIndex = "1";    }    else if ($curPm!='all') {        $activeIndex = "2";    }    else if ($curSt!='all') {        $activeIndex = "3";    }    else if ($curMid!='all') {        $activeIndex = "4";    }?><input type='hidden' id='default-active' value='<?php echo $activeIndex ?>'><script type='text/javascript' src='//static.addtoany.com/menu/page.js'></script>