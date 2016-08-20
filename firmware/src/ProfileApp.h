/*! @file */

#ifndef _PROFILEAPP_H_
#define _PROFILEAPP_H_

#include <StaticDisplayApp.h>

#define PROFILE_DAN
/* #define PROFILE_ALISTAIR */
/* #define PROFILE_JON */

/**
 * @class ProfileApp
 * @author Dan Nixon
 * @brief Displays profile/contact information on the display.
 *
 * Make sure to uncomment the correct macro for whoever you are.
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
#ifdef PROFILE_DAN
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
#endif

#ifdef PROFILE_ALISTAIR
    m_badge->display().setTextColor(ILI9341_YELLOW);
    m_badge->display().setTextSize(4);
    m_badge->display().println("Alistair\n");

    m_badge->display().setTextSize(3);
    m_badge->display().setTextColor(ILI9341_CYAN);
    m_badge->display().println("@alistair");
    m_badge->display().setTextColor(ILI9341_BLUE);
    m_badge->display().println("agm.me.uk\n");

    m_badge->display().setTextColor(ILI9341_RED);
    m_badge->display().setTextSize(3);
    m_badge->display().println("Gibberish\nspeaker from the north\neast.");
#endif

#ifdef PROFILE_JON
    m_badge->display().setTextColor(ILI9341_YELLOW);
    m_badge->display().setTextSize(6);
    m_badge->display().println("Jon\nDavies\n");

    m_badge->display().setTextSize(3);
    m_badge->display().setTextColor(ILI9341_CYAN);
    m_badge->display().println("@jondavies");
    m_badge->display().setTextColor(ILI9341_BLUE);
    m_badge->display().println("fb: jonpd\n");

    m_badge->display().setTextColor(ILI9341_RED);
    m_badge->display().setTextSize(3);
    m_badge->display().println("Network nut.");
#endif
  }

  /**
   * @copydoc StaticDisplayApp::drawLandscape
   */
  virtual void drawLandscape()
  {
#ifdef PROFILE_DAN
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
#endif

#ifdef PROFILE_ALISTAIR
    m_badge->display().setTextColor(ILI9341_YELLOW);
    m_badge->display().setTextSize(5);
    m_badge->display().println("Alistair");

    m_badge->display().setTextSize(3);
    m_badge->display().println();

    m_badge->display().setTextSize(3);
    m_badge->display().setTextColor(ILI9341_CYAN);
    m_badge->display().println("@alistair");
    m_badge->display().setTextColor(ILI9341_BLUE);
    m_badge->display().println("agm.me.uk\n");

    m_badge->display().setTextColor(ILI9341_RED);
    m_badge->display().setTextSize(3);
    m_badge->display().println("Gibberish speaker\nfrom the north\neast.");
#endif

#ifdef PROFILE_JON
    m_badge->display().setTextColor(ILI9341_YELLOW);
    m_badge->display().setTextSize(5);
    m_badge->display().println("Jon Davies");

    m_badge->display().setTextSize(3);
    m_badge->display().println();

    m_badge->display().setTextSize(3);
    m_badge->display().setTextColor(ILI9341_CYAN);
    m_badge->display().println("@jondavies");
    m_badge->display().setTextColor(ILI9341_BLUE);
    m_badge->display().println("facebook: jonpd\n");

    m_badge->display().setTextColor(ILI9341_RED);
    m_badge->display().setTextSize(3);
    m_badge->display().println("Network nut.");
#endif
  }
};

#endif
