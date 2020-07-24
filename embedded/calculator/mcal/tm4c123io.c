#include "tm4c123io.h"

void GPIO_PinInit(uint8_t port, uint8_t bits, uint8_t direction) {
	switch (port) {
	case PORTA:
		if (RD1B(SYSCTL->RCGCGPIO, PORTA) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTA);
			while (RD1B(SYSCTL->PRGPIO, PORTA) == 0) {
			};
		}
		switch (bits) {
		case PA2:
			CLR1B(GPIOA->AMSEL, PA2);
			CLR1B(GPIOA->AFSEL, PA2);
			ST1B(GPIOA->DEN, PA2);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOA->DIR, PA2);
				break;
			case INPULUP:
				ST1B(GPIOA->PUR, PA2);
				CLR1B(GPIOA->DIR, PA2);
				break;
			case INPULDN:
				ST1B(GPIOA->PDR, PA2);
				CLR1B(GPIOA->DIR, PA2);
				break;
			}
			break;
		case PA3:
			CLR1B(GPIOA->AMSEL, PA3);
			CLR1B(GPIOA->AFSEL, PA3);
			ST1B(GPIOA->DEN, PA3);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOA->DIR, PA3);
				break;
			case INPULUP:
				ST1B(GPIOA->PUR, PA3);
				CLR1B(GPIOA->DIR, PA3);
				break;
			case INPULDN:
				ST1B(GPIOA->PDR, PA3);
				CLR1B(GPIOA->DIR, PA3);
				break;
			}
			break;
		case PA4:
			CLR1B(GPIOA->AMSEL, PA4);
			CLR1B(GPIOA->AFSEL, PA4);
			ST1B(GPIOA->DEN, PA4);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOA->DIR, PA4);
				break;
			case INPULUP:
				ST1B(GPIOA->PUR, PA4);
				CLR1B(GPIOA->DIR, PA4);
				break;
			case INPULDN:
				ST1B(GPIOA->PDR, PA4);
				CLR1B(GPIOA->DIR, PA4);
				break;
			}
			break;
		case PA5:
			CLR1B(GPIOA->AMSEL, PA5);
			CLR1B(GPIOA->AFSEL, PA5);
			ST1B(GPIOA->DEN, PA5);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOA->DIR, PA5);
				break;
			case INPULUP:
				ST1B(GPIOA->PUR, PA5);
				CLR1B(GPIOA->DIR, PA5);
				break;
			case INPULDN:
				ST1B(GPIOA->PDR, PA5);
				CLR1B(GPIOA->DIR, PA5);
				break;
			}
			break;
		case PA6:
			CLR1B(GPIOA->AMSEL, PA6);
			CLR1B(GPIOA->AFSEL, PA6);
			ST1B(GPIOA->DEN, PA6);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOA->DIR, PA6);
				break;
			case INPULUP:
				ST1B(GPIOA->PUR, PA6);
				CLR1B(GPIOA->DIR, PA6);
				break;
			case INPULDN:
				ST1B(GPIOA->PDR, PA6);
				CLR1B(GPIOA->DIR, PA6);
				break;
			}
			break;
		case PA7:
			CLR1B(GPIOA->AMSEL, PA7);
			CLR1B(GPIOA->AFSEL, PA7);
			ST1B(GPIOA->DEN, PA7);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOA->DIR, PA7);
				break;
			case INPULUP:
				ST1B(GPIOA->PUR, PA7);
				CLR1B(GPIOA->DIR, PA7);
				break;
			case INPULDN:
				ST1B(GPIOA->PDR, PA7);
				CLR1B(GPIOA->DIR, PA7);
				break;
			}
			break;
		}
		break;   // BREAK PORT A
	case PORTB:
		if (RD1B(SYSCTL->RCGCGPIO, PORTB) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTB);
			while (RD1B(SYSCTL->PRGPIO, PORTB) == 0) {
			};
		}
		switch (bits) {
		case PB0:
			CLR1B(GPIOB->AMSEL, PB0);
			CLR1B(GPIOB->AFSEL, PB0);
			ST1B(GPIOB->DEN, PB0);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOB->DIR, PB0);
				break;
			case INPULUP:
				ST1B(GPIOB->PUR, PB0);
				CLR1B(GPIOB->DIR, PB0);
				break;
		case INPULDN:
				ST1B(GPIOB->PDR, PB0);
				CLR1B(GPIOB->DIR, PB0);
				break;
			}
			break;
		case PB1:
			CLR1B(GPIOB->AMSEL, PB1);
			CLR1B(GPIOB->AFSEL, PB1);
			ST1B(GPIOB->DEN, PB1);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOB->DIR, PB1);
				break;
			case INPULUP:
				ST1B(GPIOB->PUR, PB1);
				CLR1B(GPIOB->DIR, PB1);
				break;
		  case INPULDN:
				ST1B(GPIOB->PDR, PB1);
				CLR1B(GPIOB->DIR, PB1);
			  break;
			}
			break;
		case PB2:
			CLR1B(GPIOB->AMSEL, PB2);
			CLR1B(GPIOB->AFSEL, PB2);
			ST1B(GPIOB->DEN, PB2);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOB->DIR, PB2);
				break;
			case INPULUP:
				ST1B(GPIOB->PUR, PB2);
				CLR1B(GPIOB->DIR, PB2);
				break;
		  case INPULDN:
				ST1B(GPIOB->PDR, PB2);
				CLR1B(GPIOB->DIR, PB2);
			  break;
			}
			break;
		case PB3:
			CLR1B(GPIOB->AMSEL, PB3);
			CLR1B(GPIOB->AFSEL, PB3);
			ST1B(GPIOB->DEN, PB3);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOB->DIR, PB3);
				break;
			case INPULUP:
				ST1B(GPIOB->PUR, PB3);
				CLR1B(GPIOB->DIR, PB3);
				break;
			case INPULDN:
				ST1B(GPIOB->PDR, PB3);
				CLR1B(GPIOB->DIR, PB3);
			  break;
			}
			break;
		case PB4:
			CLR1B(GPIOB->AMSEL, PB4);
			CLR1B(GPIOB->AFSEL, PB4);
			ST1B(GPIOB->DEN, PB4);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOB->DIR, PB4);
				break;
			case INPULUP:
				ST1B(GPIOB->PUR, PB4);
				CLR1B(GPIOB->DIR, PB4);
				break;
			case INPULDN:
				ST1B(GPIOB->PDR, PB4);
				CLR1B(GPIOB->DIR, PB4);
			  break;
			}
			break;
		case PB5:
			CLR1B(GPIOB->AMSEL, PB5);
			CLR1B(GPIOB->AFSEL, PB5);
			ST1B(GPIOB->DEN, PB5);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOB->DIR, PB5);
				break;
			case INPULUP:
				ST1B(GPIOB->PUR, PB5);
				CLR1B(GPIOB->DIR, PB5);
				break;
			case INPULDN:
				ST1B(GPIOB->PDR, PB5);
				CLR1B(GPIOB->DIR, PB5);
			  break;
			}
			break;
		case PB6:
			CLR1B(GPIOB->AMSEL, PB6);
			CLR1B(GPIOB->AFSEL, PB6);
			ST1B(GPIOB->DEN, PB6);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOB->DIR, PB6);
				break;
			case INPULUP:
				ST1B(GPIOB->PUR, PB6);
				CLR1B(GPIOB->DIR, PB6);
				break;
			case INPULDN:
				ST1B(GPIOB->PDR, PB6);
				CLR1B(GPIOB->DIR, PB6);
			  break;
			}
			break;
		case PB7:
			CLR1B(GPIOB->AMSEL, PB7);
			CLR1B(GPIOB->AFSEL, PB7);
			ST1B(GPIOB->DEN, PB7);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOB->DIR, PB7);
				break;
			case INPULUP:
				ST1B(GPIOB->PUR, PB7);
				CLR1B(GPIOB->DIR, PB7);
				break;
			case INPULDN:
				ST1B(GPIOB->PDR, PB7);
				CLR1B(GPIOB->DIR, PB7);
			  break;
			}
			break;
		}
		break;
	case PORTC:
		if (RD1B(SYSCTL->RCGCGPIO, PORTC) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTC);
			while (RD1B(SYSCTL->PRGPIO, PORTC) == 0) {
			};
		}
		switch (bits) {
		case PC4:
			CLR1B(GPIOC->AMSEL, PC4);
			CLR1B(GPIOC->AFSEL, PC4);
			ST1B(GPIOC->DEN, PC4);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOC->DIR, PC4);
				break;
			case INPULUP:
				ST1B(GPIOC->PUR, PC4);
				CLR1B(GPIOC->DIR, PC4);
				break;
			case INPULDN:
				ST1B(GPIOC->PDR,PC4);
				CLR1B(GPIOC->DIR,PC4);
			  break;
			}
			break;
		case PC5:
			CLR1B(GPIOC->AMSEL, PC5);
			CLR1B(GPIOC->AFSEL, PC5);
			ST1B(GPIOC->DEN, PC5);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOC->DIR, PC5);
				break;
			case INPULUP:
				ST1B(GPIOC->PUR, PC5);
				CLR1B(GPIOC->DIR, PC5);
				break;
			case INPULDN:
				ST1B(GPIOC->PDR,PC5);
				CLR1B(GPIOC->DIR,PC5);
			  break;
			}
			break;
		case PC6:
			CLR1B(GPIOC->AMSEL, PC6);
			CLR1B(GPIOC->AFSEL, PC6);
			ST1B(GPIOC->DEN, PC6);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOC->DIR, PC6);
				break;
			case INPULUP:
				ST1B(GPIOC->PUR, PC6);
				CLR1B(GPIOC->DIR, PC6);
				break;
			case INPULDN:
				ST1B(GPIOC->PDR,PC6);
				CLR1B(GPIOC->DIR,PC6);
			  break;
			}
			break;
		case PC7:
			CLR1B(GPIOC->AMSEL, PC7);
			CLR1B(GPIOC->AFSEL, PC7);
			ST1B(GPIOC->DEN, PC7);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOC->DIR, PC7);
				break;
			case INPULUP:
				ST1B(GPIOC->PUR, PC7);
				CLR1B(GPIOC->DIR, PC7);
				break;
			case INPULDN:
				ST1B(GPIOC->PDR,PC7);
				CLR1B(GPIOC->DIR,PC7);
			  break;
			}
			break;
		}
		break;
	case PORTD:
		if (RD1B(SYSCTL->RCGCGPIO, PORTD) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTD);
			while (RD1B(SYSCTL->PRGPIO, PORTD) == 0) {
			};
		}
		switch (bits) {
		case PD0:
			CLR1B(GPIOD->AMSEL, PD0);
			CLR1B(GPIOD->AFSEL, PD0);
			ST1B(GPIOD->DEN, PD0);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOD->DIR, PD0);
				break;
			case INPULUP:
				ST1B(GPIOD->PUR, PD0);
				CLR1B(GPIOD->DIR, PD0);
				break;
			case INPULDN:
				ST1B(GPIOD->PDR,PD0);
				CLR1B(GPIOD->DIR,PD0);
			  break;
			}
			break;
		case PD1:
			CLR1B(GPIOD->AMSEL, PD1);
			CLR1B(GPIOD->AFSEL, PD1);
			ST1B(GPIOD->DEN, PD1);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOD->DIR, PD1);
				break;
			case INPULUP:
				ST1B(GPIOD->PUR, PD1);
				CLR1B(GPIOD->DIR, PD1);
				break;
			case INPULDN:
				ST1B(GPIOD->PDR,PD1);
				CLR1B(GPIOD->DIR,PD1);
			  break;
			}
			break;
		case PD2:
			CLR1B(GPIOD->AMSEL, PD2);
			CLR1B(GPIOD->AFSEL, PD2);
			ST1B(GPIOD->DEN, PD2);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOD->DIR, PD2);
				break;
			case INPULUP:
				ST1B(GPIOD->PUR, PD2);
				CLR1B(GPIOD->DIR, PD2);
				break;
			case INPULDN:
				ST1B(GPIOD->PDR,PD2);
				CLR1B(GPIOD->DIR,PD2);
			  break;
			}
			break;
		case PD3:
			CLR1B(GPIOD->AMSEL, PD3);
			CLR1B(GPIOD->AFSEL, PD3);
			ST1B(GPIOD->DEN, PD3);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOD->DIR, PD3);
				break;
			case INPULUP:
				ST1B(GPIOD->PUR, PD3);
				CLR1B(GPIOD->DIR, PD3);
				break;
			case INPULDN:
				ST1B(GPIOD->PDR,PD3);
				CLR1B(GPIOD->DIR,PD3);
			  break;
			}
			break;
		case PD6:
			CLR1B(GPIOD->AMSEL, PD6);
			CLR1B(GPIOD->AFSEL, PD6);
			ST1B(GPIOD->DEN, PD6);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOD->DIR, PD6);
				break;
			case INPULUP:
				ST1B(GPIOD->PUR, PD6);
				CLR1B(GPIOD->DIR, PD6);
				break;
			case INPULDN:
				ST1B(GPIOD->PDR,PD6);
				CLR1B(GPIOD->DIR,PD6);
			  break;
			}
			break;
		case PD7:
			GPIOD->LOCK = UNLOCK;
			ST1B(GPIOD->CR, PD7);
			CLR1B(GPIOD->AMSEL, PD7);
			CLR1B(GPIOD->AFSEL, PD7);
			ST1B(GPIOD->DEN, PD7);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOD->DIR, PD7);
				break;
			case INPULUP:
				ST1B(GPIOD->PUR, PD7);
				CLR1B(GPIOD->DIR, PD7);
				break;
			case INPULDN:
				ST1B(GPIOD->PDR,PD7);
				CLR1B(GPIOD->DIR,PD7);
			  break;
			}
			break;
		}
		break;
	case PORTE:
		if (RD1B(SYSCTL->RCGCGPIO, PORTE) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTE);
			while (RD1B(SYSCTL->PRGPIO, PORTE) == 0) {
			};
		}
		switch (bits) {
		case PE0:
			CLR1B(GPIOE->AMSEL, PE0);
			CLR1B(GPIOE->AFSEL, PE0);
			ST1B(GPIOE->DEN, PE0);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOE->DIR, PE0);
				break;
			case INPULUP:
				ST1B(GPIOE->PUR, PE0);
				CLR1B(GPIOE->DIR, PE0);
				break;
			case INPULDN:
				ST1B(GPIOE->PDR,PE0);
				CLR1B(GPIOE->DIR,PE0);
			  break;
			}
			break;
		case PE1:
			CLR1B(GPIOE->AMSEL, PE1);
			CLR1B(GPIOE->AFSEL, PE1);
			ST1B(GPIOE->DEN, PE1);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOE->DIR, PE1);
				break;
			case INPULUP:
				ST1B(GPIOE->PUR, PE1);
				CLR1B(GPIOE->DIR, PE1);
				break;
			case INPULDN:
				ST1B(GPIOE->PDR,PE1);
				CLR1B(GPIOE->DIR,PE1);
			  break;
			}
			break;
		case PE2:
			CLR1B(GPIOE->AMSEL, PE2);
			CLR1B(GPIOE->AFSEL, PE2);
			ST1B(GPIOE->DEN, PE2);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOE->DIR, PE2);
				break;
			case INPULUP:
				ST1B(GPIOE->PUR, PE2);
				CLR1B(GPIOE->DIR, PE2);
				break;
			case INPULDN:
				ST1B(GPIOE->PDR,PE2);
				CLR1B(GPIOE->DIR,PE2);
			  break;
			}
			break;
		case PE3:
			CLR1B(GPIOE->AMSEL, PE3);
			CLR1B(GPIOE->AFSEL, PE3);
			ST1B(GPIOE->DEN, PE3);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOE->DIR, PE3);
				break;
			case INPULUP:
				ST1B(GPIOE->PUR, PE3);
				CLR1B(GPIOE->DIR, PE3);
				break;
			case INPULDN:
				ST1B(GPIOE->PDR,PE3);
				CLR1B(GPIOE->DIR,PE3);
			  break;
			}
			break;
		case PE4:
			CLR1B(GPIOE->AMSEL, PE4);
			CLR1B(GPIOE->AFSEL, PE4);
			ST1B(GPIOE->DEN, PE4);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOE->DIR, PE4);
				break;
			case INPULUP:
				ST1B(GPIOE->PUR, PE4);
				CLR1B(GPIOE->DIR, PE4);
				break;
			case INPULDN:
				ST1B(GPIOE->PDR,PE4);
				CLR1B(GPIOE->DIR,PE4);
			  break;
			}
			break;
		case PE5:
			CLR1B(GPIOE->AMSEL, PE5);
			CLR1B(GPIOE->AFSEL, PE5);
			ST1B(GPIOE->DEN, PE5);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOE->DIR, PE5);
				break;
			case INPULUP:
				ST1B(GPIOE->PUR, PE5);
				CLR1B(GPIOE->DIR, PE5);
				break;
			case INPULDN:
				ST1B(GPIOE->PDR,PE5);
				CLR1B(GPIOE->DIR,PE5);
			  break;
			}
			break;
		}
		break;
	case PORTF:
		if (RD1B(SYSCTL->RCGCGPIO, PORTF) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTF);
			while (RD1B(SYSCTL->PRGPIO, PORTF) == 0) {
			};
		}
		switch (bits) {
		case PF0:
			GPIOF->LOCK = UNLOCK;
			ST1B(GPIOF->CR, PF0);
			CLR1B(GPIOF->AMSEL, PF0);
			CLR1B(GPIOF->AFSEL, PF0);
			ST1B(GPIOF->DEN, PF0);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOF->DIR, PF0);
				break;
			case INPULUP:
				ST1B(GPIOF->PUR, PF0);
				CLR1B(GPIOF->DIR, PF0);
				break;
			case INPULDN:
				ST1B(GPIOF->PDR,PF0);
				CLR1B(GPIOF->DIR,PF0);
			  break;
			}
			break;
		case PF1:
			CLR1B(GPIOF->AMSEL, PF1);
			CLR1B(GPIOF->AFSEL, PF1);
			ST1B(GPIOF->DEN, PF1);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOF->DIR, PF1);
				break;
			case INPULUP:
				ST1B(GPIOF->PUR, PF1);
				CLR1B(GPIOF->DIR, PF1);
				break;
			case INPULDN:
				ST1B(GPIOF->PDR,PF1);
				CLR1B(GPIOF->DIR,PF1);
			  break;
			}
			break;
		case PF2:
			CLR1B(GPIOF->AMSEL, PF2);
			CLR1B(GPIOF->AFSEL, PF2);
			ST1B(GPIOF->DEN, PF2);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOF->DIR, PF2);
				break;
			case INPULUP:
				ST1B(GPIOF->PUR, PF2);
				CLR1B(GPIOF->DIR, PF2);
				break;
			case INPULDN:
				ST1B(GPIOF->PDR,PF2);
				CLR1B(GPIOF->DIR,PF2);
			  break;
			}
			break;
		case PF3:
			CLR1B(GPIOF->AMSEL, PF3);
			CLR1B(GPIOF->AFSEL, PF3);
			ST1B(GPIOF->DEN, PF3);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOF->DIR, PF3);
				break;
			case INPULUP:
				ST1B(GPIOF->PUR, PF3);
				CLR1B(GPIOF->DIR, PF3);
				break;
			case INPULDN:
				ST1B(GPIOF->PDR,PF3);
				CLR1B(GPIOF->DIR,PF3);
			  break;
			}
			break;
		case PF4:
			CLR1B(GPIOF->AMSEL, PF4);
			CLR1B(GPIOF->AFSEL, PF4);
			ST1B(GPIOF->DEN, PF4);
			switch (direction) {
			case OUTPUT :
				ST1B(GPIOF->DIR, PF4);
				break;
			case INPULUP:
				ST1B(GPIOF->PUR, PF4);
				CLR1B(GPIOF->DIR, PF4);
				break;
			case INPULDN:
				ST1B(GPIOF->PDR,PF4);
				CLR1B(GPIOF->DIR,PF4);
			  break;
			}
			break;
		}
	}
}

void GPIO_PinOut(uint8_t port, uint8_t bits, uint8_t volt) {
	switch (port) {
	case PORTA:
		switch (bits) {
		case PA2:
			switch (volt) {
			case HIGH:
				ST1B(GPIOA->DATA, PA2);
				break;
			case LOW:
				CLR1B(GPIOA->DATA, PA2);
			}
			break;
		case PA3:
			switch (volt) {
			case HIGH:
				ST1B(GPIOA->DATA, PA3);
				break;
			case LOW:
				CLR1B(GPIOA->DATA, PA3);
			}
			break;
		case PA4:
			switch (volt) {
			case HIGH:
				ST1B(GPIOA->DATA, PA4);
				break;
			case LOW:
				CLR1B(GPIOA->DATA, PA4);
			}
			break;
		case PA5:
			switch (volt) {
			case HIGH:
				ST1B(GPIOA->DATA, PA5);
				break;
			case LOW:
				CLR1B(GPIOA->DATA, PA5);
			}
			break;
		case PA6:
			switch (volt) {
			case HIGH:
				ST1B(GPIOA->DATA, PA6);
				break;
			case LOW:
				CLR1B(GPIOA->DATA, PA6);
			}
			break;
		case PA7:
			switch (volt) {
			case HIGH:
				ST1B(GPIOA->DATA, PA7);
				break;
			case LOW:
				CLR1B(GPIOA->DATA, PA7);
				break;
			}
			break;
		}
		break;
	case PORTB:
		switch (bits) {
		case PB0:
			switch (volt) {
			case HIGH:
				ST1B(GPIOB->DATA, PB0);
				break;
			case LOW:
				CLR1B(GPIOB->DATA, PB0);
				break;
			}
			break;
		case PB1:
			switch (volt) {
			case HIGH:
				ST1B(GPIOB->DATA, PB1);
				break;
			case LOW:
				CLR1B(GPIOB->DATA, PB1);
				break;
			}
			break;
		case PB2:
			switch (volt) {
			case HIGH:
				ST1B(GPIOB->DATA, PB2);
				break;
			case LOW:
				CLR1B(GPIOB->DATA, PB2);
				break;
			}
			break;
		case PB3:
			switch (volt) {
			case HIGH:
				ST1B(GPIOB->DATA, PB3);
				break;
			case LOW:
				CLR1B(GPIOB->DATA, PB3);
				break;
			}
			break;
		case PB4:
			switch (volt) {
			case HIGH:
				ST1B(GPIOB->DATA, PB4);
				break;
			case LOW:
				CLR1B(GPIOB->DATA, PB4);
				break;
			}
			break;
		case PB5:
			switch (volt) {
			case HIGH:
				ST1B(GPIOB->DATA, PB5);
				break;
			case LOW:
				CLR1B(GPIOB->DATA, PB5);
				break;
			}
			break;
		case PB6:
			switch (volt) {
			case HIGH:
				ST1B(GPIOB->DATA, PB6);
				break;
			case LOW:
				CLR1B(GPIOB->DATA, PB6);
				break;
			}
			break;
		case PB7:
			switch (volt) {
			case HIGH:
				ST1B(GPIOB->DATA, PB7);
				break;
			case LOW:
				CLR1B(GPIOB->DATA, PB7);
				break;
			}
			break;
		}
		break;
	case PORTC:
		switch (bits) {
		case PC4:
			switch (volt) {
			case HIGH:
				ST1B(GPIOC->DATA, PC4);
				break;
			case LOW:
				CLR1B(GPIOC->DATA, PC4);
				break;
			}
			break;
		case PC5:
			switch (volt) {
			case HIGH:
				ST1B(GPIOC->DATA, PC5);
				break;
			case LOW:
				CLR1B(GPIOC->DATA, PC5);
				break;
			}
			break;
		case PC6:
			switch (volt) {
			case HIGH:
				ST1B(GPIOC->DATA, PC6);
				break;
			case LOW:
				CLR1B(GPIOC->DATA, PC6);
				break;
			}
			break;
		case PC7:
			switch (volt) {
			case HIGH:
				ST1B(GPIOC->DATA, PC7);
				break;
			case LOW:
				CLR1B(GPIOC->DATA, PC7);
				break;
			}
			break;
		}
		break;
	case PORTD:
		switch (bits) {
		case PD0:
			switch (volt) {
			case HIGH:
				ST1B(GPIOD->DATA, PD0);
				break;
			case LOW:
				CLR1B(GPIOD->DATA, PD0);
				break;
			}
			break;
		case PD1:
			switch (volt) {
			case HIGH:
				ST1B(GPIOD->DATA, PD1);
				break;
			case LOW:
				CLR1B(GPIOD->DATA, PD1);
				break;
			}
			break;
		case PD2:
			switch (volt) {
			case HIGH:
				ST1B(GPIOD->DATA, PD2);
				break;
			case LOW:
				CLR1B(GPIOD->DATA, PD2);
				break;
			}
			break;
		case PD3:
			switch (volt) {
			case HIGH:
				ST1B(GPIOD->DATA, PD3);
				break;
			case LOW:
				CLR1B(GPIOD->DATA, PD3);
				break;
			}
			break;
		case PD6:
			switch (volt) {
			case HIGH:
				ST1B(GPIOD->DATA, PD6);
				break;
			case LOW:
				CLR1B(GPIOD->DATA, PD6);
				break;
			}
			break;
		case PD7:
			switch (volt) {
			case HIGH:
				ST1B(GPIOD->DATA, PD7);
				break;
			case LOW:
				CLR1B(GPIOD->DATA, PD7);
				break;
			}
			break;
		}
		break;
	case PORTE:
		switch (bits) {
		case PE0:
			switch (volt) {
			case HIGH:
				ST1B(GPIOE->DATA, PE0);
				break;
			case LOW:
				CLR1B(GPIOE->DATA, PE0);
				break;
			}
			break;
		case PE1:
			switch (volt) {
			case HIGH:
				ST1B(GPIOE->DATA, PE1);
				break;
			case LOW:
				CLR1B(GPIOE->DATA, PE1);
				break;
			}
			break;
		case PE2:
			switch (volt) {
			case HIGH:
				ST1B(GPIOE->DATA, PE2);
				break;
			case LOW:
				CLR1B(GPIOE->DATA, PE2);
				break;
			}
			break;
		case PE3:
			switch (volt) {
			case HIGH:
				ST1B(GPIOE->DATA, PE3);
				break;
			case LOW:
				CLR1B(GPIOE->DATA, PE3);
				break;
			}
			break;
		case PE4:
			switch (volt) {
			case HIGH:
				ST1B(GPIOE->DATA, PE4);
				break;
			case LOW:
				CLR1B(GPIOE->DATA, PE4);
				break;
			}
			break;
		case PE5:
			switch (volt) {
			case HIGH:
				ST1B(GPIOE->DATA, PE5);
				break;
			case LOW:
				CLR1B(GPIOE->DATA, PE5);
				break;
			}
			break;
		}
		break;
	case PORTF:
		switch (bits) {
		case PF0:
			switch (volt) {
			case HIGH:
				ST1B(GPIOF->DATA, PF0);
				break;
			case LOW:
				CLR1B(GPIOF->DATA, PF0);
				break;
			}
			break;
		case PF1:
			switch (volt) {
			case HIGH:
				ST1B(GPIOF->DATA, PF1);
				break;
			case LOW:
				CLR1B(GPIOF->DATA, PF1);
				break;
			}
			break;
		case PF2:
			switch (volt) {
			case HIGH:
				ST1B(GPIOF->DATA, PF2);
				break;
			case LOW:
				CLR1B(GPIOF->DATA, PF2);
				break;
			}
			break;
		case PF3:
			switch (volt) {
			case HIGH:
				ST1B(GPIOF->DATA, PF3);
				break;
			case LOW:
				CLR1B(GPIOF->DATA, PF3);
				break;
			}
			break;
		case PF4:
			switch (volt) {
			case HIGH:
				ST1B(GPIOF->DATA, PF4);
				break;
			case LOW:
				CLR1B(GPIOF->DATA, PF4);
				break;
			}
			break;
		}
	}
}
uint8_t GPIO_PinRead(uint8_t port, uint8_t bits) {
	uint8_t input=0;
	switch (port) {
	case PORTA:
		switch (bits) {
		case PA2:
				input=RD1B(GPIOA->DATA, PA2);
				break;
		case PA3:
				input=RD1B(GPIOA->DATA, PA3);
			break;
		case PA4:
				input=RD1B(GPIOA->DATA, PA4);
				break;
		case PA5:
				input=RD1B(GPIOA->DATA, PA5);
				break;
		case PA6:
				input=RD1B(GPIOA->DATA, PA6);
				break;
		case PA7:
				input=RD1B(GPIOA->DATA, PA7);
				break;
			}
			break;
	case PORTB:
		switch (bits) {
		case PB0:
				input=RD1B(GPIOB->DATA, PB0);
				break;
		case PB1:
				input=RD1B(GPIOB->DATA, PB1);
			break;
		case PB2:
				input=RD1B(GPIOB->DATA, PB2);
			break;
		case PB3:
				input=RD1B(GPIOB->DATA, PB3);
			break;
		case PB4:
				input=RD1B(GPIOB->DATA, PB4);
				break;
		case PB5:
				input=RD1B(GPIOB->DATA, PB5);
			break;
		case PB6:
				input=RD1B(GPIOB->DATA, PB6);
			break;
		case PB7:
				input=RD1B(GPIOB->DATA, PB7);
				break;
		}
		break;
	case PORTC:
		switch (bits) {
			case PC4:
				input=RD1B(GPIOC->DATA, PC4);
				break;
		case PC5:
				input=RD1B(GPIOC->DATA, PC5);
			break;
		case PC6:
				input=RD1B(GPIOC->DATA, PC6);
			break;
		case PC7:
				input=RD1B(GPIOC->DATA, PC7);
				break;
		}
		break;
	case PORTD:
		switch (bits) {
		case PD0:
				input=RD1B(GPIOD->DATA, PD0);
				break;
		case PD1:
				input=RD1B(GPIOD->DATA, PD1);
				break;
		case PD2:
				input=RD1B(GPIOD->DATA, PD2);
			break;
		case PD3:
				input=RD1B(GPIOD->DATA, PD3);
			break;
		case PD6:
				input=RD1B(GPIOD->DATA, PD6);
			break;
		case PD7:
				input=RD1B(GPIOD->DATA, PD7);
			break;
		}
		break;
	case PORTE:
		switch (bits) {
		case PE0:
				input=RD1B(GPIOE->DATA, PE0);
				break;
		case PE1:
				input=RD1B(GPIOE->DATA, PE1);
				break;
		case PE2:
				input=RD1B(GPIOE->DATA, PE2);
				break;
		case PE3:
				input=RD1B(GPIOE->DATA, PE3);
			break;
		case PE4:
				input=RD1B(GPIOE->DATA, PE4);
			break;
		case PE5:
				input=RD1B(GPIOE->DATA, PE5);
			break;
		}
		break;
	case PORTF:
		switch (bits) {
		case PF0:
				input=RD1B(GPIOF->DATA, PF0);
		case PF1:
				input=RD1B(GPIOF->DATA, PF1);
				break;
		case PF2:
				input=RD1B(GPIOF->DATA, PF2);
			break;
		case PF3:
				input=RD1B(GPIOF->DATA, PF3);
			break;
		case PF4:
				input=RD1B(GPIOF->DATA, PF4);
				break;
			}
			break;
	}
	return input;
}


void GPIO_PortInit(uint8_t port, uint8_t direction) {
	switch (port) {
	case PORTA:
		if (RD1B(SYSCTL->RCGCGPIO, PORTA) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTA);
			while (RD1B(SYSCTL->PRGPIO, PORTA) == 0) {
			};
		}
		STV6BI(GPIOA->AMSEL, PA2, 0);
		STV6BI(GPIOA->AFSEL, PA2, 0);
		STV6BI(GPIOA->DEN, PA2, 0x3F);
		switch (direction) {
		case OUTPUT :
			STV6BI(GPIOA->DIR, PA2, 0x3F);
			break;
		case INPULUP:
			STV6BI(GPIOA->DEN, PA2, 0);

		}
		break;
	case PORTB:
		if (RD1B(SYSCTL->RCGCGPIO, PORTB) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTB);
			while (RD1B(SYSCTL->PRGPIO, PORTB) == 0) {
			};
		}
		STV(GPIOB->AMSEL, 0);
		STV(GPIOB->AFSEL, 0);
		STV(GPIOB->DEN, 0xFF);
		switch (direction) {
		case OUTPUT :
			STV(GPIOB->DIR, 0xFF);
			break;
		case INPULUP:
			STV(GPIOB->DIR, 0);

		}
		break;
	case PORTC:
		if (RD1B(SYSCTL->RCGCGPIO, PORTC) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTC);
			while (RD1B(SYSCTL->PRGPIO, PORTC) == 0) {
			};
		}
		STV4BI(GPIOC->AMSEL, PC4, 0);
		STV4BI(GPIOC->AFSEL, PC4, 0);
		STV4BI(GPIOC->DEN, PC4, 0x0F);
		switch (direction) {
		case OUTPUT :
			STV4BI(GPIOC->DIR, PC4, 0x0F);
			break;
		case INPULUP:
			STV4BI(GPIOC->DIR, PC4, 0);
		}
		break;
	case PORTD:
		if (RD1B(SYSCTL->RCGCGPIO, PORTD) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTD);
			while (RD1B(SYSCTL->PRGPIO, PORTD) == 0) {
			};
		}
		STV4BI(GPIOD->AMSEL, PD0, 0);
		STV2BI(GPIOD->AMSEL, PD6, 0);
		STV4BI(GPIOD->AFSEL, PD0, 0);
		STV2BI(GPIOD->AFSEL, PD6, 0);
		STV4BI(GPIOD->DEN, PD0, 0x0F);
		STV2BI(GPIOD->DEN, PD6, 0x3);
		STV(GPIOD->LOCK, UNLOCK);
		ST1B(GPIOD->CR, PD7);
		switch (direction) {
		case OUTPUT :
			STV4BI(GPIOD->DIR, PD0, 0x0F);
			STV2BI(GPIOD->DIR, PD6, 0x3);
			break;
		case INPULUP:
			STV4BI(GPIOD->DIR, PD0, 0);
			STV2BI(GPIOD->DIR, PD6, 0);
		}
		break;
	case PORTE:
		if (RD1B(SYSCTL->RCGCGPIO, PORTE) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTE);
			while (RD1B(SYSCTL->PRGPIO, PORTE) == 0) {
			};
		}
			STV6BI(GPIOE->AMSEL, PE0, 0);
			STV6BI(GPIOE->AFSEL, PE0, 0);
      STV6BI(GPIOE->DEN, PE0, 0x3F);
		switch (direction) {
		case OUTPUT :
			STV6BI(GPIOE->DIR, PE0, 0x3F);
			break;
		case INPULUP:
			STV6BI(GPIOE->DIR, PE0, 0);
		}
		break;
	case PORTF:
		if (RD1B(SYSCTL->RCGCGPIO, PORTF) == 0) {
			ST1B(SYSCTL->RCGCGPIO, PORTF);
			while (RD1B(SYSCTL->PRGPIO, PORTF) == 0) {
			};
		}
		STV(GPIOF->LOCK, UNLOCK);
		ST1B(GPIOF->CR, PF0);
		STV4BI(GPIOF->AMSEL, PF0, 0);
		STV4BI(GPIOF->AFSEL, PF0, 0);
		STV4BI(GPIOF->DEN, PF0, 0x0F);
		switch (direction) {
		case OUTPUT :
			STV4BI(GPIOF->DIR, PF0, 0x0F);
			break;
		case INPULUP:
			STV4BI(GPIOF->DIR, PF0, 0);

		}
	}
}
void GPIO_PortOutput(uint8_t port, uint8_t volt) {
	switch (port) {
	case PORTA:
		switch (volt) {
		case HIGH:
			STV6BI(GPIOA->DATA, PA2, volt);

			break;
		case LOW:
			STV6BI(GPIOA->DATA, PA2, volt);

		}
		break;
	case PORTB:
		switch (volt) {
		case HIGH:
			STV(GPIOB->DATA, volt);

			break;
		case LOW:
			STV(GPIOB->DATA, volt);

		}
		break;
	case PORTC:
		switch (volt) {
		case HIGH:
			STV4BI(GPIOC->DATA, PC4, volt);

			break;
		case LOW:
			STV4BI(GPIOC->DATA, PC4, volt);

			break;
		}
		break;
	case PORTD:
		switch (volt) {
		case HIGH:
			STV4BI(GPIOD->DATA, PD0, volt);
			STV2BI(GPIOD->DATA, PD6, volt);
			break;
		case LOW:
			STV4BI(GPIOD->DATA, PD0, volt);
			STV2BI(GPIOD->DATA, PD6, volt);
			break;
		}
		break;
	case PORTE:
		switch (volt) {
		case HIGH:
			STV6BI(GPIOE->DATA, PE0, volt);
			break;
		case LOW:
			STV6BI(GPIOE->DATA, PE0, 0);
		}
		break;
	case PORTF:
		switch (volt) {
		case HIGH:
			STV4BI(GPIOF->DATA, PF0, 0x0F);
			break;
		case LOW:
			STV4BI(GPIOF->DATA, PF0, 0);

		}
		break;
	}
}
void GPIO_Two_INDEXs_Output(uint8_t port, uint8_t startPin,uint8_t value) {
	switch (port) {
	case PORTA:
			STV2BI(GPIOA->DATA, startPin, value);
		break;
	case PORTB:
			STV2BI(GPIOB->DATA, startPin, value);
		break;
	case PORTC:
			STV2BI(GPIOC->DATA, startPin, value);
		break;
	case PORTD:
			STV2BI(GPIOD->DATA, startPin, value);
		break;
	case PORTE:
			STV2BI(GPIOE->DATA, startPin, value);
		break;
	case PORTF:
			STV2BI(GPIOF->DATA, startPin, value);
		break;
	}
}

uint8_t GPIO_Four_INDEXs_INPULUP_READ(uint8_t port, uint8_t startPin) {
	uint8_t input = 0;
	switch (port) {
	case PORTA:
			input = RD4B(GPIOA->DATA, startPin);
		break;
	case PORTB:
			input = RD4B(GPIOB->DATA, startPin);
		break;
	case PORTC:
			input = RD4B(GPIOC->DATA, startPin);
		break;
	case PORTD:
			input = RD4B(GPIOD->DATA, startPin);
		break;
	case PORTE:
			input = RD4B(GPIOE->DATA, startPin);
		break;
	case PORTF:
			input = RD4B(GPIOF->DATA, startPin);
		break;
	}
	return input;
}
void GPIO_NibblePinsOut(uint8_t port, uint8_t startPin,uint8_t value) {
	switch (port) {
	case PORTA:
			STV4BI(GPIOA->DATA, startPin, value);
		break;
	case PORTB:
			STV4BI(GPIOB->DATA, startPin, value);
		break;
	case PORTC:
			STV4BI(GPIOC->DATA, startPin, value);
		break;
	case PORTD:
			STV4BI(GPIOD->DATA, startPin, value);
		break;
	case PORTE:
			STV4BI(GPIOE->DATA, startPin, value);
		break;
	case PORTF:
			STV4BI(GPIOF->DATA, startPin, value);
		break;
	}
}
