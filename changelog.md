All prices below are based 5 pieces (minimum) on: [JLCPCB](https://jlcpcb.com/).

# Keyboard revison 2 (PCB: $22.34, SMT: $77.29 work in progress)
- PCB based on Rev 1 features, added:
  - ⭐ Switch matrix is driven by IO expanders through SPI to achieve <1 ms end to end latencies.
  - ⭐ Heavily increased brightness of all LEDs by having separate LED driver for each 2 columns (due to max current per chip).
  - ⭐ Fixed bug with swapped GND and VCC, no more bridging needed.
- TKL Case
  - ⭐ Added support for magnetically attachable numpad from left or right by inserting magnets into prepared sockets.
    - I recommend N52 magnets, with those connection is strong enough to lift numpad part into air :)
    - I used these [magnets 20x5x2](https://www.aliexpress.com/item/1005001646834539.html?spm=a2g0o.order_list.0.0.25271802ZhGVrg) from exactly this store. I had bad experience with some other sellers as quality of magnets were lower than advertised.
    - You need 18 magnets in total for TKL keyboard (and another 18 for numpad).
- Numpad Case
  - ⭐ Created magnetically attachable numpad! :)
    - Similar design like main TKL keyboard (just without internal pillars for extra support)
    - Requires it's own microcontroller and battery in case of bluetooth usage.
    - Top part of numpad is kept empty for this moment - work in progress, meant for display and fingerprint sensor.

# Keyboard revison 1 (PCB: $21.8, SMT: $30.56)
- PCB based on revision 0 features, added:
  - ⭐ Switch matrix is driven by IO expanders through I2C.
  - ⭐ Added RGB leds to every switch
    - Each LED's color configurable separately.
    - Controlled by built-in LED driver controlled through I2C.
  - 💪🏻 All solderable [JLCPCB](https://jlcpcb.com/) library components for assembly are moved to top side.
  - 💪🏻 Increased clearances.
  - 🤜🏻 Collisions of diods with stabilizers are fixed.
  - :exclamation: Contains bug with powering MCP23017 chips (GND and VCC are swapped - can be easily fixed by bridging with 2 wires and some scratching :) )

# Keyboard revision 0 (PCB: $22.1, SMT: N/A)
- ⭐ TKL matrix for Cherry MX switches.
- ⭐ Holes for stabilizers.
