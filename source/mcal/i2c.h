#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>

void I2C_Init(void);
void I2C_WriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
void I2C_ReadRegisters(uint8_t slaveAddr, uint8_t startReg, uint8_t *buffer, uint8_t length);

#endif	// I2C_H
