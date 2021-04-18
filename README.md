# iSyS

**DESCRIPTION**

An Intelligent Robotics Device (IRD) is developed in order to support safe mobility for disabled or  elderly people with various impairments. The proposed system offers five main functions: obstacle  detection and avoidance through bone conduction, live tracking, geofencing, GPS navigation. First,  through a combination of an ultrasonic sensor and bone conduction phone, it detects diverse  obstacles and produces that describe environmental information, including the positions and sizes of  obstacles, which is then given to the learning-based algorithm. By learning the common patterns  among assigned to the same directions, the IRD can automatically find paths to prevent collisions  with obstacles. Second, it distinguishes a situation whereby the user is standing on a sidewalk, traffic  intersection, or roadway through analysing the texture and shape of the images, which aids in  preventing any accidents that would result in fatal injuries to the user, such as collisions with  vehicles. In this project, a novel IRD system is presented that provides more safety for people with  impairments and for elderly people. In order to assure safe mobility, our product offers gps live  tracking, GPS navigation and geofencing. With these three functions, it can perceive obstacles of  various types and recognize dangerous situations, and then recommend viable paths to evade them.  First, obstacles are identified using a combination of ultrasonic ones, and then the avoidable  directions are determined using learning based algorithms. Second, in order to prevent collisions  with vehicles at traffic intersections, the situation recognition component distinguishes the type of  place where the user is currently located as a sidewalk, an intersection. This work aims to provide  safe mobility to wheelchair users while they control the wheelchair toward a destination. In order to  support safe mobility, the wheelchair must detect a range of obstacles and dangerous situations in  real environments and generate avoidable paths to prevent collisions with them. In order to achieve  this, a hybrid obstacle avoidance method and a situation recognition method are proposed.

**SYSTEMS DEPLOYED:**

1.Ultrasonic detection and bone conduction system.

2.GPS GSM SOS ALERT SYSTEM

3.GPS GSM LIVE TRACKING SYSTEM

4.GPS LIVE TRACKING SYSTEM

**OUR IMPLEMENTATION:**

![image](https://user-images.githubusercontent.com/79503433/115146364-d0d16880-a073-11eb-9096-be6999f2d061.png)
![image](https://user-images.githubusercontent.com/79503433/115146375-de86ee00-a073-11eb-99d4-9bdc3ed786b7.png)
![image](https://user-images.githubusercontent.com/79503433/115146565-a2a05880-a074-11eb-86d8-bb1186d62d50.png)
![image](https://user-images.githubusercontent.com/79503433/115146576-ac29c080-a074-11eb-8db5-961d0fccf661.png)
![image](https://user-images.githubusercontent.com/79503433/115146583-b8ae1900-a074-11eb-93f7-ec15e716e6c7.png)





**COMPONENTS USED:**

1.Arduino UNO

2.NEO 6M UBLOX GPS MODULE

3.SIM 900A GSM MODULE

4.PAM 8043 AMPLIFIER

5.PIEZO ELECTRIC TRANSDUCER

6.3.5 MM AUDIO JACK AND SOCKET

7.7805 MOSFET VOLTAGE REGULATOR

8.9V BATTERY

9.SD CARD MODULE

10.HC SR04 ULTRASONIC SENSOR

**TinyGPSPlus**

A new, customizable Arduino NMEA parsing library A NEW Full-featured GPS/NMEA Parser for Arduino TinyGPS++ is a new Arduino library for parsing NMEA data streams provided by GPS modules.

Like its predecessor, TinyGPS, this library provides compact and easy-to-use methods for extracting position, date, time, altitude, speed, and course from consumer GPS devices.

However, TinyGPS++’s programmer interface is considerably simpler to use than TinyGPS, and the new library can extract arbitrary data from any of the myriad NMEA sentences out there, even proprietary ones.

See Arduiniana - TinyGPS++ for more detailed information on how to use TinyGPSPlus

![image](https://user-images.githubusercontent.com/79503433/115144960-fdce4d00-a06c-11eb-957f-8eef09a2af17.png)
![image](https://user-images.githubusercontent.com/79503433/115144982-1179b380-a06d-11eb-9400-d9611b5c2d90.png)

**ULTRASONIC DETECTION SYSTEM:**

AN HC SR04 ULTRASONIC SENSOR IS USED TO DETECT THE OBSTACLE IN FRONT OF THE BLIND PERSON AND THE INFORMATION IS SENT TO AN ARDUINO UNO MICROCONTROLLER. IT THEN GIVES THE AUDIO OUTPUT TO  BONE CONDUCTION PHONE FROM THE SOUND RECORDINGS SAVED IN SD CARD.

![image](https://user-images.githubusercontent.com/79503433/115145093-9533a000-a06d-11eb-8817-72cba41746d0.png)
![image](https://user-images.githubusercontent.com/79503433/115145228-260a7b80-a06e-11eb-88e7-b47e7c8ccb89.png)

**GPS SOS ALERT SYSTEM:**

WHEN THE BLIND PERSON IS ANY EXEGENCY AND IF THE PUSH BUTTON IS PRESSED, IT COMMUNICATES WITH ARDUINO MICRO CONTROLLER AND IT GETS THE GPS COORDINATES FROM NEO 6M UBLOX GPS MODULE. THEN IT SENDS THOSE INFO TO GSM MODULE WHICH TRANSMITS THE DATA TO THE EMERGENCY CONTACT NUMBERS THROUGH THE SIM CARD PLACED IN IT. 

![image](https://user-images.githubusercontent.com/79503433/115145815-28baa000-a071-11eb-886c-25e2a0e225a2.png)
![image](https://user-images.githubusercontent.com/79503433/115145836-44be4180-a071-11eb-8761-dc41c67894c4.png)

**GPS GSM LIVE TRACKING SYSTEM:**

AN UBLOX NEO 6M GPS MODULE IS USED TO OBTAIN THE LIVE GPS COORDINATES AND SENT TO ARDUINO MEGA MICTRO CONTROLLER WHICH INTURN SENDS THE DATA THAT HAS TO BE TRANSMITTED TO THINGER.IO IOT CLOUD PLATFORM TO THE GSM MODULE AND THROUGH THIS SYSTEM WE WILL BE ABLE TO LIVE TRACK THE PERSON FROM ANYWHERE AND ANYTIME .

**GPS LIVE TRACKING SYSTEM:**

AN NEO 6M UBLOX GPS MODULE IS USED TO OBTAIN THE GPS COORDINATES AND IT IS SENT TO ARDUINIO UNO MICRO CONTROLLER FOR PROCESSING. WE USE WAYPOINT METHOD FOR NAVIGATION AND THE ARDUINO CONSTANTLY COMPARES THE LIVE GPS COORDINATES AND THEIR MOVEMENTS .

![image](https://user-images.githubusercontent.com/79503433/115145938-f3628200-a071-11eb-87fc-a0a93d0630c8.png)
![image](https://user-images.githubusercontent.com/79503433/115145946-ffe6da80-a071-11eb-8e05-757c573fd66b.png)







