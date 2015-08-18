#!/bin/sh

METER=$1
echo "${METER}($(curl -s http://127.0.0.1:8000/devices/temp${METER}/sensor/temperature/c)*C)" > /run/shm/metern${METER}.txt