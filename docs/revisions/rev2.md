# Build Revision 2 (Work in progress!!!)
This repository contains all necessary artefact to build the keyboard.

Meaning:
- PCB
- [List of components](#List-of-components)
- [Firmware](#Firmware)
- [Plate](#Plate)
- Frame (not done yet)

## Dimensions
- Plate: 343x119 mm
- PCB: 349x128 mm

## List of components
LCSC numbers are based on [JLCPCB](http://jlcpcb.com/) catalog.

| Type              | Name                                                                                                                   | LCSC    | Package  | Amount | Description                                                           | 
| ----------------- | ---------------------------------------------------------------------------------------------------------------------- | ------- | -------- | ------ | --------------------------------------------------------------------- |
| Diods             | [1N4148WT](https://datasheet.lcsc.com/szlcsc/1908191708_MDD-Microdiode-Electronics-1N4148WT_C414017.pdf)               | C414017 | SOD-523  |  87    | Preventing key ghosting & masking effects.                            |
| RGB LED           | [19-237/R6GHBHC-A04/2T](https://datasheet.lcsc.com/szlcsc/2010222107_Everlight-Elec-19-237-R6GHBHC-A04-2T_C883183.pdf) | C883183 | 19-237   |  87    | Light under each switch.                                              |
| IO Expanders      | [MCP23S17T-E/SO](https://datasheet.lcsc.com/szlcsc/Microchip-Tech-MCP23017-E-SO_C47023.pdf)                            | C47023  | SOIC-28  |   3    | Connecting rows & columns from switch matrix through I2C or SPI.      |
| LED Driver        | [IS32FL3746B](https://www.lumissil.com/assets/pdf/core/IS32FL3746B_DS.pdf)                                             | N/A     | WFQFN-32 |   5    | Addressing LED and controlling RGB LED diods through SPI.             |
| Hotswap sockets   | [Kailh sockets](https://www.kailhswitch.com/info/kailh-switch-pcb-hot-swapping-socket-33463528.html)                   | N/A     | N/A      |  87    | Connecting Cherry MX switches                                         |
| Stabilizers       | [Cherry stabilizers](https://www.aliexpress.com/item/32951252318.html)                                                 | N/A     | N/A      |   5    | Stabilizing long keycaps.                                             |
| Capacitor 1uF     | [CL05A105KA5NQNC](https://datasheet.lcsc.com/szlcsc/Samsung-Electro-Mechanics-CL05A105KA5NQNC_C52923.pdf)              | C52923  | 0402     |   4    | Stabilizing power circuit for LED drivers.                            |
| Resistor 10 KOhm  | [0402WGF1002TCE](https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1002TCE_C25744.pdf)                            | C25744  | 0402     |  11    | Controlling brightness & pull ups for IO expanders.                   |
| Resistor 4.7 KOhm | [0402WGF4701TCE](https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF4701TCE_C25900.pdf)                            | C25900  | 0402     |   8    | Pull up resistor for LED drivers.                                     |
| Resistor 200 Ohm  | [0402WGF2000TCE](https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF2000TCE_C25087.pdf)                            | C25087  | 0402     |  12    | Green and blue LED channels to limit current and prevent overheating. |
| Resistor 150 Ohm  | [0402WGF1500TCE](https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1500TCE_C25082.pdf)                            | C25082  | 0402     |   6    | Red LED channel to limit current and prevent overheating.             |

## Firmware
Firmware is custom made in this [repo](../../firmware/Custom/), thou there is nothing preventing using QMK firmware if support for this keyboard is added. I might add it in the future, currently it's not in my focus as I am focusing on hardware finalization first.

## Plate
Built with the help of [Keyboard Layout Editor](http://www.keyboard-layout-editor.com/#/) & Keeb's Plate tool (https://plate.keeb.io/).

## Case
Built in OnShape CAD software, [check out](https://cad.onshape.com/documents/c60788452082993ff7acdd11/w/b14733d6a8d57351c8582e21/e/f5989423f9dc86a71831a4e9) the models!