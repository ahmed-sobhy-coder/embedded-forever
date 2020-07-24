#ifndef __SYSTICK_Timer_H__
#define __SYSTICK_Timer_H__
#include "stdint.h"
#include "bit.h"
#define CYCLES_OF_ONE_SECOND         16000000
#define CYCLES_OF_ONE_MILLISECOND    16000
#define CYCLES_OF_ONE_MICROSECOND    16
#define SYS_EN   0
#define INTEN    1
#define CLK_SRC  2
#define SYS_CNT   16
void msDelay(uint32_t ms);
void usDelay(uint32_t us);
void SYSTICK_Interrupt_Init(void);
void SYSTICK_Periodic_Interval(int32_t p);
void SYSTICK_Clear_Counter(void);
#endif
