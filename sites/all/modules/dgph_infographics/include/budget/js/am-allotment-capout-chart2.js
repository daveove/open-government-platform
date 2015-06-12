var chart;

var allotmentData= [
    {
        "year": 'Personnel Services',
        "2010": 493142064,
        "2011": 47014932,
        "2012": 53384339, 
        "2013": 47044283, 
        "2010a": '493,142,064',
        "2011a":'540,156,996',
        "2012a":'593,541,335',
        "2013a":'640,585,618',
        "color":'#fa9a97'
    },
    
{
        "year": 'Maintenance and other Operating Expenses',
        "2010": 823034369,
        "2011": 74089096,  
        "2012": 47840712, 
        "2013": 94705227, 
        "2010a": '823,034,369',
        "2011a":'897,123,465',
        "2012a":'944,964,177',
        "2013a":'1,039,669,404',
        "color":'#fecdaa'
    },
    
    {
        "year": 'Capital Outlays',
        "2010": 207719539,
        "2011": 16704028, 
        "2012": 69774949, 
        "2013": 48150490, 
        "2010a":'224,423,567',
        "2011a":'(Decrease) 207,719,539',
        "2012a":'277,494,488',
        "2013a":'325,644,978',
        "color":'#c8c8a6'
    }

];

AmCharts.ready(function () {
    // SERIALL CHART
    chart = new AmCharts.AmSerialChart();
    chart.dataProvider = allotmentData;
    chart.categoryField = "year";
    chart.plotAreaBorderAlpha = 0;
    chart.rotate = true;
    
    // AXES
    // Category
    var categoryAxis = chart.categoryAxis;
    categoryAxis.gridAlpha = 0.1;
    categoryAxis.axisAlpha = 0;
      categoryAxis.gridAlpha = 0;
    categoryAxis.axisAlpha = 0;
    categoryAxis.gridPosition = "start";
	categoryAxis.labelsEnabled = false;
    categoryAxis.gridPosition = "start";
    
    // value                      
    var valueAxis = new AmCharts.ValueAxis();
    valueAxis.stackType = "regular";
   valueAxis.gridAlpha = 0;
    valueAxis.axisAlpha = 0;
	valueAxis.labelsEnabled = false;
    chart.addValueAxis(valueAxis);
    
    // GRAPHS
    // firstgraph 
    var graph = new AmCharts.AmGraph();
    graph.title = "2010";
    graph.labelText = "[[category]]";
    graph.fontSize =14;
    graph.valueField = "2010";
    graph.type = "column";
    graph.lineAlpha = 0;
    graph.colorField = "color";
    graph.fillAlphas = 1;
    graph.lineColor = "color";
    graph.balloonText = "<b><span style='color:[[color]]'>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[2010a]]</b></span>";
    chart.addGraph(graph);
    
    // second graph                              
    graph = new AmCharts.AmGraph();
    graph.title = "2011";
    graph.labelText = "";
    graph.valueField = "2011";
    graph.type = "column";
    graph.lineAlpha = 0;
  graph.colorField = "color";
    graph.fillAlphas = .85;
    graph.lineColor = "color";
    graph.balloonText = "<b><span style='color:[[color]]'>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[2011a]]</b></span>";
    chart.addGraph(graph);
    
    
    
    // third graph              
    graph = new AmCharts.AmGraph();
    graph.title = "2012";
    graph.labelText = "";
    graph.valueField = "2012";
    graph.type = "column";
    graph.lineAlpha = 0;
   graph.colorField = "color";
    graph.fillAlphas = .7;
    graph.lineColor = "color";
    graph.balloonText = "<b><span style='color:[[color]]'>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[2012a]]</b></span>";
    chart.addGraph(graph);
    
    // fourth graph 
    graph = new AmCharts.AmGraph();
    graph.title = "2013";
    graph.labelText = "";
    graph.valueField = "2013";
    graph.type = "column";
    graph.lineAlpha = 0;
   graph.colorField = "color";
    graph.fillAlphas = .55;
    graph.lineColor = "color";
    graph.balloonText = "<b><span style='color:[[color]]'>[[title]]</b></span><br><span style='font-size:14px'>[[category]]: <b>[[2013a]]</b></span>";
    chart.addGraph(graph);
    
    // WRITE
    chart.write("capout-chart-2010");
});

// Make chart 2D/3D
function setDepth() {
    if (document.getElementById("rb1").checked) {
        chart.depth3D = 0;
        chart.angle = 0;
    } else {
        chart.depth3D = 20;
        chart.angle = 30;
    }
    chart.validateNow();
}