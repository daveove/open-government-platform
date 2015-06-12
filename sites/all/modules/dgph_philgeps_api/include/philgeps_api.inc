<?php
    /**
     * Procurement item format
     */
    define('PI_ITEM_ID', 'item_id');
    define('PI_TITLE', 'title');
    define('PI_AGENCY_ID', 'agency_id');
    define('PI_BID_REFERENCE_NUMBER', 'bid_reference_number');
    define('PI_DATE_POSTED', 'date_posted');
    define('PI_BID_CLASSIFICATION', 'bid_classification');
    define('PI_APPROVED_BUDGET', 'approved_budget');
    define('PI_FUNDING_SOURCE', 'funding_source');
    define('PI_PROCUREMENT_MODE', 'procurement_mode');
    define('PI_BID_STATUS', 'bid_status');
    define('PI_BID_STATUS_DATE', 'bid_status_date');
    define('PI_BID_STATUS_REASON', 'bid_status_reason');
    define('PI_NUMBER_OF_BIDDERS', 'number_of_bidders');
    define('PI_AWARDEE', 'awardee');
    define('PI_CONTRACT_AMOUNT', 'contract_amount');


    /**
     * Callback for creating procurement items
     * @param object $item the procurement item information
     * @return object the item identifier and access URL
     */
    function _procurement_item_create($item) {
        // check parameters
        if (!isset($item[PI_TITLE])) {
            return services_error('Missing bid title', 406);
        }
        if (!isset($item[PI_AGENCY_ID])) {
            return services_error('Missing agency identifier', 406);
        }
        if (!isset($item[PI_BID_REFERENCE_NUMBER])) {
            return services_error('Missing bid reference number', 406);
        }
        if (!isset($item[PI_DATE_POSTED])) {
            return services_error('Missing date posted', 406);
        }
        if (!isset($item[PI_BID_CLASSIFICATION])) {
            return services_error('Missing bid classification', 406);
        }
        if (!isset($item[PI_APPROVED_BUDGET])) {
            return services_error('Missing approved budget', 406);
        }
        if (!isset($item[PI_FUNDING_SOURCE])) {
            return services_error('Missing funding source', 406);
        }
        if (!isset($item[PI_PROCUREMENT_MODE])) {
            return services_error('Missing procurement mode', 406);
        }       
        if (!isset($item[PI_BID_STATUS])) {
            return services_error('Missing bid status', 406);
        }
        if (!isset($item[PI_BID_STATUS_DATE])) {
            return services_error('Missing bid status date', 406);
        }
        if (!isset($item[PI_BID_STATUS_REASON])) {
            return services_error('Missing bid status reason', 406);
        }
        if (!isset($item[PI_NUMBER_OF_BIDDERS])) {
            return services_error('Missing number of bidders', 406);
        }
        if (!isset($item[PI_AWARDEE])) {
            return services_error('Missing awardee', 406);
        }
        if (!isset($item[PI_CONTRACT_AMOUNT])) {
            return services_error('Missing contract amount', 406);
        }
        // create item
        $itemId = dgph_philgeps_api_write_item($item);
        return (object)array('id' => $itemId);
    }
    
    /**
     * Callback for updating procurement items
     * @param int $id identifier of the procurement item to update
     * @param object $item the procurement item information
     * @return object the item identifier and access URL
     */
    function _procurement_item_update($id, $item) {
        // check it this item exists
        $itemId = 0;
        $curItem = dgph_philgeps_api_get_item($id);
        if ($curItem!=null) {
            // updates item
            $item['id'] = $id;
            $itemId = dgph_philgeps_api_write_item($item);
        }
        return (object)array('id' => $itemId);
    }
    /**
     * Callback for retrieving procurement items
     * @param int $id the procurement item identifier
     * @return object the procurement item
     */
    function _procurement_item_retrieve($id) {
        return dgph_philgeps_api_get_item($id);
    }
    /**
     * Callback for deleting procurement items
     * @param int $id the procurement item identifier
     * @return object the identifier of the deleted item
     */
    function _procurement_item_delete($id) {
        dgph_philgeps_api_delete_item($id);
        return (object)array('id' => $id);
    }
     /**
      * Callback for listing procurement items
      * @param int $page the requested page number
      * @param array $params request parameters
      * @return array the list of procurement items
      */
    function _procurement_item_list($page, $params) {
        if ($page<1) {
            return services_error('Page number must be a positive integer', 406);
        }
        return dgph_philgeps_api_fetch($page, $params);
    }
?>