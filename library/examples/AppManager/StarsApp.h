/*! @file */

#ifndef _STARSAPP_H_
#define _STARSAPP_H_

#include <App.h>

struct Star
{
  long col;
  float x;
  float y;
};

/**
 * @class StarsApp
 * @author Iain Yarnall
 * @brief Displays Starfield
 */
class StarsApp : public App
{
public:
  static const int STAR_COUNT = 100; /* Number of Stars */

public:
  StarsApp()
      : App("Stars")
  {
  }

  virtual ~StarsApp()
  {
  }

  /**
   * @copydoc App::onEntry
   */
  virtual void onEntry()
  {
    App::onEntry();
    /* Clear the screen */
    m_badge->display().fillScreen(ILI9341_BLACK);

    for (int a = 0; a < STAR_COUNT; a++)
    {
      m_stars[a].col = random(16777215);
      m_stars[a].x = random(240);
      m_stars[a].y = random(320);
      m_badge->display().drawPixel(int(m_stars[a].x), int(m_stars[a].y), m_stars[a].col);
    }
  }

  virtual void run()
  {
    App::run();

    if (millis() >= m_lastRan + m_frameDelay)
    {
      m_lastRan = millis();
      for (int a = 0; a < STAR_COUNT; a++)
      {
        m_badge->display().drawPixel(int(m_stars[a].x), int(m_stars[a].y), 0);
        if (m_mode == 0) /* LEFT */
        {
          m_stars[a].x += m_speed;
          if (m_stars[a].x >= 240)
          {
            m_stars[a].x = random(m_speed);
            m_stars[a].y = random(320);
            m_stars[a].col = random(16777215);
          }
        }
        else if (m_mode == 1) /* UP */
        {
          m_stars[a].y -= m_speed;
          if (m_stars[a].y < 0)
          {
            m_stars[a].y = 319 - random(m_speed);
            m_stars[a].x = random(240);
            m_stars[a].col = random(16777215);
          }
        }
        else if (m_mode == 2) /* DOWN */
        {
          m_stars[a].y += m_speed;
          if (m_stars[a].y >= 320)
          {
            m_stars[a].y = random(m_speed);
            m_stars[a].x = random(240);
            m_stars[a].col = random(16777215);
          }
        }
        else if (m_mode == 3) /* RIGHT */
        {
          m_stars[a].x -= m_speed;
          if (m_stars[a].x < 0)
          {
            m_stars[a].x = 239 - random(m_speed);
            m_stars[a].y = random(320);
            m_stars[a].col = random(16777215);
          }
        }
        else if (m_mode == 4) /* FORWARDS */
        {
          m_stars[a].x += (m_stars[a].x - 120) * m_zoom;
          if (m_stars[a].x < 0 or m_stars[a].x >= 240)
          {
            m_stars[a].x = random(240);
            m_stars[a].col = random(16777215);
          }
          m_stars[a].y += (m_stars[a].y - 160) * m_zoom;
          if (m_stars[a].y < 0 or m_stars[a].y >= 320)
          {
            m_stars[a].y = random(320);
            m_stars[a].col = random(16777215);
          }
        }
        m_badge->display().drawPixel(int(m_stars[a].x), int(m_stars[a].y), m_stars[a].col);
      }
    }
  }

  /**
  * @copydoc App::handleButton
  */
  virtual bool handleButton(IButton *button)
  {
    if (App::handleButton(button))
      return true;

    if (button->isActive())
    {
      m_mode = button->getID();
      return true;
    }

    return false;
  }

private:
  struct Star m_stars[STAR_COUNT];
  long m_lastRan = millis();
  int m_frameDelay = 150;
  float m_zoom =
      .1; /* Speed of forward motion (% of distance from centre point to add each frame) */
  int m_speed = 10; /* No of pixels to travel for each frame in L/R/U/D modes */
  int m_mode = 5;   /* Direction of travel (relates to button IDs) */
};

#endif
