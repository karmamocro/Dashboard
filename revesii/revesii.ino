// Paint application - Demonstate both TFT and Touch Screen
#include <stdint.h>
#include <SeeedTouchScreen.h>
#include <TFTv2.h>
#include <SPI.h>

int buttonLaatsteHoogteELHo = 320;
int ColorPaletteHigh = 30;
int color = WHITE;  //Paint brush color
unsigned int colors[8] = {BLACK, RED, GREEN, BLUE, CYAN, YELLOW, WHITE, GRAY1};

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// The 2.8" TFT Touch shield has 300 ohms across the X plate

TouchScreen ts = TouchScreen(XP, YP, XM, YM); //init TouchScreen port pins

#define LIGHT_YELLOW 0xebcb8b
#define LIGHT_GREEN 0xa3be8c
#define BACKGROUND 0x0

// Maximum amount of buttons on the screen
#define MAX_BUTTONS 6

// Buttons
void (*m_ButtonCallbacks_MO[MAX_BUTTONS])();
int m_ButtonX0_MO[MAX_BUTTONS];
int m_ButtonX1_MO[MAX_BUTTONS];
int m_ButtonY0_MO[MAX_BUTTONS];
int m_ButtonY1_MO[MAX_BUTTONS];

int m_ButtonCount_MO = 0;

void setup()
{
    Tft.TFTinit();  //init TFT library
    Serial.begin(115200);
    //Draw the pallet
    for(int i = 0; i<8; i++)
    {
        Tft.fillRectangle(i*30, 0, 30, ColorPaletteHigh, colors[i]);
    }


  createButton("Test ", 0, 280, LIGHT_GREEN, channelDown);
}

void channelDown(){
  Serial.println("test");
}


void loop()
{
    // a point object holds x y and z coordinates.
    Point p = ts.getPoint();

    //map the ADC value read to into pixel co-ordinates

    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!

    if (p.z > __PRESURE) {
        // Detect  paint brush color changem
        if(p.y < ColorPaletteHigh+2)
        {
            color = colors[p.x/30];
            Serial.println(p.y);
            Serial.println(buttonLaatsteHoogteELHo);
        }
        if(p.y > 285){
          Serial.println("laatste button");
          Serial.println(p.y);
          Serial.println(buttonLaatsteHoogteELHo);
        }
        else
        {
            Tft.fillCircle(p.x,p.y,2,color);
            Serial.println(p.y);
            Serial.println("else");
        }
    }
}

void createButton(String text, int x, int y, int color, void (*callback)(void)) {
  int width = buttonLaatsteHoogteELHo;//text.length() * 12 + 20;
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
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
