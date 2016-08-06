/*! @file */

#include "AppManager.h"

#include "App.h"
#include "ConfigService.h"

/**
 * @brief Creates a new application manager.
 * @param badge Pointer to badge driver
 */
AppManager::AppManager(Dilbert *badge)
    : m_badge(badge)
    , m_activeAppIdx(0)
    , m_bButton(nullptr)
    , m_appExitFlag(false)
{
  for (uint8_t i = 0; i < MAX_NUM_APPS; i++)
    m_apps[i] = NULL;
}

AppManager::~AppManager()
{
}

/**
 * @brief Initialises the application manager.
 */
void AppManager::begin()
{
  /* Register this as the button handler */
  m_badge->buttons().setCallback(this);

  /* Enter frst application */
  m_apps[0]->onEntry();

  /* Cache the B button driver */
  m_bButton = (IButton *)m_badge->buttons().getDevice(Dilbert::BUTTON_B);

  /* Ensure backlight is on by default */
  feedBacklight();
}

/**
 * @brief Adds an application to the manager.
 * @param app Pointer to the application
 * @return Index of the added application (255 on error)
 *
 * Note that the first application added must be a home page/launcher
 * application. When an application exits application 0 will be launched.
 */
uint8_t AppManager::addApp(App *app)
{
  for (uint8_t i = 0; i < MAX_NUM_APPS; i++)
  {
    if (!m_apps[i])
    {
      m_apps[i] = app;
      app->m_manager = this;
      app->m_badge = m_badge;
      return i;
    }
  }

  return 255;
}

/**
 * @brief Activates an application given it's name.
 * @param name Name of the app
 * @return True if the app was successfully activated
 */
bool AppManager::activateAppByName(char *name)
{
  uint8_t idx = appIdx(name);
  return activateAppByIdx(idx);
}

/**
 * @brief Activates an application given it's index.
 * @param idx Index of the app
 * @return True if the app was successfully activated
 */
bool AppManager::activateAppByIdx(uint8_t idx)
{
  if (idx > MAX_NUM_APPS)
    return false;

  App *oldApp = m_apps[m_activeAppIdx];
  if (!oldApp)
    return false;

  oldApp->onExit();
  m_activeAppIdx = idx;
  activeApp()->onEntry();

  return true;
}

/**
 * @brief Gets the index of an app given it's name.
 * @param name Name of the app
 * @return Index or 255 if not in manager
 */
uint8_t AppManager::appIdx(char *name)
{
  for (uint8_t i = 0; i < MAX_NUM_APPS; i++)
  {
    if (m_apps[i] && strcmp(name, m_apps[i]->name()) == 0)
      return i;
  }

  return 255;
}

/**
 * @brief Gets the index of an application.
 * @param app Pointer to application
 * @return Index or 255 if not in manager
 */
uint8_t AppManager::appIdx(App *app) const
{
  for (uint8_t i = 0; i < MAX_NUM_APPS; i++)
  {
    if (m_apps[i] == app)
      return i;
  }

  return 255;
}

/**
 * @brief Gets the number of applications in the manager.
 * @return NUmber of apps
 */
size_t AppManager::numApps() const
{
  uint8_t i = 0;
  for (; i < MAX_NUM_APPS; i++)
  {
    if (!m_apps[i])
      break;
  }

  return i;
}

/**
 * @brief Ensures that the backlight stays on, otherwise it is susceptible to
 *        the timeouts set in SystemConfigData.
 */
void AppManager::feedBacklight(uint8_t status)
{
  /* Turn the backlight back on to the given level */
  if (m_backlightStatus < status)
  {
    m_backlightStatus = status;
    updateBacklightOutput();
  }

  if (m_backlightStatus <= status)
    m_lastBacklightFeedTime = millis();
}

/**
 * @brief Runs the loop of the active application.
 */
void AppManager::run()
{
  m_apps[m_activeAppIdx]->run();

  /* Check if the B button has been held long enough to exit the app */
  if (m_bButton->isActive() && !m_appExitFlag &&
      millis() - m_bButton->lastStateChange() >=
          ConfigService::Instance().getConfig().value(CONFIG_BACK_BUTTON_EXIT_DELAY))
  {
    m_apps[m_activeAppIdx]->exit();
    feedBacklight();
    m_appExitFlag = true;
  }

  /* Update backlight timeout */
  if (m_backlightStatus > BACKLIGHT_STATE_OFF)
  {
    uint32_t backlightDeltaT = millis() - m_lastBacklightFeedTime;

    /* Get threshold */
    uint32_t backlightTimeout = 0;
    switch (m_backlightStatus)
    {
    case BACKLIGHT_STATE_FULL:
      backlightTimeout = ConfigService::Instance().getConfig().value(CONFIG_BL_DIM_TIMEOUT);
      break;
    case BACKLIGHT_STATE_DIM:
      backlightTimeout = ConfigService::Instance().getConfig().value(CONFIG_BL_OFF_TIMEOUT);
      break;
    }

    /* Ignore a timeout value of 0 */
    if (backlightTimeout > 0 && backlightDeltaT >= backlightTimeout)
    {
      m_backlightStatus--;
      updateBacklightOutput();
    }
  }
}

/**
 * @brief Handles a state change of an input device.
 * @param type Type of input device (should always be button)
 * @param device Pointer to input device
 */
void AppManager::handleUniversalInputEvent(inputtype_t type, IInputDevice *device)
{
  if (type == UIT_BUTTON)
  {
    IButton *button = (IButton *)device;

    /* If the B button is released after exiting an app then ignore the press */
    if (button == m_bButton && !button->isActive() && m_appExitFlag)
    {
      m_appExitFlag = false;
      return;
    }

    /* Pass button press to active application */
    if (m_apps[m_activeAppIdx]->handleButton(button))
      feedBacklight();
  }
}

/**
 * @brief Updates the backlight output to match the current state.
 */
void AppManager::updateBacklightOutput()
{
  uint16_t intensity;

  switch (m_backlightStatus)
  {
  case BACKLIGHT_STATE_FULL:
    intensity = ConfigService::Instance().getConfig().value(CONFIG_BL_FULL_BRIGHT);
    break;
  case BACKLIGHT_STATE_DIM:
    intensity = ConfigService::Instance().getConfig().value(CONFIG_BL_DIM_BRIGHT);
    break;
  default:
    intensity = 0;
  }

  m_badge->setBacklight(intensity);
}
