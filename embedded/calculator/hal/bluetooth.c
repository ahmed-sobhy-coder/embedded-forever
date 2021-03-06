#include "bluetooth.h"
#define TEST_CMD   "AT"
#define RESET_CMD  "AT+RESET"
void HC05_init(uint8_t mode)
{
    UART_INIT_TYPE huart;
    huart.CHAR_LEN = 8; //int8_tlength
    huart.NSTOP_BIT = 1; //number of stop bits
    huart.PARITY_BIT = 0; //parity is diabled
    huart.TYPE = BOTH; //activate both RX & TX
    switch(mode)
    {
    case COMMAND_MODE:
        huart.BAUD_RATE = 38400; //baud rate
        break;
    case DATA_MODE:
        huart.BAUD_RATE = 9600; //baud rate
        break;
    }
    Uart_Init(UT3, &huart); //initialize uart3
}
//print to bluetooth 
void printBluetooth(int8_t* str)
{
	Uart_SendStrRcNl(UT3,str);//print to bluetooth 
}
//get from data bluetooth 
void getBluetooth(int8_t* str,uint32_t max)
{
	UART_GetStrRcNl(UT3,str,max);//print to bluetooth 
}

