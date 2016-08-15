/*! @file */

#include "DebugApp.h"

#include <ESP8266WiFi.h>

/**
 * @brief Creates a debugging application.
 */
DebugApp::DebugApp()
    : App("Debug")
{
}

DebugApp::~DebugApp()
{
}

/**
 * @copydoc App::onEntry
 */
void DebugApp::onEntry()
{
  App::onEntry();

  /* Clear the screen */
  m_badge->display().fillScreen(ILI9341_BLACK);

  m_badge->display().setCursor(0, 0);

  /* Draw header */
  m_badge->display().setTextColor(ILI9341_YELLOW);
  m_badge->display().setTextSize(3);
  m_badge->display().println("Debug\n");

  m_badge->display().setTextSize(2);
  m_badge->display().setTextColor(ILI9341_BLUE);

  /* Draw free heap space */
  m_badge->display().print(ESP.getFreeHeap());
  m_badge->display().println("B free heap");

  /* Draw station IP */
  m_badge->display().print("IP: ");
  m_badge->display().println(WiFi.localIP());

  m_badge->display().println();

  /* Draw button test header */
  m_badge->display().setTextSize(1);
  m_badge->display().setTextColor(ILI9341_RED);
  m_badge->display().println("Button test:");
}

/**
 * @copydoc App::handleButton
 */
bool DebugApp::handleButton(IButton *button)
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
