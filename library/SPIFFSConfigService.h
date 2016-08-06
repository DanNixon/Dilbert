/*! @file */

#ifndef _SPIFFSCONFIGSERVICE_H_
#define _SPIFFSCONFIGSERVICE_H_

#include "IConfigStorage.h"

class SPIFFSConfigService : public IConfigStorage
{
  public:
    SPIFFSConfigService();
    virtual ~SPIFFSConfigService();

    virtual bool save(SystemConfigData *data);
    virtual bool load(SystemConfigData *data);
};

#endif
