//Led
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Wifi

#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


#define WIFI_SSID "SSID"
#define WIFI_PASS "PASSWORD"

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


const char* wl_status_to_string(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD: return "WL_NO_SHIELD";
    case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
    case WL_CONNECTED: return "WL_CONNECTED";
    case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED: return "WL_DISCONNECTED";
  }
}


void setup()
{

  Serial.begin(9600);
  
  //LED
  
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();

  //WIFI
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    lcd.print("Conectando...");
    delay(1000);
    lcd.clear();
    Serial.println(wl_status_to_string(WiFi.status()));


  }

  lcd.clear();
  lcd.print("Conectado!!");
  delay(3000);

}
// Get parking available parking spots from api
String getAvailableParkingSpot() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    WiFiClient wifiClient;
    HTTPClient http;  //Declare an object of class HTTPClient

    http.begin(wifiClient, "http://tcc-parking-iot.herokuapp.com/parking-spots/available-parkingspot");
    int httpCode = http.GET();
    Serial.println(httpCode);//Send the request

    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload

      Serial.print("codigo :");
      Serial.print(http.GET());
      Serial.println("\n");
      Serial.print("payload :");
      Serial.println(payload);             //Print the response payload
      return payload;
    }

    http.end();   //Close connection

  }

}

void loop() {

  String payload = getAvailableParkingSpot();


  // Shows welcome message
  for (int i = 0; i < 16; i++) {

    lcd.setCursor(i, 0); // col  - row
    lcd.print("Bem-vindos");
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Vagas: ");
    lcd.print(payload);
  }


  delay(10000);

}
