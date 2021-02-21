# Keyboard overview
As usual, I started with this project because I couldn't find keyboard I'd like to use.

This project is trying to build following:
- TKL hotswap keyboard for Cherry MX switches.
- RGB LEDs under each switch (individually controllable from connected device).
- Bluetooth 5.0.
- Charging through USB-C.
- Ionidized aluminium frame of Filco Majestouch 2 design.

Side features:
- Except of LED drivers & sockets everything is on front side for soldering on JCLPCB side.
- PCB dimension's compatible with Filco Majestouch 2.
- Modularity - All logic chips are on separate modules. Main PCB contains just RGB LEDs, sockets and IO expanders with LED drivers.

# Build
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
Built on top of [QMK](https://qmk.fm/).

## Plate
Built with the help of [Keyboard Layout Editor](http://www.keyboard-layout-editor.com/#/) & Keeb's Plate tool (https://plate.keeb.io/).

# Galery

## PCB
Scheme
![PCB scheme](./docs/images/pcb_rev1.png)

Render front
![PCB scheme](./docs/images/pcb_render_front_rev1.png)

Render Back
![PCB scheme](./docs/images/pcb_render_back_rev1.png)

## Frame
Plate
![Plate](./docs/images/plate_rev1.png)