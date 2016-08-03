/*! @file */

#include "MenuApp.h"

#define OFFSET(a, d) (((m_itemSize + 1) * d) * a)
#define OFFSET_X(x) OFFSET(x, 6)
#define OFFSET_Y(y) OFFSET(y, 8)

#define MENU_START_Y 50

/**
 * @brief Creates a new menu application.
 * @param itemSize Size of text for menu items (multiples of 8 pixels)
 * @param bgColour Background colour
 * @param textColour Text colour
 * @param iconColour CUrrent app selection colour
 */
MenuApp::MenuApp(uint8_t itemSize, uint16_t bgColour, uint16_t textColour, uint16_t iconColour)
    : App("App Menu")
    , m_itemSize(itemSize)
    , m_textColour(textColour)
    , m_iconColour(iconColour)
    , m_selectedAppIndex(0)
{
  setBackgroundColour(bgColour);
}

MenuApp::~MenuApp()
{
}

/**
 * @copydoc App::create
 */
void MenuApp::create()
{
  App::create();
  m_selectedAppIndex = 0;
}

/**
 * @copydoc App::onEntry
 */
void MenuApp::onEntry()
{
  App::onEntry();

  Adafruit_ILI9341 &display = m_badge->display();

  display.setTextColor(m_textColour);

  /* Print title */
  display.setCursor(0, 0);
  display.setTextSize(4);
  display.print("Dilbert");
  display.setTextSize(2);
  display.println(" Apps");

  display.setTextSize(m_itemSize);

  /* Print application names */
  for (uint8_t i = 0; i < m_manager->numApps(); i++)
  {
    display.setCursor(OFFSET_X(1), MENU_START_Y + OFFSET_Y(i));
    display.print(m_manager->app(i)->name());
  }

  redrawSelectonIcon();
}

/**
 * @copydoc App::handleButton
 */
bool MenuApp::handleButton(IButton *button)
{
  if (App::handleButton(button))
    return true;

  if (!button->isActive())
  {
    switch (button->getID())
    {
    case Dilbert::BUTTON_DOWN:
      /* Next item */
      m_selectedAppIndex++;
      if (m_selectedAppIndex >= m_manager->numApps())
        m_selectedAppIndex = 0;
      redrawSelectonIcon();
      break;

    case Dilbert::BUTTON_UP:
      /* Previous item */
      if (m_selectedAppIndex == 0)
        m_selectedAppIndex = m_manager->numApps();
      m_selectedAppIndex--;
      redrawSelectonIcon();
      break;

    case Dilbert::BUTTON_B:
      /* First item */
      m_selectedAppIndex = 0;
      redrawSelectonIcon();
      break;

    case Dilbert::BUTTON_A:
      /* Launch selected app */
      m_manager->activateAppByIdx(m_selectedAppIndex);
      return true;

    default:
      return false;
    }

    return true;
  }

  return false;
}

/**
 * @brief Redraws the selected application icon.
 */
void MenuApp::redrawSelectonIcon()
{
  /* Clear display around selection arow position */
  m_badge->display().fillRect(0, MENU_START_Y, OFFSET_X(1) - 1, 319, ILI9341_BLACK);

  /* Draw selection arrow */
  m_badge->display().setTextColor(m_iconColour);
  m_badge->display().setCursor(1, MENU_START_Y + OFFSET_Y(m_selectedAppIndex));
  m_badge->display().print(">");
}
