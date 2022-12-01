/*
 * Touch.c
 *
 *  Created on: Oct 29, 2022
 *      Author: Joaquin
 */

#include "Touch.h"




uint8_t XPT2046_TouchGetCoordinates(uint32_t* x, uint32_t* y)
{

	static const uint8_t cmd_read_x[] = { READ_X };
    static const uint8_t cmd_read_y[] = { READ_Y };
    static const uint8_t zeroes_tx[] = { 0x00, 0x00 };



    HAL_GPIO_WritePin(TOUCH_CS_GPIO_Port,TOUCH_CS_Pin,0);

    uint32_t avg_x = 0;
    uint32_t avg_y = 0;
    uint8_t nsamples = 0;

    for(uint8_t i = 0; i < 16; i++)
    {
        if(HAL_GPIO_ReadPin(TOUCH_IRQ_GPIO_Port, TOUCH_IRQ_Pin))
            break;

        nsamples++;

        uint8_t y_raw[2];
        uint8_t x_raw[2];


        HAL_SPI_Transmit(&hspi2, (uint8_t*)cmd_read_y, sizeof(cmd_read_y), HAL_MAX_DELAY);
        HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)zeroes_tx, y_raw, sizeof(y_raw), HAL_MAX_DELAY);

        HAL_SPI_Transmit(&hspi2, (uint8_t*)cmd_read_x, sizeof(cmd_read_x), HAL_MAX_DELAY);
        HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)zeroes_tx, x_raw, sizeof(x_raw), HAL_MAX_DELAY);



        avg_x += (((uint16_t)x_raw[0]) << 8) | ((uint16_t)x_raw[1]);
        avg_y += (((uint16_t)y_raw[0]) << 8) | ((uint16_t)y_raw[1]);
    }

    HAL_GPIO_WritePin(TOUCH_CS_GPIO_Port, TOUCH_CS_Pin, 1);

    if(nsamples < 16)
        return 0;

    uint32_t raw_x = (avg_x / 16);

    if(raw_x < XPT2046_MIN_RAW_X) raw_x = XPT2046_MIN_RAW_X;
    if(raw_x > XPT2046_MAX_RAW_X) raw_x = XPT2046_MAX_RAW_X;

    uint32_t raw_y = (avg_y / 16);

    *x = raw_x;
    *y = raw_y;

    if(raw_y < XPT2046_MIN_RAW_Y) raw_y = XPT2046_MIN_RAW_Y;
    if(raw_y > XPT2046_MAX_RAW_Y) raw_y = XPT2046_MAX_RAW_Y;


    // Uncomment this line to calibrate touchscreen:
//    printf("raw_x = %6d, raw_y = %6d\r\n", (int) raw_x, (int) raw_y);
//    printf("\x1b[1F");


	*x = 320-(raw_x - XPT2046_MIN_RAW_X) * 320 / (XPT2046_MAX_RAW_X - XPT2046_MIN_RAW_X);
	*y =(raw_y - XPT2046_MIN_RAW_Y) * 240 / (XPT2046_MAX_RAW_Y - XPT2046_MIN_RAW_Y);

    return 1;
}
