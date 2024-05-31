#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <LiquidCrystal_I2C.h>

#include "skylink.h"

const char* ssid = "SSID";
const char* password = "PASS";
const char* host = "HOST";
const uint16_t port = 65432;

skylink skylink(host, port, "AUTH"); 
int lcdColumns = 16;
int lcdRows = 2;
int lcdAddr = 0x27;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  skylink.connect();
}

void loop() {
  if (skylink.isConnected()) {
    skylink.sendData("STATUS D8");
    String receivedDataD8 = skylink.receiveData();
    
    skylink.sendData("STATUS D7"); 
    String receivedDataD7 = skylink.receiveData();

    if (receivedDataD8 == "Invalid device" || receivedDataD7 == "Invalid device") {
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(receivedDataD8);
      lcd.setCursor(0, 1);
      lcd.print(receivedDataD7);
    }

    Serial.println(receivedDataD8);
    Serial.println(receivedDataD7);
  } else {
    Serial.println("Connection lost. Reconnecting...");
    skylink.connect();
  }

  delay(300);
}
