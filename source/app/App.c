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
#include "hal/accel.h"

#include "mcal/uart.h"
#include "hardware.h"




// #define DEBUG
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
void int_to_ascii(int n, char *s);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
AccelData_t   rawValues;   // Para X, Y, Z en g's
AccelAngles_t angles;      // Para Rolido y Cabeceo en grados


char val_ascii[12];        // Buffer para conversión numérica



void App_Init(void) {
	Accel_Init();
	UART_Init();
	__enable_irq();

	// --- TEST: Enviar mensaje desde la Freedom a la PC ---
	UART_SendString("\r\n*********************************\r\n");
	UART_SendString("   FRDM-K64F: UART READY (9600)\r\n");
	UART_SendString("*********************************\r\n");

}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run(void) {


	/*************************************
	 *
	 * 			TEST UART
	 *
	 ************************************/


	// El programa se queda aquí esperando un byte
	/*unsigned char dato = UART_Receive_Data();

	if (dato == 'A' || dato == 'a') {
		// Caso Correcto
		UART_SendString("' -> RESULTADO: CORRECTO\r\n");
	} else {
		// Caso Incorrecto
		UART_SendString("' -> RESULTADO: INCORRECTO\r\n");
	}

	UART_SendString("Intenta de nuevo: ");*/

	/*************************************
	 *
	 * 	TEST ACELEROMETRO CON I2C
	 *
	 ************************************/

	if (Accel_StartCapture()) {

		// Mientras esto ocurre, las interrupciones llenan el buffer en background
		while (!Accel_IsDataReady()) {



			//	Código en paralelo



		}

		Accel_GetProcessedData(&rawValues);
		Accel_CalculateAngles(&rawValues, &angles);

		// --- IMPRIMIR ROLIDO ---
		UART_SendString("Rolido: ");
		int_to_ascii((int)angles.roll, val_ascii);
		UART_SendString(val_ascii);
		UART_SendString(" deg | ");

		// --- IMPRIMIR CABECEO ---
		UART_SendString("Cabeceo: ");
		int_to_ascii((int)angles.pitch, val_ascii);
		UART_SendString(val_ascii);
		UART_SendString(" deg");

		// --- NUEVA LINEA ---
		UART_SendString("\r\n");
		}

		// Delay para que la terminal sea legible
		for(volatile int i = 0; i < 5000000; i++);

}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void int_to_ascii(int n, char *s) {
    int i = 0, sign;

    if ((sign = n) < 0) n = -n; // Guardar signo y hacer positivo

    // Extraer dígitos en orden inverso
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) s[i++] = '-';
    s[i] = '\0';

    // Invertir el string (porque los dígitos se sacaron al revés)
    for (int j = 0, k = i-1; j < k; j++, k--) {
        char temp = s[j];
        s[j] = s[k];
        s[k] = temp;
    }
}
/*******************************************************************************
 ******************************************************************************/
