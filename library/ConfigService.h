/*! @file */

#ifndef _CONFIGSERVICE_H_
#define _CONFIGSERVICE_H_

#include "IConfigStorage.h"
#include "SystemConfigData.h"

/**
 * @class ConfigService
 * @author Dan Nixon
 * @brief provides access to system confgiuration.
 */
class ConfigService
{
public:
  /**
   * @brief Gets the configuration service.
   * @return Instance of the configuration service
   */
  static ConfigService &Instance()
  {
    static ConfigService instance;
    return instance;
  }

  void setDefaultConfig();

  bool loadFrom(IConfigStorage *storage);
  bool saveTo(IConfigStorage *storage) const;

  /**
   * @brief Gets the system configuration.
   * @return System configuration data
   */
  inline SystemConfigData getConfig() const
  {
    return m_configData;
  }

private:
  ConfigService();
  ConfigService(ConfigService const &);
  void operator=(ConfigService const &);

  SystemConfigData m_configData;
};

#endif
