/*
 * AD9833.h
 *
 *  Created on: Nov 16, 2022
 *      Author: Alejo
 *
 *  SPI:
 *  SCK máximo: 40MHz
 *  CPOL: HIGH (1)
 *  CPHA: First Edge (0)
 */

#ifndef INC_AD9833_H_
#define INC_AD9833_H_

/*Definiciones*/

#define TRUE 1
#define FALSE 0

#define MASTER_CLOCK 25000000	//Se debe testear que sean 25MHz

/*Prototipos de Funciones*/

//Por defecto configura:
//Seno de 1Hz
//(Usa registros FREQ0 y PHASE0)
void AD9833_Init(void);

//En Hz
void AD9833_SetFrequency(uint32_t);
void AD9833_SetEnabled(uint8_t);

#endif /* INC_AD9833_H_ */
