/**
 * @file DigitalFilter.cpp
 * @brief Digital filter
 * 
 * Copyright (c) 2021 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#include "DigitalFilter.h"

const uint16_t filter::Constants::DATA_REGISTER = 11;
// FIR fileter coefficients. hamming window/cutoff=0.9/10taps/quantized
const int16_t filter::Constants::COEFFICIENTS[] = {
      0, 1, 2, 5, 5, 0, -14, -38, -64, -85, 844
    };
// quantized parameter(amplitude gain)
const uint16_t filter::Constants::QUANT_COEF = 656;

filter::DigitalFilter::DigitalFilter() {}

filter::DigitalFilter::DigitalFilter(uint16_t data) {
  data_register.resize(filter::Constants::DATA_REGISTER);
  for (auto i = 0; i < filter::Constants::DATA_REGISTER; i++) {
    data_register.erase(data_register.begin());
    data_register.push_back(data);
  }
}

uint16_t filter::DigitalFilter::get_filtered_data(uint16_t data) {
  data_register.erase(data_register.begin());
  data_register.push_back(data);
  
  int32_t result = 0;
  for (auto i = 0; i < filter::Constants::DATA_REGISTER; i++) {
    result += filter::Constants::COEFFICIENTS[i] * data_register[i];
  }
  return result / filter::Constants::QUANT_COEF;
}
