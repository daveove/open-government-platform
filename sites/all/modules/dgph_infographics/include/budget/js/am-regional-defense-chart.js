// JavaScript Document

var chart17;
var rChartData17;
var chartData17 = [
[
    {
        "label": "Domestic Security",
        "litres": 73354
    }
],[
    {
        "label": "Domestic Security",
        "litres": 101449
    }
],[
    {
        "label": "Domestic Security",
        "litres": 87181
    }
],[
    {
        "label": "Domestic Security",
        "litres": 89539
    }
],[
    {
        "label": "Domestic Security",
        "litres": 92850
    }
]
];
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
    chart17.color = "#ffffff";chart17.labelRadius=-80;
    
	
    // WRITE
    chart17.write("regional-defense-chart");
}

AmCharts.ready(function () {
	rChartData17 = chartData17[0];
	drawChart17();	
});