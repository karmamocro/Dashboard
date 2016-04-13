/*****************************************************************
 *                  Arduino CMPS10 example code                  *
 *          CMPS10 running I2C mode with serial monitor          *
 *     by Dick van Kalsbeek, ROC ter AA, Helmond, 20feb2015      *
 *                thanks to: James Henderson                     *
 *****************************************************************/
#include <Wire.h>

#define ADDRESS 0x60                                          // Defines address of CMPS10

void setup()
{
  Wire.begin();   
  Serial.begin(9600);
  Serial.println("Start up finished..");
}

void loop()
{
  byte highByte, lowByte, fine;              // highByte and lowByte store high and low bytes of the bearing and fine stores decimal place of bearing
  byte pitch, roll;                          // Stores pitch and roll values of CMPS10, chars are used because they support signed value
  int bearing;                               // Stores full bearing

  //Serial.println("Start communication with CMPS10..");
  Wire.beginTransmission(ADDRESS);           //starts communication with CMPS10
  Wire.write(2);                              //Sends the register we wish to start reading from
  Wire.endTransmission();

  //Serial.println("Get data from CMPS10..");
  Wire.requestFrom(ADDRESS, 4);              // Request 4 bytes from CMPS10
  while(Wire.available() < 4);               // Wait for bytes to become available

  highByte = Wire.read();           
  lowByte = Wire.read();            
  pitch = (byte)Wire.read();              
  roll = (byte)Wire.read();               

  bearing = ((highByte<<8)+lowByte)/10;      // Calculate full bearing
  fine = ((highByte<<8)+lowByte)%10;         // Calculate decimal place of bearing
  
  Serial.println("#bearing: " + (String)bearing + "\t\t" + "fine: " + (String)fine + "\t\t" + 
                 "pitch: " + (String)pitch + "\t\t" + "roll: " + (String)roll + "%"); 

  delay(100);
}

/*int soft_ver()
 {
 int data;                                      // Software version of  CMPS10 is read into data and then returned
 
 Wire.beginTransmission(ADDRESS);
 // Values of 0 being sent with write need to be masked as a byte so they are not misinterpreted as NULL this is a bug in arduino 1.0
 Wire.write((byte)0);                           // Sends the register we wish to start reading from
 Wire.endTransmission();
 
 Wire.requestFrom(ADDRESS, 1);                  // Request byte from CMPS10
 while(Wire.available() < 1);
 data = Wire.read();           
 
 return(data);
 }*/

