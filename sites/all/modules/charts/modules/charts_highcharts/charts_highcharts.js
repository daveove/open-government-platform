/**
 * @file
 * JavaScript integration between Highcharts and Drupal.
 */
(function ($) {

Drupal.behaviors.chartsHighcharts = {};
Drupal.behaviors.chartsHighcharts.attach = function(context, settings) {
  $('.charts-highchart').once('charts-highchart', function() {
    if ($(this).attr('data-chart')) {
      var config = $.parseJSON($(this).attr('data-chart'));
      if (config.chart.type=='column') {
            var labels = config.xAxis[0].labels;
            labels.style.fontFamily = 'Roboto';
            labels.style.fontSize = '12px';
            labels.y = 18;
            var tooltip = config.tooltip;
            tooltip.formatter = function() { 
                    var y = this.point.y,
                        key = this.point.hasOwnProperty('dept') ? this.point.dept : this.point.category,
                        color = this.series.color,
                        name = this.series.name;
                    if ((y%1)!=0) {
                        y = y.toFixed(2);
                    }
                    return  "<span style='font-size: 10px'>"+key+"</span><br/>"+
                            "<span style='color:"+color+"'>"+name+"</span>: <b>"+y+"</b><br/>";
                };
      }
      else if (config.chart.type=='pie') {
          var tooltip = config.tooltip;
          tooltip.pointFormat = "<b>{point.percentage:.1f}%</b><br/>";
      }
      else if (config.chart.type=='line') {
          var tooltip = config.tooltip;
          tooltip.formatter = function() { 
                var y = this.point.y,
                    key = this.point.hasOwnProperty('customCategory') ? this.point.customCategory : this.point.category,
                    color = this.series.color,
                    name = this.series.name;
                if ((y%1)!=0) {
                    y = y.toFixed(2);
                }
                return  "<span style='font-size: 10px'>"+key+"</span><br/>"+
                        "<span style='color:"+color+"'>"+name+"</span>: <b>"+y+"</b><br/>";
            };
      }
      $(this).highcharts(config);
    }
  });
};

})(jQuery);
