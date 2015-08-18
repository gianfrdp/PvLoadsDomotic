#!/usr/bin/env python
import webiopi
import Adafruit_DHT
import json

SENSOR = Adafruit_DHT.AM2302
PIN = 24

@webiopi.macro
def temperature():
  humidity, temperature = Adafruit_DHT.read_retry(SENSOR, PIN)
  if humidity is not None and temperature is not None:
    fahrenheit = 9.0 / 5.0  * temperature + 32
    return json.dumps({
      "temperature": temperature,
      "humidity": humidity
    })
  else:
    return False