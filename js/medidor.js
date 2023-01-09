google.charts.load('current', {'packages':['gauge']});
google.charts.setOnLoadCallback(drawChart);

function drawChart() {

var data = google.visualization.arrayToDataTable([
    ['Label', 'Value'],
    ['CO2', 0]
]);

var options = {
    width: 500, height: 500,
    redFrom: 90, redTo: 100,
    yellowFrom:75, yellowTo: 90,
    minorTicks: 5
};

var chart = new google.visualization.Gauge(document.getElementById('Medidor'));

chart.draw(data, options);

setInterval(function() {
    var JSON=$.ajax({url: "http://localhost/ProyectoTI/backend/getCO2.php", dataType: 'json', async: false}).responseText;
    var Resp=jQuery.parseJSON(JSON);

    data.setValue(0, 1, (Resp[0].co2)/10 );
    chart.draw(data, options);
}, 1000);

}
