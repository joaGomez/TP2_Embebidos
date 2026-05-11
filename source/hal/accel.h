#ifndef ACCEL_H
#define ACCEL_H

#include <stdint.h>


typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} AccelData_t;

void Accel_Init(void);
void Accel_ReadData(AccelData_t *data);

#endif	// ACCEL_H
