//CAMOUFLAGE

// GLOBALES VARIABLES
//GPIO
int PIN_LED=/*complete with the GPIO's number*/;

//Reference Frequency
int Blue_Frequency=3;
int Red_Frequency=7;
int Green_Frequency=4;
 

//SETUP: function that initialize the components and display a start message to the serial monitor - code only runs once
void setup() 
{ 
  //INITIALIZATION
  //ESP32 sends information to the LED
  pinMode(PIN_LED,/*complete with the LED's mode*/); 
  
  //SERIAL COMMUNICATION
  Serial.begin(9600); 
  delay(5000); 
  Serial.println("Camouflage!"); 
}

//LOOP: function that flashes the LED - code executed repeatedly
void loop() 
{ 
  //turn on LED
  digitalWrite(PIN_LED, /*complete with the LED's level*/);  
  delay(500);
  
  //turn off LED 
  digitalWrite(PIN_LED, /*complete with the LED's level*/); 
  delay(500);
}