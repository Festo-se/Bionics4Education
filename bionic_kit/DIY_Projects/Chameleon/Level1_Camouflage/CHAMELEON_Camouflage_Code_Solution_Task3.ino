// LED2 (built-in ESP32)
// GPIO
#define LED2 13

// RGB LED
// GPIO
#define LED_RGB 16

// color sensor
// GPIO
// define pin for TTL level square wave
#define sensorOut 25
// define frequency scaling (S1 = 0)
#define S0 17
// define color array (S2 not defined, because for red and blue color detection it must be LOW (not connected))
#define S3 26
// define variable for each color frequency (red, green, blue)
int red_frequency = 0;
int blue_frequency = 0;
// define a lower and upper treshold of the color sensor
int colorsensorTresholdLower = 1000;
int colorsensorTresholdUpper = 3000;

// global variables
char serialprint_buffer[100];

void setup()
{
  // setup LED2 as OUTPUT
  pinMode(LED2, OUTPUT);

  // setup LED_RGB as OUTPUT
  pinMode(LED_RGB, OUTPUT);

  // setup color sensor
  pinMode(sensorOut, INPUT);
  // setup frequency scaling
  pinMode(S0, OUTPUT);
  // set frequency scaling to 20% (S1 = LOW, not connected)
  digitalWrite(S0, HIGH);
  // setup color array (S2 not defined)
  pinMode(S3, OUTPUT);
  
  // setup the serial communication
  Serial.begin(9600);
}

void loop()
{
  // set sensor to read RED color only (S2 = LOW because it's not connected)
  digitalWrite(S3, LOW);
  // write the pulse width of the sensor signal into the red_frequency variable
  red_frequency = pulseIn(sensorOut, HIGH);

  // set sensor to read BLUE color only (S2 = LOW because it's not connected)
  digitalWrite(S3, HIGH);
  // write the pulse width of the sensor signal into the blue_frequency variable
  blue_frequency = pulseIn(sensorOut, HIGH);

  // print RGB values in the serial monitor
  sprintf(serialprint_buffer, "Red: %d Blue: %d", red_frequency, blue_frequency);
  Serial.println(serialprint_buffer);

  // write the detected color in the serial monitor
  if (red_frequency > colorsensorTresholdLower && red_frequency < colorsensorTresholdUpper && red_frequency < blue_frequency) {
    Serial.println("red");
    // flash the red LED (LED2)
    digitalWrite(LED2, HIGH);
    digitalWrite(LED_RGB, LOW);
  }
  else if (blue_frequency > colorsensorTresholdLower && blue_frequency < colorsensorTresholdUpper && blue_frequency < red_frequency) {
    Serial.println("blue");
    // flash the blue LED (RGB_LED)
    digitalWrite(LED_RGB, HIGH);
    digitalWrite(LED2, LOW);
  }
  else {
    digitalWrite(LED_RGB, LOW);
    digitalWrite(LED2, LOW);
  }
  delay(1000);
}