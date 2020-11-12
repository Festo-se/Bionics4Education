
#ifndef SERVOSERICE_H_
#define SERVOSERICE_H_

// MARK: Includes

#include <ESP32_Servo.h>
#include <Ticker.h>
#include "Models.h"
#include "Settings.h"

class ServoService {

  public:

    // MARK: Static Methods

    static ServoService* getSharedInstance();

    // MARK: Methods

    Project getProject() {
      return project;
    }

    SliderConfiguration getConfiguration() {
      return configuration;
    }

    void update(const boolean has_active_connection);
    void setProject(Project project);
    void setConfiguration(SliderConfiguration configuration);
    void fishLoop();

  protected:

  private:

    // MARK: Initialization

    ServoService();

    // MARK: Private Properties

    Servo* servo_0;
    Servo* servo_1;
    Servo* servo_2;
    Servo* servo_3;

    SliderConfiguration configuration;
    Project project;

    Ticker fish_timer;

    int32_t led_loop_counter;
    boolean led_is_on;
    boolean led_loop_counter_length;
    boolean led_is_blinking;

    int16_t servo_0_value;
    int16_t servo_1_value;
    int16_t servo_2_value;
    int16_t servo_3_value;

    float servo_speed = 0;
    float servo_step = FISH_STEP_DEFAULT;
    int16_t servo_position = FISH_POSITION_CENTER;
    int16_t servo_amplitude_min = FISH_POSITION_LEFT;
    int16_t servo_amplitude_max = FISH_POSITION_RIGHT;

    // MARK: Helpers

    void writeLED(const boolean has_active_connection);

    void attachAll();
    void detachAll();

    void writeServos(SliderConfiguration new_configuration);
    void write(Servo* servo, int16_t value);
    void attachIfNeeded(Servo* servo);
    void resetFishTimer(SliderConfiguration new_configuration);

};

#endif
