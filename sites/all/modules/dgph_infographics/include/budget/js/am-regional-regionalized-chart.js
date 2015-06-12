
// JavaScript Document

var chart44;

var rChartData44;
var chartData44 = [
[	//2013
    {
        "label": "Nationwide",
        "litres": 417115815
	},
	{
        "label": "Central Office",
        "litres": 609685582
    }
],[	//2012
    {
        "label": "Nationwide",
        "litres": 395598696
    },
	{
        "label": "Central Office",
        "litres": 553902716
    }
],[ //2011
    {
        "label": "Nationwide",
        "litres": 506751867
    },
	{
        "label": "Central Office",
        "litres": 521062584
    }
],[	//2010
    {
        "label": "Nationwide",
        "litres": 477547939
    },
	{
        "label": "Central Office",
        "litres": 503809096
    }
],[	//2009
    {
        "label": "Nationwide",
        "litres": 338984262
    },
	{
        "label": "Central Office",
        "litres": 518934061
    }
]
];

AmCharts.ready(function () {
	rChartData44 = chartData44[0];
	drawChart44();
});

function drawChart44(){
    // PIE CHART
    chart44 = new AmCharts.AmPieChart();
    chart44.dataProvider = rChartData44;
    chart44.titleField = "label";
    chart44.valueField = "litres";
    chart44.outlineColor = "#FFFFFF";
    chart44.outlineAlpha = 0.8;
    chart44.outlineThickness = 2;
    chart44.balloonText = "[[title]]<br><span style='font-size:14px'><b>[[value]]</b> ([[percents]]%)</span>";
	chart44.colors = [ "#ebaead"];
    chart44.labelsEnabled=true;
    chart44.labelText="[[title]]";
    chart44.fontSize=16;
    chart44.color = "#ffffff";
	chart44.labelRadius=-80;
    
	
    // WRITE
    chart44.write("regional-regionalized-chart");
}