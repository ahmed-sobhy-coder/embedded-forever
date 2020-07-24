#include "TM4C123GH6PM.h"
#include "sysTick.h"
volatile uint32_t tick; //will be increment every 1ms
volatile uint32_t _tick; //will take current tick value
extern uint32_t sysclock;

void msDelay(uint32_t ms) {
	uint32_t noCycles= (sysclock/1000)-1; //to get period of 1ms
	SysTick->LOAD= noCycles - 1; /*Reload register is going th have this value*/
	while (ms > 0) {
		SysTick->VAL = 0;  /*-write-clear operation,
		 -clear current reg and count bit flag
		 -any wri
		te to current clears it
		 */
		ST1B(SysTick->CTRL,SYS_EN); /*ENABLE_SYSTICK the down counter*/
		ST1B(SysTick->CTRL,CLK_SRC);/*it means use the internal clock not PIOSC*/
		while (RD1B(SysTick->CTRL,SYS_CNT) == 0)
			; /* wait until down counter underfLOW, 
			 wait until count bit becomes 1*/
		ms--;
	}
}
void usDelay(uint32_t us) {
	uint32_t noCycles= (sysclock/1000000)-1; //to get period of 1s
	SysTick->LOAD = noCycles - 1; /*Reload register is going th have this value*/
	while (us > 0) {
		SysTick->VAL= 0; /*-write-clear operation,
		 -clear current reg and count bit flag
		 -any write to current clears it
		 */
		ST1B(SysTick->CTRL,SYS_EN); /*ENABLE_SYSTICK the down counter*/
		ST1B(SysTick->CTRL,CLK_SRC);/*it means use the internal clock not PIOSC*/
		while (RD1B(SysTick->CTRL,SYS_CNT) == 0)
			; /* wait until down counter underfLOW, 
			 wait until count bit becomes 1*/
		us--;
	}
}
/*atomic function, we disable interrupt to a void race condition */
uint32_t Get_Tick(void){
  __disable_irq(); //disable global interrupt
	_tick=tick; //critical section
  __enable_irq();//ENABLE_SYSTICK gloaba interrupt
	return _tick;
}
/* create the required ms delay */
void TaskDelay(uint32_t ms){
	uint32_t current_tick=Get_Tick();//store the value of current tick
	while((Get_Tick()- current_tick)<ms);//wait to create the required ms
}
// ENABLE_SYSTICK systick interrupt, interrupt every 1ms
void SYSTICK_Interrupt_Init(void){
	CLR1B(SysTick->CTRL,SYS_EN);   //Disable SysTick timer
	SysTick->LOAD = 16000-1;  // generate periodic timer ticks every 1mS
	SysTick->VAL=0; //clear STCURRENT and COUNT flag
	ST1B(SysTick->CTRL,CLK_SRC); //use system clcok
	ST1B(SysTick->CTRL,INTEN); //ENABLE_SYSTICK systick interrupt
	ST1B(SysTick->CTRL,SYS_EN); //ENABLE_SYSTICK systick
	__enable_irq();
}
//clear systick timer and count flag
void SYSTICK_Clear_Counter(void){
	SysTick->VAL = 0 ; //clear systick timer and count flag
}
/* systick interrupt */
/*void SysTick_Handler(void){
	tick++; //increment every 1ms
}*/

