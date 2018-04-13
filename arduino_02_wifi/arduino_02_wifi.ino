
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WiFiUdp.h>
#include <NTPClient.h>

ESP8266WiFiMulti WiFiMulti;
WiFiUDP ntpUDP;
// By default 'time.nist.gov' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP);


void setup() {
  Serial.begin(115200);
  delay(100);

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
  for (int ii = 0; ii < 3; ii++) {
    delay(1000);
    timeClient.update();
    Serial.print("Time:");
    Serial.println(timeClient.getFormattedTime());
  }

  Serial.println("------------ Setup completed --------------");
  delay(100);
}

void loop() {
  timeClient.update();

  Serial.print("Time: ");
  Serial.println(timeClient.getFormattedTime());

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);

}

