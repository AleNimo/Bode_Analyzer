#ifndef GLOBALES_H
#define GLOBALES_H

#include "libusb.h"


#define MY_VENDOR  ((uint16_t) 1155)//0x0483)
#define MY_PRODUCT ((uint16_t) 22352)//0x5910)

#define TRANSFER_SIZE ((uint8_t) 64)

libusb_device **devs;
libusb_context *ctx = NULL;

libusb_device_handle *dev_handle;

libusb_device_descriptor desc;
libusb_config_descriptor *config;

const libusb_interface *inter;
const libusb_interface_descriptor *interdesc;
const libusb_endpoint_descriptor *epdesc;

uint8_t connected = 0;
uint8_t Dispositivo;


#endif // GLOBALES_H
