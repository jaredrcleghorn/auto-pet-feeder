#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

ESP8266WebServer server(80);

void setup() {
	// Set up a soft access point.
	WiFi.softAP("Auto Pet Feeder");

	server.on("/", [] { server.send(200, "text/plain", "hello, world"); });

	// Start the server.
	server.begin();
}

void loop() {
	server.handleClient();
}
