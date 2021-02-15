// LED
// GPIO
#define LED_RGB_Red 16

// global variable
int bpm = 60;

char serialprint_buffer[100];

// setup the components
void setup()
{
  // setup LED as OUTPUT
  pinMode (LED_RGB_Red, OUTPUT);

  Serial.begin(9600);
  // setup the serial communication
}

void loop()
{
  // look for an input in the serial monitor
  if (Serial.available() > 0)
  {
    // read incoming byte
    int bpm_read = 60;
    bpm_read = Serial.parseInt();
    // clear the buffer
    Serial.flush();

    // If the read in variable is between the permitted min and max bpm value set the variable bpm to the read in variable.
    // If the read in variable is not between the permitted min and max bpm values print a notification into the serial monitor.
  }
  // print the bpm value to the serial monitor
  sprintf(serialprint_buffer, "pulse %d bpm", bpm);
  Serial.println(serialprint_buffer);

  // calculate the interval time between LED HIGH and LED LOW: convert bpm into msceond and subtract the time of "power on" of the LED
  unsigned long interval_time = (60 * 1000 / bpm) - 100;
  digitalWrite (LED_RGB_Red, HIGH);
  delay(100);
  digitalWrite(LED_RGB_Red, LOW);
  delay(interval_time);
  // print the time between LED LOW and LED HIGH
  sprintf(serialprint_buffer, "interval time: %d ms", interval_time);
  Serial.println(serialprint_buffer);
}