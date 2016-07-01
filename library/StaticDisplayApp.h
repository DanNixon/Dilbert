/*! @file */

#ifndef _STATICDISPLAYAPP_H_
#define _STATICDISPLAYAPP_H_

#include "App.h"

/**
 * @class StaticDisplayApp
 * @author Dan Nixon
 * @brief Used for displaying static content at any screen orientation.
 */
class StaticDisplayApp : public App
{
public:
  StaticDisplayApp(char *name);
  virtual ~StaticDisplayApp();

  virtual void onEntry();
  virtual void onExit();

  virtual bool handleButton(IButton *button);

protected:
  void redraw(uint8_t orientation);

  /**
   * @brief Draws the portrait version of the content.
   */
  virtual void drawPortrait()
  {
  }

  /**
   * @brief Draws the landscape version of the content.
   */
  virtual void drawLandscape()
  {
  }
};

#endif
