/*! @file */

#ifndef _SYSTEMCONFIGDATA_H_
#define _SYSTEMCONFIGDATA_H_

#include <Arduino.h>

/**
 * @author Dan Nixon
 * @brief Used to store system configuration data
 */
struct SystemConfigData
{
  uint16_t backButtonExitDelay;
  uint16_t backlightFullBrightness;
  uint16_t backlightPowerSaveBrightness;
  uint16_t backlightTimeToPowerSaveMs;
  uint16_t backlightTimeToOffMs;
};

#endif
