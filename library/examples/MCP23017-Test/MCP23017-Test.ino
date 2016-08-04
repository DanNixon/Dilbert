/*!
 * @file
 * @author Dan Nixon
 * @brief Basic pin reading and pullup test for the MCP23017 I/O expander.
 *
 * 12 to GPIO 5 (SCL)
 * 13 to GPIO 4 (SDA)
 * 15, 16 and 17 to GND (address 0)
 * 9 to VCC
 * 10 to GND
 * 18 pullup to 5V (RST)
 */

#include <Wire.h>
#include <Adafruit_MCP23017.h>

#define INTERRUPT_PIN 2
#define INTERRUPT_NUM 0

Adafruit_MCP23017 mcp;        //!< MCP23017 driver
volatile bool interrupt_wake; //!< Flag indicating if the MCP23017 triggered an interrupt

void setup()
{
  Serial.begin(115200);

  mcp.begin();

  /* Setup all pins as inputs with pullup and interrupt */
  for (uint8_t i = 0; i < 15; i++)
  {
    mcp.pinMode(i, INPUT);
    mcp.pullUp(i, HIGH);
    mcp.setupInterruptPin(i, FALLING);
  }

  /* Interrupt setup code as per Dilbert.cpp */
  mcp.setupInterrupts(true, false, LOW);

  /* Setup interrupt handler */
  interrupt_wake = false;
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);

  Serial.println("MCP23017 Test Ready!");
}

void loop()
{
  attachInterrupt(INTERRUPT_NUM, interrupt_handle, CHANGE);

  while (!interrupt_wake)
  {
  }

  detachInterrupt(INTERRUPT_NUM);

  if (interrupt_wake)
  {
    /* Output both ports */
    Serial.print(millis());
    Serial.print(":\t");
    Serial.println(mcp.readGPIOAB(), BIN);

    /* Reset interrupt state */
    /* EIFR = 0x01; */
    interrupt_wake = false;
  }
}

/**
 * @brief Handle MCP23017 interrupt.
 */
void interrupt_handle()
{
  interrupt_wake = true;
}
