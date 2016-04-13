//REMARK
//Disconnect the pins of the sensor before uploading the source
//the connected pins will disable the PC/Arduino connection

#define ECHOPIN 6                            // Pin to receive echo pulse
#define TRIGPIN 7                            // Pin to send trigger pulse
#define BUZZER 3
void setup(){
  Serial.begin(9600);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
}

void loop(){
  digitalWrite(TRIGPIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                   // Send pin low again
  int distance = pulseIn(ECHOPIN, HIGH);        // Read in times pulse
  distance= distance/58;                        // Calculate distance from time of pulse
  Serial.println(distance);                     
  delay(500);                                    // Wait 50mS before next ranging


  if(distance < 150 && distance > 50){
    Serial.println("lower then 100");
    tone(BUZZER,1000,200);
    delay(400);
  }

  if(distance < 70 && distance > 30){
    Serial.println("lower then 50");
    tone(BUZZER,1000,200);
    delay(200);
  }

  if(distance < 30){
    Serial.println("lower then 10");
    tone(BUZZER,1000,200);
    delay(10);
  }
  
  
}
