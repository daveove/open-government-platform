// JavaScript Document

var chart16;
var rChartData16;
var chartData16 = [
[	//2013
    {	
		"label" : "R6",
        "litres": 73317107
    },
    {
        "label": "R7",
        "litres": 63383939
    },
	{
        "label": "R8",
        "litres": 55374677
    }
],[		//2012
    {	
		"label" : "R6",
        "litres": 62831630
    },
    {
        "label": "R7",
        "litres": 54435252
    },
	{
        "label": "R8",
        "litres": 49370036
    }
],[		//2011
    {	
		"label" : "R6",
        "litres": 50341903
    },
    {
        "label": "R7",
        "litres": 41080696
    },
	{
        "label": "R8",
        "litres": 34628516
    }
],[		//2010
    {	
		"label" : "R6",
        "litres": 47258924
    },
    {
        "label": "R7",
        "litres": 36530106
    },
	{
        "label": "R8",
        "litres": 33190052
    }
],[
    {	
		"label" : "R6",
        "litres": 45545049
    },
    {
        "label": "R7",
        "litres": 35998644
    },
	{
        "label": "R8",
        "litres": 32624097
    }
]
];

AmCharts.ready(function () {
	rChartData16 = chartData16[0];
	drawChart16();
});

function drawChart16(){
    // PIE CHART
    chart16 = new AmCharts.AmPieChart();
    chart16.dataProvider = rChartData16;
    
    chart16.titleField = "label";
    chart16.valueField = "litres";
    chart16.outlineColor = "#FFFFFF";
    chart16.outlineAlpha = 0.8;
    chart16.outlineThickness = 2;
    chart16.balloonText = "[[title]]<br><span style='font-size:14px'><b>[[value]]</b> ([[percents]]%)</span>";
	chart16.colors = [ "#c7c8a7", "#dddec6", "#afae87", "#bfbe97" ];
    
     chart16.labelsEnabled=true;
    chart16.labelText="[[title]]";
    chart16.fontSize=16;
    chart16.color = "#ffffff";chart16.labelRadius=-80
    
	
    // WRITE
    chart16.write("regional-visayas-chart");
}
