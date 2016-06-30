#ifndef _DILBERTAPP_H_
#define _DILBERTAPP_H_

class DilbertApp
{
  public:
    DilbertApp()
      : m_initDone(false)
    {
    }

    virtual ~DilbertApp();

    virtual void onInit()
    {
      m_initDone = true;
    }

    virtual void onEntry()
    {
      if (!m_initDone)
        onInit();
    }

    virtual void run() = 0;

    virtual void onExit()
    {
    }

  protected:
    bool m_initDone;
};

#endif
