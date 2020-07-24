#include "switch.h"
#include "RGB.h"
void SWITCH_Init(uint32_t sw) {
	switch (sw) {
	case SWITCH_1:
		GPIO_PinInit(PORTF, SWITCH_1, INPULUP);
		break;
	case SWITCH_2:
		GPIO_PinInit(PORTF, SWITCH_2, INPULUP);
		break;
	}
}

void SWITCH_App1(void){
	RGB_Init(ALL);
	SWITCH_Init(SWITCH_2);
	while (1) {
		RGB_Out(LED_RED,OFF);
		if (RD1B(GPIOF->DATA,SWITCH_2)== LOW) {
			RGB_Out(LED_RED,ON);
			while(RD1B(GPIOF->DATA,SWITCH_2)==0);
		}
	}
}
void SWITCH_App2(void){
  RGB_Init(ALL);
	SWITCH_Init(SWITCH_1);
	SWITCH_Init(SWITCH_2);
	while (1) {
		if(RD1B(GPIOF->DATA,SWITCH_2)== LOW) {
			RGB_Out(LED_RED,ON);
			while(RD1B(GPIOF->DATA,SWITCH_2)==0);
		}
		if(RD1B(GPIOF->DATA,SWITCH_1)== LOW) {
			RGB_Out(LED_RED,OFF);
			while(RD1B(GPIOF->DATA,SWITCH_1)==0);
		}
	}
}
uint8_t SWITCH_IsPressed(uint8_t sw){
	uint8_t state=0;
	switch(sw){
	case SWITCH_1:
		if(RD1B(SWITCH_PORT ,SWITCH_1)== LOW) state=1;
		break;
	case SWITCH_2:
		if(RD1B(SWITCH_PORT ,SWITCH_2)== LOW) state=1;
		break;
	}	
	return state;
}
void SWITCH_Interrpt_Init(uint8_t sw){
	switch(sw){
		case SWITCH_1:
			break;
		case SWITCH_2:
			break;
	}
}
