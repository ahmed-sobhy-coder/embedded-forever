#ifndef _CLOCK_H__
#define _CLOCK_H__
#include "bit.h"
#include "tm4c123io.h"
#define MOSC           0
#define XTAL           6
#define USESYSDIV      22
#define MOSC           0
#define SEXTEEN_MHZ    0x15
#define OSCSRC2        4
#define BYPASS2        11
#define MOSCDIS        0
#define OSCSRC         4
#define BYPASS         11
#define SYSDIV         23
#define SYSDIV2        23
#define DIV_1          0
#define DIV_2          1
#define DIV_3          2
#define DIV_4          3
#define DIV_5          4
#define DIV_6          5
#define DIV_7          6
#define DIV_8          7
#define DIV_9          8
#define DIV_10         9
#define DIV_11         10
#define DIV_12         11
#define DIV_13         12
#define DIV_14         13
#define DIV_15         14
#define DIV_16         15
#define PWRDN          13
#define PWRDN2         13
#define MOSC_16MHZ        16
#define MOSC_8MHZ         8
#define MOSC_4MHZ         4
#define MOSC_2MHZ         2
#define MOSC_1MHZ         1 
#define PIOSC_16MHZ       16
#define PIOSC_8MHZ        8
#define PIOSC_4MHZ        4
#define PIOSC_2MHZ        2
#define PIOSC_1MHZ        1 
#define PIOSC          1
#define CLK_80MHZ 80
#define CLK_50MHZ 50
#define CLK_40MHZ 40
#define CLK_25MHZ 25
#define CLK_20MHZ 20
#define CLK_16MHZ 16
#define CLK_10MHZ 10
#define CLK_8MHZ  8
#define CLK_5MHZ  5
#define CLK_4MHZ  4

#define CVAL     0
#define MOSCIM   1
#define MOFRIS   3
#define USERCC2  31
#define PLLRIS   6
#define DIV400   30
#define SYSDIV2LSB 22
#define MOSC_XTAL_FREQ    16
void PIOSC_Init(uint8_t PIOSC_freq);
void MOSC_Init(uint8_t MOSC_freq);
void PLL_init(uint8_t freq);
void HYOSC_Init(void);
#endif

