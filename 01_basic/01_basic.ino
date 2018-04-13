
// the setup routine runs once when you press reset or switch device on etc...
void setup() {
  Serial.begin(115200);
  Serial.print("print ");
  Serial.println("println");
  
  pinMode(D5, OUTPUT);            // Initialize the LED pin as an output

  Serial.println("LOW");
  digitalWrite(D5, LOW);          // Turn the LED off
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("HIGH");
  digitalWrite(D5, HIGH);         // Turn the LED off by making the voltage HIGH
  delay(2000);
  
  Serial.println("LOW");
  digitalWrite(D5, LOW);          // Turn the LED on
  delay(1000);
}
