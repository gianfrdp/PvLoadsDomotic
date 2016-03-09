#!/bin/sh

curl -s "http://192.168.2.31:8080/json.htm?type=command&param=udevice&idx=6&nvalue=0&svalue="$(ds18b20.py $1)