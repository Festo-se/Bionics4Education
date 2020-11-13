//A LITTLE HEART

//TASK 4

//GLOBALES VARIABLES
//GPIO
int PIN_LED=16;
int PIN_SENSOR=26;

//Variable
int Average;

//FUNCTION
//avarge_function: function that calculates the measures average (on 3 secondes)
void average_function()
{ 
  //variable that stockes the sum of all values given by the pulse sensor  
  int sum=0;

  //loop during 3 secondes (75*40ms=3000ms=3s) to read 75 measures
  for (int i=0; i<75; i=i+1) 
  {
    // addition 
    sum=sum+analogRead(PIN_SENSOR);
    //sampling every 40 ms 
    delay(40);
  }
  //division
  Average=sum/75; 
}

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
  Serial.println("A little heart: task 4!"); 
}

//LOOP: function allows the LED to light up with each heartbeat (peak) - code executed repeatedly
void loop()
{
 //3 secondes
 average_function(); 
 
 //20 secondes
 for ( int y = 0; y <3000;y=y+1)
 {
  int Value = analogRead(PIN_SENSOR);
  Serial.println(Value);
    if ( Value >= average+30)
    {
      digitalWrite(PIN_LED,HIGH);
      delay(5);
    }
    digitalWrite(PIN_LED,LOW);
 }
}