#include "skylink.h"

skylink::skylink(const char* host, uint16_t port, const char* auth) 
    : _host(host), _port(port), _auth(auth), _connected(false) {
}


void skylink::connect() {
    _client.connect(_host, _port);
    _client.print(_auth);  

    _connected = true;
}

void skylink::disconnect() {
    _client.stop();
    _connected = false;
}

bool skylink::isConnected() {
    return _connected;
}

void skylink::sendData(const char* data) {
    _client.print(data);
}

String skylink::receiveData() {
    if (_client.available()) {
        return _client.readStringUntil('\n');
    } else {
        return ""; 
    }
}
