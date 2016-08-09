/*! @file */

#ifndef _CONWAYS_H_
#define _CONWAYS_H_

#include <App.h>

class Conways : public App
{
  static const uint16_t GRID_X = 60, GRID_Y = 80, PIXEL_SCALE = 4, PATTERN_COUNT = 5;
  unsigned long wait, next;
  uint8_t currPattern;
  uint8_t worldX, worldY;
  bool getDots;
  unsigned char frontGrid[(uint16_t)(((float)GRID_X / 8.0) + 1.0)][GRID_Y];
  unsigned char backGrid[(uint16_t)(((float)GRID_X / 8.0) + 1.0)][GRID_Y];
  unsigned char patterns[PATTERN_COUNT][8] = {
      // blinker
      {B00000000, B00000000, B00010000, B00010000, B00010000, B00000000, B00000000, B00000000},
      // glider
      {B00000000, B00000000, B00010000, B00001000, B00111000, B00000000, B00000000, B00000000},
      // lwss
      {B00000000, B00000000, B00111100, B01000100, B00000100, B01001000, B00000000, B00000000},
      // mwss
      {B00000000, B00000000, B01111100, B10000100, B00000100, B10001000, B00100000, B00000000},
      // hwss
      {B00000000, B00000000, B01111110, B10000010, B00000010, B10000100, B00110000, B00000000}};

  void setFGBit(uint16_t x, uint16_t y, uint8_t val)
  {
    uint16_t subX = (float)x / 8.0;
    if (val)
    {
      frontGrid[subX][y] = frontGrid[subX][y] | (1 << (x % 8));
    } // turn bit on
    else
    {
      frontGrid[subX][y] = frontGrid[subX][y] & ~(1 << (x % 8));
    } // turn bit off
  }
  unsigned char getFGBit(uint16_t x, uint16_t y)
  {
    return frontGrid[(uint16_t)((float)x / 8.0)][y] & (1 << (x % 8));
  }
  void setBGBit(uint16_t x, uint16_t y, uint16_t val)
  {
    uint16_t subX = (float)x / 8.0;
    if (val)
    {
      backGrid[subX][y] = backGrid[subX][y] | (1 << (x % 8));
    } // turn bit on
    else
    {
      backGrid[subX][y] = backGrid[subX][y] & ~(1 << (x % 8));
    } // turn bit off
  }
  unsigned char getBGBit(uint16_t x, uint16_t y)
  {
    return backGrid[(uint16_t)((float)x / 8.0)][y] & (1 << (x % 8));
  }
  unsigned char getPattBit(uint16_t pattern, uint16_t x, uint16_t y)
  {
    return patterns[pattern][y] & (1 << (x % 8));
  }

  bool cgolGetDot(uint16_t x, uint16_t y)
  {
    uint8_t count = 0;
    int16_t xleft = x - 1, xright = x + 1, ytop = y + 1, ybottom = y - 1;
    if (xleft < 0)
      xleft = GRID_X - 1;
    if (xright == GRID_X)
      xright = 0;
    if (ytop == GRID_Y)
      ytop = 0;
    if (ybottom < 0)
      ybottom = GRID_Y - 1;
    if (getFGBit(xleft, ytop))
      count++; // top left
    if (getFGBit(x, ytop))
      count++; // top middle
    if (getFGBit(xright, ytop))
      count++; // top right
    if (getFGBit(xleft, y))
      count++; // middle left
    if (getFGBit(xright, y))
      count++; // middle right
    if (getFGBit(xleft, ybottom))
      count++; // bottom left
    if (getFGBit(x, ybottom))
      count++; // bottom middle
    if (getFGBit(xright, ybottom))
      count++; // bottom right
    if (getFGBit(x, y) && count < 2)
    { // < 2 && alive, death
      return false;
    }
    else if (getFGBit(x, y) && (count == 2 || count == 3))
    { // ==2 || ==3 && alive, live
      return true;
    }
    else if (getFGBit(x, y) && count > 3)
    { // >3 && alive, death
      return false;
    }
    else if (getFGBit(x, y) == false && count == 3)
    { // ==3 && dead, birth
      return true;
    }
    return false;
  }

  void cgol()
  {
    for (uint16_t x = 0; x < GRID_X; x++)
    {
      for (uint16_t y = 0; y < GRID_Y; y++)
      {
        setBGBit(x, y, cgolGetDot(x, y));
      }
    }
    /*
    if(worldX<GRID_X && getDots){
      if(worldY<GRID_Y){
        setBGBit(worldX,worldY,cgolGetDot(worldX,worldY));
        worldY++;
      }else{
        if(getDots){
          worldY=0;
          worldX++;
        }
      }
    }else{
      if(getDots){
        worldX=0;
        getDots=false;
      }
    }
    */
    for (uint16_t x = 0; x < GRID_X; x++)
    {
      for (uint16_t y = 0; y < GRID_Y; y++)
      {
        bool bit = getBGBit(x, y);
        setFGBit(x, y, bit);
        m_badge->display().fillRect(x * PIXEL_SCALE, y * PIXEL_SCALE, PIXEL_SCALE, PIXEL_SCALE,
                                    bit ? ILI9341_WHITE : ILI9341_BLACK);
      }
    }
    /*
    if(worldX<GRID_X && !getDots){
      if(worldY<GRID_Y){
        bool bit=getBGBit(worldX,worldY);
        setFGBit(worldX,worldY,bit);
        m_badge->display().fillRect(worldX*PIXEL_SCALE,worldY*PIXEL_SCALE,PIXEL_SCALE,PIXEL_SCALE,bit?ILI9341_WHITE:ILI9341_BLACK);
        worldY++;
      }else{
        if(!getDots){
          worldY=0;
          worldX++;
        }
      }
    }else{
      if(!getDots){
        worldX=0;
        getDots=true;
      }
    }
    */
  }

public:
  Conways()
      : App("Conways")
      , wait(500)
      , next(millis())
      , currPattern(0)
      , worldX(0)
      , worldY(0)
      , getDots(true)
  {
  }

  ~Conways()
  {
  }

  /**
   * @copydoc App:onEntry
   */
  void onEntry()
  {
    Serial.begin(9600);
    App::onEntry();

    /* Clear the screen */
    m_badge->display().fillScreen(ILI9341_BLACK);

    // random fill screen pixels
    for (int x = 0; x < GRID_X; x++)
    {
      for (int y = 0; y < GRID_Y; y++)
      {
        bool bit = random(2);
        setFGBit(x, y, bit);
        m_badge->display().fillRect(x * PIXEL_SCALE, y * PIXEL_SCALE, PIXEL_SCALE, PIXEL_SCALE,
                                    bit ? ILI9341_WHITE : ILI9341_BLACK);
      }
    }
  }

  /**
   * @copydoc App:handleButton
   */
  bool handleButton(IButton *button)
  {
    if (App::handleButton(button))
      return true;

    if (button->isActive())
    {
      if (button->getID() == 1)
      { // up (next pattern)
        for (int x = 0; x < GRID_X; x++)
        { // clear grid
          for (int y = 0; y < GRID_Y; y++)
          {
            setFGBit(x, y, 0);
          }
        }
        m_badge->display().fillScreen(ILI9341_BLACK); // clear screen
        currPattern++;
        currPattern = currPattern >= PATTERN_COUNT ? PATTERN_COUNT - 1 : currPattern;
        uint16_t xOffset = (GRID_X / 2) - 4, yOffset = (GRID_Y / 2) - 4;
        for (int x = 0; x < 8; x++)
        { // set pattern
          for (int y = 0; y < 8; y++)
          {
            bool bit = getPattBit(currPattern, 7 - x, y); // kludge! invert x?!
            setFGBit(x + xOffset, y + yOffset, bit);
            m_badge->display().fillRect((x + xOffset) * PIXEL_SCALE, (y + yOffset) * PIXEL_SCALE,
                                        PIXEL_SCALE, PIXEL_SCALE,
                                        bit ? ILI9341_WHITE : ILI9341_BLACK);
          }
        }
      }
      if (button->getID() == 2)
      { // down (prev pattern)
        for (int x = 0; x < GRID_X; x++)
        { // clear grid
          for (int y = 0; y < GRID_Y; y++)
          {
            setFGBit(x, y, 0);
          }
        }
        m_badge->display().fillScreen(ILI9341_BLACK); // clear screen
        currPattern--;
        currPattern = currPattern < 0 ? 0 : currPattern;
        uint16_t xOffset = (GRID_X / 2) - 4, yOffset = (GRID_Y / 2) - 4;
        for (int x = 0; x < 8; x++)
        { // set pattern
          for (int y = 0; y < 8; y++)
          {
            bool bit = getPattBit(currPattern, 7 - x, y); // kludge! invert x?!
            setFGBit(x + xOffset, y + yOffset, bit);
            m_badge->display().fillRect((x + xOffset) * PIXEL_SCALE, (y + yOffset) * PIXEL_SCALE,
                                        PIXEL_SCALE, PIXEL_SCALE,
                                        bit ? ILI9341_WHITE : ILI9341_BLACK);
          }
        }
      }
      if (button->getID() == 0)
      { // left: slower game speed
        wait += 100;
        wait = wait > 10000 ? 10000 : wait;
      }
      if (button->getID() == 3)
      { // right: faster game speed
        wait -= 100;
        wait = wait < 100 ? 100 : wait;
      }
      if (button->getID() == 4)
      { // a (random pattern)
        // random fill screen pixels
        for (int x = 0; x < GRID_X; x++)
        {
          for (int y = 0; y < GRID_Y; y++)
          {
            bool bit = random(2);
            setFGBit(x, y, bit);
            m_badge->display().fillRect(x * PIXEL_SCALE, y * PIXEL_SCALE, PIXEL_SCALE, PIXEL_SCALE,
                                        bit ? ILI9341_WHITE : ILI9341_BLACK);
          }
        }
      }
      if (button->getID() == 5)
      { // b
        wait = 500;
      }
    }

    return true;
  }

  /**
   * @copydoc App:run
   */
  void run()
  {
    /* Keep backlight on */
    m_manager->feedBacklight(BACKLIGHT_STATE_DIM);

    if (next < millis())
    {
      next = millis() + wait;
      cgol();
    }
  }
};

#endif
