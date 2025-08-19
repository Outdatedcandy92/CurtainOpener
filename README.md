# Curtain Opener

A compact DIY curtain opener that uses an ESP32 microcontroller and a NEMA 17 stepper motor to automatically open and close curtains. The device is powered directly from a wall outlet, ensuring consistent and reliable operation.


https://github.com/user-attachments/assets/f7b5ea29-201d-4f92-9817-be86e9db4244



## Hardware Components

- ESP32 C3 SuperMini
- NEMA 17 stepper motor
- TMC2209 stepper driver
- 12V DC power adapter
- MP1584EN step-down converter
- Paracord or Kevlar string for curtain movement
- Mounting hardware (screws, heat inserts, anchors)

See [BOM.md](BOM.md) for the full bill of materials.

## How It Works

1. The NEMA 17 motor, controlled by the ESP32, pulls a string to move the curtain.
2. Power is supplied by a 12V DC adapter connected to a wall outlet it is stepped down to 5v to power the ESP32.
3. The ESP32 can be programmed for scheduled routines or remote operation.


## Assembly

1. 3D print the enclosure and mechanical parts (see `src/CAD/`).
3. Mount the motor, idler, and string to the curtain.
4. Wire up the stuff and enclose it in a case (optional).
5. Upload your control firmware to the ESP32. (see `src/code`).

## Parts


**Motor Mount**

Screws into the motor and then screws onto the wall near the curtain.

![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/f254cdb409c4352ede6f9bf59e0e4b67e1376b5c_image.png)

**Idler**

This uses a gt2 idler with 8mm bore, this attaches to the curtain rod. (you might have to redesign this based off your cutain rod diameter).

![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/1b50151c39fc53b18b28b7761289c440c27df66d_image.png)


**Enclosure**

This holds all the electronics (motor drivers, step down, esp32 and wires). It has a detachable front panel and side mounts in case you need to update it later.

![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/43ee5cf89285f22024de84485ae08d6685e71685_image.png)

## Wiring Diagram (scuffed)

EN_PIN = 5

STEP_PIN = 6

DIR_PIN = 7

MS1_PIN = 8

MS2_PIN = 9
![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/bd48201a68f4de720ef6dcef808b0d0c94304497_image.png)


## IRL Pics

**Motor**


![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/a1ab29212790c803a154bdb8636eeee0de47712d_20250819_194457.jpg)


**Idler**


![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/b3e822d82838e54c2dde38fbf0247bf391b5e340_20250819_194513.jpg)


**Enclosure**
![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/9ef18a15c913e1592a6d093ecda7e250634e2401_20250819_194533.jpg)


