/*! @file */

#include "SPIFFSConfigService.h"

SPIFFSConfigService::SPIFFSConfigService()
    : IConfigStorage()
{
  m_init = SPIFFS.begin();
}

SPIFFSConfigService::~SPIFFSConfigService()
{
}

/**
 * @copydoc IConfigStorage::save
 */
bool SPIFFSConfigService::save(SystemConfigData *data)
{
  bool retVal = true;

  for (size_t i = 0; i < SystemConfigData::NUM_CONFIGS; i++)
  {
    Config c = (Config)i;
    File file = openFile(data->name(c), true);
    if (file)
    {
      file.print(data->value(c));
      file.close();
    }
  }

  return retVal;
}

/**
 * @copydoc IConfigStorage::load
 */
bool SPIFFSConfigService::load(SystemConfigData *data)
{
  bool retVal = true;

  for (size_t i = 0; i < SystemConfigData::NUM_CONFIGS; i++)
  {
    Config c = (Config)i;
    File file = openFile(data->name(c), false);
    if (file)
    {
      data->value(c) = file.parseInt();
      file.close();
    }
  }

  return retVal;
}

File SPIFFSConfigService::openFile(char *configName, bool write)
{
  size_t len = strlen(configName) + 6;
  char filename[len];
  sprintf(filename, "/%s.txt", configName);

  File file = SPIFFS.open(filename, write ? "w" : "r");
  return file;
}
