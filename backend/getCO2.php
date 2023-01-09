<?php

$co2 = file_get_contents("co2Value.txt");
/* $status = json_decode($co2, true);
 */
echo "[{$co2}]";
/* foreach ($status as $item) {
    echo $item;
} */

?>