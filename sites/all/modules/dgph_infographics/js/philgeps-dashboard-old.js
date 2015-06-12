/**
 * Clean the status of all the checkboxes in a group but one
 * @param group the group name
 * @param optId the identifier of the checkbox to leave unchanged
 */
function unselectOptions(group, optId) {
    jQuery("input[id^='"+group+"']").each(function() {
            var thisId = jQuery(this).attr('id');
            if (thisId!=optId) {
                jQuery(this).next('span.custom.checkbox').removeClass('checked');
            }
        });
}

/**
 * Free search for PhilGEPS dashboard
 * @param sname the name of the search field
 * @param baseUri base URI for search
 */
function lookupPhilgeps(sname, baseUri) {
    var svalue = jQuery('#philgeps_free_search').val();
    if (svalue!=null && svalue.length>3) {
        svalue = svalue.replace(' ', '+', 'g');
        var uri = baseUri+'/'+sname+'/'+svalue;
        location.href = uri;
    }
}

/**
 * Remove all overlays from a map
 * @param mapId the map identifier
 */
function philgeps_map_remove_overlays(mapId) {
    var ol_map = jQuery('#'+mapId).data('openlayers');
    if (ol_map!=null) {
        var map = ol_map.openlayers;
        var layers = map.getLayersByClass("OpenLayers.Layer.Vector");
        layers.forEach(function(layer) {
                map.removeLayer(layer);
            });
        map.setCenter(new OpenLayers.LonLat(13614373, 1266145), 5);
    }
}

/**
 * Add a PhilGEPS KML feedback layer to an map
 * @param mapId the map identifier
 * @param layerName the KML layer name
 * @param layerIndex the layer index
 * @return the added layer, or <code>null</code> if an error occurs
 */
var select;
function philgeps_map_add_kml(mapId, layerName, layerIndex) {
    var layer = null;
    if ((typeof(layerName)!='undefined') && layerName) {
        var ol_map = jQuery('#'+mapId).data('openlayers');
        if (ol_map!=null) {
            var map = ol_map.openlayers;
            var layerPath = "/sites/default/files/philgeps_documents/"+layerName;
            var sm = new OpenLayers.StyleMap({
                            "default": new OpenLayers.Style({
                                strokeColor: '#000000',
                                strokeOpacity: .3,
                                strokeWidth: 2,
                                fillColor: '#000000',
                                fillOpacity: 0,
                                cursor: "pointer"
                            })
                        })

            console.log(sm);
            layer = new OpenLayers.Layer.Vector(layerName, {
                        projection: map.displayProjection,
                        styleMap: sm,
                        strategies: [new OpenLayers.Strategy.Fixed()],
                        protocol: new OpenLayers.Protocol.HTTP({
                            url: layerPath,
                            format: new OpenLayers.Format.KML({
                                extractStyles: true, 
                                extractAttributes: true
                            })
                        })
                    });
            map.addLayers([layer]);
            select = new OpenLayers.Control.SelectFeature(layer);
            layer.events.on({
                "featureselected": onFeatureSelect,
                "featureunselected": onFeatureUnselect,
                "mouseover": onSelectHover,
                "mouseout": onMouseOut
            });
            map.addControl(select);
            select.activate();
            map.setLayerIndex(layer, layerIndex);
        }else{
            console.log("no map");
        }
    }
    return layer;
}

function onSelectHover(event){
    if(event.target.localName == "image"){
        jQuery("image").css("cursor", "pointer");
    }
}

function onMouseOut(event){
    document.body.style.cursor = "default";
}

function onFeatureSelect(event) {
    var feature = event.feature;
    var ol_map = jQuery('#openlayers-map').data('openlayers');
    var map = ol_map.openlayers;

    var content = feature.attributes.description;
    if (content.search("<script") != -1) {
        content = "Content contained Javascript! Escaped content below.<br>" + content.replace(/</g, "&lt;");
    }
    popup = new OpenLayers.Popup.FramedCloud("popup", 
                             feature.geometry.getBounds().getCenterLonLat(),
                             new OpenLayers.Size(100,100),
                             content,
                             null, true, onPopupClose);
    feature.popup = popup;
    map.addPopup(popup);
}

function onPopupClose(event) {
    select.unselectAll();
}

function onFeatureUnselect(event) {
    var feature = event.feature;
    var ol_map = jQuery('#openlayers-map').data('openlayers');
    var map = ol_map.openlayers;
    if(feature.popup) {
        map.removePopup(feature.popup);
        feature.popup.destroy();
        delete feature.popup;
    }
}

/**
 * Zooms the a map to the last layer's extent
 * @param mapId the map identifier
 */
function philgeps_map_zoom_to_layer(mapId) {
    var ol_map = jQuery('#'+mapId).data('openlayers');
    if (ol_map!=null) {
        var map = ol_map.openlayers;
        var layersCount = map.layers.length;
        if (layersCount>1) {
            var layer = map.layers[layersCount-1];
            layer.events.register('loadend', layer, function(){ map.zoomToExtent(layer.getDataExtent()) })
        }
    }
}

/**
 * Handler for change year event
 * @param year the selected year
 */
function philgeps_year_changed(year) {
    var exp = /^\d+$/;
    if(exp.test(year)) {
        var deptId = jQuery('#org_biglist').text();
        var uri = '/infographics/philgeps/all/'+year;
        location.href = uri;
    }
}

/**
 * Handler for change agency event
 * @param deptId the selected agency (department) identifier
 */
function philgeps_agency_changed(deptId) {
    var year = jQuery('#philgeps-selected-year').text();
    var uri = '/infographics/philgeps/'+deptId+'/'+year;
    location.href = uri;
}

/**
 * Free search handler
 * @param searchType the search type
 */
function philgeps_free_search(searchType) {
    var searchText = jQuery('#philgeps_free_search').val();
    if (searchText!="") {
        if (!searchType) {
           searchType = "free_search";
        }
        var deptId = jQuery('#org_biglist').val(),
            year = jQuery('#philgeps-selected-year').text(),
            uri = "/infographics/philgeps/"+deptId+"/"+year+"/all/all/all/all/all?"+searchType+"="+searchText;
        window.location = encodeURI(uri);
    }
}


function set_agency_title(){
    jQuery("#agency_title").text(get_current_agency_name());
}


window.current_agency_id = '1433';


function get_current_agency_id(){
    return window.current_agency_id;
}


function get_current_agency_name(){
    agency_id = get_current_agency_id();
    agency_name = jQuery("#org_biglist option[value='" + agency_id + "']").text();
    if(agency_name){
        return agency_name;
    }
    return "";
}

/**
 * Updates a procurement item notice
 * @param bidId the bid identifier
 * @param noticeType notice type
 */
function philgeps_update_notice(bidId, noticeType) {
    jQuery(".philgeps-ajax-loading").show();
    var notice = jQuery("#"+noticeType+"-notice-"+bidId).val();
    var params = new Object();
    params.bid_nid = bidId;
    params.bid_notice_type = noticeType;
    params.bid_notice = notice;
    jQuery.ajax({
        url: '/infographics/philgeps-update-notice-ajax',
        type: 'POST',
        data: params,
        success: function(res) {
            jQuery(".philgeps-ajax-loading").hide();
            var resObj = JSON.parse(res);
            if (!resObj.success) {
                console.log("failed to update notice for procurement item #"+bidId);
            }
        },
        error: function(jqXHR, textStatus, errorThrown) {
            jQuery(".philgeps-ajax-loading").hide();
            console.log("failed to update notice for procurement item #"+bidId+": "+errorThrown);
        }
    });
}

/**
 * Apply the currently selected filters to the PhilGEPS dashboard and reloads the page
 */
function philgeps_apply_filters() {
    var agencyId = jQuery('#org_biglist').val(),
        year = jQuery('#philgeps-selected-year').text(),
        bc = jQuery('input[name=philgeps_bc]:checked').val(),
        ab = jQuery('input[name=philgeps_ab]:checked').val(),
        pm = jQuery('input[name=philgeps_pm]:checked').val(),
        st = jQuery('input[name=philgeps_st]:checked').val(),
        mn = jQuery('input[name=philgeps_mn]:checked').val();
    var url = "/infographics/philgeps/"+agencyId+"/"+year+"/"+bc+"/"+ab+"/"+pm+"/"+st+"/"+mn;
    url = encodeURI(url.replace(/undefined/g, 'all'));
    location.href = url;
}

/**
 * Clear all currently applied filters from the PhilGEPS dashboard
 */
function philgeps_clear_filters() {
    var agencyId = jQuery('#philgeps-selected-agency-id').text(),
        year = jQuery('#philgeps-selected-year').text();
    var url = encodeURI("/infographics/philgeps/"+agencyId+"/"+year);
    location.href = url;
}

jQuery(document).ready(function() {
    jQuery('#apply-filters').on('click', function(){
            philgeps_apply_filters();
        });
    jQuery('#clear-filters').on('click', function(){
            philgeps_clear_filters();
        });    
    jQuery('#lookup-philgeps').on('click', function(){
            jQuery('#lookup-category').slideToggle('slow');
        });
    jQuery(".flipper-markup a").click(function(){
		jQuery(".flipper-markup a").removeClass("active");
		jQuery("form.comment-form div.field-name-field-add-a-photo").hide();
		jQuery("form.comment-form div.field-name-field-embed-video").hide();
                jQuery("form.comment-form div.field-name-field-add-a-kml-file").hide();
		var selected = jQuery(this).attr('class');
		if (selected=='embed-video') {
                    jQuery("form.comment-form div.field-name-field-embed-video").show();
		}
                else if (selected=='add-kml') {
                    jQuery("form.comment-form div.field-name-field-add-a-kml-file").show();
		}
                else {
                    jQuery("form.comment-form div.field-name-field-add-a-photo").show();
		}
		jQuery(this).addClass("active");
		
	});
    jQuery('#accordion-notices').bind('activate', function(event, ui) {
                if(select){
                    onPopupClose();    
                }
                
                var hdr = ui.newHeader;
                var hid = hdr.prop("id");
                if (typeof(hid)!='undefined') {
                    var parts = hid.match(/^view-map-(\d+)/);
                    if ((parts!=null) && (parts.length>1)) {
                        var nid = parts[1];
                        if (nid>0) {
                            philgeps_map_remove_overlays('openlayers-map');
                            var map = jQuery("#openlayers-container-openlayers-map").parent().contents();
                            var layerObj, layerName;
                            for(i=0; i<3; i++) {
                                layerObj = jQuery('#kml-layer-filename-'+nid+'-'+i);
                                if (typeof(layerObj)!='undefined') {
                                    layerName = layerObj.val();
                                    philgeps_map_add_kml('openlayers-map', layerName, 10+i);
                                }
                            }
                            philgeps_map_zoom_to_layer('openlayers-map');
                            var cnt = jQuery('#map-container-'+nid);
                            cnt.append(map);
                        }
                    }
                }
            });
     jQuery('.philgeps-year-ref').click(function(){
            philgeps_year_changed(jQuery(this).text()); 
        });
     jQuery('.philgeps-agency-ref').click(function(){ 
            philgeps_agency_changed(jQuery(this).attr('dept-id')); 
        });   
     jQuery('.view-procurement-bid').click(function() {
                var url = jQuery(this).prop('href');
                var dlg = jQuery('<div></div>')
                                .html('<iframe style="border: 0px; " src="'+url+'" width="100%" height="100%"></iframe>')
                                .dialog({
                                    autoOpen: false,
                                    modal: true,
                                    height: 625,
                                    width: 960,
                                    title: "View Procurement Bid"
                                });
                dlg.dialog('open');
                return false;
            });

     jQuery('#org_biglist').on('change', function(e) {
        // triggers when whole value changed
        philgeps_apply_filters();
      });


     jQuery("#org_biglist").val(get_current_agency_id());
    
     /*jQuery("#org_biglist").chosen();*/
     jQuery('#org_biglist').select2({
        data: window.org_biglist_data,
        initSelection: function (element, callback) {
            initialData = {
              id  : get_current_agency_id(),
              text: window.org_biglist_data[get_current_agency_id()]
            };
            callback(initialData);
        },
        query: function (q) {
            var pageSize, results;
            pageSize = 20; // or whatever pagesize
            results  = [];
            if (q.term && q.term !== "") {
                // HEADS UP; for the _.filter function i use underscore (actually lo-dash) here
                results = _.filter(this.data, function (e) {
                    return (e.text.toUpperCase().indexOf(q.term.toUpperCase()) >= 0);
                });
            } else if (q.term === "") {
                results = this.data;
            }
            q.callback({
                results: results.slice((q.page - 1) * pageSize, q.page * pageSize),
                more   : results.length >= q.page * pageSize
                });
            }
     });

     set_agency_title();


})