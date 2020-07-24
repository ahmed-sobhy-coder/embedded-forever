#ifndef _BLUETOOTH__H_
#define _BLUETOOTH__H_
#include "uart.h"

#define COMMAND_MODE   1
#define DATA_MODE      2
void HC05_init(uint8_t mode);
//print to terminal and bluetooth 
void print(int8_t* str);
//get from data bluetooth 
void getBluetooth(int8_t* str,uint32_t max)  ;
//print to bluetooth 
void printBluetooth(int8_t* str);
#endif
