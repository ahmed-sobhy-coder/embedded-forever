#include "NVIC.h"
void NVIC_Enable_IRQ(uint8_t isr_number,uint8_t priority){
	STV3BI(SCB->AIRCR,PRIGROUB,0);//3bit for priorty levels,no subpriorty bits
	STV3BI(NVIC->IP[isr_number],5,priority);//set priority starting from index 5
	ST1B(NVIC->ISER[isr_number>>16],(isr_number%32)); //isr_number>>16 = isr_number/32
}
