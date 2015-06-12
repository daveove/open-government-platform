// JavaScript Document

var chart3;

var chartData3 = [
    {
        "year": 2010,
        "Domestic Security": 73354,
    },
    {
        "year": 2011,
        "Domestic Security": 101449,
    },
    {
        "year": 2012,
        "Domestic Security": 87181,
    },
    {
        "year": 2013,
        "Domestic Security": 89539,
    },
    {
        "year": 2014,
        "Domestic Security": 92850,
    }	
];
var rChart3Data = [];
AmCharts.ready(function () {
	rChart3Data[0] = chartData3[0];
	drawChart3();
});
function drawChart3(){
    // SERIALL CHART
    chart3 = new AmCharts.AmSerialChart();
    chart3.dataProvider = rChart3Data;
    chart3.categoryField = "year";
   // chart.plotAreaBorderAlpha = 0.2;
    chart3.rotate = true;
	chart3.marginTop = 100;

    
    // AXES
    // Category
    var categoryAxis = chart3.categoryAxis;
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
    chart3.addValueAxis(valueAxis);
    
    // GRAPHS
    // firstgraph 
    var graph = new AmCharts.AmGraph();
    graph.title = "Domestic Security";
    graph.labelText = "DOMESTIC SECURITY";
    graph.valueField = "Domestic Security";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#fbceab";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 12;
    chart3.addGraph(graph);
    
	
    
    // WRITE
    chart3.write("sector-chart-domsec");
}

// Make chart 2D/3D
function setDepth() {
    if (document.getElementById("rb1").checked) {
        chart3.depth3D = 0;
        chart3.angle = 0;
    } else {
        chart3.depth3D = 20;
        chart3.angle = 30;
    }
    chart3.validateNow();
}