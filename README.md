# PvLoadsDomotic
Home Automation management of electrical loads using 123solar

These are 123solar (http://123solar.org) extension to manage Raspberry Pi GPIO pin for turning on/off relais following production/consumption difference.
The main golas of the project is to remote control your relais and to optimize PV self-consumption.

It's based on 123solar 1.5.5 version for Production reading and can use different types of systems to read consumption:
- meterN (http://metern.org)
- measureit (https://code.google.com/p/measureit/)
- a modified version for Arduino Solar Meter (https://solarmeter.codeplex.com/)
- Eastron SDM Modbus meter (https://github.com/gianfrdp/SDM120C)

It uses WebIOPi to control GPIO (https://code.google.com/p/webiopi/), Redis (http://redis.io/) to store relays statues with PHP binding (https://github.com/phpredis/phpredis)
 
