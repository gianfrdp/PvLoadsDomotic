<?php

$data = file_get_contents("http://192.168.2.33");

$json = json_decode($data, true);

try {
    $temp = $json["temperature"];
    settype($temp, 'float');
    $humi = $json["humidity"];
    settype($humi, 'float');
    echo "temp = $temp C, humi = $humi %\n";
    if ($humi > 0) {
	$URL = "http://127.0.0.1:8080/json.htm?type=command&param=udevice&idx=1&nvalue=0&svalue=" . $temp .";". $humi .";0";

	//echo "$URL\n";

	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, $URL);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	$response = curl_exec($ch);
	//echo "$response\n";
	$headers=get_headers($URL, 1);
	curl_close($ch);
    }

} catch (Exception $e) {
    die( "Cannot send temp/humi: ".$e->getMessage() );
}


?>
