(function ($) {    $(document).ready(function() {        $( "#accordion" ).accordion({ heightStyle: "content", autoHeight: false });        $( "#accordion2" ).accordion({ heightStyle: "content", autoHeight: false });        $( "#accordion3" ).accordion({ heightStyle: "content", autoHeight: false });        $( ".accordion4" ).accordion({ header:"h3", heightStyle: "content", autoHeight: true, collapsible: true, active: false });        $(document).on('click', 'form.custom span.custom.checkbox', function (event) {            if (!$(this).not('philgeps-checkbox')) {                var obj = $(this).prev("input[type='checkbox']");                if (obj.is(':enabled')) {                    $(this).toggleClass('checked');                    obj.attr("checked", !obj.attr("checked"));                    var url = null;                    if ($(this).hasClass('checked') && typeof(obj.attr('target-uri'))!='undefined') {                        url = obj.attr('target-uri');                    }                    else if (!$(this).hasClass('checked') && typeof(obj.attr('target-cleanup-uri'))!='undefined') {                        url = obj.attr('target-cleanup-uri');                    }                    else if (obj.hasClass('search-auto')) {                        var filters = buildContextualFilters();                        var urlParams = '';                        $.each(filters, function(index, value) {                            urlParams += '/'+value;                        });                        url = '/data-requests/list'+urlParams;                    }                    if (url!=null) {                        window.location = url;                    }                }            }        });        $('.clander-btn-auto').click(function(event) { freeSearch($(this)) });        $('.has-tip').tooltip({                    position: {                    my: "center bottom-20",                    at: "center top",                    collision: "flipfit",                    using: function( position, feedback ) {                        $( this ).css( position );                        $( "<div>" )                        .addClass( "arrow" )                        .addClass( feedback.vertical )                        .addClass( feedback.horizontal )                        .appendTo( this );                    }                }            });    });})(jQuery);function setGridView(sg, typeName){    if(sg == 1){        if (jQuery("."+typeName).removeClass("list")){            jQuery(".gridicon").css("opacity", "1");            jQuery(".listicon").css("opacity", "0.1");            jQuery("."+typeName).addClass("grid");        }    }    else{        if(jQuery("."+typeName).removeClass("grid")){            jQuery(".gridicon").css("opacity", "0.1");            jQuery(".listicon").css("opacity", "1");            jQuery("."+typeName).addClass("list");        }    } }function buildContextualFilters() {    var filters = [];    var drOts = [];    jQuery("input[type='checkbox'][name='dr_ot']").each(function() {        if (jQuery(this).attr('checked')=='checked') {            drOts.push(jQuery(this).val());        }     });    if (drOts.length>0) {         filters.push(drOts.join('+'));    }    else {        filters.push('all');    }    var drSus = [];    jQuery("input[type='checkbox'][name='dr_su']").each(function() {        if (jQuery(this).attr('checked')=='checked') {            drSus.push(jQuery(this).val());        }     });    if (drSus.length>0) {         filters.push(drSus.join('+'));    }    else {        filters.push('all');    }    return filters;}function freeSearch(obj) {    var text = obj.next("input[type='text']").val();    text = text.replace(' ', '+');    var url = '/data-requests/list/all/all/'+escape(text);    window.location = url;}function fbPostToFeed(postUrl, postImage, postName, postDescr) {    // calling the API ...    var obj = {            method: 'feed',            link: postUrl,            picture: postImage,            name: postName,            description: postDescr        };    function callback(resp) {        if (resp!=null) {            document.getElementById('msg').innerHTML = "Post ID: " + resp['post_id'];        }    }    FB.ui(obj, callback);}function homeSearchClicked() {    var txt = jQuery('#home-search-text').val();    if (txt!='') {        txt.replace(' ', '+');        location.href='/catalogue/dataset?q='+txt    }}function homeSearchKeydown(ev) {    if (ev.keyCode == 13) {        homeSearchClicked();    }}function forumSearchClicked() {    var txt = jQuery('#forum-search-text').val();    if (txt!='') {        txt.replace(' ', '+');        location.href='/forum/latest?f='+txt    }}function forumSearchKeydown(ev) {    if (ev.keyCode == 13) {        forumSearchClicked();    }}(function ($) {Drupal.behaviors.dataSlide = {  attach: function (context, settings) {	$(document).foundation();  }};})(jQuery);