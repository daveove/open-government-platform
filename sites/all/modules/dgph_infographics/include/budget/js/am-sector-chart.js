// JavaScript Document

var chart;

var chartData = [
    {
        "year": 2010,
        "Economic Services": 398993,
        "Social Services": 491513,
        "Defense": 73354,
        "General Public Services": 285588,
        "Debt Burden": 276212
    },
    {
        "year": 2011,
        "Economic Services": 361926,
        "Social Services": 521445,
        "Defense": 101449,
        "General Public Services": 288090,
        "Debt Burden": 357090
    },
    {
        "year": 2012,
        "Economic Services": 438990,
        "Social Services": 613391,
        "Defense": 87181,
        "General Public Services": 320331,
        "Debt Burden": 333107
    },	
    {
        "year": 2013,
        "Economic Services": 509193,
        "Social Services": 699440,
        "Defense": 89539,
        "General Public Services": 347326,
        "Debt Burden": 333902
    },
    {
        "year": 2014,
        "Economic Services": 590219,
        "Social Services": 842806,
        "Defense": 92850,
        "General Public Services": 364523,
        "Debt Burden": 352652
    }
];

var rChartData = [];
function handleClick(event)
{
	jQuery('#sector-chart-ecserv, #sector-chart-socserv, #sector-chart-domsec, #sector-chart-genpubserv, #sector-chart-debt').css({
		'opacity': 0,
		'position': 'absolute'
	});
    jQuery('#' + event.graph.id).css({
		'opacity': 1,
		'position': 'relative'
	});
}

AmCharts.ready(function () {
	rChartData[0] = chartData[0];
	drawChart();
});

function drawChart( ){
	chart = new AmCharts.AmSerialChart();
	
 	// add click listener
    chart.addListener("clickGraphItem", handleClick);
    // SERIALL CHART
    chart.dataProvider = rChartData;
    chart.categoryField = "year";
    chart.rotate = true;
	chart.marginTop = 100;
	chart.startDuration = 1;
	chart.startEffect = "elastic";
	
    // AXES
    // Category
    var categoryAxis = chart.categoryAxis;
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
    chart.addValueAxis(valueAxis);
    
    // GRAPHS
    // firstgraph 
    var graph = new AmCharts.AmGraph();
    graph.title = "Economic Services";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Economic Services";
	graph.id = "sector-chart-ecserv";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#eb7878";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart.addGraph(graph);
    
    // second graph                              
    graph = new AmCharts.AmGraph();
    graph.title = "Social Services";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Social Services";
	graph.id = "sector-chart-socserv";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#f69b98";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart.addGraph(graph);
    
    // third graph              
    graph = new AmCharts.AmGraph();
    graph.title = "Defense";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Defense";
	graph.id = "sector-chart-domsec";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#fbceab";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart.addGraph(graph);
    
    // fourth graph 
    graph = new AmCharts.AmGraph();
    graph.title = "General Public Services";
    graph.labelText = "[[percents]]%";
    graph.valueField = "General Public Services";
	graph.id = "sector-chart-genpubserv";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#c7c8a7";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart.addGraph(graph);
    
    // Fifth graph  
    graph = new AmCharts.AmGraph();
    graph.title = "Debt Burden";
    graph.labelText = "[[percents]]%";
    graph.valueField = "Debt Burden";
	graph.id = "sector-chart-debt";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.fillAlphas = 1;
    graph.lineColor = "#81b09b";
    graph.balloonText = "<b><span>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[value]]</b></span>";
	graph.color = "#ffffff";
	graph.fontSize = 18;
    chart.addGraph(graph);
    
    // WRITE
    chart.write("sector-chart");
}