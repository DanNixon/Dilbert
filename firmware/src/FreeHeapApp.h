/*! @file */

#ifndef _FREEHEAPAPP_H_
#define _FREEHEAPAPP_H_

#include <App.h>

/**
 * @class FreeHeapApp
 * @author Dan Nixon
 * @brief Shows the amount of free heap memory.
 */
class FreeHeapApp : public App
{
public:
  /**
   * @brief Creates a buton test application.
   */
  FreeHeapApp()
      : App("Free Heap")
  {
  }

  virtual ~FreeHeapApp()
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

    /* Draw header*/
    m_badge->display().setCursor(0, 0);
    m_badge->display().setTextColor(ILI9341_WHITE);
    m_badge->display().setTextSize(2);
    m_badge->display().println("Free Heap Space");

    m_badge->display().setTextSize(1);

    update();
  }

  /**
   * @copydoc App::handleButton
   */
  virtual bool handleButton(IButton *button)
  {
    if (App::handleButton(button))
      return true;

    /* Update the value when A is pressed */
    if (button->isActive() && button->getID() == Dilbert::BUTTON_A)
    {
      update();
      return true;
    }

    return false;
  }

private:
  /**
   * @brief Updates the current displayed value for heap usage.
   */
  void update()
  {
    m_badge->display().print(ESP.getFreeHeap());
    m_badge->display().println("MB");
  }
};

#endif
