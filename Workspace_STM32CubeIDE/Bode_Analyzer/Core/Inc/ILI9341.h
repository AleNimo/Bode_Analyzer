/*
 * ILI9341.h
 *
 *  Created on: Jul 21, 2022
 *      Author: Joaquin
 */

#ifndef INC_ILI9341_H_
#define INC_ILI9341_H_
#include "main.h"


/*Comands*/
//Contrast
#define VCOM_CMD	0xC5

//Memory Access Control(pag 127)
#define MEM_ACC_CTRL_CMD	0x36

//These 3 bits control MCU to memory write/read direction.
#define MY 0//Row Address Order
#define MX 0//Column Address Order
#define MV 1//Row / Column Exchange

//LCD vertical refresh direction control
#define ML 0 //Vertical Refresh Order
#define MH 0 //Horizontal Refresh Order

//RGB-BGR Order Color selector switch control
#define BGR  1//(0=RGB color filter panel, 1=BGR color filter panel)

//config MEM_ACC_CTRL
#define MEM_ACC_CTRL_CONFIG (uint16_t)(0x0000 | (MY<<7 | MX<<6 | MV<<5 | ML<<4 | BGR<<3 | MH<<2))

//16-18 bits/pixel (pag 134)
#define PIXEL_FMT_CMD	0x3A

#define DPI 0x5 //RGB Interface Format
#define DBI DPI //MCU Interface Format

#define PIXEL_FMT_CONFIG (uint16_t)(0x0000 | (DPI<<6 | DBI<<2)) // 16bit


//Sleep Out Enable (pag 245)
#define SLEEP_OUT_CMD	0x11

//Display ON (pag 109)
#define DISPLAY_ON_CMD	0x29

//Memory Write (pag 114)
#define MEM_WR_CMD	0x2C //Transfer data from MCU to frame memory.


//Column Address Set (pag 110)
#define COL_ADD_SET 0x2A //define area of frame memory where MCU can access on X position

//Page Address Set (pag 112)
#define PAGE_ADD_SET 0x2B //define area of frame memory where MCU can access on Y position




void LCD_Write(uint16_t word);

void LCD_Command_Write(uint16_t command);
void LCD_Data_Write(uint16_t data);
void LCD_Init(void);

void Address_Set(uint16_t y1,uint16_t y2,uint16_t x1,uint16_t x2);


void Draw_Pixel(uint16_t x, uint16_t y,uint16_t colour);




#endif /* INC_ILI9341_H_ */
