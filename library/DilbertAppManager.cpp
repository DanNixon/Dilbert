#include "DilbertAppManager.h"

DilbertAppManager::DilbertAppManager()
  : m_activeAppIdx(0)
{
  for (uint8_t i = 0; i < MAX_NUM_APPS; i++)
    m_apps[i] = NULL;
}

DilbertAppManager::~DilbertAppManager()
{
}


bool DilbertAppManager::addApp(char * name, DilbertApp * app)
{
}

bool DilbertAppManager::removeApp(char * name)
{
}

bool DilbertAppManager::removeApp(DilbertApp * app)
{
}

bool DilbertAppManager::activateApp(char * name)
{
}

bool DilbertAppManager::activateApp(DilbertApp * app)
{
}

DilbertApp * app(char * name)
{
}
