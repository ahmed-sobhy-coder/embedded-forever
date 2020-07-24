#include "ssi.h"

void SSI_Init(uint8_t SSIn, uint8_t mode) {
	switch (SSIn) {
	case SPI0:
		ST1B(SYSCTL->RCGCSSI, SPI0);//enable the clock for SSI0
		ST1B(SYSCTL->RCGCGPIO, PORTA);//enable the clock for GPIOD
		switch (mode) {
		case MASTER:
			ST3B(GPIOA->DIR, SSI0CLK, SSI0FSS, SSI0TX);
			CLR1B(GPIOA->DIR, SSI0RX);
			CLR4B(GPIOA->AMSEL, SSI0CLK, SSI0FSS, SSI0RX, SSI1TX);
			ST4B(GPIOA->DEN, SSI0CLK, SSI0FSS, SSI0RX, SSI0TX);
			ST4B(GPIOA->AFSEL, SSI0CLK, SSI0FSS, SSI0RX, SSI0TX);
			CLR1B(SSI0->CR1, SSE);//SSI operation is disabled
			CLR1B(SSI0->CC, SYS_CLOCK);//use system clock	
			CLR1B(SSI0->CR1, MS);//master
		   /*configure SSI1CLK to be 1 MHZ*/
			STV8BI(SSI0->CPSR, CPSDVSR, 2);
			STV4BI(SSI0->CR0, SCR, 7);
			/*configure SSI0 frame format*/
			STV2BI(SSI0->CR0, FRF, 0); //Freescale frame format
			STV4BI(SSI0->CR0, DSS, 7); //8 bit data size
			CLR2B(SSI0->CR0, SPO, SPH); //SPO=0, SPH=0;
			ST1B(SSI0->CR1, SSE);//SSI operation is Enabled
			break;
		case SLAVE:
			ST2B(GPIOA->DIR, SSI0CLK, SSI0TX);
			CLR2B(GPIOA->DIR, SSI0FSS,SSI0RX);
			CLR4B(GPIOA->AMSEL, SSI0CLK, SSI0FSS, SSI0RX, SSI0TX);
			ST4B(GPIOA->DEN, SSI0CLK, SSI0FSS, SSI0RX, SSI0TX);
			ST4B(GPIOA->AFSEL, SSI0CLK, SSI0FSS, SSI0RX, SSI0TX);
			CLR1B(SSI0->CC, SYS_CLOCK);//use system clock	
			CLR1B(SSI0->CR1, SSE);//SSI operation is disabled
			ST1B(SSI0->CR1, MS);//slave
		   /*configure SSI1CLK to be 1 MHZ*/
			STV8BI(SSI0->CPSR, CPSDVSR, 2);
			STV4BI(SSI0->CR0, SCR, 7);
			/*configure SSI0 frame format*/
			STV2BI(SSI0->CR0, FRF, 0); //Freescale frame format
			STV4BI(SSI0->CR0, DSS, 7); //8 bit data size
			CLR2B(SSI0->CR0, SPO, SPH); //SPO=0, SPH=0;
			ST1B(SSI0->CR1, SSE);//SSI operation is Enabled
			break;

		}
		break;
	case SPI1:
		//GPIOF->LOCK = UNLOCK;//we have to write to this register to unlock PF0
		//ST1B(GPIOF->CR, PF0); //commit the change in PF0
	
		ST1B(SYSCTL->RCGCSSI, SPI1);//enable the clock for SSI0
		ST1B(SYSCTL->RCGCGPIO, PORTF);//enable the clock for GPIOF
		GPIOF->LOCK = UNLOCK;//we have to write to this register to unlock PF0
		ST1B(GPIOF->CR, PF0); //commit the change in PF0
	switch (mode) {
		case MASTER:
			ST3B(GPIOF->DIR, SSI1CLK, SSI1FSS, SSI1TX);
			CLR1B(GPIOF->DIR, SSI1RX);
			CLR4B(GPIOF->AMSEL, SSI1CLK, SSI1FSS, SSI1RX, SSI1TX);
			ST4B(GPIOF->DEN, SSI1CLK, SSI1FSS, SSI1RX, SSI1TX);
			ST4B(GPIOF->AFSEL, SSI1CLK, SSI1FSS, SSI1RX, SSI1TX);
			ST4B4MI(GPIOF->PCTL, SSI1CLK, 2);
			ST4B4MI(GPIOF->PCTL, SSI1FSS, 2);
			ST4B4MI(GPIOF->PCTL, SSI1RX, 2);
			ST4B4MI(GPIOF->PCTL, SSI1TX, 2);
			CLR1B(SSI1->CR1, SSE);//SSI operation is disabled
			CLR1B(SSI1->CC, SYS_CLOCK);//use system clock	
			CLR1B(SSI1->CR1, MS);//master
		   /*configure SSI1CLK to be 1 MHZ*/
			STV8BI(SSI1->CPSR, CPSDVSR, 2);
			STV4BI(SSI1->CR0, SCR, 7);
			/*configure SSI0 frame format*/
			STV2BI(SSI1->CR0, FRF, 0); //Freescale frame format
			STV4BI(SSI1->CR0, DSS, 7); //8 bit data size
			CLR2B(SSI1->CR0, SPO, SPH); //SPO=0, SPH=0;
			ST1B(SSI1->CR1, SSE);//SSI operation is Enabled
			break;
		case SLAVE:
			ST2B(GPIOF->DIR, SSI1CLK, SSI1TX);
			CLR2B(GPIOF->DIR,SSI1FSS,SSI1RX);
			CLR4B(GPIOF->AMSEL, SSI1CLK, SSI1FSS, SSI1RX, SSI1TX);
			ST4B(GPIOF->DEN, SSI1CLK, SSI1FSS, SSI1RX, SSI1TX);
			ST4B(GPIOF->AFSEL, SSI1CLK, SSI1FSS, SSI1RX, SSI1TX);
			ST4B4MI(GPIOF->PCTL, SSI1CLK, 2);
			ST4B4MI(GPIOF->PCTL, SSI1FSS, 2);
			ST4B4MI(GPIOF->PCTL, SSI1RX, 2);
			ST4B4MI(GPIOF->PCTL, SSI1TX,2);
			CLR1B(SSI1->CC, SYS_CLOCK);//use system clock	
			CLR1B(SSI1->CR1, SSE);//SSI operation is disabled
			ST1B(SSI1->CR1, MS);//slave
		   /*configure SSI1CLK to be 1 MHZ*/
			STV8BI(SSI1->CPSR, CPSDVSR, 2);
			STV4BI(SSI1->CR0, SCR, 7);
			/*configure SSI0 frame format*/
			STV2BI(SSI1->CR0, FRF, 0); //Freescale frame format
			STV4BI(SSI1->CR0, DSS, 7); //8 bit data size
			CLR2B(SSI1->CR0, SPO, SPH); //SPO=0, SPH=0;
			ST1B(SSI1->CR1, SSE);//SSI operation is Enabled
			break;
		}

		break;
	case SPI2:
		ST1B(SYSCTL->RCGCSSI, SPI2);//enable the clock for SSI0
		ST1B(SYSCTL->RCGCGPIO, PORTB);//enable the clock for GPIOB
		switch (mode) {
		case MASTER:
			ST3B(GPIOB->DIR, SSI2CLK, SSI2FSS, SSI2TX);
			CLR1B(GPIOB->DIR, SSI2RX);
			CLR4B(GPIOB->AMSEL, SSI2CLK, SSI2FSS, SSI2RX, SSI1TX);
			ST4B(GPIOB->DEN, SSI2CLK, SSI2FSS, SSI2RX, SSI2TX);
			ST4B(GPIOB->AFSEL, SSI2CLK, SSI2FSS, SSI2RX, SSI2TX);
			ST4B4MI(GPIOB->PCTL, SSI2CLK, 2);
			ST4B4MI(GPIOB->PCTL, SSI2FSS, 2);
			ST4B4MI(GPIOB->PCTL, SSI2RX, 2);
			ST4B4MI(GPIOB->PCTL, SSI2TX, 2);
			CLR1B(SSI2->CR1, SSE);//SSI operation is disabled
			CLR1B(SSI2->CC, SYS_CLOCK);//use system clock	
			CLR1B(SSI2->CR1, MS);//master
		   /*configure SSI1CLK to be 1 MHZ*/
			STV8BI(SSI2->CPSR, CPSDVSR, 2);
			STV4BI(SSI2->CR0, SCR, 7);
			/*configure SSI0 frame format*/
			STV2BI(SSI2->CR0, FRF, 0); //Freescale frame format
			STV4BI(SSI2->CR0, DSS, 7); //8 bit data size
			CLR2B(SSI2->CR0, SPO, SPH); //SPO=0, SPH=0;
			ST1B(SSI2->CR1, SSE);//SSI operation is Enabled
			break;
		case SLAVE:
			ST2B(GPIOB->DIR, SSI2CLK, SSI2TX);
			CLR2B(GPIOB->DIR,SSI2FSS,SSI2RX);
			CLR4B(GPIOB->AMSEL, SSI2CLK, SSI2FSS, SSI2RX, SSI2TX);
			ST4B(GPIOB->DEN, SSI2CLK, SSI2FSS, SSI2RX, SSI2TX);
			ST4B(GPIOB->AFSEL, SSI2CLK, SSI2FSS, SSI2RX, SSI2TX);
			ST4B4MI(GPIOB->PCTL, SSI2CLK, 2);
			ST4B4MI(GPIOB->PCTL, SSI2FSS, 2);
			ST4B4MI(GPIOB->PCTL, SSI2RX, 2);
			ST4B4MI(GPIOB->PCTL, SSI2TX,2);
			CLR1B(SSI2->CC, SYS_CLOCK);//use system clock	
			CLR1B(SSI2->CR1, SSE);//SSI operation is disabled
			ST1B(SSI2->CR1, MS);//slave
		   /*configure SSI1CLK to be 1 MHZ*/
			STV8BI(SSI2->CPSR, CPSDVSR, 2);
			STV4BI(SSI2->CR0, SCR, 7);
			/*configure SSI0 frame format*/
			STV2BI(SSI2->CR0, FRF, 0); //Freescale frame format
			STV4BI(SSI2->CR0, DSS, 7); //8 bit data size
			CLR2B(SSI2->CR0, SPO, SPH); //SPO=0, SPH=0;
			ST1B(SSI2->CR1, SSE);//SSI operation is Enabled
			break;
		}
		break;
	case SPI3:
		ST1B(SYSCTL->RCGCSSI, SPI3);//enable the clock for SSI0
		ST1B(SYSCTL->RCGCGPIO, PORTD);//enable the clock for GPIOD
		switch (mode) {
		case MASTER:
			ST3B(GPIOD->DIR, SSI3CLK, SSI3FSS, SSI3TX);
			CLR1B(GPIOD->DIR, SSI3RX);
			CLR4B(GPIOD->AMSEL, SSI3CLK, SSI3FSS, SSI3RX, SSI1TX);
			ST4B(GPIOD->DEN, SSI3CLK, SSI3FSS, SSI3RX, SSI3TX);
			ST4B(GPIOD->AFSEL, SSI3CLK, SSI3FSS, SSI3RX, SSI3TX);
			ST4B4MI(GPIOD->PCTL, SSI3CLK, 1);
			ST4B4MI(GPIOD->PCTL, SSI3FSS, 1);
			ST4B4MI(GPIOD->PCTL, SSI3RX, 1);
			ST4B4MI(GPIOD->PCTL, SSI3TX, 1);
			CLR1B(SSI3->CR1, SSE);//SSI operation is disabled
			CLR1B(SSI3->CC, SYS_CLOCK);//use system clock	
			CLR1B(SSI3->CR1, MS);//master
		   /*configure SSI1CLK to be 1 MHZ*/
			STV8BI(SSI3->CPSR, CPSDVSR, 2);
			STV4BI(SSI3->CR0, SCR, 7);
			/*configure SSI0 frame format*/
			STV2BI(SSI3->CR0, FRF, 0); //Freescale frame format
			STV4BI(SSI3->CR0, DSS, 7); //8 bit data size
			CLR2B(SSI3->CR0, SPO, SPH); //SPO=0, SPH=0;
			ST1B(SSI3->CR1, SSE);//SSI operation is Enabled
			break;
		case SLAVE:
			ST2B(GPIOD->DIR, SSI3CLK, SSI3TX);
			CLR2B(GPIOD->DIR,SSI3FSS,SSI3RX);
			CLR4B(GPIOD->AMSEL, SSI3CLK, SSI3FSS, SSI3RX, SSI3TX);
			ST4B(GPIOD->DEN, SSI3CLK, SSI3FSS, SSI3RX, SSI3TX);
			ST4B(GPIOD->AFSEL, SSI3CLK, SSI3FSS, SSI3RX, SSI3TX);
			ST4B4MI(GPIOD->PCTL, SSI3CLK, 1);
			ST4B4MI(GPIOD->PCTL, SSI3FSS, 1);
			ST4B4MI(GPIOD->PCTL, SSI3RX, 1);
			ST4B4MI(GPIOD->PCTL, SSI3TX, 1);
			CLR1B(SSI3->CC, SYS_CLOCK);//use system clock	
			CLR1B(SSI3->CR1, SSE);//SSI operation is disabled
			ST1B(SSI3->CR1, MS);//slave
		   /*configure SSI1CLK to be 1 MHZ*/
			STV8BI(SSI3->CPSR, CPSDVSR, 2);
			STV4BI(SSI3->CR0, SCR, 7);
			/*configure SSI0 frame format*/
			STV2BI(SSI3->CR0, FRF, 0); //Freescale frame format
			STV4BI(SSI3->CR0, DSS, 7); //8 bit data size
			CLR2B(SSI3->CR0, SPO, SPH); //SPO=0, SPH=0;
			ST1B(SSI3->CR1, SSE);//SSI operation is Enabled
			break;
		}
		break;
	}
}
void SSI_Write_Data(uint8_t SSIn, uint8_t data) {
	switch (SSIn) {
	case SPI0:
		while (RD1B(SSI0->SR, TNF) == 0);
		SSI0->DR = (data & 0x00FF);
		while (RD1B(SSI0->SR, BSY) == 1) {};
		break;
	case SPI1:
		while (RD1B(SSI1->SR, TNF) == 0);
		SSI1->DR = (data & 0x00FF);
		while (RD1B(SSI1->SR, BSY) == 1) {};
		break;
	case SPI2:
		while (RD1B(SSI2->SR, TNF) == 0);
		SSI2->DR = (data & 0x00FF);
		while (RD1B(SSI2->SR, BSY) == 1) {};
		break;
	case SPI3:
		while (RD1B(SSI3->SR, TNF) == 0);
		SSI3->DR = (data & 0x00FF);
		while (RD1B(SSI3->SR, BSY) == 1) {};
		break;
	}

}
uint8_t SSI_Read_Data(uint8_t SSIn) {
	uint8_t data;
	switch (SSIn) {
	case SPI0:
		while (RD1B(SSI0->SR, RNE) == 0);
		data = SSI0->DR;
		while (RD1B(SSI0->SR, BSY) == 1);
		break;
	case SPI1:
		while (RD1B(SSI1->SR, RNE) == 0);
		data = SSI1->DR;
		while (RD1B(SSI1->SR, BSY) == 1);
		break;
	case SPI2:
		while (RD1B(SSI2->SR, RNE) == 0);
		data = SSI2->DR;
		while (RD1B(SSI2->SR, BSY) == 1);
		break;
	case SPI3:
		while (RD1B(SSI3->SR, RNE) == 0);
		data = SSI3->DR;
		while (RD1B(SSI3->SR, BSY) == 1);
		break;
	}

	return data;
}
void SSI_Write_String(int8_t SSIn, int8_t* string) {
	int8_t counter = 0;
	switch (SSIn) {
	case SPI0:
		while (string[counter] != '\0') {
			SSI_Write_Data(SPI0, string[counter]);
			counter++;
		}
		SSI_Write_Data(SPI0, '\0');
		break;
	case SPI1:
		while (string[counter] != '\0') {
			SSI_Write_Data(SPI1, string[counter++]);
		}
		SSI_Write_Data(SPI1, '\0');

		break;
	case SPI2:
		while (string[counter] != '\0') {
			SSI_Write_Data(SPI2, string[counter]);
			counter++;
		}
		break;
	case SPI3:
		while (string[counter] != '\0') {
			SSI_Write_Data(SPI3, string[counter]);
			counter++;
		}
		break;
	}

}

void SSI_Read_String(int8_t SSIn, int8_t* string, int8_t size) {
	int8_t counter = 0;
	int8_t chr;
	switch (SSIn) {
	case SPI0:
		while ((chr = SSI_Read_Data(SPI0)) != '\0') {
			string[counter++] = chr;
		}
		string[counter] = '\0';
		break;
	case SPI1:
		while ((chr = SSI_Read_Data(SPI1)) != '\0') {
			string[counter++] = chr;
		}
		string[counter] = '\0';
		break;
	case SPI2:
		while ((chr = SSI_Read_Data(SPI2)) != '\0') {
			string[counter++] = chr;
		}
		string[counter] = '\0';
		break;
	case SPI3:
		while ((chr = SSI_Read_Data(SPI3)) != '\0') {
			string[counter++] = chr;
		}
		string[counter] = '\0';
		break;
	}

}

