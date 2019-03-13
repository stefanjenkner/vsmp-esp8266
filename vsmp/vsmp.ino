
#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>

// ESP8266 ePaper board
GxEPD2_BW < GxEPD2_750, GxEPD2_750::HEIGHT / 2 > display(GxEPD2_750(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16));

#include "frames.h"

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  display.init(115200);

  display.firstPage();
  display.fillScreen(GxEPD_WHITE);
  display.nextPage();
  delay(2000);

  const unsigned char* bitmaps[] = { myBitmap_1, myBitmap_2, myBitmap_3, myBitmap_4, myBitmap_5, myBitmap_6 };

  for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
  {
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
    }
    while (display.nextPage());
    delay(60000);
  }

  display.firstPage();
  display.fillScreen(GxEPD_WHITE);
  while (display.nextPage());

  Serial.println("good bye");

  while (display.nextPage());
  display.powerOff();

}

void loop()
{
}
