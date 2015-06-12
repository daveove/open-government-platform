<?php

/**
 * @file
 * * Customs Visualization Dashboard: template for Brokers and Importers View.
 * URL Parameters:
 *  2: command (default: VIEW_BROKERS_IMPORTERS)
 *  3: year (default: 2013)
 */

?>

<?php
    $cid = arg(2) ? intval(arg(2)) : VIEW_BROKERS_IMPORTERS;
    $year = arg(3) ? arg(3) : 2013;
    $modPath = drupal_get_path('module', 'dgph_customs_viz');
?>

<div class='row dashboard-header'><?php require('customs-header.inc')  ?></div>
<div class='row'>
    <div class='large-3 columns left-sidebar'>
        <div id='left-sidebar-accordion' class='customs-viz-accordion ui-accordion ui-widget ui-helper-reset'>
            <h3 class='left-ui-accordion-header'>View By</h3>
            <div>
                <ul class="commands">
                    <li><?php echo l("Customs Total", "infographics/customs-viz/1/$year", array('attributes' => array('class' => array(($cid==VIEW_TOTAL_BOC) ? 'active' : 'not-active')))) ?></li>
                    <li><?php echo l("Port", "infographics/customs-viz/2/$year", array('attributes' => array('class' => array(($cid==VIEW_PORT) ? 'active' : 'not-active')))) ?></li>
                    <li><?php echo l("Commodity", "infographics/customs-viz/3/$year/".COMMODITY_VIEW_MOTOR_VEHICLES, array('attributes' => array('class' => array(($cid==VIEW_COMMODITY) ? 'active' : 'not-active')))) ?></li>
                    <li><?php echo l("Brokers and Importers", "infographics/customs-viz/4/$year", array('attributes' => array('class' => array(($cid==VIEW_BROKERS_IMPORTERS) ? 'active' : 'not-active')))) ?></li>
                </ul>
            </div>
        </div>
    </div>
    <div class='large-9 columns works'>
        <h2>TOP IMPORTERS AND BROKERS BASED ON CIF VALUE</h2>
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
        <h3 class="sub-title">View data on the top importers and brokers that facilitate these importations for the year indicated, and compare the duties paid against CIF value and volume imported.</h3>
        <div class='clear'></div>
        <div id="customs-viz-accordion">
            <h4 class="section-header section-header-accordion">
                <img src='<?php echo "/$modPath/images/star-icon.png" ?>'>
                <div class="hs-description">Top Brokers</div>
            </h4>
            <div class="section-content section-content-first">
                <table class="customs-viz-table">
                <tr class='header'>
                    <th class="data-importers-rank first">Rank</th>
                    <th class="data-importers-importer">Broker</th>
                    <th class="data-importers-cif"><span>CIF Value (PHP)</span><a href='javascript:void(0)' title='Cost of Goods, Insurance and Freight' class='cviz-tip'><img src='/sites/all/themes/dgph/images/info.png'></a></th>
                    <th class="data-importers-volume"><span>Volume (Kg)</span><a href='javascript:void(0)' title='Gross weight of commodities imported' class='cviz-tip'><img src='/sites/all/themes/dgph/images/info.png'></a></th>
                    <th class="data-importers-customs-duties last"><span>Customs Duties (PHP)</span><a href='javascript:void(0)' title='Customs Duties Paid' class='cviz-tip'><img src='/sites/all/themes/dgph/images/info.png'></a></th>
                </tr>
                <?php
                    $brksCharts = isset($charts['top_brokers']) ? $charts['top_brokers'] : array();
                    if (!empty($brksCharts)) {
                        foreach($brksCharts as $idx => $bcharts) {
                            $rank = $bcharts['rank'];
                            $broker = $bcharts['name'];
                            $cifChart = $bcharts['cif_value'];
                            $volumeChart = $bcharts['volume'];
                            $dutiesChart = $bcharts['customs_duties'];
                ?>
                <tr class='blank-row'><td colspan='5'></td></tr>
                <tr class='data-row'>
                    <td class="data-importers-rank first"><?php echo $rank ?></td>
                    <td class="data-importers-importer"><?php echo $broker ?></td>
                    <td class="data-importers-cif"><div id="table-chart-top-importers-cif-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($cifChart) ?></div></td>
                    <td class="data-importers-volume"><div id="table-chart-top-importers-volume-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($volumeChart) ?></div></td>
                    <td class="data-importers-customs-duties last"><div id="table-chart-top-importers-duties-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($dutiesChart) ?></div></td>
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
            <h4 class="section-header section-header-accordion section-header-next">
                <img src='<?php echo "/$modPath/images/star-icon.png" ?>'>
                <div class="hs-description">Top Importers</div>
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
                            $importer = $icharts['name'];
                            $cifChart = $icharts['cif_value'];
                            $volumeChart = $icharts['volume'];
                            $dutiesChart = $icharts['customs_duties'];
                ?>
                <tr class='blank-row'><td colspan='5'></td></tr>
                <tr class='data-row'>
                    <td class="data-importers-rank first"><?php echo $rank ?></td>
                    <td class="data-importers-importer"><?php echo $importer ?></td>
                    <td class="data-importers-cif"><div id="table-chart-top-importers-cif-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($cifChart) ?></div></td>
                    <td class="data-importers-volume"><div id="table-chart-top-importers-volume-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($volumeChart) ?></div></td>
                    <td class="data-importers-customs-duties last"><div id="table-chart-top-importers-duties-<?php echo $idx ?>" class="table-chart-configuration"><?php echo json_encode($dutiesChart) ?></div></td>
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