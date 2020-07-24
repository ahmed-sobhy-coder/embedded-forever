#ifndef __SSI_H__
#define __SSI_H__
#include "stdint.h"
#include "bit.h"
#include "tm4c123io.h"

#define SYS_CLOCK  0
#define SSI0CLK    PA2
#define SSI0FSS    PA3
#define SSI0RX     PA4
#define SSI0TX     PA5
 
#define SSI1CLK    PF2
#define SSI1FSS    PF3
#define SSI1RX     PF0
#define SSI1TX     PF1

#define SSI2CLK    PB4
#define SSI2FSS    PB5
#define SSI2RX     PB6
#define SSI2TX     PB7

#define SSI3CLK    PD0
#define SSI3FSS    PD1
#define SSI3RX     PD2
#define SSI3TX     PD3

#define CPSDVSR     0
#define SSI0_MODE   2
#define SSE         1
#define MS          2
#define SCR         8
#define DSS         0
#define FRF         4
#define SPO         6
#define SPH         7
#define TNF         1
#define BSY         4       
#define RNE         2
#define SPI0   0
#define SPI1   1
#define SPI2   2
#define SPI3   3
#define MASTER 0
#define SLAVE 1
void SSI_Init(uint8_t SSIn, uint8_t mode);
void SSI_Write_Data(uint8_t SSIn, uint8_t data) ;
uint8_t SSI_Read_Data(uint8_t SSIn) ;
void SSI_Read_String(int8_t SSIn, int8_t* string, int8_t size);
void SSI_Write_String(int8_t SSIn, int8_t* string) ;

#endif
