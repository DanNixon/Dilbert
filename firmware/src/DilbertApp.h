/*! @file */

#ifndef _DILBERTAPP_H_
#define _DILBERTAPP_H_

#include <App.h>

/**
 * @class DilbertApp
 * @author Iain Yarnall
 * @brief Displays Dilbert image
 */
class DilbertApp : public App
{
public:
  DilbertApp()
      : App("Dilbert")
  {
  }

  /**
   * @copydoc App::onEntry
   */
  virtual void onEntry()
  {
    App::onEntry();

    /* Clear the screen */
    m_badge->display().fillScreen(ILI9341_BLACK);

    drawHeader();
    drawDilbert();
  }

private:
  /**
   * @brief Draws a textual header.
   */
  void drawHeader()
  {
    m_badge->display().setTextColor(ILI9341_WHITE);
    m_badge->display().setCursor(0, 0);
    m_badge->display().setTextSize(4);
    m_badge->display().println("Dilbert");
  }

  /**
   * @brief Draws the Dilbert ASCII art.
   */
  void drawDilbert()
  {
    m_badge->display().setTextSize(1);
    m_badge->display().println("");
    m_badge->display().println("       ,-._.-._.-._.-._.-.");
    m_badge->display().println("       `-.             ,-'");
    m_badge->display().println("         |             | ");
    m_badge->display().println("         |             | ");
    m_badge->display().println("         |             | ");
    m_badge->display().println("         |    .. ,.    |  ");
    m_badge->display().println("       ,-|___|  |  |___|-.");
    m_badge->display().println("       | |   L__;__J   | |");
    m_badge->display().println("       `|      / \\      |'");
    m_badge->display().println("        |     (   )     |");
    m_badge->display().println("        |      `''      |");
    m_badge->display().println("        |               |");
    m_badge->display().println("        |               |");
    m_badge->display().println("        ;--..._____...--;");
    m_badge->display().println("       ,'--.._/   \\_..--`.");
    m_badge->display().println("      /       `. ,'       \\");
    m_badge->display().println("     /    /`.  | |    _l_  \\");
    m_badge->display().println("    /_/   \\  \\_J |  |\"   |\\_\\");
    m_badge->display().println("    //     `-.__.'  |    | \\\\");
    m_badge->display().println("   ||           |   `---'   ||");
    m_badge->display().println("   ||           |           || ");
    m_badge->display().println("  ||            |            ||");
    m_badge->display().println("  ||            |            ||");
    m_badge->display().println("  ||            |            ||");
    m_badge->display().println(" ;' |           |           | `; ");
    m_badge->display().println("  `' \\          |          / `'");
    m_badge->display().println("      `--..____/ \\____..--'");
    m_badge->display().println("        |       |       |");
    m_badge->display().println("        |       |       |");
    m_badge->display().println("        |       |       |");
    m_badge->display().println("        |       |       |");
    m_badge->display().println("        |       |       |");
    m_badge->display().println("        |       |       |");
    m_badge->display().println("        |       |       |");
    m_badge->display().println("        |       |       |");
    m_badge->display().println("        |       |       |");
    m_badge->display().println("        |       |       |");
    m_badge->display().println("        |_______|_______|");
    m_badge->display().println("  _..--'      |   |      `--.._");
    m_badge->display().println(" ;________.___|   |___.________;");
  }
};

#endif
