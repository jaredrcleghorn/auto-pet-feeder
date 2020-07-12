#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

ESP8266WebServer server(80);

void handleRoot() {
  String htmlPage = String("<label for=\"ssid\">SSID</label>") +
                           "<select id=\"ssid\">";

  for (int i = 0; i < WiFi.scanNetworks(); ++i) {
    htmlPage += "<option>" + WiFi.SSID(i) + "</option>";
  }

  htmlPage += String("</select>") +
              "<input type=\"text\" />";
  
  server.send(200, "text/html", htmlPage);

  
}

void handleSpin() {
  server.send(200, "text/html", "Spinning...");
  
  digitalWrite(5, HIGH);
  delay(5000);
  digitalWrite(5, LOW);
}

void setup() {
  WiFi.softAP("Automatic Pet Feeder");
  
  server.on("/", handleRoot);
  server.on("/spin", handleSpin);
  server.begin();

  pinMode(5, OUTPUT);
}

void loop() {
  server.handleClient();
}
