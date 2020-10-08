![Festo_logo](/DIY_Projects/Image/Logo_Festo.png)
# STEP-BY-STEP 
# Cycle of the day 
![Fish](/DIY_Projects/Image/Cycle_of_the_day_photo_finale.JPG)


In this project you will recreate the cycle of the day of the fish. With the fish, we don't talk about sleep, but rather about periods of inactivity when their 
reactivity is reduced. To rest, some species of fish swim more slowly. For this scenario, a light sensor will indicate whether it is day or night. During the day,the fish swims 
fast and during the night, the fish swims slowly. Moreover, unlike humans, fish are unable to manage their inside temperature. The temperature of the aquatic environment in 
which he swims will therefore directly influence his metabolism. Thus, use a temperature sensor to determine if the water is cold or hot , LEDs (blue and red) will light up accordingly.

## Objective
* You can control an LED with signals.
* You can write if structure.
* You learn how to use temperature sensor.
* You learn how to use light sensor.
* You learn how to control a servomotor.
* You learn to deal with global and local variables.

## Material 
* 1 Microcontroller ESP32
* 1 Breadboard
* 5 Jumper cables
* 1 RGB LED
* 1 Resistor 330 Ohm
* 1 Resistor 4.7 kOhm
* 1 Luminosity sensor
* 1 Temperature sensor
* 1 servo motor (Waterproof)
* 1 Glas with hot water (red)
* 1 Glas with cold water (blue)
* 1 3D printed part of: 3D_Structure_Light_sensor (download on github)
* 1 3D printed part of: Light_Box_Bottom.stl (download on github)
* 1 3D printed part of: Light_Box_Top.stl (download on github)
* 2 Cable ties
* *FISH_Cycle-of-the-day_Code_Challenge.ino* (download on github)
![Fish](/DIY_Projects/Image/Cycle_of_the_day_components.JPG)

<img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="ampoule" width="50"/> *Throughout the tutorial, do not hesitate to refer to the documentation.*

# TASK 1: Flashing LED 
Create a color sequence with the two LEDs, one LED is built-in the ESP32 and the second is a RGB LED. The RGB LED brings together 3 simple LEDs. Here, please use the blue pin only. To do this, please control the power supply of the LED. The ESP32 only send information to the LED. The LED send no data back to the ESP32. 
<br><img src="/DIY_Projects/Image/LED_RGB.PNG" alt="RGB LED" width="150"/> <br>(C) This image was created with Fritzing.
 
## Wiring scheme:
The picture shows the Assembly of the breadboard (grey), LED RGB (clear), 330 Ohm resistor and ESP32 (brown) with cables.
![Cycle of the day step 1 ](/DIY_Projects/Image/Cycle_of_the_day_Task1.PNG) <br>(C) This image was created with Fritzing.

RGB LED | Breadbord
------------ | -------------
Blue | GPIO 16 
Back | GND

<img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/> *The LED must be in series with a 330 Ohm resistor.*
## Code:
1. Open the *FISH_Cycle-of-the-day_Code_Challenge.ino*  file.
<br> <img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="ampoule" width="50"/> *Don't hesitate to consult the documentation to better understand the functions used.*
2. *global variables*
<br>In order to simplify understanding of the code, a global variable is associated with each GPIO number used. Associate the variabe "PIN_LED_B" to the number's GPIO 16. 
3. *setup()*
<br>First, indicate the GPIO mode. Then you may notice instructions regarding the serial link. Do not hesitate to open the serial monitor.
4. *loop()*
<br>Pleas power on and off LEDs to create a color sequence.

# TASK 2: Temperature sensor  
Use the temperature sensor and show the result with red LED (warm) or blue LED (cold). The temperature sensor has 3 pins : ground (black), power supply (red) and data pin connection (yellow).
<br>After reading the sensor value via the connection pin, light up the red LED if it is hot or blue LED if it is cold.
<br><img src="/DIY_Projects/Image/temperature_sensor.PNG" alt="temperature sensor" width="80"/> <br>(C) This image was created with Fritzing.

## Wiring scheme: 
The picture shows the assembly of the breadboard (grey), LED RGB (clear), 330 Ohm resistor, temperature sensor, 4.7 kOhm  and ESP32 (brown) with cables.
![Cycle of the day step 2 ](/DIY_Projects/Image/Cycle_of_the_day_Task2.PNG) <br>(C) This image was created with Fritzing.
 
RGB LED | Breadbord
------------ | -------------
Blue | GPIO 16 
Back | GND                               
 
Temperature sensor | Breadboard 
------------ | ------------- 
Yellow | GPIO 17
Black | GND
Red | VCC
 
<img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/> *Don't forget the 4.7km Ohm resistor.*
## Code: 
1. *global variables* 
<br>Please create a variable that stockes the limmit temperature between hot and cold.For a first test, this value can be 22. 
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*You can take the sensor on you hands to increase the temperature.*
2. *setup()* 
<br>Please indicate the mode of the temperature sensor.
<br><img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/> *The ESP32 receives information from the temperature sensor*
3. *loop()*
<br>Please read the temperature and display it on the serial monitor.

```
//Reading and display the temperature (°C) 
sensors.requestTemperatures(); 
float Temperature_Value = sensors.getTempCByIndex(0);
Serial.println("Temperature");
Serial.print(Temperature_Value);
Serial.println("ºC");
```

<br>Please light the red LED if the temperature is hot or blue LED if the temperature is cold by utilizing the limit temperature.
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*Don't hesitate to consult the documentation to better understand how to use the conditions structure.*

# Task 3: Luminosity sensor 
Use the luminosity sensor and send an analog value proportional to the amount of light to its OUT pin.
The luminosity sensor has 3 pins : ground (GND), power supply (VCC) and data pin connection (OUT).
<br> <img src="/DIY_Projects/Image/luminosity_sensor.PNG" alt="luminoity sensor" width="100"/> <br>(C) This image was created with Fritzing.

## Wiring scheme: 
The picture shows the Assembly of the breadboard (grey), LED RGB (clear), 330 Ohm resistor, temperature sensor, 4,7 kOhm light sensor and ESP32 (brown) with cables.
![Cycle of the day step 3](/DIY_Projects/Image/Cycle_of_the_day_Task3.PNG) <br>(C) This image was created with Fritzing.
 
RGB LED | Breadbord
------------ | -------------
Blue | GPIO 16 
Back | GND                               

Temperature sensor | Breadboard 
------------ | ------------- 
Yellow | GPIO 17
Black | GND
Red | VCC
 
Luminosity sensor | ESP32 
------------ | ------------- 
OUT | GPIO 26
VCC | VCC
GND | GND

## Code: 
1. *global variables* 
<br>Please indicate the numbers of the new GPIO used for th OUT pin of luminosity sensor. In addition, create a global variable that will store the value of the limit of the amount of light between day and night. I'd advise you to put the value of 500.
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/> *This value can be modified deponds on the room's light.*
2. *setup()*
<br>Please indicate the mode of new GPIO used. 
<br><img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/> *The ESP32 receives information from the OUT pin.*
3. *loop()* 
<br>Please read the data from the luminosity sensor on the OUT pin and display on the serial monitor.

```
//Reading and display the luminosity
int Luminosity_Value = analogRead(PIN_LIGHT_SENSOR); 
Serial.println("Light");
Serial.println(Luminosity_Value,DEC)
```

<br>The value of the variable will be compared to the limit between day and night defined before. If the value is superior than or equal to the limit, you can display " Day" 
,otherwise "Night".
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*Don't hesitate to consult the documentation to better understand how to use the conditions structure.*

# Task 4: Servo motors 
Send information from the ESP32 to the servo motor with pin GPIO 25.
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*Don't hesitate to consult the documentation to know wich function you can use to control the servomotor.*

## Wiring scheme: 
The picture shows the assembly of the breadboard (grey), LED RGB (clear), 330 Ohm resistor, temperature sensor, 4.7 kOhm, 1 servomotor and ESP32 (brown) with cables.
![Cycle of the day step 4](/DIY_Projects/Image/Cycle_of_the_day_Task4.PNG) <br>(C) This image was created with Fritzing.

RGB LED | Breadbord
------------ | -------------
Blue | GPIO 16 
Back | GND                               
 
Temperature sensor | Breadboard 
------------ | ------------- 
Yellow | GPIO 17
Black | GND
Red | VCC
 
Luminosity sensor | ESP32 
------------ | ------------- 
OUT | GPIO 26
VCC | VCC
GND | GND

Servo motor| ESP32 
------------ | ------------- 
White | GPIO 25
Red | VCC
Black | GND

<br>![Cycle of the day step 4](/DIY_Projects/Image/Cycle_of_the_day_structure.JPG)

## Code:
1. *global variables* 
<br>Please indicate the numbers of the new GPIO used for the servo motor. 
<br>In addition, please create a global variable that will stock the value of the delay between different motor's instructions. This value determines the speed of the servo 
motor. I'd advise you to put the value of 500 and test several value to undersatand how it works. 
2. *setup()*
<br>First, create the connection for the servo motor:

```
servo.attach(PIN_SERVO);
```

<br>Then,you can initialize the angle of the servomotor:

```
servo.write(90);
```

3. *loop()* 
<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*Please comment the next code to understand how a servomotor works.* 
<br>Please create a servo motor movement:

```
// SERVO MOVEMENT 
// the servomotor moves to be 110° position
servo.write(110); 
// wait Temporization ms
delay(Temporization); 
// the servomotor moves to be 70° position
servo.write(70);
// wait Temporization ms 
delay(Temporization);
```

<br><img src="/DIY_Projects/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*You can modify the swimming amplitude by changing the degree set points and modify the swimming speed by changing the delay (Temporization value), make tests to understand how it works!* 

# Task 5: Final code 
Create the final code. The speed of the fish depends on the luminosity: The fish swim faster by day than by night. The color of the LED depends on the temperature: when it's hot the red LED lights up, the blue one otherwise.
The wiring scheme is the same that task 4.

## Code:
1. *global variables* 
<br>Please create two variables:
* The first is the delay for the speed in day.
* The second is the delay for the speed in night.

```
//Temporization determines the speed of the fish
int Temporization=500; 
//Delay_Day determines the speed for the day
int Delay_Day=500;
//Delay_Nightdetermines the speed for the night  
int Delay_Night = 2000;
```

<br><img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/> *If the delay increase, the speed decrease.*
<br>3. *loop()* 
<br><img src="/DIY_Projects/Image/Warning_sghr.PNG" alt="warning" width="50"/> *Remember to uncomment the task 3 code.*
<br>Please modify the **if structure** to change the color and servo motor's speed wich depends on the quantity of light and the temperature.
* Day: The speed is definied with Delay_Day.
* Night: The speed is definied with Delay_Night. 
<br>The variable *Temporization* is egal to *Delay_Day* or *Delay_Night* depending on the quantity of light.
* Hot: The red LED light up.
* Cold: The blue LED light up.

<br> <br><img src="/DIY_Projects/Image/firework_sghr.png" alt="fireworh" width="50"/> Congratulations, you've coded the **Cycle of the day** scenario successfully!
