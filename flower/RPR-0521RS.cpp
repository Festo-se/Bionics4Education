/*****************************************************************************
  RPR-0521RS.cpp

 Copyright (c) 2018 ROHM Co.,Ltd.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
******************************************************************************/
//#include <avr/pgmspace.h>
#include <Arduino.h>
#include <Wire.h>
#include "RPR-0521RS.h"

RPR0521RS::RPR0521RS(void)
{

}

uint8_t RPR0521RS::init(void)
{
  uint8_t rc;
  uint8_t reg;
  uint8_t index;
  uint8_t als_gain_table[] = {1, 2, 64, 128};
  uint32_t als_meas_time_table[] = {0,0,0,0,0,100,100,100,100,100,400,400,50,0,0,0};

  rc = read(RPR0521RS_SYSTEM_CONTROL, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't access RPR0521RS");
    return (rc);
  }
  reg &= 0x3F;
  Serial.print("RPR0521RS Part ID Register Value = 0x");
  Serial.println(reg, HEX);

  if (reg != RPR0521RS_PART_ID_VAL) {
    Serial.println("Can't find RPR0521RS");
    return -1;
  }

  rc = read(RPR0521RS_MANUFACT_ID, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't access RPR0521RS");
    return (rc);
  }
  Serial.print("RPR0521RS MANUFACT_ID Register Value = 0x");
  Serial.println(reg, HEX);

  if (reg != RPR0521RS_MANUFACT_ID_VAL) {
    Serial.println("Can't find RPR0521RS");
    return (rc);
  }

  reg = RPR0521RS_ALS_PS_CONTROL_VAL;
  rc = write(RPR0521RS_ALS_PS_CONTROL, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't write RPR0521RS ALS_PS_CONTROL register");
    return (rc);
  }

  rc = read(RPR0521RS_PS_CONTROL, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't read RPR0521RS PS_CONTROL register");
    return (rc);
  }

  reg |= RPR0521RS_PS_CONTROL_VAL;
  rc = write(RPR0521RS_PS_CONTROL, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't write RPR0521RS PS_CONTROL register");
  }

  reg = RPR0521RS_MODE_CONTROL_VAL;
  rc = write(RPR0521RS_MODE_CONTROL, &reg, sizeof(reg));
  if (rc != 0) {
    Serial.println("Can't write RPR0521RS MODE CONTROL register");
    return (rc);
  }

  reg = RPR0521RS_ALS_PS_CONTROL_VAL;
  index = (reg >> 4) & 0x03;
  _als_data0_gain = als_gain_table[index];
  index = (reg >> 2) & 0x03;
  _als_data1_gain = als_gain_table[index];

  index = RPR0521RS_MODE_CONTROL_VAL & 0x0F;
  _als_measure_time = als_meas_time_table[index];

  return (rc);
}

boolean RPR0521RS::is_connected(void)
{
  uint8_t reg;  
  uint8_t rc;
  
  rc = read(RPR0521RS_SYSTEM_CONTROL, &reg, sizeof(reg));
  if (rc != 0) return false;
  if ((reg & 0x3F) != RPR0521RS_PART_ID_VAL) return false;

  rc = read(RPR0521RS_MANUFACT_ID, &reg, sizeof(reg));
  if (rc != 0) return false;
  if (reg != RPR0521RS_MANUFACT_ID_VAL) return false;
  
  return true;
}

uint8_t RPR0521RS::get_rawpsalsval(uint8_t *data)
{
  uint8_t rc;

  rc = read(RPR0521RS_PS_DATA_LSB, data, 6);
  if (rc != 0) {
    Serial.println("Can't get RPR0521RS PS/ALS_DATA value");
  }

  return (rc);
}

uint8_t RPR0521RS::get_psalsval(uint32_t *ps, float *als)
{
  uint8_t rc;
  uint8_t val[6];
  uint32_t rawps;
  uint32_t rawals[2];

  rc = get_rawpsalsval(val);
  if (rc != 0) {
    return (rc);
  }

  rawps     = ((uint32_t)val[1] << 8) | val[0];
  rawals[0] = ((uint32_t)val[3] << 8) | val[2];
  rawals[1] = ((uint32_t)val[5] << 8) | val[4];

  *ps  = rawps;
  *als = convert_lx(rawals);

  return (rc);
}

uint8_t RPR0521RS::check_near_far(uint32_t data)
{
  if (data >= RPR0521RS_NEAR_THRESH) {
    return (RPR0521RS_NEAR_VAL);
  } else {
    return (RPR0521RS_FAR_VAL);
  }
}

float RPR0521RS::convert_lx(uint32_t *data)
{
  float lx;
  float d0, d1, d1_d0;

  if (_als_data0_gain == 0) {
    return (RPR0521RS_ERROR);
  }

  if (_als_data1_gain == 0) {
    return (RPR0521RS_ERROR);
  }

  if (_als_measure_time == 0) {
    return (RPR0521RS_ERROR);
  } else if (_als_measure_time == 50) {
    if ((data[0] & 0x8000) == 0x8000) {
      data[0] = 0x7FFF;
    }
    if ((data[1] & 0x8000) == 0x8000) {
      data[1] = 0x7FFF;
    }
  }

  d0 = (float)data[0] * (100 / _als_measure_time) / _als_data0_gain;
  d1 = (float)data[1] * (100 / _als_measure_time) / _als_data1_gain;

  if (d0 == 0) {
    lx = 0;
    return (lx);
  }

  d1_d0 = d1 / d0;

  if (d1_d0 < 0.595) {
    lx = (1.682 * d0 - 1.877 * d1);
  } else if (d1_d0 < 1.015) {
    lx = (0.644 * d0 - 0.132 * d1);
  } else if (d1_d0 < 1.352) {
    lx = (0.756 * d0 - 0.243 * d1);
  } else if (d1_d0 < 3.053) {
    lx = (0.766 * d0 - 0.25 * d1);
  } else {
    lx = 0;
  }

  return (lx);
}

uint8_t RPR0521RS::write(uint8_t memory_address, uint8_t *data, uint8_t size)
{
  uint8_t rc;

  Wire.beginTransmission(RPR0521RS_DEVICE_ADDRESS);
  Wire.write(memory_address);
  Wire.write(data, size);
  rc = Wire.endTransmission();
  return (rc);
}

uint8_t RPR0521RS::read(uint8_t memory_address, uint8_t *data, int32_t size)
{
  uint8_t rc;
  uint8_t cnt;

  Wire.beginTransmission(RPR0521RS_DEVICE_ADDRESS);
  Wire.write(memory_address);
  rc = Wire.endTransmission(false);
  if (rc != 0) {
    return (rc);
  }

  Wire.requestFrom(RPR0521RS_DEVICE_ADDRESS, size, true);
  cnt = 0;
  while(Wire.available()) {
    data[cnt] = Wire.read();
    cnt++;
  }

  return (0);
}
