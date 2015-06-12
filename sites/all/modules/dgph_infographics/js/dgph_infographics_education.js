/**
 * Sends the current page to the printer
 */
function infographics_print() {
    window.print();
}
/**
 * Free schools search
 * @param key the lookup key, or <code>null</code> to search by school name
 */
function lookupSchools(key) {
    var svalue = jQuery('#edu_free_search').val();
    if ((svalue!=null) && (svalue.length>0)) {
        var uri = location.pathname+'?school='+svalue;
        if (key!=null) {
            uri += '&key='+key;
        }
        location.href = uri;
    }
}
function lookupSchoolsKeydown(ev) {
    if (ev.keyCode == 13) {
        lookupSchools();
    }
}

/**
 * Handler for change school year event
 * @param year the selected year
 */
function dashboardSchoolYearChanged(year) {
    var pos = year.indexOf('-');
    if (pos>-1) {
        year = year.substring(0, pos);
    }
    var uri = '/infographics/education/'+year;
    location.href = uri;
}

jQuery(document).ready(function() {
    jQuery('.edu-year-ref').click(function(){
            dashboardSchoolYearChanged(jQuery(this).text()); 
        });
    jQuery('td a').tooltip({ position: { my: "center bottom+10", at: "center top" } });
    jQuery('#lookup-school').on('click', function(){
            jQuery('#lookup-category').slideToggle('slow');
        });
})