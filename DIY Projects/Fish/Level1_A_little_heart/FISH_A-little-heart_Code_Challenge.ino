//A LITTLE HEART

//GLOBALES VARIABLES
//GPIO
int PIN_LED=/*complete with GPIO's number*/;

//FUNCTION
//avarge_function: function that calculates the measures average (on 3 secondes )

//SETUP: function that initialize the components and display a start message to the serial monitor - code only runs once
void setup() 
{ 
  //INITIALIZATION
  //ESP32 sends information to the LED 
  pinMode(PIN_LED,/*complete with the GPIO's mode*/); 
  
  //SERIAL COMMUNICATION
  //9600 bauds 
  Serial.begin(9600);
  delay(5000); 
  Serial.println("A little heart!"); 
}

//LOOP: function that flashes the LED
//code executed repeatedly
void loop() 
{ 
  //turn on LED 
  digitalWrite(PIN_LED, /*complete with the GPIO's level*/); 
  delay(500);
  
  //turn off LED 
  digitalWrite(PIN_LED, /*complete with the GPIO's level*/); 
  delay(500);
}