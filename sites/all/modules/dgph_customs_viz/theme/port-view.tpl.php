<?php

/**
 * @file
 * * Customs Visualization Dashboard: template for Port View.
 * URL Parameters:
 *  2: command (default: VIEW_PORT)
 *  3: year (default: 2013)
 *  4: port (default: 0, none)
 */

?>

<?php
    $cid = arg(2) ? intval(arg(2)) : VIEW_PORT;
    $year = arg(3) ? arg(3) : 2013;
    $port = arg(4) ? arg(4) : 0;
    $modPath = drupal_get_path('module', 'dgph_customs_viz');
    $map = openlayers_map_load('customs_viz_map');
    $mapCode = openlayers_render_map($map->data, $map->name);
?>

<div class='row dashboard-header'><?php require('customs-header.inc')  ?></div>
<div class='row'>
    <div class='large-3 columns left-sidebar'>
        <div id='left-sidebar-accordion' class='customs-viz-accordion ui-accordion ui-widget ui-helper-reset'>
            <h3 class='left-ui-accordion-header'>View By</h3>
            <div>
                <ul class="commands">
                    <li><?php echo l("Customs Total", "infographics/customs-viz/1/$year", array('attributes' => array('class' => array(($cid==1) ? 'active' : 'not-active')))) ?></li>
                    <li>
                        <?php echo l("Port", "infographics/customs-viz/2/$year", array('attributes' => array('class' => array(($cid==2) ? 'active' : 'not-active')))) ?>
                        <ul class="commands-submenu">
                            <?php
                                $ports = dgph_customs_viz_load_ports();
                                foreach($ports as $pid => $ptitle) {
                            ?>
                                    <li><?php echo l($ptitle, "infographics/customs-viz/2/$year/$pid", array('attributes' => array('class' => array(($port==$pid) ? 'active' : 'not-active')))) ?></li>
                            <?php
                                }
                            ?>
                        </ul>
                    </li>
                    <!-- <li><?php echo l("Commodity", "infographics/customs-viz/3/$year/".COMMODITY_VIEW_MOTOR_VEHICLES, array('attributes' => array('class' => array(($cid==3) ? 'active' : 'not-active')))) ?></li>
                    <li><?php echo l("Brokers and Importers", "infographics/customs-viz/4/$year", array('attributes' => array('class' => array(($cid==4) ? 'active' : 'not-active')))) ?></li> -->
                </ul>
            </div>
        </div>
    </div>
    <div class='large-9 columns works'>
        <h2>CUSTOMS DATA BY PORT</h2>
        <ul class='social-icon'>
            <li><a href="javascript:dashboard_print()"><img alt='' src='/sites/all/themes/dgph/images/icon-11.png'></a></li>
            <?php
                $dashbUploadUri = infographics_get_dashboard_datafile(DGPH_CUSTOMS_VIZ_DASHBOARD_ID, $year);
                if (!empty($dashbUploadUri)) {
            ?>
            <li><a href='<?php echo $dashbUploadUri ?>' title='Download dashboard data'><img alt='' src='/sites/all/themes/dgph/images/icon-19.png'></a></li>
            <?php
                }
            ?>
            <li><img alt='' src='/sites/all/themes/dgph/images/icon-20.png'></li>
        </ul>
        <div class='clear'></div>
        <h4 class="section-header">
            <img src='<?php echo "/$modPath/images/star-icon.png" ?>'>
            <div class="hs-description">Year-On-Year Collection Performance</div>
        </h4>
        <div class="section-content section-content-first">
            <div id="ports-map" class="map-container">
                <p class='intro'>Click on each port marker to view year-on-year growth in collections. Click again to view more detailed customs data about that port.</p>
                <?php echo $mapCode ?>
            </div>
        </div>
        <?php
            if ($port>0) {
                $portName = $ports[$port];
        ?>
        <div class='clear'></div>
        <h4 class="section-header">
            <img src='<?php echo "/$modPath/images/star-icon.png" ?>'>
            <div class="hs-description"><?php echo $portName ?></div>
        </h4>
        <div class="section-content section-content-first">
            <h5 class="title"><span>COLLECTIONS</span><a><img src='<?php echo "/$modPath/images/info.png" ?>'></a></h5>
            <div id="port-view-collection-performance" class="chart-container">
                <textarea id="port-view-collection-performance-chart-config" class="chart-configuration"><?php if (isset($charts['collection_performance'])) { echo json_encode($charts['collection_performance']); } ?></textarea>
            </div>
        </div>
        <div class="section-content">
            <h5 class="title"><span>YEAR-ON-YEAR GROWTH</span><a><img src='<?php echo "/$modPath/images/info.png" ?>'></a></h5>
            <div id="total-boc-yoy-growth" class="chart-container">
                <textarea id="total-boc-yoy-growth-chart-config" class="chart-configuration"><?php if (isset($charts['yoy_growth'])) { echo json_encode($charts['yoy_growth']); } ?></textarea>
            </div>
        </div>
        <div class="section-content">
            <h5 class="title"><span>CIF VALUE OF IMPORTS vs. COLLECTIONS</span><a><img src='<?php echo "/$modPath/images/info.png" ?>'></a></h5>
            <div id="total-boc-cif-value-vs-collections" class="chart-container">
                <textarea id="total-boc-cif-value-vs-collections-chart-config" class="chart-configuration"><?php if (isset($charts['cif_value_vs_collections'])) { echo json_encode($charts['cif_value_vs_collections']); } ?></textarea>
            </div>
        </div>
        <div class="section-content">
            <h5 class="title"><span>VOLUME OF IMPORTS (million kg)</span><a><img src='<?php echo "/$modPath/images/info.png" ?>'></a></h5>
            <div id="total-boc-volume-of-import" class="chart-container">
                <textarea id="total-boc-volume-of-import-chart-config" class="chart-configuration"><?php if (isset($charts['volume_of_import'])) { echo json_encode($charts['volume_of_import']); } ?></textarea>
            </div>
        </div>
        <div class="section-content">
            <h5 class="title"><span>IMPORT ENTRIES (number)</span><a><img src='<?php echo "/$modPath/images/info.png" ?>'></a></h5>
            <div id="total-boc-import-entries" class="chart-container">
                <textarea id="total-boc-import-entries-chart-config" class="chart-configuration"><?php if (isset($charts['import_entries'])) { echo json_encode($charts['import_entries']); } ?></textarea>
            </div>
        </div>
    </div>
    <?php } ?>
</div>