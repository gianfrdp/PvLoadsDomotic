#!/bin/sh

DATA="$(php /usr/local/bin/dht_esp.php $1)"
#echo $DATA

if [ x"$DATA" != x ]; then
    echo $DATA | tr " " "\n" > /run/shm/metern$1.txt
fi
