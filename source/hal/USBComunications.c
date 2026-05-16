#include "mcal/uart.h"
#include "hal/USBComunications.h"

void USBCom_Init(void)
{
    UART_Init();
}

unsigned char USBCom_Receive_Data(void)
{
    return UART_Receive_Data();
}

void USBCom_SendString(char* str)
{
    UART_SendString(str);
}