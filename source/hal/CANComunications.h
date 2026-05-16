#ifndef _CANCOMUNICATIONS_H_
#define _CANCOMUNICATIONS_H_

#include <stdint.h>
#include <stdbool.h>


bool CANReceived(void);

uint8_t isMsgRGB(void); // Devuelve ZERO si no es mio o color si es mio

uint8_t USBUpdate(char * CANData, char * CANDataType); // Devuelve Grupo

bool SendCAN(char * CANData, char * CANDataType, uint8_t size);

#endif // _CANCOMUNICATIONS_H_