/*! @file */

#ifndef _MENUAPP_H_
#define _MENUAPP_H_

#include "App.h"

/**
 * @class MenuApp
 * @author Dan Nixon
 * @brief Provides a menu for launching applications.
 */
class MenuApp : public App
{
public:
  MenuApp(uint8_t itemSize = 3, uint16_t bgColour = ILI9341_BLACK,
          uint16_t textColour = ILI9341_WHITE, uint16_t iconColour = ILI9341_YELLOW);
  virtual ~MenuApp();

  virtual void create();
  virtual void onEntry();

  virtual bool handleButton(IButton *button);

protected:
  void redrawSelectonIcon();

protected:
  uint8_t m_itemSize; //!< Text size (scaling) for menu item text

  uint16_t m_backgroundColour; //!< Background colour
  uint16_t m_textColour;       //!< Text colour
  uint16_t m_iconColour;       //!< Selection icon colour

  uint8_t m_selectedAppIndex; //!< Index of currently selected item
};

#endif
