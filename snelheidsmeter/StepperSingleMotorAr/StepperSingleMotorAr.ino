
//created by: Dick van Kalsbeek, ROC ter AA, Helmond, 20jan2016
//controlling 4 steppermotors by using the Sparkfun steppermotordriver

int doDirPin0  = 6;
int doStepPin0 = 7;

int stepDelayInUs = 800; //delay too short will stall motor

void setup()
{
  Serial.begin(9600);

  pinMode(doDirPin0, OUTPUT);
  pinMode(doStepPin0, OUTPUT);
}
void loop()
{
  ControlMotors();
}

void ControlMotors()
{
  BackWard();
  ForWard();
}

void BackWard()
{
  int i;

  digitalWrite(doDirPin0, LOW);                         // Set the direction.

  delay(1000);

  for (i = 0; i <= 16000; i++)                          // Iterate for i microsteps.
  {
    {
      digitalWrite(doStepPin0, LOW);                    // This LOW to HIGH change is what creates the
      digitalWrite(doStepPin0, HIGH);                   // "Rising Edge" so the easydriver knows to when to step.
    }
    delayMicroseconds(stepDelayInUs);                   // This delay time is close to top speed for this
  }                                                     // particular motor. Any faster the motor stalls.;
}

void ForWard()
{
  int i;

  digitalWrite(doDirPin0, HIGH);     // Set the direction.

  delay(1000);

  for (i = 0; i <= 16000; i++)     // Iterate for i microsteps
  {
    {
      digitalWrite(doStepPin0, LOW);  // This LOW to HIGH change is what creates the
      digitalWrite(doStepPin0, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    }
    delayMicroseconds(stepDelayInUs); // This delay time is close to top speed for this
  }                                   // particular motor. Any faster the motor stalls.
}
