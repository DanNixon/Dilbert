/*! @file */

#ifndef _NEOTESTAPP_H_
#define _NEOTESTAPP_H_

#include "RainbowChase.h"
#include "RainbowCycle.h"
#include <Adafruit_NeoPixel.h>
#include <App.h>

class NeoTestApp : public App
{
  static const int PIN = 15, PATTERN_COUNT = 2;
  Adafruit_NeoPixel *strip = 0;
  int currPattern = 0;
  NPPattern *patterns[PATTERN_COUNT];

public:
  NeoTestApp()
      : App("NeoTestApp")
  {
    strip = new Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);
    patterns[0] = new RainbowCycle(strip, 20);
    patterns[1] = new RainbowChase(strip, 50);
    currPattern = 0;
  }

  ~NeoTestApp()
  {
    for (int i = 0; i < PATTERN_COUNT; i++)
    {
      if (patterns[i])
        free(patterns[i]);
    }
    if (strip)
      free(strip);
  }

  /**
   * @copydoc App:onEntry
   */
  void onEntry()
  {
    App::onEntry();

    /* Clear the screen */
    m_badge->display().fillScreen(ILI9341_BLACK);

    /* Set font style */
    /* It is important for each app to do this here */
    m_badge->display().setCursor(0, 0);
    m_badge->display().setTextColor(ILI9341_PINK);
    m_badge->display().setTextSize(2);
    m_badge->display().println(m_name);
    m_badge->display().setTextSize(1);
    m_badge->display().print("The classic\nNeopixel strandtest\napp.\n\n");
    m_badge->display().println("Long press B to return to app menu.\n");
  }

  /**
   * @copydoc App:handleButton
   */
  bool handleButton(IButton *button)
  {
    if (App::handleButton(button))
      return true;

    if (!button->isActive())
    { // button released
      if (button->lastActiveDuration() < 800)
      { // short press
        if (button->getID() == 1)
        { // up
          patterns[currPattern]->setBrightness(patterns[currPattern]->getBrightness() + 10);
        }
        if (button->getID() == 2)
        { // down
          patterns[currPattern]->setBrightness(patterns[currPattern]->getBrightness() - 10);
        }
        if (button->getID() == 0)
        { // left
          patterns[currPattern]->setBrightness(patterns[currPattern]->getBrightness() - 1);
        }
        if (button->getID() == 3)
        { // right
          patterns[currPattern]->setBrightness(patterns[currPattern]->getBrightness() + 1);
        }
      }
      else
      { // long press
        if (button->getID() == 1)
        { // up
          currPattern++;
        }
        if (button->getID() == 2)
        { // down
          currPattern--;
        }
        if (button->getID() == 0)
        { // left
        }
        if (button->getID() == 3)
        { // right
        }
        currPattern = currPattern >= PATTERN_COUNT
                          ? PATTERN_COUNT - 1
                          : currPattern = currPattern < 0 ? 0 : currPattern;
      }
    }

    return true;
  }

  /**
   * @copydoc App:run
   */
  void run()
  {
    patterns[currPattern]->run();
  }

  /**
   * @copydoc App:onExit
   */
  void onExit()
  {
    App::onExit();
    strip->setBrightness(0);
    strip->show();
  }
};
#endif
