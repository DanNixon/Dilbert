/*! @file */

#include "WeatherApp.h"

const char *WeatherApp::ROOT_API_URL = "http://api.openweathermap.org/data/2.5/";
const char *WeatherApp::ENDPOINT_CURRENT = "weather?";
const char *WeatherApp::ENDPOINT_FORECAST = "forecast?";

const char *WeatherApp::API_KEY = "6756e4ca67d2fc305e7f867b30d2ddc4";

WeatherApp::WeatherApp(char *location)
    : App("Weather")
    , m_locationQuery(location)
{
}

WeatherApp::~WeatherApp()
{
}

void WeatherApp::update()
{
}
