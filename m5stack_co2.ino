/*
 * Project: CO2 sensor OLED display
 * Author: toms74209200
 *
 * Created on 2019/05/12
 * 
 * Copyright (c) 2019 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#include <vector>

#include <M5Stack.h>

#include "DigitalFilter.h"
#include "src/TimeUtil/TimeUtil.h"
#include "src/MHZ19B_Controller/MHZ19B_Controller.h"

constexpr auto RX_PIN = 1;
constexpr auto TX_PIN = 0;
constexpr auto LCD_HEIGHT = 240;
constexpr auto LCD_WIDTH = 320;
constexpr uint16_t CHART_DATA_OFFSET = 20;
constexpr uint16_t CHART_DATA_HEIGHT = LCD_HEIGHT - CHART_DATA_OFFSET;
constexpr uint16_t CHART_DATA_MIN = 350;
constexpr uint16_t CHART_DATA_MAX = 3000;

constexpr unsigned long INTERVAL = time_util::Minutes::toMillis(1);

#define DAT_AVE_NUM 16

co2::MHZ19B_Controller co2_controller;
std::vector<uint16_t> co2_data_vector(LCD_WIDTH);
uint8_t valid_data_pointer = LCD_WIDTH;

filter::DigitalFilter diginal_filter;

void setup() {
// M5stack initialization
// bool LCDEnable, bool SDEnable, bool SerialEnable, bool I2CEnable
// Serial.begin(115200);
    M5.begin(true, false, true, false); 
    M5.Lcd.setBrightness(30);
    M5.Lcd.setTextSize(3);
    M5.Lcd.clear();

// CO2 sensor initialization
    co2_controller.init();

    diginal_filter = filter::DigitalFilter(co2_controller.get_co2());

    M5.update();
}

void loop() {

    auto co2_data = co2_controller.get_co2();
    auto filtered_data = diginal_filter.get_filtered_data(co2_data);

    Serial.println(filtered_data);

    M5.lcd.clear();
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print(filtered_data);
    M5.Lcd.print("ppm");

    co2_data_vector.erase(co2_data_vector.begin());
    co2_data_vector.push_back(filtered_data);

    if (valid_data_pointer == 0) {
        for (uint8_t i = 1; i < LCD_WIDTH; i++) {
            plot_data(i - 1, i, co2_data_vector[i-1], co2_data_vector[i]);
        }
    } else {
        for (uint8_t i = valid_data_pointer; i < LCD_WIDTH; i++) {
            plot_data(i - 1, i, co2_data_vector[i-1], co2_data_vector[i]);
        }
        valid_data_pointer--;
    }

    delay(INTERVAL);
}

/**
 * @brief plot a pair data
 * @param[in] display_x0 1st position of the pair
 * @param[in] display_x1 2nd position of the pair
 * @param[in] data0 1st data of the pair
 * @param[in] data1 1nd data of the pair
 */
void plot_data(uint16_t display_x0, uint16_t display_x1, uint16_t data0, uint16_t data1) {
  uint16_t display_y0 = LCD_HEIGHT + (((data0 - CHART_DATA_MIN) * CHART_DATA_OFFSET) / CHART_DATA_MAX) - (((data0 - CHART_DATA_MIN) * CHART_DATA_HEIGHT) / CHART_DATA_MAX);
  uint16_t display_y1 = LCD_HEIGHT + (((data1 - CHART_DATA_MIN) * CHART_DATA_OFFSET) / CHART_DATA_MAX) - (((data1 - CHART_DATA_MIN) * CHART_DATA_HEIGHT) / CHART_DATA_MAX);
  M5.Lcd.drawLine(display_x0, display_y0, display_x1, display_y1, WHITE);
}