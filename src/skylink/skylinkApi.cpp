#include <skylink/skylinkApi.h>

skylink::skylink(const char* host, uint16_t port, const char* auth, const char* container) 
    : _host(host), _port(port), _auth(auth), _container(container), _connected(false) {
}

void skylink::connect() {
    if (_client.connect(_host, _port)) {
        String authMessage = "AUTH " + String(_auth) + " " + String(_container) + " \n";
        Serial.println("Sending Auth Message: " + authMessage);

        _client.print(authMessage);
        delay(50); 
        
        if (_client.connected() && _client.available()) {
            String response = _client.readStringUntil('\n');
            if (response == "Authenticated") {
                _connected = true;
            } else {
                _connected = false;
                _client.stop();
            }
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
        String value = getString(data, pin);
        Serial.println(value); 
    }
}

String skylink::getString(const String& data, const String& pin) {
    int start = data.indexOf(pin + "=");
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
bool skylink::getBool(const String& data, const String& pin) {
    int start = data.indexOf(pin + "=");
    if (start == -1) {
        return false; 
    }

    start += pin.length() + 1;
    int end = data.indexOf(',', start);
    if (end == -1) {
        end = data.length(); 
    }

    String value = data.substring(start, end);
    value.trim(); 

    if (value.equalsIgnoreCase("ON") ||
        value.equalsIgnoreCase("on") ||
        value.equalsIgnoreCase("true") ||
        value == "1") {
        return true;
    } else {
        return false;
    }
}