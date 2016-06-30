#ifndef _DILBERTAPPMANAGER_H_
#define _DILBERTAPPMANAGER_H_

#include <Arduino.h>

#include "DilbertApp.h"

#define MAX_NUM_APPS 16

class DilbertAppManager
{
  public:
    DilbertAppManager();
    virtual ~DilbertAppManager();

    bool addApp(char * name, DilbertApp * app);
    bool removeApp(char * name);
    bool removeApp(DilbertApp * app);

    bool activateApp(char * name);
    bool activateApp(DilbertApp * app);

    DilbertApp * app(char * name);

    inline DilbertApp * activeApp()
    {
      return m_apps[m_activeAppIdx];
    }

  private:
    DilbertApp * m_apps[MAX_NUM_APPS];
    char * m_appNames[MAX_NUM_APPS];
    uint8_t m_activeAppIdx;
};

#endif
