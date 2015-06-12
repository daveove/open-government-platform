<?php
    define("MIN_DATES_DIFF", 25569);
    define("SEC_IN_DAY", 86400); 

    /**
     *  Import DBM form
     */
    function dgph_infographics_dbm_import_form() {
        $form=array();
        $form['description'] = array(
           '#type' => 'item',
           '#title' => '<h2>Import DBM data</h2>',
         );
        $form['#attributes'] = array(
                'enctype' => "multipart/form-data",
                'class' => array('dashboard')
            );
        $form['dbm_excel_file'] = array(
            '#title' => 'Path to data file (*.xlsx)',
            '#type' => 'file',
            '#size' => 80,
            '#required' => false,
            '#suffix' => ""
        ); 
        $form['submit'] = array(
            '#value' => t('Start Import'),
            '#type' => 'submit',
        );        
        return $form;    
    }
    
    /**
     *  Validator for import DBM form
     */
    function dgph_infographics_dbm_import_form_validate($form, &$form_state) {
        $file = file_save_upload('dbm_excel_file', array(
                    'file_validate_extensions' => array('xlsx')
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
     *  Handler for DBM form submit
     */
    function dgph_infographics_dbm_import_form_submit($form, &$form_state) {
        module_load_include('inc', 'phpexcel', 'phpexcel');
        
        $dataFile = $form_state['values']['data_file'];
        $filePath = drupal_realpath($dataFile->uri);
        unset($form_state['values']['data_file']);
        $successCount = 0;
        $errorCount = 0;
        // load records from file
        $cells = phpexcel_import($filePath);
        if (is_array($cells)) {
            // import records to database
            $rows = $cells[0];
            foreach($rows as $row) {
                try {
                    // check if this record is a duplicate
                    $year = isset($row['year']) ? $row['year'] : (isset($row['Year']) ? $row['Year'] : null);
                    $qt = isset($row['quarter']) ? $row['quarter'] : (isset($row['Quarter']) ? $row['Quarter'] : null);
                    $agency = $row['agency'];
                    $record = $row['record'];
                    if (!empty($year) && !empty($qt) && !empty($agency) && !empty($record)) {
                        $query = db_select('t_budget_data', 'b')
                                    ->condition('year', $year)
                                    ->condition('quarter', $qt)
                                    ->condition('agency', $agency)
                                    ->condition('record', $record);
                        $numRows = $query->countQuery()->execute()->fetchField();
                        if ($numRows==0) {
                            // insert the new record
                            $obrigRate = str_replace(array('%'), '', $row['obligrate']);
                            db_insert('t_budget_data')
                                    ->fields(array(
                                            'year' => $year,
                                            'quarter' => $qt,
                                            'agency' => $agency,
                                            'record' => $record,
                                            'record_label' => trim($row['record_label']),
                                            'approp' => floatval($row['approp']),
                                            'allot_ps' => floatval($row['allot_ps']),
                                            'allot_mode' => floatval($row['allot_mode']),
                                            'allot_co' => floatval($row['allot_co']),
                                            'allot_tot' => floatval($row['allot_tot']),
                                            'oblig_ps' => floatval($row['oblig_ps']),
                                            'oblig_mode' => floatval($row['oblig_mode']),
                                            'oblig_co' => floatval($row['oblig_co']),
                                            'oblig_tot' => floatval($row['oblig_tot']),
                                            'uoblig_ps' => floatval($row['uoblig_ps']),
                                            'uoblig_mode' => floatval($row['uoblig_mode']),
                                            'uoblig_co' => floatval($row['uoblig_co']),
                                            'uoblig_tot' => floatval($row['uoblig_tot']),
                                            'obligrate' => floatval($obrigRate),
                                            'compliance' => trim($row['compliance'])
                                        ))
                                    ->execute();
                            $successCount++;
                        }
                    }
                }
                catch(Exception $e) {
                   $errorCount++;
                }
            }
            drupal_set_message("Operation completed: $successCount records successfully imported, $errorCount errors!");
        }
        else {
            drupal_set_message("An error occured while processing input file!", 'error');
        }
    }
    
    
    /**
     *  Import commodity form
     */
    function dgph_infographics_commodity_import_form() {
        drupal_set_title("");
        $form=array();
         $form['description'] = array(
            '#type' => 'item',
            '#title' => '<h2>Import Commodity data</h2>',
          );
        $form['#attributes'] = array(
                'enctype' => "multipart/form-data",
                'class' => array('dashboard')
            );
        $form['commodity_excel_file'] = array(
            '#title' => 'Path to data file (*.xlsx)',
            '#type' => 'file',
            '#size' => 80,
            '#required' => false,
            '#suffix' => ""
        ); 
        $form['submit'] = array(
            '#value' => t('Start Import'),
            '#type' => 'submit',
        );        
        return $form;    
    }
    
    /**
     *  Validator for import commodity form
     */
    function dgph_infographics_commodity_import_form_validate($form, &$form_state) {
        $file = file_save_upload('commodity_excel_file', array(
                    'file_validate_extensions' => array('xlsx')
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
    function verify_categories() {
        $categories = array();
  
        $result = db_query("SELECT cid, title FROM {pm_categories} ORDER BY cid desc");
        if($result->rowCount() > 0):
          $categories = $result->fetchAllAssoc('title');
              foreach($categories as $category):
                $result = db_query("SELECT pid, title FROM {pm_products} WHERE cid = :cid", array(':cid' => $category->cid));
                $products = $result->fetchAllAssoc('title');	
                if($result->rowCount() > 0):
                  $category->products = $products;
                else:
                  $category->products = new stdClass();
                endif;  
              endforeach;
        endif;
        return $categories ;  
    }
    function insert_category($category_name) {
        $entry = array(
          'title' => $category_name,
              'status' => 'Enabled',
              'parent' => 0,
              'weight' => 0,
              'added_on' => format_date(time(), 'custom', 'Y-m-d H:i:s'),
        );

        $id = db_insert('pm_categories')
                        ->fields($entry)
                        ->execute(); 
        return $id;				  		
      }

    function insert_product($product_name, $category_id) {
        $entry = array(
            'title' => $product_name,
                'status' => 'Enabled',
                'cid' => $category_id,
                'added_on' => format_date(time(), 'custom', 'Y-m-d H:i:s'),
          );
  
        $id = db_insert('pm_products')
                  ->fields($entry)
                  ->execute(); 
        return $id;				  		
    }

    function insert_product_price($product_id, $dated, $price) {
      $entry = array(
            'pid' => $product_id,
            'price' => $price,
            'dated' => $dated,	
            'added_on' => format_date(time(), 'custom', 'Y-m-d H:i:s'),
      );

      $id = db_insert('pm_product_price')
                      ->fields($entry)
                      ->execute(); 
      return $id;	
    }
    function non_empty(array $a) {
        return array_sum(array_map(function($b) {return empty($b) ? 0 : 1;}, $a));
    }
    
    
    function excel2timestamp($excelDate) {
       if ($excelDate <= MIN_DATES_DIFF)
          return 0;
       return  ($excelDate - MIN_DATES_DIFF) * SEC_IN_DAY;
    }
    
    /**
     * Cleanup commodities
     */
    function cleanup_commodities() {
        db_delete('pm_product_price')->execute();
    }
    
    /**
     *  Handler for commodity form submit
     */   
    function dgph_infographics_commodity_import_form_submit($form, &$form_state) {
        $libsPath = libraries_get_path('PHPExcel');
        require_once("$libsPath/Classes/PHPExcel.php");
        require_once("$libsPath/Classes/PHPExcel/IOFactory.php");
        
        // cleanup current prices
        cleanup_commodities();
        
        $dataFile = $form_state['values']['data_file'];
        $filePath = drupal_realpath($dataFile->uri);
        unset($form_state['values']['data_file']);
        $catsCount = 0;
        $prodsCount = 0;
        $pricesCount = 0;
        $errorCount = 0;
        try {
            // load records from file
            $objPHPExcel = PHPExcel_IOFactory::load($filePath);
            $objWorksheet = $objPHPExcel->getActiveSheet();
            $worksheetTitle = $objWorksheet->getTitle();
            $highestRow = $objWorksheet->getHighestRow(); // e.g. 10
            $highestColumn = $objWorksheet->getHighestColumn(); // e.g 'F'
            $highestColumnIndex = PHPExcel_Cell::columnIndexFromString($highestColumn);
            $nrColumns = ord($highestColumn) - 64;
            $rowIterator = $objWorksheet->getRowIterator();	
      
            $records = array();
            foreach($rowIterator as $row){
                $cellIterator = $row->getCellIterator();
                $cellIterator->setIterateOnlyExistingCells(true); // Loop all cells, even if it is not set
                $rowIndex = $row->getRowIndex();	
                foreach ($cellIterator as $cell) {
                    $records[$rowIndex][$cell->getColumn()] = $cell->getCalculatedValue();
                }
            }
  
            $header = $records[1];
            unset($records[1]);
  
            $categories = verify_categories();  
            foreach($records as $record):
                $is_category = non_empty($record);
                if($is_category == 1):
                    if(isset($record['A'])):
                        $category = $record['A'];
                        if(isset($categories[$category]->cid)):
                            $category_id = $categories[$category]->cid;
                        else:
                            $category_id = insert_category($category);
                            $catsCount++;
                        endif;
                        continue;	  
                    endif;
                endif;
	
                foreach($record as $key => $value):
                    if($key == 'A'):
                        $product = $value;
                        if(isset($categories[$category]->products[$product]->pid)):
                            $product_id = $categories[$category]->products[$product]->pid;
                        else:
                            $product_id = insert_product($product, $category_id);
                            $prodsCount++;
                        endif;
                        continue;
                    endif;
                    if(isset($header[$key]) and !empty($header[$key])):
                        if(is_numeric($header[$key])):
                            $timestamp = excel2timestamp($header[$key]);
                            $dated = format_date($timestamp, 'custom', 'Y-m-d H:i:s');
                            $price = $value;
                            insert_product_price($product_id, $dated, $price);
                            $pricesCount++;
                        endif;
                    endif;
                endforeach;
            endforeach;
        }
        catch(Exception $e) {
           $errorCount++;
        }  
        drupal_set_message("Operation completed: imported $catsCount categories, $prodsCount products, $pricesCount product prices ($errorCount errors)!");
    }
    
    /**
     * Handler for import procurement data action
     */
    function dgph_infographics_import_procurement_data() {
        // load departments
        $query = db_select('t_departments', 'd')
                        ->fields('d');
	$res = $query->execute();
        $depts = array();
        foreach($res as $row) {
            $depts[$row->id] = $row->name.' ('.$row->code.')';
        }
        drupal_set_title("");
        $code = drupal_render(drupal_get_form('dgph_infographics_import_procurement_data_form', $depts));
        return $code;
    }
    
    
    /**
     *  Create the import procurement data form
     */
    function dgph_infographics_import_procurement_data_form($form, &$form_state, $depts) {
        $form['description'] = array(
            '#type' => 'item',
            '#title' => '<h1>Import Procurement Compliance and Performance Indicators</h1>',
          );
        $form['#attributes'] = array('class' => array('dashboard'));
        $form['year'] = array(
                '#type' => 'textfield',
                '#title' => t('Enter Year'),
                '#attributes' => array(
                        'name' => 'year',
                        'class' => array('number')
                    )
              );
        $form['data_file'] = array(
            '#type' => 'file',
            '#title' => 'Path to data file'
        );
        // Submit button
        $form['submit'] = array(
          '#type' => 'submit',
          '#value' => 'Update',
        );

        return $form;
    }
    
    /**
     *  Validator for import procurement data form
     */
    function dgph_infographics_import_procurement_data_form_validate($form, &$form_state) {
        // validate year
        $year = $form_state['input']['year'];
        $minYear = 2010;
        $maxYear = date("Y");
        if ((null==$year) || !is_numeric($year) || intval($year)<$minYear || intval($year)>$maxYear) {
            form_set_error('year', t("Year must be an integer value in the range $minYear - $maxYear."));
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
    
    function strip_tags_content($text, $tags = '', $invert = FALSE) {
        preg_match_all('/<(.+?)[\s]*\/?[\s]*>/si', trim($tags), $tags);
        $tags = array_unique($tags[1]);

        if(is_array($tags) AND count($tags) > 0) {
            if($invert == FALSE) {
                return preg_replace('@<(?!(?:'. implode('|', $tags) .')\b)(\w+)\b.*?>.*?</\1>@si', '', $text);
            }
            else {
                return preg_replace('@<('. implode('|', $tags) .')\b.*?>.*?</\1>@si', '', $text);
            }
        }
        elseif($invert == FALSE) {
            return preg_replace('@<(\w+)\b.*?>.*?</\1>@si', '', $text);
        }
        return $text;
    } 
    
    /**
     * Gets information about an APCPI record
     * @param str the source string
     * @return information about the record
     */
    function extractApcpiInfo($str) {
        $info = array();
        $pos = strpos($str, '::');
        if ($pos>-1) {
            $label = substr($str, $pos+2);
            $id = substr($str, 6, $pos-6);
        }
        $pos = strpos($str, '--');
        if ($pos>-1) {
            $label = substr($str, $pos+2);
            $id = substr($str, 9, $pos-9);
        }
        $pos = strpos($str, ')');
        if ($pos>-1) {
            $label = substr($str, $pos+1);
            $id = substr($str, $pos-1, 1);
        }
        $info['id'] = !empty($id) ? $id : 0;
        $info['label'] = !empty($label) ? trim($label) : '';
        return $info;
    }
    /**
     * Import agency procurement compliant and personal indicator (apcpi) data file
     * @param dataFile path to data file to be imported
     * @param year the reference year
     */
    function importApcpiData($dataFile, $year) {
        $libsPath = libraries_get_path('PHPExcel');
        require_once("$libsPath/Classes/PHPExcel.php");
        require_once("$libsPath/Classes/PHPExcel/IOFactory.php");
        $objPHPExcel = PHPExcel_IOFactory::load($dataFile);
        $sheetData = $objPHPExcel->getActiveSheet()->toArray(null, true, false, true);
        $rowsCount = count($sheetData);
        $importedCount = 0;
        $errorsCount = 0;
        $deptsResults = array('H'=>'DBM', 'J'=>'DOST', 'L'=>'DOH', 'N'=>'DPWH', 'P'=>'DFA', 'R'=>'DENR', 'T'=>'DOF', 'V'=>'DOJ', 'X'=>'DND', 'Z'=>'DAR',
                              'AB'=>'DOT', 'AD'=>'DOE', 'AF'=>'DTI', 'AH'=>'DOLE', 'AJ'=>'DILG', 'AL'=>'DepEd', 'AN'=>'DA', 'AP'=>'DSWD');
        $ratingsCols = array('I', 'K', 'M', 'O', 'Q', 'S', 'U', 'W', 'Y', 'AA', 'AC', 'AE', 'AG', 'AI', 'AK', 'AM', 'AO', 'AQ');
        $deptsCount = count($deptsResults);
        for($idx=4; $idx<=$rowsCount; $idx++){
            try {
                // extract data from Excel row
                $info = extractApcpiInfo($sheetData[$idx]['B']);
                $pillarId = intval($info['id']);
                $pillar = $info['label'];
                $info = extractApcpiInfo($sheetData[$idx]['C']);
                $indicatorId = intval($info['id']);
                $indicator = $info['label'];
                $info = extractApcpiInfo($sheetData[$idx]['D']);
                $itemId = $info['id'];
                $item = $info['label'];
                $benchmark = $sheetData[$idx]['E'];
                $avgResult = $sheetData[$idx]['F'];
                $avgRating = floatval($sheetData[$idx]['G']);
                if (!empty($pillar)) {
                    // save indicator information
                    $pid = db_insert('t_procurement_indicators')
                                ->fields(array(
                                        'year', 
                                        'pillar_id', 
                                        'pillar', 
                                        'indicator_id',
                                        'indicator', 
                                        'item_id', 
                                        'item', 
                                        'benchmark', 
                                        'average_all_results', 
                                        'average_all_ratings'
                                    ))
                                ->values(array(
                                        $year,
                                        $pillarId,
                                        $pillar,
                                        $indicatorId,
                                        $indicator,
                                        $itemId,
                                        $item,
                                        $benchmark,
                                        $avgResult,
                                        $avgRating
                                    ))
                                ->execute();
                    $jdx = 0;
                    foreach($deptsResults as $colId=>$dept) {
                        $result = $sheetData[$idx][$colId];
                        $nextColId = $ratingsCols[$jdx++];
                        $rating = floatval($sheetData[$idx][$nextColId]);
                        // save department data
                        db_insert('t_procurement_indicators_departments')
                            ->fields(array(
                                    'procurement_indicator_id', 
                                    'department_code', 
                                    'result', 
                                    'rating'
                                ))
                            ->values(array(
                                    $pid,
                                    $dept,
                                    $result,
                                    $rating
                                ))
                            ->execute();
                    }
                    $importedCount++;
                }
                else {
                    $pillarId = -1;
                    $item = strtolower($sheetData[$idx]['A']);
                    if (strpos($item, 'pillar') === 0) {
                        // get pillar id
                        $pillarLabels = array(1=>'pillar# i score', 2=>'pillar# ii score', 3=>'pillar# iii score', 4=>'pillar# iv score');
                        $pillarId = array_search($item, $pillarLabels);
                    }
                    else if ($item=='total average') {
                        // all pillars
                        $pillarId = 0;
                    }
                    if ($pillarId>=0) {
                        // save total average for this pillar
                        $totalAvg = $sheetData[$idx]['G'];
                        db_insert('t_procurement_indicators')
                            ->fields(array(
                                        'year' => $year,
                                        'pillar_id' => $pillarId,
                                        'pillar' => 'Pillar Total Average',
                                        'indicator_id' => 0,
                                        'indicator' => '',
                                        'item_id' => '',
                                        'item' => '',
                                        'benchmark' => 0,
                                        'average_all_results' => 0, 
                                        'average_all_ratings' => $totalAvg
                                    ));
                        // save agencies averages
                        $jdx = 0;
                        foreach($deptsResults as $colId=>$dept) {
                            $nextColId = $ratingsCols[$jdx++];
                            $rating = floatval($sheetData[$idx][$nextColId]);
                            // save department average
                            db_insert('t_procurement_indicators_averages')
                                ->fields(array(
                                        'year', 
                                        'department_code', 
                                        'pillar_id', 
                                        'average_rating'
                                    ))
                                ->values(array(
                                        $year,
                                        $dept,
                                        $pillarId,
                                        $rating
                                    ))
                                ->execute();
                        }
                    }
                    else {
                        // save grand total average
                        $totalAvg = $sheetData[$idx]['G'];
                        db_insert('t_procurement_indicators')
                            ->fields(array(
                                        'year' => $year,
                                        'pillar_id' => 0,
                                        'pillar' => 'Pillar Total Average',
                                        'indicator_id' => 0,
                                        'indicator' => '',
                                        'item_id' => '',
                                        'item' => '',
                                        'benchmark' => 0,
                                        'average_all_results' => 0, 
                                        'average_all_ratings' => $totalAvg
                                    ));
                    }
                }
            }
            catch(Exception $e) {
                $errorsCount++;
            }
        }
        drupal_set_message("Operation completed: $importedCount records imported, $errorsCount errors!");
    }
    
    /**
     * Submit handler for import procurement data form
     */
    function dgph_infographics_import_procurement_data_form_submit($form, &$form_state) {
        $dataFile = $form_state['values']['data_file'];
        $filePath = drupal_realpath($dataFile->uri);
        unset($form_state['values']['data_file']);
        $year = $form_state['values']['year'];
        importApcpiData($filePath, $year);
    }
    
    /**
     *  Create the import education data form
     */
    function dgph_infographics_education_import_form($form, &$form_state) {
        $form['description'] = array(
            '#type' => 'item',
            '#title' => '<h1>Import Education Data</h1>',
          );
        $form['#attributes'] = array('class' => array('dashboard'));
        $form['year'] = array(
                '#type' => 'textfield',
                '#title' => t('Enter Year'),
                '#attributes' => array(
                        'name' => 'year',
                        'class' => array('number')
                    )
              );
        $form['data_file'] = array(
            '#type' => 'file',
            '#title' => 'Path to data file'
        );
        // Submit button
        $form['submit'] = array(
          '#type' => 'submit',
          '#value' => 'Update',
        );
        return $form;
    }
    
    /**
     *  Validator for import education data form
     */
    function dgph_infographics_education_import_form_validate($form, &$form_state) {
        // validate year
        $year = $form_state['input']['year'];
        $minYear = 2010;
        $maxYear = date("Y");
        if ((null==$year) || !is_numeric($year) || intval($year)<$minYear || intval($year)>$maxYear) {
            form_set_error('year', t("Year must be an integer value in the range $minYear - $maxYear."));
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
     *  Handler for education form submit
     */   
    function dgph_infographics_education_import_form_submit($form, &$form_state) {
        module_load_include('inc', 'phpexcel', 'phpexcel');
        
        $year = $form_state['values']['year'];
        $dataFile = $form_state['values']['data_file'];
        $filePath = drupal_realpath($dataFile->uri);
        unset($form_state['values']['data_file']);
        $successCount = 0;
        $errorCount = 0;
        // load records from file
        $cells = phpexcel_import($filePath, false);
        if (is_array($cells)) {
            // skip first row (header)
            $rows = $cells[0];
            array_shift($rows);
            foreach($rows as $row) {
                try {
                    // fetch row values
                    $region = $row[0];
                    $province = $row[1];
                    $municipality = $row[2];
                    $division = $row[3];
                    $schoolId = $row[4];
                    $schoolName = $row[5];
                    $schoolType = $row[6];
                    $y1m = isset($row[7]) ? intval($row[7]) : 0;
                    $y1f = isset($row[8]) ? intval($row[8]) : 0;
                    $y2m = isset($row[9]) ? intval($row[9]) : 0;
                    $y2f = isset($row[10]) ? intval($row[10]) : 0;
                    $y3m = isset($row[11]) ? intval($row[11]) : 0;
                    $y3f = isset($row[12]) ? intval($row[12]) : 0;
                    $y4m = isset($row[13]) ? intval($row[13]) : 0;
                    $y4f = isset($row[14]) ? intval($row[14]) : 0;
                    $y5m = isset($row[15]) ? intval($row[15]) : 0;
                    $y5f = isset($row[16]) ? intval($row[16]) : 0;
                    $y6m = isset($row[17]) ? intval($row[17]) : 0;
                    $y6f = isset($row[18]) ? intval($row[18]) : 0;
                    // save the record to DB
                    db_insert('t_education')
                                ->fields(array('year', 'region', 'province', 'municipality', 'division', 'school_id', 'school_name', 'school_type',
                                               'y1m', 'y1f', 'y2m', 'y2f', 'y3m', 'y3f', 'y4m', 'y4f', 'y5m', 'y5f', 'y6m', 'y6f'
                                    ))
                                ->values(array(
                                        $year, $region, $province, $municipality, $division, $schoolId, $schoolName, $schoolType,
                                        $y1m, $y1f, $y2m, $y2f, $y3m, $y3f, $y4m, $y4f, $y5m, $y5f, $y6m, $y6f
                                    ))
                                ->execute();
                    $successCount++;
                }
                catch(Exception $e) {
                   $errorCount++;
                }
            }
            drupal_set_message("Operation completed: $successCount records successfully imported, $errorCount errors!");
        }
        else {
            drupal_set_message("An error occured while processing input file!", 'error');
        }
    }