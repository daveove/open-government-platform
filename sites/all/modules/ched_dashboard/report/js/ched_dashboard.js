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


	// dashboard 1 pillar 1
	$("form.custom.dash1pill1 span.custom.checkbox").click(function(){

			var obj = jQuery(this).prev("form.custom.dash1pill1 input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var cmp_year = obj.attr('dash1-p1');
                }
            }

		/*
        var val = [];
        $('.dash1pill1 :checkbox:checked').each(function(i){
          val[i] = $(this).val();

		  alert($(this).val());

        });
		*/

			var ch_act = parseInt(jQuery("#default-active").val());
			if(ch_act==3){
				var uri = '/infographics/ched-higher-education/d1/1/2012/2013';
			} else {
				var uri = location.pathname;
			}
			
		    var path = '';

		    path = '/cmp/'+cmp_year;

			if(cmp_year=='2010' || cmp_year=='2011') {
				location.href = uri+path;
			} else {
				location.href = '/infographics/ched-higher-education/d1/1/2012/2013';				
			}
    });
	// End dashboard 1 pillar 1


	// dashboard 1 pillar 1 choose by year (see single year data on graph)
	$("form.custom.dash1pill1choose span.custom.checkbox").click(function(){
		$("form.custom.dash1pill1choose span.custom.checkbox").removeClass('checked');

			var obj = jQuery(this).prev("form.custom.dash1pill1choose input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var date_range = obj.attr('dash1-p1');
                }
            }
			
			var uri = '/infographics/ched-higher-education/d1/1/'+date_range+'/choose';			

			if(date_range=='2010/2011' || date_range=='2011/2012' || date_range=='2012/2013') {
				location.href = uri;			
			} else {
				location.href = '/infographics/ched-higher-education/d1/1/2012/2013';				
			}

    });
	// End dashboard 1 pillar 1 choose by year (see single year data on graph)


	// dashboard 1 pillar 2
	$("form.custom.dash1pill2 span.custom.checkbox").click(function(){
		$("form.custom.dash1pill2 span.custom.checkbox").removeClass('checked');

			var obj = jQuery(this).prev("form.custom.dash1pill2 input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var date_range = obj.attr('dash1-p2');
                }
            }
			var uri = '/infographics/ched-higher-education/d1/2/'+date_range;			

			if(date_range=='2010/2011' || date_range=='2011/2012' || date_range=='2012/2013') {
				location.href = uri;			
			} else {
				location.href = '/infographics/ched-higher-education/d1/2/2012/2013';				
			}
    });
	// End dashboard 1 pillar 2


	// dashboard 1 pillar 3
	$("form.custom.dash1pill3 span.custom.checkbox").click(function(){
		$("form.custom.dash1pill3 span.custom.checkbox").removeClass('checked');

			var obj = jQuery(this).prev("form.custom.dash1pill3 input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var date_range = obj.attr('dash1-p3');
                }
            }
			var uri = '/infographics/ched-higher-education/d1/3/'+date_range;
			
			if(date_range=='2010/2011' || date_range=='2011/2012' || date_range=='2012/2013') {
				location.href = uri;			
			} else {
				location.href = '/infographics/ched-higher-education/d1/3/2012/2013';				
			}
    });
	// End dashboard 1 pillar 3


	// dashboard 1 pillar 4
	$("form.custom.dash1pill4 span.custom.checkbox").click(function(){
		$("form.custom.dash1pill4 span.custom.checkbox").removeClass('checked');

			var obj = jQuery(this).prev("form.custom.dash1pill4 input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var date_range = obj.attr('dash1-p4');
                }
            }
			var uri = '/infographics/ched-higher-education/d1/4/'+date_range+'/choose';
			
			if(date_range=='2010/2011' || date_range=='2011/2012' || date_range=='2012/2013') {
				location.href = uri;			
			} else {
				location.href = '/infographics/ched-higher-education/d1/4/2012/2013';				
			}
    });
	// End dashboard 1 pillar 4

	
	// dashboard 2 pillar 1
	$("form.custom.dash2pill1 span.custom.checkbox").click(function(){
		$("form.custom.dash2pill1 span.custom.checkbox").removeClass('checked');

			var obj = jQuery(this).prev("form.custom.dash2pill1 input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var date_range = obj.attr('dash2-p1');
                }
            }
			var uri = '/infographics/ched-higher-education/d2/1/'+date_range+'/choose';

			if(date_range=='2010/2011/enrollment' || date_range=='2011/2012/enrollment' || date_range=='2012/2013/enrollment' || date_range=='2010/2011/graduates' || date_range=='2011/2012/graduates' || date_range=='2012/2013/graduates') {
				location.href = uri;
			} else {
				location.href = '/infographics/ched-higher-education/d2/1/2012/2013/enrollment';				
			}
    });
	// End dashboard 2 pillar 1


	// dashboard 2 pillar 2
	$("form.custom.dash2pill2 span.custom.checkbox").click(function(){

			var obj = jQuery(this).prev("form.custom.dash2pill2 input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var cmp_year = obj.attr('dash2-p2');
                }
            }	

			var ch_act = parseInt(jQuery("#default-active").val());
			if(ch_act==3){
				var uri = '/infographics/ched-higher-education/d2/2/2012/2013/enrollment';
			} else {
				var uri = location.pathname;
			}
			
		    var path = '';

		    path = '/cmp/'+cmp_year;

			if(cmp_year=='2010' || cmp_year=='2011') {
				location.href = uri+path;
			} else {
				location.href = '/infographics/ched-higher-education/d2/2/2012/2013/enrollment';				
			}
    });
	// End dashboard 2 pillar 2

	// dashboard 2 pillar 2 choose by year (see single year data on graph)
	$("form.custom.dash2pill2choose span.custom.checkbox").click(function(){
		$("form.custom.dash2pill2choose span.custom.checkbox").removeClass('checked');

			var obj = jQuery(this).prev("form.custom.dash2pill2choose input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var date_range = obj.attr('dash2-p2');
                }
            }

			var en_gr = $("#en-gr").val();
			
			var uri = '/infographics/ched-higher-education/d2/2/'+date_range+'/'+en_gr+'/choose';			

			if(date_range=='2010/2011' || date_range=='2011/2012' || date_range=='2012/2013') {
				location.href = uri;			
			} else {
				location.href = '/infographics/ched-higher-education/d2/2/2012/2013/enrollment';				
			}

    });
	// End dashboard 2 pillar 2 choose by year (see single year data on graph)


	// dashboard 2 pillar 3
	$("form.custom.dash2pill3 span.custom.checkbox").click(function(){

			var obj = jQuery(this).prev("form.custom.dash2pill3 input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var cmp_year = obj.attr('dash2-p3');
                }
            }			

			var ch_act = parseInt(jQuery("#default-active").val());
			if(ch_act==3){
				var uri = '/infographics/ched-higher-education/d2/3/2012/2013/enrollment';
			} else {
				var uri = location.pathname;
			}
			
		    var path = '';

		    path = '/cmp/'+cmp_year;

			if(cmp_year=='2010' || cmp_year=='2011') {
				location.href = uri+path;
			} else {
				location.href = '/infographics/ched-higher-education/d2/3/2012/2013/enrollment';
			}
    });
	// End dashboard 2 pillar 3


	// dashboard 2 pillar 3 choose by year (see single year data on graph)
	$("form.custom.dash2pill3choose span.custom.checkbox").click(function(){
		$("form.custom.dash2pill3choose span.custom.checkbox").removeClass('checked');

			var obj = jQuery(this).prev("form.custom.dash2pill3choose input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var date_range = obj.attr('dash2-p3');
                }
            }

			var en_gr = $("#en-gr").val();
			
			var uri = '/infographics/ched-higher-education/d2/3/'+date_range+'/'+en_gr+'/choose';			

			if(date_range=='2010/2011' || date_range=='2011/2012' || date_range=='2012/2013') {
				location.href = uri;			
			} else {
				location.href = '/infographics/ched-higher-education/d2/3/2012/2013/enrollment';				
			}

    });
	// End dashboard 2 pillar 3 choose by year (see single year data on graph)


	// dashboard 3 pillar 1
	$("form.custom.dash3pill1 span.custom.checkbox").click(function(){
		$("form.custom.dash3pill1 span.custom.checkbox").removeClass('checked');

			var obj = jQuery(this).prev("form.custom.dash3pill1 input[type='checkbox']");
                        if (obj.is(':enabled')) {
                            var prevChk = obj.attr('checked');
                            if (prevChk!='checked') {
                                var date_range = obj.attr('dash3-p1');
                            }
                        }
			var uri = '/infographics/ched-higher-education/d3/1/'+date_range+'/choose';
	
			if(date_range=='2010/2011' || date_range=='2011/2012' || date_range=='2012/2013') {
				location.href = uri;			
			} else {
				location.href = '/infographics/ched-higher-education/d3/1/2012/2013';				
			}
    });
	// End dashboard 3 pillar 1


	// dashboard 3 pillar 2
	$("form.custom.dash3pill2 span.custom.checkbox").click(function(){
		$("form.custom.dash3pill2 span.custom.checkbox").removeClass('checked');

			var obj = jQuery(this).prev("form.custom.dash3pill2 input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var date_range = obj.attr('dash3-p2');
                }
            }
			var uri = '/infographics/ched-higher-education/d3/2/'+date_range+'/choose';

			if(date_range=='2010/2011' || date_range=='2011/2012' || date_range=='2012/2013') {
				location.href = uri;			
			} else {
				location.href = '/infographics/ched-higher-education/d3/2/2012/2013';				
			}
    });
	// End dashboard 3 pillar 2




	$( ".region" ).change(function() {
		var reg = $( ".region" ).val();
		 //alert( "Handler for .change() called." + reg );

		 var uri = location.pathname+'?region='+reg;

		 location.href = uri;
    });

	$( ".college_university" ).change(function() {
		 var reg = $( ".region" ).val();
		 var suc = $( ".college_university" ).val();
		 var uri = location.pathname+'?region='+reg+'&suc='+suc;
		 location.href = uri;
    });

	$("form.custom.dash4total span.custom.checkbox").click(function(){
		$("form.custom.dash4total span.custom.checkbox").removeClass('checked');
		 var reg = $( ".region" ).val();
		 var suc = $( ".college_university" ).val();

		 var uri = location.pathname+'?';
		 var path = '';

		 if(reg){ path = 'region='+reg; }
		 if(suc){ path = path+'&suc='+suc; }

            var obj = jQuery(this).prev("form.custom.dash4total input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var qid = obj.attr('quarter-id');										
                }
            }
			if(qid){ path = path+'&tot='+qid; }

            var obj1 = jQuery(this).prev("form.custom.dash4psc input[type='checkbox']");
            if (obj1.is(':enabled')) {
                var prevChk1 = obj1.attr('checked');
                if (prevChk1!='checked') {
                    var psc_id = obj1.attr('psc-id');						
                }
            }
			if(psc_id){ path = path+'&psc='+psc_id; }

			location.href = uri+path;
    });

	$("form.custom.dash4psc span.custom.checkbox").click(function(){
		$("form.custom.dash4psc span.custom.checkbox").removeClass('checked');
		 var reg = $( ".region" ).val();
		 var suc = $( ".college_university" ).val();

		 var uri = location.pathname+'?';
		 var path = '';

		 if(reg){ path = 'region='+reg; }
		 if(suc){ path = path+'&suc='+suc; }


            var obj = jQuery(this).prev("form.custom.dash4total input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                if (prevChk!='checked') {
                    var qid = obj.attr('quarter-id');									
                }
            }
			if(qid){ path = path+'&tot='+qid; }

            var obj1 = jQuery(this).prev("form.custom.dash4psc input[type='checkbox']");
            if (obj1.is(':enabled')) {
                var prevChk1 = obj1.attr('checked');
                if (prevChk1!='checked') {
                    var psc_id = obj1.attr('psc-id');						
                }
            }
			if(psc_id){ path = path+'&psc='+psc_id; }

			location.href = uri+path;
    });
    
    // dashboard 4 choose by year (see single year data on graph)
	jQuery("form.custom.dash4pill1 span.custom.checkbox").click(function(){
            jQuery("form.custom.dash4pill1 span.custom.checkbox").removeClass('checked');
            var obj = jQuery(this).prev("form.custom.dash4pill1 input[type='checkbox']");
            if (obj.is(':enabled')) {
                var prevChk = obj.attr('checked');
                var dateRange = "";
                if (prevChk!='checked') {
                    dateRange = obj.attr('dash4-p1');
                }
                var uri = '/infographics/ched-higher-education/d4/1/'+dateRange;
                if(dateRange=='2010/2011' || dateRange=='2011/2012' || dateRange=='2012/2013') {
                    location.href = uri;			
                } else {
                    location.href = '/infographics/ched-higher-education/d4/1/2012/2013';				
                }
            }
        });

  }
};
})(jQuery);