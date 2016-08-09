/*!
 * @file
 * @author Dan Nixon
 * @brief Testing button integration using Universal Inputs.
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_ILI9341.h>
#include <UniversalInputManager.h>
#include <IButton.h>
#include <MCP23017Button.h>

#include <Adafruit_MCP23017.h>
#include <Dilbert.h>

Adafruit_MCP23017 mcp;
UniversalInputManager inputs;

void handler(inputtype_t type, IInputDevice * device);

void setup()
{
  Serial.begin(9600);

  /* MCP23017 setup */
  mcp.begin();

  /* Add buttons */
  inputs.addDevice(new MCP23017Button(&mcp, Dilbert::BUTTON_UP, Dilbert::BUTTON_UP));
  inputs.addDevice(new MCP23017Button(&mcp, Dilbert::BUTTON_DOWN, Dilbert::BUTTON_DOWN));
  inputs.addDevice(new MCP23017Button(&mcp, Dilbert::BUTTON_LEFT, Dilbert::BUTTON_LEFT));
  inputs.addDevice(new MCP23017Button(&mcp, Dilbert::BUTTON_RIGHT, Dilbert::BUTTON_RIGHT));
  inputs.addDevice(new MCP23017Button(&mcp, Dilbert::BUTTON_A, Dilbert::BUTTON_A));
  inputs.addDevice(new MCP23017Button(&mcp, Dilbert::BUTTON_B, Dilbert::BUTTON_B));

  inputs.setCallback(handler);
}

void loop()
{
  inputs.poll();
}

/**
 * @brief Handles a state change of an input device.
 * @param type Type of input device (should always be button)
 * @param device Pointer to input device
 */
void handler(inputtype_t type, IInputDevice * device)
{
  if(type == UIT_BUTTON)
  {
    IButton * button = (IButton *) device;

    if(button->isActive())
    {
      Serial.print("Button ");
      Serial.print(button->getID());
      Serial.println(" has been pressed...");
    }
    else
    {
      Serial.print("Button ");
      Serial.print(button->getID());
      Serial.print(" has been released after ");
      Serial.print(button->lastActiveDuration());
      Serial.println("ms.");
    }
  }
}
