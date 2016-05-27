#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_MCP23017.h>

#include <Adafruit_ILI9341.h>

#include <Dilbert.h>

/* #define TFT_DEBUG */

Dilbert *badge;

void setup()
{
  badge = new Dilbert();

  Serial.begin(9600);
  Serial.println("Hardware demo");

#ifdef TFT_DEBUG
  uint8_t x;

  x = badge->display().readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x");
  Serial.println(x, HEX);

  x = badge->display().readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x");
  Serial.println(x, HEX);

  x = badge->display().readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x");
  Serial.println(x, HEX);

  x = badge->display().readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x");
  Serial.println(x, HEX);

  x = badge->display().readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x");
  Serial.println(x, HEX);
#endif

  badge->setBacklight(100);

  badge->neoPixels().setBrightness(4);

  badge->neoPixels().setPixelColor(0, Adafruit_NeoPixel::Color(255, 0, 0));
  badge->neoPixels().show();
  badge->neoPixels().setPixelColor(1, Adafruit_NeoPixel::Color(0, 255, 0));
  badge->neoPixels().show();
  badge->neoPixels().setPixelColor(2, Adafruit_NeoPixel::Color(0, 0, 255));
  badge->neoPixels().show();
  badge->neoPixels().setPixelColor(3, Adafruit_NeoPixel::Color(120, 120, 120));
  badge->neoPixels().show();
}

void loop()
{
  badge->display().setCursor(0, 0);

  badge->display().setTextColor(ILI9341_RED);
  badge->display().setTextSize(3);
  badge->display().println("Hello, world!");

  badge->display().println();

  badge->display().setTextColor(ILI9341_BLUE);
  badge->display().setTextSize(3);
  badge->display().println("My name is\nDilbert!");

  badge->display().setCursor(0, 150);

  badge->display().fillRect(0, 150, 240, 20, ILI9341_BLACK);

  badge->display().setTextColor(ILI9341_YELLOW);
  badge->display().setTextSize(2);
  badge->display().println(millis());

  delay(1000);
}
