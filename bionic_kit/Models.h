
#ifndef MODELS_H_
#define MODELS_H_

// MARK: Includes

#include <SPIFFS.h>
#include <string>

// MARK: Types

enum Project {
  fish, elephant, chameleon
};

struct SliderConfiguration {
  int16_t slider_value_0;
  int16_t slider_value_1;
  int16_t slider_value_2;
  int16_t slider_value_3;
};

#endif
