/*! @file */

#ifndef _SYSTEMSETTINGS_H_
#define _SYSTEMSETTINGS_H_

#include "App.h"

/**
 * @class SystemSettingsApp
 * @author Dan Nixon
 * @brief Provides functionality for changing system setings.
 */
class SystemSettingsApp : public App
{
public:
  SystemSettingsApp();
  virtual ~SystemSettingsApp();

  virtual void create();
  virtual void onEntry();

  virtual bool handleButton(IButton *button);
};

#endif
