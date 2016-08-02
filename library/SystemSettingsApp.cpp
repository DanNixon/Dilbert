/*! @file */

#include "SystemSettingsApp.h"


/**
 * @brief Creates a new system settings application.
 */
SystemSettingsApp::SystemSettingsApp()
    : App("System Settings")
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

  /* TODO */
}

/**
 * @copydoc App::onEntry
 */
void SystemSettingsApp::onEntry()
{
  App::onEntry();

  /* TODO */
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
    /* TODO */

    return false;
  }

  return false;
}
