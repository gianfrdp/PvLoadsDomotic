#!/bin/bash

action=$1
mac=$2
ip=$3
reversedMac=${mac:10:1}${mac:11:1}${mac:8:1}${mac:9:1}${mac:6:1}${mac:7:1}${mac:4:1}${mac:5:1}${mac:2:1}${mac:3:1}${mac:0:1}${mac:1:1}

# Subscribe to the device:
echo '6864001e636c'$mac'202020202020'$reversedMac'202020202020' | xxd -r -p | nc -u -w1 -p10000 $ip 10000 | xxd -p

case $action in
off)
        # Switch Off
        echo '686400176463'$mac'2020202020200000000000' | xxd -r -p | nc -u -w1 -p10000 $ip 10000 | xxd -p
        ;;
on)
        # Switch On
        echo '686400176463'$mac'2020202020200000000001' | xxd -r -p | nc -u -w1 -p10000 $ip 10000 | xxd -p
        ;;
esac

exit;