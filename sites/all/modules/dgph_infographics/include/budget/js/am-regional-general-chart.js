// JavaScript Document

var chart16;
var rChartData16;
var chartData16 = [
[
    {	
		"label" : "General",
        "litres": 93760
    },
    {
        "label": "Public",
        "litres": 95100
    },
	{
        "label": "Other",
        "litres": 22303
    },
	{
        "label": "Subsidy",
        "litres": 74425
    }
],[
    {	
		"label" : "General",
        "litres": 79522
    },
    {
        "label": "Public",
        "litres": 118398
    },
	{
        "label": "Other",
        "litres": 9826
    },
	{
        "label": "Subsidy",
        "litres": 80344
    }
],[
    {	
		"label" : "General",
        "litres": 112039
    },
    {
        "label": "Public",
        "litres": 115897
    },
	{
        "label": "Other",
        "litres": 15868
    },
	{
        "label": "Subsidy",
        "litres": 76527
    }
],[
    {	
		"label" : "General",
        "litres": 124458
    },
    {
        "label": "Public",
        "litres": 124279
    },
	{
        "label": "Other",
        "litres": 13944
    },
	{
        "label": "Subsidy",
        "litres": 84645
    }
],[
    {	
		"label" : "General",
        "litres": 117057
    },
    {
        "label": "Public",
        "litres": 134526
    },
	{
        "label": "Other",
        "litres": 17307
    },
	{
        "label": "Subsidy",
        "litres": 95633
    }
]
];

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
    chart16.write("regional-general-chart");
}

AmCharts.ready(function () {
	rChartData16 = chartData16[0];
	drawChart16();
});