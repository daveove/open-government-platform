// JavaScript Document

// since v3, chart can accept data in JSON format
// if your category axis parses dates, you should only
// set date format of your data (dataDateFormat property of AmSerialChart)            
var lineChartData = [
    {
        "date": "2010",
        "value": 1540600,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/y2y-bullet-1.gif"
    },
    {
        "date": "2011",
        "value": 1645000,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/y2y-bullet-2.gif"
    },
    {
        "date": "2012",
        "value": 1816000,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/y2y-bullet-3.gif"
    },
    {
        "date": "2013",
        "value": 2005900,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/y2y-bullet-4.gif"
    }
];

AmCharts.ready(function () {
    var chart = new AmCharts.AmSerialChart();
    chart.dataProvider = lineChartData;
    chart.pathToImages = "http://www.amcharts.com/lib/3/images/";
    chart.categoryField = "date";
    chart.dataDateFormat = "YYYY";
    
    // sometimes we need to set margins manually
    // autoMargins should be set to false in order chart to use custom margin values
    chart.autoMargins = false;
    chart.marginRight = 50;
    chart.marginLeft = 50;
    chart.marginBottom = 50;
    chart.marginTop = 50;
	
	chart.sequencedAnimation = true;
	chart.startEffect = "elastic";
	chart.innerRadius = "30%";

	chart.startDuration = 2;
	chart.labelRadius = 15;
	
	// the following two lines makes the chart 3D
	chart.depth3D = 10;
	chart.angle = 15;
    
    // AXES
    // category                
    var categoryAxis = chart.categoryAxis;
    categoryAxis.minPeriod = "YYYY"; // our data is daily, so we set minPeriod to DD
    categoryAxis.inside = true;
    categoryAxis.gridAlpha = 0;
    categoryAxis.tickLength = 0;
    categoryAxis.axisAlpha = 0;
	categoryAxis.labelsEnabled = false;
    
    // value
    var valueAxis = new AmCharts.ValueAxis();
    valueAxis.dashLength = 4;
    valueAxis.axisAlpha = 0;
    valueAxis.gridAlpha = 0;
	valueAxis.labelsEnabled = false;
    chart.addValueAxis(valueAxis);
    
    // GRAPH
    var graph = new AmCharts.AmGraph();
    graph.type = "line";
    graph.valueField = "value";
    graph.lineColor = "transparent";
    graph.bulletSize = 115; // bullet image should be a rectangle (width = height)

    graph.customBulletField = "bullet"; // this will make the graph to display custom bullet (red star)
    chart.addGraph(graph);
    
     var chartCursor = new AmCharts.ChartCursor();
    chart.addChartCursor(chartCursor);
    
	var balloon = chart.balloon;
	chart.balloon.enabled = false   ;
       
    // WRITE
    chart.write("yeartoyear-chart");
});
