/* Hi ! This example will teach you how to use the bionic flower touch sensor. The sensor detects when you touch right or left.
The sensor use the I2C communication.*/

// Touch sensor's library
#include <SparkFun_CAP1203_Registers.h>
#include <SparkFun_CAP1203_Types.h>
//I2C communication library 
#include <Wire.h>

//I2C communication GPIO
#define I2C_SDA 4
#define I2C_SCL 5 

//Object creation : touch sensor 
CAP1203 touch_sensor=CAP1203(0x28); 

void setup() {
  
     //start the serial communication 
     Serial.begin(9600);
     //start the I2C communication 
     Wire.begin(I2C_SDA, I2C_SCL, 100000); 
     
     delay(5000); //time to open the serial monitor
     // Touch sensor is connected ? 
     while (touch_sensor.begin() == false) 
     {
      Serial.println("Not connected. Please check connections.");
      delay(1000);
      }
     Serial.println("Touch sensor connected!");
}

void loop() {
  
    if (touch_sensor.isLeftTouched() == true)
    {
      Serial.println("Left");
    }
    if (touch_sensor.isRightTouched() == true)
    {
      Serial.println("Right");
    }
    delay(500);
}
