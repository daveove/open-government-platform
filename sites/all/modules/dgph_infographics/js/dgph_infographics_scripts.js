/**
 * Sends the current page to the printer
 */
function infographics_print() {
    window.print();
}
/**
 * Free search for Agency Procurement Notices and Details dashboard
 * @param sname the name of the search field
 * @param baseUri base URI for search
 */
function lookupAPND(sname, baseUri) {
    var svalue = jQuery('#apnd_free_search').val();
    if (svalue!=null && svalue.length>3) {
        svalue = svalue.replace(' ', '+', 'g');
        var uri = baseUri+'/'+sname+'/'+svalue;
        location.href = uri;
    }
}

/**
 * Generic handler for change year event
 * @param year the selected year
 * @param dashb the dashboard identifier
 */
function dashboardYearChanged(year, dashb) {
    var exp = /^\d+$/;
    if(exp.test(year)) {
        var deptId = jQuery('#selected-agency-id').text();
        var uri = '/infographics/'+dashb;
        if (deptId!='') {
            uri += '/'+deptId+'/'+year;
        }
        else {
            uri += '/'+year;
        }
        location.href = uri;
    }
}

/**
 * Handler for change agency event
 * @param deptId the selected agency (department) identifier
 * @param dashb the dashboard identifier
 */
function dashboardAgencyChanged(deptId, dashb) {
    var year = jQuery('#selected-year').text();
    var uri = '/infographics/'+dashb+'/'+deptId+'/'+year;
    location.href = uri;
}

/**
 * Handler for change quarter event
 * @param quarterId the selected quarter identifier
 * @param dashb the dashboard identifier
 */
function dashboardQuarterChanged(quarterId, dashb) {
    var objId = null;
    for(var i=1; i<=4; i++) {
        if (i!=quarterId) {
            objId = '#dbm_q'+i;
            jQuery(objId).next('span.custom.checkbox').removeClass('checked');
        }
    }
    var year = jQuery('#selected-year').text();
    var deptId = jQuery('#selected-agency-id').text();
    var pillarId = jQuery('#selected-pillar-id').text();
    var trendId = jQuery('#selected-trend-id').text();
    var uri = '/infographics/'+dashb+'/'+deptId+'/'+year+'/'+quarterId+'/'+pillarId+'/'+trendId;
    location.href = uri;
}

/**
 * Handler for change month event
 * @param monthId the selected month identifier (1 = January, 2 = February, ...)
 * @param dashb the dashboard identifier
 */
function dashboardMonthChanged(monthId, dashb) {
    var objId = null;
    for(var i=1; i<=12; i++) {
        if (i!=monthId) {
            objId = '#cd_month'+i;
            jQuery(objId).next('span.custom.checkbox').removeClass('checked');
        }
    }
    var year = jQuery('#selected-year').text();
    var mid = jQuery('#selected-macro-category').text();
    var viewBy = 1; // view by month
    var uri = '/infographics/'+dashb+'/'+year+'/'+mid+'/'+viewBy+'/'+monthId;
    location.href = uri;
}

/**
 * Handler for change year event (Budget)
 * @param year the selected year
 */
function budgetYearChanged(year) {
    var exp = /^\d+$/;
    if(exp.test(year)) {
        var deptId = jQuery('#selected-agency-id').text(),
            quarterId = jQuery('#selected-quarter-id').text(),
            pillarId = jQuery('#selected-pillar-id').text(),
            trendId = jQuery('#selected-trend-id').text();
        var uri = '/infographics/dbm/'+deptId+'/'+year+'/'+quarterId+'/'+pillarId+'/'+trendId;
        location.href = uri;
    }
}

/**
 * Called when the selected category is changed on the Commodity Dashboard (Monthly View)
 * @param idx the category index
 * @param mid identifier of the macro - category this category belongs to
 */
function cd_category_changed(idx, mid){
    var visId = 'visibility-state'+idx,
        subId = 'sub'+idx,
        plusId = 'plus'+idx,
        selfId = 'state'+idx,
        iconName = 'm'+mid+'c'+idx;
    var code = '<style>#'+selfId+'{background: url("/sites/all/modules/dgph_infographics/images/'+iconName+'-big.png") no-repeat scroll 10px 50% #FFC425 !important; font-family: "Roboto", sans-serif; font-weight: bold; font-size: 30px !important; height: 55px;}</style>';
    jQuery('#for_css_class').html(code);
    jQuery("#"+subId).toggle();
    jQuery("#"+plusId).toggle();
    if (jQuery("#"+visId).is(':visible')) {
        // slide up this category
        jQuery("#"+visId+" .category-container").slideUp('slow', function() { jQuery("#"+visId).hide(); });
    }
    else {
        // slide down this category
        jQuery("#"+visId).show();
        jQuery("#"+visId+" .category-container").hide();
        jQuery("#"+visId+" .category-container").slideDown('slow');
    }
}

jQuery(document).ready(function() {
    var activeIdx = parseInt(jQuery("#default-active").val());
    jQuery('#accordion-notices-search').accordion({ 
            heightStyle: "content", autoHeight: false, collapsible: true, active: activeIdx });
    jQuery('#accordion-notices').accordion({collapsible: true, active: false, heightStyle: "content", autoHeight: true});
    jQuery('.apcpi-year-ref').click(function(){
            dashboardYearChanged(jQuery(this).text(), 'procurement-compliance'); 
        });
    jQuery('.apcpi-agency-ref').click(function(){ 
            dashboardAgencyChanged(jQuery(this).attr('dept-id'), 'procurement-compliance'); 
        });  
    jQuery('.dbm-year-ref').click(function(){
            budgetYearChanged(jQuery(this).text()); 
        });
    jQuery('.dbm-agency-ref').click(function(){ 
            dashboardAgencyChanged(jQuery(this).attr('dept-id'), 'dbm'); 
        });  
    jQuery('.commodity-year-ref').click(function(){
            dashboardYearChanged(jQuery(this).text(), 'commodity'); 
        });
    jQuery('#lookup-apnd').on('click', function(){
            jQuery('#lookup-category').slideToggle('slow');
        });
    jQuery(document).on('click', 'form.custom span.custom.checkbox', function (event) {
            var obj = jQuery(this).prev("input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var qid = obj.attr('quarter-id');
                    if (typeof(qid)!='undefined' && parseInt(qid)>=1) {
                        dashboardQuarterChanged(qid, 'dbm');
                    }
                    var monthId = obj.attr('month-id');
                    if (typeof(monthId)!='undefined' && parseInt(monthId)>=1 && parseInt(monthId)<=12) {
                        dashboardMonthChanged(monthId, 'commodity');
                    }
                }
            }
        });
})