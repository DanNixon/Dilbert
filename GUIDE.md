# Guide

This aims to provide a general overview of the badge, important stuff,
troubleshooting and building/flashing.

## Power

**The *PWR IN* header accepts up to 6v only**, this is good for either a USB
power bank or a single cell lithium battery.

**There is no reverse polarity protection!** I don't know exactly what would
happen if you connected the supply in reverse polarity, I haven't tried.

If using a bare battery keep in mind that **there is no voltage detection or
protection on the board** (other than the internal supply voltage measurement on
the ESPs ADC) and that the regulator will operate as far down as 3.3V.

Therefore it is your responsibility to make sure the cell voltage of a battery
used to power the board does not fall too low.

An ideal battery to power the board if only used for low power applications
(i.e. no WiFi, no NeoPixels and no external modules) is a 240mAh or 380mAh
micro quad (e.g. Hubsan) battery.

I find that when the battery voltage does start to fall the MCP23017 is the
first device to fail, which is noticeable by the buttons becoming unresponsive.

## Assembly

Most of this is self explanatory, but just a few pointers:

- Do not reflow solder the ESP12 (reflowing my bridge vias on the ESP and the
  Dilbert board)
- Reflow solder the NeoPixels (it is much more difficult to make an arse of
  reflowing them)
- Mod wires must be added to connect the ground of the first NeoPixel and the
  VCC of the last NeoPixel
- Make sure everything works before soldering in the LCD, the holes are tight
  enough for a good connection to be made without soldering

## MCP23017

There are a pair of solder bridge pads near the *X1* designator (bottom left of
the ESP12) that connect the interrupt output of the MCP23017 to the TXd of the
ESP8266 UART.

This connection is made by default using a small trace between the pads. It can
be removed easily with a small screwdriver by scraping the trace between the
pads away and remade by flowing solder over the pads.

If you have issues flashing the board that are not due to lack of power then try
breaking this connection.

## Software

There are a few examples that show how to do most things you would want to do on
the board.

Graphics are handled by the [Adafruit GFX
library](https://github.com/adafruit/Adafruit-GFX-Library), NeoPixels are
handled by the [Adafruit NeoPixel
library](https://github.com/adafruit/Adafruit_NeoPixel), if you choose to use
the additional IO pins of the MCP23017 they are accessed using the [Adafruit
MCP23017
library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library), buttons
are managed using [Universal
Inputs](https://github.com/DanNixon/ArduinoUniversalInput).

Instances to the drivers of each of these devices are provided by the `Dilbert`
object:

- Display: `Dilbert::display()`
- NeoPIxels: `Dilbert::neoPixels()`
- MCP23017: `Dilbert::io()`
- Buttons: `Dilbert::buttons()`

The backlight intensity can be set using either `Dilbert::setBacklight(uint16_t)`
where the parameter is a value between 0 and 1023 or
`Dilbert::setBacklightOn(bool)` where the parameter is a boolean denoting either
full brightness or off.

When handling buttons events from Universal Inputs the IDs are enumerated as:

- `Dilbert::BUTTON_UP`
- `Dilbert::BUTTON_DOWN`
- `Dilbert::BUTTON_LEFT`
- `Dilbert::BUTTON_RIGHT`
- `Dilbert::BUTTON_A`
- `Dilbert::BUTTON_B`

The values of the IDs correspond to the IO on the MCP23017 the button is
connected to.

If using the spare IO pins of the MCP23017 be sure not to change the global
interrupt configuration or the individual pin configurations of any pin
connected to a button.

## Flashing

- Clone this repository
- Run `./init_submodules.sh` (this downloads git submodules containing
  libraries)
- Install [PlatfromIO](http://platformio.org)
- Connect the badge via an FTDI adapter
- Hold the *SWD* switch and press the *RESET* switch, keeping *SWD* pressed
  while the ESP8266 resets (the LED on the ESP12 should blink once)
- `cd firmware`
- `pio run -t upload`
- ???
- Profit

## SD card slot

There is an SD card slot, it shares the SPI bus with the display.

It's chip select pin is connected to the RXd pin of the ESP8266 UART.

I have not tested it but it should probably work OK with the
[SdFat](https://github.com/greiman/SdFat) library.
