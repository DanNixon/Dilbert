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
  static const size_t NUM_OPTIONS = 6;

public:
  SystemSettingsApp();
  virtual ~SystemSettingsApp();

  virtual void create();
  virtual void onEntry();

  virtual bool handleButton(IButton *button);

private:
  void redraw();
  void modifyCurrentSetting(int8_t direction);

private:
  size_t m_selectedIndex; //!< Index of currently selected setting item
};

#endif
