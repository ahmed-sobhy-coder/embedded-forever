#ifndef __LCD_H__
#define __LCD_H__
#include "tm4c123io.h"
#include "bit.h"
#include "systick.h"
#include "strfuncs.h"

#define LCD_4BIT_INTERFACE        1

#if (LCD_4BIT_INTERFACE==1)
    #define LCD_PORT                     PORTB
    #define LCD_GPIO                     GPIOB
    #define LCD_RS                       PB0
    #define LCD_RW                       PB1
    #define LCD_E                        PB2 //lcd enable pin
    
    #define LCD_D4                       PB4
    #define LCD_D5                       PB5
    #define LCD_D6                       PB6
    #define LCD_D7                       PB7

#else
    #define LCD_CONTROL_PORT             PORTA //lcd control PORT
    #define LCD_DATA_PORT                PORTB  //LCD DATA PORT
    #define LCD_RS                       PA5
    #define LCD_RW                       PA6
    #define LCD_E                        PA7
    
    #define LCD_D0                       PB0
    #define LCD_D1                       PB1
    #define LCD_D2                       PB2
    #define LCD_D3                       PB3
    #define LCD_D4                       PB4
    #define LCD_D5                       PB5
    #define LCD_D6                       PB6
    #define LCD_D7                       PB7
#endif

#define RIGHT              1
#define LEFT               2 
#define  LIN1_POS0   0x00 //the location of the first dot in the first line
#define  LIN2_POS0   0x40 //the location of the first dot in the second line
#define LINE1    1 //lcd line 1
#define LINE2    2 //lcd line 2
#define COLUMN1       0
#define COLUMN2       1
#define COLUMN3       2
#define COLUMN4       3
#define COLUMN5       4
#define COLUMN6       5
#define COLUMN7       6
#define COLUMN8       7
#define COLUMN9       8
#define COLUMN10      9
#define COLUMN11      10
#define COLUMN12      11
#define COLUMN13      12
#define COLUMN14      13
#define COLUMN15      14
#define COLUMN16      15

void LCD_Init(void);
void LCD_SendCmd(uint8_t cmd);
void LCD_SendStr(int8_t*str);
void LCD_SendChr(int8_t data);
void LCD_ShiftDisplay(uint8_t dir);
void LCD_GoToXY(uint8_t row,uint8_t col);
void LCD_SendStrXY(uint8_t col,uint8_t row,int8_t* str);
void LCD_SendChrXY(uint8_t col,uint8_t row,int8_t chr);
void LCD_SendStrMid(uint8_t row,int8_t* str);
void LCD_Clr(void);
void LCD_Print(int8_t* str);
void LCD_SetCGRAM(const int8_t*userChars);
void LCD_ReturnHome(void);
void LCD_ShiftCurs(uint8_t dir);
void LCD_ForceCursline(uint8_t line);
#endif
