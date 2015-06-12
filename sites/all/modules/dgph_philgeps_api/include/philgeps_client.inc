<?php
    define('DGPH_PHILGEPS_API_RESOURCE_ENDPOINT', '/philgeps/api');
    define('DGPH_PHILGEPS_API_SESSION_TOKEN_ENDPOINT', '/services/session/token');
    define('API_LOGIN', 'testagency');
    define('API_PASSWORD', '$igma_94');
    
    /**
     * Sends a request to the PhilGEPS API
     * @param string $username the name of user sending the request
     * @param string $password the user password
     * @param array $params the request parameters
     * @return the server response, in JSON format
     */
    function philgeps_send_request($username, $password, $params) {
        $out = '';
        $reqParams = array(
                'username' => $username,
                'password' => $password
            );
        $reqData = http_build_query($reqParams, '', '&');
        $reqOpts = array(
            'method' => 'POST',
            'data' => $reqData
        );
        global $base_url;
        $reqUrl = $base_url.DGPH_PHILGEPS_API_RESOURCE_ENDPOINT.'/user/login';
        $resp = drupal_http_request($reqUrl, $reqOpts);
        if ($resp->code == 200) {
            // build the login cookie
            $respData = json_decode($resp->data);
            $cookie = $respData->session_name . '=' . $respData->sessid;
            // sends a request for the login token
            $reqOpts = array(
                'method' => 'GET',
                'headers' => array('Cookie' => $cookie)
            );
            $reqUrl = $base_url.DGPH_PHILGEPS_API_SESSION_TOKEN_ENDPOINT;
            $resp = drupal_http_request($reqUrl, $reqOpts);
            if ($resp->code == 200) {
                // gets the session token
                $token = $resp->data;
                // sends the request
                $reqFields = isset($params['fields']) ? $params['fields'] : array();
                $reqOpts = array(
                            'method' => isset($params['method']) ? $params['method'] : 'GET',
                            'headers' => array(
                                        'Cookie' => $cookie,
                                        'X-CSRF-Token' => $token
                                    ),
                            'data' => http_build_query($reqFields, '', '&')
                        );
                $reqUrl = $base_url.DGPH_PHILGEPS_API_RESOURCE_ENDPOINT.'/procurement_item';
                if (isset($params[PI_ITEM_ID])) {
                    $reqUrl .= '/'.$params[PI_ITEM_ID].'.json';
                }
                $resp = drupal_http_request($reqUrl, $reqOpts);
                $out = $resp->data;
            }
            else {
               $out = json_encode(array($resp->error));
            }
        }
        else {
            $out = json_encode(array($resp->error));
        }
        return $out;
    }
    
    /**
     * Provides test functions for REST client
     * @param string $action the CRUD action to be tested
     */
    function dgph_philgeps_api_example_client($action = 'read') {
        $params = array();
        switch($action) {
            case 'create':
                $params['method'] = 'POST';
                $params['fields'] = array(
                        PI_TITLE => 'This is test for Services API',
                        PI_AGENCY_ID => 136,    // Department of Agrarian Reform
                        PI_BID_REFERENCE_NUMBER => '2505821',
                        PI_DATE_POSTED => 'Dec 24, 2013',
                        PI_BID_CLASSIFICATION => 'Goods',
                        PI_APPROVED_BUDGET => '280000',
                        PI_FUNDING_SOURCE => 'Government of the Philippines (GOP)',
                        PI_PROCUREMENT_MODE => 'Test',
                        PI_BID_STATUS => 'Closed',
                        PI_BID_STATUS_DATE => 'Dec 24, 2013',
                        PI_BID_STATUS_REASON => 'This is a test',
                        PI_NUMBER_OF_BIDDERS => 0,
                        PI_AWARDEE => '',
                        PI_CONTRACT_AMOUNT => 0
                    );
                break;
            case 'read':
                $params['method'] = 'GET';
                $params[PI_ITEM_ID] = isset($_GET['id']) ? $_GET['id'] : '0';
                break;
            case 'update':
                $params['method'] = 'PUT';
                $params[PI_ITEM_ID] = isset($_GET['id']) ? $_GET['id'] : '0';
                $params['fields'] = array(
                        PI_TITLE => 'This is test for Services API (UPDATED)',
                        PI_PROCUREMENT_MODE => 'Test (UPDATED)',
                        PI_BID_STATUS_REASON => 'This is a test (UPDATED)'
                    );
                break;
            case 'delete':
                $params['method'] = 'DELETE';
                $params[PI_ITEM_ID] = isset($_GET['id']) ? $_GET['id'] : '0';
                break;
            case 'list':
                $params['method'] = 'GET';
                $params['query'] = array('page' => 1);
                break;
        }
        $out = philgeps_send_request(API_LOGIN, API_PASSWORD, $params);
        echo $out;
        drupal_exit();
    }
?>