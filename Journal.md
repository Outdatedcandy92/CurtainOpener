# Curtain Opener

## What am I making?
My plan is to make a compact device that is able to open and close my curtain with the use of a NEMA motor, it will also be powered by on-device Li-Po cells and be charged with a solar panel making it fully self sufficient with no need for any external power cables.


### Time Spent Overall: 12 Hours


# June 19 - Speedrunning the project

I have my advance functions final exam tomorrow and I'll be going to spurhacks right after it so I had to speed run  my entire project.

Here are some notes I made on how this project was going to work-
![image](https://hc-cdn.hel1.your-objectstorage.com/s/v3/582fa37a328a42d4e52599ca1750219942cea29b_20250628_140355.jpg)
![image](https://hc-cdn.hel1.your-objectstorage.com/s/v3/ad6aa71f030fdc5ebe147ac3e9d138a6d832821c_20250628_140407.jpg)




The entire plan here is to have a NEMA motor connected to one end of the curtain and an idler the opposite end, and then by having a belt or a Kevlar string I can push and pull the curtain. all of this would be powered by 2 1200mAh lipo cells which will get charged by a 12v solar panel that's mounted on my window. Additionally everything here would be controlled by a ESP32 allowing me to setup routines or control it remotely.

I also spent at least an hour finding which parts to use and found decent modules for almost everything in my project


### Time Spent: 3 Hours

# June 26th - CAD

I basically finished the entire CAD required for this project and here it is-

![image](https://hc-cdn.hel1.your-objectstorage.com/s/v3/4bf2869c00d16564ae28e0266ea0a0e8517d0e28_image.png)
![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/4d07558412cdce223ecdd9737a21b2b357baa3a0_image.png)

This is essentially a very compact (almost 8x8x8cm) box which houses all the electronics, and the batteries. I've opted to go with a perfboard for this project instead of a PCB mainly because I wanted to use upgradable modules, having a perfboard allows me to update and upgrade things in the future whereas a PCB really keeps me locked in to what I have.

The box has plenty of space inside to house all my required electronics, it also has a separate sort of isolated section for the Li-Po cells, I've added grills to the sides to allow for ventilation and heat dissipation from the batteries as I don't want them blowing up or catching fire. I'm using 2 1200mAh 18650 cells wired in parallel to output a total of 3.7v with 2400mAh capacity. the 3.7v output would be boosted to 12v for operating the motors and that 12v would be stepped down to 5v to power up the ESP32.

Also spent some time today working out the BOM for the project and here's what I ended up with
![image](https://hc-cdn.hel1.your-objectstorage.com/s/v3/d587c0fcad33226fb2439c4eb15b8f7c7760398d_image.png)
I still need to add up a few more things but this is more or less the core components required.

### Time Spent: 5 hours

# 28 June - Finishing Up

Made a official wiring diagram for the project
![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/fb45de9de3ca4f33184c879b21a519c5208f83f0_image.png)


Also finished up the CAD for the project. Made a v groove pulley for the motor and another v groove idler that uses a 608 bearing.

![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/f9fdd612560e5c7c8c466bc684028abd44992640_image.png)
![img](https://hc-cdn.hel1.your-objectstorage.com/s/v3/ba7b6fe9ca186f0fa3ed5157393cf5dc5194fcca_image.png)

Also designed a mount that screws into the main box and also screws into the wall
![img]( https://hc-cdn.hel1.your-objectstorage.com/s/v3/292575c62df909653dd1b7516db82622792a3e49_image.png)


Also updated my BOM a bit 
![image](https://hc-cdn.hel1.your-objectstorage.com/s/v3/f7c49bd9ee47e746852bcf265466894e132fc4b6_image.png)

Also spent some time updating and creating a github repo for this project



### Time Spent: 4 Hours