/*
 * AD9833.c
 *
 *  Created on: Nov 16, 2022
 *      Author: Alejo
 */
#include "main.h"
#include "AD9833.h"

extern SPI_HandleTypeDef hspi3;

#define ROUND_TO_INT(x) ((uint32_t)((x)+0.5))

void AD9833_Init(void)
{
	uint16_t control_reg = 0b0010000100000000;
	/*
	 * D15,D14 = 00: escritura en registro de control
	 * D13 = 1: escritura completa del registro FREQX en siguientes dos transmisiones
	 * D12 = 0: ignorado dado que D13 = 1 (selecciona parte MSB o LSB de FREQX en caso de que D13=0)
	 * D11 = 0: FREQ0 seleccionado para la frecuencia de salida
	 * D10 = 0: PHASE0 seleccionado para la el acumulador de fase
	 * D09 = 0: reservado, se debe escribir 0
	 * D08 = 1: reset activado, registros internos a 0 (no resetea FREQX ni PHASEX), inhabilita la salida del DAC mientras se inicializa
	 * D07 = 0: Master Clock (MCLOCK) habilitado, es el utilizado para generar la señal
	 * D06 = 0: DAC activo
	 * D05 = 0: para modo senoidal
	 * D04 = 0: reservado, se debe escribir 0
	 * D03 = 0: ignorado estando en modo senoidal (indica division de clock si la señal es cuadrada)
	 * D02 = 0: reservado, se debe escribir 0
	 * D01 = 0: para modo senoidal
	 * D00 = 0: reservado, se debe escribir 0
	 */
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&control_reg, 1, HAL_MAX_DELAY);	//Escribo registro de control
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);

	/******************************************/

	AD9833_SetFrequency(1);	//Escribo FREQ0 con la frecuencia de 1Hz

	/******************************************/

	uint16_t phase_reg = 0b1100000000000000;
	/*
	 * D15,D14,D13 = 110: escritura en registro PHASE0
	 * D12 = 0: bit ignorado
	 * D11 a D0 = 0: se escribe esa fase al registro (no importa la fase que tiene)
	 */

	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&phase_reg, 1, HAL_MAX_DELAY);	//Escribo en PHASE0 la fase de 0
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);

	/******************************************/
	control_reg = 0b0010000000000000; //Saco el reset con D08 = 0, la salida se activa luego de 8 ciclos del MasterClock

	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&control_reg, 1, HAL_MAX_DELAY);	//Escribo registro de control
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);

}


void AD9833_SetFrequency(uint32_t freq_out)
{
	//Freq_reg = Fout * 2^28 / F_MasterClock

	if(freq_out > 12500000) freq_out = 12500000;	//Frecuencia máxima posible segun datasheet

	float freq_reg = freq_out * (268435456.0 / MASTER_CLOCK);

	uint32_t auxiliar = ROUND_TO_INT(freq_reg);

	uint16_t freq_reg_vector[2] = {(0b01<<14) | (auxiliar & 0x3FFF), (0b01<<14) | auxiliar>>14};
	/*
	 * D15,D14 = 01 : Escribo en registro FREQ0
	 */

	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi3, (uint8_t*)freq_reg_vector, 2, HAL_MAX_DELAY);	//Escribo en FREQ0 la frecuencia de 1Hz
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
}

void AD9833_SetEnabled(uint8_t state)
{
	uint16_t control_reg;

	if(state == TRUE)
		control_reg = 1<<13;
	else
		control_reg = 1<<13 | 0xC0;	//D7,D6 = 11: Deshabilito DAC y clock interno que actualiza la salida (los registros se pueden escribir)

	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&control_reg, 1, HAL_MAX_DELAY);	//Escribo registro de control
	HAL_Delay(1);
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
}
