/*! @file */

#ifndef _WEATHERAPP_H_
#define _WEATHERAPP_H_

#include <App.h>

/**
 * @class WeatherApp
 * @author Dan Nixon
 * @brief Provides a basic weather forecast.
 */
class WeatherApp : public App
{
public:
  static const char *ROOT_API_URL;
  static const char *ENDPOINT_CURRENT;
  static const char *ENDPOINT_FORECAST;

private:
  static const char *API_KEY;

public:
  WeatherApp(char *location);
  virtual ~WeatherApp();

  virtual void onEntry()
  {
    m_badge->display().fillScreen(ILI9341_BLACK);
    bool res = m_manager->wifiBegin();
  }

private:
  void update();

private:
  char *m_locationQuery;
};

#endif
