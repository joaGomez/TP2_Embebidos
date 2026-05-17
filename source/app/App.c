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

#include "hal/USBComunications.h"
#include "hardware.h"




// #define DEBUG
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define MAXCHAR 4
#define MINTIMEELAPSED 50 // ms

#define MAXTIMEELAPSED 2000 // ms

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
void int_to_ascii(int n, char *s);
int ascii_to_int(char * s);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
AccelData_t   rawValues;   // Para X, Y, Z en g's
AccelAngles_t angles;      // Para roll y pitch en grados


char val_ascii[MAXCHAR];        // Buffer para conversión numérica


typedef struct 
{
	char pitch[MAXCHAR];
	char roll[MAXCHAR];
	char orientation[MAXCHAR];
} position_t;

position_t posGrupos[4] = {
	{{'0','0','0','0'}, {'0','0','0','0'}, {'0','0','0','0'}},
	{{'0','0','0','0'}, {'0','0','0','0'}, {'0','0','0','0'}},
	{{'0','0','0','0'}, {'0','0','0','0'}, {'0','0','0','0'}},
	{{'0','0','0','0'}, {'0','0','0','0'}, {'0','0','0','0'}}
}; // Nombre de grupo - 1

void App_Init(void) {
	Accel_Init();
	USBCom_Init();
	__enable_irq();
	// --- TEST: Enviar mensaje desde la Freedom a la PC ---
	USBCom_SendString("\r\n*********************************\r\n");
	USBCom_SendString("   FRDM-K64F: USB READY (9600)\r\n");
	USBCom_SendString("*********************************\r\n");
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

	if (Accel_StartCapture()) 
	{
		// Mientras esto ocurre, las interrupciones llenan el buffer en background
		while (!Accel_IsDataReady()) 
		{
			if (CANReceived())
			{
				if (isMsgPosition())
				{
					char CANData[MAXCHAR];
					uint8_t group;
					char CANDataType;
					group = (USBUpdate(CANData, &CANDataType)); // En posGrupos[G-1]
					switch (CANDataType)
					{
						case 'R': // Roll
							for (int i = 0; i < MAXCHAR; i++)
							{
								posGrupos[group-1].roll[i] = CANData[i];
							}
							break;
						case 'C': // Pitch
							for (int i = 0; i < MAXCHAR; i++)
							{
								posGrupos[group-1].pitch[i] = CANData[i];
							}
							break;
						case 'O': // Orientación
							for (int i = 0; i < MAXCHAR; i++)
							{
								posGrupos[group-1].orientation[i] = CANData[i];
							}
							break;
						default:
							break;
					}
					switch(group)
					{
						case 0:
							USBCom_SendString(">S0,A1,V"); // Rolido: Estación 0, Ángulo 1
							USBCom_SendString(posGrupos[0].roll);
							USBCom_SendString("\n"); // Fin de trama
							USBCom_SendString(">S0,A0,V"); // Pitch: Estación 0, Ángulo 0
							USBCom_SendString(posGrupos[0].pitch);
							USBCom_SendString("\n"); // Fin de trama
							break;
						case 1:
							USBCom_SendString(">S1,A1,V"); // Rolido: Estación 1, Ángulo 1
							USBCom_SendString(posGrupos[1].roll);
							USBCom_SendString("\n"); // Fin de trama
							USBCom_SendString(">S1,A0,V"); // Pitch: Estación 1, Ángulo 0
							USBCom_SendString(posGrupos[1].pitch);
							USBCom_SendString("\n"); // Fin de trama
							break;
						default:
						case 2:
							USBCom_SendString(">S2,A1,V"); // Rolido: Estación 2, Ángulo 1
							USBCom_SendString(posGrupos[2].roll);
							USBCom_SendString("\n"); // Fin de trama
							USBCom_SendString(">S2,A0,V"); // Pitch: Estación 2, Ángulo 0
							USBCom_SendString(posGrupos[2].pitch);
							USBCom_SendString("\n"); // Fin de trama
							break;
					}
				}
			}
		}

	}

	Accel_GetProcessedData(&rawValues);
	Accel_CalculateAngles(&rawValues, &angles);
	if ( (((angles.roll > (ascii_to_int(posGrupos[3].roll) + 5) || angles.roll < (ascii_to_int(posGrupos[3].roll) - 5)) && true) || false) ) 
	{
		USBCom_SendString(">S3,A1,V"); // Rolido: Estación 3, Ángulo 1
		int_to_ascii((int)angles.roll, posGrupos[3].roll);
		USBCom_SendString(posGrupos[3].roll);
		USBCom_SendString("\n"); // Fin de trama
		sendCAN(posGrupos[3].roll, 'R', sizeof(posGrupos[3].roll)/sizeof(posGrupos[3].roll[0]));
	}
	if ( (((angles.pitch > (ascii_to_int(posGrupos[3].pitch) + 5) || angles.pitch < (ascii_to_int(posGrupos[3].pitch) - 5)) && true) || false) ) // falta chequear el tiempo
	{
		USBCom_SendString(">S3,A0,V"); // Pitch: Estación 3, Ángulo 0
		int_to_ascii((int)angles.pitch, posGrupos[3].pitch);
		USBCom_SendString(posGrupos[3].pitch);
		USBCom_SendString("\n"); // Fin de trama
		sendCAN(posGrupos[3].pitch, 'C', sizeof(posGrupos[3].pitch)/sizeof(posGrupos[3].pitch[0]));
	}

	/*************************************
	 *
	 * 	LECTURA EN EL PUERTO DE LA PC
	 *
	 ************************************/
	
	/*
	// --- IMPRIMIR roll ---
	UART_SendString("roll: ");
	int_to_ascii((int)angles.roll, val_ascii);
	UART_SendString(val_ascii);
	UART_SendString(" deg | ");

	// --- IMPRIMIR pitch ---
	UART_SendString("pitch: ");
	int_to_ascii((int)angles.pitch, val_ascii);
	UART_SendString(val_ascii);
	UART_SendString(" deg");

	// --- NUEVA LINEA ---
	UART_SendString("\r\n");
	}
	// Delay para que la terminal sea legible
	for(volatile int i = 0; i < 5000000; i++);
	*/


	/*************************************
	 *
	 * 	LECTURA EN LA APP DE PYTHON
	 *
	 ************************************/
	// --- ENVIAR roll (angle 0) ---
	/*
	UART_SendString(">S0,A0,V"); // Cabecera: Estación 0, Ángulo 0
	int_to_ascii((int)angles.roll, val_ascii);
	UART_SendString(val_ascii);
	UART_SendString("\n"); // Fin de trama

	// --- ENVIAR pitch (angle 1) ---
	UART_SendString(">S0,A1,V"); // Cabecera: Estación 0, Ángulo 1
	int_to_ascii((int)angles.pitch, val_ascii);
	UART_SendString(val_ascii);
	UART_SendString("\n"); // Fin de trama
	*/
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


int ascii_to_int(char * s) 
{
	int result = 1;
	uint32_t aux = 0;
	uint32_t j = 1;
	uint32_t i = 0; 
	if ( *(s) == '-')
	{
		result *= -1;
		++s;
	}
	while (s[i+1] != '\0')
	{
	  j=j*10;
	  i++;
	}
	while (*s != '\0')
	{
		aux += (int)((*s) - '0')*j;
		j /= 10;
		s++;
	}
	return result*aux;
}
/*******************************************************************************
 ******************************************************************************/

