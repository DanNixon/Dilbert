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
  SystemConfigData &scd = ConfigService::Instance().getConfig();
  for (size_t i = 0; i < SystemConfigData::NUM_CONFIGS; i++)
  {
    display.setCursor(OFFSET_X(4), MENU_START_Y + OFFSET_Y((i + 1)));
    display.print(scd.name((Config)i));
  }

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

    case Dilbert::BUTTON_A:
      /* Select item */
      if (m_selectedIndex == 0)
      {
        /* Reset config option */
        ConfigService::Instance().getConfig().setDefaultValues();
        ConfigService::Instance().save();
        redraw();
      }
      break;

    case Dilbert::BUTTON_LEFT:
      /* Decrease */
      modifyCurrentSetting(-1);
      break;

    case Dilbert::BUTTON_RIGHT:
      /* Increase */
      modifyCurrentSetting(1);
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
  display.fillRect(0, MENU_START_Y, OFFSET_X(4) - 1, 319, ILI9341_BLACK);

  /* Draw selection arrow */
  display.setTextSize(2);
  display.setTextColor(ILI9341_YELLOW);
  display.setCursor(1, MENU_START_Y + OFFSET_Y(m_selectedIndex));
  display.print(">");

  SystemConfigData &scd = ConfigService::Instance().getConfig();

  /* Draw values */
  display.setTextSize(1);
  display.setTextColor(ILI9341_RED);

  for (size_t i = 0; i < SystemConfigData::NUM_CONFIGS; i++)
  {
    display.setCursor(OFFSET_X(1), VALUE_START_Y + OFFSET_Y((i + 1)));
    display.print(scd.value((Config)i));
  }
}

/**
 * @brief Modifys the current value of a setting.
 */
void SystemSettingsApp::modifyCurrentSetting(int8_t direction)
{
  if (m_selectedIndex > 0)
  {
    SystemConfigData &scd = ConfigService::Instance().getConfig();
    Config c = (Config)(m_selectedIndex - 1);

    int16_t delta = scd.delta(c) * direction;
    scd.value(c) += delta;

    redraw();

    ConfigService::Instance().save();
  }
}
