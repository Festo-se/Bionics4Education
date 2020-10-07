//CAMOUFLAGE

//TASK 2

//GLOBALES VARIABLES
//GPIO
int PIN_LED=16;
int PIN_LED_R=16;
int PIN_LED_G=17;
int PIN_LED_B=26;  

//Reference Frequency
int Blue_Frequency=3;
int Red_Frequency=7;
int Green_Frequency=4;

//SETUP: function that initialize the components and display a start message to the serial monitor - code only runs once
 void setup() 
{ 
  //INITIALIZATION
  //ESP32 send information to LED RGB
  pinMode(PIN_LED_R, OUTPUT); 
  pinMode(PIN_LED_G, OUTPUT); 
  pinMode(PIN_LED_B, OUTPUT); 
  
  //SERIAL COMMUNICATION
  Serial.begin(9600); 
  delay(5000); 
  Serial.println("Camouflage: task 2!"); 
}

//LOOP: function that create a color sequence : blue,green,red,blue,green,.. - code executed repeatedly
 void loop()
{  
  //Blue
  digitalWrite(PIN_LED_B, HIGH);
  digitalWrite(PIN_LED_G, LOW);
  digitalWrite(PIN_LED_R, LOW);
  delay(2000);
  
  //Green
  digitalWrite(PIN_LED_G, HIGH);
  digitalWrite(PIN_LED_B, LOW);
  digitalWrite(PIN_LED_R, LOW);  
  delay(2000);
  
  //Red
  digitalWrite(PIN_LED_R, HIGH);
  digitalWrite(PIN_LED_G, LOW);
  digitalWrite(PIN_LED_B, LOW); 
  delay(2000);
}