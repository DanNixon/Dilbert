#ifndef _DEMOAPP_H_
#define _DEMOAPP_H_

#include <DilbertApp.h>

class DemoApp : public DilbertApp
{
public:
  DemoApp(char *name)
      : DilbertApp(name)
  {
  }

  virtual ~DemoApp()
  {
  }

  virtual void onEntry()
  {
    DilbertApp::onEntry();

    m_badge->display().fillScreen(ILI9341_BLACK);
    m_badge->display().setCursor(0, 0);

    m_badge->display().print("Entered demo app ");
    m_badge->display().println(m_name);
  }

  virtual void run()
  {
    m_badge->display().print("Demo app ");
    m_badge->display().print(m_name);
    m_badge->display().println(" is running");

    delay(100);
  }

  virtual void handleButton(IButton *button)
  {
    DilbertApp::handleButton(button);

    if (!button->isActive())
    {
      switch(button->getID())
      {
        case Dilbert::BUTTON_UP:
          m_parent->activateAppByIdx(1);
          return;
        case Dilbert::BUTTON_DOWN:
          m_parent->activateAppByIdx(2);
          return;
      }
    }
  }
};

#endif
