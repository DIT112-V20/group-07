# group-07 ![CI App](https://github.com/DIT112-V20/group-07/workflows/CI%20App/badge.svg) ![CI Arduino](https://github.com/DIT112-V20/group-07/workflows/CI%20Arduino/badge.svg)

## Project
### WHAT?
We will create a last-mile delivery service. The deliveries will be handled by an autonomous car that can be tracked on an interface  that will be part of our system. 

The application will show the customer:
  1. The current location of the delivery vehicle. 
  2. The delivery route.
  3. The destination i.e. the customers chosen drop-off point.
  4. Estimated time of arrival.

### WHY?
To make it easier for customers to get deliveries, since an autonomous delivery system does not have the constraints that a system using a human driver has, so deliveries can be made whenever the customer desires. Also making delivery of expensive goods  safer since, during transport, no human interaction will be necessary other than that of the customer.

### HOW?
We plan on using the following technologies to complete this project: 
- the Arduino IDE and the Smart Car Shield library to control the car
- Sensors to be able to detect obstacles in the car’s path
- Something similar to the GPRS+GPS Quadband Module for Arduino to track the localisation of the car
- Android studio or something similar to create the application that is able to track the localisation of the car.


## Resources
### Hardware
- 1x Smartcar
- 2x Ultrasonic sensor
- 1x Micro Lidar sensor
- 2x ?? CONNECTION BOARD ??
- 1x Neo gps 6m module
- 1x Android Smartphone

### Software
- Arduino IDE
- Android Studio
- Smartcar library
- Bluetooth serial library
- VL53L0X library
- Wire library
- [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) library

## Setup

### Smartcar

### App
- Google play services SDK
- Enable USB debugging on your android phone and connect it via USB to your computer to be able to download the application.

### User Manual
![Selection](https://imgur.com/zAEGNVP)
- This is where you can choose to either be a Driver or a user.
- By pushing the "Driver"-button you will be able to controll the car by the controls displayed below.
- By pushing the "User"- button it will send you to the Users screen.

![Controller](https://imgur.com/8RqL9Vr)
- You can connect to the car by using the "CONNECT TO BLUETOOTH"-button.
- By pressing the "START"-button you will make the car drive forward in gear 1.
- By pressing the "STOP"-button the car will stop.
- If you want the car to go in reverse, you press the "Reverse"-button.
- To control the car's speed and steering use the two sliders on the screen.
- To open the map, click the "MAP"-button.

![User](https://imgur.com/nykkonX)
- Here you can see the car's location which is displayed by a green marker.
- You can set the destination by either pressing on the map or entering the desired address on the search bar.
- A path will automatically appear on the map between the car and the desired location.


## Developer
- Oscar Hjern
- Mikael Höije
- Jakob Sixten
- Johann Tammen
- Maximilien Uddgren
- Maja Wennroth
