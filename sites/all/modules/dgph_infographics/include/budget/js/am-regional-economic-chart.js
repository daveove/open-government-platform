// JavaScript Document

var chart15;

var rChartData15;
var chartData15 = [
[
    {
        "label": "A",
        "litres":  89219 
    },
    {
        "label": "B",
        "litres": 14838
    },
    {
        "label": "C",
        "litres": 5650
    },
    {
        "label": "D",
        "litres": 2317
    },
    {
        "label": "E",
        "litres": 5127
    },
    {
        "label": "F",
        "litres": 18545
    },
    {
        "label": "G",
        "litres": 151524
    },
    {
        "label": "H",
        "litres": 18682
    },
    {
        "label": "I",
        "litres": 93031
    }
],[
    {
        "label": "A",
        "litres":  65973 
    },
    {
        "label": "B",
        "litres": 13088
    },
    {
        "label": "C",
        "litres": 4514
    },
    {
        "label": "D",
        "litres": 1833
    },
    {
        "label": "E",
        "litres": 1784
    },
    {
        "label": "F",
        "litres": 14577
    },
    {
        "label": "G",
        "litres": 145301
    },
    {
        "label": "H",
        "litres": 14426
    },
    {
        "label": "I",
        "litres": 100430
    }
],[
    {
        "label": "A",
        "litres":  99445 
    },
    {
        "label": "B",
        "litres": 19786
    },
    {
        "label": "C",
        "litres": 6066
    },
    {
        "label": "D",
        "litres": 2260
    },
    {
        "label": "E",
        "litres": 11827
    },
    {
        "label": "F",
        "litres": 17431
    },
    {
        "label": "G",
        "litres": 167368
    },
    {
        "label": "H",
        "litres": 19149
    },
    {
        "label": "I",
        "litres": 95658
    }
],[
    {
        "label": "A",
        "litres":  111140 
    },
    {
        "label": "B",
        "litres": 25529
    },
    {
        "label": "C",
        "litres": 7187
    },
    {
        "label": "D",
        "litres": 3464
    },
    {
        "label": "E",
        "litres": 11402
    },
    {
        "label": "F",
        "litres": 22347
    },
    {
        "label": "G",
        "litres": 203774
    },
    {
        "label": "H",
        "litres": 18544
    },
    {
        "label": "I",
        "litres": 105806
    }
],[
    {
        "label": "A",
        "litres":  116575 
    },
    {
        "label": "B",
        "litres": 25924
    },
    {
        "label": "C",
        "litres": 7741
    },
    {
        "label": "D",
        "litres": 3733
    },
    {
        "label": "E",
        "litres": 14258
    },
    {
        "label": "F",
        "litres": 28589
    },
    {
        "label": "G",
        "litres": 253128
    },
    {
        "label": "H",
        "litres": 20730
    },
    {
        "label": "I",
        "litres": 119541
    }
]
];

AmCharts.ready(function () {
	rChartData15 = chartData15[0];
	drawChart15();
});

function drawChart15(){
    // PIE CHART
    chart15 = new AmCharts.AmPieChart();
    chart15.dataProvider = rChartData15;
    chart15.titleField = "label";
    chart15.valueField = "litres";
    chart15.outlineColor = "#FFFFFF";
    chart15.outlineAlpha = 0.8;
    chart15.outlineThickness = 2;
    chart15.balloonText = "[[title]]<br><span style='font-size:14px'><b>[[value]]</b> ([[percents]]%)</span>";
	chart15.colors = [ "#ec7878", "#d56c6c", "#ec6868", "#d55c5c", "#ec5858", "#d54c4c", "#ec4848", "#d53c3c", "#ec3838" ];
    
	chart15.labelsEnabled=true;
    chart15.labelText="[[title]]";
    chart15.fontSize=16;
    chart15.color = "#ffffff";chart15.labelRadius=-80;
	
    // WRITE
    chart15.write("regional-economic-chart");
}