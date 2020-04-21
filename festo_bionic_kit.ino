/**@file bionic_edu_32_async_new_ssid_class.ino*/
/**
 * @file bionic_edu_32_async_new_ssid_class.ino
 * @author Lucas Schweitzer (lucas.schweitzer@jntec.de)
 * 
 * @brief EN: This file contains the main functions of the bionic-kit for the Arduino IDE
 *        DE: Diese Datei beinhaltet die Hauptfunktionen fuer das bionic-kit fuer die Arduino IDE
 * 
 * @date 2018-10-23
 * 
 * 
 */

// INCLUDE FILES //
#include <ESP32_Servo.h>
#include "settings.h"
#include <algorithm>
#include <string>
#include "bionic_webserver.h"
#include <Ticker.h>

#define LED_BUILTIN 13

const String VERSION =  "v1.4";
const String DATE =  __DATE__;
const String TIME = __TIME__;

const String PRINT_PREFIX = "[SKETCH]: "; //!< Prefix for the serial output of the Sketch file
   
bool g_write_to_servo_b = false;          //!< Flag if there are new values for the servos
bool g_new_values_web_b = false;          //!< Flag if there are new values from the Webserver

Ticker g_timer_fish_loop;                 //!< Timer object to control the speed of the bionic_fish

Servo g_servo_01;                         //!< Servo object to control the servo 1
Servo g_servo_02;                         //!< Servo object to control the servo 2
Servo g_servo_03;                         //!< Servo object to control the servo 3
Servo g_servo_04;                         //!< Servo object to control the servo 4

BionicWebserver myServer(80);             //!< Instance of the BionicWebserver

int16_t g_actual_web_values_a[4];         //!< Storage for the WebServer values

int16_t g_slider_1_old_ui16 = 0;          //!< Storage for the last values from slider 1
int16_t g_slider_2_old_ui16 = 0;          //!< Storage for the last values from slider 2
int16_t g_slider_3_old_ui16 = 0;          //!< Storage for the last values from slider 3
int16_t g_slider_4_old_ui16 = 0;          //!< Storage for the last values from slider 4

bool g_new_val_s1_b = false;              //!< Flag if there are new values from Slider 1 (for controlling the motors separately)
bool g_new_val_s2_b = false;              //!< Flag if there are new values from Slider 2 (for controlling the motors separately)
bool g_new_val_s3_b = false;              //!< Flag if there are new values from Slider 3 (for controlling the motors separately)
bool g_new_val_s4_b = false;              //!< Flag if there are new values from Slider 4 (for controlling the motors separately)

int16_t g_last_project_id_ui16 = 0;       //!< Last project id to determine if the project was switched
int16_t g_actual_project_id_ui16 = 0;     //!< Actual project id
bool g_project_switched_b = false;        //!< Flag if project was switched

int16_t g_servo_pos_i16 = 90;             //!< Variable for the actual servo position
int16_t g_servo_speed_i16 = 0;            //!< Variable for the actual servo speed
int16_t g_servo_amplitude_max_i16 = 150;  //!< Calculated max value of the fin amplitude 
int16_t g_servo_amplitude_min_i16 = 40;   //!< Calculated min value of the fin amplitude
int16_t g_servo_offset_i16 = 0;           //!< Calculated offset from the fin center point

int32_t g_led_state_i32 = LOW;                  //!< Onboard led status
const int32_t g_blink_length_i32 = 200000;      //!< Number of cycles the led should be switched on
const int32_t g_led_pin_i32 =  LED_BUILTIN;     //!< Pin number of the onboard LED
uint32_t g_loop_count_ui16 = 0;                 //!< Actual loop cycle count

bool g_led_blink_b = false;                     //!< flag if the LED should blink

/**
 * @brief Blink with onboard LED
 * 
 * EN: This function let the onboard LED blink. The output can be changed 
 *     with the define LED_BUILTIN.
 * 
 * DE: Diese Funktion ermoeglicht es die onboard LED blinken zu lassen.
 *     Welche LED genutzt werden soll, kann mittels des defines LED_BUILTIN 
 *     festgelegt werden.
 * 
 * @param f_count_i32 EN: Number of LED flashes / DE: Anzahl wie oft die LED blinken soll 
 */
void blinkOnBoardLED(const int32_t f_count_i32)
{
  for (int i = 0; i < f_count_i32; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}

/**
 * @brief Calculate the bionic_fish specific values
 * 
 *  EN: Calculates the bionic_fish specific values like speed, max and min amplitude
 *      and the direction of the fish (offset from the center). This function should 
 *      be called when new values from the website are available. 
 * 
 *  DE: Berechnet die speziellen Werte fuer den bionic_fish wie Geschwindigkeit, maximale und 
 *      minimale Amplitude der Schwanzflosse sowie die Richtung (offset from center) in die der 
 *      Fisch schwimmen soll. Diese Funktion sollte immer dann aufgerufen werden wenn neue Werte 
 *      vom Webserver vorliegen. 
 * 
 */
void calculateFishValues()
{
  // The desired speed equals to the first entry in the g_actual_web_values_a array (Slider 1)
  g_servo_speed_i16 = g_actual_web_values_a[0];
 
  // If the speed value is smaller than 1 keep it at one to prevent dividing through 0
  if (g_servo_speed_i16 <= 1)
  {
    g_servo_speed_i16 = 1;
  }

  // Calculate the direction of the fish with the offset from the center (Slider 2)
  g_servo_offset_i16 = FISH_AMPLITUDE_CENTER_DEFAULT + g_actual_web_values_a[1];

  // Calculates the max and min amplitude with g_servo_offset_i16 and the value from Slider 3.
  // With FISH_AMPLITUDE_MULTIPLIER it is possible to reduce the maximum swing of the fin to 
  // prevent mechanical blocking of the servo. 
  int16_t amp_i16 = (g_actual_web_values_a[2] / 2);
  g_servo_amplitude_max_i16 = (g_servo_offset_i16 + amp_i16) * FISH_AMPLITUDE_MULTIPLIER;
  g_servo_amplitude_min_i16 = (g_servo_offset_i16 - amp_i16) * FISH_AMPLITUDE_MULTIPLIER;

  Serial.println(PRINT_PREFIX + "Speed: " + g_servo_speed_i16);
  Serial.println(PRINT_PREFIX + "Servo offset: " + g_servo_offset_i16);
  Serial.println(PRINT_PREFIX + "Fish amplitude MAX: " + g_servo_amplitude_max_i16 );
  Serial.println(PRINT_PREFIX + "Fish amplitude MIN: " + g_servo_amplitude_min_i16 );
  Serial.println("");

}


int32_t g_add_value_i32 = 5;  //!< Defines how much the next servo position is incremented at each update
/**
 * @brief Main routine for controlling the fish movement
 * 
 *  EN: Main routine for controlling the bionic_fish movement. Everytime the
 *      method is called a new possition for the servo is calculated depending 
 *      on the last postion, speed and max/min amplitude. If the servo postion
 *      reaches the max amplitude the servo changes direction and driving towards
 *      min amplitude. 
 * 
 *  DE: Hauptroutine fuer die Bewegung des bionic_fish. Jedesmal wenn die Funktion
 *      aufgerufen wird, wird eine neue Servo Zielposition berechnet. Die Berechnung
 *      erfolgt in Abhaengigkeit der letzten Position, Geschwindigkeit und der maximalen
 *      und minimalen Amplitude. Wenn der Servo die maximale Position erreicht, kehrt
 *      er um und bewegt sich Richtung minimaler Position. 
 * 
 */
void fishLoop()
{
  // if the speed is smaller than one, stop the fish movement
  if (g_servo_speed_i16 < 1)
  {
    return;
  }
  else
  {
    // Add g_add_value_i32 to the last position value
    g_servo_pos_i16 += g_add_value_i32;

    // If the position gets larger then the max. amplitude, switch the direction
    if (g_servo_pos_i16 >= g_servo_amplitude_max_i16)
    {
      g_servo_pos_i16 = g_servo_amplitude_max_i16 - (g_add_value_i32 + 1);
      g_add_value_i32 *= -1;
    }

    // If the position gets smaller then the min. amplitude, switch the direction
    if (g_servo_pos_i16 <= g_servo_amplitude_min_i16)
    {
      g_servo_pos_i16 = g_servo_amplitude_min_i16 + (g_add_value_i32 + 1);
      g_add_value_i32 *= -1;
    }


  }  
 
  // Set the Flag to write the values to the servo
  g_write_to_servo_b = true;
}

/**
 * @brief Attach all connected servos at once
 * 
 */
void attachAllServos()
{
    g_servo_01.attach(GPIO_SERVO_01, MIN_PPM_VALUE, MAX_PPM_VALUE);
    g_servo_02.attach(GPIO_SERVO_02, MIN_PPM_VALUE, MAX_PPM_VALUE);
    g_servo_03.attach(GPIO_SERVO_03, MIN_PPM_VALUE, MAX_PPM_VALUE);
    g_servo_04.attach(GPIO_SERVO_04, MIN_PPM_VALUE, MAX_PPM_VALUE);

}

/**
 * @brief Detach all connected servos at once
 * 
 * Note: The waterproofe servo is not detachable. It held its stiffness even when the pwm is zero. 
 */
void detachAllServos()
{
    g_servo_01.detach();
    g_servo_02.detach();       
    g_servo_03.detach();
    g_servo_04.detach();

}

/**
 * @brief Arduino specific setup or init routine 
 * 
 *  EN: The setup method will be called once at the beginning of the code. 
 *      It contains all necessary configurations for the bionic kit. 
 * 
 *  DE: Die setup Methode wird einmalig beim Beginn des Programms
 *      aufgerufen. In ihr werden alle Einstellungen vorgenommen.
 * 
 */
void setup(void)
{
    // Initialize the serial port with baud rate 115200
    Serial.begin(115200);
    
    // Wait till the port is connected
    while (!Serial) {; // wait for serial port to connect.
    } 

    Serial.println("");
    Serial.println("*** Version: "+VERSION+" ***");
    Serial.println("*** Build Date: "+DATE+" ***");
    Serial.println("*** Build Time: "+TIME+" ***");
    Serial.println("");

    // Initialize the empty web_values array with proper values
    g_actual_web_values_a[0]=0;
    g_actual_web_values_a[1]=0;
    g_actual_web_values_a[2]=0;
    g_actual_web_values_a[3]=0;
    
    // Initialize the BionicWebserver class with the webserver port 80 (HTTP)
    myServer.init(80);

    // Update the empty web_values array of the bionic webserver with the previous defined values
    // in g_actual_web_values_a to keep it synchronized
    //  myServer.updateWebValues(g_actual_web_values_a);
    //myServer.printValues();

    // Initialize the servo objects with the right GPIO and the specific PPM Values
    // for the servo motors
    attachAllServos();
  
    // Initialize the onboard LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

}


/**
 * @brief Main Loop of the arduino code
 * 
 * EN: the loop method is an arduino specific method and will be 
 *     executed until the controller is shut down or reseted. 
 * 
 * DE: Die loop Methode ist eine von Arduino vorgegebene Methode, 
 *     welche unendlich oft immer wieder aufgerufen wird, bist das Programm 
 *     beendet wird.
 *     
 */
void loop(void)
{    
  // Process next DNS request and keep the server running
  myServer.processRequests();
  
  //If there are new slider values get them
  if (myServer.isNewWebValue())
  {    
    myServer.getWebValues(g_actual_web_values_a);

    // if there are new values led the onboard led blink
    g_led_blink_b = true;

    // determine which values are new, to enable the single motor movement
    // in elephant mode and set the corresponding flag
    if(g_actual_web_values_a[0] != g_slider_1_old_ui16)
    {
      g_new_val_s1_b = true;
      g_slider_1_old_ui16 = g_actual_web_values_a[0];
      Serial.println(PRINT_PREFIX + "New Value Slider 1");
    
    }

    if(g_actual_web_values_a[1] != g_slider_2_old_ui16)
    {
      g_new_val_s2_b = true;
      g_slider_2_old_ui16 = g_actual_web_values_a[1];
      Serial.println(PRINT_PREFIX + "New Value Slider 2");
    
    }

    if(g_actual_web_values_a[2] != g_slider_3_old_ui16)
    {
      g_new_val_s3_b = true;
      g_slider_3_old_ui16 = g_actual_web_values_a[2];
      Serial.println(PRINT_PREFIX + "New Value Slider 3");
    
    }

    if(g_actual_web_values_a[3] != g_slider_4_old_ui16)
    {
      g_new_val_s4_b = true;
      g_slider_4_old_ui16 = g_actual_web_values_a[3];
      Serial.println(PRINT_PREFIX + "New Value Slider 4");
    
    }
    
    // Get the actual project ID 
    g_actual_project_id_ui16 = myServer.getActiveProjectId();

    // Check if the project was switched to init the default values for the servos properly 
    if(g_actual_project_id_ui16 != g_last_project_id_ui16)
    {
      g_project_switched_b = true;      
      g_last_project_id_ui16 = g_actual_project_id_ui16;
    
    }

    // Notifiy the main routine that there is a update
    g_new_values_web_b = true;
  }

  // If bionic_fish is selected
  if (g_actual_project_id_ui16 == 0)
  {

    if(g_project_switched_b)
    {
      attachAllServos();
      g_project_switched_b = false;
    
    }

    // If there are new slider values ...
    if (g_new_values_web_b)
    {
      //Recalculate the bionic_fish specific values
      calculateFishValues();

      // If the slider is on the left most postion, stop the movement
      if (g_servo_speed_i16 <= 1)
      {
        // Stop the timer
        g_timer_fish_loop.detach();
       
        // Stop writing to the servo
        g_write_to_servo_b = false;
      }
      else
      {
        // Calculate the timespan for the timer, based on the speed slider position and the boundaries defined in settings.h
        // The timer also defines the write speed to the servo. 
        // The MAX_SERVO_UPDATE_FREQ boundary is necessary to prevent the servo from over writing and from a crash of the serial connection (BUG?)
        // The MIN_SERVO_UPDATE_FREQ boundary is necessary to make a smooth servo movement without stopping between the updates
        int16_t timer_time_f = (1 / (MIN_SERVO_UPDATE_FREQ + ((MAX_SERVO_UPDATE_FREQ / 100.0)*g_servo_speed_i16)))*1000;
        //Serial.print(PRINT_PREFIX + "Time for Timer: ");
        //Serial.println(timer_time_f/1000.0, DEC);
        //Serial.println("");
                
        // Start the timer and attach the fish_loop
        g_timer_fish_loop.detach();
        g_timer_fish_loop.attach(timer_time_f/1000.0, fishLoop);
      }

      // If everything is set, reset the g_new_values_web_b flag
      g_new_values_web_b = false;
    }

    // Update the servo postion if the flag is rised
    if (g_write_to_servo_b)
    {
      g_servo_01.write(g_servo_pos_i16);
      g_servo_02.write(g_servo_pos_i16);
      g_servo_03.write(g_servo_pos_i16);
      g_servo_04.write(g_servo_pos_i16);
      g_write_to_servo_b = false;
    }
  }
  // Elephant trunk
  else if (g_actual_project_id_ui16 == 1)
  {
    // Ift the project was switched, reset the new value flags to prevent that all
    // servos move at the same time (battery voltage will drop )
    if(g_project_switched_b)
    {
       // reset the new value flags
       g_new_val_s1_b = false;
       g_new_val_s2_b = false;
       g_new_val_s3_b = false;
       g_new_val_s4_b = false;

       // Stop the fish timer
       g_timer_fish_loop.detach();
       
       // Set all PWMs to zero (Note: waterproof servo will hold its stiffness)
       detachAllServos();
       g_project_switched_b = false;

    }
    if(g_new_values_web_b || g_new_val_s1_b || g_new_val_s2_b || g_new_val_s3_b || g_new_val_s4_b )
    {      
      // Write the specific slider values to the corresponding servo and disable the unneeded ones. 
      // This is important to prevent the battery voltage from dropping
      if(g_new_val_s1_b == true)
      {
        g_servo_01.attach(GPIO_SERVO_01, MIN_PPM_VALUE, MAX_PPM_VALUE);        
        g_servo_02.detach();
        g_servo_03.detach();
        g_servo_04.detach();
        
        g_servo_01.write(g_actual_web_values_a[0]);
        g_new_val_s1_b = false;
      
      }
      else if(g_new_val_s2_b == true)
      {
        g_servo_01.detach();
        g_servo_02.attach(GPIO_SERVO_02, MIN_PPM_VALUE, MAX_PPM_VALUE);                
        g_servo_03.detach();
        g_servo_04.detach();
        
        g_servo_02.write(g_actual_web_values_a[1]);
        g_new_val_s2_b = false;
      
      }
      else if(g_new_val_s3_b == true)
      {
        g_servo_01.detach();
        g_servo_02.detach();
        g_servo_03.attach(GPIO_SERVO_03, MIN_PPM_VALUE, MAX_PPM_VALUE);
        g_servo_04.detach();
        
        g_servo_03.write(g_actual_web_values_a[2]);
        g_new_val_s3_b = false;
      
      }
      else if(g_new_val_s4_b == true)
      {
        g_servo_01.detach();
        g_servo_02.detach();
        g_servo_03.detach();        
        g_servo_04.attach(GPIO_SERVO_04, MIN_PPM_VALUE, MAX_PPM_VALUE); 
        
        g_servo_04.write(g_actual_web_values_a[3]);
        g_new_val_s4_b = false;
      
      }
      
      g_new_values_web_b = false;
    }
  }
  //Chameleon tung
  else if (g_actual_project_id_ui16 == 2)
  {

    if(g_project_switched_b)
    {
      // Stop the fish timer
      g_timer_fish_loop.detach();

      // Attach all Servos for the chameleon project
      attachAllServos();

      g_project_switched_b = false;

    }
    
    if(g_new_values_web_b)
    {
      // Write the slider values to the servos
      g_servo_01.write(g_actual_web_values_a[0]);
      g_servo_02.write(g_actual_web_values_a[1]);
      g_servo_03.write(g_actual_web_values_a[2]);
      g_servo_04.write(g_actual_web_values_a[3]);
      g_new_values_web_b = false;
    }
  }
  //Wrong Parameter
  else
  {
    Serial.println(PRINT_PREFIX + "Unknown project id!");
  }

  // Onboard LED-Blink logic
  // If no client is connected the led is on. 
  // If a client is connected the led is off.
  // If new values from the webserver are available the LED blinks once. 
  if(!myServer.getActiveConnections())
  {
     g_led_state_i32 = HIGH;     
  }
  else
  {
    if(g_led_blink_b)
    {
      if(g_loop_count_ui16<g_blink_length_i32)
      {
        g_led_state_i32 = HIGH;
      }
      else
      {
        g_led_state_i32 = LOW;
        g_loop_count_ui16 = 0;
        g_led_blink_b = false;         
      }
      g_loop_count_ui16++;
    }
    else
    {
      g_led_state_i32 = LOW;
    }    
  }
  digitalWrite(g_led_pin_i32, g_led_state_i32);
}
