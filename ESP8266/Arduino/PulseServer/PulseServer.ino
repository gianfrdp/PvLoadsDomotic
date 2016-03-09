/* PulseServer - ESP8266 Webserver with a pulse counter as an input


   Based on ESP8266Webserver, DHTexample, and BlinkWithoutDelay (thank you)


   Version 1.0  5/3/2014   Version 1.0   Mike Barela for Adafruit Industries
   Version 1.1  29/02/2016 Version 1.1   Gianfranco Di Prinzio
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define PIN D2

const char* ssid     = "myssid";
const char* password = "mypassword";


// the IP address for the shield:
IPAddress ip (192, 168, 3, 21);
IPAddress dns (192, 168, 3, 1);
IPAddress gateway (192, 168, 3, 1);
IPAddress subnet (255, 255, 255, 0);


void getCounter();


ESP8266WebServer server(80);
 
float counter = 0, read_counter;  // Values read from sensor
unsigned long seconds;
String webString="";     // String to display
// Generally, you should use "unsigned long" for variables that hold time
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor
 
void handle_root() {
  getCounter();       // read sensor
  webString="{\"counter\":" + String(read_counter) + ",\"seconds\":" + String(seconds) + "}";
  server.send(200, "application/json", webString);            // send to someones browser when asked
  delay(100);
}

void manageCounter() {
  // Increase counter
  counter++;
}

void setup(void)
{
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable
  //pinMode(PIN, INPUT);
  pinMode(PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN), manageCounter, FALLING);

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
  Serial.println("Pulse Counter Server");
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

void getCounter() {
  // Wait at least 2 seconds seconds between measurements.
  // if the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor
  // Works better than delay for things happening elsewhere also
  unsigned long currentMillis = millis();
 
  if (currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor 
    
    seconds = (currentMillis - previousMillis)/1000;
    Serial.println("Time since start = " + String((int)(currentMillis/1000)) + " sec");
    Serial.println("Time since last read = " + String(seconds) + " sec");
    previousMillis = currentMillis;


    read_counter = counter; // Read counter
    counter = 0;   // reset counter
    // Check if any reads failed and exit early (to try again).
    if (isnan(read_counter)) {
      Serial.println("Failed to read from counter!");
      return;
    }
    Serial.println("Counter: " + String(read_counter));
  }
}
