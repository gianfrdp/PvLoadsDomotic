import requests
from optparse import OptionParser
from pyintesishome import IntesisHome
import sys
import pycurl
import re
try:
    from io import BytesIO
except ImportError:
    from StringIO import StringIO as BytesIO

def main():

    # Need pyIntesishome and python 3.5
    #
    username="xxxxxx" # change me
    password="yyyyyy" # change me
    idd = xyxyxyxyxyxy # change me
    aquarea = None
    #id = opts.id

    aquarea = IntesisHome(username, password)
    aquarea.poll_status()
    #if not (aquarea.is_connected):
    #    aquarea.connect()

    tank_temp = aquarea.get_tank_temperature(idd)
    print("Tank temperature = %.1f°C" % aquarea.get_tank_temperature(idd))

    #aquarea.closeLoop()

    domoticzURL = "http://127.0.0.1:8080" # chamge me
    domoticzIDX = "18" # change me
    URL = domoticzURL + "/json.htm?type=command&param=udevice&idx=" + domoticzIDX + "&nvalue=0&svalue=" + str(tank_temp)
    print(URL)

    #buffer = BytesIO()
    #c = pycurl.Curl()
    #c.setopt(c.URL, URL)
    #c.setopt(c.WRITEDATA, buffer)
    #c.perform()
    #c.close()

    #body = buffer.getvalue()
    # Body is a byte string.
    # We have to know the encoding in order to print it to a text file
    # such as standard output.
    #print(body.decode('iso-8859-1'))

    r = requests.get(URL)
    print(r)

if __name__ == "__main__":
    main()
