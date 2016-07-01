#ifndef _DILBERTMENUAPP_H_
#define _DILBERTMENUAPP_H_

#include "DilbertApp.h"

class DilbertMenuApp : public DilbertApp
{
public:
  DilbertMenuApp(uint8_t itemSize = 3, uint16_t bgColour = ILI9341_BLACK,
                 uint16_t textColour = ILI9341_WHITE,
                 uint16_t iconColour = ILI9341_YELLOW);
  virtual ~DilbertMenuApp();

  virtual void create();
  virtual void onEntry();

  virtual bool handleButton(IButton *button);

protected:
  void redrawSelectonIcon();

protected:
  uint8_t m_itemSize;
  uint16_t m_backgroundColour;
  uint16_t m_textColour;
  uint16_t m_iconColour;

  uint8_t m_selectedAppIndex;
};

#endif
