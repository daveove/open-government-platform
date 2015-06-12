// JavaScript Document

var chart4;

var chartData4 = [
    {
        "year": 2010,
        "General Administration": 93760,
		"Public Order and Safety": 95100,
		"Other General Public Services": 22303,
		"Subsidy to Local Government Units": 74425
    },
    {
        "year": 2011,
        "General Administration": 79522,
		"Public Order and Safety": 118398,
		"Other General Public Services": 9826,
		"Subsidy to Local Government Units": 80344
    },
    {
        "year": 2012,
        "General Administration": 112039,
		"Public Order and Safety": 115897,
		"Other General Public Services": 15868,
		"Subsidy to Local Government Units": 76527
    },
    {
        "year": 2013,
        "General Administration": 124458,
		"Public Order and Safety": 124279,
		"Other General Public Services": 13944,
		"Subsidy to Local Government Units": 84645
    },
    {
        "year": 2014,
        "General Administration": 117057,
		"Public Order and Safety": 134526,
		"Other General Public Services": 17307,
		"Subsidy to Local Government Units": 95633
    }	
];
var rChart4Data = [];
AmCharts.ready(function () {
	rChart4Data[0] = chartData4[0];
	drawChart4();
});
function drawChart4(){
    // SERIALL CHART
    chart4 = new AmCharts.AmSerialChart();
    chart4.dataProvider = rChart4Data;
    chart4.categoryField = "year";
   // chart.plotAreaBorderAlpha = 0.2;
    chart4.rotate = true;
	chart4.marginTop = 100;

    
    // AXES
    // Category
    var categoryAxis = chart4.categoryAxis;
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
    chart4.addValueAxis(valueAxis);
    
    // GRAPHS
    // firstgraph 
    var graph = new AmCharts.AmGraph();
    graph.title = "General Administration";
    graph.labelText = "[[percents]]%";
    graph.valueField = "General Administration";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#c7c8a7";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart4.addGraph(graph);
	
	 // secondgraph 
    var graph = new AmCharts.AmGraph();
    graph.title = "Public Order and Safety";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Public Order and Safety";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#cccdb0";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart4.addGraph(graph);
	
	 // thirdgraph 
    var graph = new AmCharts.AmGraph();
    graph.title = "Other General Public Services";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Other General Public Services";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#d2d3b9";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart4.addGraph(graph);
    
	 // fourthgraph 
    var graph = new AmCharts.AmGraph();
    graph.title = "Subsidy to Local Government Units";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Subsidy to Local Government Units";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#d8d8c1";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart4.addGraph(graph);
	
	
   
    // WRITE
    chart4.write("sector-chart-genpubserv");
}

// Make chart 2D/3D
function setDepth() {
    if (document.getElementById("rb1").checked) {
        chart4.depth3D = 0;
        chart4.angle = 0;
    } else {
        chart4.depth3D = 20;
        chart4.angle = 30;
    }
    chart4.validateNow();
}