#include <Arduino.h>
/*
Required libs:
  - ArtNet by hideakitai
  - esp_dmx by Mitch Weisbrod
  - UUID by Rob Tillaart
*/

#include <ArtnetWiFi.h>
#include <esp_dmx.h>

#include <UUID.h>

#include <EEPROM.h>

#define wifi_max_connect_time = 10000

int transmit_pin = 0;
dmx_port_t dmx_port = 1;

byte universe[DMX_PACKET_SIZE];

ArtnetWiFiReceiver artnet;

void setup_eeprom() {
    UUID uuid;
    uuid.generate();

    // EEPROM layout: 32 bytes auth code (the uuid); 32 bytes last wifi ssid; 32 bytes last wifi password
}

void write_to_dmx(const uint8_t* data, const uint16_t size) {
    for (size_t i = 0; i < size; i++) {
        universe[i + 1] = data[i];
    }

    dmx_write(dmx_port, universe, DMX_PACKET_SIZE);
    dmx_send(dmx_port, DMX_PACKET_SIZE);
}

// bool connect_wifi(const char[] ssid, const char[] password) {
//     WiFi.begin(ssid, password);
//     delay(wifi_max_connect_time);

//     switch(WiFi.status()) {
//         case WL_CONNECT_FAILED
//     }

//     return WiFi.status() == WL_CONNECTED;
// }

void setup() {
    artnet.begin();
    artnet.subscribe(0, write_to_dmx);

    // port; transmit-, receive-, enable pin
    dmx_set_pin(dmx_port, transmit_pin, 18, 19);
}

void loop() {
    artnet.parse();
    // dmx_wait_sent(dmx_port, DMX_TIMEOUT_TICK);
}

/*
Not working board urls for this project:
http://arduino.esp8266.com/stable/package_esp8266com_index.json
https://dl.espressif.com/dl/package_esp32_index.json
https://github.com/espressif/arduino-esp32/releases/download/2.0.6/package_esp32_index.json
*/