/*! @file */

#ifndef _STARSAPP_H_
#define _STARSAPP_H_

#include <App.h>

struct Star
{
  long col;
  float x;
  float y;
  int size;
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
      newRandomStar(a);
      drawStar(a);
    }
  }

  /**
   * @copydoc App:run
   */
  virtual void run()
  {
    App::run();

    /* Keep backlight on */
    m_manager->feedBacklight(BACKLIGHT_STATE_DIM);

    if (millis() >= m_lastRan + m_frameDelay and m_mode != 5)
    {
      m_lastRan = millis();
      for (int a = 0; a < STAR_COUNT; a++)
      {
        hideStar(a);
        if (m_mode == 0) /* LEFT */
        {
          m_stars[a].x += m_speed;
          if (m_stars[a].x >= 240)
          {
            newRandomStar(a);
            m_stars[a].x = random(m_speed);
          }
        }
        else if (m_mode == 1) /* UP */
        {
          m_stars[a].y -= m_speed;
          if (m_stars[a].y < 0)
          {
            newRandomStar(a);
            m_stars[a].y = 319 - random(m_speed);
          }
        }
        else if (m_mode == 2) /* DOWN */
        {
          m_stars[a].y += m_speed;
          if (m_stars[a].y >= 320)
          {
            newRandomStar(a);
            m_stars[a].y = random(m_speed);
          }
        }
        else if (m_mode == 3) /* RIGHT */
        {
          m_stars[a].x -= m_speed;
          if (m_stars[a].x < 0)
          {
            newRandomStar(a);
            m_stars[a].x = 239 - random(m_speed);
          }
        }
        else if (m_mode == 4) /* FORWARDS */
        {
          m_stars[a].x += (m_stars[a].x - 120) * m_zoom;
          m_stars[a].y += (m_stars[a].y - 160) * m_zoom;
          if (m_stars[a].x < 0 or m_stars[a].x >= 240 or m_stars[a].y < 0 or m_stars[a].y >= 320)
          {
            newRandomStar(a);
          }
        }
        drawStar(a);
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

  void newRandomStar(int a)
  {
    m_stars[a].col = random(16777215);
    m_stars[a].size = random(3);
    m_stars[a].size = random(m_stars[a].size);
    do
    {
      m_stars[a].x = random(240);
      m_stars[a].y = random(320);
    } while (m_stars[a].x == 120 and m_stars[a].y == 160);
  }

  void hideStar(int a)
  {
    if (m_stars[a].size == 0)
    {
      m_badge->display().drawPixel(int(m_stars[a].x), int(m_stars[a].y), 0);
    }
    else
    {
      m_badge->display().fillCircle(int(m_stars[a].x), int(m_stars[a].y), m_stars[a].size, 0);
    }
  }

  void drawStar(int a)
  {
    if (m_stars[a].size == 0)
    {
      m_badge->display().drawPixel(int(m_stars[a].x), int(m_stars[a].y), m_stars[a].col);
    }
    else
    {
      m_badge->display().fillCircle(int(m_stars[a].x), int(m_stars[a].y), m_stars[a].size,
                                    m_stars[a].col);
    }
  }
};

#endif
