#!/bin/sh

W=`cat /run/shm/metern1.txt  | egrep "^1\(" | grep "*W)" | egrep -o '[0-9]*(\.)?[0-9]*\*' | egrep -o '[0-9]*(\.)?[0-9]*'`
WH=`cat /run/shm/metern1.txt  | egrep "^1\(" | grep "*Wh)" | egrep -o '[0-9]*\*' | egrep -o '[0-9]*'`
V=`cat /run/shm/metern1.txt  | egrep "^1_1\(" | grep "*V)" | egrep -o '[0-9]*(\.)?[0-9]*\*' | egrep -o '[0-9]*(\.)?[0-9]*'`
A=`cat /run/shm/metern1.txt  | egrep "^1_2\(" | grep "*A)" | egrep -o '[0-9]*(\.)?[0-9]*\*' | egrep -o '[0-9]*(\.)?[0-9]*'`

curl -s "http://192.168.2.31:8080/json.htm?type=command&param=udevice&idx=3&nvalue=0&svalue=$W"
curl -s "http://192.168.2.31:8080/json.htm?type=command&param=udevice&idx=4&nvalue=0&svalue=$V"
curl -s "http://192.168.2.31:8080/json.htm?type=command&param=udevice&idx=5&nvalue=0&svalue=$A"
curl -s "http://192.168.2.31:8080/json.htm?type=command&param=udevice&idx=2&nvalue=0&svalue=$W;$WH"
