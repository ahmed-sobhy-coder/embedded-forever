#ifndef _NVIC__H_
#define _NVIC__H_
#include "stdint.h"
#include "bit.h"
#include "TM4C123GH6PM.h"
#define PRIGROUB               8
void NVIC_Enable_IRQ(uint8_t isr_number,uint8_t priority);
#endif
