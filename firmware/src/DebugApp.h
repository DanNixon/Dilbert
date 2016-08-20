/*! @file */

#ifndef _DEBUG_APP_H_
#define _DEBUG_APP_H_

#include <App.h>

/**
 * @class DebugApp
 * @author Dan Nixon
 * @brief App containing debug information and button test.
 */
class DebugApp : public App
{
public:
  DebugApp();
  virtual ~DebugApp();

  virtual void onEntry();
  virtual bool handleButton(IButton *button);
};

#endif
