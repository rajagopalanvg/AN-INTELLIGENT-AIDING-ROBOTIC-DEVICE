# iSyS

**DESCRIPTION**

An Intelligent Robotics Device (IRD) is developed in order to support safe mobility for disabled or  elderly people with various impairments. The proposed system offers five main functions: obstacle  detection and avoidance through bone conduction, live tracking, geofencing, GPS navigation. First,  through a combination of an ultrasonic sensor and bone conduction phone, it detects diverse  obstacles and produces that describe environmental information, including the positions and sizes of  obstacles, which is then given to the learning-based algorithm. By learning the common patterns  among assigned to the same directions, the IRD can automatically find paths to prevent collisions  with obstacles. Second, it distinguishes a situation whereby the user is standing on a sidewalk, traffic  intersection, or roadway through analysing the texture and shape of the images, which aids in  preventing any accidents that would result in fatal injuries to the user, such as collisions with  vehicles. In this project, a novel IRD system is presented that provides more safety for people with  impairments and for elderly people. In order to assure safe mobility, our product offers gps live  tracking, GPS navigation and geofencing. With these three functions, it can perceive obstacles of  various types and recognize dangerous situations, and then recommend viable paths to evade them.  First, obstacles are identified using a combination of ultrasonic ones, and then the avoidable  directions are determined using learning based algorithms. Second, in order to prevent collisions  with vehicles at traffic intersections, the situation recognition component distinguishes the type of  place where the user is currently located as a sidewalk, an intersection. This work aims to provide  safe mobility to wheelchair users while they control the wheelchair toward a destination. In order to  support safe mobility, the wheelchair must detect a range of obstacles and dangerous situations in  real environments and generate avoidable paths to prevent collisions with them. In order to achieve  this, a hybrid obstacle avoidance method and a situation recognition method are proposed.

**SYSTEMS DEPLOYED:**

1.Ultrasonic detection and bone conduction system.

2.GPS GSM SOS ALERT SYSTEM

3.GPS GSM LIVE TRACKING SYSTEM

4.GPS LIVE TRACKING SYSTEM

**OUR IMPLEMENTATION:**

![image](https://user-images.githubusercontent.com/79503433/115166519-461f5680-a0d1-11eb-917a-a9fab2de98b7.png) ![image](https://user-images.githubusercontent.com/79503433/115166544-5c2d1700-a0d1-11eb-9d4f-6b974351e176.png)

![image](https://user-images.githubusercontent.com/79503433/115166577-7ff05d00-a0d1-11eb-821d-5d9c04a02bdb.png) ![image](https://user-images.githubusercontent.com/79503433/115166597-95658700-a0d1-11eb-96ef-99fe7c7bf397.png)








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

# LIBRARIES :

**TinyGPSPlus**

A new, customizable Arduino NMEA parsing library A NEW Full-featured GPS/NMEA Parser for Arduino TinyGPS++ is a new Arduino library for parsing NMEA data streams provided by GPS modules.

Like its predecessor, TinyGPS, this library provides compact and easy-to-use methods for extracting position, date, time, altitude, speed, and course from consumer GPS devices.

However, TinyGPS++’s programmer interface is considerably simpler to use than TinyGPS, and the new library can extract arbitrary data from any of the myriad NMEA sentences out there, even proprietary ones.

See Arduiniana - TinyGPS++ for more detailed information on how to use TinyGPSPlus

![image](https://user-images.githubusercontent.com/79503433/115144960-fdce4d00-a06c-11eb-957f-8eef09a2af17.png)
![image](https://user-images.githubusercontent.com/79503433/115144982-1179b380-a06d-11eb-9400-d9611b5c2d90.png)

# SYSTEMS :

**ULTRASONIC DETECTION SYSTEM:**

AN HC SR04 ULTRASONIC SENSOR IS USED TO DETECT THE OBSTACLE IN FRONT OF THE BLIND PERSON AND THE INFORMATION IS SENT TO AN ARDUINO UNO MICROCONTROLLER. IT THEN GIVES THE AUDIO OUTPUT TO  BONE CONDUCTION PHONE FROM THE SOUND RECORDINGS SAVED IN SD CARD.

![image](https://user-images.githubusercontent.com/79503433/115145093-9533a000-a06d-11eb-8817-72cba41746d0.png) ![image](https://user-images.githubusercontent.com/79503433/115166720-3eac7d00-a0d2-11eb-9d5c-4ac042d0f603.png)

![image](https://user-images.githubusercontent.com/79503433/115145228-260a7b80-a06e-11eb-88e7-b47e7c8ccb89.png)

**GPS GSM SOS ALERT SYSTEM:**

WHEN THE BLIND PERSON IS ANY EXEGENCY AND IF THE PUSH BUTTON IS PRESSED, IT COMMUNICATES WITH ARDUINO MICRO CONTROLLER AND IT GETS THE GPS COORDINATES FROM NEO 6M UBLOX GPS MODULE. THEN IT SENDS THOSE INFO TO GSM MODULE WHICH TRANSMITS THE DATA TO THE EMERGENCY CONTACT NUMBERS THROUGH THE SIM CARD PLACED IN IT. 

![image](https://user-images.githubusercontent.com/79503433/115166766-6d2a5800-a0d2-11eb-954e-89e1690c6dca.png)
![image](https://user-images.githubusercontent.com/79503433/115166867-eb86fa00-a0d2-11eb-815c-c0b52a42a7f3.png)


**GPS GSM LIVE TRACKING SYSTEM:**

AN UBLOX NEO 6M GPS MODULE IS USED TO OBTAIN THE LIVE GPS COORDINATES AND SENT TO ARDUINO MEGA MICTRO CONTROLLER WHICH INTURN SENDS THE DATA THAT HAS TO BE TRANSMITTED TO THINGER.IO IOT CLOUD PLATFORM TO THE GSM MODULE AND THROUGH THIS SYSTEM WE WILL BE ABLE TO LIVE TRACK THE PERSON FROM ANYWHERE AND ANYTIME .

![image](https://user-images.githubusercontent.com/79503433/115166918-212be300-a0d3-11eb-8316-fdb7b0aa0c7d.png) ![image](https://user-images.githubusercontent.com/79503433/115166924-2c7f0e80-a0d3-11eb-8d85-af466b6aa0ba.png)



**GPS NAVIGATION SYSTEM:**

AN NEO 6M UBLOX GPS MODULE IS USED TO OBTAIN THE GPS COORDINATES AND IT IS SENT TO ARDUINIO UNO MICRO CONTROLLER FOR PROCESSING. WE USE WAYPOINT METHOD FOR NAVIGATION AND THE ARDUINO CONSTANTLY COMPARES THE LIVE GPS COORDINATES AND THEIR MOVEMENTS .

![image](https://user-images.githubusercontent.com/79503433/115166967-57696280-a0d3-11eb-85a3-707f4991e8dd.png) ![image](https://user-images.githubusercontent.com/79503433/115166980-6223f780-a0d3-11eb-8582-2a9afa11b8a7.png)









