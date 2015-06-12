// JavaScript Document

var chart14;

var rChartData14;
var chartData14 = [
[
    {
        "label": "A",
        "litres": 240585
    },
    {
        "label": "B",
        "litres": 40030
    },
    {
        "label": "C",
        "litres": 103570
    },
    {
        "label": "D",
        "litres": 5466
    },
    {
        "label": "E",
        "litres": 1279
    },
	{
        "label": "F",
        "litres": 2236
    },
	{
        "label": "G",
        "litres": 98347
    }
],[
    {
        "label": "A",
        "litres": 271493
    },
    {
        "label": "B",
        "litres": 38392
    },
    {
        "label": "C",
        "litres": 94105
    },
    {
        "label": "D",
        "litres": 5737
    },
    {
        "label": "E",
        "litres": 3966
    },
	{
        "label": "F",
        "litres": 1583
    },
	{
        "label": "G",
        "litres": 106169
    }
],[
    {
        "label": "A",
        "litres": 299958
    },
    {
        "label": "B",
        "litres": 50559
    },
    {
        "label": "C",
        "litres": 150368
    },
    {
        "label": "D",
        "litres": 7086
    },
    {
        "label": "E",
        "litres": 2500
    },
	{
        "label": "F",
        "litres": 1795
    },
	{
        "label": "G",
        "litres": 101125
    }
],[
    {
        "label": "A",
        "litres": 330181
    },
    {
        "label": "B",
        "litres": 57738
    },
    {
        "label": "C",
        "litres": 169464
    },
    {
        "label": "D",
        "litres": 23334
    },
    {
        "label": "E",
        "litres": 5000
    },
	{
        "label": "F",
        "litres": 1871
    },
	{
        "label": "G",
        "litres": 111852
    }
],[
    {
        "label": "A",
        "litres": 389518
    },
    {
        "label": "B",
        "litres": 88346
    },
    {
        "label": "C",
        "litres": 214923
    },
    {
        "label": "D",
        "litres": 16662
    },
    {
        "label": "E",
        "litres": 5000
    },
	{
        "label": "F",
        "litres": 1985
    },
	{
        "label": "G",
        "litres": 126372
    }
]
];

AmCharts.ready(function () {
	rChartData14 = chartData14[0];
	drawChart14();
});

function drawChart14(){
    // PIE CHART
    chart14 = new AmCharts.AmPieChart();
    chart14.dataProvider = rChartData14;
    chart14.titleField = "label";
    chart14.valueField = "litres";
    chart14.outlineColor = "#FFFFFF";
    chart14.outlineAlpha = 0.8;
    chart14.outlineThickness = 2;
    chart14.balloonText = "[[title]]<br><span style='font-size:14px'><b>[[value]]</b> ([[percents]]%)</span>";
	chart14.colors = [ "#ebaead", "#f7c9c9", "#f5d5d5", "#ea9593", "#f69b98", "#f5b8b8", "#f5c8d8" ];
         chart14.labelsEnabled=true;
    chart14.labelText="[[title]]";
    chart14.fontSize=16;
    chart14.color = "#ffffff";
	chart14.labelRadius=-80
    
	
    // WRITE
    chart14.write("regional-social-chart");
	
}