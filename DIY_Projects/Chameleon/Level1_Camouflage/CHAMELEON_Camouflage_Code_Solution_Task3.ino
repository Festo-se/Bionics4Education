//CAMOUFLAGE

//TASK 3

//GLOBALES VARIABLES
//GPIO
int PIN_LED=16;
int PIN_LED_R=16;
int PIN_LED_G=17;
int PIN_LED_B=26;
int PIN_COLOR=25;

//Reference Frequency
int Blue_Frequency=3;
int Red_Frequency=7;
int Green_Frequency=4;

//SETUP: function that initialize the components and display a start message to the serial monitor - code only runs once
void setup()
{
  //INITIALIZATION
  //ESP32 sends information to LED
  pinMode(PIN_LED_R, OUTPUT); 
  pinMode(PIN_LED_G, OUTPUT); 
  pinMode(PIN_LED_B, OUTPUT);
 
 //ESP32 receives information from the color sensor
  pinMode(PIN_COLOR, INPUT);
  
  //SERIAL COMMUNICATION
  Serial.begin(9600); 
  delay(5000);
  Serial.println("Camouflage: task 3!");  
}

//LOOP: function that tunrs on the LED of the same color as the object in front of the color sensor - code executed repeatedly
 void loop()
{ 
  // Read Current_Frequency
  int Current_Frequency=pulseIn(PIN_COLOR, HIGH);
  Serial.println(Current_Frequency);

  //Red color
  if ((Current_Frequency==Red_Frequency)
    {
		digitalWrite(PIN_LED_R, HIGH);
		digitalWrite(PIN_LED_B, LOW);  
		digitalWrite(PIN_LED_G, LOW);
	}
	//Blue color         
	else if ((Current_Frequency==Blue_Frequency)
    {
		digitalWrite(PIN_LED_B, HIGH);
		digitalWrite(PIN_LED_R, LOW);  
		digitalWrite(PIN_LED_G, LOW);
	}
	//Green color      
	else if (Current_Frequency==Green_Frequency)
    {
		digitalWrite(PIN_LED_G, HIGH);
		digitalWrite(PIN_LED_R, LOW);  
		digitalWrite(PIN_LED_B, LOW);
	}
	//Other color
	else 
	{ 
		digitalWrite(PIN_LED_G, LOW);
		digitalWrite(PIN_LED_R, LOW);  
		digitalWrite(PIN_LED_B, LOW);
	}  
}