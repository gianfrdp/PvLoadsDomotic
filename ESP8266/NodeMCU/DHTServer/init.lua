--load credentials for WI-FI
dofile("credentials.lua")

function startup()
    if file.open("init.lua") == nil then
      print("init.lua deleted")
    else
      print("Running")
      file.close("init.lua")
      -- Run main program
      dofile("myprogram.lua")
    end
end

--init.lua
print("set up wifi mode")
wifi.setmode(wifi.STATION)
wifi.sta.config(SSID,PASSWORD)
--here SSID and PassWord should be modified according your wireless router
wifi.sta.connect()
-- Staic IP
wifi.sta.setip({ip="192.168.2.33",netmask="255.255.255.0",gateway="192.168.2.1"})
print("ESP8266 mode is: " .. wifi.getmode())
print("Network: " .. SSID)
print("The module MAC address is: " .. wifi.ap.getmac())
print("Config done, IP is "..wifi.sta.getip())
--print("You have 5 seconds to abort Startup")
--print("Waiting...")
--tmr.alarm(0,5000,0,startup)
startup()