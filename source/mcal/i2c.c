#include "i2c.h"
#include "hardware.h"
#include "MK64F12.h"


/************************************************
 * 			PRIVATE FUNCTIONS
 ***********************************************/

static int I2C_Wait(void) {
    uint32_t timeout = 10000;

    // Esperar bandera de interrupción
    while (!(I2C0->S & I2C_S_IICIF_MASK) && timeout > 0) {
        timeout--;
    }

    if (timeout == 0) return -1; // Error por tiempo agotado

    I2C0->S |= I2C_S_IICIF_MASK; // Limpiar bandera SIEMPRE

    // Verificar si el esclavo nos dio el ACK
    // Si RXAK es 1, el esclavo NO respondió (NACK)
    if (I2C0->S & I2C_S_RXAK_MASK) {
        return -1; // Error: Nadie respondió
    }

    return 0;
}

static void I2C_Start(void) {
    // Esperar a que el bus esté libre antes de iniciar
    while (I2C0->S & I2C_S_BUSY_MASK);

    I2C0->C1 |= I2C_C1_MST_MASK;
    I2C0->C1 |= I2C_C1_TX_MASK;
}

static void I2C_Stop(void) {
    I2C0->C1 &= ~I2C_C1_MST_MASK; // Genera STOP
    I2C0->C1 &= ~I2C_C1_TX_MASK;  // Pone en modo escucha

    // ESPERA CRÍTICA: Esperar a que el hardware confirme que el bus está libre
    uint32_t timeout = 1000;
    while ((I2C0->S & I2C_S_BUSY_MASK) && timeout > 0) {
        timeout--;
    }
}


/************************************************
 * 			PUBLIC FUNCTIONS
 ***********************************************/

void I2C_Init(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;    // Clock Puerto E
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;     // Clock I2C0

    PORTE->PCR[24] = PORT_PCR_MUX(5);      // PTE24 -> I2C0_SCL
    PORTE->PCR[25] = PORT_PCR_MUX(5);      // PTE25 -> I2C0_SDA

    I2C0->F = 0x1F;                        // Configuración de frecuencia (~100kHz)
    I2C0->C1 = I2C_C1_IICEN_MASK;          // Habilitar I2C0
}

void I2C_WriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
    I2C_Start();

    I2C0->D = (devAddr << 1);              // Dirección + Write (0)
    I2C_Wait();

    I2C0->D = regAddr;                     // Registro a escribir
    I2C_Wait();

    I2C0->D = data;                        // Dato a enviar
    I2C_Wait();

    I2C_Stop();
}


void I2C_ReadRegisters(uint8_t slaveAddr, uint8_t startReg, uint8_t *buffer, uint8_t length) {
	I2C_Start();
	I2C0->D = (slaveAddr << 1);    // Dirección + Write (0)
	I2C_Wait();

	I2C0->D = startReg;            // Registro inicial (ej: 0x01)
	I2C_Wait();

	// 2. Fase de Reinicio (Repeated Start) para cambiar a modo Lectura
	I2C0->C1 |= I2C_C1_RSTA_MASK;  // Repeated Start
	I2C0->D = (slaveAddr << 1) | 1; // Dirección + Read (1)
	I2C_Wait();

	// 3. Preparar el cambio a modo Recepción
	I2C0->C1 &= ~I2C_C1_TX_MASK;   // TX=0 (Recibir)
	I2C0->C1 &= ~I2C_C1_TXAK_MASK; // Asegurar que mandamos ACK al inicio

	// Dummy Read: El primer acceso a D dispara el reloj para traer el primer byte real
	volatile uint8_t dummy = I2C0->D;
	I2C_Wait();

	// 4. EL BUCLE QUE PREGUNTASTE:
	for (int i = 0; i < length; i++) {

		if (i == (length - 2)) {
			// Penúltimo byte: Configurar NACK para el final
			I2C0->C1 |= I2C_C1_TXAK_MASK;
		}

		if (i == (length - 1)) {
			// Último byte: Generar STOP antes de la última lectura de D
			I2C_Stop();
		}

		buffer[i] = I2C0->D; // Capturar el byte que ya llegó al registro

		if (i < (length - 1)) {
			// No esperamos en el último porque el STOP ya cerró el bus
			I2C_Wait();
		}
	}
}

