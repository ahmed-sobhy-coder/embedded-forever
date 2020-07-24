#include "lcdapps.h"
extern int8_t userChars1[64];
extern int8_t userChars2[64];
extern int8_t userChars3[64];
extern int8_t userChars4[64];
void LCD_LoadingShape(void)
{
	LCD_SetCGRAM(userChars1);
	LCD_SendStrMid(1,"loading");
	uint8_t count=0;
		for(count=0;count<16;count++)
		{		
			LCD_SendChrXY(count,2,2);
					msDelay(500);
		}
}
void LCD_CloseDoor(void)
{
LCD_SetCGRAM(userChars1);
  	uint16_t count=0;
	  for(count=0;count<16;count++)
    {
		   LCD_SendChrXY(count,1,2);//window shape
			 LCD_SendChrXY(count,2,2);//window shap
			 msDelay(200);
		}
}
void LCD_OpenDoor(void)
{
    uint16_t count=0;
	LCD_SetCGRAM(userChars1);
  for(count=0;count<8;count++)
    {
		   LCD_SendChrXY(8+count,1,3);//window shape				
		   LCD_SendChrXY(8+count,2,3);//window shap
			LCD_SendChrXY(7-count,1,3);//window shape
			 LCD_SendChrXY(7-count,2,3);//window shap

			msDelay(200);
		}
}
void LCD_Snake1(void)
{
	int8_t count1 = 0, count2 = 0;
	uint8_t noSpaces = 7;
	uint8_t flag1 = 1, flag2 = 0;
	uint8_t lstIndx = 0;
	while (1)
	{
		for (count1 = 0; count1 < 16; count1++)
		{
			if (flag2 == 1)
			{
				LCD_SendChrXY(count1, 2, 2);
				msDelay(100);
				LCD_SendChrXY(count1, 1, 3);
				msDelay(1);
				noSpaces = 7;
				lstIndx = 0;
				flag1 = 1;
				flag2 = 0;
			}
			if (count1 > 0)
			{
				LCD_SendChrXY(count1, 2, 4);
				msDelay(1);
				LCD_SendChrXY(count1 - 1, 2, 2);

			}
			msDelay(500);
			if (count1 > 7)
			{
				while (lstIndx < count1 - noSpaces)
				{
					LCD_SendChrXY(lstIndx, 2, 3);
					msDelay(1);
					lstIndx++;

				}
				noSpaces--;
			}
		}
		for (count2 = count1 - 1; count2 >= 0; count2--)
		{
			if (flag1 == 1)
			{
				lstIndx = count2;
				LCD_SendChrXY(count2, 1, 2);
				msDelay(100);
				LCD_SendChrXY(count2, 2, 3);
				msDelay(1);
				noSpaces = 7;
				msDelay(1);
				flag1 = 0;
				flag2 = 1;
				continue;
			}
			if (count2 < 15)
			{
				LCD_SendChrXY(count2, 1, 5);
				msDelay(1);
				LCD_SendChrXY(count2 + 1, 1, 2);

			}
			msDelay(500);
			if (count2 < 8)
			{
				while (lstIndx > count2 + noSpaces)
				{
					LCD_SendChrXY(lstIndx, 1, 3);
					msDelay(1);
					lstIndx--;

				}
				noSpaces--;
			}
		}
	}
}
void LCD_MovRevse(void)
{
	LCD_SetCGRAM(userChars1);
	uint8_t count;
	for (count = 0; count < 16; count++)
	{
		LCD_SendChrXY(15 - count, 1, 2);
		LCD_SendChrXY(count, 2, 2);
		msDelay(200);
	}
}
void LCD_Snake2(void)
{
	int8_t count1 = 0, count2 = 0;
	int8_t lstIndx1 = -1;//initialization of 
	//the index of the last segment of the snake on line 1 
	int8_t lstIndx2 = 0;//initialization of 
	//the index of the last segment of the snake on line 2
	LCD_SetCGRAM(userChars1);
	while (1)
	{
		lstIndx2 = 0;
		for (count2 = 0; count2 < 16; count2++)
		{

			if (lstIndx1 > -1)//check if there is a body still remains in the second line
			{
				LCD_SendChrXY(lstIndx1--, 1, 3);//decrease the body, by increasing nomber of spaces
			}
			if (count2 == 0) 
			{
				LCD_SendChrXY(count2, 2, 4);//start by printing the head in the second line
			}
			else {
				LCD_SendChrXY(count2, 2, 4);
				LCD_SendChrXY(count2 - 1, 2, 2);
				msDelay(300);
				if (count2 >= 7)
				{
					LCD_SendChrXY(lstIndx2++, 2, 3);//print space	
				}

			}
		}
		LCD_SendChrXY(count2 - 1, 2, 2); //print the body in the first line
		LCD_SendChrXY(count2 - 1, 1, 5); //print head in the first line
		for (count1 = count2 - 1, lstIndx1 = count1; count1 > -1; count1--)
		{
			if (lstIndx2 < 16) {
				LCD_SendChrXY(lstIndx2++, 2, 3);
			}
			if (count1 < 15)
			{
				LCD_SendChrXY(count1, 1, 5);
				LCD_SendChrXY(count1 + 1, 1, 2);
				msDelay(300);
				if (count1 < 9)
				{
					LCD_SendChrXY(lstIndx1--, 1, 3);
				}
			}

		}
		LCD_SendChrXY(count1 + 1, 1, 2);//print the
		LCD_SendChrXY(count1 + 1, 2, 4);//print the head of line 1
	}
}
void LCD_SwimUp2LGrad(void)
{  
	 int8_t count1=0,count2=0;// count1 is for shapes,count2 is for cols
    	int8_t row1=1,row2=2;
	LCD_SetCGRAM(userChars3);
	for(count1=0;count1<8;count1++) // loop for shapes
   {
		 
			   for(count2=0;count2<16;count2++) // loop for rows
         {
					   
					   LCD_SendChrXY(count2,row1,count1);
					 	 LCD_SendChrXY(count2,row2,count1);
						  msDelay(50);
				 }
	 }
}
void LCD_SwimDwn2LGrad(void)
{  
	 int8_t count1=0,count2=0;// count1 is for shapes,count2 is for cols
    	int8_t row1=1,row2=2;
	LCD_SetCGRAM(userChars2);
	for(count1=0;count1<8;count1++) // loop for shapes
   {
		 
			   for(count2=0;count2<16;count2++) // loop for rows
         {
					   
					   LCD_SendChrXY(count2,row1,count1);
					 	 LCD_SendChrXY(count2,row2,count1);
						  msDelay(50);
				 }
	 }
}
void LCD_SwimDwn1LGrad(uint8_t row)
{  
	
	 int8_t count1=0,count2=0;// count1 is for shapes,count2 is for cols
	LCD_SetCGRAM(userChars2);
	
	for(count1=0;count1<8;count1++) // loop for shapes
   {
		 
			   for(count2=0;count2<16;count2++) // loop for rows
         {
					   
					 	 LCD_SendChrXY(count2,row,count1);
						  msDelay(50);
				 }
				 
	 }
	 			msDelay(50);
}
void LCD_SwimUp1LGrad(uint8_t row)
{  
	
	 int8_t count1=0,count2=0;// count1 is for shapes,count2 is for cols
	LCD_SetCGRAM(userChars3);
	for(count1=0;count1<8;count1++) // loop for shapes
   {
		 
			   for(count2=0;count2<16;count2++) // loop for rows
         {
					   
					 	 LCD_SendChrXY(count2,row,count1);
						  msDelay(50);
				 }
				 
	 }
	 			msDelay(50);
}
void LCD_Swim2LinDwnupGrad(void)
{
	 int8_t count1=0,count2=0;// count1 is for shapes,count2 is for cols
    	int8_t row1=1,row2=2;
	LCD_SetCGRAM(userChars2);
	for(count1=0;count1<8;count1++) // loop for shapes
   {
		 
			   for(count2=0;count2<16;count2++) // loop for rows
         {
					   
					   LCD_SendChrXY(count2,row1,count1);
						  msDelay(50);
				 }
	 }
	 						  msDelay(50);
LCD_SetCGRAM(userChars3);
	 	for(count1=0;count1<8;count1++) // loop for shapes
   {
		 
			   for(count2=0;count2<16;count2++) // loop for rows
         {
					 	 LCD_SendChrXY(count2,row2,count1);
						  msDelay(50);
				 }
	 }
	  msDelay(50);
}
void LCD_Swim2LinDwnup(void)
{
	 int8_t count1=0,count2=0;// count1 is for shapes,count2 is for cols
    	int8_t row1=1,row2=2;
	LCD_SetCGRAM(userChars2);
	for(count1=0;count1<8;count1++) // loop for shapes
   {
		 
			   for(count2=0;count2<16;count2++) // loop for rows
         {
					   
					   LCD_SendChrXY(count2,row1,count1);
						  
				 }
				 msDelay(50);
	 }
	 						  msDelay(50);
LCD_SetCGRAM(userChars3);
	 	for(count1=0;count1<8;count1++) // loop for shapes
   {
		 
			   for(count2=0;count2<16;count2++) // loop for rows
         {
					 	 LCD_SendChrXY(count2,row2,count1);
						  
				 }
				 msDelay(50);
	 }
	  
}
void LCD_MusicShape(void)
{
    LCD_SetCGRAM(userChars3);
		int8_t count1 = 0, count2 = 0;
	int8_t lstIndx1 = -1;//initialization of 
	//the index of the last segment of the snake on line 1 
	int8_t lstIndx2 = 0;//initialization of 
	//the index of the last segment of the snake on line 2
	int8_t count=3;
	while (count)
	{
		lstIndx2 = 0;
		for (count2 = 0; count2 < 16; count2++)
		{

			if (lstIndx1 > -1)//check if there is a body still remains in the second line
			{
				LCD_SendChrXY(lstIndx1--, 1, 3);//decrease the body, by increasing nomber of spaces
			}
			if (count2 == 0) 
			{
				LCD_SendChrXY(count2, 2, 4);//start by printing the head in the second line
			}
			else {
				LCD_SendChrXY(count2, 2, 4);
				LCD_SendChrXY(count2 - 1, 2, 2);
				msDelay(100);
				if (count2 >= 7)
				{
					LCD_SendChrXY(lstIndx2++, 2, 3);//print space	
				}

			}
		}
		LCD_SendChrXY(count2 - 1, 2, 2); //print the body in the first line
		LCD_SendChrXY(count2 - 1, 1, 5); //print head in the first line
		for (count1 = count2 - 1, lstIndx1 = count1; count1 > -1; count1--)
		{
			if (lstIndx2 < 16) {
				LCD_SendChrXY(lstIndx2++, 2, 3);
			}
			if (count1 < 15)
			{
				LCD_SendChrXY(count1, 1, 5);
				LCD_SendChrXY(count1 + 1, 1, 2);
				msDelay(100);
				if (count1 < 9)
				{
					LCD_SendChrXY(lstIndx1--, 1, 3);
				}
			}

		}
		LCD_SendChrXY(count1 + 1, 1, 2);//print the
		LCD_SendChrXY(count1 + 1, 2, 4);//print the head of line 1
		count--;
	}
}
void LCD_Loading2(void)
{
	LCD_SendStrMid(1,"loading");
	uint8_t count1=0,count2;
	LCD_SetCGRAM(userChars4);
		for(count1=0;count1<16;count1++)
		{		
			for(count2=0;count2<5;count2++)
      {
			  LCD_SendChrXY(count1,2,count2);
				msDelay(50);
			}
		}
}
