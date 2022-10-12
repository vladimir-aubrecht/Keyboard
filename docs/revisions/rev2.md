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

| Type              | Name                                                                                                                   | LCSC     | Package              | Amount | Description                                                              | 
| ----------------- | ---------------------------------------------------------------------------------------------------------------------- | -------- | -------------------- | ------ | ------------------------------------------------------------------------ |
| IO Expanders      | [MAX7301ATL+](https://jlcpcb.com/partdetail/MaximIntegrated-MAX7301ATL/C1522600)                                       | C1522600 | QFN50P600X600X80-41N |   1    | Connecting rows & columns from switch matrix through SPI.                |
| I2C Multiplexer   | [TCA9548ARGER](http://www.ti.com/lit/ds/symlink/tca9548a.pdf)                                                          | C555456  | VQFN-24              |   1    | Multiplexing communication with LED drivers.                             |
| C 47 nF           | [CC0402KRX5R9BB473](https://datasheet.lcsc.com/lcsc/2003312232_YAGEO-CC0402KRX5R9BB473_C505502.pdf)                    | C505502  | 0402                 |   1    | Power stabilization.                                                     |
| C 100 nF          | [CL05A105KA5NQNC](https://datasheet.lcsc.com/lcsc/1811091611_Samsung-Electro-Mechanics-CL05A105KA5NQNC_C52923.pdf)     | C52923   | 0402                 |   9    | Power stabilization.                                                     |
| C 1 uF            | [CL05B104KO5NNNC](https://datasheet.lcsc.com/lcsc/1810191219_Samsung-Electro-Mechanics-CL05B104KO5NNNC_C1525.pdf)      | C1525    | 0402                 |   6    | Power stabilization.                                                     |
| Diods             | [1N4148WT](https://datasheet.lcsc.com/szlcsc/1908191708_MDD-Microdiode-Electronics-1N4148WT_C414017.pdf)               | C414017  | SOD-523              |  87    | Preventing key ghosting & masking effects.                               |
| Resistor 10 KOhm  | [0402WGF1002TCE](https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1002TCE_C25744.pdf)                            | C25744   | 0402                 |  19    | Controlling brightness & pull ups for IO expanders.                      |
| Resistor 39 KOhm  | [0402WGF3902TCE](https://datasheet.lcsc.com/lcsc/2206010100_UNI-ROYAL-Uniroyal-Elec-0402WGF3902TCE_C25783.pdf)         | C25783   | 0402                 |   1    | Controlling brightness                                                   |
| RGB LED           | [19-237/R6GHBHC-A04/2T](https://datasheet.lcsc.com/szlcsc/2010222107_Everlight-Elec-19-237-R6GHBHC-A04-2T_C883183.pdf) | C883183  | 19-237               |  87    | Light under each switch.                                                 |
| LED Driver        | [IS32FL3746B](https://www.lumissil.com/assets/pdf/core/IS32FL3746B_DS.pdf)                                             | C2678953 | WFQFN-32             |   9    | Addressing LED and controlling RGB LED diods through SPI.                |
| Stabilizers       | [Cherry stabilizers](https://www.aliexpress.com/item/32951252318.html)                                                 | N/A      | N/A                  |   5    | Stabilizing long keycaps.                                                |
| Hotswap sockets   | [Kailh sockets](https://www.kailhswitch.com/info/kailh-switch-pcb-hot-swapping-socket-33463528.html)                   | C2803348 | SMAD                 |  87    | Connecting Cherry MX switches                                            |


## Firmware
Firmware is custom made in this [repo](../../firmware/Custom/), thou there is nothing preventing using QMK firmware if support for this keyboard is added. I might add it in the future, currently it's not in my focus as I am focusing on hardware finalization first.

## Plate
Built with the help of [Keyboard Layout Editor](http://www.keyboard-layout-editor.com/#/) & Keeb's Plate tool (https://plate.keeb.io/).

## Case
Built in OnShape CAD software, [check out](https://cad.onshape.com/documents/c60788452082993ff7acdd11/w/b14733d6a8d57351c8582e21/e/f5989423f9dc86a71831a4e9) the models!