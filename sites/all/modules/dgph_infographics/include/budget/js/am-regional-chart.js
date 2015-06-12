// JavaScript Document

function bigMap()

{
    jQuery('#test_close').css({
		              'opacity': 0,'z-index':1});
    jQuery('#regional-chart').css({
		              'opacity': 1,'z-index':999});
}

var chart13;
var rChartData13;
var chartData13 = 
[
	[	//2013
		{
    		"label": "NCR",
			"litres": 129628330
		},
		{
  			"label": "Luzon",
			"litres": 402578217
		},
		{
			"label": "Visayas",
			"litres": 192075723
		},
		{
			"label": "Mindanao",
			"litres": 254816333
		},
		{
  			"label": "Regionalized",
			"litres": 979098603
		}
	],
	[	//2012
		{
			"label": "NCR",
			"litres": 120281083
		},
		{
			"label": "Luzon",
			"litres": 352935383
		},
		{
			"label": "Visayas",
			"litres": 166636918
		},
		{
			"label": "Mindanao",
			"litres": 226645204
		},
		{
			"label": "Regionalized",
			"litres": 866498588
		}
	],
	[	//2011
		{
			"label": "NCR",
			"litres": 58835327
		},
		{
			"label": "Luzon",
			"litres": 268321024
		},
		{
			"label": "Visayas",
			"litres": 123051115
		},
		{
			"label": "Mindanao",
			"litres": 163978083
		},
		{
			"label": "Regionalized",
			"litres": 617185549
		}
	],
	[	//2010
		{
			"label": "NCR",
			"litres": 52346710
		},
		{
			"label": "Luzon",
			"litres": 242158208
		},
		{
			"label": "Visayas",
			"litres": 116979082
		},
		{
			"label": "Mindanao",
			"litres": 148158965
		},
		{
			"label": "Regionalized",
			"litres": 559642965
		}
	],
	[	//2009		
		{
			"label": "NCR",
			"litres": 52375902 
		},
		{
			"label": "Luzon",
			"litres": 239474389
		},
		{
			"label": "Visayas",
			"litres": 114167790
		},
		{
			"label": "Mindanao",
			"litres": 151063596
		},
		{
			"label": "Regionalized",
			"litres": 557081677
		}
	]
];

function pieClick(event)
{
    
    jQuery('#regional-ncr-chart').css({
		              'opacity': 0,'z-index':0,});
    jQuery('#regional-luzon-chart').css({
		              'opacity': 0,'z-index':0,});
    jQuery('#regional-visayas-chart').css({
		              'opacity': 0,'z-index':0,});
    jQuery('#regional-mindanao-chart').css({
		              'opacity': 0,'z-index':0,});
	jQuery('#regional-regionalized-chart').css({
		              'opacity': 0,'z-index':0,});					  
    jQuery('#divNCR').css({
		              'opacity': 0,'z-index':0,});				  					  
    jQuery('#divLuzon').css({
		              'opacity': 0,'z-index':0,});			  					  					  
    jQuery('#divGroup').css({
		              'height': '1000px'});					  					  					  					  
    
	switch(event.dataItem.title)
    {
           case 'NCR':
                jQuery('#regional-ncr-chart').css({
		              'opacity': 1,'z-index':999,
                        });
                jQuery('#divNCR').css({
		              'opacity': 1,'z-index':999,
                        });						
                break;
            
            case 'Luzon':
                jQuery('#regional-luzon-chart').css({
		              'opacity': 1,'z-index':999,
                        });
                jQuery('#divLuzon').css({
		              'opacity': 1,'z-index':999,
                        });						
                break;
            
            case 'Visayas':
                jQuery('#regional-visayas-chart').css({
		              'opacity': 1,'z-index':999,
                        });                
                break;
            
            case 'Mindanao':
                jQuery('#regional-mindanao-chart').css({
		              'opacity': 1,'z-index':999,
                        });
                break;
            
            case 'Regionalized':
                jQuery('#regional-regionalized-chart').css({
		              'opacity': 1,'z-index':999,
                        });
            
                break; 
                
        }
    

}

function drawChart13(){
    // PIE CHART
    chart13 = new AmCharts.AmPieChart();
    chart13.dataProvider = rChartData13;
    
    
	// add click listener
    chart13.addListener("clickSlice", pieClick);
    
    chart13.titleField = "label";
    chart13.labelsEnabled=true;
    chart13.labelText="[[title]]";
    chart13.valueField = "litres";
    chart13.fontSize=16;
    chart13.color = "#ffffff";
    chart13.outlineColor = "#FFFFFF";
    chart13.pullOutOnlyOne = true;
    chart13.labelRadius=-80
    chart13.outlineAlpha = 0.8;
    chart13.outlineThickness = 2;
    chart13.balloonText = "[[title]]<br><span style='font-size:14px'><b>[[value]]</b> ([[percents]]%)</span>";
	chart13.colors = [ "#ec7878", "#f69c99", "#c6c8a6", "#81b09c", "#fcceac" ];
    
    // WRITE
    chart13.write("regional-chart");
}
AmCharts.ready(function () {
	rChartData13 = chartData13[0];
	drawChart13();
});
