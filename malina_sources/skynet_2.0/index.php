<!DOCTYPE HTML>
<?
  include "htdocs/config.php";
  include "htdocs/conn.php";
  $tmpdata1 = "[";
  $xxx=mysql_query("select `time`,`temperature` from `thermo_doma` where `sensor`='venku'");
  while ($zaznam=MySQL_Fetch_Array($xxx)):
    $temp1 = $zaznam["temperature"];   
    $time = (7200+$zaznam["time"])*1000;
    $tmpdata1 = $tmpdata1."[$time,$temp1],";
  endwhile;
  $tmpdata1 = rtrim($tmpdata1, ",");
  $tmpdata1 = $tmpdata1."]";
  
  $tmpdata2 = "[";
  $xxx=mysql_query("select `time`,`temperature` from `thermo_doma` where `sensor`='doma'");
  while ($zaznam=MySQL_Fetch_Array($xxx)):
    $temp2 = $zaznam["temperature"];   
    $time = (7200+$zaznam["time"])*1000;
    $tmpdata2 = $tmpdata2."[$time,$temp2],";
  endwhile;
  $tmpdata2 = rtrim($tmpdata2, ",");
  $tmpdata2 = $tmpdata2."]";

  mysql_close($conn);
?>
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<title>Highstock Example</title>

		<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
		<script type="text/javascript">
$(function() {
	$.getJSON('http://www.highcharts.com/samples/data/jsonp.php?filename=aapl-c.json&callback=?', function(data) {

		// Create the chart
		$('#container').highcharts('StockChart', {
			
       chart: {
	    },
      
			rangeSelector : {
				enabled: false
			},

			title : {
				text : 'Teplota za oknem - sever  aktuálně:<? echo $temp1;?> °C'
			},
      
      xAxis: {
        type: 'datetime',
        range: 12 * 3600 * 1000
    	},
      
      yAxis: {
	    	min: -20.0,
	    	max: 40.0
	    },

			series : [{
				name : 'za oknem - sever',
				data : <? echo $tmpdata1; ?>,
        typr : "areaspline",
				threshold : null,
				tooltip : {
					valueDecimals : 2
				},
				fillColor : {
					linearGradient : {
						x1: 0, 
						y1: 0, 
						x2: 0, 
						y2: 1
					},
					stops : [[0, Highcharts.getOptions().colors[0]], [1, 'rgba(0,0,0,0)']]
				}
			},
      {
				name : 'doma - sever',
				data : <? echo $tmpdata2; ?>,
        typr : "areaspline",
				threshold : null,
				tooltip : {
					valueDecimals : 2
				},
				fillColor : {
					linearGradient : {
						x1: 0, 
						y1: 0, 
						x2: 0, 
						y2: 1
					},
					stops : [[0, Highcharts.getOptions().colors[0]], [1, 'rgba(0,0,0,0)']]
				}
			}
      ]
		});
	});
});

		</script>
	</head>
	<body><!--WZ-REKLAMA-1.0IZ--><div align="center"><table width="496" border="0"
cellspacing="0" cellpadding="0"><tr><td><a href="http://www.webzdarma.cz/"><img
src="http://i.wz.cz/banner/nudle03.gif" width="28" height="60" 
style="margin: 0; padding: 0; border-width: 0" alt="WebZdarma.cz" /></a></td><td>
<script type='text/javascript'><!--//<![CDATA[
   var m3_u = (location.protocol=='https:'?'https':'http')+'://ad.wz.cz/openx/www/delivery/ajs.php';
   var m3_r = Math.floor(Math.random()*99999999999);
   if (!document.MAX_used) document.MAX_used = ',';
   document.write ("<scr"+"ipt type='text/javascript' src='"+m3_u);
   document.write ("?zoneid=26");
   document.write ('&amp;cb=' + m3_r);
   if (document.MAX_used != ',') document.write ("&amp;exclude=" + document.MAX_used);
   document.write (document.charset ? '&amp;charset='+document.charset : (document.characterSet ? '&amp;charset='+document.characterSet : ''));
   document.write ("&amp;loc=" + escape(window.location));
   if (document.referrer) document.write ("&amp;referer=" + escape(document.referrer));
   if (document.context) document.write ("&context=" + escape(document.context));
   if (document.mmm_fo) document.write ("&amp;mmm_fo=1");
   document.write ("'><\/scr"+"ipt>");
//]]>--></script><noscript><div><a href='http://ad.wz.cz/openx/www/delivery/ck.php?n=a5977468&amp;cb=123'><img src='http://ad.wz.cz/openx/www/delivery/avw.php?zoneid=26&amp;cb=123&amp;n=a5977468' style='margin: 0; padding: 0; border-width: 0' alt='' /></a></div></noscript>
</td></tr></table></div>
<!--WZ-REKLAMA-1.0IK-->
<script src="htdocs/js/highstock.js"></script>
<script src="jhtdocs/s/modules/exporting.js"></script>

<div id="container" style="height: 500px; min-width: 500px"></div>
	</body>
</html>
