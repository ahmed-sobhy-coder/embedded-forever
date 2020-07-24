#include "lcd.h"
static uint32_t pos = 0;
static uint8_t line = 1;
void LCD_SetDis(uint8_t dis, uint8_t cr, uint8_t bl)
{
	if (dis == 0 && cr == 0 && bl == 0) //Display off, cursor off, blink off
	{
		LCD_SendCmd(0x08);
	}
	else if (dis == 0 && cr == 1 && bl == 0)//Display off, cursor on, blink off
	{
		LCD_SendCmd(0x0A);
	}
	else if (dis == 1 && cr == 0 && bl == 0)//Display on, cursor off, blink off
	{
		LCD_SendCmd(0x0C);
	}
	else if (dis == 1 && cr == 1 && bl == 0)//Display on, cursor on, blink off
	{
		LCD_SendCmd(0x0E);
	}
	else if (dis == 1 && cr == 1 && bl == 1)//Display on, cursor on, blink on
	{
		LCD_SendCmd(0x0F);
	}
	usDelay(37);//instruction execution time  
}
void LCD_SetInterface(uint8_t noWires, uint8_t noLines, uint8_t segNoRows) {
	switch (noWires) {
	case 4:
		switch (noLines) {
		case 1:
			switch (segNoRows) {
			case 8:
				LCD_SendCmd(0x20);//Set 4-bit, 1 line, 5x8 dots
				break;
			case 11:
				LCD_SendCmd(0x24);//Set 4-bit, 1 line, 5x11 dots
				break;
			}
			break;
		case 2:
			LCD_SendCmd(0x28);//Set 4-bit, 2 line, 5x8 dots
		}
	break;
	case 8:
		switch (noLines) {
		case 1:
			switch (segNoRows) {
			case 8:
				LCD_SendCmd(0x30);//Set 8-bit, 1 line, 5x8 dots
				break;
			case 11:
				LCD_SendCmd(0x34);//Set 8-bit, 1 line, 5x11 dots
				break;
			}
			break;
		case 2:
			LCD_SendCmd(0x38);//Set 8-bit, 2 line, 5x8 dots
			break;
		}
	}
	usDelay(37);//instruction execution time  
}

void LCD_ReturnHome(void){
 LCD_SendCmd(0x02);// return to home command, it returns the everyting to ddram address 0
	                //it returns string to line 1 postion 0
 usDelay(1520); //instruction executu=ion time 
}
void LCD_ShiftCurs(uint8_t dir)
{
    switch(dir)
    {
			case 1: //shift cursor right
				 LCD_SendCmd(0x14);
				break;
			case 2:  //shift cursor left
				  LCD_SendCmd(0x10); //command to shift cursor left
				break;
			default:
					LCD_SendCmd(0x14);//command to shift cursor right
		}
	usDelay(37);//isntruction executuion time 
}
/*force cursor to the beginning of line 1 or to */
void LCD_ForceCursline(uint8_t line)
{
	switch(line)
	{ 
		case 1: //case line 1
			LCD_SendCmd(0x80); // force cursor to the begining of the first line
		  break;
		case 2: //case line 2
      LCD_SendCmd(0xC0); // force cursor to the begining of the second line
			break;
	}			
	usDelay(37);//instruction execution time
}
void LCD_Init(void)
{
#if LCD_4BIT_INTERFACE==1 //4-bit LCD interface
	msDelay(40);//wait until the initialization ends	
   LCD_SetInterface(4,2,8);	//Set 4-bit, 2 line, 5x8 dots
	LCD_SetDis(1, 1, 0);//Display on, cursor on, blink on
	LCD_Clr();
#else //8-bit LCD interface
	msDelay(40);//wait until the initialization ends
	LCD_SendCmd(LCD_SET_8BITS_2LINE_5X8DOTS); //set 8bit interface,2 lines ,font 5X8
	usDelay(37);//instruction execution time 
	LCD_SendCmd(LCD_SET_8BITS_2LINE_5X8DOTS); //set 8bit interface,2 lines ,font 5X8
	usDelay(37);//instruction execution time 
	LCD_SendCmd(LCD_CLEAR_SCREEN);//write space characters to all DDRAM addresses
	usDelay(15200);//instruction execution time 
	LCD_SendCmd(LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON);//dispaly char,activate the cursor and make it blink 
	usDelay(37);//instruction execution time 

#endif
}

static void LCD_Enable(void)
{
#if LCD_4BIT_INTERFACE==1 //4-bit LCD interface
	ST1B(LCD_GPIO->DATA, LCD_E);//enable lcd to send data/command
	usDelay(1);   // TPWM'Enable pulse width'(460 nS),
					//'Data set-up must be settled before the falling edge
					//of the enable pusle TDSW(10 nS)  
	CLR1B(LCD_GPIO->DATA, LCD_E);//disable enable signal,the ,MCU now is storing 
							 //the data/command and the data must be available
							 //for a certain time after TPWM known as TH or THD
	usDelay(1);   //implement 'Data hold time'TH(10 nS)

#else //8-bit LCD interface
	//Generate a pulse on the LCD Enable  pin
	ST1B(GPIOA->DATA, LCD_E);//enable lcd to send data/command
	usDelay(460);//delay to
	CLR1B(GPIOA->DATA, LCD_E);
	usDelay(740);
#endif
}
void LCD_SendCmd(uint8_t cmd)
{
#if LCD_4BIT_INTERFACE==1 //4-bit LCD interface
	CLR1B(LCD_GPIO->DATA, LCD_RS);//select instruction register (IR) 
	CLR1B(LCD_GPIO->DATA, LCD_RW);//Write to lcd
	STHNVIHNR(LCD_GPIO->DATA, cmd);//send the upper nipple

	LCD_Enable();//enable the lcd to latch the information presented in the data bus
	STLNVIHNR(LCD_GPIO->DATA, cmd); //send the lower nipple
	LCD_Enable();//enable the lcd to latch the information presented in the data bus
#else //8-bit LCD interface
	CLR1B(GPIOA->DATA, LCD_REGISTER_SELECT);//select instruction register (IR) 
	CLR1B(GPIOA->DATA, LCD_RW);//Write to lcd
	STV(LCD_GPIO->DATA, cmd);//send command
	LCD_Enable();//enable the lcd to latch the information presented in the data bus
#endif
}
void LCD_SendChr(int8_t data)
{
#if LCD_4BIT_INTERFACE==1 //4-bit LCD interface
	ST1B(LCD_GPIO->DATA, LCD_RS);//select data register (DR)
	CLR1B(LCD_GPIO->DATA, LCD_RW);//Write to lcd

	STHNVIHNR(LCD_GPIO->DATA, data);//send the upper nipple
	LCD_Enable();//enable the lcd to latch the information presented in the data bus
	STLNVIHNR(LCD_GPIO->DATA, data); //send the lower nipple
	LCD_Enable();//enable the lcd to latch the information presented in the data bus
	usDelay(50);
#else //8-bit LCD interface
	ST1B(GPIOA->DATA, LCD_RS);//select data register (DR)
	CLR1B(GPIOA->DATA, LCD_RW);//Write to lcd
	STV(LCD_GPIO->DATA, data);//send char
	LCD_Enable();//enable the lcd to latch the information presented in the data bus
#endif
}

void LCD_Clr(void)
{
	LCD_SendCmd(0X1);//write space characters to all DDRAM addresses
	usDelay(15200);//instruction execution time  
	pos = 0;  //make the next int8_tposition 0
	line = 1; //make the next line is line  1
}
void LCD_SendStr(int8_t* str)
{
	uint8_t count = 0; //it is used as an index to the next int8_tto be sent
	while (str[count] != '\0') //loop until all chars are sent to LCD
	{
		if ((pos % 16) == 0 && (pos > 0))
		{
			if (line == 1)
			{
				line = 2;
				LCD_GoToXY(0, 2);
			}
			else
			{
				line = 1;
				msDelay(2000);
				LCD_Clr();
				msDelay(500);
			}

		}
		LCD_SendChr(str[count]);
		count++;
		pos++;
	}
}


void LCD_GoToXY(uint8_t col, uint8_t row)
{
    pos=0;
	line=0;
	switch (row)
	{
	case 1:
		LCD_SendCmd((0x80 | LIN1_POS0) + col);//0x80 it is a command to set ddram address,
										 //row is the address of the first location in the row
		usDelay(37);//command execution time 

		break;
	case 2:
		LCD_SendCmd((0x80 | LIN2_POS0) + col);//0x80 it is a command to set ddram address,
		usDelay(37);//command execution time 

		break;                                   //row is the address of the second location in the row
	}
}

void LCD_SendChrXY(uint8_t col, uint8_t row, int8_t chr)
{
     line=0 ;
	 pos=0;
	switch (row)
	{
	case LINE1:
		LCD_SendCmd((0x80 | LIN1_POS0) + col);//0x80 it is a command to set ddram address,
										 //row is the address of the first location in the row
		usDelay(37);//command execution time 

		break;
	case LINE2:
		LCD_SendCmd((0x80 | LIN2_POS0) + col);//0x80 it is a command to set ddram address,
										 //row is the address of the second location in the row
		usDelay(37);//command execution time 
		break;
	}
	LCD_SendChr(chr);//send int8_tto lcd
}
void LCD_SendStrXY(uint8_t col, uint8_t row, int8_t* str)
{
    line=0;
	pos=0;
	switch (row)
	{
	case 1:
		LCD_SendCmd((0x80 | LIN1_POS0) + col);//0x80 it is a command to set ddram address,
										 //row is the address of the first location in the row
		usDelay(37);//command execution time 
		break;
	case 2:
		LCD_SendCmd((0x80 | LIN2_POS0) + col);//0x80 it is a command to set ddram address,
										 //row is the address of the second location in the row
		usDelay(37);//command execution time 
		break;
	}
	LCD_SendStr(str);//send string to lcd
}
void LCD_ShiftDisplay(uint8_t dir)
{
  switch(dir)
  {
		case 1:	
			LCD_SendCmd(0x1C); //shift the entire display right
			break;
		case 2:	
			LCD_SendCmd(0x18); //shift the entire display left
			break;
		default:
			LCD_SendCmd(0x1C); //shift the entire display right
	}
	usDelay(37);//command execution time 
}

void LCD_SendStrMid(uint8_t row, int8_t* str)
{
	uint8_t noDot1L = 16;//no of dots in one line
	uint8_t strNoDot = strLen(str); //no of dots string needs
	uint8_t mid = (noDot1L - strNoDot) / 2; //the first int8_tin string will be printed in the 
										 //dot which has position mid
    line=0;
	pos=0;
	switch (row)
	{
	case 1:
		LCD_SendCmd((0x80 | LIN1_POS0) + mid);//0x80 it is a command to set ddram address,
										 //row is the address of the first location in the row
		usDelay(37);//command execution time 

		break;
	case 2:
		LCD_SendCmd((0x80 | LIN2_POS0) + mid);//0x80 it is a command to set ddram address,
										 //row is the address of the second location in the row
		usDelay(37);//command execution time 

		break;
	}
	LCD_SendStr(str);//send string to lcd
}
void LCD_Print(int8_t* str)
{
	uint8_t noDot1L = 16;//no of dots in one line
	uint8_t noDotAL = 32; //no of dots in all lines
	uint8_t strNoDot = strLen(str); //no of dots string needs
	uint8_t cnt = 0;//counter
	if (strNoDot > noDotAL)//if the length of string is greater than 32
	{
		LCD_Print("sorry,string is too long,35 dot ");
		LCD_SendStr(intToStr(strNoDot));//convert string length to integer
	}
	else
	{
		while ((cnt < noDotAL) && (cnt < strNoDot))
		{
			if (cnt == noDot1L)//is the first line is full
			{
				LCD_GoToXY(0, 2);//go to next line 
			}
			LCD_SendChr(*str++);//send string
			cnt++;//go to the next dot matrix 
		}
	}
}

void LCD_SetCGRAM(const int8_t* userChars)
{
	uint8_t NoPatrn = 8; //number of custom chars is 8
	uint8_t noBytPatrn = 8;//each pattern consist of 8 bytes/rows
	uint8_t noBytCGRAM = NoPatrn * noBytPatrn; //number of bytes in CGRAM = 4x8 = 32
	uint8_t cnt = 0;		//is a counter
	LCD_SendCmd(0x40);  //set CGRAM address
	usDelay(37);//command execution time 
	while (cnt < noBytCGRAM)//allocate each location in CGRAM
	{
		LCD_SendChr(userChars[cnt]);   //send data to CGRAM
		cnt++;
	}
	LCD_SendCmd(0x80);//Set DDRAM address to store data from DR
	usDelay(37);//command execution time 
}
