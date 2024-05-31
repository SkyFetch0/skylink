#include <skylink/skylinkApi.h>

skylink::skylink(const char* host, uint16_t port, const char* auth) 
    : _host(host), _port(port), _auth(auth), _connected(false) {
}

void skylink::connect() {
    if (_client.connect(_host, _port)) {
        _client.print(_auth);  
        if (_client.connected()) {
            _connected = true;
        } else {
            _connected = false;
            _client.stop();
        }
    } else {
        _connected = false;
    }
}

void skylink::disconnect() {
    _client.stop();
    _connected = false;
}

bool skylink::isConnected() {
    return _connected && _client.connected();
}

void skylink::sendData(const char* data) {
    if (_connected && _client.connected()) {
        _client.print(data);
    }
}

String skylink::receiveData() {
    if (_connected && _client.connected() && _client.available()) {
        return _client.readStringUntil('\n');
    } else {
        return ""; 
    }
}

void skylink::getlcd(const char* pin) {
    if (_connected && _client.connected()) {
        String command = "GETLCD ";
        command += pin;
        _client.print(command);

        String data = receiveData();
        String value = getPinValue(data, pin);
        Serial.println(value); 
    }
}

String skylink::getPinValue(const String& data, const String& pin) {
    int start = data.indexOf(pin + ":");
    if (start == -1) {
        return ""; 
    }

    start += pin.length() + 1;
    int end = data.indexOf(',', start);
    if (end == -1) {
        end = data.length(); 
    }

    return data.substring(start, end);
}
