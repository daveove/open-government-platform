<?php   
    /**
     *  Creates the customs viz import form
     */
    function dgph_customs_viz_import_form($form, &$form_state) {
        drupal_set_title("Import Customs Visualization Data");
        $form['#attributes'] = array('class' => array('dashboard-import'));
        $form['category_id'] = array(
                '#type' => 'select',
                '#title' => t('Select view'),
                '#options' => array(0 => '',
                        TOTAL_BOC_CIF_VALUE_VS_COLLECTIONS => 'Total BOC - CIF Value vs Collections',
                        TOTAL_BOC_COLLECTION_PERFORMANCE => 'Total BOC - Collection Performance',
                        TOTAL_BOC_IMPORT_ENTRIES => 'Total BOC - Import Entries',
                        TOTAL_BOC_VOLUME_OF_IMPORTS => 'Total BOC - Volume of Imports',
                        TOTAL_BOC_YOY_GROWTH => 'Total BOC - YOY Growth',
                        PORT_VIEW_CIF_VALUE_VS_COLLECTIONS => 'Port View - CIF Value vs Collections',
                        PORT_VIEW_COLLECTION_PERFORMANCE => 'Port View - Collection Performance',
                        PORT_VIEW_IMPORT_ENTRIES => 'Port View - Import Entries',
                        PORT_VIEW_VOLUME_OF_IMPORTS => 'Port View - Volume of Imports',
                        PORT_VIEW_YOY_GROWTH => 'Port View - YOY Growth',
                        COMMODITY_VIEW_IRON_AND_STEEL => 'Commodity View - Iron And Steel',
                        COMMODITY_VIEW_MOTOR_VEHICLES => 'Commodity View - Motor Vehicles',
                        COMMODITY_VIEW_PLASTIC_RESINS => 'Commodity View - Plastic Resins',
                        COMMODITY_VIEW_RICE => 'Commodity View - Rice',
                        COMMODITY_VIEW_TOBACCO => 'Commodity View - Tobacco',
                        BROKERS_IMPORTERS_VIEW => 'Broker / Importer View'
                    )
              );
        $form['data_file'] = array(
            '#type' => 'file',
            '#title' => 'Path to data file'
        );
        $form['submit'] = array(
          '#type' => 'submit',
          '#value' => 'Update',
        );
        return $form;
    }
    
    /**
     *  Validator for customs viz import form
     */
    function dgph_customs_viz_import_form_validate($form, &$form_state) {
        // validate view
        $cid = $form_state['input']['category_id'];
        if (empty($cid)) {
            form_set_error('category_id', t("Please select a view to import data for."));
        }
        $file = file_save_upload('data_file', array(
                    'file_validate_extensions' => array('xls xlsx')
                ));
        if ($file) {
            $tmpFile = file_move($file, "public://uploads");
            if ($tmpFile) {
                $form_state['values']['data_file'] = $tmpFile;
            }
            else {
                form_set_error('data_file', t('Failed to write the uploaded file the site\'s file folder.'));
            }
        }
        else {
            form_set_error('data_file', t('Please select the data file to upload from your local system.'));
        }
    }
    
     /**
     *  Handler for customs viz import form
     */   
    function dgph_customs_viz_import_form_submit($form, &$form_state) {
        module_load_include('inc', 'phpexcel', 'phpexcel');
        $cid = $form_state['values']['category_id'];
        $dataFile = $form_state['values']['data_file'];
        $filePath = drupal_realpath($dataFile->uri);
        unset($form_state['values']['data_file']);
        // load records from file
        $cells = phpexcel_import($filePath, false);
        if (is_array($cells)) {
            // import data
            $rows = $cells[0];
            $res = null;
            switch($cid) {
                case TOTAL_BOC_CIF_VALUE_VS_COLLECTIONS:
                case TOTAL_BOC_COLLECTION_PERFORMANCE:
                case TOTAL_BOC_IMPORT_ENTRIES:
                case TOTAL_BOC_VOLUME_OF_IMPORTS:
                case TOTAL_BOC_YOY_GROWTH:
                    $res = import_total_boc($rows, $cid);
                break;
                case PORT_VIEW_CIF_VALUE_VS_COLLECTIONS:
                case PORT_VIEW_COLLECTION_PERFORMANCE:
                case PORT_VIEW_IMPORT_ENTRIES:
                case PORT_VIEW_VOLUME_OF_IMPORTS:
                case PORT_VIEW_YOY_GROWTH:
                    $res = import_port_view($rows, $cid);
                break;
                case COMMODITY_VIEW_IRON_AND_STEEL:
                case COMMODITY_VIEW_MOTOR_VEHICLES:
                case COMMODITY_VIEW_PLASTIC_RESINS:
                case COMMODITY_VIEW_RICE:
                case COMMODITY_VIEW_TOBACCO:
                    // import overall data
                    $res = import_commodity_view_overall($rows, $cid);
                    // import data by port
                    $rows = $cells[1];
                    $res1 = import_commodity_view_by_port($rows, $cid);
                    // import top importers data
                    $rows = $cells[2];
                    $res2 = import_commodity_view_top_importers($rows, $cid);
                    // merge results
                    $res['imported'] += $res1['imported']+$res2['imported'];
                    $res['deleted'] += $res1['deleted']+$res2['deleted'];
                    $res['errors'] += $res1['errors']+$res2['errors'];
                break;
                case BROKERS_IMPORTERS_VIEW:
                    // import brokers data
                    $res = import_broker_importer_view($rows, BROKERS_IMPORTERS_VIEW_BROKERS);
                    // import importers data
                    $rows = $cells[1];
                    $res1 = import_broker_importer_view($rows, BROKERS_IMPORTERS_VIEW_IMPORTERS);
                    // merge results
                    $res['imported'] += $res1['imported'];
                    $res['deleted'] += $res1['deleted'];
                    $res['errors'] += $res1['errors'];
                break;
            }
            $msg = "Operation completed";
            if ($res!=null) {
                $msg .= ": ".$res['imported']." records imported, ".$res['deleted']." deleted, ".$res['errors']." errors";
            }
            drupal_set_message($msg.".");
        }
        else {
            drupal_set_message("An error occured while processing input file!", 'error');
        }
    }
    
    /**
     * Import data for Total BOC views
     * @param array $rows data rows
     * @param int $cid data category identifier
     */
   function import_total_boc($rows, $cid) {
       $res = array('imported'=>0, 'deleted'=>0, 'errors'=>0);
       // cleanup category
       $res['deleted'] = db_delete('cviz_total_boc')
                           ->condition('category_id', $cid)
                           ->execute();
       foreach($rows as $row) {
           if (is_numeric($row[0])) {
               try {
                   // import record
                   $year = $row[0];
                   $month = $row[1];
                   $total = isset($row[2]) ? floatval($row[2]) : 0;
                   db_insert('cviz_total_boc')
                       ->fields(array(
                                   'year' => $year,
                                   'month' => $month,
                                   'category_id' => $cid,
                                   'value' => $total
                               ))
                           ->execute();
                   $res['imported']++;
               }
               catch(Exception $e) {
                   $res['errors']++;
               }
           }
       }
       return $res;
   }

   /**
     * Import data for Port View
     * @param array $rows data rows
     * @param int $cid data category identifier
     */
   function import_port_view($rows, $cid) {
        $res = array('imported'=>0, 'deleted'=>0, 'errors'=>0);
        // cleanup category
        $res['deleted'] = db_delete('cviz_port_view')
                           ->condition('category_id', $cid)
                           ->execute();
        // load supported ports
        $ports = dgph_customs_viz_load_ports();
        foreach($rows as $row) {
            if (is_numeric($row[0])) {
                try {
                    // import record
                    $year = $row[0];
                    $month = $row[1];
                    $port = $row[2];
                    $total = isset($row[3]) ? floatval($row[3]) : 0;
                    $pid = array_search(strtolower($port), $ports);
                    if ($pid) {
                        db_insert('cviz_port_view')
                            ->fields(array(
                                    'year' => $year,
                                    'month' => $month,
                                    'port_nid' => $pid,
                                    'port_name' => $port,
                                    'category_id' => $cid,
                                    'value' => $total
                                ))
                            ->execute();
                        $res['imported']++;
                    }
                    else {
                        $res['errors']++;
                    }
               }
               catch(Exception $e) {
                   $res['errors']++;
               }
           }
       }
       return $res;
   }
   
   /**
     * Import overall data for Commodity View
     * @param array $rows data rows
     * @param int $cid data category identifier
     */
   function import_commodity_view_overall($rows, $cid) {
        $res = array('imported'=>0, 'deleted'=>0, 'errors'=>0);
        // cleanup category
        $res['deleted'] = db_delete('cviz_commodity_view_overall')
                           ->condition('category_id', $cid)
                           ->execute();
        foreach($rows as $row) {
            if (is_numeric($row[0])) {
                try {
                    // import record
                    $year = $row[0];
                    $month = $row[1];
                    $cif = isset($row[2]) ? floatval($row[2]) : 0;
                    $volume = isset($row[3]) ? floatval($row[3]) : 0;
                    $entries = isset($row[4]) ? floatval($row[4]) : 0;
                    $duties = isset($row[5]) ? floatval($row[5]) : 0;
                    db_insert('cviz_commodity_view_overall')
                        ->fields(array(
                                'year' => $year,
                                'month' => $month,
                                'category_id' => $cid,
                                'cif_value' => $cif,
                                'volume' => $volume,
                                'entries' => $entries,
                                'customs_duties' => $duties
                            ))
                        ->execute();
                    $res['imported']++;
               }
               catch(Exception $e) {
                   $res['errors']++;
               }
           }
       }
       return $res;
   }
   
   /**
     * Import ports data for Commodity View
     * @param array $rows data rows
     * @param int $cid data category identifier
     */
   function import_commodity_view_by_port($rows, $cid) {
        $res = array('imported'=>0, 'deleted'=>0, 'errors'=>0);
        // cleanup category
        $res['deleted'] = db_delete('cviz_commodity_view_by_port')
                           ->condition('category_id', $cid)
                           ->execute();
        // load supported ports
        $ports = dgph_customs_viz_load_ports();
        foreach($rows as $row) {
            if (is_numeric($row[0])) {
                try {
                    // import record
                    $year = $row[0];
                    $port = $row[1];
                    $cif = isset($row[2]) ? floatval($row[2]) : 0;
                    $volume = isset($row[3]) ? floatval($row[3]) : 0;
                    $entries = isset($row[4]) ? floatval($row[4]) : 0;
                    $duties = isset($row[5]) ? floatval($row[5]) : 0;
                    $pid = array_search(strtolower($port), $ports);
                    if ($pid) {
                        db_insert('cviz_commodity_view_by_port')
                            ->fields(array(
                                    'year' => $year,
                                    'port_nid' => $pid,
                                    'port_name' => $port,
                                    'category_id' => $cid,
                                    'cif_value' => $cif,
                                    'volume' => $volume,
                                    'entries' => $entries,
                                    'customs_duties' => $duties
                                ))
                            ->execute();
                        $res['imported']++;
                    }
                    else {
                        $res['errors']++;
                    }
               }
               catch(Exception $e) {
                   $res['errors']++;
               }
           }
       }
       return $res;
   }
   
   /**
     * Import top importers data for Commodity View
     * @param array $rows data rows
     * @param int $cid data category identifier
     */
   function import_commodity_view_top_importers($rows, $cid) {
        $res = array('imported'=>0, 'deleted'=>0, 'errors'=>0);
        // cleanup category
        $res['deleted'] = db_delete('cviz_commodity_view_top_importers')
                           ->condition('category_id', $cid)
                           ->execute();
        foreach($rows as $row) {
            if (is_numeric($row[0])) {
                try {
                    // import record
                    $year = $row[0];
                    $rank = $row[1];
                    $importer = $row[2];
                    $cif = isset($row[3]) ? floatval($row[3]) : 0;
                    $volume = isset($row[4]) ? floatval($row[4]) : 0;
                    $entries = isset($row[5]) ? floatval($row[5]) : 0;
                    $duties = isset($row[6]) ? floatval($row[6]) : 0;
                    db_insert('cviz_commodity_view_top_importers')
                        ->fields(array(
                                'year' => $year,
                                'rank' => $rank,
                                'importer' => $importer,
                                'category_id' => $cid,
                                'cif_value' => $cif,
                                'volume' => $volume,
                                'entries' => $entries,
                                'customs_duties' => $duties
                            ))
                        ->execute();
                    $res['imported']++;
               }
               catch(Exception $e) {
                   $res['errors']++;
               }
           }
       }
       return $res;
   }
   
   /**
     * Import data for Broker / Importer View
     * @param array $rows data rows
     * @param int $cid data category identifier
     */
   function import_broker_importer_view($rows, $cid) {
        $res = array('imported'=>0, 'deleted'=>0, 'errors'=>0);
        // cleanup category
        $res['deleted'] = db_delete('cviz_broker_importer_view')
                           ->condition('category_id', $cid)
                           ->execute();
        foreach($rows as $row) {
            if (is_numeric($row[0])) {
                try {
                    // import record
                    $year = $row[0];
                    $rank = $row[1];
                    $name = isset($row[2]) ? $row[2] : '';
                    $cif = isset($row[3]) ? floatval($row[3]) : 0;
                    $volume = isset($row[4]) ? floatval($row[4]) : 0;
                    $duties = isset($row[5]) ? floatval($row[5]) : 0;
                    db_insert('cviz_broker_importer_view')
                        ->fields(array(
                                'year' => $year,
                                'category_id' => $cid,
                                'rank' => $rank,
                                'name' => $name,
                                'cif_value' => $cif,
                                'volume' => $volume,
                                'customs_duties' => $duties
                            ))
                        ->execute();
                    $res['imported']++;
               }
               catch(Exception $e) {
                   $res['errors']++;
               }
           }
       }
       return $res;
   }