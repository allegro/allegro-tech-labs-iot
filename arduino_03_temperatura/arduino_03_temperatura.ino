/*
  Sketch which publishes temperature data from a DS1820 sensor to a MQTT topic.
  This sketch goes in deep sleep mode once the temperature has been sent to the MQTT
  topic and wakes up periodically (configure SLEEP_DELAY_IN_SECONDS accordingly).
  Hookup guide:
  - connect D0 pin to RST pin in order to enable the ESP8266 to wake up periodically
  - DS18B20:
     + connect VCC (3.3V) to the appropriate DS18B20 pin (VDD)
     + connect GND to the appopriate DS18B20 pin (GND)
     + connect D4 to the DS18B20 data pin (DQ)
     + connect a 4.7K resistor between DQ and VCC.
*/

#include <OneWire.h>
#include <DallasTemperature.h>

#define SLEEP_DELAY_IN_SECONDS  30
#define ONE_WIRE_BUS            D4      // DS18B20 pin

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

char temperatureString[6];

void setup() {
  // setup serial port
  Serial.begin(115200);
  // setup OneWire bus
//  DS18B20.begin();
}

float getTemperature() {
  Serial.println("Requesting DS18B20 temperature...");
  float temp1;

  DS18B20.requestTemperatures();
  temp1 = DS18B20.getTempCByIndex(0);
  return temp1;
}

void loop() {

  float temperature = getTemperature();

  // convert temperature to a string with two digits before the comma and 2 digits for precision
  dtostrf(temperature, 3, 2, temperatureString);

  // send temperature to the serial console
  Serial.print("Sending temperature: ");
  Serial.println(temperatureString);

  delay(2000);   // wait for deep sleep to happen
}
