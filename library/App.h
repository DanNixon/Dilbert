/*! @file */

#ifndef _APP_H_
#define _APP_H_

#include <IButton.h>

#include "AppManager.h"

/**
 * @class App
 * @author Dan Nixon
 * @brief Used to encapsulate an individual application.
 */
class App
{
public:
  /**
   * @brief Creates a new instance of a badge application.
   * @param name Name of the application
   */
  App(char *name)
      : m_ready(false)
      , m_backgroundColour(ILI9341_BLACK)
  {
    m_name = new char[strlen(name) + 1]();
    strcpy(m_name, name);
  }

  virtual ~App()
  {
    if (m_ready)
      destroy();
  }

  /**
   * @brief Gets the name of the application.
   * @return Pointer to name
   */
  inline char *name()
  {
    return m_name;
  }

  /**
   * @brief Sets the background fill colour of the display for this
   *        application.
   * @param colour Background colour
   */
  inline void setBackgroundColour(uint16_t colour)
  {
    m_backgroundColour = colour;
  }

  /**
   * @brief Creates the application.
   *
   * Memory allocations should be performed here.
   */
  virtual void create()
  {
    m_ready = true;
  }

  /**
   * @brief Called when the application is entered.
   *
   * Initial state should be set here, particularly for the display.
   */
  virtual void onEntry()
  {
    if (!m_ready)
      create();

    m_badge->display().fillScreen(m_backgroundColour);
  }

  /**
   * @brief Called in a loop while the application is active.
   *
   * Equivalent to `loop()` in Arduino.
   */
  virtual void run()
  {
    delay(50);
  }

  /**
   * @brief Exits the application.
   */
  virtual void exit()
  {
    m_manager->activateAppByIdx(0);
  }

  /**
   * @brief Called when the application exits.
   *
   * Perform any state cleanup here.
   */
  virtual void onExit()
  {
  }

  /**
   * @brief Destroys the application.
   *
   * Memory deallocation should be performed here.
   */
  virtual void destroy()
  {
    m_ready = false;
  }

protected:
  /**
   * @brief Handle button presses.
   * @param button Button that has changed
   * @return True if the button was handled in this function
   */
  virtual bool handleButton(IButton *button)
  {
    return false;
  }

protected:
  friend class AppManager;

  Dilbert *m_badge;      //!< Pointer to badge driver
  AppManager *m_manager; //!< Pointer to application manager

  char *m_name; //!< Name of application
  bool m_ready; //!< If the application has been created

  uint16_t m_backgroundColour; //!< Background colour
};

#endif
