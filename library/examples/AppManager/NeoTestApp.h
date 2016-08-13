/*! @file */

#ifndef _NEOTESTAPP_H_
#define _NEOTESTAPP_H_

#include "RainbowChase.h"
#include "RainbowCycle.h"
#include <Adafruit_NeoPixel.h>
#include <App.h>

class NeoTestApp : public App
{
public:
  static const size_t PATTERN_COUNT = 2;

public:
  NeoTestApp()
      : App("NeoTestApp")
  {
  }

  ~NeoTestApp()
  {
  }

  /**
   * @copydoc App:create
   */
  void create()
  {
    m_patterns[0] = new RainbowCycle(m_badge->neoPixels(), 20);
    m_patterns[1] = new RainbowChase(m_badge->neoPixels(), 50);
    m_currentPattern = 0;
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
   * @copydoc App:destroy
   */
  void destroy()
  {
    for (size_t i = 0; i < PATTERN_COUNT; i++)
    {
      if (m_patterns[i])
        delete m_patterns[i];
    }
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
          m_patterns[m_currentPattern]->setBrightness(m_patterns[m_currentPattern]->getBrightness() + 10);
        }
        if (button->getID() == 2)
        { // down
          m_patterns[m_currentPattern]->setBrightness(m_patterns[m_currentPattern]->getBrightness() - 10);
        }
        if (button->getID() == 0)
        { // left
          m_patterns[m_currentPattern]->setBrightness(m_patterns[m_currentPattern]->getBrightness() - 1);
        }
        if (button->getID() == 3)
        { // right
          m_patterns[m_currentPattern]->setBrightness(m_patterns[m_currentPattern]->getBrightness() + 1);
        }
      }
      else
      { // long press
        if (button->getID() == 1)
        { // up
          m_currentPattern++;
        }
        if (button->getID() == 2)
        { // down
          m_currentPattern--;
        }
        m_currentPattern = m_currentPattern >= PATTERN_COUNT
                          ? PATTERN_COUNT - 1
                          : m_currentPattern = m_currentPattern < 0 ? 0 : m_currentPattern;
      }
    }

    return true;
  }

  /**
   * @copydoc App:run
   */
  void run()
  {
    m_patterns[m_currentPattern]->run();
  }

  /**
   * @copydoc App:onExit
   */
  void onExit()
  {
    App::onExit();

    m_badge->neoPixels().setBrightness(0);
    m_badge->neoPixels().show();
  }

private:
  int m_currentPattern = 0;
  NPPattern *m_patterns[PATTERN_COUNT];
};

#endif
