/**
 * @file       skylinkApi.h
 * @brief      skylink protocol definitions
 * @author     skyfetch
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2024 skyfetch CO
 * @date       Jan 2024
 */

#ifndef skylinkApi_h
#define skylinkApi_h

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class skylink {
  public:
    skylink(const char* host, uint16_t port, const char* auth, const char* container);
    
    void connect();
    void disconnect();
    bool isConnected();
    void sendData(const char* data);
    String receiveData();
    void getlcd(const char* pin); 
    String getString(const String& data, const String& pin); 
    bool getBool(const String& data, const String& pin); 

  private:
    const char* _host;
    uint16_t _port;
    const char* _auth; 
    const char* _container; 

    WiFiClient _client;
    bool _connected;
};

#endif
