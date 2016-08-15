/*! @file */

#ifndef _SPIFFSCONFIGSERVICE_H_
#define _SPIFFSCONFIGSERVICE_H_

#include "IConfigStorage.h"

/**
 * @class SPIFFSConfigService
 * @author Dan Nixon
 * @brief Configuration storage service for saving to the SPI flash file
 *        system.
 */
class SPIFFSConfigService : public IConfigStorage
{
public:
  static const size_t JSON_BUFFER_LEN = 512;

public:
  SPIFFSConfigService();
  virtual ~SPIFFSConfigService();

  virtual bool save(SystemConfigData *data);
  virtual bool load(SystemConfigData *data);
};

#endif
