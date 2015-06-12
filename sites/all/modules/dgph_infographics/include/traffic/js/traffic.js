/** Globals */

var TRAFFIC_BASE_PATH = '/sites/all/modules/dgph_infographics/include/traffic';

var floodgroup = new L.layerGroup();
var incidentgroup = new L.layerGroup();
var firegroup = new L.layerGroup();
var constructiongroup = new L.layerGroup();
var eventgroup = new L.layerGroup();
var roadclosedgroup = new L.layerGroup();
var trafficlightgroup = new L.layerGroup();
var jsonLayer = new L.LayerJSON({url: TRAFFIC_BASE_PATH+"/data/data.json"});

/**
 * Initializes the traffic map
 */
function initMap() {
    var map = new L.Map('map', {zoom: 13, center: new L.latLng([14.615478,121.015749]) });
    map.addLayer(new L.TileLayer('http://otile1.mqcdn.com/tiles/1.0.0/map/{z}/{x}/{y}.png',{
                        attribution:'<a href="http://www.mapquest.com/" target="_blank">MapQuest</a> <img src="http://developer.mapquest.com/content/osm/mq_logo.png">'}));
       
    map.addLayer(jsonLayer);
    map.addLayer(incidentgroup);
    map.addLayer(constructiongroup);
    map.addLayer(trafficlightgroup);
    map.addLayer(roadclosedgroup);
    map.addLayer(eventgroup);
    map.addLayer(firegroup);
    map.addLayer(floodgroup);

    map.addControl(new L.Control.Layers({},{'Traffic Incidents': incidentgroup,'Construction': constructiongroup,'Traffic Lights': trafficlightgroup,'Road Closures': roadclosedgroup,'Events': eventgroup,'Fires': firegroup,'Floods': floodgroup},{ collapsed:false}));	
		
    // Header		
    var headerInfo = L.control({position: 'topleft'});		
    headerInfo.onAdd = function (map) {
            var div = L.DomUtil.create('div', 'headerinfo');
            L.DomUtil.enableTextSelection(div);
            L.DomEvent.disableClickPropagation(div);
            var date = new Date();
            var todaydate = (date.getMonth() + 1) + '/' + date.getDate() + '/' +  date.getFullYear();

            div.innerHTML += '<span style="font-weight:bold; color:#5a82b4;font-size: 18px;">TRAFFIC ALERT SYSTEM</span>&nbsp;&nbsp; <select class="historycal-dropdown" onchange="javascript:jsonLayer.update(this.value)"><option value="">Show All</option><option value="1380653876000" >Last Week</option><option value="1380653876000">Last Month</option><option value="1378512000000">Last 3 Months</option><option value="1365292800000">Last 6 Months</option></select><br/><em>Data last updated: '+todaydate+'</em>';
            return div;
        };
    headerInfo.addTo(map);	
    // Buttons		
    var buttons = L.control({position: 'topleft'});		
    buttons.onAdd = function (map) {
            var div = L.DomUtil.create('div', 'buttons');
                    div.innerHTML +=
                    '<img src="'+TRAFFIC_BASE_PATH+'/icons/historicalbutton.png" alt="Historical Data"><br /><a href="http://mmda.dev.conveyal.com/api/alerts" target="_blank"><img src="'+TRAFFIC_BASE_PATH+'/icons/databutton.png" alt="Data Feed" style="border:none;"></a>';
            return div;
    };
    buttons.addTo(map);
}

initMap();