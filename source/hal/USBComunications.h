#ifndef _USBCOMUNICATIONS_H_
#define _USBCOMUNICATIONS_H_

void USBCom_Init(void);
unsigned char USBCom_Receive_Data(void);
void USBCom_SendString(char* str);

#endif /* _USBCOMUNICATIONS_H_ */