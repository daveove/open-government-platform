<?php
    define('DGPH_PHILGEPS_CENTRAL_API_ENDPOINT_TEST', 'http://philgepsws.insomnation.com/PhilGEPSws.svc');
    define('DGPH_PHILGEPS_CENTRAL_API_ENDPOINT', 'http://202.90.153.116/PhilGEPSws.svc');
    define('CENTRAL_API_LOGIN', 'GEPSWCFUser');
    define('CENTRAL_API_PASSWORD', 'G3P$WCFUser');
    
    define('CENTRAL_API_PI_APPROVED_BUDGET', 'Approved_Budget');
    define('CENTRAL_API_PI_AWARDEE', 'Awardee');
    define('CENTRAL_API_PI_BID_REFERENCE_NUMBER', 'BidNum');
    define('CENTRAL_API_PI_BID_CLASSIFICATION', 'Bid_Classification');
    define('CENTRAL_API_PI_BID_STATUS', 'Bid_Status');
    define('CENTRAL_API_PI_BID_STATUS_DATE', 'Bid_Status_Date');
    define('CENTRAL_API_PI_BID_TITLE', 'Bid_Title');
    define('CENTRAL_API_PI_CONTRACT_AMOUNT', 'Contract_Amount');
    define('CENTRAL_API_PI_DATE_POSTED', 'Date_Posted');
    define('CENTRAL_API_PI_FUNDING_SOURCE', 'Funding_Source');
    define('CENTRAL_API_PI_NUMBER_OF_BIDDERS', 'Num_Bidders');
    define('CENTRAL_API_PI_PROCUREMENT_MODE', 'Procurement_Mode');
    define('CENTRAL_API_PI_BID_STATUS_REASON', 'Status_Reason');
    define('CENTRAL_API_PI_AWARD_CONTRACT', 'Award_Contract');
    define('CENTRAL_API_PI_AWARD_ID', 'AwardID');
    
    /**
     * Opens a new session to the PhilGEPS Central API
     * @param string $username the user name
     * @param string $password the user password
     * @return the session identifier, or <code>null</code> on failure
     */
    function philgeps_central_api_open_session($username, $password) {
        $sid = null;
        $reqUrl = DGPH_PHILGEPS_CENTRAL_API_ENDPOINT."/InitSession?UserID=$username&Pass=$password";
        $resp = drupal_http_request($reqUrl);
        if ($resp->code == HTTP_RESPONSE_OK) {
            // gets the session identifier
            $respData = json_decode($resp->data);
            $sid = $respData->SessionID;
        }
        return $sid;
    }
    
    /**
     * Close a PhilGEPS Central API session
     * @param string $sid the session identifier
     */
    function philgeps_central_api_close_session($sid) {
        if ($sid!=null) {
            // closes the session
            $reqUrl = DGPH_PHILGEPS_CENTRAL_API_ENDPOINT."/EndSession?SessionID=$sid";
            drupal_http_request($reqUrl);
        }
    }
    
    /**
     * Fetch the procurement items for an Agency
     * @param int $orgId the agency organization identifier
     * @param int $year the year to fetch items for
     * @param int $month the month to fetch items for
     * @param int $day the day to fetch items for (0 = whole month)
     * @return array the list of procurement items
     */
    function philgeps_central_api_fetch_procurement_items($orgId, $year, $month, $day = 0) {
        $items = array();
        // opens a session
        $sid = philgeps_central_api_open_session(CENTRAL_API_LOGIN, CENTRAL_API_PASSWORD);
        if ($sid!=null) {
            // gets number of procurement items
            $fromDay = ($day>0) ? $day : 1;
            $fromMonth = $month;
            $toDay = ($day>0) ? ($day+1) : 0;
            $toMonth = ($day>0) ? $month : ($month+1);
            $fromDate = date("Y-m-d", mktime(0, 0, 0, $fromMonth, $fromDay, $year));
            $toDate = date("Y-m-d", mktime(0, 0, 0, $toMonth, $toDay, $year));
            $reqOpts = array('timeout'=>60);
            $reqUrl = DGPH_PHILGEPS_CENTRAL_API_ENDPOINT."/GetProcurementCount?SessionID=$sid&OrganizationID=$orgId&FromDate=$fromDate&ToDate=$toDate";
            $resp = drupal_http_request($reqUrl, $reqOpts);
            if ($resp->code == HTTP_RESPONSE_OK) {
                // gets procurement items
                $itemsCount = $resp->data;
                if ($itemsCount>0) {
                    $reqUrl = DGPH_PHILGEPS_CENTRAL_API_ENDPOINT."/GetProcurements?SessionID=$sid&OrganizationID=$orgId&FromDate=$fromDate&ToDate=$toDate&RecordsToSkip=0&RecordsToRetrieve=$itemsCount";
                    $resp = drupal_http_request($reqUrl, $reqOpts);
                    if ($resp->code == HTTP_RESPONSE_OK) {
                        $procs = json_decode($resp->data, true);
                        foreach($procs as $proc) {
                            try {
                                // gets procurement documents information
                                $awardID = $proc[CENTRAL_API_PI_AWARD_ID];
                                if ($awardID!=null) {
                                    $reqUrl = DGPH_PHILGEPS_CENTRAL_API_ENDPOINT."/GetDocuments?SessionID=$sid&AwardID=$awardID";
                                    $resp = drupal_http_request($reqUrl, $reqOpts);
                                    if ($resp->code == HTTP_RESPONSE_OK) {
                                        // save raw response
                                        $proc[CENTRAL_API_PI_AWARD_CONTRACT] = $resp->data;
                                    }
                                }
                            }
                            catch(Exception $e) {}
                            // add item to the result
                            $items[] = $proc;
                        }
                    }
                }
            }
            // close the session
            philgeps_central_api_close_session($sid);
        }
        return $items;
    }


    /**
     * Fetch the procurement items for an Agency
     * @param int $orgId the agency organization identifier
     * @param int $year the year to fetch items for
     * @param int $month the month to fetch items for
     * @param int $day the day to fetch items for (0 = whole month)
     * @return array the list of procurement items
     */
    function philgeps_central_api_fetch_procurement_items_ckan($orgId, $year, $month, $day = 0) {
        $items = array();
        // opens a session
        $sid = philgeps_central_api_open_session(CENTRAL_API_LOGIN, CENTRAL_API_PASSWORD);
        if ($sid!=null) {
            // gets number of procurement items
            $naked_url = "http://ckan.urls.ph/api/action/datastore_search?resource_id=";
            $fromDay = ($day>0) ? $day : 1;
            $fromMonth = $month;
            $toDay = ($day>0) ? ($day+1) : 0;
            $toMonth = ($day>0) ? $month : ($month+1);
            $fromDate = date("Y-m-d", mktime(0, 0, 0, $fromMonth, $fromDay, $year));
            $toDate = date("Y-m-d", mktime(0, 0, 0, $toMonth, $toDay, $year));
            $reqOpts = array('timeout'=>60);
            
            $bid_information_resource_id = "0fa4b391-d44f-465a-a58a-6979099c35ef";
            $award_resource_id = "0896bf3d-523c-4da9-8014-011023cadcfa";
            $bidders_lists_resource_id = "6ab253bc-1d47-4995-8d88-9133bf791615";
            $organization_resource_id = "c6b1d866-8f50-40fb-8cc7-6217ee4caa41";


            $reqUrl = $naked_url.$bid_information_resource_id.'&filters={"PublishDate":"'.$fromDate.'","OrgID":'.$orgId.'}';
            $bid_information_result = drupal_http_request($reqUrl, $reqOpts);

            $json_result = array();

            if ($bid_information_result->code == HTTP_RESPONSE_OK) {
                // gets procurement items
                $bid_records = $bid_information_result->result->records;
                $bid_information_result_json = json_decode($bid_information_result->data, true);
                $bid_records = $bid_information_result_json["result"]["records"];

                if (!empty($bid_records)) {
                    // fetch award with refid == info refid
                    foreach($bid_records as $r) {
                    	$award_id = null;
	                    $awardee_id = null;
	                    $contractAmt = null;
	                    $awardee = "";
	                    
                        $bid_in_ref_id = $r["RefID"];
                        $reqUrl1 = $naked_url.$award_resource_id.'&filters={"RefID":"'.$bid_in_ref_id.'"}';
                        $award_result = drupal_http_request($reqUrl1, $reqOpts);
						if ($award_result->code == HTTP_RESPONSE_OK) {
							$award_result_json = json_decode($award_result->data, true);
							$awards = $award_result_json["result"]["records"];
	                        if(!empty($awards)){
		                        $award_id = $awards[0]["AwardID"];
		                        $awardee_id = $awards[0]["AwardeeID"];
		                        $contractAmt = $awards[0]["ContractAmt"];
		                        $awardee = $awards[0]["Awardee"];
	                        }
						}
						
						$bidders_count = 0;
						if($award_id != null){
							// fetch bidders lists awardID == award awardID
							$reqUrl2 = $naked_url.$bidders_lists_resource_id.'&filters={"AwardID":"'.$award_id.'"}';
							$bidders_lists_result = drupal_http_request($reqUrl2, $reqOpts);
							if ($bidders_lists_result->code == HTTP_RESPONSE_OK) {
								$bidders_lists_result_json = json_decode($bidders_lists_result->data, true);
								$bidders_count = count($bidders_lists_result_json["result"]["records"]);
							}
						}
						
						$address_string = "";
                        // fetch organization orgid == awardID
                        $reqUrl3 = $naked_url.$organization_resource_id.'&filters={"OrgID":"'.$awardee_id.'"}';
                        $organizations_result = drupal_http_request($reqUrl3, $reqOpts);
                        if ($organizations_result->code == HTTP_RESPONSE_OK) {
                        	// check if organization has result
                        	$organizations_result_json = json_decode($organizations_result->data, true);
	                        $org_count = $organizations_result_json["result"]["records"];
	                        if (!empty($org_count)) {
	                            $add1 = $org_count[0]["Address1"];
	                            $add2 = $org_count[0]["Address2"];
	                            $add3 = $org_count[0]["Address3"];
	                            $org_city = $org_count[0]["City"];
	                            $org_province = $org_count[0]["Province"];
	                            $org_country = $org_count[0]["Country"];
	                            
	                            if($add1 != ''){
		                            if($address_string == ''){
			                            $address_string = $address_string." -";
		                            }
		                            if($address_string == ' -'){
		                            	$address_string = $address_string." ".$add1;   
		                            }
		                            else {
			                            $address_string = $address_string.", ".$add1;   
		                            }
	                            }
	                            if($add2 != ''){
		                            if($address_string == ''){
			                            $address_string = $address_string." -";
		                            }
		                            if($address_string == ' -'){
		                            	$address_string = $address_string." ".$add2;   
		                            }
		                            else {
			                            $address_string = $address_string.", ".$add2;   
		                            }
	                            }
	                            if($add3 != ''){
		                            if($address_string == ''){
			                            $address_string = $address_string." -";
		                            }
		                            if($address_string == ' -'){
		                            	$address_string = $address_string." ".$add3;   
		                            }
		                            else {
			                            $address_string = $address_string.", ".$add3;   
		                            }
	                            }
	                            if($org_city != ''){
		                            if($address_string == ''){
			                            $address_string = $address_string." -";
		                            }
		                            if($address_string == ' -'){
		                            	$address_string = $address_string." ".$org_city;   
		                            }
		                            else {
			                            $address_string = $address_string.", ".$org_city;   
		                            }
	                            }
	                            if($org_province != ''){
		                            if($address_string == ''){
			                            $address_string = $address_string." -";
		                            }
		                            if($address_string == ' -'){
		                            	$address_string = $address_string." ".$org_province;   
		                            }
		                            else {
			                            $address_string = $address_string.", ".$org_province;   
		                            }
	                            }
	                            if($org_country != ''){
		                            if($address_string == ''){
			                            $address_string = $address_string." -";
		                            }
		                            if($address_string == ' -'){
		                            	$address_string = $address_string." ".$org_country;   
		                            }
		                            else {
			                            $address_string = $address_string.", ".$org_country;   
		                            }
	                            }
	                        }
                        }
                        
                        if(is_string($r["ApprovedBudget"])){
	                        $r["ApprovedBudget"] = (float) $r["ApprovedBudget"];
                        }
                        if(is_string($award_id)){
	                        $award_id = (int) $award_id;
                        }
                        if(is_string($contractAmt)){
	                        $contractAmt = (float) $contractAmt;
                        }
                        
                        if($r["PublishDate"] != null){
                        	$postedTimestamp = strtotime($r["PublishDate"]);
	                        $postedTimestampStr = (string)$postedTimestamp;
	                        $postedTimestampDate = "\/Date(".$postedTimestampStr."000+0800)\/";
	                        $r["PublishDate"] = $postedTimestampDate;
                        }
                        
                        if($r["ClosingDate"] != null){
                        	$postedTimestamp = strtotime($r["ClosingDate"]);
	                        $postedTimestampStr = (string)$postedTimestamp;
	                        $postedTimestampDate = "\/Date(".$postedTimestampStr."000+0800)\/";
	                        $r["ClosingDate"] = $postedTimestampDate;
                        }
                        
                        # set json data
                        $json_content = array(
                            'Approved_Budget'=> $r["ApprovedBudget"],
                            'AwardID'=> $award_id,
                            'Awardee'=> $awardee.$address_string,
                            'BidNum'=> $r["RefID"],
                            'Bid_Classification'=> $r["Classification"],
                            'Bid_Status'=> $r["TenderStatus"],
                            'Bid_Status_Date'=> $r["ClosingDate"],
                            'Bid_Title'=> $r["TenderTitle"],
                            'Contract_Amount'=> $contractAmt,
                            'Date_Posted'=> $r["PublishDate"],
                            'Funding_Source'=> $r["FundingSource"],
                            'Num_Bidders'=> $bidders_count,
                            'Procurement_Mode'=> $r["ProcurementMode"],
                            'Status_Reason'=> $r["Reason"]
                        );
                        # save to lists
                        $json_result[] = $json_content;
                    }

                    if ($json_result > 0) {
                        foreach($json_result as $proc) {
                            try {
                                // gets procurement documents information
                                // $awardID = $proc[CENTRAL_API_PI_AWARD_ID];
                                $awardID = $proc["AwardID"];
                                if ($awardID!=null) {
                                    $reqUrl = DGPH_PHILGEPS_CENTRAL_API_ENDPOINT."/GetDocuments?SessionID=$sid&AwardID=$awardID";
                                    $resp = drupal_http_request($reqUrl, $reqOpts);
                                    if ($resp->code == HTTP_RESPONSE_OK) {
                                        // save raw response
                                        $proc[CENTRAL_API_PI_AWARD_CONTRACT] = $resp->data;
                                    }
                                }
                            }
                            catch(Exception $e) {}
                            // add item to the result
                            $items[] = $proc;
                        }
                    }
                }
            }
            // close the session
            philgeps_central_api_close_session($sid);
        }
        return $items;
    }

    
    /**
     * Deletes procurement items for an agency
     * @param int $agencyId the agency node identifier
     * @param int $year the year to fetch items for
     * @param int $month the month to fetch items for
     */
    function philgeps_central_api_delete_procurement_items($agencyId, $year, $month) {
        $query= new EntityFieldQuery();
        $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', 'philgeps_procurement_item')
                    ->propertyCondition('status', 1)
                    ->fieldCondition('field_agency', 'target_id', $agencyId)
                    ->fieldCondition('field_date_posted_year', 'value', $year)
                    ->fieldCondition('field_date_posted_month', 'value', $month);
        $res = $query->execute();
        if (isset($res['node'])) {
            // delete procurement items
            $nids = array_keys($res['node']);
            node_delete_multiple($nids);
        }
    }
    
    /**
     * Gets the user(s) belonging to a government agency
     * @param int $agencyId the agency identifiers
     * @return array identifiers of users belonging to the agency
     */
    function philgeps_central_api_get_agency_users($agencyId) {
        $uids = array();
        $query = db_select('users', 'u')
                    ->fields('u', array('uid'));
        $query->join('users_roles', 'r', 'r.uid=u.uid');
        $query->join('field_data_field_user_agency', 'a', 'a.entity_id = u.uid');
        $query->condition('r.rid', PHILGEPS_ROLE_AGENCY)
              ->condition('a.field_user_agency_target_id', $agencyId);
        $res = $query->execute();
        foreach($res as $row) {
            $uids[] = $row->uid;
        }
        return $uids;
    }
    
    /**
     * Imports procurement items information from the PhilGEPS database to the PhilGEPS Dashboard
     * @param int $year the year to fetch items for (0 = this year)
     * @param int $month the month to fetch items for (0 = this month)
     * @param int $day the day to fetch items for (0 = whole month)
     * @return int the total number of successfully imported items
     */
    function philgeps_central_api_import_procurement_items($year = 0, $month = 0, $day = 0) {
        $totalImported = 0;
        if (0==$year) {
            // set current year
            $year = date('Y');
        }
        if (0==$month) {
            // set current month
            $month = date('n');
        }
        if ($year>0 && $month>0) {
            watchdog('dgph_philgeps_api', "starting procurement items import from central database ($month $year).");
            // fetch agencies
            $agencies = dgph_philgeps_api_get_agencies();
            foreach($agencies as $agency) {
                $agencyId = $agency->nid;
                $agencyOrgId = $agency->field_organization_id[LANGUAGE_NONE][0]['value'];
                // deletes current agency data
                philgeps_central_api_delete_procurement_items($agencyId, $year, $month);
                // fetch new items for this agency
                $items = philgeps_central_api_fetch_procurement_items($agencyOrgId, $year, $month, $day);
                // gets agency responsible
                $authorId = 0;
                $agencyUids = philgeps_central_api_get_agency_users($agencyId);
                if (count($agencyUids)>0) {
                    // set first agency person as author
                    $authorId = $agencyUids[0];
                }
                foreach($items as $item) {
                    // import procurement item
                    $itemRes = philgeps_central_api_import_procurement_item($item, $agencyId, $authorId);
                    if ($itemRes) {
                        // increase the number of imported items
                        $totalImported++;
                    }
                }
            }
            watchdog('dgph_philgeps_api', "ending procurement items import from central database ($month $year).");
        }
        return $totalImported;
    }
    
    
        /**
     * Imports procurement items information from the PhilGEPS database to the PhilGEPS Dashboard
     * @param int $year the year to fetch items for (0 = this year)
     * @param int $month the month to fetch items for (0 = this month)
     * @param int $day the day to fetch items for (0 = whole month)
     * @return array the total number of successfully imported items
     */
    function philgeps_central_api_import_procurement_items_ckan($year = 0, $month = 0, $day = 0) {
        $totalImported = 0;
        if (0==$year) {
            // set current year
            $year = date('Y');
        }
        if (0==$month) {
            // set current month
            $month = date('n');
        }
        if ($year>0 && $month>0) {
            watchdog('dgph_philgeps_api', "starting procurement items import from ckan database ($month $year).");
            // fetch agencies
            $agencies = dgph_philgeps_api_get_agencies();
            foreach($agencies as $agency) {
                $agencyId = $agency->nid;
                $agencyOrgId = $agency->field_organization_id[LANGUAGE_NONE][0]['value'];
                // deletes current agency data
                philgeps_central_api_delete_procurement_items($agencyId, $year, $month);
                // fetch new items for this agency
                $items = philgeps_central_api_fetch_procurement_items_ckan($agencyOrgId, $year, $month, $day);
                // gets agency responsible
                $authorId = 0;
                $agencyUids = philgeps_central_api_get_agency_users($agencyId);
                if (count($agencyUids)>0) {
                    // set first agency person as author
                    $authorId = $agencyUids[0];
                }
                foreach($items as $item) {
                    // import procurement item
                    $itemRes = philgeps_central_api_import_procurement_item($item, $agencyId, $authorId);
                    if ($itemRes) {
                        // increase the number of imported items
                        $totalImported++;
                    }
                }
            }
            watchdog('dgph_philgeps_api', "ending procurement items import from ckan database ($month $year).");
        }
        return $totalImported;
    }
    
    
    /**
     * Parse a JSON date in .NET format
     * @param string $dt the source date
     * @return int the Unix timestamp corresponding to the parsed date
     */
    function philgeps_central_api_parse_json_date($dt) {
        $matches = array();
        preg_match( '/\/Date\((\d+)([+-]\d{4})\)/', $dt, $matches);
        $sdt = date('Y-m-d', $matches[1]/1000 );
        return strtotime($sdt);
    }   
    
    /**
     * Import a procurement item to the PhilGEPS dashboard
     * @param array $item the procurement item
     * @param int @agencyId agency identifier
     * @param int $authorId author identifier
     * @return boolean the operation result
     */
    function philgeps_central_api_import_procurement_item($item, $agencyId, $authorId) {
        $res = false;
        try {
            // creates the node
            $node = new stdClass();
            $node->type = "philgeps_procurement_item";
            node_object_prepare($node);
            if ($authorId>0) {
                $node->uid = $authorId;
            }
            $node->title = $item[CENTRAL_API_PI_BID_TITLE];
            $node->language = LANGUAGE_NONE;
            $node->field_agency[LANGUAGE_NONE][0]['target_id'] = $agencyId;
            $tm = philgeps_central_api_parse_json_date($item[CENTRAL_API_PI_DATE_POSTED]);
            $node->field_date_posted[LANGUAGE_NONE][0]['value'] = date("Y-m-d", $tm);
            $node->field_date_posted_year[LANGUAGE_NONE][0]['value'] = date("Y", $tm);
            $node->field_date_posted_month[LANGUAGE_NONE][0]['value'] = date("m", $tm);
            $node->field_bid_reference_number[LANGUAGE_NONE][0]['value'] = $item[CENTRAL_API_PI_BID_REFERENCE_NUMBER];
            $node->field_bid_classification[LANGUAGE_NONE][0]['value'] = $item[CENTRAL_API_PI_BID_CLASSIFICATION];
            $node->field_funding_source[LANGUAGE_NONE][0]['value'] = $item[CENTRAL_API_PI_FUNDING_SOURCE];
            $node->field_procurement_mode[LANGUAGE_NONE][0]['value'] = $item[CENTRAL_API_PI_PROCUREMENT_MODE];
            $node->field_approved_budget[LANGUAGE_NONE][0]['value'] = isset($item[CENTRAL_API_PI_APPROVED_BUDGET]) ? intval($item[CENTRAL_API_PI_APPROVED_BUDGET]) : 0;
            $node->field_bid_status[LANGUAGE_NONE][0]['value'] = $item[CENTRAL_API_PI_BID_STATUS];
            $tm = philgeps_central_api_parse_json_date($item[CENTRAL_API_PI_BID_STATUS_DATE]);
            $node->field_bid_status_date[LANGUAGE_NONE][0]['value'] = date("M d, Y", $tm);
            $node->field_bid_status_reason[LANGUAGE_NONE][0]['value'] = isset($item[CENTRAL_API_PI_BID_STATUS_REASON]) ? $item[CENTRAL_API_PI_BID_STATUS_REASON] : '';
            $node->field_number_of_bidders[LANGUAGE_NONE][0]['value'] = is_numeric($item[CENTRAL_API_PI_NUMBER_OF_BIDDERS]) ? intval($item[CENTRAL_API_PI_NUMBER_OF_BIDDERS]) : 0;
            $node->field_awardee[LANGUAGE_NONE][0]['value'] = isset($item[CENTRAL_API_PI_AWARDEE]) ? $item[CENTRAL_API_PI_AWARDEE] : '';
            $node->field_contract_amount[LANGUAGE_NONE][0]['value'] = is_numeric($item[CENTRAL_API_PI_CONTRACT_AMOUNT]) ? $item[CENTRAL_API_PI_CONTRACT_AMOUNT] : 0;
            $node->field_contract_info[LANGUAGE_NONE][0]['value'] = isset($item[CENTRAL_API_PI_AWARD_CONTRACT]) ? $item[CENTRAL_API_PI_AWARD_CONTRACT] : '';
            $node->field_award_id[LANGUAGE_NONE][0]['value'] = is_numeric($item[CENTRAL_API_PI_AWARD_ID]) ? $item[CENTRAL_API_PI_AWARD_ID] : 0;
            $node = node_submit($node);
            if($node) {
                node_save($node);
                $res = true;
            }
        }
        catch(Exception $e) {}
        return $res;
    }
?>