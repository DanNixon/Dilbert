#ifndef _DILBERTAPP_H_
#define _DILBERTAPP_H_

#include <IButton.h>

#include "DilbertAppManager.h"

/**
 * @class DilbertApp
 * @author Dan Nixon
 * @brief Used to encapsulate an individual application.
 */
class DilbertApp
{
public:
  /**
   * @brief Creates a new instance of a badge application.
   * @param name Name of the application
   */
  DilbertApp(char *name)
      : m_ready(false)
  {
    m_name = new char[strlen(name)]();
    strcpy(m_name, name);
  }

  virtual ~DilbertApp()
  {
    if (m_ready)
      destroy();
  }

  /**
   * @brief Gets the name of the application.
   * @return Pointer to name
   */
  char *name()
  {
    return m_name;
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
   * Initial state should be set here.
   */
  virtual void onEntry()
  {
    if (!m_ready)
      create();
  }

  /**
   * @brief Called in a loop while the application is active.
   *
   * Equivalent to `loop()` in Arduino.
   */
  virtual void run() = 0;

  /**
   * @brief Exits the application.
   */
  virtual void exit()
  {
    m_parent->activateAppByIdx(0);
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
   */
  virtual void handleButton(IButton *button)
  {
    /* If the B button was released after being held for 1 second */
    if (button->getID() == Dilbert::BUTTON_B && !button->isActive() && button->lastActiveDuration() > 1000)
      exit();
  }

protected:
  friend class DilbertAppManager;

  Dilbert *m_badge;            //!< Pointer to badge driver
  DilbertAppManager *m_parent; //!<Pointer to application manager
  char *m_name;                //!< Name of application
  bool m_ready;                //!< If the application has been created
};

#endif
