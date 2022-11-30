/*
 * Touch.h
 *
 *  Created on: Oct 29, 2022
 *      Author: Joaquin
 */

#ifndef INC_TOUCH_H_
#define INC_TOUCH_H_

#include "main.h"

#define XPT2046_MIN_RAW_Y 2200
#define XPT2046_MIN_RAW_X 3400
#define XPT2046_MAX_RAW_Y 31000
#define XPT2046_MAX_RAW_X 31000

#define READ_X 0x90
#define READ_Y 0xD0



extern SPI_HandleTypeDef hspi2;

uint8_t XPT2046_TouchGetCoordinates(uint32_t* x, uint32_t* y);


#endif /* INC_TOUCH_H_ */
