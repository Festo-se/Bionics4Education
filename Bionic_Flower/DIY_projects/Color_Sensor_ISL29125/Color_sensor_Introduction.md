# Color sensor Introduction 

<br><img src="../img/Color_sensor.JPG" alt="RGB LED" width="800"/>

Each color is a mixture of three components: red, green and blue. The color sensor can measure the value of these three components and thus detect the color present on the sensor.  

However, the color sensor requires calibration as the value of the components depends on the ambient luminosity. So to take this brightness into account, we are going to take the RGB values for white (most light gets reflected - bright) and black (most light gets absorbed - dark).  So we will have the two boundary values (code: 0,0,0 - black and code 255,255,255 - white). Then each component of a color will have a value between 0 and 255.
At the end of this introduction you will be able to understand how to use the values from the color sensor and understand the functions involved. 

In this introduction you will use the color sensor to illuminate the flower with the same color as the color that has been detected.
 
<br><img src="../img/Diversity_color_sensor.JPG" alt="RGB LED" width="800"/>


We use the ISL29125 color sensor.  This sensor use  the I2C communication, so it uses the SCL and SDA pins.

Open the *Color_ISL29125.ino* file.
# Library 
To use the color sensor you need to include two libraries : 
* As mentioned above, the sensor uses I2C communication, so this library is necessary.
```
// I2C communication library
#include <Wire.h>
```
* This library is needed to use the ISL29125 sensor particularly.
```
// color sensor's library
#include "SparkFunISL29125.h"
```
# Variable global 
* You need to define the I2C GPIO for the communication. The Bionic Flower uses the GPIO 4 for the SDA pin and the GPIO 5 for the SCL pin.
```
//I2C communication pin 
#define I2C_SDA 4
#define I2C_SCL 5
```
* The advantage of I2C communication is that it is possible to connect several sensors on the same pins. However, each sensor has a different address to distinguish them.  The address of the color sensor is 0x44.
```
//Address of the color sensor
#define ADD_COLOR 0x44
```
* These 6 variables are used when we measure the RGB values of our two boundary values i.e. black and white.
```
// R G B value for the white color
unsigned int redhigh , greenhigh, bluehigh;
// R G B value for the black color
unsigned int redlow, greenlow, bluelow;
```
* This 3 variables will be used when later measuring the desired color that will be detected.. 
```
// R G B value for the color which has been detected 
unsigned int R,G,B;
```
* This line allows to create the sensor's object. 
```
// Color sensor
SFE_ISL29125 RGB_sensor;
```
# *BW_calibration()* function
<br> As mentionned above, we need to calibrate the sensor, it means measuring the RGB value for the white and the black color first. The *BW_calibration()* allows to do that. This function needs to be appeal just one time. 
<br> To have the value of the red components, you can use the next instruction : 
```
RGB_sensor.readRed();
```
* The communication with the color sensor start : 
```
// Color sensor selected, start the transmission
   Wire.beginTransmission(ADD_COLOR);
```
* First the RGB value of the white color is measured, then for the black color. 
* The communication is finished. 
```
   // The end of the transmission
    Wire.endTransmission();
 ```
# *Read_RGB()* function
<br> The *Read_RGB()* allows to read the RGB values for the color which we are measuring 
* The communication with the color sensor start. 
<br> As mentioned above, to reduce the influence of ambient light, we will restrict the values of color components in the range from 0 to 255 to get an RGB code.
* Therefore, we use transition variables :
```
//Color sensor parameters
  unsigned int red_value, green_value ,blue_value;
```
* First, the RGB value of the white is measured, after that for black . 
* The *map()* and the *constrain()* functions allow to restrict the values of color components in the range from 0 to 255 depending on the white and black components. 
```
map(red_value, redlow, redhigh, 0, 255);

constrain(red_value, 0, 255);
```
The new values are stored in R, G and B variables. 
* The communication is finished.  

# *Setup()* function
* Initialisation for the parameters of the I2C communication
```
 //I2C communication
 Wire.begin(I2C_SDA, I2C_SCL, 100000);
```
* Initialisation of the color sensor
```
 //Color sensor initialisation
 RGB_sensor.init();
```
* Black and white calibration
```
 //Black and White calibration 
 BW_calibration();
```
# *Loop()* function
* Read the RGB value.
* Light up the bionic flower whith using the LEDs with the R G B value.
