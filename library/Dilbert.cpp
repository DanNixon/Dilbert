#include "Dilbert.h"

Dilbert::Dilbert() :
  m_tftDisplay(new Adafruit_ILI9341(TFT_CS_PIN, TFT_DC_PIN))
{
  m_tftDisplay->begin();
}

Dilbert::~Dilbert()
{
  delete m_tftDisplay;
}
