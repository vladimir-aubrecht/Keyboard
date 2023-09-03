# Keyboard overview
As usual, I started with this project because I couldn't find keyboard I'd like to use.

This project is trying to build following:
- :white_check_mark: TKL hotswap keyboard for Cherry MX switches.
- :white_check_mark: RGB LEDs under each switch (individually controllable from connected device).
- :white_check_mark: Bluetooth 5.0.
- :white_check_mark: Charging through USB-C.
- :construction: Anodized aluminium frame of Filco Majestouch 2 design.
- :white_check_mark: Part of case with connector is removable & replacable (to replace either connector or whole microcontroller for any other).

Side features:
- :white_check_mark: Except of sockets & connectors for connecting to MCU everything is on front side for soldering on JCLPCB side.
- :white_check_mark: Modularity - All logic chips are on separate modules. Main PCB contains just RGB LEDs, sockets and IO expanders with LED drivers.

❤️ I have some spare PCBs based on Revision 1 & 2. <br/>
**I will donate 1 piece of PCB per person** (develiry paid by you). Be aware, that it's just PCB, components must be soldered by you.

# Current status
[Revision 2](changelog.md) PCB is working, check details about the [rev 2 build](docs/revisions/rev2.md) and [manual](./docs/manual.md)!

I am finishing validation of adjusted casing and planning aluminium manufacturing soon.

If you are interested in more granular updates, I created [this Discord channel](https://discord.com/channels/1029883759740334140/1029884160967442452) where I'll be posting status, photos, ideas, etc.

## Achievements
- :zap: It's fast. In [Joltfly test](./docs/images/joltfly_rev_1.png) I got 0 ms latency. My internal measurements are 500 microseconds.
- :high_brightness: It's bright. RGB LED lights are well visible even during the daylight.

# Next steps
Polishing firmware is main focus. It's working, but there is a lot of technical debt there due to support of multiple microcontrollers for testing.
I started to work on [QMK support](https://github.com/vladimir-aubrecht/qmk_firmware/tree/xboard/keyboards/xboard).

For more details on long term plans you can check this [document](./docs/future.md).

![TKL from top](./docs/images/tkl_rev_2_top.jpg)
![TKL from detail](./docs/images/tkl_rev_2_detail.jpg)

Check more [photos](./docs/gallery.md)! :)

# Credits

- [Jakub](https://www.printables.com/@null) for printing case for me on Prusa XL so I can have it in single piece :)