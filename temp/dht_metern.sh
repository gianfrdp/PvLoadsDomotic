#!/bin/sh

DATA="$(ADHT_metern.py $1 $2 $3)"
echo $DATA

if [ x"$DATA" != x ] && [ "$DATA" != "ERROR" ]; then
    echo $DATA | cut -d\  -f 1 > /run/shm/metern$3.txt
    echo $DATA | cut -d\  -f 2 >> /run/shm/metern$3.txt
fi
