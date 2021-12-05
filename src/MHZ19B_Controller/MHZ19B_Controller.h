/**
 * @file MHZ19B_Controller.h
 * @brief MH-Z19B CO2 sensor controller
 * 
 * Copyright (c) 2021 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#pragma once

#include <M5Stack.h>

namespace co2 {

struct Constants {
  static const byte START_BYTE;
  static const byte REQUEST_SENSOR;
  static const byte READ_CO2;
  static const byte CHECK_SUM;
  static const uint16_t UART_BAUDRATE;
  static const uint16_t TEMPERATURE_OFFSET;
};

class MHZ19B_Controller {
public:
  MHZ19B_Controller();
  void init();
  uint16_t get_co2();
  int16_t get_temperature();
private:
  bool read_mhz19b(byte* response);
};

}
