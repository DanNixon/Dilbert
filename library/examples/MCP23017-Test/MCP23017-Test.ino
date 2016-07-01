/*!
 * @file
 * @brief Basic pin reading and pullup test for the MCP23017 I/O expander
 *
 * Connect pin #12 of the expander to Analog 5 (i2c clock)
 * Connect pin #13 of the expander to Analog 4 (i2c data)
 * Connect pins #15, 16 and 17 of the expander to ground (address selection)
 * Connect pin #9 of the expander to 5V (power)
 * Connect pin #10 of the expander to ground (common ground)
 * Connect pin #18 through a ~10kohm resistor to 5V (reset pin, active low)
 */

#include <Wire.h>
#include <Adafruit_MCP23017.h>

#define INTERRUPT_PIN 2
#define INTERRUPT_NUM 0

Adafruit_MCP23017 mcp;
volatile bool interrupt_wake;

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
    EIFR = 0x01;
    interrupt_wake = false;
  }
}

void interrupt_handle()
{
  interrupt_wake = true;
}
