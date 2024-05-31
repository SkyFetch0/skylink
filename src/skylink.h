/**
 * @file       skylink.h
 * @author     skyfetch
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2024 skyfetch
 * @date       Jan 2024
 * @brief      skylink protocol definitions
 *
 */

#ifndef skylink_h
#define skylink_h
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class skylink {
  public:
    skylink(const char* host, uint16_t port,const char* auth);
    void connect();
    void disconnect();
    bool isConnected();
    void sendData(const char* data);
    String receiveData();
  
  private:
    const char* _host;
    uint16_t _port;
    const char* _auth; 
    WiFiClient _client;
    bool _connected;
};
#endif
