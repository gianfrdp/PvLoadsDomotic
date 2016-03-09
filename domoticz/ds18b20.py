#!/usr/bin/env python
import sys
from w1thermsensor import W1ThermSensor

address = sys.argv[1]
sensor = W1ThermSensor(W1ThermSensor.THERM_SENSOR_DS18B20, address)
temperature_in_celsius = sensor.get_temperature()

print("{0:.2f}".format(temperature_in_celsius))