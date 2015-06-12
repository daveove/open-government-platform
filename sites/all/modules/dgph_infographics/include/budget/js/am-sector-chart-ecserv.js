// JavaScript Document

var chart2;

var chartData2 = [
    {
        "year": 2010,
        "Agriculture Agrarian Reform Natural Resources": 89219,
		"Natural Resources and Environment": 14838,
        "Trade and Industry": 5650,
		"Tourism": 2317,
        "Power and Energy": 5127,
        "Water Resources Development and Flood Control": 18545,
        "Communications, Roads and Other Transport": 151524,
		"Other Economic Services": 18682,
		"Subsidy to Local Government Units": 93031
    },
    {
        "year": 2011,
        "Agriculture Agrarian Reform Natural Resources": 65973,
		"Natural Resources and Environment": 13088,
        "Trade and Industry": 4514,
		"Tourism": 1833,
        "Power and Energy": 1784,
        "Water Resources Development and Flood Control": 14577,
        "Communications, Roads and Other Transport": 145301,
		"Other Economic Services": 14426,
		"Subsidy to Local Government Units": 100430
    },
    {
        "year": 2012,
        "Agriculture Agrarian Reform Natural Resources": 99445,
		"Natural Resources and Environment": 19786,
        "Trade and Industry": 6066,
		"Tourism": 2260,
        "Power and Energy": 11827,
        "Water Resources Development and Flood Control": 17431,
        "Communications, Roads and Other Transport": 167368,
		"Other Economic Services": 19149,
		"Subsidy to Local Government Units": 95658
    },
    {
        "year": 2013,
        "Agriculture Agrarian Reform Natural Resources": 111140,
		"Natural Resources and Environment": 25529,
        "Trade and Industry": 7187,
		"Tourism": 3464,
        "Power and Energy": 11402,
        "Water Resources Development and Flood Control": 22347,
        "Communications, Roads and Other Transport": 203774,
		"Other Economic Services": 18544,
		"Subsidy to Local Government Units": 105806
    },
    {
        "year": 2014,
        "Agriculture Agrarian Reform Natural Resources": 116575,
		"Natural Resources and Environment": 25924,
        "Trade and Industry": 7741,
		"Tourism": 3733,
        "Power and Energy": 14258,
        "Water Resources Development and Flood Control": 28589,
        "Communications, Roads and Other Transport": 253128,
		"Other Economic Services": 20730,
		"Subsidy to Local Government Units": 119541
    }
];
var rChart2Data = [];
AmCharts.ready(function () {
	rChart2Data[0] = chartData2[0];
	drawChart2();
});
function drawChart2( ){
    // SERIALL CHART
    chart2 = new AmCharts.AmSerialChart();
    chart2.dataProvider = rChart2Data;
    chart2.categoryField = "year";
   // chart.plotAreaBorderAlpha = 0.2;
    chart2.rotate = true;
	chart2.marginTop = 100;

    
    // AXES
    // Category
    var categoryAxis = chart2.categoryAxis;
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
    chart2.addValueAxis(valueAxis);
    
    // GRAPHS
    // firstgraph 
    var graph = new AmCharts.AmGraph();
    graph.title = "Agriculture, Agrarian Reform, and Natural Resources";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Agriculture Agrarian Reform Natural Resources";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#eb7878";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart2.addGraph(graph);
    
    // second graph                              
    graph = new AmCharts.AmGraph();
    graph.title = "Trade and Industry";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Trade and Industry";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#ed8585";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart2.addGraph(graph);
    
    // third graph              
    graph = new AmCharts.AmGraph();
    graph.title = "Tourism";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Tourism";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#ef9393";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart2.addGraph(graph);
    
    // fourth graph 
    graph = new AmCharts.AmGraph();
    graph.title = "Power and Energy";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Power and Energy";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#f1a0a0";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart2.addGraph(graph);
    
    // Fifth graph  
    graph = new AmCharts.AmGraph();
    graph.title = "Water Resources Development and Flood Control";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Water Resources Development and Flood Control";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#f3aeae";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart2.addGraph(graph);
    
	// sixth graph  
    graph = new AmCharts.AmGraph();
    graph.title = "Communications, Roads and Other Transport";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Communications, Roads and Other Transport";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#f5bbbb";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart2.addGraph(graph);
	
	// seventh graph  
    graph = new AmCharts.AmGraph();
    graph.title = "Other Economic Services";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Other Economic Services";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#f5bbbb";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart2.addGraph(graph);
	
	// eighth graph  
    graph = new AmCharts.AmGraph();
    graph.title = "Subsidy to Local Government Units";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Subsidy to Local Government Units";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#f7c9c9";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart2.addGraph(graph);
	
    
    // WRITE
    chart2.write("sector-chart-ecserv");
}

// Make chart 2D/3D
function setDepth() {
    if (document.getElementById("rb1").checked) {
        chart2.depth3D = 0;
        chart2.angle = 0;
    } else {
        chart2.depth3D = 20;
        chart2.angle = 30;
    }
    chart2.validateNow();
}