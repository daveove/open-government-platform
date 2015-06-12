<?php

    /**
     * Handler for import dof data action
     */
    function dgph_infographics_import_dof_data() {
        drupal_set_title("Import Customs Data");
        $code = drupal_render(drupal_get_form('dgph_infographics_import_dof_data_form'));
        return $code;
    }


    /**
     *  Create the import dof data form
     */
    function dgph_infographics_import_dof_data_form($form, &$form_state) {

        $form['#attributes'] = array('class' => array('dashboard'));
        $form['year'] = array(
                '#type' => 'textfield',
		'#required' => true,
                '#title' => t('Enter Year'),
		'#description' => t('Please enter here year, example : 2010'),
                '#attributes' => array(
                        'name' => 'year',
                        'class' => array('number')
                    )
              );

	$depts = array(
		'dof_dashb1_pillar1' => 'Commodity Import',
		'dof_dashb2_pillar1' => 'Commodity Report - Rice Imports',
		'dof_dashb2_pillar1_2' => 'Commodity Report - Top Rice Importers',
		'dof_dashb2_pillar2' => 'Commodity Report - Motor Vehicle Imports',
		'dof_dashb2_pillar2_2' => 'Commodity Report - Motor Vehicles (MV) - Top MV imports sorted by type',
		'dof_dashb2_pillar2_3' => 'Commodity Report - Motor Vehicles (MV) - Top MV importers sorted by type',
                'customs_plasticresins_ports' => 'Commodity Report - Plastic Resins By Port',
                'customs_plasticresins_types' => 'Commodity Report - Plastic Resins By Type',
                'customs_plasticresins_importers' => 'Commodity Report - Plastic Resins By Importer',
                'customs_tobacco_ports' => 'Commodity Report - Tobacco By Port',
                'customs_tobacco_types' => 'Commodity Report - Tobacco By Type',
                'customs_tobacco_importers' => 'Commodity Report - Tobacco By Importer',
                'customs_ironandsteel_ports' => 'Commodity Report - Iron/Steel By Port',
                'customs_ironandsteel_types' => 'Commodity Report - Iron/Steel By Type',
                'customs_ironandsteel_importers' => 'Commodity Report - Iron/Steel By Importer',
		'dof_dashb3_pillar1' => 'Trade Activities By Port',
		'dof_dashb4_pillar1' => 'Brokers and Importers'
	);

        $form['data_type'] = array(
            '#type' => 'select',
	    '#required' => true,
            '#title' => t('Category'),
            '#options' => $depts,
            '#attributes' => array(
                        'id' => 'department'
                    )
          );
        $form['data_file'] = array(
            '#type' => 'file',
            '#title' => 'Path to data file'
        );
        // Submit button
        $form['submit'] = array(
          '#type' => 'submit',
          '#value' => 'Import',
        );

        return $form;
    }


    /**
     *  Validator for import dof data form
     */
    function dgph_infographics_import_dof_data_form_validate($form, &$form_state) {
        
        $file = file_save_upload('data_file', array(
                    'file_validate_extensions' => array('xls xlsx')
                ));
        if ($file) {
            $tmpFile = file_move($file, "public://import");
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
     * Submit handler for import procurement data form
     */
    function dgph_infographics_import_dof_data_form_submit($form, &$form_state) {
        $data_type = $form_state['values']['data_type'];
        $data_file = $form_state['values']['data_file'];
        $file_path = drupal_realpath($data_file->uri);
	unset($form_state['values']['data_file']);
	$year = $form_state['values']['year'];
	switch($data_type){
            case 'dof_dashb1_pillar1':
                 import_dof_dashb1_pillar1($file_path, $year);
                 break;
            case 'dof_dashb2_pillar1':
                 import_dof_dashb2_pillar1($file_path, $year);
                 break;
            case 'dof_dashb2_pillar1_2':
                 import_dof_dashb2_pillar1_2($file_path, $year);
                 break;
            case 'dof_dashb2_pillar2':
                 import_dof_dashb2_pillar2($file_path, $year);
                 break;

            case 'dof_dashb2_pillar2_2':
                 import_dof_dashb2_pillar2_2($file_path, $year);
                 break;
            case 'dof_dashb2_pillar2_3':
                 import_dof_dashb2_pillar2_3($file_path, $year);
                 break;

            case 'dof_dashb3_pillar1':
                 import_dof_dashb3_pillar1($file_path, $year);
                 break;
            case 'dof_dashb4_pillar1':
                 import_dof_dashb4_pillar1($file_path, $year);
                 break;		
            case 'customs_plasticresins_ports':
            case 'customs_tobacco_ports':
            case 'customs_ironandsteel_ports':
                 import_customs_pti_ports($file_path, $year, $data_type);
                 break;
             case 'customs_plasticresins_types':
            case 'customs_tobacco_types':
            case 'customs_ironandsteel_types':
                 import_customs_pti_types($file_path, $year, $data_type);
                 break;
             case 'customs_plasticresins_importers':
            case 'customs_tobacco_importers':
            case 'customs_ironandsteel_importers':
                 import_customs_pti_importers($file_path, $year, $data_type);
                 break;
	}
    }


     /**
     * Load import excel file.
     */
    function dof_dashboard_excel_load($dataFile) {
	$libsPath = libraries_get_path('PHPExcel');
        require_once("$libsPath/Classes/PHPExcel.php");
        require_once("$libsPath/Classes/PHPExcel/IOFactory.php");
        $objPHPExcel = PHPExcel_IOFactory::load($dataFile);
        $sheetData = $objPHPExcel->getActiveSheet()->toArray(null, true, false, true);

	return $sheetData;
    }


     /**
     * Import (dof : import_dof_dashb1_pillar1) data file
     * @param data_file path to data file to be imported
     * @param  year (e.g. 2013)
     */
    function import_dof_dashb1_pillar1($dataFile, $year) {
        $num_deleted = db_delete('dof_dashb1_pillar1')
		  ->condition('year', $year)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");

        $sheetData = dof_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;

        for($x=5; $x<=$rowsCount; $x++){	
            try {
		$month				= $sheetData[$x]['A'];
		$rank				= $sheetData[$x]['B'];
		$category			= $sheetData[$x]['C'];
		$hs_code			= $sheetData[$x]['D'];
		$description			= $sheetData[$x]['E'];
		$cif_value			= $sheetData[$x]['F'];
		$volume				= $sheetData[$x]['G'];
		$import_entries			= $sheetData[$x]['H'];
		$total_duties_taxes_collected	= $sheetData[$x]['I'];
		$collection_cif_value		= $sheetData[$x]['J'];

                if ($month!=null) {

                    db_insert('dof_dashb1_pillar1')
                        ->fields(array(
                                'year', 
                                'month',
				'rank',
				'port',
				'category',
				'hs_code',
				'description',
				'cif_value',
				'volume',
				'import_entries',
				'total_duties_taxes_collected',
                                'collection_cif_value'
                            ))
                        ->values(array(
                                $year,
                                $month,
				$rank,
				$port,
				$category,
				$hs_code,
				$description,
				$cif_value,
				$volume,
				$import_entries,
				$total_duties_taxes_collected,
                                $collection_cif_value
                            ))
                        ->execute();

                    $importedCount++;
                }

            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
       
        drupal_set_message("Operation completed: $importedCount records imported, $errorsCount errors!");
    }


     /**
     * Import (dof : import_dof_dashb2_pillar1) data file (Commodity Report - Rice Imports)
     * @param data_file path to data file to be imported
     * @param year (e.g. 2013)
     */
    function import_dof_dashb2_pillar1($dataFile, $year) {
        $num_deleted = db_delete('dof_dashb2_pillar1')
		  ->condition('year', $year)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");

        $sheetData = dof_dashboard_excel_load($dataFile);

        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;

        for($x=5; $x<=$rowsCount; $x++){

            try {
		$month			= $sheetData[$x]['A'];
		$port			= $sheetData[$x]['B'];
		$cif_value		= $sheetData[$x]['C'];
		$distribution		= $sheetData[$x]['D'];
		$volume			= $sheetData[$x]['E'];
		$distribution1		= $sheetData[$x]['F'];
		$cud_collected		= $sheetData[$x]['G'];
		$distribution2		= $sheetData[$x]['H'];
		$import_entries		= $sheetData[$x]['I'];
		$distribution3		= $sheetData[$x]['J'];

                if ($month!=null) {
                    db_insert('dof_dashb2_pillar1')
                        ->fields(array(
                                'year', 
                                'month',
				'port',
				'cif_value',
				'distribution',
				'volume',
				'distribution1',
				'cud_collected',
				'distribution2',
				'import_entries',
                                'distribution3'
                            ))
                        ->values(array(
                                $year,
				$month,
				$port,
				$cif_value,
				$distribution,
				$volume,
				$distribution1,
				$cud_collected,
				$distribution2,
				$import_entries,				
                                $distribution3
                            ))
                        ->execute();
                    $importedCount++;
                }

            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
       
        drupal_set_message("Operation completed: $importedCount records imported, $errorsCount errors!");
    }


     /**
     * Import (dof : import_dof_dashb2_pillar1_2) data file (Commodity Report: Rice - Top rice importers)
     * @param data_file path to data file to be imported
     * @param year (e.g. 2013)
     */
    function import_dof_dashb2_pillar1_2($dataFile, $year) {
        $num_deleted = db_delete('dof_dashb2_pillar1_2')
		  ->condition('year', $year)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");

        $sheetData = dof_dashboard_excel_load($dataFile);

        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;

        for($x=5; $x<=$rowsCount; $x++){

            try {
		$month			= $sheetData[$x]['A'];
		$rank			= $sheetData[$x]['B'];
		$port			= $sheetData[$x]['C'];
		$importer		= $sheetData[$x]['D'];
		$cif_value		= $sheetData[$x]['E'];
		$volume			= $sheetData[$x]['F'];
		$cud_paid		= $sheetData[$x]['G'];
		$cud_as_of_cif_value	= $sheetData[$x]['H'];		

                if ($month!=null) {
                    db_insert('dof_dashb2_pillar1_2')
                        ->fields(array(
                                'year', 
                                'month',
				'rank',
				'port',
				'importer',
				'cif_value',
				'volume',
				'cud_paid',
				'cud_as_of_cif_value'
                            ))
                        ->values(array(
                                $year,
				$month,
				$rank,
				$port,
				$importer,
				$cif_value,
				$volume,
				$cud_paid,
				$cud_as_of_cif_value
                            ))
                        ->execute();
                    $importedCount++;
                }

            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
       
        drupal_set_message("Operation completed: $importedCount records imported, $errorsCount errors!");
    }



     /**
     * Import (dof : import_dof_dashb2_pillar2) data file Commodity Report - Motor Vehicle Imports
     * @param data_file path to data file to be imported
     * @param year the academic year (e.g. 2013)
     */
    function import_dof_dashb2_pillar2($dataFile, $year) {
        $num_deleted = db_delete('dof_dashb2_pillar2')
		  ->condition('year', $year)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");

        $sheetData = dof_dashboard_excel_load($dataFile);

        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;

        for($x=5; $x<=$rowsCount; $x++){

            try {
		$month			= $sheetData[$x]['A'];
		$port			= $sheetData[$x]['B'];
		$cif_value		= $sheetData[$x]['C'];
		$distribution		= $sheetData[$x]['D'];
		$volume			= $sheetData[$x]['E'];
		$distribution1		= $sheetData[$x]['F'];
		$cud_collected		= $sheetData[$x]['G'];
		$distribution2		= $sheetData[$x]['H'];
		$import_entries		= $sheetData[$x]['I'];
		$distribution3		= $sheetData[$x]['J'];

                if ($month!=null) {
                    db_insert('dof_dashb2_pillar2')
                        ->fields(array(
                                'year', 
                                'month',
				'port',
				'cif_value',
				'distribution',
				'volume',
				'distribution1',
				'cud_collected',
				'distribution2',
				'import_entries',
                                'distribution3'
                            ))
                        ->values(array(
                                $year,
				$month,
				$port,
				$cif_value,
				$distribution,
				$volume,
				$distribution1,
				$cud_collected,
				$distribution2,
				$import_entries,				
                                $distribution3
                            ))
                        ->execute();
                    $importedCount++;
                }

            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
       
        drupal_set_message("Operation completed: $importedCount records imported, $errorsCount errors!");
    }


     /**
     * Import (dof : import_dof_dashb2_pillar2_2) data file Commodity Report - Motor Vehicles (MV) - Top MV imports sorted by type
     * @param data_file path to data file to be imported
     * @param year the academic year (e.g. 2013)
     */
    function import_dof_dashb2_pillar2_2($dataFile, $year) {
        $num_deleted = db_delete('dof_dashb2_pillar2_2')
		  ->condition('year', $year)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");

        $sheetData = dof_dashboard_excel_load($dataFile);

        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;

        for($x=5; $x<=$rowsCount; $x++){	
            try {
		$month				= $sheetData[$x]['A'];
		$rank				= $sheetData[$x]['B'];		
		$hs_code			= $sheetData[$x]['C'];
		$description			= $sheetData[$x]['D'];
		$cif_value			= $sheetData[$x]['E'];
		$volume				= $sheetData[$x]['F'];
		$no_import_entries		= $sheetData[$x]['G'];
		$cud_collected			= $sheetData[$x]['H'];
		$cud_as_of_cif_value		= $sheetData[$x]['I'];

                if ($month!=null) {

                    db_insert('dof_dashb2_pillar2_2')
                        ->fields(array(
                                'year', 
                                'month',
				'rank',		
				'hs_code',
				'description',
				'cif_value',
				'volume',
				'no_import_entries',
				'cud_collected',
                                'cud_as_of_cif_value'
                            ))
                        ->values(array(
                                $year,
                                $month,
				$rank,
				$hs_code,
				$description,
				$cif_value,
				$volume,
				$no_import_entries,
				$cud_collected,
                                $cud_as_of_cif_value
                            ))
                        ->execute();

                    $importedCount++;
                }

            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
       
        drupal_set_message("Operation completed: $importedCount records imported, $errorsCount errors!");
    }


     /**
     * Import (dof : import_dof_dashb2_pillar2_3) data file Commodity Report - Motor Vehicles (MV) - Top MV importers sorted by type
     * @param data_file path to data file to be imported
     * @param year the academic year (e.g. 2013)
     */
    function import_dof_dashb2_pillar2_3($dataFile, $year) {
        $num_deleted = db_delete('dof_dashb2_pillar2_3')
		  ->condition('year', $year)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");

        $sheetData = dof_dashboard_excel_load($dataFile);

        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;

        for($x=5; $x<=$rowsCount; $x++){	
            try {
		$month = $sheetData[$x]['A'];
                if ($month!=null) {
                    $rank = $sheetData[$x]['B'];		
                    $hsCode = $sheetData[$x]['C'];
                    $hsDescr = $sheetData[$x]['D'];
                    $importer = $sheetData[$x]['E'];
                    $cif_value = $sheetData[$x]['F'];
                    $volume = $sheetData[$x]['G'];
                    $cud_paid = $sheetData[$x]['H'];
                    $hsCodeDescr = "$hsCode - $hsDescr";
                    db_insert('dof_dashb2_pillar2_3')
                        ->fields(array(
                                'year', 
                                'month',
				'rank',		
				'hs_code_description',
				'importer',
				'cif_value',
				'volume',			
                                'cud_paid'
                            ))
                        ->values(array(
                                $year,
                                $month,
				$rank,
				$hsCodeDescr,
				$importer,
				$cif_value,
				$volume,		
                                $cud_paid
                            ))
                        ->execute();

                    $importedCount++;
                }

            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
       
        drupal_set_message("Operation completed: $importedCount records imported, $errorsCount errors!");
    }



     /**
     * Import (dof : import_dof_dashb3_pillar1) data file
     * @param data_file path to data file to be imported
     * @param year (e.g. 2013)
     */
    function import_dof_dashb3_pillar1($dataFile, $year) {
        $num_deleted = db_delete('dof_dashb3_pillar1')
		  ->condition('year', $year)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");

        $sheetData = dof_dashboard_excel_load($dataFile);

        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;

        for($x=5; $x<=$rowsCount; $x++){

            try {
                $month				= $sheetData[$x]['A'];
		$port				= $sheetData[$x]['B'];
		$cif_value			= $sheetData[$x]['C'];
		$distribution			= $sheetData[$x]['D'];
		$volume				= $sheetData[$x]['E'];
		$distribution1			= $sheetData[$x]['F'];
		$total_duties_taxes_collected	= $sheetData[$x]['G'];
		$distribution2			= $sheetData[$x]['H'];
		$import_entries			= $sheetData[$x]['I'];
		$share_total_import_entries	= $sheetData[$x]['J'];
		

                if ($month!=null) {
                    db_insert('dof_dashb3_pillar1')
                        ->fields(array(
                                'year', 
				'month',
				'port',
				'cif_value',
				'distribution',
				'volume',
				'distribution1',
				'total_duties_taxes_collected',
				'distribution2',
				'import_entries',                 
                                'share_total_import_entries'
                            ))
                        ->values(array(
                                $year,
                                $month,
				$port,
				$cif_value,
				$distribution,
				$volume,
				$distribution1,
				$total_duties_taxes_collected,
				$distribution2,
				$import_entries,
                                $share_total_import_entries
                            ))
                        ->execute();
                    $importedCount++;
                }

            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
       
        drupal_set_message("Operation completed: $importedCount records imported, $errorsCount errors!");
    }



    /**
     * Import (dof : import_dof_dashb4_pillar1) data file
     * @param data_file path to data file to be imported
     * @param year (e.g. 2013)
     */
    function import_dof_dashb4_pillar1($dataFile, $year) {
        $num_deleted = db_delete('dof_dashb4_pillar1')
		  ->condition('year', $year)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");

        $sheetData = dof_dashboard_excel_load($dataFile);

        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;

        for($x=5; $x<=$rowsCount; $x++){

            try {
		
		$category		= $sheetData[$x]['A'];
		$importers_brokers	= $sheetData[$x]['B'];
		$cif_value		= $sheetData[$x]['C'];
		$volume			= $sheetData[$x]['D'];
		$cud_paid		= $sheetData[$x]['E'];

                if ($importers_brokers!=null) {
                    db_insert('dof_dashb4_pillar1')
                        ->fields(array(
                                'year',                                
				'category',
				'importers_brokers',
				'cif_value',
				'volume',
				'cud_paid'
                            ))
                        ->values(array(
                                $year,
                                $category,
				$importers_brokers,
				$cif_value,
				$volume,
				$cud_paid
                            ))
                        ->execute();
                    $importedCount++;
                }

            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
       
        drupal_set_message("Operation completed: $importedCount records imported, $errorsCount errors!");
    }
    
    /**
     * Import data for "Customs - Plastic Resins / Tobacco / Iron & Steel - By Port" mini - dashboard
     * @param string $path path to data file
     * @param int $year reference year
     * @param string $tableName name of table to save data into
     */
    function import_customs_pti_ports($dataFile, $year, $tableName) {
        // cleanup current data
        $deletedCount = db_delete($tableName)
		  ->condition('year', $year)
		  ->execute();
        $sheetData = dof_dashboard_excel_load($dataFile);
        $importedCount = 0;
        $errorsCount = 0;
        foreach($sheetData as $row) {
            try {
                $count = count(array_filter($row, function($el) { return ($el!==null); }));
                $month = (($count>=10) && (strtolower(trim($row['A']))!='month')) ? $row['A'] : '';
                if (!empty($month)) {
                    // insert this record
                    db_insert($tableName)
                        ->fields(array(
                                'year' => $year,
                                'month' => $month,
                                'port' => $row['B'],
                                'cif' => $row['C'],
                                'cif_distribution' => $row['D'],
                                'volume' => $row['E'],
                                'volume_distribution' => $row['F'],
                                'cud' => $row['G'],
                                'cud_distribution' => $row['H'],
                                'entries' => $row['I'],
                                'entries_distribution' => $row['J']
                            ))
                        ->execute();
                    $importedCount++;
                }

            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
        drupal_set_message("Operation completed: $deletedCount records deleted, $importedCount imported, $errorsCount errors!");
    }
    
    /**
     * Import data for "Customs - Plastic Resins / Tobacco / Iron & Steel - By Type" mini - dashboard
     * @param string $path path to data file
     * @param int $year reference year
     * @param string $tableName name of table to save data into
     */
    function import_customs_pti_types($dataFile, $year, $tableName) {
        // cleanup current data
        $deletedCount = db_delete($tableName)
		  ->condition('year', $year)
		  ->execute();
        $sheetData = dof_dashboard_excel_load($dataFile);
        $importedCount = 0;
        $errorsCount = 0;
        foreach($sheetData as $row) {
            try {
                $count = count(array_filter($row, function($el) { return ($el!==null); }));
                $month = (($count>=9) && (strtolower(trim($row['A']))!='month')) ? $row['A'] : '';
                if (!empty($month)) {
                    // insert this record
                    db_insert($tableName)
                        ->fields(array(
                                'year' => $year,
                                'month' => $month,
                                'rank' => intval($row['B']),
                                'hs_code' => $row['C'],
                                'description' => $row['D'],
                                'cif' => $row['E'],
                                'volume' => $row['F'],
                                'entries' => $row['G'],
                                'cud' => $row['H'],
                                'cud_to_cif_perc' => $row['I']
                            ))
                        ->execute();
                    $importedCount++;
                }

            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
        drupal_set_message("Operation completed: $deletedCount records deleted, $importedCount imported, $errorsCount errors!");
    }
    
    /**
     * Import data for "Customs - Plastic Resins / Tobacco / Iron & Steel - By Importer" mini - dashboard
     * @param string $path path to data file
     * @param int $year reference year
     * @param string $tableName name of table to save data into
     */
    function import_customs_pti_importers($dataFile, $year, $tableName) {
        // cleanup current data
        $deletedCount = db_delete($tableName)
		  ->condition('year', $year)
		  ->execute();
        $sheetData = dof_dashboard_excel_load($dataFile);
        $importedCount = 0;
        $errorsCount = 0;
        foreach($sheetData as $row) {
            try {
                $count = count(array_filter($row, function($el) { return ($el!==null); }));
                $month = (($count>=8) && (strtolower(trim($row['A']))!='month')) ? $row['A'] : '';
                if (!empty($month)) {
                    // insert this record
                    db_insert($tableName)
                        ->fields(array(
                                'year' => $year,
                                'month' => $month,
                                'rank' => intval($row['B']),
                                'hs_code' => $row['C'],
                                'description' => $row['D'],
                                'importer' => $row['E'],
                                'cif' => $row['F'],
                                'volume' => $row['G'],
                                'cud' => $row['H']
                            ))
                        ->execute();
                    $importedCount++;
                }
            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
        drupal_set_message("Operation completed: $deletedCount records deleted, $importedCount imported, $errorsCount errors!");
    }

