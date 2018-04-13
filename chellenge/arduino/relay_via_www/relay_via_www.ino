#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

ESP8266WiFiMulti WiFiMulti;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.pl.pool.ntp.org");
ESP8266WebServer server(80);

const char LAMP_PIN = D5;
int state = 1;
String message = "{\"State\": \"Unknown\"}";

void handleRoot() {
  server.send(200, "text/plain", "Lamp switcher v1.0.0");
}

void handleState() {
  server.send(200, "application/json", message);
}

void handleSwitch() {
  if (state == 0) {
    digitalWrite(LAMP_PIN, LOW);
    state = 1;
    message = "{\"State\": \"On\"}";
  } else if (state == 1) {
    digitalWrite(LAMP_PIN, HIGH);
    state = 0;
    message = "{\"Status\": \"Off\"}";
  } else {
    state = 1;
    message = "{\"Status\": \"Unknown\"}";
  }
  server.send(200, "application/json", message);
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

  pinMode(LAMP_PIN, OUTPUT);
  // We always set state to HIGH (off lamp) when initialize
  // bacause in specification is write that the state change whien go to LOW state
  digitalWrite(LAMP_PIN, HIGH);
  
  //-------- Initialize WiFi
  Serial.println();
  Serial.print("Waiting for WiFi... ");

  WiFiMulti.addAP("esp8266labs", "esp8266labs");

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
  for (int i = 0; i < 3; i++) {
    delay(1000);
    timeClient.update();
    Serial.print("Time:");
    Serial.println(timeClient.getFormattedTime());
  }

  //--------- Initialize HTTP server
  server.on("/", handleRoot);
  server.on("/switch", handleSwitch);
  server.on("/status", handleState);
 
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  Serial.println("------------ Setup completed --------------");
  delay(100);
}

void loop() {
  for (int i = 0; i < 100; i++) {
    server.handleClient();
    delay(100);
  }
  timeClient.update();

  Serial.print("Time: ");
  Serial.println(timeClient.getFormattedTime());

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
}

