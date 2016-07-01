/*! @file */

#ifndef _DEMOAPP_H_
#define _DEMOAPP_H_

#include <App.h>

/**
 * @class DemoApp
 * @author Dan Nixon
 * @brief Demo app that reports button presses/releases.
 */
class DemoApp : public App
{
public:
  /**
   * @brief Creates a demo application.
   * @param name Name of the app
   */
  DemoApp(char *name)
      : App(name)
  {
  }

  virtual ~DemoApp()
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

    /* Set font style */
    /* It is important for each app to do this here */
    m_badge->display().setCursor(0, 0);
    m_badge->display().setTextColor(ILI9341_PINK);
    m_badge->display().setTextSize(2);

    m_badge->display().println("Entered demo app");
    m_badge->display().println(m_name);
    m_badge->display().println();

    m_badge->display().setTextSize(1);

    m_badge->display().println("Long press B to return to app menu");
    m_badge->display().println();
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
      m_badge->display().print("Button ");
      m_badge->display().print(button->getID());
      m_badge->display().println(" pressed");
    }
    else
    {
      m_badge->display().print("Button ");
      m_badge->display().print(button->getID());
      m_badge->display().print(" released after ");
      m_badge->display().print(button->lastActiveDuration());
      m_badge->display().println("ms.");
    }

    return true;
  }
};

#endif
