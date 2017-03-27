/*! @file */

#pragma once

#include <App.h>

/**
 * @class FlanNoTsubasa
 * @author Dan Nixon
 */
class FlanNoTsubasa : public App
{
public:
  FlanNoTsubasa();
  virtual ~FlanNoTsubasa();

  virtual void onEntry();
  virtual void onExit();
  virtual bool handleButton(IButton *button);
  virtual void run();
};
