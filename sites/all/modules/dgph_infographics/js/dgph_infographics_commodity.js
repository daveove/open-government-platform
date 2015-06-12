/**
 * Triggers a compare by year action in the yearly view
 * @param yearId the identifier of the year to compare the current yearly view with
 */
function compareByYear(yearId) {
    var year = 0;
    if (yearId=='cd_year1') {
        year = 2012;
    }
    else if (yearId=='cd_year2') {
        year = 2013;
    }
    if (year>0) {
        // redirects to the comparison url
        var url = document.URL+"?cmp="+year;
        location.href = url;
    }
}


jQuery(document).ready(function() {
        jQuery(document).on('click', "form.custom label[for^=cd_year] span.custom.checkbox", function (event) {
            var obj = jQuery(this).prev("input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    compareByYear(obj.attr('id'));
                }
                else {
                    var url = location.protocol+'//'+location.host+location.pathname;
                    location.href = url;
                }
            }
        });
})