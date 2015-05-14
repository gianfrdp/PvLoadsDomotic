<?php
// Credit Louviaux Jean-Marc 2015
define('checkaccess', TRUE);
include('../config/config_main.php');
include('../scripts/memory.php');
date_default_timezone_set($DTZ);

$dir    = '../data/csv/';
$output = glob($dir . '/*.csv');
rsort($output);

@$shmid = shmop_open($LIVEMEMORY, 'a', 0, 0);
if (!empty($shmid) && isset($output[0])) {
    $size = shmop_size($shmid);
    shmop_close($shmid);
    $shmid = shmop_open($LIVEMEMORY, 'c', 0644, $size);
    $memdata  = shmop_read($shmid, 0, $size);
    $live = json_decode($memdata, true);
    shmop_close($shmid);

    //echo "MEMORY = $MEMORY\n";
    @$shmid = shmop_open($MEMORY, 'a', 0, 0);
    if (!empty($shmid)) {
        $size = shmop_size($shmid);
        shmop_close($shmid);
        $shmid = shmop_open($MEMORY, 'c', 0644, $size);
        $memdata  = shmop_read($shmid, 0, $size);
        $memory = json_decode($memdata, true);
        shmop_close($shmid);

        $array = array();

        //var_dump($memory);
        $array = array();
        for ($i = 1; $i <= $NUMMETER; $i++) {
            include("../config/config_met$i.php");

            if (${'TYPE' . $i} == 'Elect') {
                $val_mid = $memory["Midnight$i"];
                settype($val_mid, 'integer');
                //echo "val_mid $i: $val_mid\n";
                $val_tot = $memory["Totalcounter$i"];
                settype($val_tot, 'integer');
                //echo "val_tot $i: $val_tot\n";
                $val_today = $val_tot - $val_mid;
                //echo "val_today $i: $val_today\n";
                $val_today /= 1000;
                $array["${'METNAME'.$i}$i"] = array("KW" => $live["${'METNAME'.$i}$i"], "KWH" => round($val_today,${'PRECI' . $i}));
            }
        }
    }
} else {
    for ($i = 1; $i <= $NUMMETER; $i++) {
        include("../config/config_met$i.php");

        $array["${'METNAME'.$i}$i"] = array("KW" => 0, "KWH" => 0);
    }
}

header("Content-type: text/json");
echo json_encode($array);
?>
