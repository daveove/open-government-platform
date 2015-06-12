// JavaScript Document

var chart14;

var rChartData14;
var chartData14 = [
[	// 2013
    {
        "label": "R1",	
        "litres": 49536146
    },
    {
        "label": "CAR",
        "litres": 31379449
    },
    {
        "label": "R2",
        "litres": 44604291
    },
    {
        "label": "R3",
        "litres": 87263957
    },
    {
        "label": "R4",
        "litres": 127638263
    },
	{
        "label": "R5",
        "litres": 62156111
    }
],[	//2012
    {
        "label": "R1",
        "litres": 42827518
    },
    {
        "label": "CAR",
        "litres": 27737915
    },
    {
        "label": "R2",
        "litres": 38070610
    },
    {
        "label": "R3",
        "litres": 73637544
    },
    {
        "label": "R4",
        "litres": 116649167
    },
	{
        "label": "R5",
        "litres": 54012629
    }
],[	//2011
    {
        "label": "R1",
        "litres": 37696855
    },
    {
        "label": "CAR",
        "litres": 19697439
    },
    {
        "label": "R2",
        "litres": 29007087
    },
    {
        "label": "R3",
        "litres": 58535586
    },
    {
        "label": "R4",
        "litres": 82472444
    },
	{
        "label": "R5",
        "litres": 40911613
    }
],[	//2010
    {
        "label": "R1",
        "litres": 33294449
    },
    {
        "label": "CAR",
        "litres": 16924455
    },
    {
        "label": "R2",
        "litres": 27394583
    },
    {
        "label": "R3",
        "litres": 53073183
    },
    {
        "label": "R4",
        "litres": 76008159
    },
	{
        "label": "R5",
        "litres": 35463379
    }
],[	//2009
    {
        "label": "R1",
        "litres": 30876249
    },
    {
        "label": "CAR",
        "litres": 21063614
    },
    {
        "label": "R2",
        "litres": 26000019
    },
    {
        "label": "R3",
        "litres": 51357710
    },
    {
        "label": "R4",
        "litres": 75156442
    },
	{
        "label": "R5",
        "litres": 35020355
    }
]
];

AmCharts.ready(function () {
	rChartData14 = chartData14[0];
	drawChart14();
});

function drawChart14(){
    // PIE CHART
    chart14 = new AmCharts.AmPieChart();
    chart14.dataProvider = rChartData14;
    chart14.titleField = "label";
    chart14.valueField = "litres";
    chart14.outlineColor = "#FFFFFF";
    chart14.outlineAlpha = 0.8;
    chart14.outlineThickness = 2;
    chart14.balloonText = "[[title]]<br><span style='font-size:14px'><b>[[value]]</b> ([[percents]]%)</span>";
	chart14.colors = [ "#ebaead", "#f7c9c9", "#f5d5d5", "#ea9593", "#f69b98", "#f5b8b8", "#f5c8d8" ];
         chart14.labelsEnabled=true;
    chart14.labelText="[[title]]";
    chart14.fontSize=16;
    chart14.color = "#ffffff";
	chart14.labelRadius=-80
    
	
    // WRITE
    chart14.write("regional-luzon-chart");
	
}