/*
 * Leaflet Generic JSON Layer 1.0.0
 * http://labs.easyblog.it/maps/leaflet-layerjson
 *
 * https://github.com/stefanocudini/leaflet-layerJSON
 * https://bitbucket.org/zakis_/leaflet-layerJSON
 *
 * Copyright 2013, Stefano Cudini - stefano.cudini@gmail.com
 * Licensed under the MIT license.
 */
(function() {

L.LayerJSON = L.FeatureGroup.extend({

	includes: L.Mixin.Events,
	//
	//Managed Events:
	//	Event			Data passed		Description
	//  dataloading		{url}			fired before ajax/jsonp reques(useful for show gif loader)
	//	dataloaded		{data}			fired on ajax/jsonp request success
	//
	options: {
		url: 'http://mmda.dev.conveyal.com/api/alerts',
		//url: 'http://prc.insomnation.com/traffic/data.json',
		jsonpParam: null,			//callback parameter name for jsonp request append to url
		callData: null,				//alternative function that return data (if use $.ajax() set async=false)
		propertyLoc: 'loc', 		//json property used as Latlng of marker
		//TODO supporting lat,lng fields like L.Control.Search
		propertyTitle: 'title', 	//json property used as title(popup, marker, icon)
		filter: null,				//function that filter marker by its data, run before onEachMarker
		dataToMarker: null,			//function that will be used for creating markers from json points, similar to pointToLayer of L.GeoJSON
		onEachMarker: null,			//function called on each marker created, similar to option onEachFeature of L.GeoJSON
		layerTarget: null,			//pre-existing layer to add markers, is a LayerGroup or L.MarkerClusterGroup http://goo.gl/tvmu0
		buildPopup: true,			//function popup builder
		optsPopup: null,			//popup options
		buildIcon: null,			//function icon builder
		minShift: 8000,				//min shift for update data(in meters)
		updateOutBounds: true,		//request new data only if current bounds higher than last bounds
		precision: 6,				//number of digit send to server for lat,lng precision
		attribution: ''				//attribution text
	},
    
	initialize: function(options) {			
		L.FeatureGroup.prototype.initialize.call(this, []);
		L.Util.setOptions(this, options);
		this._dataToMarker = this.options.dataToMarker || this._defaultDataToMarker;
		this._buildIcon = this.options.buildIcon || this._defaultBuildIcon;
		this._buildPopup = this.options.buildPopup || this._defaultBuildPopup; 
		this._filterMarker = this.options.filter || function(){ return true; };
		this._dataRequest = null;
		this._dataUrl = this.options.url;
		this._center = null;
		this._maxBounds = null;
		this._markers = {};	//used for caching _dataToMarker builds
		if(this.options.jsonpParam)
		{
			this._dataUrl += '&'+this.options.jsonpParam+'=';
			this._callData = this.getJsonp;
		}
		else
			this._callData = this.options.callData || this.getAjax;
	},

	onAdd: function(map) { //console.info('onAdd');
		
		L.FeatureGroup.prototype.onAdd.call(this, map);		//set this._map
		this._center = map.getCenter();
		this._maxBounds = map.getBounds();

		map.on('moveend', this._onMove, this);
			
		this.update();
	},
    
	onRemove: function(map) { //console.info('onRemove');
		
		map.off('moveend', this._onMove, this); //FIXME not work!
		
		L.FeatureGroup.prototype.onRemove.call(this, map);	

		for (var i in this._layers) {
			if (this._layers.hasOwnProperty(i)) {
				L.FeatureGroup.prototype.removeLayer.call(this, this._layers[i]);
			}
		}
	},

	getAttribution: function() {
		return this.options.attribution;
	},

	addLayer: function (layer) {
		if(this.options.layerTarget)
		{
			this.options.layerTarget.addLayer.call(this.options.layerTarget, layer);
			return this.fire('layeradd', {layer: layer});
		}
		else
			L.FeatureGroup.prototype.addLayer.call(this, layer);
		return this;
	},
	
	removeLayer: function (layer) {
		if(this.options.layerTarget)
		{
			this.options.layerTarget.removeLayer.call(this.options.layerTarget, layer);
			return this.fire('layerremove', {layer: layer});
		}
		else
			L.FeatureGroup.prototype.removeLayer.call(this, layer);
		return this;
	},
	
	clearLayers: function () {
		if(this.options.layerTarget)
			this.options.layerTarget.clearLayers.call(this.options.layerTarget);
		else
			L.FeatureGroup.prototype.clearLayers.call(this);
		return this;
	},

  _defaultBuildPopup: function(data, marker) {  //default popup builder
    var html = '';
    
    if(data.hasOwnProperty(this.options.propertyTitle))
    {
       html += '<img src="/sites/all/modules/dgph_infographics/include/traffic/icons/'+data['type']+'-large.png" style="float:right; margin-left:10px;">';
	  html += '<h3>'+ data[this.options.propertyTitle] +'</h3>';
      delete data[this.options.propertyTitle];
    }
    data[this.options.propertyLoc] = data[this.options.propertyLoc].join();
     html += '<label>Type:</label><div class="event-type">'+data['type']+'</div>';
	 if(data.hasOwnProperty('activeTo')) 
	 {
		html += '<label>Active From:</label><div class="event-active-range">'+data['activeFrom']+' - '+data['activeTo']+'</div>';
	 } else {
	 	html += '<label>Date:</label><div class="event-date">'+data['activeFrom']+'</div>';
	 }
	 html += '<label>Description:</label><div class="event-description">'+data['publicDescription']+'</div>';
	
	
	//for(var i in data)
     // html += '<b>'+i+':</b> '+data[i]+'<br>';
    
    return html;
  }, 
	
	_defaultBuildIcon: function(data, title) {
		/*return new L.Icon.Default();*/
		if (data['type']=='trafficlight') {
			var icon = 'trafficlight';	
		} else if (data['type']=='construction') {
			var icon = 'construction';
		} else if (data['type']=='event') {
			var icon = 'event';
		} else if (data['type']=='fire') {
			var icon = 'fire';
		} else if (data['type']=='flood') {
			var icon = 'flood';
		} else if (data['type']=='roadclosed') {
			var icon = 'roadclosed';
		} else {
			var icon = 'incident';
		}
		
		return new L.icon({
    iconUrl: '/sites/all/modules/dgph_infographics/include/traffic/icons/'+icon+'.png',
    iconSize:     [30, 30], // size of the icon
    iconAnchor:   [15, 15], // point of the icon which will correspond to marker's location
    popupAnchor:  [0, -16] // point from which the popup should open relative to the iconAnchor
});
		
		
	},
	
	_defaultDataToMarker: function(data, latlng) {	//make marker from data

		var title = data[ this.options.propertyTitle ],
			//TODO check propertyLoc and propertyTitle in addMarker
			markerOpts = L.Util.extend({icon: this._buildIcon(data,title) }, data),
			marker = new L.Marker(latlng, markerOpts );
		
		if(this.options.buildPopup)
			marker.bindPopup(this._defaultBuildPopup(data, marker), this.options.optsPopup );
		
		
		return marker;
	},
	
	addMarker: function(data) {
		//TODO empty this._markers sooner or later

		var latlng = data[this.options.propertyLoc],
			hash = latlng.join() + data[this.options.propertyTitle];

		if(!this._markers[hash])
			this._markers[hash] = this._dataToMarker(data, latlng);

		if(this.options.onEachMarker)//maybe useless
			this.options.onEachMarker(data, this._markers[hash]);
		
		if (data['type']=='trafficlight') {  /// Put into groups for layer control
			trafficlightgroup.addLayer(this._markers[hash]);	
		} else if (data['type']=='construction') {
			constructiongroup.addLayer(this._markers[hash]);
		} else if (data['type']=='event') {
			eventgroup.addLayer(this._markers[hash]);
		} else if (data['type']=='fire') {
			firegroup.addLayer(this._markers[hash]);
		} else if (data['type']=='flood') {
			floodgroup.addLayer(this._markers[hash]);
		} else if (data['type']=='roadclosed') {
			roadclosedgroup.addLayer(this._markers[hash]);
		} else {
			incidentgroup.addLayer(this._markers[hash]);
		}
			
		
		this.addLayer( this._markers[hash] );
	},

	_updateMarkersCached: function(bounds) {
		for(var i in this._markers)
			if( bounds.contains(this._markers[i].getLatLng()) )
				this.addLayer(this._markers[i]);
			else
				this.removeLayer(this._markers[i]);
	},
	
	_onMove: function(e) {

/*		var newCenter = this._map.getCenter(),
			newBounds = this._map.getBounds();

		if( this.options.minShift && this._center.distanceTo(newCenter) < this.options.minShift )
			return false;
		else
			this._center = newCenter;

		if( this.options.updateOutBounds && this._maxBounds.contains(newBounds) )//bounds not incremented
		{
			this._updateMarkersCached(newBounds);
			//TODO maybe execute this ever
			return false;
		}
		else
			this._maxBounds.extend(newBounds);
		
		this.update();
*/
	},
	
	update: function(fromDate) {	//populate target layer
	
	/*	var //clear = clear || false,
			
			bb = this._map.getBounds(),
			sw = bb.getSouthWest(),
			ne = bb.getNorthEast(),
			//TODO send map bounds decremented
			p = this.options.precision,
			url = L.Util.template(this._dataUrl, {
					minlat: sw.lat.toFixed(p), maxlat: ne.lat.toFixed(p), 
					minlon: sw.lng.toFixed(p), maxlon: ne.lng.toFixed(p)
				});
*/
	var layerstate = {		
    "incident": 0,
	"construction": 0,
	"trafficlight": 0,
	"roadclosed": 0,
	"event": 0,
	"fire": 0,
	"flood": 0};
	
	var map = this._map;
    if(map.hasLayer(incidentgroup)) layerstate['incident'] = 1;
	if(map.hasLayer(constructiongroup)) layerstate['construction'] = 1;
	if(map.hasLayer(trafficlightgroup)) layerstate['trafficlight'] = 1;
	if(map.hasLayer(roadclosedgroup)) layerstate['roadclosed'] = 1;
	if(map.hasLayer(eventgroup)) layerstate['event'] = 1;
	if(map.hasLayer(firegroup)) layerstate['fire'] = 1;
	if(map.hasLayer(floodgroup)) layerstate['flood'] = 1;

		var url = L.Util.template(this._dataUrl);
		
		if(this._dataRequest)
			this._dataRequest.abort();	//prevent parallel requests

		var that = this;
		that.fire('dataloading', {url: url});	
		this._dataRequest = this._callData(url, function(json) {//using always that inside function

			that._dataRequest = null;

			that.fire('dataloaded', {data: json});
			
			that.clearLayers();
			for(var k in json)
				//if(that._filterMarker(json[k]))
			//	if(fromDate && toDate) {
			//		if((Date.parse(json[k]['activeFrom']))<fromDate)
			//			that.addMarker.call(that, json[k]);
				 if (fromDate === undefined){
					 that.addMarker.call(that, json[k]);
					 
				} else {
					//if((Date.parse(json[k]['activeFrom']))>fromDate)
					if((Date.parse(json[k]['activeFrom']))>fromDate && layerstate[json[k]['type']]==1)					
						that.addMarker.call(that, json[k]);
				}
		});
	},



/////////////////ajax jsonp methods

	getAjax: function(url, cb) {	//default ajax request

		if (window.XMLHttpRequest === undefined) {
			window.XMLHttpRequest = function() {
				try {
					return new ActiveXObject("Microsoft.XMLHTTP.6.0");
				}
				catch  (e1) {
					try {
						return new ActiveXObject("Microsoft.XMLHTTP.3.0");
					}
					catch (e2) {
						throw new Error("XMLHttpRequest is not supported");
					}
				}
			};
		}
		var request = new XMLHttpRequest();
		request.open('GET', url);
		request.onreadystatechange = function() {
			var response = {};
		    if (request.readyState === 4 && request.status === 200) {
		    	try {
					if(window.JSON) {
				        response = JSON.parse(request.responseText);
					} else {
						response = eval("("+ request.responseText + ")");
					}
		    	} catch(err) {
		    		console.info(err);
		    		response = {};
		    	}
		        cb(response);
		    }
		};
		request.send();
		return request;   
	},
	
	getJsonp: function(url, cb) {  //extract searched records from remote jsonp service
		var body = document.getElementsByTagName('body')[0],
			script = L.DomUtil.create('script','layerjson-jsonp', body );
		
		L.LayerJSON.callJsonp = function(data) {	//jsonp callback
			//TODO data = filterJSON.apply(that,[data]);
			cb(data);
			body.removeChild(script);
		}
		script.type = 'text/javascript';
		script.src = url+'L.LayerJSON.callJsonp';
		return {abort: function() { script.parentNode.removeChild(script); } };
	}
});

}).call(this);
