<?php

if($_GET['q'] == ""){
} else {
    $co2 = $_GET["q"];

	$array = array('co2' => $co2);

	$json = json_encode($array);
	file_put_contents("co2Value.txt", $json);
	echo "CO2 = $co2";
}
?>