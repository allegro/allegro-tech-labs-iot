
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WiFiUdp.h>
#include <NTPClient.h>

#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#define SLEEP_DELAY_IN_SECONDS  30
#define ONE_WIRE_BUS            D4      // DS18B20 pin

#define ledPin D5

ESP8266WiFiMulti WiFiMulti;
WiFiUDP ntpUDP;
// By default 'time.nist.gov' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

float temperature;
char temperatureString[6];

ESP8266WebServer server(80);

float getTemperature() {
//  Serial.println("Requesting DS18B20 temperature...");

  DS18B20.requestTemperatures();
  return DS18B20.getTempCByIndex(0);
}


void handleRoot() {
//  char message[255];

  String arguments = "Args\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    arguments += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  arguments += "\n";
  Serial.println(arguments);
  server.send(200, "text/plain", arguments);
}

void handleBlink() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  server.send(200, "text/plain", "Blinked");
}

void handleTemperature() {
  char charBuf[50];
  String message;               // workaround for couple of strncpy
  float temp = getTemperature();

  message = "{\"temp\":";
  message += String(temp, 6);
  message += "}";

  message.toCharArray(charBuf, 50);
  server.send(200, "application/json", charBuf);

}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  //-------- Initialize WiFi
  Serial.println();
  Serial.print("Waiting for WiFi... ");

  WiFiMulti.addAP("esp8266lab", "esp8266labs");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //-------- Initialize NTP
  Serial.println("Waiting for ntp...");
  timeClient.begin();
  for (int ii = 0; ii < 3; ii++) {
    delay(1000);
    timeClient.update();
    Serial.print("Time:");
    Serial.println(timeClient.getFormattedTime());
  }

  //--------- Initialize MDNS responder
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  //--------- Initialize HTTP server

  server.on("/", handleRoot);
  server.on("/blink", handleBlink);
  server.on("/temp", handleTemperature);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
 
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  Serial.println("------------ Setup completed --------------");
  delay(100);
}

void loop() {

  for (int ii = 0; ii < 100; ii++) {
    server.handleClient();
    delay(100);
  }


  timeClient.update();

  Serial.print("Time: ");
  Serial.println(timeClient.getFormattedTime());

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Temperatura: ");
  temperature = getTemperature();
  dtostrf(temperature, 2, 2, temperatureString);
  Serial.println(temperatureString);

}

