// JavaScript Document

var chart5;

var chartData5 = [
    {
        "year": 2010,
        "Debt Burden": 276212,
    },
    {
        "year": 2011,
        "Debt Burden": 357090,
    },
    {
        "year": 2012,
        "Debt Burden": 333107,
    },
    {
        "year": 2013,
        "Debt Burden": 333902,
    },
    {
        "year": 2014,
        "Debt Burden": 352652,
    }	
	
];
var rChart5Data = [];
AmCharts.ready(function () {
	rChart5Data[0] = chartData5[0];
	drawChart5();
});
function drawChart5(){
    // SERIALL CHART
    chart5 = new AmCharts.AmSerialChart();
    chart5.dataProvider = rChart5Data;
    chart5.categoryField = "year";
   // chart.plotAreaBorderAlpha = 0.2;
    chart5.rotate = true;
	chart5.marginTop = 100;

    
    // AXES
    // Category
    var categoryAxis = chart5.categoryAxis;
    categoryAxis.gridAlpha = 0.1;
    categoryAxis.axisAlpha = 0;
    categoryAxis.gridPosition = "start";
	categoryAxis.labelsEnabled = false;
	categoryAxis.gridAlpha = 0;
    
    // value                      
    var valueAxis = new AmCharts.ValueAxis();
    valueAxis.stackType = "100%";
    valueAxis.gridAlpha = 0.1;
    valueAxis.axisAlpha = 0;
	valueAxis.labelsEnabled = false;
	valueAxis.gridAlpha = 0;
    chart5.addValueAxis(valueAxis);
    
    // GRAPHS
    // firstgraph 
    var graph = new AmCharts.AmGraph();
    graph.title = "Debt Burden";
    graph.labelText = "DEBT BURDEN";
    graph.valueField = "Debt Burden";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#81b09b";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 12;
    chart5.addGraph(graph);
    
	
    
    // WRITE
    chart5.write("sector-chart-debt");
}

// Make chart 2D/3D
function setDepth() {
    if (document.getElementById("rb1").checked) {
        chart5.depth3D = 0;
        chart5.angle = 0;
    } else {
        chart5.depth3D = 20;
        chart5.angle = 30;
    }
    chart5.validateNow();
}