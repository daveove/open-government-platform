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


    function endsWith($haystack, $needle)
    {
        $length = strlen($needle);
        if ($length == 0) {
            return true;
        }

        return (substr($haystack, -$length) === $needle);
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
        watchdog('dgph_philgeps_api', "sid: ".$sid);
        if ($sid == null){
            watchdog('dgph_philgeps_api', "SID IS NULL");
        }

        if ($sid!=null) {
            // gets number of procurement items
            //$naked_url = 'http://ckan.urls.ph/api/action/datastore_search_sql?sql=SELECT%20*%20from%20"';
            $naked_url = 'http://data.gov.ph/catalogue/api/action/datastore_search_sql?sql=SELECT%20*%20from%20"';
        $fromDay = ($day>0) ? $day : 1;
            $fromMonth = $month;
            $toDay = ($day>0) ? ($day+1) : 0;
            $toMonth = ($day>0) ? $month : ($month+1);
            $fromDate = date("Y-m-d", mktime(0, 0, 0, $fromMonth, $fromDay, $year));
            /*$toDate = date("Y-m-d", mktime(0, 0, 0, $toMonth, $toDay, $year));*/
            $toDate = date("Y-m-d", mktime(0, 0, 0, $toMonth+1, $fromDay, $year));
            $reqOpts = array('timeout'=>60);
            
            $bid_information_resource_id = "9c74991c-a5e6-4489-8413-c20a8a181d90";
            $award_resource_id = "314aa773-e6e4-4554-80ce-4f588212e0d1";
            $bidders_lists_resource_id = "922f8c2c-8ef6-4e46-bc4e-8799c47b8ecf";
            $organization_resource_id = "23de10e9-197e-4294-abd1-eba0188110cd";

            $reqUrl = $naked_url.$bid_information_resource_id.'"%20WHERE%20publish_date%20>=%20%27'.$fromDate.'%27%20AND%20publish_date<=%27'.$toDate.'%27%20AND%20org_id%20=%20'.$orgId;
            watchdog('dgph_philgeps_api', "reqURL: ".$reqUrl);
            $bid_information_result = drupal_http_request($reqUrl, $reqOpts);

            $json_result = array();

            watchdog('dgph_philgeps_api', "($orgId) orgid response: ".$bid_information_result->code);

            if ($bid_information_result->code == HTTP_RESPONSE_OK) {
                // gets procurement items
                $bid_information_result_json = json_decode($bid_information_result->data, true);
                $bid_records = $bid_information_result_json["result"]["records"];

                if (!empty($bid_records)) {
                    // fetch award with refid == info refid
                    foreach($bid_records as $r) {
                        $bid_in_ref_id = $r["ref_id"];
                        /*$reqUrl1 = $naked_url.$award_resource_id.'&filters={"RefID":"'.$bid_in_ref_id.'"}';*/
                        $reqUrl1 = $naked_url.$award_resource_id.'"%20WHERE%20ref_id%20=%20%27'.$bid_in_ref_id.'%27';
                        watchdog('dgph_philgeps_api', "reqURL: ".$reqUrl);
                        $award_result = drupal_http_request($reqUrl1, $reqOpts);
                        watchdog('dgph_philgeps_api', "($bid_in_ref_id) award response: ".$award_result->code);

                        if($r["publish_date"] != null){
                            $postedTimestamp = strtotime($r["publish_date"]);
                            $postedTimestampStr = (string)$postedTimestamp;
                            $postedTimestampDate = "\/Date(".$postedTimestampStr."000+0800)\/";
                            $r["publish_date"] = $postedTimestampDate;
                        }
                        
                        if($r["closing_date"] != null){
                            $postedTimestamp = strtotime($r["closing_date"]);
                            $postedTimestampStr = (string)$postedTimestamp;
                            $postedTimestampDate = "\/Date(".$postedTimestampStr."000+0800)\/";
                            $r["closing_date"] = $postedTimestampDate;
                        }
                        
                        if ($award_result->code == HTTP_RESPONSE_OK) {

                            $award_result_json = json_decode($award_result->data, true);
                            $awards = $award_result_json["result"]["records"];

                            foreach($awards as $award_record) {
                                $award_id = null;
                                $awardee_id = null;
                                $contractAmt = null;
                                $contractBudget = $r["approved_budget"];
                                $awardee = "";

                                if($award_record["item_name"] && $award_record["line_item_id"] != null){
                                    $bidTitle = $r["tender_title"].' - '.$award_record["line_item_id"].' - '.$award_record["item_name"];
                                }
                                else {
                                    $bidTitle = $r["tender_title"];
                                }

                                $award_id = $award_record["award_id"];
                                $awardee_id = $award_record["awardee_id"];
                                $contractAmt = $award_record["contract_amt"];
                                if ($award_record["budget"]){
                                    $contractBudget = $award_record["budget"];
                                }
                                $awardee = $award_record["awardee"];

                                $bidders_count = 0;
                                if($award_id != null){
                                    // fetch bidders lists awardID == award awardID
                                    /*$reqUrl2 = $naked_url.$bidders_lists_resource_id.'&filters={"AwardID":"'.$award_id.'"}';*/
                                    $reqUrl2 = $naked_url.$bidders_lists_resource_id.'"%20WHERE%20award_id%20=%20%27'.$award_id.'%27';
                                    $bidders_lists_result = drupal_http_request($reqUrl2, $reqOpts);
                                    watchdog('dgph_philgeps_api', "($award_id) award id response: ".$bidders_lists_result->code);
                                    if ($bidders_lists_result->code == HTTP_RESPONSE_OK) {
                                        $bidders_lists_result_json = json_decode($bidders_lists_result->data, true);
                                        $bidders_count = count($bidders_lists_result_json["result"]["records"]);
                                    }
                                }

                                $address_string = "";
                                // fetch organization orgid == awardID
                                /*$reqUrl3 = $naked_url.$organization_resource_id.'&filters={"OrgID":"'.$awardee_id.'"}';*/
                                $reqUrl3 = $naked_url.$organization_resource_id.'"%20WHERE%20org_id%20=%20%27'.$awardee_id.'%27';
                                $organizations_result = drupal_http_request($reqUrl3, $reqOpts);
                                watchdog('dgph_philgeps_api', "($awardee_id) awardee id response: ".$organizations_result->code);
                                if ($organizations_result->code == HTTP_RESPONSE_OK) {
                                    // check if organization has result
                                    $organizations_result_json = json_decode($organizations_result->data, true);
                                    $org_count = $organizations_result_json["result"]["records"];
                                    if (!empty($org_count)) {
                                        $add1 = $org_count[0]["address1"];
                                        $add2 = $org_count[0]["address2"];
                                        $add3 = $org_count[0]["address3"];
                                        $org_city = $org_count[0]["city"];
                                        $org_province = $org_count[0]["province"];
                                        $org_country = $org_count[0]["country"];
                                        
                                        if($add1 != ''){
                                            if($address_string == ''){
                                                $address_string = $address_string." -";
                                            }
                                            if($address_string == ' -'){
                                                $address_string = $address_string." ".$add1;   
                                            }
                                            else {
                                                if(endsWith($address_string, ",")){
                                                    $address_string = $address_string." ".$add1;   
                                                }
                                                else {
                                                    $address_string = $address_string.", ".$add1;   
                                                }
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
                                                if(endsWith($address_string, ",")){
                                                    $address_string = $address_string." ".$add2;   
                                                }
                                                else {
                                                    $address_string = $address_string.", ".$add2;   
                                                }
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
                                                if(endsWith($address_string, ",")){
                                                    $address_string = $address_string." ".$add3; 
                                                }
                                                else {
                                                    $address_string = $address_string.", ".$add3;   
                                                }  
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
                                                if(endsWith($address_string, ",")){
                                                    $address_string = $address_string." ".$org_city;  
                                                }
                                                else {
                                                    $address_string = $address_string.", ".$org_city;  
                                                }  
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
                                                if(endsWith($address_string, ",")){
                                                    $address_string = $address_string." ".$org_province; 
                                                }
                                                else {
                                                    $address_string = $address_string.", ".$org_province; 
                                                }  
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
                                                if(endsWith($address_string, ",")){
                                                    $address_string = $address_string." ".$org_country;   
                                                }
                                                else {
                                                    $address_string = $address_string.", ".$org_country;   
                                                }  
                                            }
                                        }
                                    }
                                }
                                
                                if(is_string($r["approved_budget"])){
                                    $r["approved_budget"] = (float) $r["approved_budget"];
                                }
                                if(is_string($award_id)){
                                    $award_id = (int) $award_id;
                                }
                                if(is_string($contractAmt)){
                                    $contractAmt = (float) $contractAmt;
                                }
                                
                                # set json data
                                $json_content = array(
                                    'Approved_Budget'=> $contractBudget,
                                    'AwardID'=> $award_id,
                                    'Awardee'=> $awardee.$address_string,
                                    'BidNum'=> $r["ref_id"],
                                    'Bid_Classification'=> $r["classification"],
                                    'Bid_Status'=> $r["tender_status"],
                                    'Bid_Status_Date'=> $r["closing_date"],
                                    'Bid_Title'=> $bidTitle,
                                    'Contract_Amount'=> $contractAmt,
                                    'Date_Posted'=> $r["publish_date"],
                                    'Funding_Source'=> $r["funding_source"],
                                    'Num_Bidders'=> $bidders_count,
                                    'Procurement_Mode'=> $r["procurement_mode"],
                                    'Status_Reason'=> $r["reason"]
                                );
                                # save to lists
                                $json_result[] = $json_content;

                            }
                        }
                    }

                    if ($json_result > 0) {
                        foreach($json_result as $proc) {
                            try {
                                // gets procurement documents information
                                // $awardID = $proc[CENTRAL_API_PI_AWARD_ID];
                                $awardID = $proc["award_id"];
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
    function philgeps_central_api_fetch_procurement_items_ckan2($offset) {
        $items = array();
        // gets number of procurement items
        //$naked_url = 'http://ckan.urls.ph/api/action/datastore_search_sql?sql=SELECT%20*%20from%20"';
        $naked_url = 'http://data.gov.ph/catalogue/api/action/datastore_search_sql?sql=SELECT%20*%20from%20"';
        
        $reqOpts = array('timeout'=>60);
        
        $bid_information_resource_id = "9c74991c-a5e6-4489-8413-c20a8a181d90";
        $award_resource_id = "314aa773-e6e4-4554-80ce-4f588212e0d1";
        $bidders_lists_resource_id = "922f8c2c-8ef6-4e46-bc4e-8799c47b8ecf";
        $organization_resource_id = "23de10e9-197e-4294-abd1-eba0188110cd";

        if($offset>0){
            $reqUrl = $naked_url.$bid_information_resource_id.'"%20limit%202%20offset%20'.$offset;
        }
        else {
            $reqUrl = $naked_url.$bid_information_resource_id.'"%20limit%201000';
        }
        watchdog('dgph_philgeps_api', "reqURL: ".$reqUrl);
        $bid_information_result = drupal_http_request($reqUrl, $reqOpts);

        $json_result = array();

        if ($bid_information_result->code == HTTP_RESPONSE_OK) {
            // gets procurement items
            $bid_information_result_json = json_decode($bid_information_result->data, true);
            $bid_records = $bid_information_result_json["result"]["records"];

            if (!empty($bid_records)) {
                // fetch award with refid == info refid
                foreach($bid_records as $r) {
                    $bid_in_ref_id = $r["ref_id"];
                    /*$reqUrl1 = $naked_url.$award_resource_id.'&filters={"RefID":"'.$bid_in_ref_id.'"}';*/
                    $reqUrl1 = $naked_url.$award_resource_id.'"%20WHERE%20ref_id%20=%20%27'.$bid_in_ref_id.'%27';
                    watchdog('dgph_philgeps_api', "reqURL2: ".$reqUrl1);
                    $award_result = drupal_http_request($reqUrl1, $reqOpts);
                    /*watchdog('dgph_philgeps_api', "($bid_in_ref_id) award response: ".$award_result->code);*/

                    if($r["publish_date"] != null){
                        $postedTimestamp = strtotime($r["publish_date"]);
                        $postedTimestampStr = (string)$postedTimestamp;
                        $postedTimestampDate = "\/Date(".$postedTimestampStr."000+0800)\/";
                        $r["publish_date"] = $postedTimestampDate;
                    }
                    
                    if($r["closing_date"] != null){
                        $postedTimestamp = strtotime($r["closing_date"]);
                        $postedTimestampStr = (string)$postedTimestamp;
                        $postedTimestampDate = "\/Date(".$postedTimestampStr."000+0800)\/";
                        $r["closing_date"] = $postedTimestampDate;
                    }
                    
                    if ($award_result->code == HTTP_RESPONSE_OK) {

                        $award_result_json = json_decode($award_result->data, true);
                        $awards = $award_result_json["result"]["records"];

                        foreach($awards as $award_record) {
                            $award_id = null;
                            $awardee_id = null;
                            $contractAmt = null;
                            $contractBudget = $r["approved_budget"];
                            $awardee = "";

                            if($award_record["item_name"] && $award_record["line_item_id"] != null){
                                $bidTitle = $r["tender_title"].' - '.$award_record["line_item_id"].' - '.$award_record["item_name"];
                            }
                            else {
                                $bidTitle = $r["tender_title"];
                            }

                            $award_id = $award_record["award_id"];
                            $awardee_id = $award_record["awardee_id"];
                            $contractAmt = $award_record["contract_amt"];
                            if ($award_record["budget"]){
                                $contractBudget = $award_record["budget"];
                            }
                            $awardee = $award_record["awardee"];

                            $bidders_count = 0;
                            if($award_id != null){
                                // fetch bidders lists awardID == award awardID
                                /*$reqUrl2 = $naked_url.$bidders_lists_resource_id.'&filters={"AwardID":"'.$award_id.'"}';*/
                                $reqUrl2 = $naked_url.$bidders_lists_resource_id.'"%20WHERE%20award_id%20=%20%27'.$award_id.'%27';
                                $bidders_lists_result = drupal_http_request($reqUrl2, $reqOpts);
                                /*watchdog('dgph_philgeps_api', "($award_id) award id response: ".$bidders_lists_result->code);*/
                                if ($bidders_lists_result->code == HTTP_RESPONSE_OK) {
                                    $bidders_lists_result_json = json_decode($bidders_lists_result->data, true);
                                    $bidders_count = count($bidders_lists_result_json["result"]["records"]);
                                }
                            }

                            $address_string = "";
                            // fetch organization orgid == awardID
                            /*$reqUrl3 = $naked_url.$organization_resource_id.'&filters={"OrgID":"'.$awardee_id.'"}';*/
                            $reqUrl3 = $naked_url.$organization_resource_id.'"%20WHERE%20org_id%20=%20%27'.$awardee_id.'%27';
                            $organizations_result = drupal_http_request($reqUrl3, $reqOpts);
                            /*watchdog('dgph_philgeps_api', "($awardee_id) awardee id response: ".$organizations_result->code);*/
                            if ($organizations_result->code == HTTP_RESPONSE_OK) {
                                // check if organization has result
                                $organizations_result_json = json_decode($organizations_result->data, true);
                                $org_count = $organizations_result_json["result"]["records"];
                                if (!empty($org_count)) {
                                    $add1 = $org_count[0]["address1"];
                                    $add2 = $org_count[0]["address2"];
                                    $add3 = $org_count[0]["address3"];
                                    $org_city = $org_count[0]["city"];
                                    $org_province = $org_count[0]["province"];
                                    $org_country = $org_count[0]["country"];
                                    
                                    if($add1 != ''){
                                        if($address_string == ''){
                                            $address_string = $address_string." -";
                                        }
                                        if($address_string == ' -'){
                                            $address_string = $address_string." ".$add1;   
                                        }
                                        else {
                                            if(endsWith($address_string, ",")){
                                                $address_string = $address_string." ".$add1;   
                                            }
                                            else {
                                                $address_string = $address_string.", ".$add1;   
                                            }
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
                                            if(endsWith($address_string, ",")){
                                                $address_string = $address_string." ".$add2;   
                                            }
                                            else {
                                                $address_string = $address_string.", ".$add2;   
                                            }
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
                                            if(endsWith($address_string, ",")){
                                                $address_string = $address_string." ".$add3; 
                                            }
                                            else {
                                                $address_string = $address_string.", ".$add3;   
                                            }  
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
                                            if(endsWith($address_string, ",")){
                                                $address_string = $address_string." ".$org_city;  
                                            }
                                            else {
                                                $address_string = $address_string.", ".$org_city;  
                                            }  
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
                                            if(endsWith($address_string, ",")){
                                                $address_string = $address_string." ".$org_province; 
                                            }
                                            else {
                                                $address_string = $address_string.", ".$org_province; 
                                            }  
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
                                            if(endsWith($address_string, ",")){
                                                $address_string = $address_string." ".$org_country;   
                                            }
                                            else {
                                                $address_string = $address_string.", ".$org_country;   
                                            }  
                                        }
                                    }
                                }
                            }
                            
                            if(is_string($r["approved_budget"])){
                                $r["approved_budget"] = (float) $r["approved_budget"];
                            }
                            if(is_string($award_id)){
                                $award_id = (int) $award_id;
                            }
                            if(is_string($contractAmt)){
                                $contractAmt = (float) $contractAmt;
                            }
                            
                            # set json data
                            $json_content = array(
                                'Approved_Budget'=> $contractBudget,
                                'AwardID'=> $award_id,
                                'Awardee'=> $awardee.$address_string,
                                'BidNum'=> $r["ref_id"],
                                'Bid_Classification'=> $r["classification"],
                                'Bid_Status'=> $r["tender_status"],
                                'Bid_Status_Date'=> $r["closing_date"],
                                'Bid_Title'=> $bidTitle,
                                'Contract_Amount'=> $contractAmt,
                                'Date_Posted'=> $r["publish_date"],
                                'Funding_Source'=> $r["funding_source"],
                                'Num_Bidders'=> $bidders_count,
                                'Procurement_Mode'=> $r["procurement_mode"],
                                'OrgID'=> $r["org_id"],
                                'Status_Reason'=> $r["reason"]
                            );
                            # save to lists
                            $json_result[] = $json_content;

                        }
                    }
                }

                /*if ($json_result > 0) {
                    foreach($json_result as $proc) {
                        try {
                            // gets procurement documents information
                            // $awardID = $proc[CENTRAL_API_PI_AWARD_ID];
                            $awardID = $proc["award_id"];
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
                }*/
            }
        }
        else {
            watchdog('dgph_philgeps_api', "error");
            watchdog('dgph_philgeps_api', $bid_information_result->code );
        }
        return $items;
    }

    
    /**
     * Deletes procurement items for an agency
     * @param int $agencyId the agency node identifier
     * @param int $year the year to fetch items for
     * @param int $month the month to fetch items for
     */
    function philgeps_central_api_delete_procurement_items($agencyId, $year, $month, $day) {
        $query= new EntityFieldQuery();

        /*if($day != 0){
            $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', 'philgeps_procurement_item')
                    ->propertyCondition('status', 1)
                    ->fieldCondition('field_agency', 'target_id', $agencyId)
                    ->fieldCondition('field_date_posted', 'value', $year.'-'.$month.'-'.$day);
        }
        else {*/
        $query->entityCondition('entity_type', 'node')
                ->entityCondition('bundle', 'philgeps_procurement_item')
                ->propertyCondition('status', 1)
                ->fieldCondition('field_agency', 'target_id', $agencyId)
                ->fieldCondition('field_date_posted_year', 'value', $year)
                ->fieldCondition('field_date_posted_month', 'value', $month);
        /*}*/

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
            watchdog('dgph_philgeps_api', "starting procurement items import from central database ($month $year $day).");
            // fetch agencies
            $agencies = dgph_philgeps_api_get_agencies();
            foreach($agencies as $agency) {
                $agencyId = $agency->nid;
                $agencyOrgId = $agency->field_organization_id[LANGUAGE_NONE][0]['value'];
                // deletes current agency data
                philgeps_central_api_delete_procurement_items($agencyId, $year, $month, $day);
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
            watchdog('dgph_philgeps_api', "ending procurement items import from central database ($month $year $day).");
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
            watchdog('dgph_philgeps_api', "starting procurement items import from ckan database ($day $month $year).");
            // fetch agencies
            $agencies = dgph_philgeps_api_get_agencies();
            foreach($agencies as $agency) {
                $agencyId = $agency->nid;
                $agencyOrgId = $agency->field_organization_id[LANGUAGE_NONE][0]['value'];
                // deletes current agency data
                philgeps_central_api_delete_procurement_items($agencyId, $year, $month, $day);
                // fetch new items for this agency
                watchdog('dgph_philgeps_api', "starting procurement items import from central database of organization ($agencyOrgId).");
                $items = philgeps_central_api_fetch_procurement_items_ckan($agencyOrgId, $year, $month, $day);

                watchdog('dgph_philgeps_api', var_export($items, true));
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
            watchdog('dgph_philgeps_api', "ending procurement items import from ckan database ($day $month $year).");
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
    function philgeps_central_api_import_procurement_items_ckan2($offset) {
        /*$offset = (int)str_replace(' ', '', $offset);*/
        $totalImported = 0;
        
        /*watchdog('dgph_philgeps_api', "starting procurement items import from ckan database ($day $month $year).");*/
        // fetch agencies
        
        // deletes current agency data
        /*philgeps_central_api_delete_procurement_items($agencyId, $year, $month, $day);*/
        // fetch new items for this agency
        /*watchdog('dgph_philgeps_api', "starting procurement items import from central database of organization ($agencyOrgId).");*/
        $items = array();
        $row = 0;
        $filename = '/var/www/dgph/procurement_item_csv/tender'.$offset.'.csv';
        watchdog('dgph_philgeps_api', $filename);
        if (($handle = fopen($filename, "r")) !== FALSE) {
            while (($data = fgetcsv($handle)) !== FALSE) {
                $row++;

                $contractBudget = (float) (0);

                if(!empty($data[2])){
                    $contractBudget = (float) $data[2];
                }

                if(!empty($data[13])){
                    $contractBudget = (float) $data[13];
                }

                $award_id = '';
                if(!empty($data[18])){
                    $award_id = $data[18];
                }

                $awardee = "";
                if(!empty($data[15])){
                    $awardee = $data[15];
                }

                $address_string = '';
                if(!empty($data[16])){
                    $text = preg_replace("/[\r\n]+/", ", ", $data[16]);
                    $address_string = ' - '.$text;
                }

                $ref_id = $data[5];

                $classification = "null";
                if(!empty($data[6])){
                    $classification = $data[6];
                }

                $tender_status = "Pending";
                if(!empty($data[7])){
                    $tender_status = $data[7];
                }

                $closing_date = "";
                if(!empty($data[8])){
                    $closing_date = $data[8];
                }

                $bidTitle = "";
                if(!empty($data[1])){
                    $bidTitle = $data[1];
                }

                $contractAmt = (float) (0);
                if(!empty($data[17])){
                    $contractAmt = (float)$data[17];
                }

                $date_posted = "";
                if(!empty($data[4])){
                    $date_posted = $data[4];
                }

                $funding_source = "";
                if(!empty($data[10])){
                    $funding_source = $data[10];
                }

                $bidders_count = 0;
                if(!empty($data[14])){
                    $bidders_count = $data[14];
                }

                $procurement_mode = "null";
                if(!empty($data[3])){
                    $procurement_mode = $data[3];
                }

                $reason = "";
                if(!empty($data[9])){
                    $reason = $data[9];
                }

                $region = "";
                if(!empty($data[19])){
                    $region = $data[19];
                }

                $province = "";
                if(!empty($data[20])){
                    $province = $data[20];
                }

                $municipality = "";
                if(!empty($data[21])){
                    $municipality = $data[21];
                }

                $json_content = array(
                    'Approved_Budget'=> $contractBudget,
                    'AwardID'=> $award_id,
                    'Awardee'=> $awardee.$address_string,
                    'OrgID'=> $data[0],
                    'region'=> $region,
                    'province'=> $province,
                    'municipality'=> $municipality,
                    'BidNum'=> $ref_id,
                    'Bid_Classification'=> $classification,
                    'Bid_Status'=> $tender_status,
                    'Bid_Status_Date'=> $closing_date,
                    'Bid_Title'=> $bidTitle,
                    'Contract_Amount'=> $contractAmt,
                    'Date_Posted'=> $date_posted,
                    'Funding_Source'=> $funding_source,
                    'Num_Bidders'=> $bidders_count,
                    'Procurement_Mode'=> $procurement_mode,
                    'Status_Reason'=> $reason
                );

                $items[] = $json_content;
            }
            fclose($handle);
        }

        /*watchdog('dgph_philgeps_api', var_export($items, true));*/
        // gets agency responsible
        $authorId = 0;
        /*$agencyUids = philgeps_central_api_get_agency_users($agencyId);*/
        /*if (count($agencyUids)>0) {
            // set first agency person as author
            $authorId = $agencyUids[0];
        }*/
        foreach($items as $item) {
            // import procurement item
            $itemRes = philgeps_central_api_import_procurement_item_ckan2($item);
            if ($itemRes) {
                // increase the number of imported items
                $totalImported++;
            }
        }

        watchdog('dgph_philgeps_api', $totalImported);
        /*watchdog('dgph_philgeps_api', "ending procurement items import from ckan database ($day $month $year).");*/
        return $totalImported;
    }
    
    
    /**
     * Parse a JSON date in .NET format
     * @param string $dt the source date
     * @return int the Unix timestamp corresponding to the parsed date
     */
    function philgeps_central_api_parse_json_date($dt) {
        /*$matches = array();
        preg_match( '/\/Date\((\d+)([+-]\d{4})\)/', $dt, $matches);*/
        /*$sdt = date('Y-m-d', $dt);*/
        return strtotime($dt);
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
            watchdog('dgph_philgeps_api_node', var_export($node, true));
            if($node) {
                node_save($node);
                $res = true;
                watchdog('dgph_philgeps_api_SAVED', var_export($node, true));
            }
        }
        catch(Exception $e) {
            watchdog('dgph_philgeps_api_EXCEPTION', var_export($e, true));
        }
        return $res;
    }

    /**
     * Import a procurement item to the PhilGEPS dashboard
     * @param array $item the procurement item
     * @param int @agencyId agency identifier
     * @param int $authorId author identifier
     * @return boolean the operation result
     */
    function philgeps_central_api_import_procurement_item_ckan2($item) {
        $res = false;

        /*watchdog('dgph_philgeps_api_node_item', var_export($item, true));*/

        try {
            // creates the node
            $node = new stdClass();
            $node->type = "philgeps_procurement_item";
            node_object_prepare($node);
            
            $node->title = $item[CENTRAL_API_PI_BID_TITLE];
            $node->language = LANGUAGE_NONE;
            /*$node->field_agency[LANGUAGE_NONE][0]['target_id'] = $agencyId;*/
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
            $node->field_orgid[LANGUAGE_NONE][0]['value'] = $item['OrgID'];
            $node->field_region[LANGUAGE_NONE][0]['value'] = $item['region'];
            $node->field_province[LANGUAGE_NONE][0]['value'] = $item['province'];
            $node->field_municipality[LANGUAGE_NONE][0]['value'] = $item['municipality'];
            $node = node_submit($node);
            /*watchdog('dgph_philgeps_api_node', var_export($node, true));*/
            if($node) {
                node_save($node);
                $res = true;
                /*watchdog('dgph_philgeps_api_SAVED', var_export($node, true));*/
            }
        }
        catch(Exception $e) {
            watchdog('dgph_philgeps_api_EXCEPTION', var_export($e, true));
        }
        return $res;
    }
?>
