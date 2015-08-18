#!/bin/sh

DATA="$(php /usr/local/bin/dht.php $1 $2)"

if [ x"$DATA" != x ]; then
    echo $DATA | tr " " "\n" > /run/shm/metern$2.txt
fi
