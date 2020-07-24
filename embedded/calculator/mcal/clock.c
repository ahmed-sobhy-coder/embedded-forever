#include "clock.h"
void MOSC_Init(uint8_t freq){
	uint8_t divisor;
	divisor = (MOSC_XTAL_FREQ/freq) -1;
	ST1B(SYSCTL->RCC,BYPASS);// the system clock is derived from clock source
  CLR1B(SYSCTL->RCC,MOSCDIS); //enable MIOSC
  STV2BI(SYSCTL->RCC,OSCSRC,MOSC);//choose MOSC
	ST1B(SYSCTL->RCC,PWRDN);//PLL power down
	STV5BI(SYSCTL->RCC,XTAL,SEXTEEN_MHZ);//MOSC is 16 MHZ
	ST1B(SYSCTL->MOSCCTL,CVAL); //enable MOSC verification circuit
	ST1B(SYSCTL->MOSCCTL,MOSCIM); //enable MOSC verification circuit 
  if(freq==16) CLR1B(SYSCTL->RCC,USESYSDIV);
	else if((freq>1)&&(freq<16))
  {
	  CLR1B(SYSCTL->RCC,USESYSDIV);	
		STV4BI(SYSCTL->RCC,SYSDIV,divisor);

	}
	while(RD1B(SYSCTL->RIS,MOFRIS)==1);//MOSC failure
}

void PIOSC_Init(uint8_t freq){
	uint8_t divisor;
	divisor = (MOSC_XTAL_FREQ/freq) -1;
	ST1B(SYSCTL->RCC,BYPASS);/* disable PLL and enable clock source*/
	ST1B(SYSCTL->RCC,MOSCDIS); //enable PIOSC
  STV2BI(SYSCTL->RCC,OSCSRC,PIOSC);/* choose PIOSC*/
	ST1B(SYSCTL->RCC,PWRDN);/* PLL power down*/
	 if(freq==16) CLR1B(SYSCTL->RCC,USESYSDIV);
	else if((freq>1)&&(freq<16))
  {
	  CLR1B(SYSCTL->RCC,USESYSDIV);	
		STV4BI(SYSCTL->RCC,SYSDIV,divisor);
	}
}

void PLL_init(uint8_t freq){
	uint8_t divisor = 400/freq ;
	uint8_t sysdiv2=((divisor-1)>>1); //to initialized SYSDIV2
	uint8_t sysdiv2lsb = ((divisor-1)&0x1); //to initialize SYSDIV2LSB
	/* MOSC init*/
  ST1B(SYSCTL->RCC2,USERCC2);	//USERCC2 RCC2 overrides RCC fields
	ST1B(SYSCTL->RCC2,BYPASS2);/* the system clock is derived from clock source*/
	CLR1B(SYSCTL->RCC,USESYSDIV);//the system clock source is undivided
	CLR1B(SYSCTL->RCC,MOSCDIS); //enable MIOSC
  STV3BI(SYSCTL->RCC2,OSCSRC2,MOSC);/* choose MOSC*/
 	STV5BI(SYSCTL->RCC,XTAL,SEXTEEN_MHZ);/* MOSC is 16 MHZ*/
 	 /* PLL init*/
	CLR1B(SYSCTL->RCC2,PWRDN2);/* enable PLL */
  ST1B(SYSCTL->RCC2,DIV400); //400MHZ
	STV6BI(SYSCTL->RCC2,SYSDIV2,sysdiv2);// 400/5 ==>80
	STV1BI(SYSCTL->RCC2,SYSDIV2LSB,sysdiv2lsb);
	ST1B(SYSCTL->RCC,USESYSDIV);//the system clock source is undivided
	while(RD1B(SYSCTL->RIS,PLLRIS)==0);
	CLR1B(SYSCTL->RCC2,BYPASS2);/* the system clock is derived by PLL */

}
