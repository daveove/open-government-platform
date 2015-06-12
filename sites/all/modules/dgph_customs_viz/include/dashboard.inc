<?php
    /**
     * Landing page for Customs Vizualization Dashboard 
     * @param int $view view identifier
     * @param int $year reference year
     * @param int $entityId custom entity (e.g. port, commodity) identifier (0 = not applicable)
     */
    function dgph_customs_viz_index($view = 1, $year = 2013, $entityId = 0) {
        $dashb = array('view' => $view, 'year' => $year, 'charts'=>array());
        drupal_set_title("");
        drupal_add_js('sites/all/libraries/highcharts/js/highcharts.js');
        drupal_add_js('sites/all/libraries/highcharts/js/highcharts-more.js');
        drupal_add_js('sites/all/libraries/highcharts/plugins/crossing-specific-value/crossing-specific-value.js');
        $modPath =  drupal_get_path('module', 'dgph_customs_viz');
        drupal_add_js($modPath.'/js/customs-viz-scripts.js');
        $viewName = null;
        switch($view) {
            case VIEW_TOTAL_BOC:
                $dashb['charts'] = dgph_customs_viz_get_total_boc_charts($year);
                $viewName = 'customs_viz';
                break;
            case VIEW_PORT:
                $dashb['charts'] = dgph_customs_viz_get_port_view_charts($year, $entityId);
                $viewName = 'port_view';
                break;
            case VIEW_COMMODITY:
                $dashb['charts'] = dgph_customs_viz_get_commodity_view_charts($year, $entityId);
                $viewName = 'commodity_view';
                break;
            case VIEW_BROKERS_IMPORTERS:
                $dashb['charts'] = dgph_customs_viz_get_brokers_importers_view_charts($year);
                $viewName = 'brokers_importers_view';
                break;
        }
        return theme($viewName, $dashb);
    }
    
    /**
     * Builds a column chart containing Customs monthly data
     * @param array $dataSeries the data series
     * @param array $options configuration options
     * @return the chart configuration
     */
    function cviz_build_column_chart($dataSeries, $options = array()) {
        $chartType = array_key_exists('chart-type', $options) ? $options['chart-type'] : 'basic';
        $chartConfig = array(
                            "chart" => array("type"=>"column", "backgroundColor"=>"#E6E7E7"),
                            "credits" => array("enabled" => false),
                            "title" => array("text" => ""),
                            "legend" => array("enabled" => false),
                            "plotOptions" => array(
                                    "column" => array(
                                        "borderColor" => "transparent",
                                        "color" => "#2D9B49",
                                        "pointPadding" => -0.1,
                                        "negativeColor" => "#851618"
                                    )
                                ),
                            "xAxis" => array(
                                    "categories" => array("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"),
                                    "lineColor" => "#000000",
                                    "gridLineWidth" => 0,
                                    "minorGridLineWidth" => 0
                                ),
                            "yAxis" => array(
                                    "lineColor" => "#000000",
                                    "lineWidth" => 1,
                                    "gridLineWidth" => 0,
                                    "minorGridLineWidth" => 0
                                ),
                            "tooltip" => array("formatter" => null),
                            "series" => $dataSeries,
                            "cvizOptions" => array("chartType" => $chartType)
                        );
        if ($chartType=='basic') {
            $chartConfig['yAxis']['min'] = 0;
            $chartConfig['plotOptions']['column']['dataLabels'] = array(
                                                                "enabled" => true,
                                                                "y" => 30,
                                                                "color" => "#FFFFFF",
                                                                "style" => array("fontSize" => "10px"),
                                                                "format" => array_key_exists('data-labels-format', $options) ? $options['data-labels-format'] : '{y}'
                                                            );
        }
        else {
            $chartConfig['plotOptions']['column']['dataLabels'] = array(
                                                                "enabled" => true, 
                                                                "color" => "#000000"
                                                            );
            $chartConfig['yAxis']['lineWidth'] = 0;
            $chartConfig['yAxis']['title'] = array("text" => "");
            $chartConfig['yAxis']['labels'] = array("enabled" => false);
            $chartConfig['xAxis']['crossing'] = 0;
            $chartConfig['xAxis']['opposite'] = true;
            $chartConfig['xAxis']['labels'] = array("enabled" => false);
        }
        if (array_key_exists('y-title', $options)) {
            $chartConfig['yAxis']['title'] = array(
                                "text" => $options['y-title'], 
                                "style" => array("color" => "#000000", "fontWeight" => "normal", "textTransform" => "uppercase")
                            );
        }
        return $chartConfig;
    }
    
    /**
     * Builds a column chart containing Customs monthly data
     * @param array $dataSeries the data series
     * @param array $options configuration options
     * @return the chart configuration
     */
    function cviz_build_bubble_chart($dataSeries, $options = array()) {
        $chartConfig = array(
                            "chart" => array("type"=>"bubble", "zoomType" => "xy", "backgroundColor" => "#E6E7E7"),
                            "credits" => array("enabled" => false),
                            "title" => array(
                                                "text" => "IN BILLION PESOS",
                                                "verticalAlign" => "bottom",
                                                "y" => -25,
                                                "style" => array("color" => "#000000", "fontSize" => "12px")
                                            ),
                            "legend" => array(
                                        "enabled" => true, 
                                        "align" => "center",
                                        "y" => 10
                                    ),
                            "colors" => array("#B6DBB3", "#449A49"),
                            "plotOptions" => array(
                                    "bubble" => array(
                                        "maxSize" => "50%",
                                        "tooltip" => array("pointFormat" => "<b>{point.z}</b>")
                                    )
                                ),
                            "xAxis" => array(
                                    "categories" => array("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"),
                                    "labels" => array("enabled" => true, "style" => array("fontWeight" => "bold")),
                                    "lineWidth" => 0,
                                    "tickWidth" => 0,
                                    "min" => 0,
                                    "max" => 11,
                                    "opposite" => true
                                ),
                            "yAxis" => array(
                                    "lineWidth" => 0,
                                    "title" => array("text" => ""),
                                    "labels" => array("enabled" => false)
                                ),
                            "series" => $dataSeries
                        );
        if (array_key_exists('x-title', $options)) {
            $chartConfig['xAxis']['title'] = array(
                                "text" => $options['x-title'], 
                                "style" => array("color" => "#000000", "fontWeight" => "normal", "textTransform" => "uppercase")
                            );
        }
        return $chartConfig;
    }
    
    /**
     * Builds an area chart containing Customs monthly data
     * @param array $dataSeries the data series
     * @param array $options configuration options
     * @return the chart configuration
     */
    function cviz_build_area_chart($dataSeries, $options = array()) {
        $chartConfig = array(
                                "chart" => array("type" => "area", "backgroundColor" => "#E6E7E7"),
                                "credits" => array("enabled" => false),
                                "title" => array("text" => ""),
                                "legend" => array("enabled" => false),
                                "plotOptions" => array(
                                    "area" => array(
                                        "dataLabels" => array(
                                                "enabled" => true,
                                                "y" => 40,
                                                "color" => "#FFFFFF",
                                                "style" => array("fontSize" => "10px"),
                                                "padding" => 4
                                            ),
                                        "marker" => array("enabled" => true)
                                    )
                                ),
                                "xAxis" => array(
                                        "categories" => array("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"),
                                        "lineWidth" => 0,
                                        "labels" => array("enabled" => false)
                                    ),
                                "yAxis" => array(
                                    "lineWidth" => 0,
                                    "gridLineWidth" => 0,
                                    "minorGridLineWidth" => 0,
                                    "labels" => array("enabled" => false),
                                    "title" => ''
                                ),
                                "series" => $dataSeries
                            );
        if (array_key_exists('area-color', $options)) {
            $chartConfig['plotOptions']['area']['color'] = $options['area-color'];
        }
        if (array_key_exists('labels-background-color', $options)) {
            $chartConfig['plotOptions']['area']['dataLabels']['backgroundColor'] = $options['labels-background-color'];
        }
        return $chartConfig;
    }
    
    /**
     * Builds a chart containing only one horizontal bar and no other information (axis, grids, legends, titles, etc ...)
     * @param float $value current bar value
     * @param float $max max value
     * @param string $barColor bar color
     * @param boolean $reversed whether the y-axis should be reversed
     * @return the chart configuration
     */
    function cviz_build_single_bar_chart($value, $max, $barColor = "#9EB8D8", $reversed = false) {
        $chartConfig = array(
                            "chart" => array(
                                    "type" => "bar",
                                    "height" => 40,
                                    "margin" => array(0, 0, 0, 0),
                                    "spacing" => array(0, 0, 0, 0),
                                    "events" => array("load" => "")
                                ),
                            "credits" => array("enabled" => false),
                            "title" => array("text" => ""),
                            "legend" => array("enabled" => false),
                            "tooltip" => array("enabled" => false),
                            "plotOptions" => array(
                                    "bar" => array(
                                        "color" => $barColor,
                                        "groupPadding" => 0,
                                        "pointPadding" => 0,
                                        "dataLabels" => array(
                                                "enabled" => true,
                                                "inside" => true,
                                                "color" => "#000000"
                                            )
                                    )
                                ),
                            "xAxis" => array(
                                    "categories" => array(""),
                                    "lineWidth" => 0,
                                    "labels" => array("enabled" => false)
                                ),
                            "yAxis" => array(
                                    "min" => 0,
                                    "max" => $max,
                                    "title" => array("text" => null),
                                    "gridLineWidth" => 0,
                                    "minPadding" => 0,
                                    "maxPadding" => 0,
                                    "labels" => array("enabled" => false),
                                    "reversed" => $reversed
                                ),
                            "series" => array(array("data" => array($value)))
                        );
        return $chartConfig;
    }
    
    /**
     * Gets charts for Total BOC View
     * @param int $year reference year
     * @return array view charts
     */
    function dgph_customs_viz_get_total_boc_charts($year) {
        $charts = array();
        // Collections
        $months = array("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December");
        $cperfs = dgph_customs_viz_fetch_total_boc($year, TOTAL_BOC_COLLECTION_PERFORMANCE);
        $cperfSeriesData = array();
        foreach($months as $month) {
            if (array_key_exists($month, $cperfs)) {
                $cperfSeriesData[] = floatval(number_format($cperfs[$month]/1000000000, 2));  // in billion pesos
            }
            else {
                $cperfSeriesData[] = 0;
            }
        }
        $cperfSeries = array(array("name" => "Collections", "data" => $cperfSeriesData));
        $options = array('chart-type' => 'basic', 'y-title' => 'In Billion Pesos');
        $charts['collection_performance'] = cviz_build_column_chart($cperfSeries, $options);
        // Year-On-Year Growth
        $yoy = dgph_customs_viz_fetch_total_boc($year, TOTAL_BOC_YOY_GROWTH);
        $yoySeriesData = array();
        foreach($months as $month) {
            $yoySeriesData[] = array_key_exists($month, $yoy) ? floatval(number_format($yoy[$month], 3)) : 0;
        }
        $yoySeries = array(array("name" => "Growth", "data" => $yoySeriesData));
        $options = array('chart-type' => 'symmetric');
        $charts['yoy_growth'] = cviz_build_column_chart($yoySeries, $options);
        // CIF Value of Imports vs. Collections
        $cif = dgph_customs_viz_fetch_total_boc($year, TOTAL_BOC_CIF_VALUE_VS_COLLECTIONS);
        $cifSeriesData = array();
        $colsData = array();
        foreach($months as $idx => $month) {
            $cifValue = array_key_exists($month, $cif) ? floatval(number_format($cif[$month], 1)) : 0;
            $colValue = array_key_exists($month, $cperfs) ? floatval(number_format($cperfs[$month]/1000000000, 1)) : 0;
            $cifSeriesData[] = array($idx, 0, $cifValue);
            $colsData[] = array($idx, 0, $colValue);
        }
        $cvcSeries = array(
                            array(
                                    "name" => "CIF VALUE OF IMPORTS", 
                                    "data" => $cifSeriesData,
                                    "dataLabels" => array(
                                            "enabled" => true,
                                            "y" => 70,
                                            "color" => "#000000",
                                            "format" => "{point.z}",
                                            "style" => array("fontSize" => "10px"),
                                            "backgroundColor" => "#B6DBB3",
                                            "padding" => 4
                                        )
                                ),
                            array(
                                    "name" => "COLLECTIONS",
                                    "data" => $colsData,
                                    "dataLabels" => array(
                                            "enabled" => true,
                                            "y" => 5,
                                            "color" => "#FFFFFF",
                                            "format" => "{point.z}",
                                            "style" => array("fontSize" => "10px")
                                        )
                                )
                        );
        $charts['cif_value_vs_collections'] = cviz_build_bubble_chart($cvcSeries);
        // Volume of Imports
        $volImps = dgph_customs_viz_fetch_total_boc($year, TOTAL_BOC_VOLUME_OF_IMPORTS);
        foreach($months as $idx => $month) {
            $volImpsSeriesData[] = array_key_exists($month, $volImps) ? floatval(number_format($volImps[$month]/1000000, 1, '.', '')) : 0;
        }
        $volImpsSeries = array(array("name" => "Volume", "data" => $volImpsSeriesData));
        $options = array('area-color' => '#8198CC', 'labels-background-color' => '#425FA9');
        $charts['volume_of_import'] = cviz_build_area_chart($volImpsSeries, $options);
        // Import Entries
        $impEntries = dgph_customs_viz_fetch_total_boc($year, TOTAL_BOC_IMPORT_ENTRIES);
        foreach($months as $idx => $month) {
            $impEntriesSeriesData[] = array_key_exists($month, $impEntries) ? $impEntries[$month] : 0;
        }
        $impEntriesSeries = array(array("name" => "Entries", "data" => $impEntriesSeriesData));
        $options = array('area-color' => '#CF6C7E', 'labels-background-color' => '#BA1B2E');
        $charts['import_entries'] = cviz_build_area_chart($impEntriesSeries, $options);
        return $charts;
    }
    
    /**
     * Gets charts for Port View
     * @param int $year reference year
     * @param int $portId port identifier
     * @return array view charts
     */
    function dgph_customs_viz_get_port_view_charts($year, $portId) {
        $charts = array();
        // Collections
        $months = array("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December");
        $cperfs = dgph_customs_viz_fetch_port_view($year, $portId, PORT_VIEW_COLLECTION_PERFORMANCE);
        $cperfSeriesData = array();
        foreach($months as $month) {
            if (array_key_exists($month, $cperfs)) {
                $cperfSeriesData[] = $cperfs[$month]/1000000;  // in million pesos
            }
            else {
                $cperfSeriesData[] = 0;
            }
        }
        $cperfSeries = array(array("name" => "Collections", "data" => $cperfSeriesData));
        $options = array('chart-type' => 'basic', 'y-title' => 'In Million Pesos', 'data-labels-format' => '{y:.2f}');
        $charts['collection_performance'] = cviz_build_column_chart($cperfSeries, $options);
        // Year-On-Year Growth
        $yoy = dgph_customs_viz_fetch_port_view($year, $portId, PORT_VIEW_YOY_GROWTH);
        $yoySeriesData = array();
        foreach($months as $month) {
            $yoySeriesData[] = array_key_exists($month, $yoy) ? floatval(number_format($yoy[$month], 3)) : 0;
        }
        $yoySeries = array(array("name" => "Growth", "data" => $yoySeriesData));
        $options = array('chart-type' => 'symmetric');
        $charts['yoy_growth'] = cviz_build_column_chart($yoySeries, $options);
        // CIF Value of Imports vs. Collections
        $cif = dgph_customs_viz_fetch_port_view($year, $portId, PORT_VIEW_CIF_VALUE_VS_COLLECTIONS);
        $cifSeriesData = array();
        $colsData = array();
        foreach($months as $idx => $month) {
            $cifValue = array_key_exists($month, $cif) ? floatval(number_format($cif[$month], 1)) : 0;
            $colValue = array_key_exists($month, $cperfs) ? floatval(number_format($cperfs[$month]/1000000000, 1)) : 0;
            $cifSeriesData[] = array($idx, 0, $cifValue);
            $colsData[] = array($idx, 0, $colValue);
        }
        $cvcSeries = array(
                            array(
                                    "name" => "CIF VALUE OF IMPORTS", 
                                    "data" => $cifSeriesData,
                                    "dataLabels" => array(
                                            "enabled" => true,
                                            "y" => 70,
                                            "color" => "#000000",
                                            "format" => "{point.z}",
                                            "style" => array("fontSize" => "10px"),
                                            "backgroundColor" => "#B6DBB3",
                                            "padding" => 4
                                        )
                                ),
                            array(
                                    "name" => "COLLECTIONS",
                                    "data" => $colsData,
                                    "dataLabels" => array(
                                            "enabled" => true,
                                            "y" => 5,
                                            "color" => "#FFFFFF",
                                            "format" => "{point.z}",
                                            "style" => array("fontSize" => "10px")
                                        )
                                )
                        );
        $charts['cif_value_vs_collections'] = cviz_build_bubble_chart($cvcSeries);
        // Volume of Imports
        $volImps = dgph_customs_viz_fetch_port_view($year, $portId, PORT_VIEW_VOLUME_OF_IMPORTS);
        foreach($months as $idx => $month) {
            $volImpsSeriesData[] = array_key_exists($month, $volImps) ? floatval(number_format($volImps[$month]/1000000, 1, '.', '')) : 0;
        }
        $volImpsSeries = array(array("name" => "Volume", "data" => $volImpsSeriesData));
        $options = array('area-color' => '#8198CC', 'labels-background-color' => '#425FA9');
        $charts['volume_of_import'] = cviz_build_area_chart($volImpsSeries, $options);
        // Import Entries
        $impEntries = dgph_customs_viz_fetch_port_view($year, $portId, PORT_VIEW_IMPORT_ENTRIES);
        foreach($months as $idx => $month) {
            $impEntriesSeriesData[] = array_key_exists($month, $impEntries) ? $impEntries[$month] : 0;
        }
        $impEntriesSeries = array(array("name" => "Entries", "data" => $impEntriesSeriesData));
        $options = array('area-color' => '#CF6C7E', 'labels-background-color' => '#BA1B2E');
        $charts['import_entries'] = cviz_build_area_chart($impEntriesSeries, $options);
        return $charts;
    }
    
    /**
     * Gets charts for Commodity View
     * @param int $year reference year
     * @param int $commodityId commodity identifier
     * @return array view charts
     */
    function dgph_customs_viz_get_commodity_view_charts($year, $commodityId) {
        $charts = array();
        // Commodity Overall
        $months = array("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December");
        $perfs = dgph_customs_viz_fetch_commodity_view_overall($year, $commodityId);
        $cifSeriesData = array();
        $volumeSeriesData = array();
        $entriesSeriesData = array();
        $collsSeriesData = array();
        foreach($months as $idx => $month) {
            if (array_key_exists($month, $perfs)) {
                $cifValue = floatval(number_format($perfs[$month]['cif_value']/1000000000, 2));
                $volumeSeriesData[] = floatval(number_format($perfs[$month]['volume']/1000000, 1, '.', ''));
                $entriesSeriesData[] = $perfs[$month]['entries'];
                $colValue = floatval(number_format($perfs[$month]['customs_duties']/1000000000, 2));
            }
            else {
                $cifValue = 0;
                $volumeSeriesData[] = 0;
                $entriesSeriesData[] = 0;
                $colValue = 0;
            }
            $cifSeriesData[] = array($idx, 0, $cifValue);
            $collsSeriesData[] = array($idx, 0, $colValue);
        }
        // CIF Value of Imports vs. Collections
        $cvcSeries = array(
                            array(
                                    "name" => "CIF VALUE OF IMPORTS", 
                                    "data" => $cifSeriesData,
                                    "dataLabels" => array(
                                            "enabled" => true,
                                            "y" => 70,
                                            "color" => "#000000",
                                            "format" => "{point.z}",
                                            "style" => array("fontSize" => "10px"),
                                            "backgroundColor" => "#B6DBB3",
                                            "padding" => 4
                                        )
                                ),
                            array(
                                    "name" => "COLLECTIONS",
                                    "data" => $collsSeriesData,
                                    "dataLabels" => array(
                                            "enabled" => true,
                                            "y" => 5,
                                            "color" => "#FFFFFF",
                                            "format" => "{point.z}",
                                            "style" => array("fontSize" => "10px")
                                        )
                                )
                        );
        $charts['cif_value_vs_collections'] = cviz_build_bubble_chart($cvcSeries);
        // Volume of Imports
        $volumeSeries = array(array("name" => "Volume", "data" => $volumeSeriesData));
        $options = array('area-color' => '#8198CC', 'labels-background-color' => '#425FA9');
        $charts['volume_of_import'] = cviz_build_area_chart($volumeSeries, $options);
        // Import Entries
        $entriesSeries = array(array("name" => "Entries", "data" => $entriesSeriesData));
        $options = array('area-color' => '#CF6C7E', 'labels-background-color' => '#BA1B2E');
        $charts['import_entries'] = cviz_build_area_chart($entriesSeries, $options);
        // Commodities by Port
        $charts['by_port'] = array();
        $portPerfs = dgph_customs_viz_fetch_commodity_view_by_port($year, $commodityId);
        // calculates max values for charts
        $maxDuties = 0;
        $maxCif = 0;
        foreach($portPerfs as $portPerf) {
            if ($portPerf['customs_duties']>$maxDuties) {
                $maxDuties = $portPerf['customs_duties'];
            }
            if ($portPerf['cif_value']>$maxCif) {
                $maxCif = $portPerf['cif_value'];
            }
        }
        // build charts
        foreach($portPerfs as $portPerf) {
            $duties = $portPerf['customs_duties'];
            $cif = $portPerf['cif_value'];
            $charts['by_port'][] = array(
                        'port_name' => $portPerf['port_name'],
                        'customs_duties' => cviz_build_single_bar_chart($duties, $maxDuties, '#8DD39F', true),
                        'cif_value' => cviz_build_single_bar_chart($cif, $maxCif)
                    );
        }
        // Top Importers
        $charts['top_importers'] = array();
        $impPerfs = dgph_customs_viz_fetch_commodity_view_top_importers($year, $commodityId);
        // calculates max values for charts
        $maxCif = 0;
        $maxDuties = 0;
        $maxVolume = 0;
        foreach($impPerfs as $impPerf) {
            if ($impPerf['cif_value']>$maxCif) {
                $maxCif = $impPerf['cif_value'];
            }
            if ($impPerf['customs_duties']>$maxDuties) {
                $maxDuties = $impPerf['customs_duties'];
            }
            if ($impPerf['volume']>$maxVolume) {
                $maxVolume = $impPerf['volume'];
            }
        }
        // build charts
        foreach($impPerfs as $rank => $impPerf) {
            $cif = $impPerf['cif_value'];
            $duties = $impPerf['customs_duties'];
            $volume = $impPerf['volume'];
            $charts['top_importers'][] = array(
                        'rank' => $rank,
                        'importer' => $impPerf['importer'],
                        'cif_value' => cviz_build_single_bar_chart($cif, $maxCif, '#8DD39F'),
                        'customs_duties' => cviz_build_single_bar_chart($duties, $maxDuties),
                        'volume' => cviz_build_single_bar_chart($volume, $maxVolume, '#F38038')           
                    );
        }
        return $charts;
    }
    
    /**
     * Gets charts for Brokers and Importers View
     * @param int $year reference year
     * @param int $commodityId commodity identifier
     * @return array view charts
     */
    function dgph_customs_viz_get_brokers_importers_view_charts($year) {
        $charts = array('top_brokers' => array(), 'top_importers' => array());
        // Top Brokers
        $brkPerfs = dgph_customs_viz_fetch_brokers_importers_view($year, BROKERS_IMPORTERS_VIEW_BROKERS);
        // calculates max values for charts
        $maxCif = 0;
        $maxDuties = 0;
        $maxVolume = 0;
        foreach($brkPerfs as $brkPerf) {
            if ($brkPerf['cif_value']>$maxCif) {
                $maxCif = $brkPerf['cif_value'];
            }
            if ($brkPerf['customs_duties']>$maxDuties) {
                $maxDuties = $brkPerf['customs_duties'];
            }
            if ($brkPerf['volume']>$maxVolume) {
                $maxVolume = $brkPerf['volume'];
            }
        }
        // build charts
        foreach($brkPerfs as $rank => $brkPerf) {
            $cif = $brkPerf['cif_value'];
            $duties = $brkPerf['customs_duties'];
            $volume = $brkPerf['volume'];
            $charts['top_brokers'][] = array(
                        'rank' => $rank,
                        'name' => $brkPerf['name'],
                        'cif_value' => cviz_build_single_bar_chart($cif, $maxCif, '#8DD39F'),
                        'customs_duties' => cviz_build_single_bar_chart($duties, $maxDuties),
                        'volume' => cviz_build_single_bar_chart($volume, $maxVolume, '#F38038')           
                    );
        }
        // Top Importers
        $impPerfs = dgph_customs_viz_fetch_brokers_importers_view($year, BROKERS_IMPORTERS_VIEW_IMPORTERS);
        // calculates max values for charts
        $maxCif = 0;
        $maxDuties = 0;
        $maxVolume = 0;
        foreach($impPerfs as $impPerf) {
            if ($impPerf['cif_value']>$maxCif) {
                $maxCif = $impPerf['cif_value'];
            }
            if ($impPerf['customs_duties']>$maxDuties) {
                $maxDuties = $impPerf['customs_duties'];
            }
            if ($impPerf['volume']>$maxVolume) {
                $maxVolume = $impPerf['volume'];
            }
        }
        // build charts
        foreach($impPerfs as $rank => $impPerf) {
            $cif = $impPerf['cif_value'];
            $duties = $impPerf['customs_duties'];
            $volume = $impPerf['volume'];
            $charts['top_importers'][] = array(
                        'rank' => $rank,
                        'name' => $impPerf['name'],
                        'cif_value' => cviz_build_single_bar_chart($cif, $maxCif, '#8DD39F'),
                        'customs_duties' => cviz_build_single_bar_chart($duties, $maxDuties),
                        'volume' => cviz_build_single_bar_chart($volume, $maxVolume, '#F38038')           
                    );
        }
        return $charts;
    }
    
    /**
     * Gets an YOY chart for a port
     * @param int $nid port node identifier
     * @param int $year reference year
     * @return the chart code
     */
    function cviz_get_port_yoy_chart($nid, $year) {
        // Build YOY chart
        $yoy = dgph_customs_viz_fetch_port_view($year, $nid, PORT_VIEW_YOY_GROWTH);
        $yoySeriesData = array();
        $months = array("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December");
        foreach($months as $month) {
            $yoySeriesData[] = array_key_exists($month, $yoy) ? floatval(number_format($yoy[$month], 2)) : 0;
        }
        $yoySeries = array(array("name" => "Growth", "data" => $yoySeriesData));
        $options = array('chart-type' => 'symmetric');
        $yoyChart = cviz_build_column_chart($yoySeries, $options);
        $code = "
                    <html>
                    <head>
                        <script src='/sites/all/modules/jquery_update/replace/jquery/1.8/jquery.js?v=1.8.2' type='text/javascript'></script>
                        <script src='/sites/all/libraries/highcharts/js/highcharts.js' type='text/javascript'></script>
                        <script type='text/javascript'>
                            function cviz_format_percent() {
                                var perc = this.point.y * 100.0;
                                return perc.toFixed(0)+' %';
                            }
                            function cviz_format_yoy_tooltip() {
                                var name = this.point.category,
                                    perc = this.point.y * 100.0;
                                return name+': <b>'+perc.toFixed(1)+' %</b>';
                            }
                            jQuery(document).ready(function() {
                                    var config = jQuery('#popup-chart-config').text();
                                    if (config!=null) {
                                        config = config.trim();
                                        if (config.length>0) {
                                            var chartConfig = JSON.parse(config.trim());
                                            chartConfig.tooltip = { enabled: true };
                                            chartConfig.xAxis.lineWidth = 0;
                                            chartConfig.plotOptions.column.dataLabels.formatter = cviz_format_percent;
                                            chartConfig.tooltip.formatter = cviz_format_yoy_tooltip;
                                            jQuery('#popup-chart-container').highcharts(chartConfig);
                                        }
                                    }
                                });
                        </script>
                    </head>
                    <body>
                        <div id='popup-chart-container' style='width: 400; height: 190'><textarea id='popup-chart-config' class='chart-configuration'>".json_encode($yoyChart)."</textarea></div>
                    </body>
                    </html>";
        echo $code;
    }
?>