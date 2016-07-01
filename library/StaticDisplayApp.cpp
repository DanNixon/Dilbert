#include "StaticDisplayApp.h"

StaticDisplayApp::StaticDisplayApp(char *name, uint16_t bgColour)
    : DilbertApp(name)
    , m_backgroundColour(bgColour)
{
}

StaticDisplayApp::~StaticDisplayApp()
{
}

void StaticDisplayApp::onEntry()
{
  redraw(0);
}

void StaticDisplayApp::onExit()
{
  m_badge->display().setRotation(0);
}

bool StaticDisplayApp::handleButton(IButton *button)
{
  if (DilbertApp::handleButton(button))
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
