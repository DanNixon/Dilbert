/*! @file */

#ifndef _PROFILEAPP_H_
#define _PROFILEAPP_H_

#include <StaticDisplayApp.h>

/**
 * @class ProfileApp
 * @author Dan Nixon
 * @brief Displays profile/contact information on the display.
 */
class ProfileApp : public StaticDisplayApp
{
public:
  ProfileApp()
      : StaticDisplayApp("Profile")
  {
  }

  virtual ~ProfileApp()
  {
  }

  /**
   * @copydoc App::run
   */
  virtual void run()
  {
    App::run();

    /* Keep backlight on */
    m_manager->feedBacklight(BACKLIGHT_STATE_DIM);
  }

protected:
  /**
   * @copydoc StaticDisplayApp::drawPortrait
   */
  virtual void drawPortrait()
  {
    m_badge->display().setTextColor(ILI9341_YELLOW);
    m_badge->display().setTextSize(6);
    m_badge->display().println("Dan\nNixon\n");

    m_badge->display().setTextSize(3);
    m_badge->display().setTextColor(ILI9341_CYAN);
    m_badge->display().println("@technoducky");
    m_badge->display().setTextColor(ILI9341_BLUE);
    m_badge->display().println("dan-nixon.com\n");

    m_badge->display().setTextColor(ILI9341_RED);
    m_badge->display().setTextSize(3);
    m_badge->display().println("Code Monkey, Electronics\nEngineer, Mad\nScientist.");
  }

  /**
   * @copydoc StaticDisplayApp::drawLandscape
   */
  virtual void drawLandscape()
  {
    m_badge->display().setTextColor(ILI9341_YELLOW);
    m_badge->display().setTextSize(5);
    m_badge->display().println("Dan Nixon");

    m_badge->display().setTextSize(3);
    m_badge->display().println();

    m_badge->display().setTextSize(3);
    m_badge->display().setTextColor(ILI9341_CYAN);
    m_badge->display().println("@technoducky");
    m_badge->display().setTextColor(ILI9341_BLUE);
    m_badge->display().println("dan-nixon.com\n");

    m_badge->display().setTextColor(ILI9341_RED);
    m_badge->display().setTextSize(3);
    m_badge->display().println("Code Monkey,\nElectronics\nEngineer,\nMad Scientist.");
  }
};

#endif
