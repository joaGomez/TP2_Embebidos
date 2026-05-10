/***************************************************************************/ /**
   @file     App.c
   @brief    Application functions
   @author   Nicolás Magliola
  ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

// FOR INIT
#include "hal/board.h"
#include "hal/leds.h"
#include "hal/system.h"
#include "hal/timers.h"

#include "mcal/uart.h"
#include "hardware.h"

// #define DEBUG
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



void App_Init(void) {

	UART_Init();
	__enable_irq();
	// --- TEST: Enviar mensaje desde la Freedom a la PC ---
	UART_SendString("\r\n*********************************\r\n");
	UART_SendString("   FRDM-K64F: UART READY (9600)\r\n");
	UART_SendString("*********************************\r\n");
	UART_SendString("Escribe 'A' para testear recepcion:\r\n");

}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run(void) {

	// --- TEST: Recibir de la PC y validar ---

		// El programa se queda aquí esperando un byte
		unsigned char dato = UART_Receive_Data();

		if (dato == 'A' || dato == 'a') {
			// Caso Correcto
			UART_SendString("' -> RESULTADO: CORRECTO\r\n");
		} else {
			// Caso Incorrecto
			UART_SendString("' -> RESULTADO: INCORRECTO\r\n");
		}

		UART_SendString("Intenta de nuevo: ");
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*******************************************************************************
 ******************************************************************************/
