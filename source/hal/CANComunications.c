#include "CANComunications.h"
#include "leds.h"

#define GROUPSHIFT 4
#define GROUPMASK  0x70
#define GROUP(x) (uint8_t)(((x) & GROUPMASK) >> GROUPSHIFT)
#define COLORMASK  0x07
#define COLOR(x) (uint8_t)((x) & COLORMASK)

#define DIGITS_RECEIVED(x) ((x) - 1)
#define CANT0(x) (4 - (DIGITS_RECEIVED(x)))

#define CAN_GROUP_MASK   0x00000007U



char msg[8];
uint32_t id;
uint8_t msglength;



bool CANInit(void){
    CAN0_Init();
    ledsInit(RED);
    ledsInit(GREEN);
    ledsInit(BLUE);
}

bool CANReceived(void){
    bool newmsgflag = CAN0_MsgGetter( &id, (uint8_t*)msg, &msglength);
    return newmsgflag;
}




bool isMsgPosition(void){

     if((msg[0] & 0x80)){
        if((GROUP(msg[0]) == GRUPO_NUM)){
            ledOff(WHITE);
            ledOn(COLOR(msg[0]));
        }
        return false;
     }

    return true;
}

uint8_t USBUpdate(char * CANData, char * CANDataType){

    *CANDataType = msg[0];
    
    uint8_t cant0 = CANT0(msglength);
    uint8_t i = 0;

    for(i=0; i < cant0; i++){
        CANData[i] = '0';
    }
    for(uint8_t j = 1; j< msglength; j++){
        CANData[i++]= msg[j];
    }

    uint8_t group = (uint8_t)(id & CAN_GROUP_MASK);

    return group;
}

bool SendCAN(char * CANData, char CANDataType, uint8_t size){
    
    char angle[size+1];

    angle[0] = CANDataType;

    for(uint8_t i = 0; i < size; i++){
        angle[1+i] = CANData[i];
    }
    
    
    return CAN0_WriteMessage(MY_ID, (uint8_t*)angle , size+1);
}

