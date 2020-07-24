#ifndef __SWITCH_H__
#define __SWITCH_H__
#include "tm4c123io.h"
#include "rgb.h"
#define SWITCH_1               PF4
#define SWITCH_2               PF0
#define SWITCH_PORT       (GPIOF->DATA)
void SWITCH_Init(uint32_t sw);
uint8_t SWITCH_Read(uint32_t sw);
void SWITCH_App1(void);
void SWITCH_App2(void);
uint8_t SWITCH_IsPressed(uint8_t sw);

#endif
