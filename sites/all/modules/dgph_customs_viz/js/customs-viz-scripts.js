var gLastFeature = null;

/**
 * Sends the current page to the printer
 */
function dashboard_print() {
    window.print();
}

function cviz_format_percent() {
    var perc = this.point.y * 100.0;
    return perc.toFixed(0)+' %';
}

function cviz_format_symmetric_tooltip() {
    var name = this.point.category,
        perc = this.point.y * 100.0;
    return name+": <b>"+perc.toFixed(1)+" %</b>";
}

function commaSeparateNumber(val){
    while (/(\d+)(\d{3})/.test(val.toString())){
        val = val.toString().replace(/(\d+)(\d{3})/, '$1'+','+'$2');
    }
    return val;
}

function cviz_format_number() {
    var num = this.point.y;
    return commaSeparateNumber(num.toFixed(0));
}

function cviz_format_basic_tooltip() {
    var name = this.point.category,
        num = this.point.y;
    return name+": <b>"+commaSeparateNumber(num.toFixed(2))+"</b>";
}

/**
 * Draws the Custom Viz charts configured by the current page
 */
function cviz_draw_charts() {
    jQuery(".chart-container textarea.chart-configuration").each(function() {
        var config = jQuery(this).text();
        if (config!=null) {
            config = config.trim();
            if (config.length>0) {
                var chartConfig = JSON.parse(config.trim());
                if (chartConfig.cvizOptions) {
                    var chartType = chartConfig.cvizOptions.chartType;
                    if (chartType=='basic') {
                        chartConfig.tooltip.formatter = cviz_format_basic_tooltip;
                    }
                    else if (chartType=='symmetric') {
                        chartConfig.plotOptions.column.dataLabels.formatter = cviz_format_percent;
                        chartConfig.tooltip.formatter = cviz_format_symmetric_tooltip;
                    }
                }
                var chartType = chartConfig.chart.type;
                if (chartType=='area') {
                    chartConfig.plotOptions.area.dataLabels.formatter = cviz_format_number;
                }
                jQuery(this).parent().highcharts(chartConfig);
            }
        }
    });
    jQuery(".table-chart-configuration").each(function() {
        var config = jQuery(this).text();
        if (config!=null) {
            config = config.trim();
            if (config.length>0) {
                var chartConfig = JSON.parse(config.trim());
                jQuery(this).parent().highcharts(chartConfig);
            }
        }
    });
}

/**
 * Handler for sort icon click event
 */
function sort_icon_clicked() {
    var sorter = jQuery(this).attr("data-sorter");
    if (typeof(sorter)!='undefined') {
        var url = location.href;
        url = url.split("?")[0]+"?sort="+sorter;
        location.href = url;
    }
}

/**
 * Creates a popup for the Ports Map
 */
function cviz_ports_map_create_popup(ev) {
    console.log("create popup");
    var ol_map = jQuery('#openlayers-map').data('openlayers');
    if (ol_map!=null) {
        var map = ol_map.openlayers;
        var feature = ev;
        var nid = feature.data.nid,
            title = feature.data.title,
            year = jQuery('#customs-selected-year').text(),
            chartUrl = "http://"+location.hostname+"/infographics/cviz-get-port-yoy-chart/"+nid+"/"+year;
            markerContent = "<div class='marker-content'>"+
                                "<div class='title'>"+title+"</div>"+
                                "<iframe src='"+chartUrl+"' width='420' height='210' frameborder='0' seamless></iframe>"+
                                "<div class='popup-console'><a href='/infographics/customs-viz/2/"+year+"/"+nid+"'>View more</a></div>"+
                            "</div>";
        feature.popup = new OpenLayers.Popup.FramedCloud(
                        "port_popup",
                        feature.geometry.getBounds().getCenterLonLat(),
                        null,
                        markerContent,
                        null,
                        true,
                        cviz_ports_map_destroy_popup
                    );
        map.addPopup(feature.popup);
        gLastFeature = feature;
    }
}

/**
 * Destroy a popup for the Ports Map
 */
function cviz_ports_map_destroy_popup(ev) {
    var feature = gLastFeature;  
    if (feature.popup) {
        var ol_map = jQuery('#openlayers-map').data('openlayers');
        if (ol_map!=null) {
            var map = ol_map.openlayers;
            map.removePopup(feature.popup);
            feature.popup.destroy();
            delete feature.popup;
        }
    }
}

/**
 * Zoom handler
 */
function handleZoom(event) {
    var map = event.object;
    if (map.getZoom()<4) {
        var center = map.getCenter();
        map.setCenter(center, 4);
        OpenLayers.Event.stop(event);
        return false;
    }
    return true;
}

/**
 * Initializes the ports map
 */
function cviz_init_ports_map() {
    var ol_map = jQuery('#openlayers-map').data('openlayers');
    if (ol_map!=null) {
        var map = ol_map.openlayers;
        map.events.register('zoomend', map, handleZoom);
        var layers = map.layers;
        if (layers.length>0) {
            var portsLayer = layers[1];
            var highlightCtrl = new OpenLayers.Control.SelectFeature(portsLayer, {
                    hover: true,
                    highlightOnly: true,
                    renderIntent: "temporary",
                    overFeature: function() { jQuery("#openlayers-map").css("cursor", "pointer"); },
                    outFeature: function() { jQuery("#openlayers-map").css("cursor", "auto"); }
                });
            var selectCtrl = new OpenLayers.Control.SelectFeature(portsLayer, {
                    clickout: true,
                    onSelect: cviz_ports_map_create_popup,
                    onUnselect: cviz_ports_map_destroy_popup
                }
            );

            map.addControl(highlightCtrl);
            map.addControl(selectCtrl);

            highlightCtrl.activate();
            selectCtrl.activate();
        }
    }
}

jQuery(document).ready(function() {
    if (jQuery("#left-sidebar-accordion").length) {
        jQuery("#left-sidebar-accordion").accordion({ heightStyle: "content", autoHeight: false });
    }
    jQuery('.cviz-tip').tooltip({
                    position: {
                    my: "center bottom-10",
                    at: "center top",
                    collision: "flipfit",
                    using: function( position, feedback ) {
                        jQuery( this ).css( position );
                        jQuery( "<div>" )
                            .addClass( "arrow" )
                            .addClass( feedback.vertical )
                            .addClass( feedback.horizontal )
                            .appendTo( this );
                    }
                }
            });
    jQuery('.sort-icon').click(sort_icon_clicked);
    cviz_draw_charts();
    cviz_init_ports_map();
    jQuery('#customs-viz-accordion').accordion({
                                        header: "h4",
                                        collapsible: true,
                                        active: false,
                                        heightStyle: "content",
                                        autoHeight: true
                                    });
})