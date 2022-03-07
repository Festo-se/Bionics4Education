/* Hi ! This example will teach you how to use the bionic flower light sensor. The sensor measures the proximity and the luminosity vaue.
The sensor use the I2C communication.*/

// Light sensor's library
#include "RPR-0521RS.h"
//I2C communication library 
#include <Wire.h>

//I2C communication GPIO
#define I2C_SDA 4
#define I2C_SCL 5 

// object creation : light sensor 
RPR0521RS rpr0521rs;
int rc;

void setup() {
  
    //start the serial communication 
     Serial.begin(9600);
     //start the I2C communication 
     Wire.begin(I2C_SDA, I2C_SCL, 100000);
     //Initialisation light sensor 
     rc = rpr0521rs.init();
}

void loop() {

  uint32_t proximity;
  float luminosity;
  rc = rpr0521rs.get_psalsval(&proximity,&luminosity);
  Serial.print("Luminosity : "); Serial.print(luminosity);Serial.println(" [lx] ");
  delay(500);

}
