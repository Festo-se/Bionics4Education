![Festo_logo](/Scenario/Image/Logo_Festo.png)
# STEP-BY-STEP
# Adaptability of the trunk 
<br>![](/Scenario/Image/Adaptability_of_the_trunk_photo_final.JPG)

The trunk of elephants is used to breathe, to drink, catch fruit, communicate, etc.. The movements of the trunk are numerous. In this project you will use a light sensor, a touch sensor and a buzzer to create several behaviors depending on the different sensors. You create behaviors like communication, drinking or the sleep.  

## Objective
* You can control an LED with signals.
* You can write if structure.
* You learn how to use a touch sensor.
* You learn how to use a light sensor.
* You leran how to control servomotor.
* You learn to deal with global and local variables.

## Material 
* 1 Microcontroller ESP32
* 9 Jumper cables
* 1 Touch sensor (blue sqaure)
* 1 Passive buzzer (blue)
* 1 Light sensor (red)
* 1 Servomotor
* 2 Cable ties
* 1 3D printed part of: 3D_Structure_Light_sensor.stl (download on github)
* 1 3D printed part of: Light_Box_Top.stl (download on github)
* 1 3D printed part of: Light_Box_Bottom.stl (download on github)
* *ELEPHANT_Adaptability-of-the-trunk_Code_Challenge.ino* (download on github)
<br>![](/Scenario/Image/Adaptability_of_the_trunk_Components.JPG)

# Task 1: Snoring with LED
Simulate the snoring of an elephant thanks to a built-in LED. Therefore, please control the power supply of the LED. The ESP32 only send information to the LED. The LED send no data back to the ESP32. 

## Code:
1. Open the *ELEPHANT_Adaptability-of-the-trunk_Code_Challenge.ino*  file.
<br><img src="/Scenario/Image/bulb_sghr.PNG" alt="ampoule" width="50"/>*Don't hesitate to consult the documentation to better understand the functions used.*
2.*globales variables*
<br>Please define the "PIN_Built_in" variable with the GPIO's number associed to the LED, GPIO 13.
3. *setup()*
<br>Please indicate the GPIO mode. Then you may notice instructions regarding the serial link. Do not hesitate to open the serial monitor.
4. *loop()*
<br>Please, complete the code to turn on and turn off the led. For structures allow you to create snoring.

# Task 2: Make noise with the passive buzzer
Use the passive buzzer and create a noise using a for loop to control the buzzer. 
<br>The passive buzzer has 3 pins: ground (GND), power supply (VCC) and data pin connection (I/O).
<br><img src="/Scenario/Image/passive_buzzer.PNG" alt="Simple LED" width="150"/> <br>(C) This image was created with Fritzing.

## Wiring scheme: 
The picture shows the assembly of the passive buzzer (black) and ESP32 (brown) with cables.
<br>![](/Scenario/Image/Adaptability_of_the_trunk_Task2.PNG) <br>(C) This image was created with Fritzing.

Passive buzzer | ESP32
------------ | -------------
I/O | GPIO 17
VCC | VCC
GND | GND

## Code: 
1. *global variables* 
<br>Please indicate the numbers of the new GPIOs used for passive buzzer.
2. *setup()* 
<br>Please indicate the mode of the passive buzzer.
<br><img src="/Scenario/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*ESP32 sends information to the passive buzzer.*
3. *loop()*
<br>Please create a noise by controlling the power to the buzzer.

```
//Create a noise
for (int i = 0; i <20; i++) 
{
 digitalWrite (PIN_BUZZER, HIGH) ;
 delay (2);
 digitalWrite (PIN_BUZZER, LOW) ;
 delay (2);
}
```

<br> <img src="/Scenario/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*You can change the delay time to get different sounds.*

# Task 3: Create the communication with the touch sensor
Use a touch sensor to comunicate with the elephant: If a contact is detected there is a noise. It may sound like morse language.
<br>The touch sensor has 3 pins: ground (GND), power supply (VCC) and data pin connection (I/O). It sends a high level when a touch is detected.
<br><img src="/Scenario/Image/Touch_sensor.PNG" alt="Simple LED" width="150"/> <br>(C) This image was created with Fritzing.

## Wiring scheme: 
The picture shows the assembly of the passive buzzer (black), the touche sensor (blue) and ESP32 (brown) with cables.
<br>![](/Scenario/Image/Adaptability_of_the_trunk_Task3.PNG) <br>(C) This image was created with Fritzing.

Passive buzzer | ESP32
------------ | -------------
I/O | GPIO 17
VCC | VCC
GND | GND

Touch sensor| ESP32
------------ | -------------
I/O | GPIO 16
VCC | VCC
GND  | GND

## Code: 
1. *global variables* 
<br>Please indicate the numbers of the new GPIOs used for the touch sensor.
2. *setup()* 
<br>Please indicate the mode of touch sensor.
<br><img src="/Scenario/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*ESP32 receives information from the touch sensor.*
2. *loop()* 
<br>Please read the touch sensor's value:

```
//Reading and display the touch value
int State_Touch = digitalRead(PIN_TOUCH);
Serial.printn("State touch");
Serial.println(State_Touch);
```

<br>Please write the code to make a noise each time a contact is detected.
<br><img src="/Scenario/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*Don't hesitate to consult the documentation to better understand how to use the conditions structure.*

# Task 4: Definition of different time of day with the light sensor
Use the light sensor and definie a different time of the day to create several situations.
<br> The light sensor has 3 pins: ground (GND), power supply (VCC) and data pin connection (OUT). The luminosity sensor sends an analog value to its OUT pin. The abalog value is proportional to the amount of light.
<br><img src="/Scenario/Image/luminosity_sensor.PNG" alt="luminoity sensor" width="100"/> <br>(C) This image was created with Fritzing.

## Wiring scheme: 
The picture shows the assembly of the passive buzzer (black), the touche sensor (blue), the light sensor (black) and ESP32 (brown) with cables.
<br>![](/Scenario/Image/Adaptability_of_the_trunk_Task4.PNG) <br>(C) This image was created with Fritzing.

Passive buzzer | ESP32
------------ | -------------
I/O | GPIO 17
VCC | VCC
GND | GND

Touch sensor| ESP32
------------ | -------------
I/O | GPIO 16
VCC | VCC
GND  | GND

Light sensor| ESP32
------------ | -------------
OUT  | GPIO 26
VCC | VCC
GND  | GND

## Code: 
1. *global variables* 
<br>Please indicate the numbers of the new GPIO used for th OUT pin of light sensor.
<br>In addition, please create two global variables:
* one will store the limit value of the amount of light between daytime and midday. I advise you to put the value of 1000.
* other will store the limit value of the amount of light between midday and night. I advise you to put the value of 200.
<br><img src="/Scenario/Image/bulb_sghr.PNG" alt="bulb" width="50"/> *This value can be modified deponds on the room's light.*
2. *setup()*
<br>Please indicate the mode of new GPIO. 
<br><img src="/Scenario/Image/Warning_sghr.PNG" alt="warning" width="50"/>*The ESP32 receives information from the OUT pin.*
3. *loop()* 
<br>Please read the data from the luminosity sensor on the OUT pin and display on the serial monitor.

```
//Reading and diplay the ligth sensor value
int Light_Value = analogRead(PIN_LIGHT);
Serial.println("Light value");
Serial.println(Light_Value,DEC);
```

<br>The value of the variable will be compared to the variables defined before.
* If it is day, communicate with the elephant (touch sensor and passive buzzer).
* If it is night, create a snoring with the LED.
* If it is middle of the day, write "Middle" on serial monitor.
<br><img src="/Scenario/Image/bulb_sghr.PNG" alt="bulb" width="50"/>*Don't hesitate to consult the documentation to better understand how to use the conditions structure.*

# Task 5: Creation of the trunk movement
Control the servomotor and create a trunk's movement for the middle of the day.

## Wiring scheme: 
The picture shows the assembly of the passive buzzer (black), the touche sensor (blue), the light sensor (black), on servomotor and ESP32 (brown) with cables.
<br>![](/Scenario/Image/Adaptability_of_the_trunk_Task5.PNG) <br>(C) This image was created with Fritzing.

Passive buzzer | ESP32
------------ | -------------
I/O | GPIO 17
VCC | VCC
GND | GND

Touch sensor| ESP32
------------ | -------------
I/O | GPIO 16
VCC | VCC
GND  | GND

Light sensor| ESP32
------------ | -------------
OUT  | GPIO 26
VCC | VCC
GND  | GND

Servo motor| ESP32 
------------ | ------------- 
White | GPIO 25
Red | VCC
Black | GND

<br>![](/Scenario/Image/Adaptability_of_the_trunk_Structure.JPG)

## Code:
1. *global variables* 
<br>Please indicate the numbers of the new GPIO used for the servo motor. 
2.*function*
<br>Please complete the movement_tongue() function to create a movement thanks to the servomotor.
<br>For this, please use the Command_servo() function and delay.

```
//The servomotor in 130° position
Command_servo(130);
delay(1000);
```

3. *setup()*
<br>Please indicate the mode of new GPIO used. 
4. *loop()* 
<br>Call the movement_tongue() function so that the tongue moves during the middle of the day.
<br><br><img src="/Scenario/Image/firework_sghr.png" alt="fireworh" width="50"/>Congratulations, you've coded the **Adaptability of the trunk** scenario successfully!