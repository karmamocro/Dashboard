//29mar2016
//based on 13jan2014 version
//donwsized to basics

#include <Wire.h>

int radio_Channel = 0;
int freqWord = 0;

//Buttons aan een pin toewijzen
const int btnChannelUp = 10;
const int btnChannelDown = 11;
const int btnUpdate = 12;

int btnChannelUpState = 0;
int btnChannelDownState = 0;
int btnUpdateState = 0;

//byte array
byte m_i2cData[26];
byte volume;
byte treble;
byte bass;

//digital outputs
byte radio_PLL0 = 0x55;
byte radio_PLL1 = 0xAA;
byte tempPllLsb;

//analog inputs
int potmeter = 0;
const int potpin0 = A0;
int potmeter1 = 0;
const int potpin1 = A1;

//LED toewijzen aan pinnen
const int doLedD5 = 5;
const int doLedD6 = 6;

const int doBuzz = 3;

void xsetup()
{
  Serial.begin(9600);
  Serial.println("init");
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  pinMode(btnChannelUp, INPUT);
  pinMode(btnChannelDown, INPUT);
  pinMode(btnUpdate, INPUT);

  digitalWrite(btnChannelUp, HIGH);
  digitalWrite(btnChannelDown, HIGH);
  digitalWrite(btnUpdate, HIGH);

  pinMode(doBuzz, OUTPUT);

  Serial.println("init");

  initDefaults();

  Beep(true);
}

void loop()
{
  forceUpdateDevice();

  changeFreq();

  
  changeVolume();
}

//c file

void Radio::testLeds()
{
  digitalWrite(doLedD5, HIGH);
  delay(500);
  digitalWrite(doLedD5, LOW);
  delay(500);
  digitalWrite(doLedD5, HIGH);
  delay(500);
  digitalWrite(doLedD5, LOW);
}

void Radio::Beep(boolean a_On)
{
  if (a_On)
  {
    tone(doBuzz, 2000);
    delay(50);
    noTone(doBuzz);
  }
  else
  {
    noTone(doBuzz);
  }
}

void Radio::forceUpdateDevice()
{
  if (digitalRead(btnUpdate) == true)
  {
    //Serial.println("down");
  }
  else
  {
    setDeviceInformation();
  }
}

void  Radio::changeFreq()
{
  String m_logData;

  if (digitalRead(btnChannelUp) == false)
  {
    digitalWrite(doLedD5, HIGH);

    freqWord++;
    m_logData = "Up: ";// + freqWord;
    Serial.println(m_logData);
    Serial.println(freqWord);

    prepFreq();
    setDeviceInformation();

    delay(200);
  }
  else
  {
    digitalWrite(doLedD5, LOW);
  }

  if (digitalRead(btnChannelDown) == false)
  {
    digitalWrite(doLedD6, HIGH);

    freqWord--;
    m_logData = "down:";// + freqWord;
    Serial.println("down:" + freqWord);
    Serial.println(freqWord);

    prepFreq();
    setDeviceInformation();

    delay(200);
  }
  else
  {
    digitalWrite(doLedD6, LOW);
    //setDeviceInformation();
  }
}

void changePllLsb()
{
  potmeter = analogRead(potpin0);

  potmeter = map(potmeter, 0, 1023, 0, 255);
  tempPllLsb = (byte)potmeter;

  //Serial.println(tempPllLsb);
}

void  Radio::changeVolume()
{
  potmeter1 = analogRead(potpin1);

  volume = map(potmeter1, 0, 1023, 0, 127);//CRPR1

  //Serial.println("volume is:");
  //Serial.print(volume, HEX);
}

void  Radio::prepFreq()
{
  int m_freqWord;
  double m_freq;
  String m_data;

  if (freqWord > 410)
  {
    freqWord = 0;
  }

  if (freqWord < 0)
  {
    freqWord = 410;
  }

  m_freqWord = freqWord;

  m_freq = (((double) (m_freqWord) * 0.05) + 87.500);
  Serial.println("frequency is:");
  Serial.println(m_freq);

  if ((m_freq >= 87.5) && (m_freq <= 108))
  {
    m_freqWord = (int)  (m_freq * 100);
    m_freqWord = (int) ((m_freqWord - 8750) / 5);
    m_freqWord = (int) ((m_freqWord + 1964) & 0xFFFF);

    radio_PLL0 = (byte)((m_freqWord >> 8) & 0xFF);
    radio_PLL1 = (byte)(m_freqWord & 0xFF);
  }

  m_data = "PLL0";// + radio_PLL0;
  Serial.println(m_data);
  Serial.println(radio_PLL0);

  m_data = "PLL1";// + radio_PLL1;
  Serial.println(m_data);
  Serial.println(radio_PLL1);
}

void initDefaults()
{
  freqWord = 0;

  radio_PLL0 = 0x07;
  radio_PLL1 = 0xAF;

  volume = 0x35;
  treble = 0x0C;
  bass = 0x0c;

  setDeviceInformation();
}

void setDeviceInformation()
{
  //init sequence received from Erik-Jan Otto
  //device address niet in array, gebeurt door wire.begintrans..
  //init sequence received from Erik-Jan Otto
  m_i2cData[0] = 0x20;//Device address radio
  //hierna alleen radio
  m_i2cData[1] = 0xFE; //USB–i2c device
  m_i2cData[2] = radio_PLL0;//0x07;//Channel
  m_i2cData[3] = radio_PLL1;//0xAE;//tempPllLsb;//Channel
  m_i2cData[4] = 0x2C;//0x40;//DAA
  m_i2cData[5] = 0x00;//AGC
  m_i2cData[6] = 0x20;//BAND
  m_i2cData[7] = 0x53;//0x84;//LEVELALIGN
  m_i2cData[8] = 0x25;//0x20;//IFCF
  m_i2cData[9] = 0x08;//0x06;//IFCAP
  m_i2cData[10] = 0x0A;//ACD
  m_i2cData[11] = 0x75;//0x85;//SENSE
  m_i2cData[12] = 0x66;//TIMING
  m_i2cData[13] = 0x74;//SNC
  m_i2cData[14] = 0x6F;//HIGHCUT
  m_i2cData[15] = 0x6A;//SOFTMUTE
  m_i2cData[16] = 0x1A;//RADIO
  m_i2cData[17] = 0x00;//INPUT
  m_i2cData[18] = volume;//Volume
  m_i2cData[19] = treble;//Treble
  m_i2cData[20] = bass;//Bass
  m_i2cData[21] = 0x00;//FADER
  m_i2cData[22] = 0x00;//OUTPUT
  m_i2cData[23] = 0x00;//0x80;//BALANCE
  m_i2cData[24] = 0x0C;//LOUDNESS
  m_i2cData[25] = 0x16;//POWER

  Wire.beginTransmission(0x61);   //writing TEF6901

  for (int m_byteNr = 0; m_byteNr < 26; m_byteNr++)
  {
    Wire.write(m_i2cData[m_byteNr]);
  }

  Wire.endTransmission();

  Serial.println("update radio data");
}

}
//header file
//dit moet naar een .h file
class  Radio
{
    public
      void changeFreq();
      void changeVolume();
    private
      void prepFreq();
      int  test;
};











