/*
 * TouchGFX_DataTransfer.h
 *
 *  Created on: Sep 27, 2022
 *      Author: Joaquin
 */

#ifndef TARGET_TOUCHGFX_DATATRANSFER_H_
#define TARGET_TOUCHGFX_DATATRANSFER_H_

#include <stdint.h>

void touchgfxDisplayDriverTransmitBlock(uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
uint32_t touchgfxDisplayDriverTransmitActive(void);

#endif /* TARGET_TOUCHGFX_DATATRANSFER_H_ */
