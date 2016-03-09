<?php
if (isset($argv[1])) {
    $id = $argv[1];
    $data = file_get_contents("http://192.168.2.33");

    $dht = json_decode($data, true);
    $temperature = round($dht["temperature"],2);
    $humidity = round($dht["humidity"],2);

    if ($temperature <> 0 && $humidity > 0) {
        echo "$id($temperature*C)\n";
        echo "$id($humidity*%)\n";
    }
} else {
    die("Usage: dht id\n");
}

?>