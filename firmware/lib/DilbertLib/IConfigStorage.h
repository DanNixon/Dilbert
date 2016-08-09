/*! @file */

#ifndef _ICONFIGSTORAGE_H_
#define _ICONFIGSTORAGE_H_

#include "SystemConfigData.h"

/**
 * @class IConfigStorage
 * @author Dan Nixon
 * @brief Interface for configuration storage.
 */
class IConfigStorage
{
public:
  IConfigStorage()
  {
  }
  virtual ~IConfigStorage()
  {
  }

  /**
   * @brief Saves a system configuration.
   * @param data Pointer to a system data to save
   * @return True for successful saving
   */
  virtual bool save(SystemConfigData *data) = 0;

  /**
   * @brief Loads a system configuration.
   * @param data Pointer to a system data to store loaded values in
   * @return True for successful loading
   */
  virtual bool load(SystemConfigData *data) = 0;
};

#endif
