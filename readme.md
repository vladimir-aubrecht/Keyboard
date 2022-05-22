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
[Revision 1](changelog.md) keyboard is working, check details about the [build](docs/build_rev1.md)!

What is missing in Revision 1:
- Bluetooth 5.0.
- Charging through USB-C.
- Anodized aluminium frame of Filco Majestouch 2 design.

Currently I am focusing on finishing casing for the keyboard.
I managed to test dimensions of casing (see photo in [Galery](#Galery)) and keyboard can be already fully assembled when 3D printed! :)

# Next steps
At this time I am in process of ordering aluminium plate made on CNC(~25 usd - if everything will go well, I'll share where to make it ...).

I am delaying aluminium case little bit longer as I want to extend project for magnetically attachable numpad (connected through POGO connectors from left or right side).

There are also planned changes in PCB namily:
- switch to SPI interface to get lower latencies
- improving brightness and colors of LEDs
- adding status LEDs or tiny colorful OLED display (if I find some which fits into existing space, this is preferable solution).
- switch for turning keyboard on and off
- better microcontroller with USB-C and more program storage

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

| Description                 | Component | Revision | Picture                                                                          |
|:---------------------------:|:---------:|:--------:|----------------------------------------------------------------------------------|
| Reality top cover           | Case      | 1        | ![Case top cover](./docs/images/case_top_with_cover.jpeg)                        |
| Reality top white LEDs      | Case      | 1        | ![Case top white LEDs](./docs/images/case_top_white_leds.jpeg)                   |
| Reality top colorfull LEDs  | Case      | 1        | ![Case top colorfull LEDs](./docs/images/case_top_colorfull_leds.jpeg)           |
| Reality back                | Case      | 1        | ![Case back](./docs/images/case_back.jpeg)                                       |
| Reality back connector      | Case      | 1        | ![Case back connector](./docs/images/case_back_connector.jpeg)                   |
| Keyboard                    | Keyboard  | 1        | ![keyboard](./docs/images/keyboard_rev1.png)                                     |
| Reality front random colors | PCB       | 1        | ![PCB reality front random colors](./docs/images/pcb_real_front_rev1_colors.png) |
| Reality front               | PCB       | 1        | ![PCB reality front](./docs/images/pcb_real_front_rev1.png)                      |
| Render                      | Case      | 1        | ![Case render](./docs/images/case_render_full.png)                               |
| Render no plate             | Case      | 1        | ![case render no plate](./docs/images/case_render_without_plate.png)             |
| Render no pcb               | Case      | 1        | ![case render no pcb](./docs/images/case_render_without_pcb.png)                 |
| Render no cover             | Case      | 1        | ![case render no cover](./docs/images/case_render_without_cover.png)             |
| Render front                | PCB       | 1        | ![PCB render front](./docs/images/pcb_render_front_rev1.png)                     |
| Render back                 | PCB       | 1        | ![PCB render back](./docs/images/pcb_render_back_rev1.png)                       |
| Render                      | Plate     | 1        | ![Plate render](./docs/images/plate_rev1.png)                                    |
| Scheme                      | PCB       | 1        | ![PCB scheme](./docs/images/pcb_rev1.png)                                        |
| Reality front               | PCB       | 0        | ![PCB reality front](./docs/images/pcb_real_front_rev0.png)                      |
| Reality back                | PCB       | 0        | ![PCB reality back](./docs/images/pcb_real_back_rev0.png)                        |


