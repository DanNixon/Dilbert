/*! @file */

#include "AppManager.h"

#include "App.h"

/**
 * @brief Creates a new application manager.
 * @param badge Pointer to badge driver
 */
AppManager::AppManager(Dilbert *badge)
    : m_badge(badge)
    , m_activeAppIdx(0)
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
 * @brief Runs the loop of the active application.
 */
void AppManager::run()
{
  m_apps[m_activeAppIdx]->run();
}

void AppManager::handleUniversalInputEvent(inputtype_t type,
                                           IInputDevice *device)
{
  if (type == UIT_BUTTON)
    m_apps[m_activeAppIdx]->handleButton((IButton *)device);
}
