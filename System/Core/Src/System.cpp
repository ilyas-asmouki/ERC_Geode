/*
 * System.cpp
 *
 *  Created on: Oct 12, 2024
 *      Author: Ilyas Asmouki
 */

#include "System.h"
#include <stdint.h>
#include <cstdio>
#include "cmsis_os2.h"
#include "stm32g4xx_hal.h"


void System::init(void) {
	const uint8_t TEST_BUF_SIZE = 64;
	char test_buf_init[TEST_BUF_SIZE];
	char test_buf_loop[TEST_BUF_SIZE];

    snprintf(test_buf_init, sizeof(test_buf_init), "SYS INIT\n");
    uint8_t counter = 0;
    while (true) {
    	snprintf(test_buf_loop, sizeof(test_buf_loop), "SYS LOOP [%u]\n", counter++);
    	HAL_Delay(1000);
    }
}
