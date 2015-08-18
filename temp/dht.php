<?php

if (isset($argv[1]) && isset($argv[2])) {
    $macro = $argv[1];
    $id = $argv[2];
    $MY_URL = "http://127.0.0.1:8000/macros/$macro";
    $post = NULL;
    $options = array(
        CURLOPT_POST => TRUE,
        CURLOPT_HEADER => FALSE,
        CURLOPT_URL => $MY_URL,
        CURLOPT_FRESH_CONNECT => TRUE,
        CURLOPT_RETURNTRANSFER => TRUE,
        CURLOPT_FORBID_REUSE => TRUE,
        CURLOPT_TIMEOUT => 30,
        CURLOPT_POSTFIELDS => $post,
        CURLOPT_POST, TRUE,
        //CURLOPT_VERBOSE, TRUE,
        CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0
    );

    $ch = curl_init();
    curl_setopt_array($ch, $options);

    $html = curl_exec($ch);
    curl_close($ch);

    $dht = json_decode($html, true);
    $temperature = round($dht["temperature"],2);
    $humidity = round($dht["humidity"],2);

    if ($temperature <> 0 && $humidity <> 0) {
        echo "$id($temperature*C)\n";
        echo "$id($humidity*%)\n";
    }

} else {
    die("Usage: dht macro id\n");
}
?>