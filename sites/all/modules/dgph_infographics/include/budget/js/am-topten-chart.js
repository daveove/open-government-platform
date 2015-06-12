// JavaScript Document

// since v3, chart can accept data in JSON format
// if your category axis parses dates, you should only
// set date format of your data (dataDateFormat property of AmSerialChart)            
var rLineChartData2;
var lineChartData2 = [
[
    {
        "rank": "1",
        "value": 161405905,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-1-2010.gif"
    },
    {
        "rank": "2",
        "value": 126930988,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-2-2010.gif"
    },
    {
        "rank": "3",
        "value": 65601956,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-3-2010.gif"
    },
    {
        "rank": "4",
        "value": 57670254,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-4-2010.gif"
    },
    {
        "rank": "5",
        "value": 39241610,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-5-2010.gif"
    },
	{
        "rank": "6",
        "value": 28686083,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-6-2010.gif"
	},
	{
        "rank": "7",
        "value": 20767776,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-7-2010.gif"
    },
	{
        "rank": "8",
        "value": 16577036,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-8-2010.gif"
    },
	{
        "rank": "9",
        "value": 15314440,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-9-2010.gif"
    },
	{
        "rank": "10",
        "value": 12190629,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-10-2010.gif"
    }
],[
    {
        "rank": "1",
        "value": 192312856,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-1-2011.gif"
    },
    {
        "rank": "2",
        "value": 100826083,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-2-2011.gif"
    },
    {
        "rank": "3",
        "value": 86853516,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-3-2011.gif"
    },
    {
        "rank": "4",
        "value": 104504921,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-4-2011.gif"
    },
    {
        "rank": "5",
        "value": 34757973,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-5-2011.gif"
    },
	{
        "rank": "6",
        "value": 32427444,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-6-2011.gif"
	},
	{
        "rank": "7",
        "value": 16365513,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-7-2011.gif"
    },
	{
        "rank": "8",
        "value": 31185088,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-8-2011.gif"
    },
	{
        "rank": "9",
        "value": 34282349,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-9-2011.gif"
    },
	{
        "rank": "10",
        "value": 11123532,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-10-2011.gif"
    }
],[
    {
        "rank": "1",
        "value": 201821472,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-1-2012.gif"
    },
    {
        "rank": "2",
        "value": 109833405,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-2-2012.gif"
    },
    {
        "rank": "3",
        "value": 75178407,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-3-2012.gif"
    },
    {
        "rank": "4",
        "value": 72577194,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-4-2012.gif"
    },
    {
        "rank": "5",
        "value": 52932023,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-5-2012.gif"
    },
	{
        "rank": "6",
        "value": 42769378,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-6-2012.gif"
	},
	{
        "rank": "7",
        "value": 17903222,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-7-2012.gif"
    },
	{
        "rank": "8",
        "value": 32788499,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-8-2012.gif"
    },
	{
        "rank": "9",
        "value": 48722175,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-9-2012.gif"
    },
	{
        "rank": "10",
        "value": 16976160,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-10-2012.gif"
    }
],[
    {
        "rank": "1",
        "value": 232595221,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-1-2013.gif"
    },
    {
        "rank": "2",
        "value": 155517533,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-2-2013.gif"
    },
    {
        "rank": "3",
        "value": 91164442,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-3-2013.gif"
    },
    {
        "rank": "4",
        "value": 80420311,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-4-2013.gif"
    },
    {
        "rank": "5",
        "value": 64474099,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-5-2013.gif"
    },
	{
        "rank": "6",
        "value": 51074586,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-6-2013.gif"
	},
	{
        "rank": "7",
        "value": 21038824,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-7-2013.gif"
    },
	{
        "rank": "8",
        "value": 34185121,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-8-2013.gif"
    },
	{
        "rank": "9",
        "value": 56333858,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-9-2013.gif"
    },
	{
        "rank": "10",
        "value": 23135850,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-10-2013.gif"
    }
],[
    {
        "rank": "1",
        "value": 281751791,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-1-2014.gif"
    },
    {
        "rank": "2",
        "value": 200265553,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-2-2014.gif"
    },
    {
        "rank": "3",
        "value": 99595064,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-3-2014.gif"
    },
    {
        "rank": "4",
        "value": 82195121,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-4-2014.gif"
    },
    {
        "rank": "5",
        "value": 69473867,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-5-2014.gif"
    },
	{
        "rank": "6",
        "value": 80807312,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-6-2014.gif"
	},
	{
        "rank": "7",
        "value": 20002768,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-7-2014.gif"
    },
	{
        "rank": "8",
        "value": 45101306,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-8-2014.gif"
    },
	{
        "rank": "9",
        "value": 78876694,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-9-2014.gif"
    },
	{
        "rank": "10",
        "value": 23359611,
		"bullet": "/sites/all/modules/dgph_infographics/include/budget/images/tt-bullet-10-2014.gif"
    }
]
];

function drawLine(){
    var chart = new AmCharts.AmSerialChart();
    chart.dataProvider = rLineChartData2;
    chart.pathToImages = "http://www.amcharts.com/lib/3/images/";
    chart.categoryField = "rank";
   // chart.dataDateFormat = "YYYY-MM-DD";
    
    // sometimes we need to set margins manually
    // autoMargins should be set to false in order chart to use custom margin values
    chart.autoMargins = false;
    chart.marginRight = 0;
    chart.marginLeft = 0;
    chart.marginBottom = 50;
    chart.marginTop = 50;
    
    // AXES
    // category                
    var categoryAxis = chart.categoryAxis;
   // categoryAxis.parseDates = true; // as our data is date-based, we set parseDates to true
    categoryAxis.minPeriod = "DD"; // our data is daily, so we set minPeriod to DD
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
    graph.bulletSize = 100; // bullet image should be a rectangle (width = height)
    graph.customBulletField = "bullet"; // this will make the graph to display custom bullet (red star)
    chart.addGraph(graph);
    
   var chartCursor = new AmCharts.ChartCursor();
    chart.addChartCursor(chartCursor);
    
	var balloon = chart.balloon;
	chart.balloon.enabled = false   ;
       
    // WRITE
    chart.write("topten-chart");
}

AmCharts.ready(function () {
	rLineChartData2 = lineChartData2[3];
	drawLine();
});
