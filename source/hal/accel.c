#include "accel.h"
#include "board.h"
#include "mcal/i2c.h"

void Accel_Init(void) {
    // 1. Poner el sensor en Standby para poder configurar registros
    I2C_WriteByte(ACCEL_ADDR, REG_CTRL_REG1, 0x00);

    // 2. Configurar rango dinámico a +/- 2g
    I2C_WriteByte(ACCEL_ADDR, REG_XYZ_DATA_CFG, 0x00);

    // 3. Activar el sensor (Modo Active, ODR 800Hz)
    I2C_WriteByte(ACCEL_ADDR, REG_CTRL_REG1, 0x01);
}

void Accel_ReadData(AccelData_t *data) {
	uint8_t buffer[6]; // X_MSB, X_LSB, Y_MSB, Y_LSB, Z_MSB, Z_LSB

	// Llamamos a la función genérica de I2C
	// Pedimos 6 bytes empezando desde el registro 0x01
	I2C_ReadRegisters(ACCEL_ADDR, REG_OUT_X_MSB, buffer, 6);

	// Procesamos el formato de 14 bits
	data->x = (int16_t)((buffer[0] << 8) | buffer[1]) >> 2;
	data->y = (int16_t)((buffer[2] << 8) | buffer[3]) >> 2;
	data->z = (int16_t)((buffer[4] << 8) | buffer[5]) >> 2;
}
