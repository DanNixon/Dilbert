/*! @file */

#include "FlanNoTsubasa.h"

FlanNoTsubasa::FlanNoTsubasa()
    : App("Flan no Tsubasa")
{
}

FlanNoTsubasa::~FlanNoTsubasa()
{
}

/**
 * @copydoc App::onEntry
 */
void FlanNoTsubasa::onEntry()
{
  App::onEntry();

  /* Clear the screen */
  m_badge->display().fillScreen(ILI9341_BLACK);

  m_badge->display().setCursor(0, 0);

  /* Draw header */
  m_badge->display().setTextColor(ILI9341_RED);
  m_badge->display().setTextSize(3);
  m_badge->display().println("Flan no Tsubasa\n");

  /* TODO */
}

/**
 * @copydoc App:onExit
 */
void FlanNoTsubasa::onExit()
{
  App::onExit();

  m_badge->neoPixels().setBrightness(0);
  m_badge->neoPixels().show();
}

/**
 * @copydoc App::handleButton
 */
bool FlanNoTsubasa::handleButton(IButton *button)
{
  if (App::handleButton(button))
    return true;

  /* TODO */
  return false;
}

/**
 * @copydoc App:run
 */
void FlanNoTsubasa::run()
{
  /* TODO */
}
