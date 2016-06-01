/**
 * Authors:  Erik Verstegen & Jacob van Eijk
 * Date:  04/14/2016
 * Class: IC.14AO.a
 */

#include <TouchScreen.h>
#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>

// Maximum amount of buttons on the screen
#define MAX_BUTTONS 6

// Maximum amount of presets
#define MAX_PRESETS 4


// Colors
#define LIGHT_YELLOW 0xebcb8b
#define LIGHT_GREEN 0xa3be8c
#define BACKGROUND 0x0

// Screen coordinates
#define MIN_X 140
#define MAX_X 900
#define MIN_Y 120
#define MAX_Y 940


// Buttons
void (*m_ButtonCallbacks_ELHo[MAX_BUTTONS])();
int m_ButtonX0_ELHo[MAX_BUTTONS];
int m_ButtonX1_ELHo[MAX_BUTTONS];
int m_ButtonY0_ELHo[MAX_BUTTONS];
int m_ButtonY1_ELHo[MAX_BUTTONS];

int m_ButtonCount_ELHo = 0;

// Touch screen
TouchScreen m_TouchScreen_ELHo = TouchScreen(XM, YM, XP, YP);

void setup() {
  Serial.begin(9600);

  // Turn on the display backlight
  TFT_BL_ON;

  // Initialize the display
  Tft.TFTinit();
  Tft.fillScreen(0, 240, 0, 420, BACKGROUND);

  // Draw the frequency buttons
  Tft.drawString("Frequentie", 5, 50, 2, WHITE);
  createButton("UP", 5, 75, LIGHT_GREEN, channelUp);
  createButton("Down", 64, 75, LIGHT_GREEN, channelDown);

  // Draw the preset frequencies buttons
  Tft.drawString("Voorkeurszenders", 5, 120, 2, WHITE);

 

  // Initialize to defaults
  initializeDefaults();
}

void initializeDefaults()
{
  
 Serial.println("inited");

}

void loop() {
  Point point_ELHo = m_TouchScreen_ELHo.getPoint();

  point_ELHo.x = 230 - map(point_ELHo.x, MIN_X, MAX_X, 240, 0);
  point_ELHo.y = 340 - map(point_ELHo.y, MIN_Y, MAX_Y, 320, 0);

  if (point_ELHo.x < 0) {
    point_ELHo.x = 0;
  }

  if (point_ELHo.y < 0) {
    point_ELHo.y = 0;
  }
  
  if (point_ELHo.z > m_TouchScreen_ELHo.pressureThreshhold) {
    for (int i = 0; i < m_ButtonCount_ELHo; ++i) {
      if ((point_ELHo.x >= m_ButtonX0_ELHo[i] && point_ELHo.x <= m_ButtonX1_ELHo[i]) && (point_ELHo.y >= m_ButtonY0_ELHo[i] && point_ELHo.y <= m_ButtonY1_ELHo[i])) {
        m_ButtonCallbacks_ELHo[i]();
      }
    }
  }
}



void setDeviceInformation()
{
  Serial.println("woeshoem");
}

void createButton(String text, int x, int y, int color, void (*callback)(void)) {
  int width = text.length() * 12 + 20;
  int height = 35;
  
  Tft.fillRectangle(x, y, width, height, color);
  Tft.drawString(text.c_str(), x + 10, y + 10, 2, WHITE);

  m_ButtonX0_ELHo[m_ButtonCount_ELHo] = x;
  m_ButtonX1_ELHo[m_ButtonCount_ELHo] = x + width;
  
  m_ButtonY0_ELHo[m_ButtonCount_ELHo] = y;
  m_ButtonY1_ELHo[m_ButtonCount_ELHo] = y + height;
  
  m_ButtonCallbacks_ELHo[m_ButtonCount_ELHo] = callback;

  m_ButtonCount_ELHo++;
  Serial.println(m_ButtonCount_ELHo);
  delay(50);
}

void channelUp() {

  setDeviceInformation();

  delay(200);
}

void channelDown() {
  setDeviceInformation();

  delay(200);
}

void setPreset() {
  Point point_ELHo = m_TouchScreen_ELHo.getPoint();

  point_ELHo.x = 230 - map(point_ELHo.x, MIN_X, MAX_X, 240, 0);
  point_ELHo.y = 340 - map(point_ELHo.y, MIN_Y, MAX_Y, 320, 0);

  if (point_ELHo.x < 0) {
    point_ELHo.x = 0;
  }

  if (point_ELHo.y < 0) {
    point_ELHo.y = 0;
  }
  
  if (point_ELHo.z > m_TouchScreen_ELHo.pressureThreshhold) {
    for (int i = 0; i < m_ButtonCount_ELHo; ++i) {
      if ((point_ELHo.x >= m_ButtonX0_ELHo[i] && point_ELHo.x <= m_ButtonX1_ELHo[i]) && (point_ELHo.y >= m_ButtonY0_ELHo[i] && point_ELHo.y <= m_ButtonY1_ELHo[i])) {

    
        setDeviceInformation();
      }
    }
  }
}

