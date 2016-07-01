#ifndef _DILBERTAPPMANAGER_H_
#define _DILBERTAPPMANAGER_H_

#include <Arduino.h>
#include <UniversalInputTypes.h>
#include <IInputDevice.h>
#include <IUniversalInputCallback.h>

#include "Dilbert.h"

#define MAX_NUM_APPS 16

class DilbertApp;

/**
 * @cass DilbertAppManager
 * @auhor Dan Nixon
 * @brief Used to manage several applications on the badge.
 */
class DilbertAppManager : public IUniversalInputCallback
{
public:
  DilbertAppManager(Dilbert * badge);
  virtual ~DilbertAppManager();

  void begin();

  uint8_t addApp(DilbertApp *app);

  bool activateAppByName(char *name);
  bool activateAppByIdx(uint8_t idx);

  uint8_t appIdx(char *name);
  uint8_t appIdx(DilbertApp *app) const;

  /**
   * @brief Gets an application given it's index.
   * @param idx Application index
   * @return Pointer to application
   */
  inline DilbertApp *app(uint8_t idx)
  {
    return m_apps[idx];
  }

  size_t numApps() const;

  /**
   * @brief Gets the active application.
   * @return Pointer to active application
   */
  inline DilbertApp *activeApp()
  {
    return m_apps[m_activeAppIdx];
  }

  void run();

  void handleUniversalInputEvent(inputtype_t type, IInputDevice * device);

private:
  Dilbert *m_badge;
  DilbertApp *m_apps[MAX_NUM_APPS];
  char *m_appNames[MAX_NUM_APPS];
  uint8_t m_activeAppIdx;
};

#endif
