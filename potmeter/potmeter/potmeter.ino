// configureer hier de potmeter pin, deze sluiten we hier
int potMeter = A9;
float maxWaarde = 565;
float sensorValue;
float percentage;

int convertedVal;
void setup() {
  Serial.begin(9600); // zet seriele poort aan op 9600 baud.
}
 
void loop() {
  sensorValue = analogRead(potMeter); // Lees de analoge ingang uit.
  percentage =  sensorValue / maxWaarde * 100;
  convertedVal = percentage;
  Serial.print("sensor: "); // print potmeter waarde via seriele monitor.
  Serial.println(sensorValue);
  Serial.print("precentage: ");
  Serial.println(convertedVal);
  Serial.println(" ");
  delay(1000); // even wachten voor een nieuwe loop.
}
