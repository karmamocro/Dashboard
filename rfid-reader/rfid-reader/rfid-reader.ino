/****************************************************************
 *                  Arduino RFID ID-12LA example code            *
 *     by Dick van Kalsbeek, ROC ter AA, Helmond, 20feb2015      *
 *****************************************************************/
 
 //LET OP!!!
 //uploaden van de code is alleen mogelijk als de RFID chip communicatielijn los ligt.

//data wordt in losse bytes (strings) gestuurd naar de serial monitor
//als de C# applicatie ArduinoConnectionBasics wordt gebruikt,
//dan is de # de start en de % het einde van de string
//in de C# applicatie is hierop een check
byte rfIdDataByte = 0;
byte nrOfBytesRead = 0;
String rfIdDataString;

//#define USESERIALMONITOR
#define ALSOSEPARATEDATA

void setup()
{
  Serial.begin(9600);

  nrOfBytesRead = 0;
  rfIdDataString = "#";
}

void loop()
{
  if (Serial.available() > 0)
  {
    rfIdDataByte = Serial.read();

    rfIdDataString = rfIdDataString +  (String)rfIdDataByte + ">";
#ifdef ONLYTOTALSTRING
    if (rfIdDataByte != 255)
    {
      Serial.println(rfIdDataByte);
    }
#endif
    nrOfBytesRead++;
  }

#ifdef USESERIALMONITOR
  if (nrOfBytesRead == 16)
  {
    Serial.println("");
    nrOfBytesRead = 0;
  }
#endif

  if (nrOfBytesRead == 16)
  {
    rfIdDataString = rfIdDataString + "%";
    Serial.println(rfIdDataString);
    rfIdDataString = "#";
    nrOfBytesRead = 0;
  }
}







