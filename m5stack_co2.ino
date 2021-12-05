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

#include <M5Stack.h>
#include "src/TimeUtil/TimeUtil.h"
#include "src/MHZ19B_Controller/MHZ19B_Controller.h"

constexpr auto RX_PIN = 1;
constexpr auto TX_PIN = 0;
constexpr auto LCD_HIGHT = 240;
constexpr auto LCD_WIDTH = 320;

constexpr unsigned long INTERVAL = time_util::Minutes::toMillis(1);

#define DAT_AVE_NUM 16

co2::MHZ19B_Controller co2_controller;

void data_array_shift();

int ary_dat[DAT_AVE_NUM];
int *p_dat;
int i,j,k;
unsigned int sum;

int ary_y[LCD_WIDTH];
int end_point;

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
    int t = co2_controller.get_co2();

    for(i=0;i<=DAT_AVE_NUM-1;i++) {
        ary_dat[i] = t;
        sum += t;
    }
}

void loop() {

    M5.update();

    end_point = 0;

    while (1) {

        p_dat = &ary_dat[0];

        for (i=0;i<=DAT_AVE_NUM-1;i++) {
        // Average
            sum -= *p_dat;
            *p_dat = co2_controller.get_co2();
            sum += *p_dat;
            int dat_ave = sum >> 4;
            p_dat++;

        //Serial output
            Serial.println(dat_ave,DEC);
        
        // LCD data print
            M5.lcd.clear();
            M5.Lcd.setCursor(10, 10);
            M5.Lcd.print(dat_ave);
            M5.Lcd.print("ppm");

        // LCD graph print
            ary_y[0] = LCD_HIGHT - (dat_ave >> 4);

            for (j=0;j<LCD_WIDTH;j++) {
                if (j < end_point) {
                    if (j > 0) {
                        M5.Lcd.drawLine(LCD_WIDTH-(j+2), ary_y[j], LCD_WIDTH-(j+1), ary_y[j-1], WHITE);
                    } else {
                        M5.Lcd.drawLine(LCD_WIDTH-(j+1), ary_y[j], LCD_WIDTH-(j+1), ary_y[j], WHITE);
                    }
                    if (j == end_point-1) {
                        data_array_shift();
                    }
                } else if (j == end_point) {
                    if (end_point == LCD_WIDTH) {
                        data_array_shift();
                    }
                } else {
                    if (end_point > 0) {
                        data_array_shift();
                    } else {
                        ary_y[j] = ary_y[j-1];
                    }
                    end_point = j;
                    break;
                }
            }

    // Interval
        delay(INTERVAL);
        }
    }
}

void data_array_shift() {
    for (k=0;k<end_point;k++) {
        ary_y[end_point-k] = ary_y[end_point-(k+1)];
    }
}