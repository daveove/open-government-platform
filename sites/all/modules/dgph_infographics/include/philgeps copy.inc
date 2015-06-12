<?php
    define('PHILGEPS_WORKFLOW_CREATED', 1);
    define('PHILGEPS_WORKFLOW_DRAFT', 2);
    define('PHILGEPS_WORKFLOW_APPROVED', 3);
    define('PHILGEPS_WORKFLOW_DECLINED', 4);
    
    define('PHILGEPS_IMPORT_BID_NUMBER', 0);
    define('PHILGEPS_IMPORT_DATE_POSTED', 1);
    define('PHILGEPS_IMPORT_BID_CLASSIFICATION', 2);
    define('PHILGEPS_IMPORT_PROCUREMENT_MODE', 3);
    define('PHILGEPS_IMPORT_BID_TITLE', 4);
    define('PHILGEPS_IMPORT_APPROVED_BUDGET', 5);
    define('PHILGEPS_IMPORT_BID_STATUS', 6);
    define('PHILGEPS_IMPORT_BID_STATUS_DATE', 7);
    define('PHILGEPS_IMPORT_AWARDEE', 8);
    define('PHILGEPS_IMPORT_CONTRACT_AMOUNT', 9);
    define('PHILGEPS_IMPORT_FUNDING_SOURCE', 10);
    define('PHILGEPS_IMPORT_NUMBER_OF_BIDDERS', 11);
    define('PHILGEPS_IMPORT_BID_STATUS_REASON', 12);
    
    define('PHILGEPS_ROLE_AGENCY', 4);
    
    define('PHILGEPS_CONTRACT_AWARD_ID', "award_id");
    define('PHILGEPS_CONTRACT_DOCUMENT_TYPE', "document_type");
    define('PHILGEPS_CONTRACT_DOCUMENT_NAME', "document_name");
    define('PHILGEPS_CONTRACT_DOCUMENT_URL', "document_url");
    define('PHILGEPS_CONTRACT_FILE_EXISTS', "file_exists");
        
    /**
     *  Import PhilGEPS form
     */
    function dgph_infographics_philgeps_import_form() {
        $form = array();
        drupal_set_title("Update Data");
        $form['#attributes'] = array('class' => array('dashboard'));
        $form['year'] = array(
                '#type' => 'textfield',
                '#title' => 'Enter Year',
                '#attributes' => array(
                        'name' => 'year',
                        'class' => array('number')
                    )
              );
        $form['month'] = array(
            '#type' => 'select',
            '#title' => 'Select Month',
            '#options' => array('', 'January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December')
          );
        $form['day'] = array(
            '#type' => 'select',
            '#title' => 'Select Day',
            '#options' => array(0=>'Select Day', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '31')
          );
        $form['submit'] = array(
            '#value' => t('Update'),
            '#type' => 'submit'
        );        
        return $form;    
    }
    
    /**
     *  Validator for import PhilGEPS data form
     */
    function dgph_infographics_philgeps_import_form_validate($form, &$form_state) {
        $year = $form_state['input']['year'];
        $minYear = 2010;
        $maxYear = date("Y");
        if ((null==$year) || !is_numeric($year) || intval($year)<$minYear || intval($year)>$maxYear) {
            form_set_error('year', t("Year must be an integer value in the range $minYear - $maxYear."));
        }
        $month = $form_state['input']['month'];
        if (empty($month)) {
            form_set_error('month', t("Please select the month you want to update data for."));
        }
    }
    
    /**
     * Gets the user(s) belonging to a government agency
     * @param int $agencyId the agency identifiers
     * @return array identifiers of users belonging to the agency
     */
    function dgph_infographics_get_agency_users($agencyId) {
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
     *  Handler for PhilGEPS form submit
     */   
    function dgph_infographics_philgeps_import_form_submit($form, &$form_state) {
        $year = $form_state['input']['year'];
        $month = $form_state['input']['month'];
        $day = $form_state['input']['day'];
        if($day == 0){
        	drupal_set_message("Select a day");	        
        }
        else{
	        $totalImported = philgeps_central_api_import_procurement_items_ckan($year, $month, $day);
	        drupal_set_message("$totalImported records imported");   
        }
    }
    
    /**
     * Gets the icon name corresponding to a procurement mode
     * @param $pm the procurement mode
     * @return the name of the icon
     */
    function philgeps_get_pm_icon_name($pm) {
        $iconName = '';
        if (!empty($pm)) {
            $pm = preg_replace('/\(.+\)/', '', $pm);
            $pm = str_replace(' ', '-', trim($pm));
            $iconName = strtolower($pm);
        }
        return $iconName;
    }
    
    /**
     * Retrieves information about the attachments to a procurement item comment
     * @param int $cid the comment identifier
     * @return array the requested information
     */
    function philgeps_get_pi_comment_attachs($cid) {
        $attachs = array();
        $query = db_select('file_managed', 'f')
                    ->fields('f', array('filename', 'uri', 'filemime'));
        $query->join('file_usage', 'u', 'f.fid=u.fid');
        $typeOr = db_or()->condition('f.filemime', 'image/%', 'like')
                         ->condition('f.filemime', 'application/vnd.google-earth.kml+xml');
        $query->condition('u.module', 'file')
              ->condition('u.type', 'comment')
              ->condition('u.id', $cid)
              ->condition($typeOr);
        $res = $query->execute();
        foreach($res as $row) {
            $furl = file_create_url($row->uri);
            $attachs[] = array(
                                'comment_attach_name' => $row->filename,
                                'comment_attach_type' => $row->filemime,
                                'comment_attach_url' => $furl
                            );
        }
        return $attachs;
    }
    
    /**
     * Load the latest comments for a procurement item
     * @param int @nid the procurement item node identifier
     * @return array the latest comments for this item
     */
    function philgeps_get_latest_pi_comments($nid) {
        $comments = array();
        // load latest comments for this node
        $query = db_select('comment', 'c')
                    ->fields('c', array('cid', 'uid', 'created'));
        $query->leftJoin('field_data_field_first_name', 'fn', 'c.uid = fn.entity_id');
        $query->leftJoin('field_data_field_last_name', 'ln', 'c.uid = ln.entity_id');
        $query->leftJoin('field_data_comment_body', 'cb', 'c.cid = cb.entity_id');
        $query->fields('fn', array('field_first_name_value'))
                ->fields('ln', array('field_last_name_value'))
                ->fields('cb', array('comment_body_value'))
                ->condition('c.nid', $nid)
                ->condition('c.status', 1)
                ->condition('cb.entity_type', 'comment')
                ->condition('cb.bundle', 'comment_node_philgeps_procurement_item')
                ->condition('cb.deleted', 0)
                ->orderBy('c.created', 'desc')
                ->range(0, 5);
        $res = $query->execute();
        foreach($res as $row) {
            $cid = $row->cid;
            $attachs = philgeps_get_pi_comment_attachs($cid);
            $comments[] = array(
                            'cid' => $row->cid,
                            'author_uid' => $row->uid,
                            'author_first_name' => $row->field_first_name_value,
                            'author_last_name' => $row->field_last_name_value,
                            'comment_created' => $row->created,
                            'comment_body' => $row->comment_body_value,
                            'comment_attachments' => $attachs
                        );
        }
        return $comments;
    }
    
    /**
     * Get the list of allowed bid classifications
     * @return array the bid classifications
     */
    function philgeps_get_bid_classifications() {
        $bcs = array(
                        "Civil Works",
                        "Consulting Services",
                        "Goods",
                        "Goods – Support Services"
                    );
        return $bcs;
    }
    
    /**
     * Get the list of allowed approved budget ranges
     * @return array the approved budget ranges
     */
    function philgeps_get_approved_budget_ranges() {
        $abs = array(
                        array('from'=>0, 'to'=>50000),
                        array('from'=>50001, 'to'=>500000),
                        array('from'=>500001, 'to'=>1000000),
                        array('from'=>1000001, 'to'=>2000000),
                        array('from'=>2000001, 'to'=>5000000),
                        array('from'=>5000001, 'to'=>20000000),
                        array('from'=>20000001, 'to'=>50000000),
                        array('from'=>50000001, 'to'=>100000000),
                        array('from'=>100000001, 'to'=>500000000),
                        array('from'=>500000001, 'to'=>-1)
                    );
        return $abs;
    }
    
    /**
     * Get the list of allowed procurement modes
     * @return array the procurement modes
     */
    function philgeps_get_procurement_modes() {
        $pms = array(
                        "Direct Contracting (Sec. 50)",
                        "International Competitive Bidding",
                        "Limited Source Bidding (Sec. 49)",
                        "National Competitive Bidding",
                        "Negotiated Procurement - Agency to Agency (Sec. 53.5)",
                        "Negotiated Procurement - Community Participation (Sec. 53.12)",
                        "Negotiated Procurement - Defense Cooperation Agreement (Sec. 53.8)",
                        "Negotiated Procurement - Emergency Cases (Sec. 53.2)",
                        "Negotiated Procurement - Highly Technical Consultants (Sec. 53.7)",
                        "Negotiated Procurement - Lease of Real Property (Sec. 53.10)",
                        "Negotiated Procurement - NGO Participation (Sec. 53.11)",
                        "Negotiated Procurement - Procurement Agent (Sec. 53.6)",
                        "Negotiated Procurement - Small Value Procurement (Sec. 53.9)",
                        "Negotiated Procurement - Two Failed Biddings (Sec. 53.1)",
                        "Negotiated Procurement - United Nations Agencies (Sec. 53.13)",
                        "Public Bidding",
                        "Shopping",
                        "Shopping - Ordinary/Regular Office Supplies & Equipment (Sec. 52.1.b)",
                        "Shopping - Unforeseen Contingency (Sec. 52.1.a)"
                    );
        return $pms;
    }
    
    /**
     * Get the list of supported statutes
     * @return array the statuses
     */
    function philgeps_get_statuses() {
        $sts = array(
                        "Awarded",
                        "Cancelled",
                        "Closed",
                        "Failed",
                        "Shortlisted"
                    );
        return $sts;
    }
    
    /**
     * Gets the PhilGEPS comments for an agency
     * @param int $agencyId the agency identifier
     * @return array the list of comments 
     */
    function dgph_infographics_philgeps_get_comments($agencyId) {
        $comments = array();
        // set the table meta-data
        $rowsPerPage = 25;
        $header = array(
                    array('data' => '#'),
                    array('data' => 'Subject'),
                    array('data' => 'Author'),
                    array('data' => 'Posted In'),
                    array('data' => 'Status', 'field' => 'c.status'),
                    array('data' => 'Operations')
                        );
        $comments['header'] = $header;
        $rows = array();
        if ($agencyId>0) {
            // load comments for this agency
            $query = db_select('comment', 'c')
                        ->fields('c', array('cid', 'nid', 'uid', 'created', 'subject', 'status'));
            $query->leftJoin('node', 'n', 'c.nid = n.nid');
            $query->leftJoin('field_data_field_first_name', 'fn', 'c.uid = fn.entity_id');
            $query->leftJoin('field_data_field_last_name', 'ln', 'c.uid = ln.entity_id');
            $query->leftJoin('field_data_field_agency', 'ag', 'c.nid = ag.entity_id');
            $query->fields('n', array('title'))
                    ->fields('fn', array('field_first_name_value'))
                    ->fields('ln', array('field_last_name_value'))
                    ->condition('ag.field_agency_target_id', $agencyId);
            $order = array_key_exists('order', $_GET) ? $_GET['order'] : '';
            $sort = array_key_exists('sort', $_GET) ? $_GET['sort'] : 'asc';
            if (!empty($order)) {
                if ($order=='Status') {
                    $query->orderBy('c.status', $sort);
                }
                else {
                    $query->orderBy($order, $sort);
                }
            }
            $query->orderBy('c.created', 'desc');
            $res = $query->execute();
            // fetch the rows
            $page = isset($_GET['page']) ? $_GET['page'] : 0;
            $totalPublished = 0;
            foreach ($res as $idx => $row) {
                $cid = $row->cid;
                $nid = $row->nid;
                $uid = $row->uid;
                $status = $row->status;
                $firstName = $row->field_first_name_value;
                $lastName = $row->field_last_name_value;
                $subj = $row->subject;
                $title = $row->title;
                $statusCode = "Pending / Declined";
                $opersCode = "<a href='/infographics/philgeps-feedback/$agencyId/$cid/approve'>approve</a>";
                if ($status==1) {
                    $statusCode = "Approved";
                    $opersCode = "<a href='/infographics/philgeps-feedback/$agencyId/$cid/decline'>decline</a>";
                    $totalPublished++;
                }
                $rows[] = array(
                    'data' => array(
                                    $page * $rowsPerPage + $idx + 1,
                                    "<a href='/comment/$cid#comment-$cid'>$subj</a>",
                                    "<a href='/user/$uid'>$firstName $lastName</a>",
                                    "<a href='/node/$nid'>$title</a>",
                                    $statusCode,
                                    $opersCode
                                )
                );
            }
        }
        $comments['rows'] = $rows;
        $comments['total_published'] = $totalPublished;
        return $comments;
    }
    
    /**
     * Executes an action on a comment
     * @param int $cid the comment identifier
     * @param string $action the comment action
     */
    function dgph_infographics_update_comment($cid, $action) {
        if ($cid>0) {
            // load comment
            $comment = comment_load($cid);
            if ($comment!=null) {
                // updates comment status
                $newStatus = ($action=='approve') ? COMMENT_PUBLISHED : COMMENT_NOT_PUBLISHED;
                $comment->status = $newStatus;
                drupal_write_record('comment', $comment, 'cid');    // skips custom modules hooks
                $msg = ($action=='approve') ? 'Comment approved.' : 'Comment declined.';
                drupal_set_message($msg);
            }
        }
    }
    
    /**
     * Feedback management console
     * @param int $agencyId the agency identifier
     * @param int $cid the comment identifier to take an action on, or <code>0</code> if not applicable
     * @param string $action the comment action, or empty if not applicable 
     */
    function dgph_infographics_philgeps_feedback($agencyId, $cid = 0, $action = '') {
        $rep = array('agency_id'=>$agencyId, 'comment_id'=>$commentId, 'comment_action'=>$action);
        if ($cid>0 && !empty($action)) {
            // execute action on comment
            dgph_infographics_update_comment($cid, $action);            
        }
        // load comments
        $rep['feedback'] = dgph_infographics_philgeps_get_comments($agencyId);
        return theme('dgph_infographics_philgeps_feedback', $rep);
    }
    
    /**
     * Theme for feedback management console
     */
    function theme_dgph_infographics_philgeps_feedback(&$vars) {
        // load agency information
        $agencyId = $vars['agency_id'];
        $agency = node_load($agencyId);
        $agencyName = $agency->title;
        drupal_set_title($agencyName);
        // show comments table
        $comments = $vars['feedback'];
        $header = $comments['header'];
        $rows = $comments['rows'];
        $published = $comments['total_published'];
        $total = count($rows);
        $pending = $total - $published;
        $code = "
                    <div class='feedback-title'>Procurement Items Feedback</div>
                    <div class='feedback-stats'><div class='total'>Total: <b>$total</b></div><div class='published'>Pending: <b>$pending</b></div></div>".
                    theme_table(array(
                                'header' => $header,
                                'rows' => $rows,
                                'attributes' => array(),
                                'colgroups' => array(),
                                'caption' => '',
                                'sticky' => true,
                                'empty' => t('No records found...')
                        )).
                  theme('pager',
                            array(
                                'tags' => array()
                            )
                        );
        $code .=  "
                    <div class='page-console-links'>
                        <ul>
                            <li><a href='/infographics/philgeps/$agencyId'>&lt;&lt;&nbsp;back to philgeps</a></li>
                        </ul>
                    </div>";
        return $code;
    }
    
    /**
     * Updates a procurement item notice via ajax
     * @return the result of the ajax call
     */
    function philgeps_update_notice_ajax() {
        $result = array('success'=>true);
        // get request parameters
        $bidId = isset($_POST['bid_nid']) ? $_POST['bid_nid'] : 0;
        $bidNotice = isset($_POST['bid_notice']) ? $_POST['bid_notice'] : '';
        $bidNoticeType = isset($_POST['bid_notice_type']) ? $_POST['bid_notice_type'] : '';
        if ($bidId>0) {
            // load node
            $node = node_load($bidId);
            if ($node) {
                // updates notice
                if ($bidNoticeType=='bid') {
                    $node->field_procurement_bid_notice[LANGUAGE_NONE][0]['value'] = $bidNotice;
                }
                else if ($bidNoticeType=='award') {
                    $node->field_award_notice_abstract[LANGUAGE_NONE][0]['value'] = $bidNotice;
                }
                node_save($node);
            }
        }
        echo drupal_json_encode($result);
    }
    
    /**
     * Extracts information about a procurement item's award contract
     * @param string $cinfo the procurement award contract description, in JSON format
     * @return array set of documents composing the contract
     */
    function philgeps_extract_award_contract($cinfo) {
        $cdocs = array();
        if (!empty($cinfo)) {
            $cobjs = json_decode($cinfo);
            foreach($cobjs as $cobj) {
                if (isset($cobj->DocCategory) && isset($cobj->DocName) && isset($cobj->DocPath)) {
                    if (!array_key_exists($cobj->DocCategory, $cdocs)) {
                        // creates an entry for this document category
                        $cdocs[$cobj->DocCategory] = array();
                    }
                    $cdocs[$cobj->DocCategory][] = array(
                                PHILGEPS_CONTRACT_AWARD_ID => $cobj->AwardId,
                                PHILGEPS_CONTRACT_DOCUMENT_TYPE => $cobj->DocCategory,
                                PHILGEPS_CONTRACT_DOCUMENT_NAME => $cobj->DocName,
                                PHILGEPS_CONTRACT_DOCUMENT_URL => $cobj->DocPath,
                                PHILGEPS_CONTRACT_FILE_EXISTS => $cobj->FileExists
                            );
                }
            }
        }
        return $cdocs;
    }
    
    /**
     * Gets the names of all the KML files uploaded to a PhilGEPS comment
     * @param int $pid the procurement item identifier
     * @return array the names of uploaded KML files
     */
    function philgeps_get_kml($pid) {
        $fnames = array();
        if ($pid>0) {
            // check if there are KML files uploaded to this procurement item
            $query = db_select('comment', 'c')
                        ->fields('c', array('cid', 'created'));
            $query->leftJoin('field_data_field_add_a_kml_file', 'fn', 'c.cid = fn.entity_id');
            $query->fields('fn', array('field_add_a_kml_file_fid'))
                  ->condition('c.nid', $pid)
                  ->condition('c.status', 1)
                  ->orderBy('c.created');
            $res = $query->execute();
            foreach($res as $row) {
                $fid = $row->field_add_a_kml_file_fid;
                if ($fid>0) {
                    // load the file name
                    $query = db_select('file_managed', 'f')
                                ->fields('f', array('filename'))
                                ->condition('f.fid', $fid);
                    $fnames[] = $query->execute()->fetchColumn();
                }
            }
        }
        return $fnames;
    }
    
    /**
     * Called whenever a new comment is posted to the PhilGEPS dashboard
     * @param $nid identifier of node the comment belongs to
     * @return array the comment reply form on success
     */
    function philgeps_post_comment($nid) {
        if (user_access('post comments')) {
            // load node
            $node = node_load($nid);
            if ($node) {
                module_load_include('inc', 'comment', 'comment.pages');
                comment_reply($node);
            }
        }
        else {
            drupal_set_message(t('Please register and login to data.gov.ph to post comments and feedback.'), 'error');
            drupal_goto("user/register");
        }
   }
?>