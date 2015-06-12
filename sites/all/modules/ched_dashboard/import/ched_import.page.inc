<?php

    /**
     * Handler for import CHED data action
     */
    function dgph_infographics_import_ched_data() {
        $code = drupal_render(drupal_get_form('dgph_infographics_import_ched_data_form'));
        return $code;
    }


    /**
     *  Create the import CHED data form
     */
    function dgph_infographics_import_ched_data_form($form, &$form_state) {

        $form['#attributes'] = array('class' => array('dashboard'));
        $form['year'] = array(
                '#type' => 'textfield',
		'#required' => true,
                '#title' => t('Enter Year'),
		'#description' => t('Please enter here year range, example : 2010/11'),
                '#attributes' => array(
                        'name' => 'year',
                        'class' => array('number')
                    )
              );

	$depts = array(
		'mini_dashb1_pillar1' => 'Dashboard one pillar 1',
		'mini_dashb1_pillar2' => 'Dashboard one pillar 2',
		'mini_dashb1_pillar3' => 'Dashboard one pillar 3',
		'mini_dashb1_pillar4' => 'Dashboard one pillar 4',
		'mini_dashb2_pillar1' => 'Dashboard two pillar 1',
		'mini_dashb2_pillar2' => 'Dashboard two pillar 2',
		'mini_dashb2_pillar3' => 'Dashboard two pillar 3',
		'mini_dashb3_pillar1' => 'Dashboard three pillar 1',
		'mini_dashb3_pillar2' => 'Dashboard three pillar 2',
		'mini_dashb4_pillar1' => 'Dashboard four pillar 1'
	);

        $form['data_type'] = array(
            '#type' => 'select',
	    '#required' => true,
            '#title' => t('Dashboard/Pillar'),
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
     *  Validator for import CHED data form
     */
    function dgph_infographics_import_ched_data_form_validate($form, &$form_state) {
        
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
    function dgph_infographics_import_ched_data_form_submit($form, &$form_state) {
        $data_type = $form_state['values']['data_type'];
        $data_file = $form_state['values']['data_file'];
        $file_path = drupal_realpath($data_file->uri);

	unset($form_state['values']['data_file']);

	$year = $form_state['values']['year'];

	switch($data_type){
		case 'mini_dashb1_pillar1':
		     import_mini_dashb1_pillar1($file_path, $year);
		     break;
		case 'mini_dashb1_pillar2':
		     import_mini_dashb1_pillar2($file_path, $year);
		     break;
		case 'mini_dashb1_pillar3':
		     import_mini_dashb1_pillar3($file_path, $year);
		     break;
		case 'mini_dashb1_pillar4':
		     import_mini_dashb1_pillar4($file_path, $year);
		     break;
		case 'mini_dashb2_pillar1':
		     import_mini_dashb2_pillar1($file_path, $year);
		     break;
		case 'mini_dashb2_pillar2':
		     import_mini_dashb2_pillar2($file_path, $year);
		     break;
		case 'mini_dashb2_pillar3':
		     import_mini_dashb2_pillar3($file_path, $year);
		     break;
		case 'mini_dashb3_pillar1':
		     import_mini_dashb3_pillar1($file_path, $year);
		     break;
		case 'mini_dashb3_pillar2':
		     import_mini_dashb3_pillar2($file_path, $year);
		     break;
		case 'mini_dashb4_pillar1':
		     import_mini_dashb4_pillar1($file_path, $year);
		     break;
	}

    }


     /**
     * Load import excel file.
     */
    function ched_mini_dashboard_excel_load($dataFile) {
	$libsPath = libraries_get_path('PHPExcel');
        require_once("$libsPath/Classes/PHPExcel.php");
        require_once("$libsPath/Classes/PHPExcel/IOFactory.php");
        $objPHPExcel = PHPExcel_IOFactory::load($dataFile);
        $sheetData = $objPHPExcel->getActiveSheet()->toArray(null, true, false, true);

	return $sheetData;
    }


     /**
     * Import (ched : import_mini_dashb1_pillar1) data file
     * @param data_file path to data file to be imported
     * @param year_range the academic year (e.g. 2013/2014)
     */
    function import_mini_dashb1_pillar1($dataFile, $year_range) {
        $num_deleted = db_delete('ched_mini_dashb1_pillar1')
		  ->condition('financial_year', $year_range)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");
        $sheetData = ched_mini_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        for($x=4; $x<=$rowsCount; $x++){
            try {
		$sector_type	= $sheetData[$x]['A'];
		$score		= $sheetData[$x]['B'];

                if ($sector_type!=null) {
                    db_insert('ched_mini_dashb1_pillar1')
                        ->fields(array(
                                'financial_year', 
                                'sector_type', 
                                'score'
                            ))
                        ->values(array(
                                $year_range,
                                $sector_type,
                                $score
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
     * Import (ched : import_mini_dashb1_pillar2) data file
     * @param data_file path to data file to be imported
     * @param year_range the academic year (e.g. 2013/2014)
     */
    function import_mini_dashb1_pillar2($dataFile, $year_range) {
        $num_deleted = db_delete('ched_mini_dashb1_pillar2')
		  ->condition('financial_year', $year_range)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");
        $sheetData = ched_mini_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        for($x=4; $x<=$rowsCount; $x++){

            try {
		$region			= $sheetData[$x]['A'];
		$main_sucs		= $sheetData[$x]['B'];
		$satellite_sucs		= $sheetData[$x]['C'];
		$lucs			= $sheetData[$x]['D'];
		$ogs			= $sheetData[$x]['E'];
		$phels			= $sheetData[$x]['F'];
		$grand_total		= $sheetData[$x]['G'];
                if ($region!=null) {
                    db_insert('ched_mini_dashb1_pillar2')
                        ->fields(array(
                                'financial_year', 
                                'region',
				'main_sucs',
				'satellite_sucs',
				'lucs',
				'ogs',
				'phels',
                                'grand_total'
                            ))
                        ->values(array(
                                $year_range,
                                $region,
				$main_sucs,
				$satellite_sucs,
				$lucs,
				$ogs,
				$phels,
                                $grand_total
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
     * Import (ched : import_mini_dashb1_pillar3) data file
     * @param data_file path to data file to be imported
     * @param year_range the academic year (e.g. 2013/2014)
     */
    function import_mini_dashb1_pillar3($dataFile, $year_range) {
        $num_deleted = db_delete('ched_mini_dashb1_pillar3')
		  ->condition('financial_year', $year_range)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");
        $sheetData = ched_mini_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        for($x=4; $x<=$rowsCount; $x++){

            try {
		$region				= $sheetData[$x]['A'];
		$state_university_and_colleges	= $sheetData[$x]['B'];
		$local_university_and_colleges	= $sheetData[$x]['C'];
		$other_govt_heis		= $sheetData[$x]['D'];
		$private			= $sheetData[$x]['E'];
		$grand_total			= $sheetData[$x]['F'];
                if ($region!=null) {
                    db_insert('ched_mini_dashb1_pillar3')
                        ->fields(array(
                                'financial_year', 
                                'region',
				'state_university_and_colleges',
				'local_university_and_colleges',
				'other_govt_heis',
				'private',
                                'grand_total'
                            ))
                        ->values(array(
                                $year_range,
                                $region,
				$state_university_and_colleges,
				$local_university_and_colleges,
				$other_govt_heis,
				$private,
                                $grand_total
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
     * Import (ched : import_mini_dashb1_pillar4) data file
     * @param data_file path to data file to be imported
     * @param year_range the academic year (e.g. 2013/2014)
     */
    function import_mini_dashb1_pillar4($dataFile, $year_range) {
        $num_deleted = db_delete('ched_mini_dashb1_pillar4')
		  ->condition('financial_year', $year_range)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");
        $sheetData = ched_mini_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        for($x=4; $x<=$rowsCount; $x++){

            try {
		$region				= $sheetData[$x]['A'];
		$state_university_and_colleges	= $sheetData[$x]['B'];
		$local_university_and_colleges	= $sheetData[$x]['C'];
		$other_govt_heis		= $sheetData[$x]['D'];
		$private			= $sheetData[$x]['E'];
		$grand_total			= $sheetData[$x]['F'];
                if ($region!=null) {
                    db_insert('ched_mini_dashb1_pillar4')
                        ->fields(array(
                                'financial_year', 
                                'region',
				'state_university_and_colleges',
				'local_university_and_colleges',
				'other_govt_heis',
				'private',
                                'grand_total'
                            ))
                        ->values(array(
                                $year_range,
                                $region,
				$state_university_and_colleges,
				$local_university_and_colleges,
				$other_govt_heis,
				$private,
                                $grand_total
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
     * Import (ched : import_mini_dashb2_pillar1) data file
     * @param data_file path to data file to be imported
     * @param year_range the academic year (e.g. 2013/2014)
     */
    function import_mini_dashb2_pillar1($dataFile, $year_range) {
        $num_deleted = db_delete('ched_mini_dashb2_pillar1')
		  ->condition('financial_year', $year_range)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");
        $sheetData = ched_mini_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        for($x=4; $x<=$rowsCount; $x++){

            try {
		$discipline_group = $sheetData[$x]['A'];
		$enrolment		  = $sheetData[$x]['B'];
		$graduates		  = $sheetData[$x]['C'];
                if ($discipline_group!=null) {
                    db_insert('ched_mini_dashb2_pillar1')
                        ->fields(array(
                                'financial_year', 
                                'discipline_group', 
                                'enrolment',
				'graduates'
                            ))
                        ->values(array(
                                $year_range,
                                $discipline_group,
                                $enrolment,
				$graduates
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
     * Import (ched : import_mini_dashb2_pillar2) data file
     * @param data_file path to data file to be imported
     * @param year_range the academic year (e.g. 2013/2014)
     */
    function import_mini_dashb2_pillar2($dataFile, $year_range) {
        $num_deleted = db_delete('ched_mini_dashb2_pillar2')
		  ->condition('financial_year', $year_range)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");
        $sheetData = ched_mini_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        for($x=4; $x<=$rowsCount; $x++){

	    try {
		$oversubscribed_program   = $sheetData[$x]['A'];
		$enrolment		  = $sheetData[$x]['B'];
		$graduates		  = $sheetData[$x]['C'];

                if ($oversubscribed_program!=null) {
                    db_insert('ched_mini_dashb2_pillar2')
                        ->fields(array(
                                'financial_year', 
                                'oversubscribed_program', 
				'enrolment', 
                                'graduates'
                            ))
                        ->values(array(
                                $year_range,
                                $oversubscribed_program,
				$enrolment,
                                $graduates
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
     * Import (ched : import_mini_dashb2_pillar3) data file
     * @param data_file path to data file to be imported
     * @param year_range the academic year (e.g. 2013/2014)
     */
    function import_mini_dashb2_pillar3($dataFile, $year_range) {
        $num_deleted = db_delete('ched_mini_dashb2_pillar3')
		  ->condition('financial_year', $year_range)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");
        $sheetData = ched_mini_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        for($x=4; $x<=$rowsCount; $x++){

            try {
		$undersubscribed_program  = $sheetData[$x]['A'];
		$enrolment		  = $sheetData[$x]['B'];
		$graduates		  = $sheetData[$x]['C'];

                if ($undersubscribed_program!=null) {
                    db_insert('ched_mini_dashb2_pillar3')
                        ->fields(array(
                                'financial_year', 
                                'undersubscribed_program', 
				'enrolment', 
                                'graduates'
                            ))
                        ->values(array(
                                $year_range,
                                $undersubscribed_program,
				$enrolment,
                                $graduates
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
     * Import (ched : import_mini_dashb3_pillar1) data file
     * @param data_file path to data file to be imported
     * @param year_range the academic year (e.g. 2013/2014)
     */
    function import_mini_dashb3_pillar1($dataFile, $year_range) {
        $num_deleted = db_delete('ched_mini_dashb3_pillar1')
		  ->condition('financial_year', $year_range)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");
        $sheetData = ched_mini_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        for($x=4; $x<=$rowsCount; $x++){

            try {
		$discipline		= $sheetData[$x]['A'];
		$passing_precentage	= $sheetData[$x]['B'];

		if ($discipline!=null) {
                    db_insert('ched_mini_dashb3_pillar1')
                        ->fields(array(
                                'financial_year', 
                                'discipline', 		
                                'passing_precentage'
                            ))
                        ->values(array(
                                $year_range,
                                $discipline,
                                $passing_precentage
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
     * Import (ched : import_mini_dashb3_pillar2) data file
     * @param data_file path to data file to be imported
     * @param year_range the academic year (e.g. 2013/2014)
     */
    function import_mini_dashb3_pillar2($dataFile, $year_range) {
        $num_deleted = db_delete('ched_mini_dashb3_pillar2')
		  ->condition('financial_year', $year_range)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");
        $sheetData = ched_mini_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        for($x=4; $x<=$rowsCount; $x++){

            try {
		$region		= $sheetData[$x]['A'];
		$public		= $sheetData[$x]['B'];
		$private	= $sheetData[$x]['C'];
		$both_sector	= $sheetData[$x]['D'];

                if ($region!=null) {
                    db_insert('ched_mini_dashb3_pillar2')
                        ->fields(array(
                                'financial_year', 
                                'region', 
				'public', 
				'private',
                                'both_sector'
                            ))
                        ->values(array(
                                $year_range,
                                $region,
				$public,
				$private,
                                $both_sector
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
     * Import (ched : import_mini_dashb4_pillar1) data file
     * @param data_file path to data file to be imported
     * @param year_range the academic year (e.g. 2013/2014)
     */
    function import_mini_dashb4_pillar1($dataFile, $year_range) {
        $num_deleted = db_delete('ched_mini_dashb4_pillar1')
		  ->condition('financial_year', $year_range)
		  ->execute();
        drupal_set_message("$num_deleted records deleted!");
        $sheetData = ched_mini_dashboard_excel_load($dataFile);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        for($x=4; $x<=$rowsCount; $x++){

            try {
		$region		= $sheetData[$x]['A'];
		$suc_name	= $sheetData[$x]['B'];
		$ps	= $sheetData[$x]['C'];
		$mood	= $sheetData[$x]['D'];
		$co	= $sheetData[$x]['E'];
		$total	= $sheetData[$x]['F'];
		$psc	= $sheetData[$x]['G'];
		$ba_bs	= $sheetData[$x]['H'];
		$ma_ms	= $sheetData[$x]['I'];
		$phd	= $sheetData[$x]['J'];

		if ($region!=null) {
                    db_insert('ched_mini_dashb4_pillar1')
                        ->fields(array(
                                'financial_year', 
                                'region', 
				'suc_name',
				'ps',
				'mood',
				'co',
				'total',
				'psc',
				'ba_bs',
				'ma_ms',		
                                'phd'
                            ))
                        ->values(array(
                                $year_range,
                                $region,
				$suc_name,
				$ps,
				$mood,
				$co,
				$total,
				$psc,
				$ba_bs,
				$ma_ms,				
                                $phd
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


