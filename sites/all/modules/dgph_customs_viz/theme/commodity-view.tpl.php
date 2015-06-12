<?php

/**
 * @file
 * * Customs Visualization Dashboard: template for Commodity View.
 * URL Parameters:
 *  2: command (default: VIEW_COMMODITY)
 *  3: year (default: 2013)
 *  4: commodityId (default: COMMODITY_VIEW_MOTOR_VEHICLES)
 */

?>

<?php
    $cid = arg(2) ? intval(arg(2)) : VIEW_COMMODITY;
    $year = arg(3) ? arg(3) : 2013;
    $commodityId = arg(4) ? arg(4) : COMMODITY_VIEW_MOTOR_VEHICLES;
    $modPath = drupal_get_path('module', 'dgph_customs_viz');
    $sort = isset($_GET['sort']) ? $_GET['sort'] : 'duties';
?>

<div class='row dashboard-header'><?php require('customs-header.inc')  ?></div>
<div class='row'>
    <div class='large-3 columns left-sidebar'>
        <div id='left-sidebar-accordion' class='customs-viz-accordion ui-accordion ui-widget ui-helper-reset'>
            <h3 class='left-ui-accordion-header'>View By</h3>
            <div>
                <ul class="commands">
                    <li><?php echo l("Customs Total", "infographics/customs-viz/1/$year", array('attributes' => array('class' => array(($cid==1) ? 'active' : 'not-active')))) ?></li>
                    <li><?php echo l("Port", "infographics/customs-viz/2/$year", array('attributes' => array('class' => array(($cid==2) ? 'active' : 'not-active')))) ?></li>
                    <li>
                        <?php echo l("Commodity", "infographics/customs-viz/3/$year/".COMMODITY_VIEW_MOTOR_VEHICLES, array('attributes' => array('class' => array(($cid==3) ? 'active' : 'not-active')))) ?>
                        <ul class="commands-submenu">
                            <li><?php echo l("Motor Vehicles", "infographics/customs-viz/3/$year/".COMMODITY_VIEW_MOTOR_VEHICLES, array('attributes' => array('class' => array(($commodityId==COMMODITY_VIEW_MOTOR_VEHICLES) ? 'active' : 'not-active')))) ?></li>
                            <li><?php echo l("Iron And Steel", "infographics/customs-viz/3/$year/".COMMODITY_VIEW_IRON_AND_STEEL, array('attributes' => array('class' => array(($commodityId==COMMODITY_VIEW_IRON_AND_STEEL) ? 'active' : 'not-active')))) ?></li>
                            <li><?php echo l("Rice", "infographics/customs-viz/3/$year/".COMMODITY_VIEW_RICE, array('attributes' => array('class' => array(($commodityId==COMMODITY_VIEW_RICE) ? 'active' : 'not-active')))) ?></li>
                            <li><?php echo l("Tobacco", "infographics/customs-viz/3/$year/".COMMODITY_VIEW_TOBACCO, array('attributes' => array('class' => array(($commodityId==COMMODITY_VIEW_TOBACCO) ? 'active' : 'not-active')))) ?></li>
                            <li><?php echo l("Plastic Resins", "infographics/customs-viz/3/$year/".COMMODITY_VIEW_PLASTIC_RESINS, array('attributes' => array('class' => array(($commodityId==COMMODITY_VIEW_PLASTIC_RESINS) ? 'active' : 'not-active')))) ?></li>
                        </ul>
                    </li>
                    <li><?php echo l("Brokers and Importers", "infographics/customs-viz/4/$year", array('attributes' => array('class' => array(($cid==4) ? 'active' : 'not-active')))) ?></li>
                </ul>
            </div>
        </div>
    </div>
    <div class='large-9 columns works'>
        <h2>COMMODITY</h2>
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
        <?php
            $commodityName = dgph_customs_viz_commodity_name($commodityId);
        ?>
        <div id="customs-viz-accordion">
            <h4 class="section-header section-header-accordion">
                <img src='<?php echo "/$modPath/images/star-icon.png" ?>'>
                <div class="hs-description"><?php echo $commodityName ?></div>
            </h4>
            <div class="section-content-group">
                <div class="section-content section-content-first">
                    <h5 class="title"><span>CIF VALUE OF IMPORTS vs. COLLECTIONS</span><a><img src='<?php echo "/$modPath/images/info.png" ?>'></a></h5>
                    <div id="total-boc-cif-value-vs-collections" class="chart-container">
                        <textarea id="total-boc-cif-value-vs-collections-chart-config" class="chart-configuration"><?php if (isset($charts['cif_value_vs_collections'])) { echo json_encode($charts['cif_value_vs_collections']); } ?></textarea>
                    </div>
                </div>
                <div class="section-content">
                    <h5 class="title"><span>VOLUME OF IMPORTS (million kg)</span><a href='javascript:void(0)' title='Volume is the gross weight in kilograms of the imported commodity.' class='cviz-tip'><img src='<?php echo "/$modPath/images/info.png" ?>'></a></h5>
                    <div id="total-boc-volume-of-import" class="chart-container">
                        <textarea id="total-boc-volume-of-import-chart-config" class="chart-configuration"><?php if (isset($charts['volume_of_import'])) { echo json_encode($charts['volume_of_import']); } ?></textarea>
                    </div>
                </div>
                <div class="section-content">
                    <h5 class="title"><span>IMPORT ENTRIES (number)</span><a href='javascript:void(0)' title='Import Entries are the total number of processed import transactions, or batches of imports.' class='cviz-tip'><img src='<?php echo "/$modPath/images/info.png" ?>'></a></h5>
                    <div id="total-boc-import-entries" class="chart-container">
                        <textarea id="total-boc-import-entries-chart-config" class="chart-configuration"><?php if (isset($charts['import_entries'])) { echo json_encode($charts['import_entries']); } ?></textarea>
                    </div>
                </div>
            </div>
            <h4 class="section-header section-header-accordion section-header-next">
                <img src='<?php echo "/$modPath/images/star-icon.png" ?>'>
                <div class="hs-description"><?php echo $commodityName ?> by Port</div>
            </h4>
            <div class="section-content section-content-first">
                <table class="customs-viz-table">
                <tr class='header'>
                    <th class="first data-port">Port</th>
                    <th class="data-customs-duties"><span>Customs Duties Collected (PHP)</span><img id="sort-by-duties" class="sort-icon" data-sorter="duties" src='<?php echo "/$modPath/images/arrow-down-".(($sort=="duties") ? "yellow" : "grey")."-small.png" ?>'></th>
                    <th class="data-cif last"><span>CIF Value (PHP)</span><a href='javascript:void(0)' title='Cost of Goods, Insurance and Freight' class='cviz-tip'><img src='/sites/all/themes/dgph/images/info.png'></a><img id="sort-by-cif" class="sort-icon" data-sorter="cif" src='<?php echo "/$modPath/images/arrow-down-".(($sort=="cif") ? "yellow" : "grey")."-small.png" ?>'></th>
                </tr>
                <?php
                    $portsCharts = isset($charts['by_port']) ? $charts['by_port'] : array();
                    if (!empty($portsCharts)) {
                        foreach($portsCharts as $idx => $pcharts) {
                            $portName = $pcharts['port_name'];
                            $dutiesChart = $pcharts['customs_duties'];
                            $cifChart = $pcharts['cif_value'];
                ?>
                <tr class='blank-row'><td colspan='3'></td></tr>
                <tr class='data-row'>
                    <td class="data-port"><?php echo $portName ?></td>
                    <td><div id="table-chart-by-port-duties-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($dutiesChart) ?></div></td>
                    <td class="last"><div id="table-chart-by-port-cif-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($cifChart) ?></div></td>
                </tr>
                <?php
                        }
                    }
                    else {
                ?>
                <tr class='blank-row'><td colspan='3'></td></tr>
                <tr class='data-row'><td colspan="3">no data available</td></tr>
                <?php         
                    }
                ?>
                </table>
            </div>
            <h4 class="section-header section-header-accordion section-header-next">
                <img src='<?php echo "/$modPath/images/star-icon.png" ?>'>
                <div class="hs-description">Top <?php echo $commodityName ?> Importers</div>
            </h4>
            <div class="section-content section-content-first">
                <table class="customs-viz-table">
                <tr class='header'>
                    <th class="data-importers-rank first">Rank</th>
                    <th class="data-importers-importer">Importer</th>
                    <th class="data-importers-cif"><span>CIF Value (PHP)</span><a href='javascript:void(0)' title='Cost of Goods, Insurance and Freight' class='cviz-tip'><img src='/sites/all/themes/dgph/images/info.png'></a></th>
                    <th class="data-importers-volume"><span>Volume (Kg)</span><a href='javascript:void(0)' title='Gross weight of commodities imported' class='cviz-tip'><img src='/sites/all/themes/dgph/images/info.png'></a></th>
                    <th class="data-importers-customs-duties last"><span>Customs Duties (PHP)</span><a href='javascript:void(0)' title='Customs Duties Paid' class='cviz-tip'><img src='/sites/all/themes/dgph/images/info.png'></a></th>
                </tr>
                <?php
                    $impsCharts = isset($charts['top_importers']) ? $charts['top_importers'] : array();
                    if (!empty($impsCharts)) {
                        foreach($impsCharts as $idx => $icharts) {
                            $rank = $icharts['rank'];
                            $importer = $icharts['importer'];
                            $cifChart = $icharts['cif_value'];
                            $volumeChart = $icharts['volume'];
                            $dutiesChart = $icharts['customs_duties'];
                ?>
                <tr class='blank-row'><td colspan='5'></td></tr>
                <tr class='data-row'>
                    <td class="data-importers-rank"><?php echo $rank ?></td>
                    <td class="data-importers-importer"><?php echo $importer ?></td>
                    <td><div id="table-chart-top-importers-cif-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($cifChart) ?></div></td>
                    <td><div id="table-chart-top-importers-volume-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($volumeChart) ?></div></td>
                    <td class="last"><div id="table-chart-top-importers-duties-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($dutiesChart) ?></div></td>
                </tr>
                <?php
                        }
                    }
                    else {
                ?>
                <tr class='blank-row'><td colspan='5'></td></tr>
                <tr class='data-row'><td colspan="5">no data available</td></tr>
                <?php         
                    }
                ?>
                </table>
            </div>
        </div>
    </div>
</div>