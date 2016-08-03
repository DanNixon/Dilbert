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
private:

	static const int starCount = 100; /* Number of Stars */
	struct Star stars[starCount];
	long last_ran = millis();
	int framedelay = 150;
	float zoom = .1; /* Speed of forward motion (% of distance from centre point to add each frame) */
	int speed = 10; /* No of pixels to travel for each frame in L/R/U/D modes */
	int mode = 5; /* Direction of travel (relates to button IDs) */
	
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
	
	
	for(int a = 0; a < starCount; a++)
	{
		stars[a].col = random(16777215);
		stars[a].x = random(240);
		stars[a].y = random(320);
		m_badge->display().drawPixel(int(stars[a].x), int(stars[a].y), stars[a].col);
	}
	

	
  }

	virtual void run()
	{
		App::run();
		
		if(millis() >= last_ran + framedelay)
		{
			last_ran = millis();
			for(int a = 0; a < starCount; a++)
			{
				m_badge->display().drawPixel(int(stars[a].x), int(stars[a].y), 0);
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
					if(stars[a].x < 0 or stars[a].x >= 240)
					{
						stars[a].x = random(240);
						stars[a].col = random(16777215);
					}
					stars[a].y += (stars[a].y - 160) * zoom;
					if(stars[a].y < 0 or stars[a].y >= 320)
					{
						stars[a].y = random(320);
						stars[a].col = random(16777215);
					}
				}
				m_badge->display().drawPixel(int(stars[a].x), int(stars[a].y), stars[a].col);
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

    /* Output some details about the buttons */
    if (button->isActive())
    {
			mode = button->getID();
    }
    else
    {
    }

    return true;
  }
  
protected:
 
};

#endif
