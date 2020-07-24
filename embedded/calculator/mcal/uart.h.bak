#ifndef __UART_H__
#define __UART_H__
#include "stdint.h"
#include "tm4c123io.h"
#include "bit.h"
#include "strfuncs.h"
#include "nvic.h"
#include "rgb.h"
#include "systick.h"
//#define CR   0x0D
#define LF   0x0A
#define BS   0x08

#define NEW_LINE        LF
#define wheelsRIAGE_RETURN CR
#define BACK_SPACE    BS


#define RX        0
#define TX        1
#define BOTH      2

#define U0RX  PA0
#define U0TX  PA1
#define U1RX  PB0
#define U1TX  PB1
#define U2RX  PD6
#define U2TX  PD7
#define U3RX  PC6
#define U3TX  PC7
#define U4RX  PC4
#define U4TX  PC5
#define U5RX  PE4
#define U5TX  PE5 
#define U6TX  PD4 //USB
#define U6RX  PD5 //USB
#define U7RX  PE0;
#define U7TX  PE1;



#define BAUD_9600                      9600U

#define BAUDINT(SYSTEM_CLOCK,BAUD)           (SYSTEM_CLOCK/(16*BAUD))

#define BAUDFLOAT(SYSTEM_CLOCK,BAUD)         (int)((((((double)SYSTEM_CLOCK/(16*BAUD))- BAUDINT(sysclock,BAUD))* 64)+0.5))
#define CHAR_SIZE(bits)          (bits-5)

#define UARTEN  0
#define WLEN    5 
#define STP2    3
#define FEN     4
#define CS   0
#define HSE   5
#define TXE   8
#define RXE   9
#define TXFF  5
#define RXFE  4
#define UT0    0
#define UT1    1
#define UT2    2
#define UT3    3
#define UT4    4
#define UT5    5
#define UT6    6
#define UT7    7
#define RXIM     4
#define TXIM     5
#define RXMIS    4
#define RXIC    4
#define TXMIS   5
#define TXIC    5
typedef struct uart{
    uint32_t BAUD_RATE; //baud rate
    uint8_t CHAR_LEN; //number of chars
    uint8_t NSTOP_BIT; //number of stop bit
    uint8_t PARITY_BIT; //parity bit even or odd
    uint8_t TYPE; //transmitter,receiver, both
}UART_INIT_TYPE; //UART attributes
typedef enum
{
    BAUDRATE_VALID, //the baud rate is valid
    BAUDRATE_INVALID, //the baud rate is invalid
    CHARSIZE_VALID, //character size is valid
    CHARSIZE_INVALID //character size is invalid
} UART_INIT_STATUS;
#define UART0_VECTOR   5
void Uart_Init(uint8_t utn, UART_INIT_TYPE* utConfig) ;
void Uart_SendChar(uint8_t uartn, int8_t character) ;
void Uart_SendStr(uint8_t uartn, int8_t* str) ;
int8_t UART_GetChar(uint8_t uartn) ;
void UART_GetStr(uint8_t uartn, int8_t* string, uint32_t max);
void Uart_SendInt(uint8_t uartn,int32_t num);
void Uart_SendFloat(uint32_t uartn,double float_num,uint8_t precision);
void UART_Interrupt_Init(uint8_t uartn, uint32_t baudRate, uint8_t both);
void UART_AT_Resp_Receive(uint8_t uartn, int8_t* string, uint32_t max);
void Uart_SendStrRcNl(uint8_t uartn, int8_t* str);//send string with '\r''\n'
void UART_GetStrRcNl(uint8_t uartn, int8_t* str, uint32_t max);//get string has '\r''\n' in its chars
//print to terminal and bluetooth 
void printTerm(int8_t* str);
#endif  
