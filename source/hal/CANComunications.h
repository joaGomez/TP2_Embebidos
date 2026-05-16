#ifndef _CANCOMUNICATIONS_H_
#define _CANCOMUNICATIONS_H_

#include "can.h"
#include <stdint.h>
#include <stdbool.h>

bool CANInit(void);

bool CANReceived(void);

bool isMsgPosition(void); // Devuelve false si es RGB, se encarga en caso de RGB de cambiar color

uint8_t USBUpdate(char * CANData, char * CANDataType); // Devuelve Grupo

bool SendCAN(char * CANData, char CANDataType, uint8_t size);

#endif // _CANCOMUNICATIONS_H_