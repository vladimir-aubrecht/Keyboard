# Keyboard overview
As usual, I started with this project because I couldn't find keyboard I'd like to use.

This project is trying to build following:
- TKL hotswap keyboard for Cherry MX switches.
- RGB LEDs under each switch (individually controllable from connected device).
- Bluetooth 5.0.
- Charging through USB-C.
- Anodized aluminium frame of Filco Majestouch 2 design.
- Part of case with connector is removable & replacable (to replace either connector or whole microcontroller for any other).

Side features:
- Except of LED drivers & sockets everything is on front side for soldering on JCLPCB side.
- Modularity - All logic chips are on separate modules. Main PCB contains just RGB LEDs, sockets and IO expanders with LED drivers.

❤️ I am having last 3 spare PCBs based on Revision 1. There is tiny bug there, but very easily fixable and otherwise fully working, including RGB LED diods.
In case you are interested **I am fine to donate 1 piece per person** in case you'll pay delivery. Be aware, that it's just PCB, components must be soldered by you.

# Current status
[Revision 2](changelog.md) PCB is working, check details about the [rev 2 build](docs/revisions/rev2.md)!

I am finishing validation of adjusted casing and planning aluminium manufacturing soon.

# Next steps
Polishing firmware (and maybe support for QMK) will be my main focus. It's working, but there is a lot of technical debt there due to support of multiple microcontrollers for testing.
I'll be also evaluating adding QMK support, thou it will probably not be replacement of custom firmware, but rather alternative.

There are also planned changes in PCB namily:
- adding status LEDs or tiny colorful display (if I find some which fits into existing space, this is preferable solution).
- switch for turning keyboard on and off
- better microcontroller with USB-C and more program storage
- gyroscope / accelerometer for movement detection for optimizing wake up experience
- fingerprint sensor

# Built-in features
- For battery below 15%, ESC will light red.

- Keyboard will disable LED lights 1.5 minute after last key press till next key press.

- Bluetooth pairing can be reset by pressing ```Ctrl+Win+Esc```

- LED lights can be turned off by pressing ```Ctrl+Win+F1```

- Switch between sending keys through USB or through Bluetooth by pressing ```Ctrl+Win+F2```
<br/>Keyboard will indicate which one is selected by turning off all LEDs and turning on LED light only under certain F key. F1 = USB, F2 = Bluetooth.

- Randomize colors under each key by pressing ```Ctrl+Win+F3```

- Show battery status by pressing ```Ctrl+Win+F4```.
<br/>Status is shown by turning off all LEDs and turning on LED light only under certain F key. F1 = 10% ... F10 = 100%.

# Galery

| Description                 | Component       | Revision | Picture                                                                          |
|:---------------------------:|:--------------: |:--------:|----------------------------------------------------------------------------------|
| Reality top cover           | Case            | 1        | ![Case top cover](./docs/images/case_top_with_cover.jpeg)                        |
| Reality top white LEDs      | Case            | 1        | ![Case top white LEDs](./docs/images/case_top_white_leds.jpeg)                   |
| Reality top colorfull LEDs  | Case            | 1        | ![Case top colorfull LEDs](./docs/images/case_top_colorfull_leds.jpeg)           |
| Reality back                | Case            | 1        | ![Case back](./docs/images/case_back.jpeg)                                       |
| Reality back connector      | Case            | 1        | ![Case back connector](./docs/images/case_back_connector.jpeg)                   |
| Keyboard                    | TKL Keyboard    | 1        | ![Keyboard](./docs/images/keyboard_rev1.png)                                     |
| Numpad from angle           | Numpad Keyboard | 2        | ![Numpad from angle](./docs/images/numpad_angled.jpg)                            |
| Numpad from top             | Numpad Keyboard | 2        | ![Numpad from top](./docs/images/numpad_top.jpg)                                 |
| Reality front random colors | PCB             | 1        | ![PCB reality front random colors](./docs/images/pcb_real_front_rev1_colors.png) |
| Reality front               | PCB             | 1        | ![PCB reality front](./docs/images/pcb_real_front_rev1.png)                      |
| Render                      | Case            | 1        | ![Case render](./docs/images/case_render_full.png)                               |
| Render no plate             | Case            | 1        | ![case render no plate](./docs/images/case_render_without_plate.png)             |
| Render no pcb               | Case            | 1        | ![case render no pcb](./docs/images/case_render_without_pcb.png)                 |
| Render no cover             | Case            | 1        | ![case render no cover](./docs/images/case_render_without_cover.png)             |
| Render front                | PCB             | 1        | ![PCB render front](./docs/images/pcb_render_front_rev1.png)                     |
| Render back                 | PCB             | 1        | ![PCB render back](./docs/images/pcb_render_back_rev1.png)                       |
| Reality Plate               | Plate           | 1        | ![Plate reality](./docs/images/plate_tkl.jpg)                                    |
| Render                      | Plate           | 1        | ![Plate render](./docs/images/plate_rev1.png)                                    |
| Scheme                      | PCB             | 1        | ![PCB scheme](./docs/images/pcb_rev1.png)                                        |
| Reality front               | PCB             | 0        | ![PCB reality front](./docs/images/pcb_real_front_rev0.png)                      |
| Reality back                | PCB             | 0        | ![PCB reality back](./docs/images/pcb_real_back_rev0.png)                        |
| Reality numpad with LEDs on | PCB             | 2        | ![PCB reality LEDs](./docs/images/numpad_pcb.jpg)                                |


