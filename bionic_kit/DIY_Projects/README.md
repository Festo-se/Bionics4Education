![Festo_logo](/bionic_kit/DIY_Projects/Image//Logo_Festo.png)
# *Documentation*
The Getting_started document gives you an overview of the scenarios for the bionics kit. You get information about how it is structured. Also you can find background information on the material and basic programming in Arduino IDE, like code structure, comments and different functions.
There are 3 scenarios for each animal, which are matched to 3 different difficulty levels. Here is an overview:

Level		| Chameleon		| Elephant					| Fish		
------------ | ------------- | ------------- | ------------- 				
Picture	|<img src="/bionic_kit/DIY_Projects/Image/Photo_Chameleon.PNG" alt="cameleon" width="100"/> 		| <img src="/bionic_kit/DIY_Projects/Image/Photo_Elephant.PNG" alt="elephant" width="100"/> | <img src="/bionic_kit/DIY_Projects/Image/Photo_Fish.PNG" alt="fish" width="100"/>					|
1			| Camouflage		|Temperature				|A little heart			
2			| Environment	| Adaptability of the trunk	| Cycle-of-the-day		
3			| Food			| Fruit				| Swimming Competition	

Each scenario consists of the following documents:

Filename								| Content											| Where to find		
------------ | ------------- | -------------  
ANIMAL_Scenario_Challenge.md			| Documentation and Tasks to build up the scenario 	| GitHub
Animal_Scenario_Code_Challenge.ino		| Start code for the Scenario						| GitHub
ANIMAL_Scenario_Code_Solution_Task1.ino | Solution code for each Task						| GitHub
ANIMAL_Scenario.MOV 					| Video how the scenario look like					| https://www.bionics4education.com
Content.STL 							| CAD files for 3D printing							| GitHub

You need for each scenario some additional material. The material is listed in the documentation file of each scenario. Here is a list of what you have to buy:

## Overview material for Arduino:
|Material				|Quantity
------------ | ------------- 
Mini breadboard			|2			
RGB LED					|1						
Resistor 330 Ohm		|3			
Resistor 4.7k Ohm		|1		
0.01 or 0.1 µF capacitor |1	
Color sensor			|1			
Light sensor			|1				
Touch sensor			|1			
Temperature sensor		|1				
Vibrating motor			|1				
3x3 cm blue paper		|1			
3x3 cm red paper		|2			
3x3 cm green paper		|1			
blue ball, d = 2 cm		|1			
red ball, d = 2 cm		|1			
green ball, d = 2 cm	|1			

Total amount about 40€.

## Background information on the material

* **ESP32:**

<br>The ESP 32 is a microcontroller that brings together 4 essential elements: a processor, memory and peripheral units and input-
output interfaces. You can control the inputs and outputs with your computer via *Arduino IDE*. In Arduino IDE you can write code and flash it on the ESP 32. Therefore select the right port: tools -> port -> COM XX.

<br> WARNING. There is two versions of the Bionics Kit.  If you have the version 2, you will find information related to your controller to the following file : 
Five GPIO's of the ESP32 modul are carried out to which you can connect sensors and actuators:
![](/bionic_kit/DIY_Projects/Image/ESP32_Bionics_Kit.png)

* **Breadboard:**
<br>A breaboard is a board that allows you to connect all of your elements without soldering.
<br>For this, different locations are connected together. The basic structure consists of two rails as illustrated below: Component rails (1) and Power rails (2) with two terminals. One negative terminal marked blue or black and one positive terminal marked red.
![Breadboard_caption](/bionic_kit/DIY_Projects/Image/breadboard.PNG)

## Arduino IDE 
The Arduino IDE tool is an integrated development environment that allows you to write and import code into the EPS32 microcontroller.

## Coding with Arduino IDE
The basic structure of Arduino code consists of three parts: global initialization, setup() and loop(): 

```
//global initialization, e.g. GPIO, global variables


// setup components
setup()
{
	//put your setup code here to run once;
}

// code is run in loops
void loop()
{
	//put your main code here to run repeatedly;
}
``` 

### Variables
A variable is the name for a space in the memory of the microcontroller. There are several types of variables: 

Type | Function | Example
------------ | ------------- | ------------- 
*int* | For storage of whole numbers | *int* number_player = 5;
*float*| For storage of floating | *float* PI_value = 3.14;
 
<br>Global variables: Variables that are defined outside of functions and can be used throughout the code.
<br>Local variables: Variables defined in a function. Local variables can only be used only in the function. 
<br>*Example:*

```
// define global variable
int c = 0;

//define local variable in the function addition()
void addition()
{
	//define local variable a and b
	int a=2;
	int b=3;
	// calculate c by adding a and b
	c=a+b;
}
```

### Functions
<br>The Arduino code has two main functions: 
* *setup()*: the code written in this function will be executed once only.
* *loop()*: the code written in this function will be executed repeatedly as long as the ESP32 is powered.

The *setup()* and *loop()* functions are obligatory for the proper functioning of the code. However, other functions can be created. These functions can be called later in 
the two main functions.

```
void name_function()
{
	// instructions of the function
}

void setup()
{
	// setup components; the code runs once;
	name_function();

}

void loop()
{
	// put your main code here to run repeatedly;
}
```

### Comments 
The microcontroller executes the instructions from top to bottom. It is possible to add comments in order to make the code more readable. These comments will not be read by the microcontroller. There are two ways to add comments:
* // comment
* /*comment*/

### Conditional: if loop 
<br>The structure of the conditions makes it possible to initiate different instructions according to different conditions. As mentioned earlier, the comparison returns true or 
false. This result is used for the if structure.
If the condition is true the instructions are executed, otherwise the following condition is tested. If none of these conditions is true, we execute the instructions of *else*.

```
if condition_1 {
	// instruction_1
}

else if condition_2 {
	// instruction_2
}

else if condition_3 {
	// instruction_3
}

else {
	// instruction_4
}
```

### Mathematical operators 
Mathematical operators are used to apply logical operations to variables.
Symbol | Meaning
------------ | -------------
+| addition
/| division

*Example:*
```
int result = 0;

void operation()
{
	int a = 10;
	int b = 6;
	result = (a+b)/2;
}
```
<br>After executing the *operation()* function, the variable *result* is equal to 8.

* Logical operators  
A logical operators returns a boolean, that is either true or false. For example, 5 > 3 returns true and 5 < 3 returns false. There are several logical operators:

Symbol | Meaning
------------ | -------------
< 	| lower
<=	| lower or equal
\> 	| superior
\>= | superior or equal
== 	| equal
!= 	| different 

A condition can be made up of several logical operators:
Symbol | Meaning
------------ | -------------
&& 				| AND
&#124; &#124; 	| OR

*Example:*

```
int a = 1;

if((a >= 2) && (a < 5)){
 // instruction_1
}

else {
 // instruction_2
}
```

<br>Here, *a* is not between 2 and 5. Thus, instructions 2 will be executed.

### For loop 
The for loop makes it possible to carry out a defined number of times of instructions.

```
for (int i = 0; i < a; i = i + 1){
 // instruction
}
```

<br>A variable i is initialized to 0. The variable will be incremented by 1 each time it passes through the for loop and the instructions inside the for loop are executed. When the variable reaches the value of a, we exit the for loop and the rest of the code is executed.

*Example:*

```
int sum = 0;

for (int i = 0; i < 5; i = i + 1){
 sum = sum + i
}
```

<br>Here, we add: 0 + 1 + 2 + 3 + 4. After the executing the for loop the variable sum is equal to 10.

### While loop
The while loop is used to execute the instructions as long as the condition is true. So first of all we check the condition. If it is true, we execute the instructions. 
Otherwise, we skip the loop.

```
while (condition) {
 // instruction
}
```

### Do-While loop
The do-while loop is used to execute the instructions as long as the condition is true. Unlike the while loop, we execute the instructions for the first time and then check that 
the condition is true to execute the instructions again.

```
do {
	// instruction
}
while (condition);
```

## Predefined functions
Some functions are required very often. Such functions are predefined in a library and can be used. Some functions are pre-installed in Arduino. For special sensors you have to install *libraries* (tools -> libraries -> search -> install), insert it in the code and only then you can use the function.
This saves you time-consuming coding.

* **pinMode**(*number_GPIO*, *mode*);
<br>Used to indicate whether the GPIO is defined as: 
<br>-> output mode: *OUTPUT* (ESP32 send information) 
<br>-> input mode: *INPUT* (ESP32 receives information)
* **delay**(*duration*);
<br>Allows you to enter a time delay with *duration* in ms.
* **digitalWrite**(*number_GPIO*, *level*);
<br>Used to power the GPIO in the high state: *HIGH*, otherwise the GPIO is in the low state: *LOW*.
* **Serial.println**("*text*");
<br>Display text on the serial monitor.
<br>You find more predefined functions in the ESP32 documentation online.

## Compile you code 
<br>This tab allows you to check and upload the code to the microcontroller.
<br>![upload](/bionic_kit/DIY_Projects/Image/uploaded_Arduino_ide.PNG)
<br>This tab opens the serial monitor. It allows you to "communicate" with the ESP32 and to display a text or a variable.
<br>![monitor_serial](/bionic_kit/DIY_Projects/Image/serial_monitor.PNG)
<br>Once the code has been verified and uploaded, if everything has worked, the following message should appear:
<br>![upload_right](/bionic_kit/DIY_Projects/Image/Upload_good.PNG)

## 3D Parts 
To integrate the sensors into the transparent body, you can use the following parts:
* Box for the color sensor:
	* Color_Box_Top.stl
	* Color_Box_Bottom.stl
<br><img src="/bionic_kit/DIY_Projects/Image/Box_color_sensor.JPG" alt="i" width="300"/> <img src="/bionic_kit/DIY_Projects/Image/Box_color_sensor_Built.jpg" alt="i" width="300"/> 
* Box for the light sensor:
	* Light_Box_Top.stl
	* Light_Box_Bottom.stl
<br><img src="/bionic_kit/DIY_Projects/Image/Box_light_sensor.JPG" alt="i" width="300"/> <img src="/bionic_kit/DIY_Projects/Image/Box_light_sensor_Built.jpg" alt="i" width="300"/> 
* The structure:
	* 3D_Structure_Color_sensor_and_Breadboard.stl
	* 3D_Structure_Light_sensor.stl
<br><img src="/bionic_kit/DIY_Projects/Image/Photo_3D_Structure.JPG" alt="i" width="300"/> <img src="/bionic_kit/DIY_Projects/Image/3D_strcuture_built.jpg" alt="i" width="300"/> 
<br><img src="/bionic_kit/DIY_Projects/Image/Box_and_structure_Color.JPG" alt="i" width="300"/> <img src="/bionic_kit/DIY_Projects/Image/Box_and_structure_light.JPG" alt="i" width="300"/>
