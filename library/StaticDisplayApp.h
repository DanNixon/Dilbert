#ifndef _STATICDISPLAYAPP_H_
#define _STATICDISPLAYAPP_H_

#include "DilbertApp.h"

class StaticDisplayApp : public DilbertApp
{
public:
  StaticDisplayApp(char * name, uint16_t bgColour = ILI9341_BLACK);
  virtual ~StaticDisplayApp();

  virtual void onEntry();
  virtual void onExit();

  virtual bool handleButton(IButton *button);

protected:
  void redraw(uint8_t orientation);

  virtual void drawPortrait()
  {
  }

  virtual void drawLandscape()
  {
  }

protected:
  uint16_t m_backgroundColour;
};

#endif
