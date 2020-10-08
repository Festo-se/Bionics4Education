![Festo_logo](/DIY_Projects/Image/Logo_Festo.png)
# STEP-BY-STEP
# Camouflage 
![Cameleon](/DIY_Projects/Image/Camouflage_photo_finale.jpg)

The chameleon is known for its bright colors. Indeed, the chameleon has the incredible characteristics of being able to change colors. Thus, thanks to a color sensor and an LED you will be able to reproduce this characteristic. Indeed, the LED will light up in the color of the support on which the chameleon is.

## Objective
* You can control an LED with signals.
* You can write if structure. 
* You learn how to use color sensor.
* You learn to deal with global and local variables.

## Material 
* 1 Microcontroller ESP32
* 1 Breadboard (orange)
* 12 Jumper cables
* 1 RGB LED
* 1 Color sensor (red square)
* 3 Resistors 330 Ohm
* 1 3D printed part of: 3D_Structure_Color_sensor_and_Breadboard.stl (download on github)
* 1 3D printed part of: 3D_Structure_Light_sensor.stl (download on github)
* 1 3D printed part of: Color_Box_Top.stl (download on github)
* 1 3D printed part of: Color_Box_Bottom.stl (download on github)
* 5 Cable ties
* *CHAMELEON_Camouflage_Code_Challenge.ino* (download on github)
<br>![Cameleon](/DIY_Projects/Image/Camouflage_Component.JPG)

<img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*Throughout the tutorial, do not hesitate to refer to the documentation.*

# Task 1: Flashing LED 
Flash an LED and turn it on and then turn it off repeatedly. Control the power supply of the LED to turn it on and off. The ESP32 only send information to the LED. The LED send no data back to the ESP32. 
<br><img src="/DIY_Projects/Image/LED.PNG" alt="Simple LED" width="50"/> <br>(C) This image was created with Fritzing.

## Wiring scheme:
The picture shows the assembly of the breadboard (grey), LED (transparent), 330 Ohm resistor, and ESP32 (brown) with cables.
![Camouflage_Task1](/DIY_Projects/Image/Camouflage_Task1.PNG) <br>(C) This image was created with Fritzing.

LED | Breadbord
------------ | -------------
Red | GPIO 16 
Back | GND

<img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/> *The LED must be in series with a 330 Ohm resistor.*

## Code:
1. Open the *CHAMELEON_Camouflage_Code_Challenge.ino*  file.
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="ampoule" width="50"/>*Don't hesitate to consult the documentation to better understand the functions used.*
2. *global variables*
<br>In order to simplify understanding of the code, a global variable is associated with each GPIO number used. Associate the variabe "PIN_LED" to the number's GPIO 16. 
3. *setup()*
<br>First, yindicate the GPIO mode. Then you may notice instructions regarding the serial link. Do not hesitate to open the serial monitor.
4. *loop()*
<br>Please power on and off the LED. You can change the delay value to change the speed of the flashing.
 
# Task 2: RGB LED 
Control an RGB LED and display a sequence of colors. For example, blue, then green and finally red. An RGB LED brings together 3 simple LEDs as studied in the previous task. The ESP32 only send information to the LED. The LED send no data back to the ESP32.  
<br><img src="/DIY_Projects/Image/LED_RGB.PNG" alt="RGB LED" width="150"/> <br>(C) This image was created with Fritzing.
 
## Wiring scheme: 
The picture shows the Assembly of the breadboard (grey), LED RGB (clear), 330 Ohm resistors, and ESP32 (brown) with cables.
![Camouflage_Task2](/DIY_Projects/Image/Camouflage_Task2.PNG) <br>(C) This image was created with Fritzing.

RGB LED | Breadbord
------------ | -------------
Red | GPIO 16
Blue | GPIO 17
Green | GPIO 26
Back | GND

<img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/>*Each LED pin must be in series with a 330 Ohm resistor.*

## Code: 
1. *global variables* 
<br>Please indicate the numbers of the new GPIOs used for RGB LED.
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="ampoule" width="50"/>*Think to change the name of the variable, a name can't be used serveral times.*
2. *setup()* 
<br>Please indicate the mode of each pin.
3. *loop()*
<br>Please create a color sequence. To make a color appear, you have to turn on the pin of this color and turn off the other two pins. Don't forget to use delay!

```
//Blue
digitalWrite(PIN_LED_B, HIGH);
digitalWrite(PIN_LED_G, LOW);
digitalWrite(PIN_LED_R, LOW);
delay(2000);
```

<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*If you feed several pins, you get a mixture and thus new colors like purple or cyan.*

# Task 3: Final code
Turn on the RGB LED of the same color as the sheet on which the chameleon is placed. For this, please use a color sensor to determine the object's color. The 
color sensor has 8 pins: ground (GND), supply power (VCC), configuration pins (S0,S1,S2,S3) and a data pin (OUT). The color sensor sends a value (proportional to the frequency) 
according to the color.
<br><img src="/DIY_Projects/Image/color_sensor.PNG" alt="color_sensor" width="400"/> <br>(C) This image was created with Fritzing.

## Wiring scheme: 
The picture shows the assembly of the breadboard (grey), LED RGB (clear), 330 Ohm resistors, the color sensor (blue) and ESP32 (brown) with cables.
![Camouflage_Task3](/DIY_Projects/Image/Camouflage_Task3.PNG) <br>(C) This image was created with Fritzing.
 
RGB LED | Breadbord
------------ | -------------
Red | GPIO 16
Blue | GPIO 17
Green | GPIO 26
Back | GND

Color sensor | ESP32
------------- | ------------- 
VCC | VCC
GND | GND 
S0| VCC 
S1 | VCC 
S2 |VCC 
S3 | GND
E0| GND 
OUT| GPIO 25

<br>![Camouflage_Task3](/DIY_Projects/Image/Camouflage_strcuture.JPG)

## Code: 
1. *global variables* 
<br>Please indicate the numbers of the new GPIO used for color sensor.
2. *setup()*
<br>Please indicate the mode of OUT pin.
<br><img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/>*The ESP32 receives information from the color sensor.*
3. *loop()* 
<br>Please read the color sensor's value.

```
//Reading the color
int Current_Frequency = pulseIn(PIN_COLOR, HIGH); //read the data GPIO OUT 
Serial.println("Color Frequency");
Serial.println(Current_Frequency);//display the frequency on serial monitor
delay(500);
```

<br>You can change the value of the global variables Blue, Green and Red according to the values you get when the sensor has to detect the color.
<br><img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/>*This value is not the same in or out body.*
<br>The value of the variable will be compared to the reference values of each color. Using an if structure, write the code to illuminate the LED of the same colour as the one 
detected with the sensor.
<br><br><img src="/DIY_Projects/Image/firework_sghr.png" alt="fireworh" width="50"/>Congratulations, you've coded the **Camouflage** scenario successfully!
