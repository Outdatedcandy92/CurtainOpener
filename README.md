# Curtain Opener

A compact, self-sufficient DIY curtain opener that uses an ESP32 microcontroller and a NEMA 17 stepper motor to automatically open and close curtains. The device is powered by Li-Po batteries and charged via a solar panel, eliminating the need for external power cables.

![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/7ce0c410209a9f04f6d95449c5436c2fce793385_image.png)
![image](https://hc-cdn.hel1.your-objectstorage.com/s/v3/574074e39db7d610d1b84c6719b676628c8d1e82_image.png)

## Features

- **Automatic Curtain Control:** Open and close curtains with routines or remote control via ESP32.
- **Self-Sufficient Power:** Dual 1200mAh Li-Po cells charged by a 12V solar panel.
- **Modular Electronics:** Uses a perfboard for easy upgrades and maintenance.
- **Compact Design:** All components fit inside an 8x8x8cm enclosure.
- **Safety:** Isolated battery compartment with ventilation grills for heat dissipation.

## Hardware Components

- ESP32 C3 SuperMini
- NEMA 17 stepper motor
- TMC2209 stepper driver
- Dual 1200mAh 18650 Li-Po cells (parallel)
- CN3791 12V solar charging module
- 100W step-up and MP1584EN step-down converters
- 3-7 perfboard
- V-groove pulleys, idler with 608 bearing
- Paracord or Kevlar string for curtain movement
- PETG filament for 3D printed parts
- Mounting hardware (screws, heat inserts, anchors)

See [BOM.md](BOM.md) for the full bill of materials.

## How It Works

1. The NEMA 17 motor, controlled by the ESP32, pulls a string to move the curtain.
2. Power is supplied by Li-Po batteries, charged by a solar panel.
3. The ESP32 can be programmed for scheduled routines or remote operation.

## Assembly

1. 3D print the enclosure and mechanical parts (see `src/CAD/`).
2. Assemble electronics on the perfboard.
3. Mount the motor, idler, and string to the curtain.
4. Install the solar panel and connect to the charging module.
5. Upload your control firmware to the ESP32.

## Wiring

This is a rough wiring diagram of the project. (More detailed one will be released when I actually build it)

![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/fb45de9de3ca4f33184c879b21a519c5208f83f0_image.png)


