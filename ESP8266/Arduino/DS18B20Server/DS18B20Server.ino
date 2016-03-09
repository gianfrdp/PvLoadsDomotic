/* DS18B20Server - ESP8266 Webserver with a DS18B20 1-Wire sensor as an input

   Based on ESP8266Webserver, DHTexample, and BlinkWithoutDelay (thank you)

   Version 1.0  5/3/2014   Version 1.0   Mike Barela for Adafruit Industries
   Version 1.1  15/02/2016 Version 1.1   Gianfranco Di Prinzio
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid     = "myssid";
const char* password = "mypassword";

// the IP address for the shield:
IPAddress ip (192, 168, 2, 34);
IPAddress dns (192, 168, 2, 1);
IPAddress gateway (192, 168, 2, 1);

IPAddress subnet (255, 255, 255, 0);

/*
IPAddress ip (192, 168, 15, 103);
IPAddress dns (192, 168, 15, 1);
IPAddress gateway (192, 168, 15, 1);
*/

void gettemperature();

ESP8266WebServer server(80);
 
//initialize 1-wire bus
#define ONE_WIRE_BUS D2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
 
float temp_c;  // Values read from sensor
String webString="";     // String to display
 
void handle_root() {
  gettemperature();       // read sensor
  webString="{\"temperature\":" + String(temp_c) + "}";
  server.send(200, "application/json", webString);            // send to someones browser when asked
  delay(100);
}
 
void setup(void)
{
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable

  // Uncomment this row to use static IP
  WiFi.config(ip, dns, gateway, subnet); 
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DS18B20 Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", handle_root);
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
} 

void gettemperature() {
  unsigned long currentMillis = millis();

  do {
    sensors.requestTemperatures(); // Send the command to get temperatures
    temp_c = sensors.getTempCByIndex(0);
  } while (temp_c == 85.0 || temp_c == (-127.0));
 
  Serial.println("Time since start (1) = " + String((int)(currentMillis/1000)) + " sec");
  currentMillis = millis();
  Serial.println("Time since start (2) = " + String((int)(currentMillis/1000)) + " sec");
  
  Serial.println("DS18B20 Temperature:" + String(temp_c) + " C");
}
