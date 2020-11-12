![Festo_logo](/DIY_Projects/Image/Logo_Festo.png)
# STEP-BY-STEP
# Temperature
![Elephant](/DIY_Projects/Image/Temperature_photo_finale.JPG)

## Objective
The elephant's trunk is very much used by the animal. For example, the elephant uses its trunk to bring water to its mouth. For this scenario, you're going to use a temperature sensor. If it's hot, the LED is red. Then you must bring water to the elephant to make him drink. Thus, the temperature sensor will be immersed in water. If the temperature will decrease the LED turns blue and the elephant drinks: the clamps open and close.

## Material 
* 1 Microcontroller ESP32
* 1 Breadboard (orange)
* 6 Jumper cables
* 1 Temperature sensor  
* 1 LED red 
* 1 LED RGB 
* 1 Servomotors
* 1 Glas with hot water (red)
* 1 Glas with cold water (blue)
* 8 3D printed part of: Plate.stl (download on github)
* *ELEPHANT_Temperature_Code_Challenge.ino* (download on github)
![Elephant](/DIY_Projects/Image/Temperature_Component.JPG)
<img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="ampoule" width="50"/>*Throughout the tutorial, do not hesitate to refer to the documentation.*

# Task 1: Flashing LED
Flash an LED and turn it on and then turn it off repeatedly. Control the power supply of the LED to turn it on and off. The ESP32 only send information to the LED. The LED send no data back to the ESP32. 
<br><img src="/DIY_Projects/Image/LED.PNG" alt="Simple LED" width="50"/> <br>(C) This image was created with Fritzing.

## Wiring scheme:
The picture shows the assembly of the breadboard (grey), LED (red), 330 Ohm resistor and ESP32 (brown) with cables.
![Temperature step1](/DIY_Projects/Image/Temperature_Task1.PNG) <br>(C) This image was created with Fritzing.

LED | Breadbord
------------ | -------------
Red | GPIO 16 
Back | GND

<img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/>*The LED must be in series with a 330 Ohm resistor.*

## Code:
1. Open the *ELEPHANT_Temperature_Code_Challenge.ino*  file.
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="ampoule" width="50"/>*Don't hesitate to consult the documentation to better understand the functions used.*
2. *global variables*
<br>In order to simplify understanding of the code, a global variable is associated with each GPIO number used. Associate the variabe "PIN_LED" to the number's GPIO 16. 
3. *setup()*
<br>First, indicate the GPIO mode. Then you may notice instructions regarding the serial link. Do not hesitate to open the serial monitor.
4. *loop()*
<br>Please power on and off the LED. You can change the delay value to change the speed of the flashing.
 
# Task 2: RGB LED 
Control the RGB LED and display a sequence of colors, for example, blue and red. An RGB LED brings together 3 simple LEDs as studied in the previous task. The ESP32 only send information to the LED. The LED send no data back to the ESP32.  
<img src="/DIY_Projects/Image/LED_RGB.PNG" alt="RGB LED" width="150"/> <br>(C) This image was created with Fritzing.
 
## Wiring scheme: 
The picture shows the assembly of the breadboard (grey), LED RGB (clear), 330 Ohm resistor and ESP32 (brown) with cables.
![Temperature_step 2 ](/DIY_Projects/Image/Temperature_Task2.PNG) <br>(C) This image was created with Fritzing.
 
RGB LED | Breadboard
------------ | -------------
Red | GPIO 16
Blue | GPIO 17
Back | GND

<img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/>*Each LED pin must be in series with a 330 Ohm resistor.*

## Code: 
1. *global variables* 
<br>Please indicate the numbers of the new GPIOs used for RGB LED.
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="ampoule" width="50"/>*Think to change the name of the variable, a name can't be used serveral times.*
2. *setup()* 
<br>Please indicate the mode of each pin.
3. *loop()*
<br>Please create a color sequence. To make a color appear, please trun on a color and turn off the other color. Don't forget to use delay!

```
//Red 
digitalWrite(PIN_LED_R,HIGH); 
digitalWrite(PIN_LED_B,LOW);
delay(500);
```

# Task 3: Temperature sensor 
Use the temperature sensor: After reading the sensor value via the connection pin, light up the red LED if it is hot or the blue LED if it is cold.
<br> The temperature sensor has 3 pins : ground (black), power supply (red) and data pin connection (yellow).
<br><img src="/DIY_Projects/Image/temperature_sensor.PNG" alt="temperature sensor" width="80"/> <br>(C) This image was created with Fritzing.
<br>Please define a variable in order to establish the limit between hot and cold. The LED is red if the temperature is hot, otherwise the LED is blue and the clamps move. 

## Wiring scheme: 
The picture shows the assembly of the breadboard (grey), LED RGB (clear), 330 Ohm resistor, temperature sensor, 4.7 kOhm  and ESP32 (brown) with cables.
![Temperature step 3](/DIY_Projects/Image/Temperature_Task3.PNG) <br>(C) This image was created with Fritzing.
 
RGB LED | Breadboard
------------ | -------------
Red | GPIO 16
Blue | GPIO 17
Back | GND

Temperature sensor | Breadboard 
------------ | ------------- 
Yellow | GPIO 26
Black | GND
Red | VCC

## Code : 
1. *global variables* 
<br>Please create a variable that stockes the value of the limit between cold and hot temperature. I'd advise you to put 20.
2. *loop()* 
<br>The loop () function must read the data from the temperature sensor. To do this, you use the follow intructions :

```
//Reading and display the temperature (°C) 
sensors.requestTemperatures(); 
float Temperature_Value = sensors.getTempCByIndex(0);
Serial.println("Temperature");
Serial.print(Temperature_Value);
Serial.println("ºC");
```
   
<br>Compare the value of the variable with the limit value. Use an if structure and write the code to illuminate the LED of the same colour as the one detected with the sensor. 
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*Don't hesitate to consult the documentation to better understand how to use the conditions structure.*

# Task 4: Servo motor and a final code
Control the servo motor in a way that it will open and close the clamps. Write the final code that will set the clamps in motion when the temperature is cold.
## Wiring scheme : 
The picture shows the Assembly of the breadboard (grey), LED RGB (clear), 330 Ohm resistor, temperature sensor,4.7 kOhm, one servomotor and ESP32 (brown) with cables.
![Temperature step 4](/DIY_Projects/Image/Temperature_Task4.PNG) <br>(C) This image was created with Fritzing.
 
RGB LED | Breadboard
------------ | -------------
Red | GPIO 16
Blue | GPIO 17
Back | GND

Temperature sensor | Breadboard 
------------ | ------------- 
Yellow | GPIO 26
Black | GND
Red | VCC
 
Servo motor| ESP32 
------------ | ------------- 
White | GPIO 25
Red | VCC
Black | GND

<br>![Temperature step 4](/DIY_Projects/Image/Temperature_Structure.JPG)
## Code : 
1.*globales variables*
<br>Please indiacte the new GPIO used by the servomotor. 
2. *setup()*
<br>Please create the connection between the servomotor and the ESP32:

```
//match between servomotor and the number pin specified 
servo.attach(PIN_SERVO);
```

3. *loop()* 
<br>Please use the following instructions to control a servo motor:

```
// Servo movement
// the servomotor moves to be 115° position
servo.write(115); 
// wait 3s
delay(3000); 
// the servomotor moves to be 45° position
servo.write(45);
// wait 3s
delay(3000);
```

<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*Don't hesitate to consult the documentation to better understand how to use the **write** function.*
<br>Now, please add the clamps movement in if structure so that the clamps close and open when the temperature is cold.
<br><br><img src="/DIY_Projects/Image/firework_sghr.png" alt="fireworh" width="50"/> Congratulations, you've coded the **Temperature** scenario successfully!
