<br><img src="/bionic_kit/DIY_Projects/Image/Logo_Festo.png" align="right"  alt="festo logo" width="200"/><br>

# Bionics Kit Version 2
### Hardware
The actuators of Bionics Kit version 2 are 5 LEDs and 4 servo motors. 

<br><img src="/bionic_kit/data/images/Controller_V2.PNG" alt="controller Bionics kit V2" width="350"/>

<br>The pin of the LEDs is GPIO 13. 
<br>The pin of servo motors are the following : S1 (GPIO 14), S2 (GPIO 27), S3 (GPIO 26), S4 (GPIO 25).

### Coding Bionics Kit V2 with Arduino IDE 

The Arduino IDE software allows you to control your Bionics Kit V2. 
<br>Here you will find some examples to control the actuators of your robot. 

* **Control the LEDs**

```
#include <FastLED.h>

// Configuration of LEDs
#define LED_PIN     13   
#define NUM_LEDS    5
CRGB leds[NUM_LEDS]; 

void setup() {

  // Actuators power 
  pinMode(33,OUTPUT);
  digitalWrite(33,HIGH);

  // Initialisation of LEDs
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();  
  FastLED.show();
}

void loop() {

  // Turn on LEDs to red color
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,0,0); 
  }
  FastLED.show();
  delay(1000); // wait 1 second

  // Turn on LEDs to blue color
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,255); 
  }
  FastLED.show();
  delay(1000); // wait 1 second
}
``` 
 
 * **Control one servo motor S1**

```
#include <ESP32Servo.h>

// Configuration of servo motor
Servo servo_S1;
#define S1_PIN   14   

void setup() {
  // Actuators power
  pinMode(33, OUTPUT);
  digitalWrite(33, HIGH); 

  // Initialisation of servo
  servo_S1.attach(S1_PIN); 
  servo_S1.write(90); // move to the 90° position
}

void loop() {

  servo_S1.write(0); // move to the 0° position
  delay(1000); // wait 1 second

  
  servo_S1.write(180); // move to the 180° position
  delay(1000); // wait 1 second
}

``` 

 * **Control all servo motors**

```
#include <ESP32Servo.h>

// Configuration of servos
Servo S1, S2, S3, S4;
#define S1_PIN  14
#define S2_PIN  27
#define S3_PIN  26
#define S4_PIN  25

void setup() {
  // Actuators power
  pinMode(33, OUTPUT);
  digitalWrite(33, HIGH); 
 
  // Initialisation of servos
  S1.attach(S1_PIN);
  S2.attach(S2_PIN); 
  S3.attach(S3_PIN); 
  S4.attach(S4_PIN); 

}

void loop() {
  
  S1.write(0);   // move servo S1 to the 0° position
  S2.write(45); // move servo S2 to the 45° position
  S3.write(90); // move servo S3 to the 90° position
  S4.write(135); // move servo S4 to the 135° position
  delay(1000); // wait 1 second

  
  S1.write(45); // move servo S1 to the 45° position
  S2.write(90); // move servo S2 to the 90° position
  S3.write(135); // move servo S3 to the 135° position
  S4.write(180); // move servo S4 to the 180° position 
  delay(1000); // wait 1 seconde
}
``` 


