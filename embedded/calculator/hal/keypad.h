#ifndef __KEYPAD_H__
#define __KEYPAD_H__
#include "tm4c123io.h"
#include "sysTick.h"

#define NCOL    4
#define NROW    4

#define KEYPAD_ROW_PORT  PORTE
#define KEYPAD_COL_PORT  PORTC

#define COL0    PC4
#define COL1    PC5
#define COL2    PC6
#define COL3    PC7

#define ROW0    PE0
#define ROW1    PE1
#define ROW2    PE2
#define ROW3    PE3
void KEYPAD_init(void);
int8_t KEYPAD_Get_Key(void);
int8_t KEYPAD_Map_Key_To_Value(int8_t key);
#endif
