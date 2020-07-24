#ifndef __tm4c123io_H__
#define __tm4c123io_H__

#include "stdint.h"
#include "bit.h"
#include "TM4C123GH6PM.H"
#define BIT0                 0
#define BIT1                 1
#define BIT2                 2
#define BIT3                 3
#define BIT4                 4
#define BIT5                 5
#define BIT6                 6
#define BIT7                 7
#define BIT8                 8

#define PORTA               0
#define PORTB               1
#define PORTC               2
#define PORTD               3
#define PORTE               4
#define PORTF               5


#define PA0               0
#define PA1               1
#define PA2               2
#define PA3               3
#define PA4               4
#define PA5               5
#define PA6               6
#define PA7               7

#define PB0               0U
#define PB1               1U
#define PB2               2U
#define PB3               3U
#define PB4               4U
#define PB5               5U
#define PB6               6U
#define PB7               7U

#define PC4               4U
#define PC5               5U
#define PC6               6U
#define PC7               7U

#define PD0               0U
#define PD1               1U
#define PD2               2U
#define PD3               3U
#define PD6               6U
#define PD7               7U

#define PE0               0U
#define PE1               1U
#define PE2               2U
#define PE3               3U
#define PE4               4U
#define PE5               5U

#define PF0               0U
#define PF1               1U
#define PF2               2U
#define PF3               3U
#define PF4               4U

#define  UNLOCK           0x4C4F434B
#define OUTPUT       1
#define INPULUP  2
#define INPULDN  3
#define HIGH        1
#define LOW        0
#define OFF                 0
#define ON                  1
#define GPIOA_ALL_BITS     0xFC
#define GPIOB_ALL_BITS     0xFF
#define GPIOC_ALL_BITS     0xF0
#define GPIOD_ALL_BITS     0xCF
#define GPIOE_ALL_BITS     0x3E
#define GPIOF_ALL_BITS     0x1F


#define GPIOB_LOWER_NIBBLE_BITS  0x0F
#define GPIOD_LOWER_NIBBLE_BITS  0x0F
#define GPIOF_LOWER_NIBBLE_BITS  0x0F

#define GPIOA_HIGHER_NIBBLE_BITS  0xF0
#define GPIOB_HIGHER_NIBBLE_BITS  0xF0
#define GPIOC_HIGHER_NIBBLE_BITS  0xF0

#define  UNLOCK           0x4C4F434B
void GPIO_PinInit(uint8_t port, uint8_t bits, uint8_t direction);
void GPIO_PinOut(uint8_t port, uint8_t bits, uint8_t volt);
void GPIO_PortInit(uint8_t port, uint8_t direction);
void GPIO_PortOutput(uint8_t port, uint8_t volt) ;
uint8_t GPIO_PinRead(uint8_t port, uint8_t bits) ;
void GPIO_NibblePinsOut(uint8_t port, uint8_t startPin,uint8_t value);

#endif
