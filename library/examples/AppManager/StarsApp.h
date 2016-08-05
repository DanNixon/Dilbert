/*! @file */

#ifndef _STARSAPP_H_
#define _STARSAPP_H_

#include <App.h>

<<<<<<< HEAD
	struct Star
	{
		long col;
		float x;
		float y;
		int size;
	};

=======
struct Star
{
  long col;
  float x;
  float y;
};
>>>>>>> refs/remotes/DanNixon/master

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
<<<<<<< HEAD
	/* Clear the screen */
	m_badge->display().fillScreen(ILI9341_BLACK);
	
	
	for(int a = 0; a < starCount; a++)
	{
		newRandomStar(a);
		drawStar(a);
	}
	
=======
    /* Clear the screen */
    m_badge->display().fillScreen(ILI9341_BLACK);
>>>>>>> refs/remotes/DanNixon/master

    for (int a = 0; a < STAR_COUNT; a++)
    {
      m_stars[a].col = random(16777215);
      m_stars[a].x = random(240);
      m_stars[a].y = random(320);
      m_badge->display().drawPixel(int(m_stars[a].x), int(m_stars[a].y), m_stars[a].col);
    }
  }

<<<<<<< HEAD
	virtual void run()
	{
		App::run();
		
		if(millis() >= last_ran + framedelay and mode != 5)
		{
			last_ran = millis();
			for(int a = 0; a < starCount; a++)
			{
				hideStar(a);
				if (mode == 0) /* LEFT */
				{
					stars[a].x += speed;
					if (stars[a].x >= 240)
					{
						stars[a].x = random(speed);
						stars[a].y = random(320);
						stars[a].col = random(16777215);
					}
				}			
				else if (mode == 1) /* UP */
				{
					stars[a].y -= speed;
					if (stars[a].y < 0)
					{
						stars[a].y = 319 - random(speed);
						stars[a].x = random(240);
						stars[a].col = random(16777215);
					}
				}			
				else if (mode == 2) /* DOWN */
				{
					stars[a].y += speed;
					if (stars[a].y >= 320)
					{
						stars[a].y = random(speed);
						stars[a].x = random(240);
						stars[a].col = random(16777215);
					}	
				}			
				else if (mode == 3) /* RIGHT */
				{
					stars[a].x -= speed;
					if (stars[a].x < 0)
					{
						stars[a].x = 239 - random(speed);
						stars[a].y = random(320);
						stars[a].col = random(16777215);
					}
				}			
				else if (mode == 4) /* FORWARDS */
				{
					stars[a].x += (stars[a].x - 120) * zoom;
					stars[a].y += (stars[a].y - 160) * zoom;
					if(stars[a].x < 0 or stars[a].x >= 240 or stars[a].y < 0 or stars[a].y >= 320)
					{
						newRandomStar(a);
					}
				}
				drawStar(a);
			}
		}
=======
  virtual void run()
  {
    App::run();
>>>>>>> refs/remotes/DanNixon/master

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
<<<<<<< HEAD
  
  void newRandomStar(int a)
  {
	stars[a].col = random(16777215);
	stars[a].size = random(3);
	stars[a].size = random(stars[a].size);
	do
	{
		stars[a].x = random(240);
		stars[a].y = random(320);
	} while (stars[a].x == 120 and stars[a].y == 160);
  }
  
  void hideStar(int a)
  {
	if(stars[a].size == 0)
	{
		m_badge->display().drawPixel(int(stars[a].x), int(stars[a].y), 0);
	}
	else
	{
		m_badge->display().fillCircle(int(stars[a].x), int(stars[a].y), stars[a].size, 0);
	} 
  }

  void drawStar(int a)
  {
	if(stars[a].size == 0)
	{
		m_badge->display().drawPixel(int(stars[a].x), int(stars[a].y), stars[a].col);
	}
	else
	{
		m_badge->display().fillCircle(int(stars[a].x), int(stars[a].y), stars[a].size, stars[a].col);
	} 
  }
  
protected:
 
=======

private:
  struct Star m_stars[STAR_COUNT];
  long m_lastRan = millis();
  int m_frameDelay = 150;
  float m_zoom =
      .1; /* Speed of forward motion (% of distance from centre point to add each frame) */
  int m_speed = 10; /* No of pixels to travel for each frame in L/R/U/D modes */
  int m_mode = 5;   /* Direction of travel (relates to button IDs) */
>>>>>>> refs/remotes/DanNixon/master
};

#endif
