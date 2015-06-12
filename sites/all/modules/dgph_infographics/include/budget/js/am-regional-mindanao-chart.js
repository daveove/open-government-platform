// JavaScript Document

var chart17;
var rChartData17;
var chartData17 = [
[
    {
        "label": "R9",
        "litres": 41862605
    },
	{
        "label": "R10",
        "litres": 47609716
    },
	{
        "label": "R11",
        "litres": 46749157
    },
	{
        "label": "R12",
        "litres": 42843474
    },
	{
        "label": "CARAGA",
        "litres": 34292030
    },
	{
        "label": "ARMM",
        "litres": 41459351
    }
],[
     {
        "label": "R9",
        "litres": 37154440
    },
	{
        "label": "R10",
        "litres": 42770556
    },
	{
        "label": "R11",
        "litres": 37680673
    },
	{
        "label": "R12",
        "litres": 38411950
    },
	{
        "label": "CARAGA",
        "litres": 30705603
    },
	{
        "label": "ARMM",
        "litres": 39921982
    }
],[
     {
        "label": "R9",
        "litres": 24871689
    },
	{
        "label": "R10",
        "litres": 35025607
    },
	{
        "label": "R11",
        "litres": 27127968
    },
	{
        "label": "R12",
        "litres": 25616008
    },
	{
        "label": "CARAGA",
        "litres": 21953943
    },
	{
        "label": "ARMM",
        "litres": 29382868
    }
],[
     {
        "label": "R9",
        "litres": 22269016
    },
	{
        "label": "R10",
        "litres": 30621630
    },
	{
        "label": "R11",
        "litres": 25740772
    },
	{
        "label": "R12",
        "litres": 24298039
    },
	{
        "label": "CARAGA",
        "litres": 21214329
    },
	{
        "label": "ARMM",
        "litres": 24015179
    }
],[
     {
        "label": "R9",
        "litres": 23933902
    },
	{
        "label": "R10",
        "litres": 31477767
    },
	{
        "label": "R11",
        "litres": 25770694
    },
	{
        "label": "R12",
        "litres": 24200092
    },
	{
        "label": "CARAGA",
        "litres": 22152515
    },
	{
        "label": "ARMM",
        "litres": 23528626
    }
]
];

AmCharts.ready(function () {
	rChartData17 = chartData17[0];
	drawChart17();	
});

function drawChart17(){
    // PIE CHART
    chart17 = new AmCharts.AmPieChart();
    chart17.dataProvider = rChartData17;
    chart17.titleField = "label";
    chart17.valueField = "litres";
    chart17.outlineColor = "#FFFFFF";
    chart17.outlineAlpha = 0.8;
    chart17.outlineThickness = 2;
    chart17.balloonText = "[[title]]<br><span style='font-size:14px'><b>[[value]]</b> ([[percents]]%)</span>";
	chart17.colors = [ "#afc5b9" ];
	chart17.title = "Luzon";
    chart17.labelsEnabled=true;
    chart17.labelText="[[title]]";
    chart17.fontSize=16;
    chart17.color = "#ffffff";
	chart17.labelRadius=-80;
    
	
    // WRITE
    chart17.write("regional-mindanao-chart");
}