/*! @file */

#include "StaticDisplayApp.h"

/**
 * @brief Creates a new static content application.
 * @param name Name of the app
 */
StaticDisplayApp::StaticDisplayApp(char *name)
    : App(name)
{
}

StaticDisplayApp::~StaticDisplayApp()
{
}

/**
 * @copydoc App::onEntry
 */
void StaticDisplayApp::onEntry()
{
  redraw(0);
}

/**
 * @copydoc App::onExit
 */
void StaticDisplayApp::onExit()
{
  m_badge->display().setRotation(0);
}

/**
 * @copydoc App::handleButton
 */
bool StaticDisplayApp::handleButton(IButton *button)
{
  if (App::handleButton(button))
    return true;

  if (!button->isActive())
  {
    switch (button->getID())
    {
    case Dilbert::BUTTON_UP:
      redraw(0);
      break;
    case Dilbert::BUTTON_DOWN:
      redraw(2);
      break;
    case Dilbert::BUTTON_LEFT:
      redraw(3);
      break;
    case Dilbert::BUTTON_RIGHT:
      redraw(1);
      break;
    default:
      return false;
    }

    return true;
  }

  return false;
}

/**
 * @brief Redraws the content at a given orientation.
 * @param orientation Orientation to draw at
 */
void StaticDisplayApp::redraw(uint8_t orientation)
{
  m_badge->display().fillScreen(m_backgroundColour);
  m_badge->display().setRotation(orientation);

  m_badge->display().setCursor(0, 0);

  if (orientation % 2 == 0)
    drawPortrait();
  else
    drawLandscape();
}
