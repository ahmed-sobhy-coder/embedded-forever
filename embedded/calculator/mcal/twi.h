
#ifndef __TWI_H__
#define __TWI_H__
#include "bit.h"
#include "tm4c123io.h"
#include "sysTick.h"
#include "stdint.h"
#include "sysTick.h"
#include "clock.h"
#include "RGB.h"
#define MODULE0   0
#define MODULE1   1
#define MODULE2   2
#define MODULE3   3

#define MFE       4
#define SFE       5

#define PBI2CSDL   PB3
#define PBI2CSCL   PB2

#define PAI2CSDL   PA7
#define PAI2CSCL   PA6

#define PEI2CSDL   PE5
#define PEI2CSCL   PE4

#define PDI2CSDL   PD1
#define PDI2CSCL   PD0

#define I2C_MODE   3
#define STANDARD_MODE  100000 
#define FAST_MODE      400000
#define FAST_PLUS_MODE 1000000
#define HIGH_SPEED     3300000
#define TPR           0
#define RW            0
#define OAR           0
#define I2C_DATA      0
#define BUSBSY        6
#define CMD_SINGLE_TRANSMIT  0x07
#define CMD_SINGLE_RECEIVE   0x07
#define ERROR  1
#define BUSY   0
#define DA       0

#define RREQ     0
#define TREQ     1

#define OAR2SEL  3
#define SA 1
#define MASTER 0
#define SLAVE  1
#define NON    0
void I2C_Init(uint8_t module, uint8_t mode,uint8_t setSLAVEAddress,uint32_t i2cfreq);
void I2C_MASTER_Byte_Write(uint8_t module, uint8_t slaveAddress, uint8_t data);
uint8_t I2C_SLAVE_Byte_Read(uint8_t module);
void I2C_SLAVE_Byte_Write(uint8_t module, uint8_t data);
uint8_t I2C_MASTER_Byte_Read(uint8_t module, uint8_t slaveAddress);
void SLAVE_Single_Read_Byte_App(void);
void MASTER_Single_Write_Byte_App(void);
void I2C_MASTER_Enable(uint8_t module);
void I2C_MASTER_Disable(uint8_t module);
void I2C_SLAVE_Enable(uint8_t module);
void I2C_SLAVE_Disable(uint8_t module);
#endif
