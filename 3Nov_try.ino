#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

// WiFi Parameters
const char* ssid = "Realme2Pro";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() {
  // Check WiFi Status
  
  if (WiFi.status() == WL_CONNECTED) {
    //Serial.println("WiFi Connected. Execution Started");
    HTTPClient http;  //Object of class HTTPClient
    http.put("http://api.iotronlabs.com/public/api/devices/update?id=1&status=0");
    http.begin("http://api.iotronlabs.com/public/api/devices/fan");
    //Serial.println("HTTP Code checking starts");
    int httpCode = http.GET();
    //Serial.println(httpCode);
    //Check the returning code                                                                  
    if (httpCode > 0) {
      
      //Serial.println("http Code conatisn some value");
      // Parsing
      const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(5) + 90;
//      const size_t bufferSize = JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 370;
      DynamicJsonBuffer jsonBuffer(capacity);
      //JsonObject& root = jsonBuffer.parseObject(http.getString());
      // Parameters
      //int device-id = root["device-id"]; 
      //const char* nam = root["device-name"]; 
      //const char* slug = root["device-slug"];
      //const char* statu = root["status"]; // "Sincere@april.biz"
      // Output to serial monitor
      //const char* json = "{\"data\":{\"device-id\":1,\"device-name\":\"CeilingFan\",\"device-slug\":\"fan\",\"status\":0,\"value\":50}}";
      //Serial.print("Debbuging point 2");
JsonObject& root = jsonBuffer.parseObject(http.getString());
//Serial.print("Debbuging point 3");
JsonObject& data = root["data"];
int data_device_id = data["device-id"]; // 1
const char* data_device_name = data["device-name"]; // "CeilingFan"
const char* data_device_slug = data["device-slug"]; // "fan"
int data_status = data["status"]; // 0
int data_value = data["value"]; // 50
    if ( data_status == 1 )
    digitalWrite(LED_BUILTIN, LOW);
    else if ( data_status == 0 )
    digitalWrite(LED_BUILTIN, HIGH);


//Serial.print("Debbuging point 4");

      
      Serial.print("data device name:");
      Serial.println(data_device_name);
      Serial.print("data_status:");
      Serial.println(data_status);
      //Serial.print("data_value:"); 
      //Serial.println(data_value);
    }
/*
http.begin("http://jsonplaceholder.typicode.com/posts/1");
   http.addHeader("Content-Type", "text/plain");            
 
   int httpResponseCode = http.PUT("PUT sent from ESP32");   
 
   if(httpResponseCode>0){
 
    String response = http.getString();   
 
    Serial.println(httpResponseCode);
    Serial.println(response);          
 
   }else{
 
    Serial.print("Error on sending PUT Request: ");
    Serial.println(httpResponseCode);
 
   }
   */

/*
http.begin("http://api.iotronlabs.com/public/api/devices/update?id=1&status=1");
//  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  */ 

http.put('http://api.iotronlabs.com/public/api/devices/update?','Content-Type: application/x-www-form-urlencoded\r\n','id=1&status=0\n');
function(code,data)
if (code<0)
Serial.println("HTTP Failed");
else
Serial.println(code, data);


    http.end();   //Close connection
  }
  // Delay
  delay(3500);
}
