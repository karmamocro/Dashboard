// drawCircle example
 
#include <TouchScreen.h>
#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>

// Colors
#define LIGHT_YELLOW 0xebcb8b
#define LIGHT_GREEN 0xa3be8c
#define BACKGROUND 0x0

// Maximum amount of buttons on the screen
#define MAX_BUTTONS 6

// Maximum amount of presets
#define MAX_PRESETS 4

// Preset frequencies
int m_PresetFrequencies_MO[] = {
  394,    // 107.20
  60,     //  90.50
  238,    //  99.40
  296     // 102.30
};


// Touch screen
TouchScreen m_TouchScreen_MO = TouchScreen(XM, YM, XP, YP);


// Buttons
void (*m_ButtonCallbacks_MO[MAX_BUTTONS])();
int m_ButtonX0_MO[MAX_BUTTONS];
int m_ButtonX1_MO[MAX_BUTTONS];
int m_ButtonY0_MO[MAX_BUTTONS];
int m_ButtonY1_MO[MAX_BUTTONS];

int m_ButtonCount_MO = 0;

 
void setup()
{
  Serial.begin(115200);
     // Turn on the display backlight
  TFT_BL_ON;

  // Initialize the display
  Tft.TFTinit();
  Tft.fillScreen(0, 240, 0, 420, BACKGROUND);

  // Draw the frequency buttons
  Tft.drawString("Buttons", 5, 50, 2, RED);
  createButton("UP ", 5, 75, LIGHT_GREEN, channelUp);
  createButton("Down ", 64, 75, LIGHT_GREEN, channelDown);



}
 
void loop()
{
  
   Point point_MO = m_TouchScreen_MO.getPoint();

  point_MO.x = 230 - map(point_MO.x, MIN_X, MAX_X, 240, 0);
  point_MO.y = 340 - map(point_MO.y, MIN_Y, MAX_Y, 320, 0);

  if (point_MO.x < 0) {
    point_MO.x = 0;
  }

  if (point_MO.y < 0) {
    point_MO.y = 0;
  }
  
  if (point_MO.z > m_TouchScreen_MO.pressureThreshhold) {
    for (int i = 0; i < m_ButtonCount_MO; ++i) {
      if ((point_MO.x >= m_ButtonX0_MO[i] && point_MO.x <= m_ButtonX1_MO[i]) && (point_MO.y >= m_ButtonY0_MO[i] && point_MO.y <= m_ButtonY1_MO[i])) {
        m_ButtonCallbacks_MO[i]();
      }
    }
  }
  
}

void setPreset() {
  Point point_MO = m_TouchScreen_MO.getPoint();

  point_MO.x = 230 - map(point_MO.x, MIN_X, MAX_X, 240, 0);
  point_MO.y = 340 - map(point_MO.y, MIN_Y, MAX_Y, 320, 0);

  if (point_MO.x < 0) {
    point_MO.x = 0;
  }

  if (point_MO.y < 0) {
    point_MO.y = 0;
  }
  
  if (point_MO.z > m_TouchScreen_MO.pressureThreshhold) {
    for (int i = 0; i < m_ButtonCount_MO; ++i) {
      if ((point_MO.x >= m_ButtonX0_MO[i] && point_MO.x <= m_ButtonX1_MO[i]) && (point_MO.y >= m_ButtonY0_MO[i] && point_MO.y <= m_ButtonY1_MO[i])) {


      }
    }
  }
}



void createButton(String text, int x, int y, int color, void (*callback)(void)) {
  int width = text.length() * 12 + 20;
  int height = 35;
  
  Tft.fillRectangle(x, y, width, height, color);
  Tft.drawString(text.c_str(), x + 10, y + 10, 2, WHITE);

  m_ButtonX0_MO[m_ButtonCount_MO] = x;
  m_ButtonX1_MO[m_ButtonCount_MO] = x + width;
  
  m_ButtonY0_MO[m_ButtonCount_MO] = y;
  m_ButtonY1_MO[m_ButtonCount_MO] = y + height;
  
  m_ButtonCallbacks_MO[m_ButtonCount_MO] = callback;

  m_ButtonCount_MO++;

  delay(50);
}

void channelUp(){
  Serial.println("up");
}

void channelDown(){
  Serial.println("down");
}

