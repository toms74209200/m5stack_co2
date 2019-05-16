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

#ifndef MHZ19B_UART_H
#define MHZ19B_UART_H

#include <M5Stack.h>

void init_co2();
int gets_co2();
int gets_co2_mid();

#endif