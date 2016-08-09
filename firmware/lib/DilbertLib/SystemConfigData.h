/*! @file */

#ifndef _SYSTEMCONFIGDATA_H_
#define _SYSTEMCONFIGDATA_H_

#include <Arduino.h>

/**
 * @author Dan Nixon
 * @brief Enumeration of config IDs.
 */
enum Config
{
  CONFIG_BACK_BUTTON_EXIT_DELAY,
  CONFIG_BL_FULL_BRIGHT,
  CONFIG_BL_DIM_BRIGHT,
  CONFIG_BL_DIM_TIMEOUT,
  CONFIG_BL_OFF_TIMEOUT
};

/**
 * @class SystemConfigData
 * @author Dan Nixon
 * @brief Used to store system configuration data
 */
class SystemConfigData
{
public:
  static const size_t NUM_CONFIGS = 5;

public:
  SystemConfigData()
  {
    /* Set configuration options */
    m_names[CONFIG_BACK_BUTTON_EXIT_DELAY] = "Exit delay";
    m_delta[CONFIG_BACK_BUTTON_EXIT_DELAY] = 50;

    m_names[CONFIG_BL_FULL_BRIGHT] = "BL full";
    m_delta[CONFIG_BL_FULL_BRIGHT] = 32;

    m_names[CONFIG_BL_DIM_BRIGHT] = "BL dimmed";
    m_delta[CONFIG_BL_DIM_BRIGHT] = 32;

    m_names[CONFIG_BL_DIM_TIMEOUT] = "BL dim delay";
    m_delta[CONFIG_BL_DIM_TIMEOUT] = 1000;

    m_names[CONFIG_BL_OFF_TIMEOUT] = "BL off delay";
    m_delta[CONFIG_BL_OFF_TIMEOUT] = 5000;

    /* Set defaults */
    setDefaultValues();
  }

  /**
   * @brief Sets default values of configuration options.
   */
  void setDefaultValues()
  {
    m_values[CONFIG_BACK_BUTTON_EXIT_DELAY] = 500;
    m_values[CONFIG_BL_FULL_BRIGHT] = PWMRANGE;
    m_values[CONFIG_BL_DIM_BRIGHT] = 256;
    m_values[CONFIG_BL_DIM_TIMEOUT] = 10000;
    m_values[CONFIG_BL_OFF_TIMEOUT] = 60000;
  }

  /**
   * @brief Gets the value of a configuration option.
   * @param config Option to get value for
   * @return Value
   */
  inline uint16_t &value(Config config)
  {
    return m_values[config];
  }

  /**
   * @brief Gets a suitable "step" in value for a given configuration option.
   * @param config Option to get delta for
   * @return Delta value
   */
  inline uint16_t delta(Config config) const
  {
    if ((size_t)config >= NUM_CONFIGS)
      return 0;

    return m_delta[config];
  }

  /**
   * @brief Gets the name of a configuration option.
   * @param config Option to get name for
   * @return Name
   */
  inline char *name(Config config)
  {
    if ((size_t)config >= NUM_CONFIGS)
      return NULL;

    return m_names[config];
  }

private:
  uint16_t m_values[NUM_CONFIGS]; //!< Array of config values
  uint16_t m_delta[NUM_CONFIGS];  //!< Array of delta values for changes to configs
  char *m_names[NUM_CONFIGS];     //!< Names of configuration options
};

#endif
