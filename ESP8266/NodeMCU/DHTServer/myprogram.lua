pin = 1
temp = 0
humi = 0

function readDHT22()
    DHT=require("dht")
    status,temp,humi,temp_decimial,humi_decimial = dht.readxx(pin)
    if( status == dht.OK ) then
        -- Float firmware using this example
        print("(1) DHT Temperature:"..temp..";".." Humidity:"..humi)
    elseif( status == dht.ERROR_CHECKSUM ) then
        print( "(2) DHT Checksum error." );
    elseif( status == dht.ERROR_TIMEOUT ) then
        print( "(3) DHT Time out." );
    end
    package.loaded["dht"]=nil
end

-- Start a simple http server
if not (srv == nil) then
  srv:close()
end
srv=net.createServer(net.TCP)
srv:listen(80, function(conn)
  conn:on("receive", function(client, payload)
    print("(4) Got query...")
    print("(5) Heap = "..node.heap().." Bytes")
    print("(6) Time since start = "..tmr.time().." sec")
    header = "HTTP/1.1 200 OK\r\n"
    --print("(7) Print payload:\n"..payload)
    readDHT22()
    print("(8) Read")

    --ok, json = pcall(cjson.encode, {temperature=temp, humidity=humi})
    json = "{\"humidity\":" .. humi .. ",\"temperature\":" .. temp .. "}"
    ok = true
    if ok then
        print("(9) json="..json)
        header = header .. "Content-Type: application/json\r\n"
        reply = json
    else
        header = header .. "Content-Type: text/html\r\n"
        reply = "<hmlt><body><h1>nothing to read</h1></body></html>"
    end
    local buf = header .. "Cache-Control: private, no-store\r\n\r\n"
    --buf = buf.. "Content-Length:" .. tostring(string.len(reply)) .. "\r\n"
    buf = buf.. reply .. "\r\n"
    --print("(10) "..buf)
    conn:send(buf)
    collectgarbage()
  end)
  conn:on("sent", function(conn)
        print("(11) closing")
        conn:close()
  end)
end)
