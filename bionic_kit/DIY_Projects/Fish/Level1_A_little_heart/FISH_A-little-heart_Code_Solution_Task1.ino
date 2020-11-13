//A LITTLE HEART

//TASK 1

//GLOBALES VARIABLES
//GPIO
int PIN_LED=16;

//SETUP: function that initialize the components and display a start message to the serial monitor
//code only runs once
void setup() 
{
  //INITIALIZATION
  //ESP32 sends information to the LED 
  pinMode(PIN_LED, OUTPUT); 
  
  //SERIAL COMMUNICATION
  //9600 bauds 
  Serial.begin(9600);
  delay(5000); 
  Serial.println(" A little heart : task 1 !"); 
}
   
//LOOP: function that flashes the LED - code executed repeatedly
void loop() 
{ 
  //turn on LED 
  digitalWrite(PIN_LED, HIGH); 
  delay(500);
  //turn off LED 
  digitalWrite(PIN_LED, LOW); 
  delay(500);
}