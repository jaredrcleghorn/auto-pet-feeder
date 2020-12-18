#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

ESP8266WebServer server(80);

void setup() {
	// Set up a soft access point.
	WiFi.softAP("Auto Pet Feeder");

	server.on("/networks", [] {
		int numNetworks = WiFi.scanNetworks();
		DynamicJsonDocument doc(JSON_ARRAY_SIZE(numNetworks) + numNetworks * (JSON_OBJECT_SIZE(3) + 32));

		for (int i = 0; i < numNetworks; ++i) {
			JsonObject obj = doc.createNestedObject();

			obj["name"] = WiFi.SSID(i);
			obj["isEncrypted"] = WiFi.encryptionType(i) != ENC_TYPE_NONE;

			const int rssi = WiFi.RSSI(i);
			const int minRssi = -100;
			const int maxRssi = -50;
			const int numStrengths = 4;

			if (rssi <= minRssi) {
				obj["strength"] = 1;
			} else if (rssi >= maxRssi) {
				obj["strength"] = numStrengths;
			} else {
				obj["strength"] = numStrengths * (rssi - minRssi) / (maxRssi - minRssi) + 1;
			}
		}

		server.send(200, "application/json", doc.as<String>());
	});

	// Start the server.
	server.begin();
}

void loop() {
	server.handleClient();
}
