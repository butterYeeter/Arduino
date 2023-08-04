/*
  ESP32 Chuck Norris Jokes
  by R. Pelayo
  Tutorial: https://www.teachmemicro.com/esp32-restful-api
  
  V1.0 - 10/27/2020
*/
 
//#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
 
//Provide your own WiFi credentials
const char* ssid = "3VG WiFi";
const char* password = "3vangogh@*";
//String for storing server response
const int    HTTP_PORT   = 80;
const String HTTP_METHOD = "GET"; // or "POST"
const char   HOST_NAME[] = "google.com"; // hostname of web server:
const String PATH_NAME   = "";
 
 
void setup(void) {
  //For displaying the joke on Serial Monitor
  Serial.begin(9600);
  //Initiate WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Atempting To Connect");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}
 
void loop(void) {
  if(client.connect(HOST_NAME, HTTP_PORT)) {
  Serial.println("Connected to server");
  // send HTTP request header
client.println(HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1");
client.println("Host: " + String(HOST_NAME));
client.println("Connection: close");
client.println(); // end HTTP request header


} else {
  Serial.println("connection failed");
}




  delay(2000);
}
