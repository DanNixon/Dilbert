/*! @file */

#include "SPIFFSConfigService.h"

#include <ArduinoJson.h>
#include <FS.h>

SPIFFSConfigService::SPIFFSConfigService()
    : IConfigStorage()
{
}

SPIFFSConfigService::~SPIFFSConfigService()
{
}

/**
 * @copydoc IConfigStorage::save
 */
bool SPIFFSConfigService::save(SystemConfigData *data)
{
  StaticJsonBuffer<JSON_BUFFER_LEN> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();

  for (size_t i = 0; i < SystemConfigData::NUM_CONFIGS; i++)
    root[data->name((Config)i)] = data->value((Config)i);

  File file = SPIFFS.open("/config.json", "w");
  if (!file)
    return false;

  root.printTo(file);
  file.close();

  return true;
}

/**
 * @copydoc IConfigStorage::load
 */
bool SPIFFSConfigService::load(SystemConfigData *data)
{
  File file = SPIFFS.open("/config.json", "r");
  if (!file)
    return false;

  char buffer[JSON_BUFFER_LEN];
  file.readBytes(buffer, JSON_BUFFER_LEN);

  StaticJsonBuffer<JSON_BUFFER_LEN> jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(buffer);
  if (!root.success())
    return false;

  for (size_t i = 0; i < SystemConfigData::NUM_CONFIGS; i++)
    data->value((Config)i) = root[data->name((Config)i)];

  return true;
}
