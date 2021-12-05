/**
 * @file MHZ19B_Controller.h
 * @brief MH-Z19B CO2 sensor controller
 * 
 * Copyright (c) 2021 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#include "MHZ19B_Controller.h"

const byte co2::Constants::START_BYTE = 0xFF;
const byte co2::Constants::REQUEST_SENSOR = 0x01;
const byte co2::Constants::READ_CO2 = 0x86;
const byte co2::Constants::CHECK_SUM = 0x79;
const uint16_t co2::Constants::UART_BAUDRATE = 9600;
const uint16_t co2::Constants::TEMPERATURE_OFFSET = 40;

HardwareSerial co2_serial(2);

co2::MHZ19B_Controller::MHZ19B_Controller() {}

void co2::MHZ19B_Controller::init() {
  co2_serial.begin(co2::Constants::UART_BAUDRATE);
  byte response[7];
  read_mhz19b(response);
}

uint16_t co2::MHZ19B_Controller::get_co2() {
  byte response[7];

  if (!read_mhz19b(response)) {
    return 0;
  }

  byte responseHigh = response[0];
  byte responseLow = response[1];
  uint16_t co2_data = (responseHigh << 8) + responseLow;
  return co2_data;
}

int16_t co2::MHZ19B_Controller::get_temperature() {
  byte response[7];

  if (!read_mhz19b(response)) {
    return 0;
  }

  int16_t temperature = response[2] - Constants::TEMPERATURE_OFFSET;

  return temperature;
}

bool co2::MHZ19B_Controller::read_mhz19b(byte* response) {
  byte cmd[9] = {Constants::START_BYTE,Constants::REQUEST_SENSOR,Constants::READ_CO2,0x00,0x00,0x00,0x00,0x00,Constants::CHECK_SUM};
  co2_serial.write(cmd, 9);
  
  const uint16_t retry_count = 10;
  for (uint16_t i = 1; ; i++) {
    byte buf[2];
    co2_serial.readBytes(buf, sizeof(buf));
    if (buf[0] == Constants::START_BYTE && buf[1] == Constants::READ_CO2) {
      break;
    }
    if (i > retry_count) {
      return false;
    }
  }
  byte buf[7];
  co2_serial.readBytes(buf, sizeof(buf));
  memcpy(response, buf, sizeof(response));
  return true;
}