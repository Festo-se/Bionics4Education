//A LITTLE HEART

//TASK 2

//GLOBALES VARIABLES
//GPIO
int PIN_LED=16;
int PIN_SENSOR=26;

//SETUP: function that initialize the components and display a start message to the serial monitor - code only runs once 
 void setup() 
{ 
  //INITIALIZATION
  //ESP32 sends information to the LED 
  pinMode(PIN_LED, OUTPUT);
  //ESP32 receives information from the sensor 
  pinMode(PIN_SENSOR,INPUT); 
  
  //SERIAL COMMUNICATION
  //9600 bauds 
  Serial.begin(9600);
  delay(5000); 
  Serial.println("A little heart: task 2!");
}

//LOOP: function that read the value of the pulse sensor and display on serial plotter - code executed repeatedly
void loop() 
{ 
  //Reading and and display the pulse of the heart
  int Value = analogRead(PIN_SENSOR);
  Serial.println(Value);
}