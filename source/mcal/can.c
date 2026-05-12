#include "can.h"
#include "gpio.h"
#include "hardware.h"
#include "MK64F12.h"

#define PIN_CAN0_TX    PORTNUM2PIN(PB, 18)
#define PIN_CAN0_RX    PORTNUM2PIN(PB, 19)



void CAN_Init(void) {
	gpioInit(PIN_CAN0_TX, PORT_mAlt2);
	gpioInit(PIN_CAN0_RX, PORT_mAlt2);

	CAN0->MCR &= ~(CAN_MCR_MDIS(0));		// Enables FLEXCAN



}




