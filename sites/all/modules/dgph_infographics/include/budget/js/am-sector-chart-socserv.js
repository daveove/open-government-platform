// JavaScript Document

var chart8;

var chartData8 = [
    {
        "year": 2010,
        "Education, Culture, and Manpower Development": 240585,
        "Health": 40030,
		"Social Security, Welfare and Employment": 103570,
        "Land Distribution": 1279,
        "Housing and Community Development": 5466,
        "Other Social Services": 2236,
		"Subsidy to Local Government Units": 98347,
    },
    {
        "year": 2011,
        "Education, Culture, and Manpower Development": 271493,
        "Health": 38392,
		"Social Security, Welfare and Employment": 94105,
        "Land Distribution": 3966,
        "Housing and Community Development": 5737,
        "Other Social Services": 1583,
		"Subsidy to Local Government Units": 106169,
    },
    {
        "year": 2012,
        "Education, Culture, and Manpower Development": 299958,
        "Health": 50559,
		"Social Security, Welfare and Employment": 150368,
        "Land Distribution": 2500,
        "Housing and Community Development": 7086,
        "Other Social Services": 1795,
		"Subsidy to Local Government Units": 101125,
    },
    {
        "year": 2013,
        "Education, Culture, and Manpower Development": 330181,
        "Health": 57738,
		"Social Security, Welfare and Employment": 169464,
        "Land Distribution": 5000,
        "Housing and Community Development": 23334,
        "Other Social Services": 1871,
		"Subsidy to Local Government Units": 111852,
    },
    {
        "year": 2014,
        "Education, Culture, and Manpower Development": 389518,
        "Health": 88346,
		"Social Security, Welfare and Employment": 214923,
        "Land Distribution": 5000,
        "Housing and Community Development": 16662,
        "Other Social Services": 1985,
		"Subsidy to Local Government Units": 126372,
    }	
	
];

var rChart8Data = [];
AmCharts.ready(function () {
	rChart8Data[0] = chartData8[0];
	drawChart8();
});

function drawChart8( ){
    // SERIALL CHART
    chart8 = new AmCharts.AmSerialChart();
    chart8.dataProvider = rChart8Data;
    chart8.categoryField = "year";
   // chart.plotAreaBorderAlpha = 0.2;
    chart8.rotate = true;
	chart8.marginTop = 100;

    
    // AXES
    // Category
    var categoryAxis = chart8.categoryAxis;
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
    chart8.addValueAxis(valueAxis);
    
    // GRAPHS
    // firstgraph 
    var graph = new AmCharts.AmGraph();
    graph.title = "Education, Culture, and Manpower Development";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Education, Culture, and Manpower Development";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#eb7878";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart8.addGraph(graph);
	
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
    chart8.addGraph(graph);
	
    // third graph              
    graph = new AmCharts.AmGraph();
    graph.title = "Health";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Health";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#ef9393";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart8.addGraph(graph);
    	
    // fourth graph 
    graph = new AmCharts.AmGraph();
    graph.title = "Social Security, Welfare and Employment";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Social Security, Welfare and Employment";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#f1a0a0";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart8.addGraph(graph);
	
    // Fifth graph  
    graph = new AmCharts.AmGraph();
    graph.title = "Land Distribution";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Land Distribution";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#f3aeae";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart8.addGraph(graph);
	
	// sixth graph  
    graph = new AmCharts.AmGraph();
    graph.title = "Housing and Community Development";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Housing and Community Development";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#f5bbbb";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart8.addGraph(graph);
		
	// seventh graph  
    graph = new AmCharts.AmGraph();
    graph.title = "Other Social Services";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Other Social Services";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#f5bbbb";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart8.addGraph(graph);
	
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
    chart8.addGraph(graph);
	
	
    
    
    // LEGEND
    //var legend = new AmCharts.AmLegend();
    //legend.position = "right";
    //legend.borderAlpha = 0.3;
    //legend.horizontalGap = 10;
    //legend.switchType = "v";
    //chart.addLegend(legend);
    
    // WRITE
    chart8.write("sector-chart-socserv");
}

// Make chart 2D/3D
function setDepth() {
    if (document.getElementById("rb1").checked) {
        chart8.depth3D = 0;
        chart8.angle = 0;
    } else {
        chart8.depth3D = 20;
        chart8.angle = 30;
    }
    chart8.validateNow();
}