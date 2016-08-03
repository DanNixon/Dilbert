/*! @file */

#include "SystemSettingsApp.h"

#include "ConfigService.h"

#define OFFSET(a, d) ((3 * d) * a)
#define OFFSET_X(x) OFFSET(x, 6)
#define OFFSET_Y(y) OFFSET(y, 8)

#define MENU_START_Y 50
#define VALUE_START_Y 54

/**
 * @brief Creates a new system settings application.
 */
SystemSettingsApp::SystemSettingsApp()
    : App("System Settings")
    , m_selectedIndex(0)
{
}

SystemSettingsApp::~SystemSettingsApp()
{
}

/**
 * @copydoc App::create
 */
void SystemSettingsApp::create()
{
  App::create();
  m_selectedIndex = 0;
}

/**
 * @copydoc App::onEntry
 */
void SystemSettingsApp::onEntry()
{
  App::onEntry();

  Adafruit_ILI9341 &display = m_badge->display();

  /* Print title */
  display.setTextColor(ILI9341_WHITE);
  display.setCursor(0, 0);
  display.setTextSize(4);
  display.print("Settings");

  display.setTextSize(2);

  /* Reset option */
  display.setCursor(OFFSET_X(4), MENU_START_Y + OFFSET_Y(0));
  display.print("Load Defaults");

  /* Setting options */
  display.setCursor(OFFSET_X(4), MENU_START_Y + OFFSET_Y(1));
  display.print("Exit delay");
  display.setCursor(OFFSET_X(4), MENU_START_Y + OFFSET_Y(2));
  display.print("BL full");
  display.setCursor(OFFSET_X(4), MENU_START_Y + OFFSET_Y(3));
  display.print("BL dimmed");
  display.setCursor(OFFSET_X(4), MENU_START_Y + OFFSET_Y(4));
  display.print("BL dim delay");
  display.setCursor(OFFSET_X(4), MENU_START_Y + OFFSET_Y(5));
  display.print("BL off delay");

  redraw();
}

/**
 * @copydoc App::handleButton
 */
bool SystemSettingsApp::handleButton(IButton *button)
{
  if (App::handleButton(button))
    return true;

  if (!button->isActive())
  {
    switch (button->getID())
    {
    case Dilbert::BUTTON_DOWN:
      /* Next item */
      m_selectedIndex++;
      if (m_selectedIndex >= NUM_OPTIONS)
        m_selectedIndex = 0;
      redraw();
      break;

    case Dilbert::BUTTON_UP:
      /* Previous item */
      if (m_selectedIndex == 0)
        m_selectedIndex = NUM_OPTIONS;
      m_selectedIndex--;
      redraw();
      break;

    case Dilbert::BUTTON_B:
      /* First item */
      m_selectedIndex = 0;
      redraw();
      break;

    case Dilbert::BUTTON_LEFT:
      /* Decrease */
      /* TODO */
      break;

    case Dilbert::BUTTON_RIGHT:
      /* Increase */
      /* TODO */
      break;

    default:
      return false;
    }

    return true;
  }

  return false;
}

/**
 * @brief Redraws the selected item indicator and setting values.
 */
void SystemSettingsApp::redraw()
{
  Adafruit_ILI9341 &display = m_badge->display();

  /* Clear display around selection arow position */
  display.fillRect(0, MENU_START_Y, OFFSET_X(1) - 1, 319, ILI9341_BLACK);

  /* Draw selection arrow */
  display.setTextSize(2);
  display.setTextColor(ILI9341_YELLOW);
  display.setCursor(1, MENU_START_Y + OFFSET_Y(m_selectedIndex));
  display.print(">");

  SystemConfigData scd = ConfigService::Instance().getConfig();

  /* Draw values */
  display.setTextSize(1);
  display.setTextColor(ILI9341_RED);
  display.setCursor(OFFSET_X(1), VALUE_START_Y + OFFSET_Y(1));
  display.print(scd.backButtonExitDelay);
  display.setCursor(OFFSET_X(1), VALUE_START_Y + OFFSET_Y(2));
  display.print(scd.backlightFullBrightness);
  display.setCursor(OFFSET_X(1), VALUE_START_Y + OFFSET_Y(3));
  display.print(scd.backlightPowerSaveBrightness);
  display.setCursor(OFFSET_X(1), VALUE_START_Y + OFFSET_Y(4));
  display.print(scd.backlightTimeToPowerSaveMs);
  display.setCursor(OFFSET_X(1), VALUE_START_Y + OFFSET_Y(5));
  display.print(scd.backlightTimeToOffMs);
}
