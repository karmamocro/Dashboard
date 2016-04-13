//example for controlling the Honeywell HMC5883L 3 axis digital compass
//created by: Dick van Kalsbeek, ROC Ter AA, Helmond, 27feb2016

//i2c library
#include <Wire.h>

byte directionValues[6];
int nr;

#define HMC588L_INIT

void setup()
{
  Wire.begin();
  Serial.begin(9600);

#ifdef HMC588L_INIT
  //initialize first three registers
  Wire.beginTransmission(0x1e);
  Wire.write(0x00);
  Wire.write(0x70);
  Wire.endTransmission();

  Wire.beginTransmission(0x1e);
  Wire.write(0x01);
  Wire.write(0xA0);
  Wire.endTransmission();

  Wire.beginTransmission(0x1e);
  Wire.write(0x02);
  Wire.write(0x00);
  Wire.endTransmission();
#endif

}

void loop()
{
  read_HMC5883L_XYZ_registers();
}

void read_HMC5883L_XYZ_registers()
{
  int X_assembled;
  int Y_assembled;
  int Z_assembled;

  //WARNING: the send address in Arduino lacks the read/write bit,
  //e.g.: 0x3C in normal operation, in Arduino is 0x1E
  //00111100 >> 0011110
  //the direction(read/write) is set by the wire command
  Wire.beginTransmission(0x1e);
  //set address pointer to first byte of the compass
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.requestFrom(0x1e, 6);
  nr = 0;

  while (Wire.available())
  {
    directionValues[nr] = Wire.read();
    //directionValues[nr] = Wire.receive();
    nr++;
  }

//  X_assembled = directionValues[0] << 8;
//  X_assembled = X_assembled | directionValues[1];
//  Y_assembled = directionValues[4] << 8;
//  Y_assembled = Y_assembled | directionValues[5];
//  Z_assembled = directionValues[3] << 8;
//  Z_assembled = Z_assembled | directionValues[4];

  //Serial.println("X: " + (String)X_assembled);
  //Serial.println("Y: " + (String)Y_assembled);
  //Serial.println("Z: " + (String)Z_assembled);

Serial.println("X: msb:" + (String)directionValues[0] + " lsb:" + (String)directionValues[1]);
Serial.println("Y: msb:" + (String)directionValues[4] + " lsb:" + (String)directionValues[5]);
Serial.println("Z: msb:" + (String)directionValues[2] + " lsb:" + (String)directionValues[3]);
  Serial.println();

  delay(500);
}


