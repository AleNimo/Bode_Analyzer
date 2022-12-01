/*
 * TouchGFX_DataTransfer.c
 *
 *  Created on: Sep 27, 2022
 *      Author: Joaquin
 */
#include "TouchGFX_DataTransfer.h"
#include "ILI9341.h"

static uint8_t isTransmittingData = 0;
extern void DisplayDriver_TransferCompleteCallback();

uint32_t touchgfxDisplayDriverTransmitActive(void)
{
	return isTransmittingData;
}

void touchgfxDisplayDriverTransmitBlock(uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	isTransmittingData = 1;
	Address_Set(x, x+w-1, y, y+h-1);
	uint32_t i = 0;
	uint16_t pixel16bit = 0;


	while(i<(w*h*2))
	{
		pixel16bit = 0;
		pixel16bit = pixels[i+1]<<8 | pixels[i];
		LCD_Data_Write(pixel16bit);
		i+=2;
	}
	isTransmittingData = 0;
	DisplayDriver_TransferCompleteCallback();
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI1) {
		//ILI9341_EndOfDrawBitmap();
		isTransmittingData = 0;
		DisplayDriver_TransferCompleteCallback();
	}
}

