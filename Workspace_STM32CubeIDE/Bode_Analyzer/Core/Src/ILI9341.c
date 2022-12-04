/*
 * ILI9341.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Joaquin
 */
#include "ILI9341.h"


void LCD_Write(uint16_t word)
{
	LCD_WR_GPIO_Port->BSRR = (uint32_t)LCD_WR_Pin << 16U;	//pin en 0

	GPIOC->ODR = ((GPIOC->ODR) & 0xFFFFE000) | (word & 0x1FFF); // bits 0 a 12 de word
	GPIOB->ODR = ((GPIOB->ODR) & 0xFFFFFFF8) | (word >>13); // bits 13 a 15 de word

	LCD_WR_GPIO_Port->BSRR = LCD_WR_Pin; //pin en 1
}

void LCD_Command_Write(uint16_t command)
{
	LCD_RS_GPIO_Port->BSRR = (uint32_t)LCD_RS_Pin << 16U;	//pin en 0

	LCD_Write(command);

}

void LCD_Data_Write(uint16_t data)
{
	LCD_RS_GPIO_Port->BSRR = LCD_RS_Pin; //pin en 1

	LCD_Write(data);

}

void LCD_Init(void)
{
	//Reset LCD
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, 1);
	HAL_Delay(5);///////////TENER CUIDADO PREUGNTAR
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, 0);
	HAL_Delay(15);
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, 1);
	HAL_Delay(15);

	//Preparacion Secuencia de Escritura
	//chip select active low
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, 1);
	HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, 1);
	HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, 1);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, 0);

	//Contraste tal vez
	LCD_Command_Write(VCOM_CMD);
	LCD_Data_Write(0x5F);//VMH
	LCD_Data_Write(0x64);//VML



	//Memory Acccess Control
	LCD_Command_Write(MEM_ACC_CTRL_CMD);
	LCD_Data_Write(MEM_ACC_CTRL_CONFIG);

	//Pixel Format
	LCD_Command_Write(PIXEL_FMT_CMD);
	LCD_Data_Write(0x55);


	//Sleep Mode Off
	LCD_Command_Write(SLEEP_OUT_CMD);
	HAL_Delay(10);//necessary to wait 5msec before sending next command

	//Sleep Mode Off
	LCD_Command_Write(DISPLAY_ON_CMD);

	//Write to frame memory
	//LCD_Command_Write(MEM_WR_CMD);

}

void Address_Set(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2)
{
	LCD_Command_Write(COL_ADD_SET);
	LCD_Data_Write(x1>>8);
	LCD_Data_Write(0xFF & x1);
	LCD_Data_Write(x2>>8);
	LCD_Data_Write(0xFF & x2);

	LCD_Command_Write(PAGE_ADD_SET);
	LCD_Data_Write(y1>>8);
	LCD_Data_Write(0xFF & y1);
	LCD_Data_Write(y2>>8);
	LCD_Data_Write(0xFF & y2);


	LCD_Command_Write(MEM_WR_CMD);

}

void Draw_Pixel(uint16_t x, uint16_t y,uint16_t colour)
{
	Address_Set(x, x+1, y, y+1);

	LCD_Data_Write(colour);
}


