/**
 * @file DigitalFilter.h
 * @brief Digital filter
 * 
 * Copyright (c) 2021 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#pragma once

#include <M5Stack.h>
#include <vector>

namespace filter {

struct Constants {
  static const uint16_t DATA_REGISTER;
  static const int16_t COEFFICIENTS[11];
  static const uint16_t QUANT_COEF;
};

class DigitalFilter {
public:
  DigitalFilter();
  DigitalFilter(uint16_t data);
  uint16_t get_filtered_data(uint16_t data);
private:
  std::vector<uint16_t> data_register;
};

}