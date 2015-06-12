
// JavaScript Document

var chart44;

var rChartData44;
var chartData44 = [
[
    {
        "label": "Debt service interest payment",
        "litres": 276212
    }
],[
    {
        "label": "Debt service interest payment",
        "litres": 357090
    }
],[
    {
        "label": "Debt service interest payment",
        "litres": 333107
    }
],[
    {
        "label": "Debt service interest payment",
        "litres": 333902
    }
],[
    {
        "label": "Debt service interest payment",
        "litres": 352652
    }
]
];

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
    chart44.color = "#ffffff";chart44.labelRadius=-80
    
	
    // WRITE
    chart44.write("regional-debt-chart");
}
AmCharts.ready(function () {
	rChartData44 = chartData44[0];
	drawChart44();
});
