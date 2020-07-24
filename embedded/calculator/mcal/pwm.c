#include "pwm.h"
extern uint32_t sysclock;
void PWM_Init(uint8_t port, uint8_t pin, uint8_t mode, uint32_t pwmFreq, float duty)
{
	uint32_t load, cmp, clk, maxCntSize, newClk;
	uint8_t div = 0;
	/*system clock is 40 MHZ*/
	clk = sysclock; //40000000hz
	maxCntSize = 65536 - 1;
	load = (clk / pwmFreq);
	if (load > maxCntSize)
	{
		ST1B(SYSCTL->RCC, USEPWMDIV);
		do
		{
			STV3BI(SYSCTL->RCC, PWMDIV, div);/*divide the system clock by 2 so that the */
			newClk = clk / (2 << div++);
			load = (newClk / pwmFreq);//20000KHZ/pwmFreqKhz
		} while (load > maxCntSize);
	}
	switch (port) {
	case PORTA:
		switch (pin)
		{
		case M1PWM2:
			ST1B(SYSCTL->RCGCGPIO, PORTA);
			while (RD1B(SYSCTL->PRGPIO, PORTA) == 0);
			ST1B(GPIOA->DIR, PA6);
			CLR1B(GPIOA->AMSEL, PA6);
			ST1B(GPIOA->AFSEL, PA6);
			ST4B4MI(GPIOA->PCTL, PA6, PWM_MODE_MODULE1);
			ST1B(GPIOA->DEN, PA6);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD1);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD1) == 0) {};//wait until PWM is ready
			CLR1B(PWM1->_1_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM1->_1_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM1->ENUPD, ENUPD2, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM1->_1_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_1_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_1_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_1_GENA, ACTLOAD, PWMAHIGH);
				STV2BI(PWM1->_1_GENA, ACTCMPAD, PWMALOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM1->_1_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_1_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_1_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_1_GENA, ACTLOAD, PWMALOW);
				STV2BI(PWM1->_1_GENA, ACTCMPAD, PWMAHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM1->_1_CTL, MODE); //up/down COUNT MODE
				cmp = (load * duty) / 100;
				if (cmp > 0) STV(PWM1->_1_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_1_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_1_GENA, ACTCMPAU, PWMAHIGH);
				STV2BI(PWM1->_1_GENA, ACTCMPAD, PWMALOW);
				break;
			}
			ST1B(PWM1->_1_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM1->ENABLE, PWM2EN); //pass PWMB to PWMP'	
			break;
		case M1PWM3:
			ST1B(SYSCTL->RCGCGPIO, PORTA);
			while (RD1B(SYSCTL->PRGPIO, PORTA) == 0);
			ST1B(GPIOA->DIR, PA7);
			CLR1B(GPIOA->AMSEL, PA7);
			ST1B(GPIOA->AFSEL, PA7);
			ST4B4MI(GPIOA->PCTL, PA7, PWM_MODE_MODULE1);
			ST1B(GPIOA->DEN, PA7);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD1);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD1) == 0) {};//wait until PWM is ready
			CLR1B(PWM1->_1_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM1->_1_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM1->ENUPD, ENUPD3, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM1->_1_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_1_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_1_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_1_GENB, ACTLOAD, PWMBHIGH);
				STV2BI(PWM1->_1_GENB, ACTCMPBD, PWMBLOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM1->_1_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_1_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_1_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_1_GENB, ACTLOAD, PWMBLOW);
				STV2BI(PWM1->_1_GENB, ACTCMPBD, PWMBHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM1->_1_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM1->_1_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_1_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_1_GENB, ACTCMPBU, PWMBHIGH);
				STV2BI(PWM1->_1_GENB, ACTCMPBD, PWMBLOW);
			}
			ST1B(PWM1->_1_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM1->ENABLE, PWM3EN); //pass PWMB to PWMP'
			break;
		}
		break;
	case PORTB:
		switch (pin)
		{
		case M0PWM0://PB6, module 0, generator 0
			ST1B(SYSCTL->RCGCGPIO, PORTB);
			while (RD1B(SYSCTL->PRGPIO, PORTB) == 0);
			ST1B(GPIOB->DIR, PB6);
			CLR1B(GPIOB->AMSEL, PB6);
			ST1B(GPIOB->AFSEL, PB6);
			ST4B4MI(GPIOB->PCTL, PB6, PWM_MODE_MODULE0);
			ST1B(GPIOB->DEN, PB6);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
			CLR1B(PWM0->_0_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM0->_0_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM0->ENUPD, ENUPD0, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM0->_0_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_0_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_0_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_0_GENA, ACTLOAD, PWMAHIGH);
				STV2BI(PWM0->_0_GENA, ACTCMPAD, PWMALOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM0->_0_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_0_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_0_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_0_GENA, ACTLOAD, PWMALOW);
				STV2BI(PWM0->_0_GENA, ACTCMPAD, PWMAHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM0->_0_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM0->_0_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_0_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_0_GENA, ACTCMPAU, PWMAHIGH);
				STV2BI(PWM0->_0_GENA, ACTCMPAD, PWMALOW);
				break;
			}
			ST1B(PWM0->_0_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM0->ENABLE, PWM0EN); //pass PWMB to PWMP'
			break;
		case M0PWM1:
			ST1B(SYSCTL->RCGCGPIO, PORTB);
			while (RD1B(SYSCTL->PRGPIO, PORTB) == 0);
			ST1B(GPIOB->DIR, PB7);
			CLR1B(GPIOB->AMSEL, PB7);
			ST1B(GPIOB->AFSEL, PB7);
			ST4B4MI(GPIOB->PCTL, PB7, PWM_MODE_MODULE0);
			ST1B(GPIOB->DEN, PB7);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
			CLR1B(PWM0->_0_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM0->_0_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM0->ENUPD, ENUPD1, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM0->_0_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_0_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_0_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_0_GENB, ACTLOAD, PWMBHIGH);
				STV2BI(PWM0->_0_GENB, ACTCMPBD, PWMBLOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM0->_0_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_0_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_0_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_0_GENB, ACTLOAD, PWMBLOW);
				STV2BI(PWM0->_0_GENB, ACTCMPBD, PWMBHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM0->_0_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM0->_0_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_0_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_0_GENB, ACTCMPBU, PWMBHIGH);
				STV2BI(PWM0->_0_GENB, ACTCMPBD, PWMBLOW);
			}
			ST1B(PWM0->_0_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM0->ENABLE, PWM1EN); //pass PWMB to PWMP'
			break;
		case M0PWM2:
			ST1B(SYSCTL->RCGCGPIO, PORTB);
			while (RD1B(SYSCTL->PRGPIO, PORTB) == 0);
			ST1B(GPIOB->DIR, PB4);
			CLR1B(GPIOB->AMSEL, PB4);
			ST1B(GPIOB->AFSEL, PB4);
			ST4B4MI(GPIOB->PCTL, PB4, PWM_MODE_MODULE0);
			ST1B(GPIOB->DEN, PB4);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
			CLR1B(PWM0->_1_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM0->_1_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM0->ENUPD, ENUPD2, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM0->_1_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_1_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_1_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_1_GENA, ACTLOAD, PWMAHIGH);
				STV2BI(PWM0->_1_GENA, ACTCMPAD, PWMALOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM0->_1_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_1_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_1_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_1_GENA, ACTLOAD, PWMALOW);
				STV2BI(PWM0->_1_GENA, ACTCMPAD, PWMAHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM0->_1_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM0->_1_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_1_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_1_GENA, ACTCMPAU, PWMAHIGH);
				STV2BI(PWM0->_1_GENA, ACTCMPAD, PWMALOW);
				break;
			}
			ST1B(PWM0->_1_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM0->ENABLE, PWM2EN); //pass PWMB to PWMP'
			break;
		case M0PWM3:
			ST1B(SYSCTL->RCGCGPIO, PORTB);
			while (RD1B(SYSCTL->PRGPIO, PORTB) == 0);
			ST1B(GPIOB->DIR, PB5);
			CLR1B(GPIOB->AMSEL, PB5);
			ST1B(GPIOB->AFSEL, PB5);
			ST4B4MI(GPIOB->PCTL, PB5, PWM_MODE_MODULE0);
			ST1B(GPIOB->DEN, PB5);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
			CLR1B(PWM0->_1_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM0->_1_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM0->ENUPD, ENUPD3, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM0->_1_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_1_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_1_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_1_GENB, ACTLOAD, PWMBHIGH);
				STV2BI(PWM0->_1_GENB, ACTCMPBD, PWMBLOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM0->_1_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_1_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_1_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_1_GENB, ACTLOAD, PWMBLOW);
				STV2BI(PWM0->_1_GENB, ACTCMPBD, PWMBHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM0->_1_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM0->_1_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_1_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_1_GENB, ACTCMPBU, PWMBHIGH);
				STV2BI(PWM0->_1_GENB, ACTCMPBD, PWMBLOW);
			}
			ST1B(PWM0->_1_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM0->ENABLE, PWM3EN); //pass PWMB to PWMP'
			break;
		}

		break;
	case PORTC:
		switch (pin)
		{
		case M0PWM6:
			ST1B(SYSCTL->RCGCGPIO, PORTC);
			while (RD1B(SYSCTL->PRGPIO, PORTC) == 0);
			ST1B(GPIOC->DIR, PC4);
			CLR1B(GPIOC->AMSEL, PC4);
			ST1B(GPIOC->AFSEL, PC4);
			ST4B4MI(GPIOC->PCTL, PC4, PWM_MODE_MODULE0);
			ST1B(GPIOC->DEN, PC4);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
			CLR1B(PWM0->_3_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM0->_3_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM0->ENUPD, ENUPD6, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENA, ACTLOAD, PWMAHIGH);
				STV2BI(PWM0->_3_GENA, ACTCMPAD, PWMALOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENA, ACTLOAD, PWMALOW);
				STV2BI(PWM0->_3_GENA, ACTCMPAD, PWMAHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM0->_3_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENA, ACTCMPAU, PWMAHIGH);
				STV2BI(PWM0->_3_GENA, ACTCMPAD, PWMALOW);
				break;
			}
			ST1B(PWM0->_3_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM0->ENABLE, PWM6EN); //pass PWMB to PWMP'
			break;
		case M0PWM7:
			ST1B(SYSCTL->RCGCGPIO, PORTC);
			while (RD1B(SYSCTL->PRGPIO, PORTC) == 0);
			ST1B(GPIOC->DIR, PC5);
			CLR1B(GPIOC->AMSEL, PC5);
			ST1B(GPIOC->AFSEL, PC5);
			ST4B4MI(GPIOC->PCTL, PC5, PWM_MODE_MODULE0);
			ST1B(GPIOC->DEN, PC5);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
			CLR1B(PWM0->_3_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM0->_3_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM0->ENUPD, ENUPD7, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENB, ACTLOAD, PWMBHIGH);
				STV2BI(PWM0->_3_GENB, ACTCMPBD, PWMBLOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENB, ACTLOAD, PWMBLOW);
				STV2BI(PWM0->_3_GENB, ACTCMPBD, PWMBHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM0->_3_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENB, ACTCMPBU, PWMBHIGH);
				STV2BI(PWM0->_3_GENB, ACTCMPBD, PWMBLOW);
			}
			ST1B(PWM0->_3_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM0->ENABLE, PWM7EN); //pass PWMB to PWMP'
			break;
		}
		break;
	case PORTD:
		switch (pin)
		{
		case M0PWM6:
			ST1B(SYSCTL->RCGCGPIO, PORTD);
			while (RD1B(SYSCTL->PRGPIO, PORTD) == 0);
			ST1B(GPIOD->DIR, PD0);
			CLR1B(GPIOD->AMSEL, PD0);
			ST1B(GPIOD->AFSEL, PD0);
			ST4B4MI(GPIOD->PCTL, PD0, PWM_MODE_MODULE0);
			ST1B(GPIOD->DEN, PD0);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
			CLR1B(PWM0->_3_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM0->_3_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM0->ENUPD, ENUPD6, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENA, ACTLOAD, PWMAHIGH);
				STV2BI(PWM0->_3_GENA, ACTCMPAD, PWMALOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENA, ACTLOAD, PWMALOW);
				STV2BI(PWM0->_3_GENA, ACTCMPAD, PWMAHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM0->_3_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENA, ACTCMPAU, PWMAHIGH);
				STV2BI(PWM0->_3_GENA, ACTCMPAD, PWMALOW);
				break;
			}
			ST1B(PWM0->_3_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM0->ENABLE, PWM6EN); //pass PWMB to PWMP'
			break;
		case M0PWM7:
			ST1B(SYSCTL->RCGCGPIO, PORTD);
			while (RD1B(SYSCTL->PRGPIO, PORTD) == 0);
			ST1B(GPIOD->DIR, PD1);
			CLR1B(GPIOD->AMSEL, PD1);
			ST1B(GPIOD->AFSEL, PD1);
			ST4B4MI(GPIOD->PCTL, PD1, PWM_MODE_MODULE0);
			ST1B(GPIOD->DEN, PD1);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
			CLR1B(PWM0->_3_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM0->_3_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM0->ENUPD, ENUPD7, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENB, ACTLOAD, PWMBHIGH);
				STV2BI(PWM0->_3_GENB, ACTCMPBD, PWMBLOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENB, ACTLOAD, PWMBLOW);
				STV2BI(PWM0->_3_GENB, ACTCMPBD, PWMBHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM0->_3_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_3_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_3_GENB, ACTCMPBU, PWMBHIGH);
				STV2BI(PWM0->_3_GENB, ACTCMPBD, PWMBLOW);
			}
			ST1B(PWM0->_3_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM0->ENABLE, PWM7EN); //pass PWMB to PWMP'
			break;
		case M1PWM0:
			ST1B(SYSCTL->RCGCGPIO, PORTD);
			while (RD1B(SYSCTL->PRGPIO, PORTD) == 0);
			ST1B(GPIOD->DIR, PD0);
			CLR1B(GPIOD->AMSEL, PD0);
			ST1B(GPIOD->AFSEL, PD0);
			ST4B4MI(GPIOD->PCTL, PD0, PWM_MODE_MODULE1);
			ST1B(GPIOD->DEN, PD0);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD1);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD1) == 0) {};//wait until PWM is ready
			CLR1B(PWM1->_0_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM1->_0_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM1->ENUPD, ENUPD0, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM1->_0_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_0_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_0_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_0_GENA, ACTLOAD, PWMAHIGH);
				STV2BI(PWM1->_0_GENA, ACTCMPAD, PWMALOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM1->_0_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_0_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_0_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_0_GENA, ACTLOAD, PWMALOW);
				STV2BI(PWM1->_0_GENA, ACTCMPAD, PWMAHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM1->_0_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM1->_0_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_0_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_0_GENA, ACTCMPAU, PWMAHIGH);
				STV2BI(PWM1->_0_GENA, ACTCMPAD, PWMALOW);
				break;
			}
			ST1B(PWM1->_0_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM1->ENABLE, PWM0EN); //pass PWMB to PWMP'
			break;
		case M1PWM1:
			ST1B(SYSCTL->RCGCGPIO, PORTD);
			while (RD1B(SYSCTL->PRGPIO, PORTD) == 0);
			ST1B(GPIOD->DIR, PD1);
			CLR1B(GPIOD->AMSEL, PD1);
			ST1B(GPIOD->AFSEL, PD1);
			ST4B4MI(GPIOD->PCTL, PD1, PWM_MODE_MODULE1);
			ST1B(GPIOD->DEN, PD1);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD1);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD1) == 0) {};//wait until PWM is ready
			CLR1B(PWM1->_0_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM1->_0_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM1->ENUPD, ENUPD0, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM1->_0_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_0_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_0_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_0_GENB, ACTLOAD, PWMBHIGH);
				STV2BI(PWM1->_0_GENB, ACTCMPBD, PWMBLOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM1->_0_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_0_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_0_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_0_GENB, ACTLOAD, PWMBLOW);
				STV2BI(PWM1->_0_GENB, ACTCMPBD, PWMBHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM1->_0_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM1->_0_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_0_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_0_GENB, ACTCMPBU, PWMBHIGH);
				STV2BI(PWM1->_0_GENB, ACTCMPBD, PWMBLOW);
			}
			ST1B(PWM1->_0_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM1->ENABLE, PWM1EN); //pass PWMB to PWMP'
			break;
		}
		break;
	case PORTE:
		switch (pin)
		{
		case M0PWM4:
			ST1B(SYSCTL->RCGCGPIO, PORTE);
			while (RD1B(SYSCTL->PRGPIO, PORTE) == 0);
			ST1B(GPIOE->DIR, PE4);
			CLR1B(GPIOE->AMSEL, PE4);
			ST1B(GPIOE->AFSEL, PE4);
			ST4B4MI(GPIOE->PCTL, PE4, PWM_MODE_MODULE0);
			ST1B(GPIOE->DEN, PE4);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
			CLR1B(PWM0->_2_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM0->_2_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM0->ENUPD, ENUPD4, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM0->_2_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_2_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_2_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_2_GENA, ACTLOAD, PWMAHIGH);
				STV2BI(PWM0->_2_GENA, ACTCMPAD, PWMALOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM0->_2_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_2_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_2_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_2_GENA, ACTLOAD, PWMALOW);
				STV2BI(PWM0->_2_GENA, ACTCMPAD, PWMAHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM0->_2_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM0->_2_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_2_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM0->_2_GENA, ACTCMPAU, PWMAHIGH);
				STV2BI(PWM0->_2_GENA, ACTCMPAD, PWMALOW);
				break;
			}
			ST1B(PWM0->_2_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM0->ENABLE, PWM4EN); //pass PWMB to PWMP'
			break;
		case M0PWM5:
			ST1B(SYSCTL->RCGCGPIO, PORTE);
			while (RD1B(SYSCTL->PRGPIO, PORTE) == 0);
			ST1B(GPIOE->DIR, PB5);
			CLR1B(GPIOE->AMSEL, PB5);
			ST1B(GPIOE->AFSEL, PB5);
			ST4B4MI(GPIOE->PCTL, PB5, PWM_MODE_MODULE0);
			ST1B(GPIOE->DEN, PB5);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
			CLR1B(PWM0->_2_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM0->_2_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM0->ENUPD, ENUPD5, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM0->_2_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_2_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_2_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_2_GENB, ACTLOAD, PWMBHIGH);
				STV2BI(PWM0->_2_GENB, ACTCMPBD, PWMBLOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM0->_2_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM0->_2_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_2_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_2_GENB, ACTLOAD, PWMBLOW);
				STV2BI(PWM0->_2_GENB, ACTCMPBD, PWMBHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM0->_2_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM0->_2_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM0->_2_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM0->_2_GENB, ACTCMPBU, PWMBHIGH);
				STV2BI(PWM0->_2_GENB, ACTCMPBD, PWMBLOW);
			}
			ST1B(PWM0->_2_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM0->ENABLE, PWM5EN); //pass PWMB to PWMP'
			break;
		}
		break;
	case PORTF:
		switch (pin) {
		case M1PWM4:
			ST1B(SYSCTL->RCGCGPIO, PORTF);
			while (RD1B(SYSCTL->PRGPIO, PORTF) == 0);
			GPIOF->LOCK = UNLOCK;
			ST1B(GPIOF->CR, PF0);
			ST1B(GPIOF->DIR, PF0);
			CLR1B(GPIOF->AMSEL, PF0);
			ST1B(GPIOF->AFSEL, PF0);
			ST4B4MI(GPIOF->PCTL, PF0, PWM_MODE_MODULE1);
			ST1B(GPIOF->DEN, PF0);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD1);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD1) == 0) {};//wait until PWM is ready
			CLR1B(PWM1->_2_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM1->_2_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM1->ENUPD, ENUPD4, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM1->_2_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_2_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_2_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_2_GENA, ACTLOAD, PWMAHIGH);
				STV2BI(PWM1->_2_GENA, ACTCMPAD, PWMALOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM1->_2_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_2_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_2_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_2_GENA, ACTLOAD, PWMALOW);
				STV2BI(PWM1->_2_GENA, ACTCMPAD, PWMAHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM1->_2_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM1->_2_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_2_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_2_GENA, ACTCMPAU, PWMAHIGH);
				STV2BI(PWM1->_2_GENA, ACTCMPAD, PWMALOW);
				break;
			}
			ST1B(PWM1->_2_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM1->ENABLE, PWM4EN); //pass PWMB to PWMP'
			break;
		case M1PWM5://module 1, generator 5/2 = 2 which is generator 2
			ST1B(SYSCTL->RCGCGPIO, PORTF);
			while (RD1B(SYSCTL->PRGPIO, PORTF) == 0);
			ST1B(GPIOF->DIR, PF1);
			CLR1B(GPIOF->AMSEL, PF1);
			ST1B(GPIOF->AFSEL, PF1);
			ST4B4MI(GPIOF->PCTL, PF1, PWM_MODE_MODULE1);
			ST1B(GPIOF->DEN, PF1);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD1);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD1) == 0) {};//wait until PWM is ready
			CLR1B(PWM1->_2_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM1->_2_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM1->ENUPD, ENUPD5, LOCALLY_SYNCH);/*any updates happens when timer resets
			//	or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM1->_2_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_2_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_2_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_2_GENB, ACTLOAD, PWMBHIGH);
				STV2BI(PWM1->_2_GENB, ACTCMPBD, PWMBLOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM1->_2_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_2_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_2_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_2_GENB, ACTLOAD, PWMBLOW);
				STV2BI(PWM1->_2_GENB, ACTCMPBD, PWMBHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM1->_2_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM1->_2_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_2_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_2_GENB, ACTCMPBU, PWMBHIGH);
				STV2BI(PWM1->_2_GENB, ACTCMPBD, PWMBLOW);
				break;
			}
			ST1B(PWM1->SYNC, SYNC2); //reset genrator 0 counter
			ST1B(PWM1->_2_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM1->CTL, 2);
			ST1B(PWM1->ENABLE, PWM5EN); //pass PWMB to PWMP'
			break;
		case M1PWM6:
			ST1B(SYSCTL->RCGCGPIO, PORTF);
			while (RD1B(SYSCTL->PRGPIO, PORTF) == 0);
			ST1B(GPIOF->DIR, PF2);
			CLR1B(GPIOF->AMSEL, PF2);
			ST1B(GPIOF->AFSEL, PF2);
			ST4B4MI(GPIOF->PCTL, PF2, PWM_MODE_MODULE1);
			ST1B(GPIOF->DEN, PF2);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD1);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD1) == 0) {};//wait until PWM is ready
			CLR1B(PWM1->_3_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM1->_3_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM1->ENUPD, ENUPD6, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM1->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_3_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_3_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_3_GENA, ACTLOAD, PWMAHIGH);
				STV2BI(PWM1->_3_GENA, ACTCMPAD, PWMALOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM1->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_3_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_3_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_3_GENA, ACTLOAD, PWMALOW);
				STV2BI(PWM1->_3_GENA, ACTCMPAD, PWMAHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM1->_3_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM1->_3_CMPA, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_3_CMPA, cmp);//duty cycle 50%
				STV2BI(PWM1->_3_GENA, ACTCMPAU, PWMAHIGH);
				STV2BI(PWM1->_3_GENA, ACTCMPAD, PWMALOW);
				break;
			}
			ST1B(PWM1->_3_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM1->ENABLE, PWM6EN); //pass PWMB to PWMP'	
			break;
		case M1PWM7:
			ST1B(SYSCTL->RCGCGPIO, PORTF);
			while (RD1B(SYSCTL->PRGPIO, PORTF) == 0);
			ST1B(GPIOF->DIR, PF3);
			CLR1B(GPIOF->AMSEL, PF3);
			ST1B(GPIOF->AFSEL, PF3);
			ST4B4MI(GPIOF->PCTL, PF3, PWM_MODE_MODULE1);
			ST1B(GPIOF->DEN, PF3);
			ST1B(SYSCTL->RCGCPWM, PWM_MOD1);
			while (RD1B(SYSCTL->PRPWM, PWM_MOD1) == 0) {};//wait until PWM is ready
			CLR1B(PWM1->_3_CTL, ENGEN); //disable PWM generator 2 , stop counter 
			cmp = (load * DTYOFCNTDN(duty));
			STV(PWM1->_3_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
			STV2BI(PWM1->ENUPD, ENUPD7, LOCALLY_SYNCH);/*any updates happens when timer resets
				or at the end of pwm cycle*/
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				CLR1B(PWM1->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_3_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_3_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_3_GENB, ACTLOAD, PWMBHIGH);
				STV2BI(PWM1->_3_GENB, ACTCMPBD, PWMBLOW);
				break;
			case RIGHT_ALIGN_MODE:
				CLR1B(PWM1->_3_CTL, MODE); //DOWN COUNT MODE
				if (cmp > 0) STV(PWM1->_3_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_3_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_3_GENB, ACTLOAD, PWMBLOW);
				STV2BI(PWM1->_3_GENB, ACTCMPBD, PWMBHIGH);
				break;
			case CENTER_ALIGN_MODE:
				ST1B(PWM1->_3_CTL, MODE); //up/down COUNT MODE
				cmp = load * DTYOFCNTUP(duty);
				if (cmp > 0) STV(PWM1->_3_CMPB, cmp - 1);//duty cycle 50%
				else if (cmp == 0)STV(PWM1->_3_CMPB, cmp);//duty cycle 50%
				STV2BI(PWM1->_3_GENB, ACTCMPBU, PWMBHIGH);
				STV2BI(PWM1->_3_GENB, ACTCMPBD, PWMBLOW);
			}
			ST1B(PWM1->_3_CTL, ENGEN); //Enable PWM generator 2
			ST1B(PWM1->ENABLE, PWM7EN); //pass PWMB to PWMP'	
			break;

		}

	}
}

void PWM_CmpUpdate(uint8_t port, uint8_t pin, uint8_t mode, float duty) {
	uint32_t cmp;
	switch (port)
	{
	case PORTA:
		switch (pin)
		{
		case M1PWM2:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM1->_1_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_1_CMPA, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM1->_1_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_1_CMPA, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM1->_1_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM1->_1_CMPA, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M1PWM3:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM1->_1_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_1_CMPB, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM1->_1_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_1_CMPB, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM1->_1_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM1->_1_CMPB, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		}
		break;
	case PORTB:
		switch (pin)
		{
		case M0PWM0:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM0->_0_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_0_CMPA, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM0->_0_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_0_CMPA, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM0->_0_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM0->_0_CMPA, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M0PWM1:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM0->_0_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_0_CMPB, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM0->_0_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_0_CMPB, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM0->_0_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM0->_0_CMPB, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M0PWM2:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM0->_1_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_1_CMPA, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM0->_1_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_1_CMPA, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM0->_1_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM0->_1_CMPA, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M0PWM3:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM0->_1_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_1_CMPB, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM0->_1_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_1_CMPB, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM0->_1_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM0->_1_CMPB, cmp - 1);//duty cycle 50%
				break;
			}
		}
		break;
	case PORTC:
		switch (pin)
		{
		case M0PWM6:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M0PWM7:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		}
		break;
	case PORTD:
		switch (pin)
		{
		case M0PWM6:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM0->_3_CMPA, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M0PWM7:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM0->_3_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM0->_3_CMPB, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M1PWM0:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM1->_0_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_0_CMPA, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM1->_0_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_0_CMPA, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM1->_0_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM1->_0_CMPA, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M1PWM1:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM1->_0_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_0_CMPB, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM1->_0_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_0_CMPB, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM1->_0_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM1->_0_CMPB, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		}
		break;
	case PORTE:
		switch (pin)
		{
		case M0PWM4:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM0->_2_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_2_CMPA, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM0->_2_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_2_CMPA, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM0->_2_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM0->_2_CMPA, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M0PWM5:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM0->_2_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_2_CMPB, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM0->_2_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM0->_0_CMPB, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM0->_2_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM0->_2_CMPB, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		}
		break;
	case PORTF:
		switch (pin) {
		case M1PWM4:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM1->_2_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_2_CMPA, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM1->_2_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_2_CMPA, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM1->_2_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM1->_2_CMPA, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M1PWM5:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM1->_2_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_2_CMPB, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM1->_2_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_2_CMPB, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM1->_2_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM1->_2_CMPB, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M1PWM6:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM1->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_3_CMPA, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM1->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_3_CMPA, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM1->_3_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM1->_3_CMPA, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		case M1PWM7:
			switch (mode)
			{
			case LEFT_ALIGN_MODE:
				cmp = ((PWM1->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_3_CMPB, cmp - 1);//duty cycle 50%
				break;
			case RIGHT_ALIGN_MODE:
				cmp = ((PWM1->_3_LOAD + 1) * DTYOFCNTDN(duty));
				STV(PWM1->_3_CMPB, cmp - 1);//duty cycle 50%
				break;
			case CENTER_ALIGN_MODE:
				cmp = ((PWM1->_3_LOAD + 1) * DTYOFCNTUP(duty));
				STV(PWM1->_3_CMPB, cmp - 1);//duty cycle 50%
				break;
			}
			break;
		}
		break;
	}
}

void PWM_GenInit(uint8_t modGen, uint8_t modA, uint8_t modB,uint32_t pwmFreq, float dutA, float dutB )
{
	uint32_t load, clk, maxCntSize, newClk;
	uint16_t cmpA, cmpB;
	uint8_t div = 0;
	clk = sysclock; //40000000hz
	maxCntSize = 65536 - 1;
	load = (clk / pwmFreq);
	if (load > maxCntSize)
	{
		ST1B(SYSCTL->RCC, USEPWMDIV);
		do
		{
			STV3BI(SYSCTL->RCC, PWMDIV, div);/*divide the system clock by 2 so that the */
			newClk = clk / (2 << div++);
			load = (newClk / pwmFreq);//20000KHZ/pwmFreqKhz
		} while (load > maxCntSize);
	}
	switch (modGen)
	{
	case MOD0GEN0:
		ST1B(SYSCTL->RCGCGPIO, PORTB);
		while (RD1B(SYSCTL->PRGPIO, PORTB) == 0);
		ST2B(GPIOB->DIR, PB6, PB7);
		CLR2B(GPIOB->AMSEL, PB6, PB7);
		ST2B(GPIOB->AFSEL, PB6, PB7);
		ST4B4MI(GPIOB->PCTL, PB6, PWM_MODE_MODULE0);
		ST4B4MI(GPIOB->PCTL, PB7, PWM_MODE_MODULE0);
		ST2B(GPIOB->DEN, PB6, PB7);
		ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
		while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
		CLR1B(PWM0->_0_CTL, ENGEN); //disable PWM generator 2 , stop counter 
		cmpA = (load * DTYOFCNTDN(dutA));
		cmpB = (load * DTYOFCNTDN(dutB));
		STV(PWM0->_0_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
		ST1B(PWM0->CTL, GLOBALSYNC0);
		//STV2BI(PWM0->ENUPD, ENUPD0, GLOBALY_SYNCH);/*any updates happens when timer resets or at the end of pwm cycle*/
	  //STV2BI(PWM0->ENUPD, ENUPD1, GLOBALY_SYNCH);/*any updates happens when timer resets*/
 //    ST1B(PWM0->SYNC,SYNC0); //reset genrator 0 counter
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM0->_0_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_0_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM0->_0_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_0_GENA, ACTLOAD, PWMAHIGH);
			STV2BI(PWM0->_0_GENA, ACTCMPAD, PWMALOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM0->_0_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_0_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM0->_0_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_0_GENA, ACTLOAD, PWMALOW);
			STV2BI(PWM0->_0_GENA, ACTCMPAD, PWMAHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpA = load * DTYOFCNTUP(dutA);
			if (cmpA > 0) STV(PWM0->_0_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_0_CMPA, cmpA);//duty cycle 50%
			ST1B(PWM0->_0_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM0->_0_GENA, ACTCMPAU, PWMAHIGH);
			STV2BI(PWM0->_0_GENA, ACTCMPAD, PWMALOW);
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM0->_0_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_0_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM0->_0_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_0_GENB, ACTLOAD, PWMBHIGH);
			STV2BI(PWM0->_0_GENB, ACTCMPBD, PWMBLOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM0->_0_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_0_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM0->_0_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_0_GENB, ACTLOAD, PWMBLOW);
			STV2BI(PWM0->_0_GENB, ACTCMPBD, PWMBHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpB = load * DTYOFCNTUP(dutB);
			if (cmpB > 0) STV(PWM0->_0_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_0_CMPB, cmpB);//duty cycle 50%
			ST1B(PWM0->_0_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM0->_0_GENB, ACTCMPBU, PWMBHIGH);
			STV2BI(PWM0->_0_GENB, ACTCMPBD, PWMBLOW);
		}
		ST1B(PWM0->_0_CTL, ENGEN); //Enable PWM generator 2
		ST2B(PWM0->ENABLE, PWM0EN, PWM1EN); //pass PWMB to PWMP'			
		break;
	case MOD0GEN1:
		ST1B(SYSCTL->RCGCGPIO, PORTB);
		while (RD1B(SYSCTL->PRGPIO, PORTB) == 0);
		ST2B(GPIOB->DIR, PB4, PB5);
		CLR2B(GPIOB->AMSEL, PB4, PB5);
		ST2B(GPIOB->AFSEL, PB4, PB5);
		ST4B4MI(GPIOB->PCTL, PB4, PWM_MODE_MODULE0);
		ST4B4MI(GPIOB->PCTL, PB5, PWM_MODE_MODULE0);
		ST2B(GPIOB->DEN, PB4, PB5);
		ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
		while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
		CLR1B(PWM0->_1_CTL, ENGEN); //disable PWM generator 2 , stop counter 
		cmpA = (load * DTYOFCNTDN(dutA));
		cmpB = (load * DTYOFCNTDN(dutB));
		STV(PWM0->_1_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
		ST1B(PWM0->CTL, GLOBALSYNC1);
		//STV2BI(PWM0->ENUPD, ENUPD0, GLOBALY_SYNCH);/*any updates happens when timer resets or at the end of pwm cycle*/
	  //STV2BI(PWM0->ENUPD, ENUPD1, GLOBALY_SYNCH);/*any updates happens when timer resets*/
 //    ST1B(PWM0->SYNC,SYNC0); //reset genrator 0 counter
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM0->_1_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_1_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM0->_1_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_1_GENA, ACTLOAD, PWMAHIGH);
			STV2BI(PWM0->_1_GENA, ACTCMPAD, PWMALOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM0->_1_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_1_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM0->_1_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_1_GENA, ACTLOAD, PWMALOW);
			STV2BI(PWM0->_1_GENA, ACTCMPAD, PWMAHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpA = load * DTYOFCNTUP(dutA);
			if (cmpA > 0) STV(PWM0->_1_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_1_CMPA, cmpA);//duty cycle 50%
			ST1B(PWM0->_1_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM0->_1_GENA, ACTCMPAU, PWMAHIGH);
			STV2BI(PWM0->_1_GENA, ACTCMPAD, PWMALOW);
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM0->_1_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_1_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM0->_1_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_1_GENB, ACTLOAD, PWMBHIGH);
			STV2BI(PWM0->_1_GENB, ACTCMPBD, PWMBLOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM0->_1_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_1_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM0->_1_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_1_GENB, ACTLOAD, PWMBLOW);
			STV2BI(PWM0->_1_GENB, ACTCMPBD, PWMBHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpB = load * DTYOFCNTUP(dutB);
			if (cmpB > 0) STV(PWM0->_1_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_1_CMPB, cmpB);//duty cycle 50%
			ST1B(PWM0->_1_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM0->_1_GENB, ACTCMPBU, PWMBHIGH);
			STV2BI(PWM0->_1_GENB, ACTCMPBD, PWMBLOW);
		}
		ST1B(PWM0->_1_CTL, ENGEN); //Enable PWM generator 2
		ST2B(PWM0->ENABLE, PWM2EN, PWM3EN); //pass PWMB to PWMP'			
		break;
	case MOD0GEN2:
		ST1B(SYSCTL->RCGCGPIO, PORTE);
		while (RD1B(SYSCTL->PRGPIO, PORTE) == 0);
		ST2B(GPIOE->DIR, PE4, PE5);
		CLR2B(GPIOE->AMSEL, PE4, PE5);
		ST2B(GPIOE->AFSEL, PE4, PE5);
		ST4B4MI(GPIOE->PCTL, PE4, PWM_MODE_MODULE0);
		ST4B4MI(GPIOE->PCTL, PE5, PWM_MODE_MODULE0);
		ST2B(GPIOE->DEN, PE4, PE5);
		ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
		while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
		CLR1B(PWM0->_2_CTL, ENGEN); //disable PWM generator 2 , stop counter 
		cmpA = (load * DTYOFCNTDN(dutA));
		cmpB = (load * DTYOFCNTDN(dutB));
		STV(PWM0->_2_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
		ST1B(PWM0->CTL, GLOBALSYNC2);
		//STV2BI(PWM0->ENUPD, ENUPD0, GLOBALY_SYNCH);/*any updates happens when timer resets or at the end of pwm cycle*/
	  //STV2BI(PWM0->ENUPD, ENUPD1, GLOBALY_SYNCH);/*any updates happens when timer resets*/
 //    ST1B(PWM0->SYNC,SYNC0); //reset genrator 0 counter
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM0->_2_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_2_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM0->_2_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_2_GENA, ACTLOAD, PWMAHIGH);
			STV2BI(PWM0->_2_GENA, ACTCMPAD, PWMALOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM0->_2_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_2_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM0->_2_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_2_GENA, ACTLOAD, PWMALOW);
			STV2BI(PWM0->_2_GENA, ACTCMPAD, PWMAHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpA = load * DTYOFCNTUP(dutA);
			if (cmpA > 0) STV(PWM0->_2_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_2_CMPA, cmpA);//duty cycle 50%
			ST1B(PWM0->_2_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM0->_2_GENA, ACTCMPAU, PWMAHIGH);
			STV2BI(PWM0->_2_GENA, ACTCMPAD, PWMALOW);
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM0->_2_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_2_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM0->_2_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_2_GENB, ACTLOAD, PWMBHIGH);
			STV2BI(PWM0->_2_GENB, ACTCMPBD, PWMBLOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM0->_2_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_2_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM0->_2_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_2_GENB, ACTLOAD, PWMBLOW);
			STV2BI(PWM0->_2_GENB, ACTCMPBD, PWMBHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpB = load * DTYOFCNTUP(dutB);
			if (cmpB > 0) STV(PWM0->_2_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_2_CMPB, cmpB);//duty cycle 50%
			ST1B(PWM0->_2_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM0->_2_GENB, ACTCMPBU, PWMBHIGH);
			STV2BI(PWM0->_2_GENB, ACTCMPBD, PWMBLOW);
		}
		ST1B(PWM0->_2_CTL, ENGEN); //Enable PWM generator 2
		ST2B(PWM0->ENABLE, PWM4EN, PWM5EN); //pass PWMB to PWMP'			
		break;
	case MOD0GEN3:
		ST1B(SYSCTL->RCGCGPIO, PORTC);
		while (RD1B(SYSCTL->PRGPIO, PORTC) == 0);
		ST2B(GPIOC->DIR, PC4, PC5);
		CLR2B(GPIOC->AMSEL, PC4, PC5);
		ST2B(GPIOC->AFSEL, PC4, PC5);
		ST4B4MI(GPIOC->PCTL, PC4, PWM_MODE_MODULE0);
		ST4B4MI(GPIOC->PCTL, PC5, PWM_MODE_MODULE0);
		ST2B(GPIOC->DEN, PC4, PC5);
		ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
		while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
		CLR1B(PWM0->_3_CTL, ENGEN); //disable PWM generator 2 , stop counter 
		cmpA = (load * DTYOFCNTDN(dutA));
		cmpB = (load * DTYOFCNTDN(dutB));
		STV(PWM0->_3_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
		ST1B(PWM0->CTL, GLOBALSYNC3);
		//STV2BI(PWM0->ENUPD, ENUPD0, GLOBALY_SYNCH);/*any updates happens when timer resets or at the end of pwm cycle*/
	  //STV2BI(PWM0->ENUPD, ENUPD1, GLOBALY_SYNCH);/*any updates happens when timer resets*/
 //    ST1B(PWM0->SYNC,SYNC0); //reset genrator 0 counter
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM0->_3_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_3_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_3_GENA, ACTLOAD, PWMAHIGH);
			STV2BI(PWM0->_3_GENA, ACTCMPAD, PWMALOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM0->_3_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_3_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_3_GENA, ACTLOAD, PWMALOW);
			STV2BI(PWM0->_3_GENA, ACTCMPAD, PWMAHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpA = load * DTYOFCNTUP(dutA);
			if (cmpA > 0) STV(PWM0->_3_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM0->_3_CMPA, cmpA);//duty cycle 50%
			ST1B(PWM0->_3_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM0->_3_GENA, ACTCMPAU, PWMAHIGH);
			STV2BI(PWM0->_3_GENA, ACTCMPAD, PWMALOW);
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM0->_3_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_3_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_3_GENB, ACTLOAD, PWMBHIGH);
			STV2BI(PWM0->_3_GENB, ACTCMPBD, PWMBLOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM0->_3_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_3_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM0->_3_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM0->_3_GENB, ACTLOAD, PWMBLOW);
			STV2BI(PWM0->_3_GENB, ACTCMPBD, PWMBHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpB = load * DTYOFCNTUP(dutB);
			if (cmpB > 0) STV(PWM0->_3_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM0->_3_CMPB, cmpB);//duty cycle 50%
			ST1B(PWM0->_3_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM0->_3_GENB, ACTCMPBU, PWMBHIGH);
			STV2BI(PWM0->_3_GENB, ACTCMPBD, PWMBLOW);
		}
		ST1B(PWM0->_3_CTL, ENGEN); //Enable PWM generator 2
		ST2B(PWM0->ENABLE, PWM6EN, PWM7EN); //pass PWMB to PWMP'			
		break;
	case MOD1GEN0:
		ST1B(SYSCTL->RCGCGPIO, PORTD);
		while (RD1B(SYSCTL->PRGPIO, PORTD) == 0);
		ST2B(GPIOD->DIR, PD0, PD1);
		CLR2B(GPIOD->AMSEL, PD0, PD1);
		ST2B(GPIOD->AFSEL, PD0, PD1);
		ST4B4MI(GPIOD->PCTL, PD0, PWM_MODE_MODULE0);
		ST4B4MI(GPIOD->PCTL, PD1, PWM_MODE_MODULE0);
		ST2B(GPIOD->DEN, PD0, PD1);
		ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
		while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
		CLR1B(PWM1->_0_CTL, ENGEN); //disable PWM generator 2 , stop counter 
		cmpA = (load * DTYOFCNTDN(dutA));
		cmpB = (load * DTYOFCNTDN(dutB));
		STV(PWM1->_0_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
		ST1B(PWM1->CTL, GLOBALSYNC0);
		//STV2BI(PWM1->ENUPD, ENUPD0, GLOBALY_SYNCH);/*any updates happens when timer resets or at the end of pwm cycle*/
	  //STV2BI(PWM1->ENUPD, ENUPD1, GLOBALY_SYNCH);/*any updates happens when timer resets*/
 //    ST1B(PWM1->SYNC,SYNC0); //reset genrator 0 counter
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM1->_0_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_0_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM1->_0_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_0_GENA, ACTLOAD, PWMAHIGH);
			STV2BI(PWM1->_0_GENA, ACTCMPAD, PWMALOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM1->_0_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_0_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM1->_0_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_0_GENA, ACTLOAD, PWMALOW);
			STV2BI(PWM1->_0_GENA, ACTCMPAD, PWMAHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpA = load * DTYOFCNTUP(dutA);
			if (cmpA > 0) STV(PWM1->_0_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_0_CMPA, cmpA);//duty cycle 50%
			ST1B(PWM1->_0_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM1->_0_GENA, ACTCMPAU, PWMAHIGH);
			STV2BI(PWM1->_0_GENA, ACTCMPAD, PWMALOW);
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM1->_0_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_0_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM1->_0_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_0_GENB, ACTLOAD, PWMBHIGH);
			STV2BI(PWM1->_0_GENB, ACTCMPBD, PWMBLOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM1->_0_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_0_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM1->_0_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_0_GENB, ACTLOAD, PWMBLOW);
			STV2BI(PWM1->_0_GENB, ACTCMPBD, PWMBHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpB = load * DTYOFCNTUP(dutB);
			if (cmpB > 0) STV(PWM1->_0_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_0_CMPB, cmpB);//duty cycle 50%
			ST1B(PWM1->_0_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM1->_0_GENB, ACTCMPBU, PWMBHIGH);
			STV2BI(PWM1->_0_GENB, ACTCMPBD, PWMBLOW);
		}
		ST1B(PWM1->_0_CTL, ENGEN); //Enable PWM generator 2
		ST2B(PWM1->ENABLE, PWM0EN, PWM1EN); //pass PWMB to PWMP'			
		break;
	case MOD1GEN1:
		ST1B(SYSCTL->RCGCGPIO, PORTA);
		while (RD1B(SYSCTL->PRGPIO, PORTA) == 0);
		ST2B(GPIOA->DIR, PA6, PA7);
		CLR2B(GPIOA->AMSEL, PA6, PA7);
		ST2B(GPIOA->AFSEL, PA6, PA7);
		ST4B4MI(GPIOA->PCTL, PA6, PWM_MODE_MODULE0);
		ST4B4MI(GPIOA->PCTL, PA7, PWM_MODE_MODULE0);
		ST2B(GPIOA->DEN, PA6, PA7);
		ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
		while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
		CLR1B(PWM1->_1_CTL, ENGEN); //disable PWM generator 2 , stop counter 
		cmpA = (load * DTYOFCNTDN(dutA));
		cmpB = (load * DTYOFCNTDN(dutB));
		STV(PWM1->_1_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
		ST1B(PWM1->CTL, GLOBALSYNC1);
		//STV2BI(PWM1->ENUPD, ENUPA6, GLOBALY_SYNCH);/*any updates happens when timer resets or at the end of pwm cycle*/
	  //STV2BI(PWM1->ENUPD, ENUPA7, GLOBALY_SYNCH);/*any updates happens when timer resets*/
 //    ST1B(PWM1->SYNC,SYNC0); //reset genrator 0 counter
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM1->_1_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_1_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM1->_1_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_1_GENA, ACTLOAD, PWMAHIGH);
			STV2BI(PWM1->_1_GENA, ACTCMPAD, PWMALOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM1->_1_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_1_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM1->_1_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_1_GENA, ACTLOAD, PWMALOW);
			STV2BI(PWM1->_1_GENA, ACTCMPAD, PWMAHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpA = load * DTYOFCNTUP(dutA);
			if (cmpA > 0) STV(PWM1->_1_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_1_CMPA, cmpA);//duty cycle 50%
			ST1B(PWM1->_1_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM1->_1_GENA, ACTCMPAU, PWMAHIGH);
			STV2BI(PWM1->_1_GENA, ACTCMPAD, PWMALOW);
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM1->_1_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_1_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM1->_1_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_1_GENB, ACTLOAD, PWMBHIGH);
			STV2BI(PWM1->_1_GENB, ACTCMPBD, PWMBLOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM1->_1_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_1_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM1->_1_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_1_GENB, ACTLOAD, PWMBLOW);
			STV2BI(PWM1->_1_GENB, ACTCMPBD, PWMBHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpB = load * DTYOFCNTUP(dutB);
			if (cmpB > 0) STV(PWM1->_1_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_1_CMPB, cmpB);//duty cycle 50%
			ST1B(PWM1->_1_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM1->_1_GENB, ACTCMPBU, PWMBHIGH);
			STV2BI(PWM1->_1_GENB, ACTCMPBD, PWMBLOW);
		}
		ST1B(PWM1->_1_CTL, ENGEN); //Enable PWM generator 2
		ST2B(PWM1->ENABLE, PWM2EN, PWM3EN); //pass PWMB to PWMP'			
		break;
	case MOD1GEN2:
		ST1B(SYSCTL->RCGCGPIO, PORTF);
		while (RD1B(SYSCTL->PRGPIO, PORTF) == 0);
		GPIOF->LOCK = UNLOCK;
		ST1B(GPIOF->CR, PF0);
		ST2B(GPIOF->DIR, PF0, PF1);
		CLR2B(GPIOF->AMSEL, PF0, PF1);
		ST2B(GPIOF->AFSEL, PF0, PF1);
		ST4B4MI(GPIOF->PCTL, PF0, PWM_MODE_MODULE0);
		ST4B4MI(GPIOF->PCTL, PF1, PWM_MODE_MODULE0);
		ST2B(GPIOF->DEN, PF0, PF1);
		ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
		while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
		CLR1B(PWM1->_2_CTL, ENGEN); //disable PWM generator 2 , stop counter 
		cmpA = (load * DTYOFCNTDN(dutA));
		cmpB = (load * DTYOFCNTDN(dutB));
		STV(PWM1->_2_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
		ST1B(PWM1->CTL, GLOBALSYNC2);
		//STV2BI(PWM1->ENUPD, ENUPF0, GLOBALY_SYNCH);/*any updates happens when timer resets or at the end of pwm cycle*/
	  //STV2BI(PWM1->ENUPD, ENUPF1, GLOBALY_SYNCH);/*any updates happens when timer resets*/
 //    ST1B(PWM1->SYNC,SYNC0); //reset genrator 0 counter
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM1->_2_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_2_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM1->_2_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_2_GENA, ACTLOAD, PWMAHIGH);
			STV2BI(PWM1->_2_GENA, ACTCMPAD, PWMALOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM1->_2_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_2_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM1->_2_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_2_GENA, ACTLOAD, PWMALOW);
			STV2BI(PWM1->_2_GENA, ACTCMPAD, PWMAHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpA = load * DTYOFCNTUP(dutA);
			if (cmpA > 0) STV(PWM1->_2_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_2_CMPA, cmpA);//duty cycle 50%
			ST1B(PWM1->_2_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM1->_2_GENA, ACTCMPAU, PWMAHIGH);
			STV2BI(PWM1->_2_GENA, ACTCMPAD, PWMALOW);
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM1->_2_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_2_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM1->_2_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_2_GENB, ACTLOAD, PWMBHIGH);
			STV2BI(PWM1->_2_GENB, ACTCMPBD, PWMBLOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM1->_2_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_2_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM1->_2_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_2_GENB, ACTLOAD, PWMBLOW);
			STV2BI(PWM1->_2_GENB, ACTCMPBD, PWMBHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpB = load * DTYOFCNTUP(dutB);
			if (cmpB > 0) STV(PWM1->_2_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_2_CMPB, cmpB);//duty cycle 50%
			ST1B(PWM1->_2_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM1->_2_GENB, ACTCMPBU, PWMBHIGH);
			STV2BI(PWM1->_2_GENB, ACTCMPBD, PWMBLOW);
		}
		ST1B(PWM1->_2_CTL, ENGEN); //Enable PWM generator 2
		ST2B(PWM1->ENABLE, PWM4EN, PWM5EN); //pass PWMB to PWMP'			
		break;
	case MOD1GEN3:
		ST1B(SYSCTL->RCGCGPIO, PORTF);
		while (RD1B(SYSCTL->PRGPIO, PORTF) == 0);
		ST2B(GPIOF->DIR, PF2, PF3);
		CLR2B(GPIOF->AMSEL, PF2, PF3);
		ST2B(GPIOF->AFSEL, PF2, PF3);
		ST4B4MI(GPIOF->PCTL, PF2, PWM_MODE_MODULE0);
		ST4B4MI(GPIOF->PCTL, PF3, PWM_MODE_MODULE0);
		ST2B(GPIOF->DEN, PF2, PF3);
		ST1B(SYSCTL->RCGCPWM, PWM_MOD0);
		while (RD1B(SYSCTL->PRPWM, PWM_MOD0) == 0) {};//wait until PWM is ready
		CLR1B(PWM1->_3_CTL, ENGEN); //disable PWM generator 2 , stop counter 
		cmpA = (load * DTYOFCNTDN(dutA));
		cmpB = (load * DTYOFCNTDN(dutB));
		STV(PWM1->_3_LOAD, load - 1);//5KHZ PWM from 20MHZ system clock
		ST1B(PWM1->CTL, GLOBALSYNC3);
		//STV2BI(PWM1->ENUPD, ENUPF2, GLOBALY_SYNCH);/*any updates happens when timer resets or at the end of pwm cycle*/
	  //STV2BI(PWM1->ENUPD, ENUPF3, GLOBALY_SYNCH);/*any updates happens when timer resets*/
 //    ST1B(PWM1->SYNC,SYNC0); //reset genrator 0 counter
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM1->_3_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_3_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM1->_3_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_3_GENA, ACTLOAD, PWMAHIGH);
			STV2BI(PWM1->_3_GENA, ACTCMPAD, PWMALOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpA > 0) STV(PWM1->_3_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_3_CMPA, cmpA);//duty cycle 50%
			CLR1B(PWM1->_3_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_3_GENA, ACTLOAD, PWMALOW);
			STV2BI(PWM1->_3_GENA, ACTCMPAD, PWMAHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpA = load * DTYOFCNTUP(dutA);
			if (cmpA > 0) STV(PWM1->_3_CMPA, cmpA - 1);//duty cycle 50%
			else if (cmpA == 0)STV(PWM1->_3_CMPA, cmpA);//duty cycle 50%
			ST1B(PWM1->_3_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM1->_3_GENA, ACTCMPAU, PWMAHIGH);
			STV2BI(PWM1->_3_GENA, ACTCMPAD, PWMALOW);
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM1->_3_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_3_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM1->_3_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_3_GENB, ACTLOAD, PWMBHIGH);
			STV2BI(PWM1->_3_GENB, ACTCMPBD, PWMBLOW);
			break;
		case RIGHT_ALIGN_MODE:
			if (cmpB > 0) STV(PWM1->_3_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_3_CMPB, cmpB);//duty cycle 50%
			CLR1B(PWM1->_3_CTL, MODE); //DOWN COUNT MODE
			STV2BI(PWM1->_3_GENB, ACTLOAD, PWMBLOW);
			STV2BI(PWM1->_3_GENB, ACTCMPBD, PWMBHIGH);
			break;
		case CENTER_ALIGN_MODE:
			cmpB = load * DTYOFCNTUP(dutB);
			if (cmpB > 0) STV(PWM1->_3_CMPB, cmpB - 1);//duty cycle 50%
			else if (cmpB == 0)STV(PWM1->_3_CMPB, cmpB);//duty cycle 50%
			ST1B(PWM1->_3_CTL, MODE); //up/down COUNT MODE
			STV2BI(PWM1->_3_GENB, ACTCMPBU, PWMBHIGH);
			STV2BI(PWM1->_3_GENB, ACTCMPBD, PWMBLOW);
		}
		ST1B(PWM1->_3_CTL, ENGEN); //Enable PWM generator 2
		ST2B(PWM1->ENABLE, PWM6EN, PWM7EN); //pass PWMB to PWMP'			
		break;
	}
}
void PWM_GenUpdate(uint8_t modGen, uint8_t modA, uint8_t modB, float dutA, float dutB)
{
	uint32_t cmpA, cmpB;
	switch (modGen)
	{
	case MOD0GEN0:
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			cmpA = ((PWM0->_0_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM0->_0_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpA = ((PWM0->_0_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM0->_0_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpA = ((PWM0->_0_LOAD + 1) * DTYOFCNTUP(dutA));
			STV(PWM0->_0_CMPA, cmpA - 1);//duty cycle 50%
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			cmpB = ((PWM0->_0_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM0->_0_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpB = ((PWM0->_0_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM0->_0_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpB = ((PWM0->_0_LOAD + 1) * DTYOFCNTUP(dutB));
			STV(PWM0->_0_CMPB, cmpB - 1);//duty cycle 50%
			break;
		}
		break;
	case MOD0GEN1:
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			cmpA = ((PWM0->_1_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM0->_1_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpA = ((PWM0->_1_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM0->_1_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpA = ((PWM0->_1_LOAD + 1) * DTYOFCNTUP(dutA));
			STV(PWM0->_1_CMPA, cmpA - 1);//duty cycle 50%
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			cmpB = ((PWM0->_1_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM0->_1_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpB = ((PWM0->_1_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM0->_1_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpB = ((PWM0->_1_LOAD + 1) * DTYOFCNTUP(dutB));
			STV(PWM0->_1_CMPB, cmpB - 1);//duty cycle 50%
			break;
		}
		break;
	case MOD0GEN2:
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			cmpA = ((PWM0->_2_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM0->_2_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpA = ((PWM0->_2_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM0->_2_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpA = ((PWM0->_2_LOAD + 1) * DTYOFCNTUP(dutA));
			STV(PWM0->_2_CMPA, cmpA - 1);//duty cycle 50%
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			cmpB = ((PWM0->_2_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM0->_2_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpB = ((PWM0->_2_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM0->_2_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpB = ((PWM0->_2_LOAD + 1) * DTYOFCNTUP(dutB));
			STV(PWM0->_2_CMPB, cmpB - 1);//duty cycle 50%
			break;
		}
		break;
	case MOD0GEN3:
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			cmpA = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM0->_3_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpA = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM0->_3_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpA = ((PWM0->_3_LOAD + 1) * DTYOFCNTUP(dutA));
			STV(PWM0->_3_CMPA, cmpA - 1);//duty cycle 50%
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			cmpB = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM0->_3_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpB = ((PWM0->_3_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM0->_3_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpB = ((PWM0->_3_LOAD + 1) * DTYOFCNTUP(dutB));
			STV(PWM0->_3_CMPB, cmpB - 1);//duty cycle 50%
			break;
		}
		break;
	case MOD1GEN0:
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			cmpA = ((PWM1->_0_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM1->_0_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpA = ((PWM1->_0_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM1->_0_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpA = ((PWM1->_0_LOAD + 1) * DTYOFCNTUP(dutA));
			STV(PWM1->_0_CMPA, cmpA - 1);//duty cycle 50%
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			cmpB = ((PWM1->_0_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM1->_0_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpB = ((PWM1->_0_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM1->_0_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpB = ((PWM1->_0_LOAD + 1) * DTYOFCNTUP(dutB));
			STV(PWM1->_0_CMPB, cmpB - 1);//duty cycle 50%
			break;
		}
		break;
	case MOD1GEN1:
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			cmpA = ((PWM1->_1_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM1->_1_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpA = ((PWM1->_1_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM1->_1_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpA = ((PWM1->_1_LOAD + 1) * DTYOFCNTUP(dutA));
			STV(PWM1->_1_CMPA, cmpA - 1);//duty cycle 50%
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			cmpB = ((PWM1->_1_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM1->_1_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpB = ((PWM1->_1_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM1->_1_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpB = ((PWM1->_1_LOAD + 1) * DTYOFCNTUP(dutB));
			STV(PWM1->_1_CMPB, cmpB - 1);//duty cycle 50%
			break;
		}
		break;
	case MOD1GEN2:
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			cmpA = ((PWM1->_2_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM1->_2_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpA = ((PWM1->_2_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM1->_2_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpA = ((PWM1->_2_LOAD + 1) * DTYOFCNTUP(dutA));
			STV(PWM1->_2_CMPA, cmpA - 1);//duty cycle 50%
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			cmpB = ((PWM1->_2_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM1->_2_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpB = ((PWM1->_2_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM1->_2_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpB = ((PWM1->_2_LOAD + 1) * DTYOFCNTUP(dutB));
			STV(PWM1->_2_CMPB, cmpB - 1);//duty cycle 50%
			break;
		}
		break;
	case MOD1GEN3:
		switch (modA)
		{
		case LEFT_ALIGN_MODE:
			cmpA = ((PWM1->_3_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM1->_3_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpA = ((PWM1->_3_LOAD + 1) * DTYOFCNTDN(dutA));
			STV(PWM1->_3_CMPA, cmpA - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpA = ((PWM1->_3_LOAD + 1) * DTYOFCNTUP(dutA));
			STV(PWM1->_3_CMPA, cmpA - 1);//duty cycle 50%
			break;
		}
		switch (modB)
		{
		case LEFT_ALIGN_MODE:
			cmpB = ((PWM1->_3_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM1->_3_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case RIGHT_ALIGN_MODE:
			cmpB = ((PWM1->_3_LOAD + 1) * DTYOFCNTDN(dutB));
			STV(PWM1->_3_CMPB, cmpB - 1);//duty cycle 50%
			break;
		case CENTER_ALIGN_MODE:
			cmpB = ((PWM1->_3_LOAD + 1) * DTYOFCNTUP(dutB));
			STV(PWM1->_3_CMPB, cmpB - 1);//duty cycle 50%
			break;
		}
		break;
	}
}
void PWM_app(uint8_t port,uint8_t pin)
{
	/*control the brightness of RED LED*/
 PLL_init(CLK_40MHZ);
  sysclock=40000000;
	float counter= 1;
  PWM_Init(port,pin,LEFT_ALIGN_MODE,20,0.1);
				msDelay(20000);//delay 20sec

 	while(1){
	  PWM_CmpUpdate(port,pin,LEFT_ALIGN_MODE,0.1);
		for(counter=1;counter<=99;counter++)
		{
	      PWM_CmpUpdate(port,pin,LEFT_ALIGN_MODE,counter);
			msDelay(1000);
		}
		msDelay(5000);
		for(counter=99;counter>=1;counter--)
		{
	  PWM_CmpUpdate(port,pin,LEFT_ALIGN_MODE,counter);
			msDelay(1000);
		}
			msDelay(5000);
	}
}

