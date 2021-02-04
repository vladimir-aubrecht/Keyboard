# Rev 0

Features:
- Standard TKL PCB with 3 RGB LEDS.
- No microcontroller on PCB
- (not working) PCB is connected through 11 PINs in 12 PINs connector
    - RGB Led diods controlled through I2C
    - Matrix scanning through I2C + dedicated PINs

# Rev 1 (work in progress)

Features:
- Based on Rev 0 features.
- All diods moved to back so they don't conflict with stabilizers anymore.
- Increased clearance to avoid cross-talk.
- Board can operate through I2C.
- Added RGB leds to every switch, each LED's color configurable separately.