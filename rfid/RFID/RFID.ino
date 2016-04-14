char ID ; //Variable to store the character that was recived from the ID
char TAG = '58007020878F';

void setup()
{
  Serial.begin(9600); //Initiates the serial with baud rate of 9600
}

 void loop ()
{
    if(Serial.available() > 0) //If the serial receive some character
    {
      ID = Serial.read(); //Store on ID variable the received character
      Serial.print(ID); //Print on serial the character received.
    }
}
