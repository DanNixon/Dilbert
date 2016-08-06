/*! @file */

#ifndef _SPIFFSCONFIGSERVICE_H_
#define _SPIFFSCONFIGSERVICE_H_

#include "IConfigStorage.h"

#include <FS.h>

/**
 * @class SPIFFSConfigService
 * @author Dan Nixon
 * @brief Configuration storage service for saving to the SPI flash file
 *        system.
 */
class SPIFFSConfigService : public IConfigStorage
{
public:
  SPIFFSConfigService();
  virtual ~SPIFFSConfigService();

  virtual bool save(SystemConfigData *data);
  virtual bool load(SystemConfigData *data);

private:
  File openFile(char *configName, bool write);

private:
  bool m_init; //!< If the file system was initialised properly
};

#endif
