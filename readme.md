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

I am having last 3 spare PCBs based on Revision 1. There is tiny bug there, but very easily fixable and otherwise fully working, including RGB LED diods.
In case you are interested **I am fine to donate 1 piece per person** in case you'll pay delivery.

# Current status
[Revision 1](changelog.md) PCB is working, check details about the [build](docs/build.md)!

What is missing in Revision 1:
- Bluetooth 5.0.
- Charging through USB-C.
- Anodized aluminium frame of Filco Majestouch 2 design.

Currently I am focusing on finishing casing for the keyboard.
I managed to test dimensions of casing (see photo in [Galery](#Galery)) and keyboard can be already fully assembled when 3D printed! :)
In next couple of weeks I should get aluminium and I already have all essential components for metal casting, so you can expect short article on metal casting from 3D printed case soon.

> :warning: Revision 1 had originally bug with 2 swapped wires for power supply for IO expanders. That's why PCB in galery has those 2 wires and it was fixed in latest commits.

# Galery

| Description                 | Component | Revision | Picture                                                                          |
|:---------------------------:|:---------:|:--------:|----------------------------------------------------------------------------------|
| Scheme                      | PCB       | 1        | ![PCB scheme](./docs/images/pcb_rev1.png)                                        |
| Render front                | PCB       | 1        | ![PCB render front](./docs/images/pcb_render_front_rev1.png)                     |
| Render back                 | PCB       | 1        | ![PCB render back](./docs/images/pcb_render_back_rev1.png)                       |
| Render                      | Plate     | 1        | ![Plate render](./docs/images/plate_rev1.png)                                    |
| Reality front               | PCB       | 0        | ![PCB reality front](./docs/images/pcb_real_front_rev0.png)                      |
| Reality back                | PCB       | 0        | ![PCB reality back](./docs/images/pcb_real_back_rev0.png)                        |
| Render                      | Case      | 1        | ![Case render](./docs/images/case_render_full.png)                               |
| Render no plate             | Case      | 1        | ![case render no plate](./docs/images/case_render_without_plate.png)             |
| Render no pcb               | Case      | 1        | ![case render no pcb](./docs/images/case_render_without_pcb.png)                 |
| Render no cover             | Case      | 1        | ![case render no cover](./docs/images/case_render_without_cover.png)             |
| Keyboard                    | Keyboard  | 1        | ![keyboard](./docs/images/keyboard_rev1.png)                                     |
| Reality front random colors | PCB       | 1        | ![PCB reality front random colors](./docs/images/pcb_real_front_rev1_colors.png) |
| Reality front               | PCB       | 1        | ![PCB reality front](./docs/images/pcb_real_front_rev1.png)                      |
