#ifndef _PWM_H__
#define _PWM_H__

#include "bit.h"
#include "tm4c123io.h"
#include "sysTick.h"
#define M0PWM0 PB6 
#define M0PWM1 PB7 
#define M0PWM2 PB4 
#define M0PWM3 PB5 
#define M0PWM4 PE4 
#define M0PWM5 PE5 
#define M0PWM6 PC4  //or PD0
#define M0PWM7 PC5  //or PD1

#define M1PWM0 PD0 
#define M1PWM1 PD1 
#define M1PWM2 PA6 
#define M1PWM3 PA7 

#define M1PWM4 PF0 
#define M1PWM5 PF1 

#define M1PWM6 PF2
#define M1PWM7 PF3 

#define LEFT_ALIGN_MODE    0
#define RIGHT_ALIGN_MODE   1
#define CENTER_ALIGN_MODE  2

#include "pwm.h"
#include "clock.h"
#define  USEPWMDIV   20
#define  PWMDIV     17

#define  DIV2        0
#define  DIV4        1
#define  DIV8        2
#define  DIV16       3
#define  DIV32       4
#define  DIV64       5


#define  M1PWM4      PF0
#define  M1PWM5      PF1
#define  PWM_MODE_MODULE0    0x4u
#define  PWM_MODE_MODULE1    0x5u
#define PWM_MOD0      0
#define PWM_MOD1      1
#define    ENGEN    0 //enable generator

#define ACTZERO       0
#define ACTLOAD       2
#define ACTCMPAU      4
#define ACTCMPAD      6
#define ACTCMPBU      8
#define ACTCMPBD      10

#define DONOTHING    0x0
#define INVERTPWMA   0x1 
#define PWMALOW      0x2
#define PWMAHIGH     0x3
#define INVERTPWMB   0x1 
#define PWMBLOW      0x2
#define PWMBHIGH     0x3
#define MODE           1
#define DOWNCOUNT      0
#define UPDOWNCOUNT    1
#define PWM0EN         0
#define PWM1EN         1
#define PWM2EN         2
#define PWM3EN         3
#define PWM4EN         4
#define PWM5EN         5
#define PWM6EN         6
#define PWM7EN         7

#define ENUPD0                  0
#define ENUPD1                  2
#define ENUPD2                  4
#define ENUPD3                  6
#define ENUPD4                  8
#define ENUPD5                  10
#define ENUPD6                  12
#define ENUPD7                  14

#define IMMEDIATE               0
#define LOCALLY_SYNCH           2
#define GLOBALY_SYNCH           3

#define PERTIMENS(CLOCK)  (1000000000/(CLOCK)) //periodic to ns 
#define PERMSTONS(PERIOD) (PERIOD*1000000) //periodic ms to ns
#define DTYOFCNTDN(DUTY)  (((float)(100-DUTY))/100) //duty of count down
#define DTYOFCNTUP(DUTY)  ((float)(DUTY)/(100)) //duty of count down
#define MOD0GEN0          0
#define MOD0GEN1          1
#define MOD0GEN2          2
#define MOD0GEN3          3
#define MOD1GEN0          4
#define MOD1GEN1          5
#define MOD1GEN2          6
#define MOD1GEN3          7

#define GLOBALSYNC0       0
#define GLOBALSYNC1       1
#define GLOBALSYNC2       2
#define GLOBALSYNC3       3

#define SYNC0             0
#define SYNC1             1
#define SYNC2             2
#define SYNC3             3

void PWM_Init(uint8_t port,uint8_t pin, uint8_t mode, uint32_t pwmFreq, float duty);
void PWM_CmpUpdate(uint8_t port,uint8_t pin, uint8_t mode, float duty) ;
void PWM_GenInit(uint8_t modGen,uint8_t modA,uint8_t modB,uint32_t pwmFreq,float dutA,float dutB);
void PWM_GenUpdate(uint8_t modGen,uint8_t modA,uint8_t modB,float dutA,float dutB) ;
void PWM_app(uint8_t port,uint8_t pin);
#endif
