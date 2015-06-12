function onChange2nd( obj ){
	if( jQuery(obj).val() == 2010){
		rChartData[0] = chartData[0];
		rChart2Data[0] = chartData2[0];
		rChart8Data[0] = chartData8[0];
		rChart3Data[0] = chartData3[0];
		rChart4Data[0] = chartData4[0];
		rChart5Data[0] = chartData5[0];
	}else if( jQuery(obj).val() == 2011){
		rChartData[0] = chartData[1];	
		rChart2Data[0] = chartData2[1];		
		rChart8Data[0] = chartData8[1];
		rChart3Data[0] = chartData3[1];
		rChart4Data[0] = chartData4[1];
		rChart5Data[0] = chartData5[1];
	}else if( jQuery(obj).val() == 2012){
		rChartData[0] = chartData[2];
		rChart2Data[0] = chartData2[2];
		rChart8Data[0] = chartData8[2];
		rChart3Data[0] = chartData3[2];
		rChart4Data[0] = chartData4[2];
		rChart5Data[0] = chartData5[2];
	}else if( jQuery(obj).val() == 2013){
		rChartData[0] = chartData[3];	
		rChart2Data[0] = chartData2[3];		
		rChart8Data[0] = chartData8[3];
		rChart3Data[0] = chartData3[3];
		rChart4Data[0] = chartData4[3];
		rChart5Data[0] = chartData5[3];
	}else if( jQuery(obj).val() == 2014){
		rChartData[0] = chartData[4];				
		rChart2Data[0] = chartData2[4];
		rChart8Data[0] = chartData8[4];
		rChart3Data[0] = chartData3[4];
		rChart4Data[0] = chartData4[4];
		rChart5Data[0] = chartData5[4];
	}
	
	drawChart();
	drawChart2();
	drawChart8();
	drawChart3();
	drawChart4();
	drawChart5();
}

function onChange4th( obj ){

	if( jQuery(obj).val() == 2010){
		rLineChartData2 = lineChartData2[0];
	}else if( jQuery(obj).val() == 2011){
		rLineChartData2 = lineChartData2[1];
	}else if( jQuery(obj).val() == 2012){
		rLineChartData2 = lineChartData2[2];
	}else if( jQuery(obj).val() == 2013){
		rLineChartData2 = lineChartData2[3];
	}else if( jQuery(obj).val() == 2014){
		rLineChartData2 = lineChartData2[4];
	}
	drawLine();
}

function onChange5nd( obj ){

	if( jQuery(obj).val() == 2010){
		rChartData13 = chartData13[0];
		rChartData15 = chartData15[0];
		rChartData14 = chartData14[0];
		rChartData17 = chartData17[0];
		rChartData44 = chartData44[0];
		rChartData16 = chartData16[0];
	}else if( jQuery(obj).val() == 2011){
		rChartData13 = chartData13[1];
		rChartData15 = chartData15[1];
		rChartData14 = chartData14[1];
		rChartData17 = chartData17[1];
		rChartData44 = chartData44[1];
		rChartData16 = chartData16[1];
	}else if( jQuery(obj).val() == 2012){
		rChartData13 = chartData13[2];
		rChartData15 = chartData15[2];
		rChartData14 = chartData14[2];
		rChartData17 = chartData17[2];
		rChartData44 = chartData44[2];
		rChartData16 = chartData16[2];
	}else if( jQuery(obj).val() == 2013){
		rChartData13 = chartData13[3];
		rChartData15 = chartData15[3];
		rChartData14 = chartData14[3];
		rChartData17 = chartData17[3];
		rChartData44 = chartData44[3];
		rChartData16 = chartData16[3];
	}else if( jQuery(obj).val() == 2014){
		rChartData13 = chartData13[4];
		rChartData15 = chartData15[4];
		rChartData14 = chartData14[4];
		rChartData17 = chartData17[4];
		rChartData44 = chartData44[4];
		rChartData16 = chartData16[4];
	}
	drawChart13();
	drawChart15();
	drawChart14();
	drawChart17();
	drawChart44();
	drawChart16();
}