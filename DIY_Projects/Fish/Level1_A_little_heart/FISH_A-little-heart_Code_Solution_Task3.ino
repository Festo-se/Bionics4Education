//A LITTLE HEART

//TASK 3

//GLOBALES VARIABLES
//GPIO
int PIN_LED=16;
int PIN_SENSOR=26;

//Variable
int Average;

//FUNCTION
//avarge_function: function that calculates the measures average (on 3 secondes)
void average_function ()
{ 
  //variable that stockes the sum of all values given by the pulse sensor  
  int sum=0;

  //loop during 3 secondes (75*40 ms=3000ms=3s) to read 75 measures
  for (int i=0;i<75;i=i+1) 
  {
    //addition 
    sum = sum + analogRead(PIN_SENSOR);
    //sampling every 40 ms 
    delay(40);
  }
  
  //division
  Average = sum/75; 
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
  Serial.println("A little heart: task 3!"); 

}

//LOOP: function that display the pulse of heart during 20s, then calculate the average during 3s - code executed repeatedly
void loop() 
{ 
  //ON SERIAL PLOTTER 
  //display the pulse of heart during 20 s (see the average (approximately))
  for (int i=0; i<500; i=i+1)
  {
    //Reading and and display the pulse of the heart
    int Value=analogRead(PIN_SENSOR);
    Serial.println(Value);
  }

  //ON SERIAL MONITOR
  //Calculate and display the average value to check the average function 
  average_function();
  Serial.println(Average);
}