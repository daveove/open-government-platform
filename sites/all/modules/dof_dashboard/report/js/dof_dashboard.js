/**
 * Sends the current page to the printer
 */
function infographics_print() {
    window.print();
}



(function ($) {
Drupal.behaviors.CHED = {
  attach: function (context, settings) {

	var activeIdx = parseInt(jQuery("#default-active").val());
	$( "#accordion2" ).accordion({
		heightStyle: "content", autoHeight: false, collapsible: true, active: activeIdx });

	$( "#dofaccording" ).accordion({
		heightStyle: "content", autoHeight: false, collapsible: true, active: false });



	// COMMODITY IMPORTS
    $('body.page-infographics-commodity-import .year-ref').click(function(){
			var month = jQuery("#month").val();
			var order = jQuery("#order").val();
			var extra_url = '';

		    if(month){
				extra_url += '/'+month;
			}
		    if(order){
				extra_url += '/'+order;
			}

            dof_dashboardYearChanged(jQuery(this).text(), 'commodity-import/1', extra_url); 
        });
	// end COMMODITY IMPORTS


	// COMMODITY REPORT (RICE IMPORTS)
    $('body.page-infographics-commodity-report-rice .year-ref').click(function(){
			var month = jQuery("#month").val();
			var port_url = jQuery("#port_url").val();
			var order = jQuery("#order").val();
			var extra_url = '';

		    if(month){
				extra_url += '/'+month;
			}
		    if(port_url){
				extra_url += '/'+port_url;
			}
		    if(order){
				extra_url += '/'+order;
			}

            dof_dashboardYearChanged(jQuery(this).text(), 'commodity-report-rice/1', extra_url); 
        });
	// end COMMODITY REPORT (RICE IMPORTS)


	// COMMODITY REPORT (MOTOR VEHICLE IMPORTS)
    $('body.page-infographics-commodity-report-motor .year-ref').click(function(){
			var month = jQuery("#month").val();
			var port_url = jQuery("#port_url").val();
			var order = jQuery("#order").val();
			var extra_url = '';

		    if(month){
				extra_url += '/'+month;
			}
		    if(port_url){
				extra_url += '/'+port_url;
			}
		    if(order){
				extra_url += '/'+order;
			}

            dof_dashboardYearChanged(jQuery(this).text(), 'commodity-report-motor/1', extra_url); 
        });
	// end COMMODITY REPORT (MOTOR VEHICLE IMPORTS)



	// TOP MOTOR VEHICLE IMPORTS BY TYPE
    $('body.page-infographics-commodity-report-motor-by-type .year-ref').click(function(){
			var month = jQuery("#month").val();
			var order = jQuery("#order").val();
			var extra_url = '';

		    if(month){
				extra_url += '/'+month;
			}
		    if(order){
				extra_url += '/'+order;
			}

            dof_dashboardYearChanged(jQuery(this).text(), 'commodity-report-motor-by-type/1', extra_url); 
        });
	// end TOP MOTOR VEHICLE IMPORTS BY TYPE


	// TOP MOTOR VEHICLE IMPORTERS
    $('body.page-infographics-commodity-report-motor-importers .year-ref').click(function(){
			var month = jQuery("#month").val();
			var order = jQuery("#order").val();
			var extra_url = '';

		    if(month){
				extra_url += '/'+month;
			}
		    if(order){
				extra_url += '/'+order;
			}

            dof_dashboardYearChanged(jQuery(this).text(), 'commodity-report-motor-importers/1', extra_url); 
        });
	// end TOP MOTOR VEHICLE IMPORTERS


	// Trade Activity by port
    $('body.page-infographics-trade-activity .year-ref').click(function(){
			var month = jQuery("#month").val();
			var port_url = jQuery("#port_url").val();
			var order = jQuery("#order").val();
			var extra_url = '';

		    if(month){
				extra_url += '/'+month;
			}
		    if(port_url){
				extra_url += '/'+port_url;
			}
		    if(order){
				extra_url += '/'+order;
			}

            dof_dashboardYearChanged(jQuery(this).text(), 'trade-activity/1', extra_url); 
        });
	// end Trade activity by port


	// Brokers Importers
    $('body.page-infographics-brokers-importers .year-ref').click(function(){
			var group = jQuery("#group").val();
			var score = jQuery("#short").val();
			var extra_url = '';

		    if(group){
				extra_url += '/'+group;
			}
		    if(score){
				extra_url += '/'+score;
			}

            dof_dashboardYearChanged(jQuery(this).text(), 'brokers-importers/1', extra_url); 
        });
	// end Brokers Importers

  }

};
})(jQuery);



/**
 * Generic handler for change year event
 * @param year the selected year
 * @param dashb the dashboard identifier
 */
function dof_dashboardYearChanged(year, dashb, extra_url) {
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

		if(extra_url){
			uri += extra_url;
		}
		//alert (uri);
        location.href = uri;
    }
}