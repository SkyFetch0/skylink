#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <LiquidCrystal_I2C.h>

#include "skylink.h"

const char* ssid = "SSID";
const char* password = "PASS";
const char* host = "IPR";
const char* auth_key = "AuthKEy";
const char* container_key = "ContainerKEy";
const uint16_t port = 65432;

skylink skylink(host, port, auth_key,container_key); 
int lcdColumns = 16;
int lcdRows = 2;
int lcdAddr = 0x27;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  lcd.init();
  pinMode(D0, OUTPUT); // LED pinini çıkış olarak ayarla

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
    String statusCommand = String("STATUS ") + container_key;
    skylink.sendData(statusCommand.c_str());    
    String receivedData = skylink.receiveData();
    


    if (receivedData == "Invalid device" || receivedData == "Invalid device") {
    } else {
      digitalWrite(D0, skylink.getBool(receivedData,"D0")); // LED'i yak

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(skylink.getString(receivedData,"D8"));
      lcd.setCursor(0, 1);
      lcd.print(skylink.getString(receivedData,"D7"));
    }

    Serial.println(skylink.getString(receivedData,"D7"));
  } else {
    Serial.println("Connection lost. Reconnecting...");
    skylink.connect();
  }

  delay(200);
}
