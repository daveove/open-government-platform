<div class='large-6 columns intro-text'>
    <h1 class='title'>Customs Data</h1>
    <p>The Customs dashboard, launched amid ongoing reforms, features information never previously published with the goal of increasing transparency of trade and revenue collection activity. The data in this dashboard is from the improved BOC Electronic to Mobile (E2M) System, which gives the public easier access.</p>
    <p>Please note that collections of each port, on each commodity, or through each broker/importer may vary due to a change in the underlying mix of imports that are levied varying duty rates depending on the type and country of origin</p>
</div>
<div class='large-6 columns'>
    <div class='year-con'>
        <div class='year'><a href='#' data-dropdown='#customs-select-year'><span><?php echo $year ?></span></a></div>
        <span id='customs-selected-year' style='display:none'><?php echo $year ?></span>
        <div id='customs-select-year' class='dropdown dropdown-tip dropdown-relative'>
            <ul class='dropdown-menu'>
<?php
    $thisYear = date('Y');
    for($y = $thisYear; $y>=2010; $y--) {
        echo "<li>".l($y, "infographics/customs-viz/$cid/$y", array('attributes' => array('class' => array('year-ref'))))."</li>";
    } 
?>
            </ul>
        </div>
    </div>
</div>