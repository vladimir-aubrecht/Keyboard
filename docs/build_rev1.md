# Build
This repository contains all necessary artefact to build the keyboard.

Meaning:
- PCB
- [List of components](#List-of-components)
- [Firmware](#Firmware) for [Adafruit Feather Bluefruit 32u4 LE](https://www.adafruit.com/product/2829) (read about [improvements](#future-improvements)!)
- [Plate](#Plate)
- Frame (not done yet)

> :warning: Revision 1 had originally bug with 2 swapped wires for power supply for IO expanders. That's why PCB in galery has those 2 wires and it was fixed in latest commits.


## Dimensions
- Plate: 343x119 mm
- PCB: 349x128 mm

## List of components for PCB
LCSC numbers are based on [JLCPCB](http://jlcpcb.com/) catalog.

| Type              | Name                                       | LCSC    | Package | Amount | Description                                                           | 
| ----------------- | ------------------------------------------ | ------- | ------- | ------ | --------------------------------------------------------------------- |
| Diods             | [1N4148WT](https://datasheet.lcsc.com/szlcsc/1908191708_MDD-Microdiode-Electronics-1N4148WT_C414017.pdf)                       | C414017 | SOD-523 |  87    | Preventing key ghosting & masking effects.                            |
| RGB LED           | [19-237/R6GHBHC-A04/2T](https://datasheet.lcsc.com/szlcsc/2010222107_Everlight-Elec-19-237-R6GHBHC-A04-2T_C883183.pdf) | C883183 | 19-237  |  87    | Light under each switch.                                              |
| IO Expanders      | [MCP23017-E/SO](https://datasheet.lcsc.com/szlcsc/Microchip-Tech-MCP23017-E-SO_C47023.pdf)               | C47023  | SOIC-28 |   2    | Connecting rows & columns from switch matrix through I2C.             |
| LED Driver        | [IS31FL3743A](https://cz.mouser.com/datasheet/2/198/IS31FL3743A_DS-1949512.pdf)                 | N/A     | QFN-40  |   2    | Addressing LED and controlling RGB LED diods through I2C.             |
| Hotswap sockets   | [Kailh sockets](https://www.kailhswitch.com/info/kailh-switch-pcb-hot-swapping-socket-33463528.html)              | N/A     | N/A     |  87    | Connecting Cherry MX switches                                         |
| Stabilizers       | [Cherry stabilizers](https://www.aliexpress.com/item/32951252318.html)    | N/A     | N/A     |   5    | Stabilizing long keycaps.                                             |
| Capacitor 1uF     | [CL05A105KA5NQNC](https://datasheet.lcsc.com/szlcsc/Samsung-Electro-Mechanics-CL05A105KA5NQNC_C52923.pdf)         | C52923  | 0402    |   4    | Stabilizing power circuit for LED drivers.                            |
| Resistor 10 KOhm  | [0402WGF1002TCE](https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1002TCE_C25744.pdf)           | C25744  | 0402    |   6    | Controlling brightness & pull ups for IO expanders.                   |
| Resistor 4.7 KOhm | [0402WGF4701TCE](https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF4701TCE_C25900.pdf)           | C25900  | 0402    |   4    | Pull up resistor for LED drivers.                                     |
| Resistor 200 Ohm  | [0402WGF2000TCE](https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF2000TCE_C25087.pdf)           | C25087  | 0402    |  12    | Green and blue LED channels to limit current and prevent overheating. |
| Resistor 150 Ohm  | [0402WGF1500TCE](https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1500TCE_C25082.pdf)           | C25082  | 0402    |   6    | Red LED channel to limit current and prevent overheating.             |

## Firmware
Custom made firmware (source code in repo) for [Adafruit Feather Bluefruit 32u4 LE](https://www.adafruit.com/product/2829). This has full feature set, keyboard functionality, RGB LEDs and Bluetooth are working.

Firmware is very simple to adjust (if needed at all) for other microcontrollers given microcontroller has required feature (USB HID, BT, I2C, 32 KB Program Storage - no need for all of them, you just need to comment USB HID or BT if your controller doesn't have it).

In Git history it's possible to find old version of firmware for QMK. It was working, but I don't maintain it anymore, thou it's possible to extend support if there will be enough of interest ...

## Plate
Built with the help of [Keyboard Layout Editor](http://www.keyboard-layout-editor.com/#/) & Keeb's Plate tool (https://plate.keeb.io/).

## Case
Built in OnShape CAD software, [check out](https://cad.onshape.com/documents/c60788452082993ff7acdd11/w/b14733d6a8d57351c8582e21/e/f5989423f9dc86a71831a4e9) the models!

## Future improvements
- Even thou RGB LED lights are working, **light intensity is quite low during the day light**. I am planning to play with global brightness resistor or switch to better LEDs.

- Adafruit Feather is working well, thou program storage is very limited - just 32 KB. Current version of firmware is using all of that and I had to comment out logging as didn't have enough of storage. It can be probably optimised more, my guess is to like 50-75% of current usage, but it will still be tight for more new features. I'll be switching to better microcontroller...

- Current combination of PCB chips is limiting I2C to 400 KHz and given amount of queries to MCP23017 there is a performance issue there. Latency of scanning is ~20 ms, **total latency ~30 ms** (through USB). Feeling wise I didn't have problem to type on it by using all my 10 fingers with quite fast speed, but I can imagine it might be **problematic for progamers**. Potential workaround around this is disconnecting RGB LEDs through the connector after which 1.7MHz on I2C should be available, potentially speeding it up.
In next version I am planning to switch to SPI.