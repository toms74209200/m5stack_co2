/*
 * Project: MH-Z19B CO2 sensor read
 * Author: toms74209200
 *
 * Created on 2019/04/04
 * 
 * Copyright (c) 2019 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#include <M5Stack.h>
#include "mhz19b_uart.h"

HardwareSerial co2Serial(2);

void init_co2() {
    co2Serial.begin(9600);
}

/*
 * gets_co2() based on
 * https://blog2.creativeflake.com/2017/04/22/%E3%82%AA%E3%83%95%E3%82%A3%E3%82%B9%E6%8F%9B%E6%B0%97%E3%81%AE%E3%81%9F%E3%82%81-co2-%E3%82%BB%E3%83%B3%E3%82%B5%E3%83%BC%E4%BD%9C%E3%82%8A-%E3%83%BC-arduino-bme280-mh-z19%E7%B7%A8/
 */
int gets_co2(){
// MH-Z19 uart communication
    byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
    unsigned char response[9]; // for answer
    co2Serial.write(cmd, 9); //request PPM CO2
    co2Serial.readBytes(response, 9);
    if (response[0] != 0xFF){
        return 0;
    }
    if (response[1] != 0x86){
        return 0;
    }

// CO2 calculation
    unsigned int responseHigh = (unsigned int) response[2];
    unsigned int responseLow = (unsigned int) response[3];
    int ppm = (256 * responseHigh) + responseLow;
    return ppm;
}

int gets_co2_mid(){
    int ary_co2_data[3];

    memset(ary_co2_data, 0, sizeof(ary_co2_data));

    for (int i=0;i<3;i++) {
        ary_co2_data[i] = gets_co2();
        delay(10);
    }

    for (int i=0;i<3;i++) {
        for (int j=i+1;j<3;j++){
            if (ary_co2_data[i] > ary_co2_data[j]) {
                int tmp;
                tmp = ary_co2_data[i];
                ary_co2_data[i] = ary_co2_data[j];
                ary_co2_data[j] = tmp;
            }
        }
    }

    return ary_co2_data[1];

}
