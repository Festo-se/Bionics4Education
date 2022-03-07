/* Hi ! This example will teach you how to use the bionic flower touch sensor.The sensor detects when you touch right or left.
If a right touch is detected the flower is opening. If a left touch is detected the flower is closing.
The sensor use the I2C communication.*/

// Touch sensor's library
#include <SparkFun_CAP1203_Registers.h>
#include <SparkFun_CAP1203_Types.h>
//I2C communication library 
#include <Wire.h>
//motor's library 
#include "BasicStepperDriver.h"

//I2C communication GPIO
#define I2C_SDA 4
#define I2C_SCL 5 

//MOTOR GPIO
#define DIR 33
#define STEP 25
#define SLEEP 13
//MOTOR CHARACTERISTIC 
//1.8 degree/step
#define MOTOR_STEPS 200 
#define MICROSTEPS 1

//Object creation : touch sensor 
CAP1203 touch_sensor=CAP1203(0x28); 
//Object creation : motor
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

//MOTOR VARIABLE
//speed
int RPM=240; 
//number of turns to go from state: full close to full open
int FLOWER_CLOSE_TO_OPEN = 120;
//position of the motor between full open and full close 
int current_position; 


//The motor_calibration() function allows completely close the flower. It's the initial position of the flower.
void motor_calibration()
{
    for (int i =0; i<FLOWER_CLOSE_TO_OPEN;i++)
    { stepper.rotate(-360);}
    current_position=0;
    Serial.println("Calibatrion motor done");
    
}

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
     
    //initialise the motor
     stepper.begin(RPM, MICROSTEPS);
     motor_calibration();
}

void loop() {
    //the flower is opening 
    if (touch_sensor.isRightTouched() == true)
    {
      Serial.println("Right");
      if (current_position < FLOWER_CLOSE_TO_OPEN)
    { 
      stepper.rotate(360);
      current_position = current_position +1;
    }
      
   }
   //the fower is closing 
    else if (touch_sensor.isLeftTouched() == true)
    {
     Serial.println("Left");
     if (current_position > 0) 
     {
      stepper.rotate(-360);
      current_position = current_position -1;
     }
    }

}
