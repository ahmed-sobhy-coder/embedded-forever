			 #include "twi.h"
extern uint32_t sysclock;
void I2C_Init(uint8_t module, uint8_t mode, uint8_t setSLAVEAddress, uint32_t i2cfreq)
{
	uint32_t divisor;
	divisor = ((sysclock) / (20 * i2cfreq)) - 1;
	switch (module)
	{
	case MODULE0:
		switch (mode)
		{
		case MASTER:
			ST1B(SYSCTL->RCGCGPIO, PORTB);//enable clock for GPIO
			ST2B(GPIOB->AFSEL, PBI2CSDL, PBI2CSCL);//this pin will not work as GPIO pin
			ST4B4MI(GPIOB->PCTL, PBI2CSDL, I2C_MODE);//this pin will be SDL
			ST4B4MI(GPIOB->PCTL, PBI2CSCL, I2C_MODE);//this pin will be SCL
			ST2B(GPIOB->DEN, PBI2CSDL, PBI2CSCL);//enable the digital function for these two pins 
			ST1B(GPIOB->ODR, PBI2CSDL);//activate open drain function on SDL pin
			ST1B(SYSCTL->RCGCI2C, MODULE0);//enable the clock for I2C module 
			ST1B(I2C0->MCR, MFE);//master device  
			STV6BI(I2C0->MTPR, TPR, divisor);//set i2c clock frequancy
			break;
		case SLAVE:
			ST1B(SYSCTL->RCGCGPIO, PORTB);//enable clock for GPIO
			ST2B(GPIOB->AFSEL, PBI2CSDL, PBI2CSCL);//this pin will not work as GPIO pin
			ST4B4MI(GPIOB->PCTL, PBI2CSDL, I2C_MODE);//this pin will be SDL
			ST4B4MI(GPIOB->PCTL, PBI2CSCL, I2C_MODE);//this pin will be SCL
			ST2B(GPIOB->DEN, PBI2CSDL, PBI2CSCL);//enable the digital function for these two pins 
			ST1B(GPIOB->ODR, PBI2CSDL);//activate open drain function on SDL pin
			ST1B(SYSCTL->RCGCI2C, MODULE0);//enable the clock for I2C module 
			ST1B(I2C0->MCR, SFE);//slave device 
    	STV7BI(I2C0->SOAR, OAR, setSLAVEAddress);//slave address
			ST1B(I2C0->SCSR, DA);//enabale the I2C slave operation
			break;
		}

		break;
	case MODULE1:
		switch (mode)
		{
		case MASTER:
			ST1B(SYSCTL->RCGCGPIO, PORTA);//enable clock for GPIO
			ST2B(GPIOA->AFSEL, PAI2CSDL, PAI2CSCL);//this pin will not work as GPIO pin
			ST4B4MI(GPIOA->PCTL, PAI2CSDL, I2C_MODE);//this pin will be SDL
			ST4B4MI(GPIOA->PCTL, PAI2CSCL, I2C_MODE);//this pin will be SCL
			ST2B(GPIOA->DEN, PAI2CSDL, PAI2CSCL);//enable the digital function for these two pins 
			ST1B(GPIOA->ODR, PAI2CSDL);//activate open drain function on SDL pin
			ST1B(SYSCTL->RCGCI2C, MODULE1);//enable the clock for I2C module 
			ST1B(I2C1->MCR, MFE);//master device  
			STV6BI(I2C1->MTPR, TPR, divisor);//set i2c clock frequancy
			break;
		case SLAVE:
			ST1B(SYSCTL->RCGCGPIO, PORTA);//enable clock for GPIO
			ST2B(GPIOA->AFSEL, PAI2CSDL, PAI2CSCL);//this pin will not work as GPIO pin
			ST4B4MI(GPIOA->PCTL, PAI2CSDL, I2C_MODE);//this pin will be SDL
			ST4B4MI(GPIOA->PCTL, PAI2CSCL, I2C_MODE);//this pin will be SCL
			ST2B(GPIOA->DEN, PAI2CSDL, PAI2CSCL);//enable the digital function for these two pins 
			ST1B(GPIOA->ODR, PAI2CSDL);//activate open drain function on SDL pin
			ST1B(SYSCTL->RCGCI2C, MODULE1);//enable the clock for I2C module 
			ST1B(I2C1->MCR, SFE);//slave device 			
		  STV7BI(I2C1->SOAR, OAR, setSLAVEAddress);//slave address
			ST1B(I2C1->SCSR, DA);//enabale the I2C slave operation
			break;
		}
		break;
	case MODULE2:
		switch (mode)
		{
		case MASTER:
			ST1B(SYSCTL->RCGCGPIO, PORTE);//enable clock for GPIO
			ST2B(GPIOE->AFSEL, PEI2CSDL, PEI2CSCL);//this pin will not work as GPIO pin
			ST4B4MI(GPIOE->PCTL, PEI2CSDL, I2C_MODE);//this pin will be SDL
			ST4B4MI(GPIOE->PCTL, PEI2CSCL, I2C_MODE);//this pin will be SCL
			ST2B(GPIOE->DEN, PEI2CSDL, PEI2CSCL);//enable the digital function for these two pins 
			ST1B(GPIOE->ODR, PEI2CSDL);//activate open drain function on SDL pin
			ST1B(SYSCTL->RCGCI2C, MODULE2);//enable the clock for I2C module 
			ST1B(I2C2->MCR, MFE);//master device  
			STV6BI(I2C2->MTPR, TPR, divisor);//set i2c clock frequancy
			break;
		case SLAVE:
			ST1B(SYSCTL->RCGCGPIO, PORTE);//enable clock for GPIO
			ST2B(GPIOE->AFSEL, PEI2CSDL, PEI2CSCL);//this pin will not work as GPIO pin
			ST4B4MI(GPIOE->PCTL, PEI2CSDL, I2C_MODE);//this pin will be SDL
			ST4B4MI(GPIOE->PCTL, PEI2CSCL, I2C_MODE);//this pin will be SCL
			ST2B(GPIOE->DEN, PEI2CSDL, PEI2CSCL);//enable the digital function for these two pins 
			ST1B(GPIOE->ODR, PEI2CSDL);//activate open drain function on SDL pin
			ST1B(SYSCTL->RCGCI2C, MODULE2);//enable the clock for I2C module 
			ST1B(I2C2->MCR, SFE);//slave device 
  		STV7BI(I2C2->SOAR, OAR, setSLAVEAddress);//slave address
			ST1B(I2C2->SCSR, DA);//enabale the I2C slave operation
			break;
		}
		break;
	case MODULE3:
		switch (mode)
		{
		case MASTER:
			ST1B(SYSCTL->RCGCGPIO, PORTD);//enable clock for GPIO
			ST2B(GPIOD->AFSEL, PDI2CSDL, PDI2CSCL);//this pin will not work as GPIO pin
			ST4B4MI(GPIOD->PCTL, PDI2CSDL, I2C_MODE);//this pin will be SDL
			ST4B4MI(GPIOD->PCTL, PDI2CSCL, I2C_MODE);//this pin will be SCL
			ST2B(GPIOD->DEN, PDI2CSDL, PDI2CSCL);//enable the digital function for these two pins 
			ST1B(GPIOD->ODR, PDI2CSDL);//activate open drain function on SDL pin
			ST1B(SYSCTL->RCGCI2C, MODULE3);//enable the clock for I2C module 
			ST1B(I2C3->MCR, MFE);//master device  
			STV6BI(I2C3->MTPR, TPR, divisor);//set i2c clock frequancy
			break;
		case SLAVE:
			ST1B(SYSCTL->RCGCGPIO, PORTD);//enable clock for GPIO
			ST2B(GPIOD->AFSEL, PDI2CSDL, PDI2CSCL);//this pin will not work as GPIO pin
			ST4B4MI(GPIOD->PCTL, PDI2CSDL, I2C_MODE);//this pin will be SDL
			ST4B4MI(GPIOD->PCTL, PDI2CSCL, I2C_MODE);//this pin will be SCL
			ST2B(GPIOD->DEN, PDI2CSDL, PDI2CSCL);//enable the digital function for these two pins 
			ST1B(GPIOD->ODR, PDI2CSDL);//activate open drain function on SDL pin
			ST1B(SYSCTL->RCGCI2C, MODULE3);//enable the clock for I2C module 
			ST1B(I2C3->MCR, SFE);//slave device 
			STV7BI(I2C3->SOAR, OAR, setSLAVEAddress);//slave address
			ST1B(I2C3->SCSR, DA);//enabale the I2C slave operation
			break;
		}
		break;
	}
}
void I2C_MASTER_Byte_Write(uint8_t module, uint8_t slaveAddress, uint8_t data)
{
	switch (module)
	{
	case MODULE0:
		while (RD1B(I2C0->MCS, BUSBSY) == 1) {};//check if the bus is busy
		CLR1B(I2C0->MSA, RW);//do write operation
		STV7BI(I2C0->MSA, SA, slaveAddress);//slave address
		STV8BI(I2C0->MDR, I2C_DATA, data);// Data to be written
		STV(I2C0->MCS, CMD_SINGLE_TRANSMIT);//start transmission,generate start and stop condition 
		while (RD1B(I2C0->MCS, BUSY) == 1);//check if the controller is busy
		while (RD1B(I2C0->MCS, ERROR) == 1) {};//check the ACH after sending address and data 
		break;
	case MODULE1:
		while (RD1B(I2C1->MCS, BUSBSY) == 1) {};//check if the bus is busy
		CLR1B(I2C1->MSA, RW);//do write operation
		STV7BI(I2C1->MSA, SA, slaveAddress);//slave address
		STV8BI(I2C1->MDR, I2C_DATA, data);// Data to be written
		STV(I2C1->MCS, CMD_SINGLE_TRANSMIT);//start transmission,generate start and stop condition 
		while (RD1B(I2C1->MCS, BUSY) == 1);//check if the controller is busy
		while (RD1B(I2C1->MCS, ERROR) == 1) {};//check the ACH after sending address and data 
		break;
	case MODULE2:
		while (RD1B(I2C2->MCS, BUSBSY) == 1) {};//check if the bus is busy
		CLR1B(I2C2->MSA, RW);//do write operation
		STV7BI(I2C2->MSA, SA, slaveAddress);//slave address
		STV8BI(I2C2->MDR, I2C_DATA, data);// Data to be written
		STV(I2C2->MCS, CMD_SINGLE_TRANSMIT);//start transmission,generate start and stop condition 
		while (RD1B(I2C2->MCS, BUSY) == 1);//check if the controller is busy
		while (RD1B(I2C2->MCS, ERROR) == 1) {};//check the ACH after sending address and data 
		break;
	case MODULE3:
		while (RD1B(I2C3->MCS, BUSBSY) == 1) {};//check if the bus is busy
		CLR1B(I2C3->MSA, RW);//do write operation
		STV7BI(I2C3->MSA, SA, slaveAddress);//slave address
		STV8BI(I2C3->MDR, I2C_DATA, data);// Data to be written
		STV(I2C3->MCS, CMD_SINGLE_TRANSMIT);//start transmission,generate start and stop condition 
		while (RD1B(I2C3->MCS, BUSY) == 1);//check if the controller is busy
		while (RD1B(I2C3->MCS, ERROR) == 1) {};//check the ACH after sending address and data 
		break;
	}
}
uint8_t I2C_SLAVE_Byte_Read(uint8_t module)
{
	uint8_t data;
	switch (module)
	{
	case MODULE0:
		while (RD1B(I2C0->SCSR, RREQ) == 0) {};
		data = (uint8_t)I2C0->SDR;
		break;
	case MODULE1:
		while (RD1B(I2C1->SCSR, RREQ) == 0) {};
		data = (uint8_t)I2C1->SDR;
		break;
	case MODULE2:
		while (RD1B(I2C2->SCSR, RREQ) == 0) {};
		data = (uint8_t)I2C2->SDR;
		break;
	case MODULE3:
		while (RD1B(I2C3->SCSR, RREQ) == 0) {};
		data = (uint8_t)I2C3->SDR;
		break;
	}
	return data;
}
uint8_t I2C_MASTER_Byte_Read(uint8_t module, uint8_t slaveAddress)
{
	uint8_t data;
	switch (module)
	{
	case MODULE0:
		ST1B(I2C0->MSA, RW);//do write operation 
		STV7BI(I2C0->MSA, SA, slaveAddress);//slave address
		while (RD1B(I2C0->MCS, BUSBSY) == 1) {};//check if the bus is busy
		STV(I2C0->MCS, CMD_SINGLE_RECEIVE);//start transmission,generate start and stop condition 
		while (RD1B(I2C0->MCS, BUSY) == 1) {};//check if the controller is busy
		while (RD1B(I2C0->MCS, ERROR) == 1) {};//check the ACH after sending address and data 
		break;
	case MODULE1:
		ST1B(I2C1->MSA, RW);//do write operation 
		STV7BI(I2C1->MSA, SA, slaveAddress);//slave address
		while (RD1B(I2C1->MCS, BUSBSY) == 1) {};//check if the bus is busy
		STV(I2C1->MCS, CMD_SINGLE_RECEIVE);//start transmission,generate start and stop condition 
		while (RD1B(I2C1->MCS, BUSY) == 1) {};//check if the controller is busy
		while (RD1B(I2C1->MCS, ERROR) == 1) {};//check the ACH after sending address and data 
		data = I2C1->MDR;
		break;
	case MODULE2:
		ST1B(I2C2->MSA, RW);//do write operation 
		STV7BI(I2C2->MSA, SA, slaveAddress);//slave address
		while (RD1B(I2C2->MCS, BUSBSY) == 1) {};//check if the bus is busy
		STV(I2C2->MCS, CMD_SINGLE_RECEIVE);//start transmission,generate start and stop condition 
		while (RD1B(I2C2->MCS, BUSY) == 1) {};//check if the controller is busy
		while (RD1B(I2C2->MCS, ERROR) == 1) {};//check the ACH after sending address and data 
		data = I2C2->MDR;
		break;
	case MODULE3:
		ST1B(I2C3->MSA, RW);//do write operation 
		STV7BI(I2C3->MSA, SA, slaveAddress);//slave address
		while (RD1B(I2C3->MCS, BUSBSY) == 1) {};//check if the bus is busy
		STV(I2C3->MCS, CMD_SINGLE_RECEIVE);//start transmission,generate start and stop condition 
		while (RD1B(I2C3->MCS, BUSY) == 1) {};//check if the controller is busy
		while (RD1B(I2C3->MCS, ERROR) == 1) {};//check the ACH after sending address and data 
		data = I2C3->MDR;
		break;
	}
	return data;
}
void I2C_SLAVE_Byte_Write(uint8_t module, uint8_t data)
{
	switch (module)
	{
	case MODULE0:
		while (RD1B(I2C0->SCSR, TREQ) == 0) {};
		I2C0->SDR = data;
		break;
	case MODULE1:
		while (RD1B(I2C1->SCSR, TREQ) == 0) {};
		I2C1->SDR = data;
		break;
	case MODULE2:
		while (RD1B(I2C2->SCSR, TREQ) == 0) {};
		I2C2->SDR = data;
		break;
	case MODULE3:
		while (RD1B(I2C3->SCSR, TREQ) == 0) {};
		I2C3->SDR = data;
		break;
	}

}
void I2C_MASTER_Enable(uint8_t module)
{ 
	switch(module)
	{
		case MODULE0:
			ST1B(I2C0->MCR,MFE);
			break;
		case MODULE1:
			ST1B(I2C1->MCR,MFE);
			break;
		case MODULE2:
			ST1B(I2C2->MCR,MFE);
			break;
		case MODULE3:
			ST1B(I2C3->MCR,MFE);
			break;
	}
}
void I2C_MASTER_Disable(uint8_t module)
{ 
	switch(module)
	{
		case MODULE0:
			CLR1B(I2C0->MCR,MFE);
			break;
		case MODULE1:
			CLR1B(I2C1->MCR,MFE);
			break;
		case MODULE2:
			CLR1B(I2C2->MCR,MFE);
			break;
		case MODULE3:
			CLR1B(I2C3->MCR,MFE);
			break;
	}
}
void I2C_SLAVE_Enable(uint8_t module)
{ 
	switch(module)
	{
		case MODULE0:
			ST1B(I2C0->MCR,SFE);
			break;
		case MODULE1:
			ST1B(I2C1->MCR,SFE);
			break;
		case MODULE2:
			ST1B(I2C2->MCR,SFE);
			break;
		case MODULE3:
			ST1B(I2C3->MCR,SFE);
			break;
	}
}
void I2C_SLAVE_Disable(uint8_t module)
{ 
	switch(module)
	{
		case MODULE0:
			CLR1B(I2C0->MCR,SFE);
			break;
		case MODULE1:
			CLR1B(I2C1->MCR,SFE);
			break;
		case MODULE2:
			CLR1B(I2C2->MCR,SFE);
			break;
		case MODULE3:
			CLR1B(I2C3->MCR,SFE);
			break;
	}
}
void SLAVE_Single_Read_Byte_App(void)
{
	PLL_init(CLK_40MHZ);
	sysclock = 40000000;
	I2C_Init(MODULE3, SLAVE, 0x08, NON);
	RGB_Init(ALL);
	uint8_t data;
	while (1) {
		data = I2C_SLAVE_Byte_Read(MODULE3);
		if (data == 1) {
			RGB_DisAll();
			RGB_Out(LED_RED, ON);
		}
		else if (data == 2)
		{
			RGB_DisAll();
			RGB_Out(LED_GREEN, ON);
		}
		else if (data == 3)
		{
			RGB_DisAll();
			RGB_Out(LED_BLUE, ON);
		}
	}
}
void MASTER_Single_Write_Byte_App(void)
{
	PLL_init(CLK_40MHZ);
	sysclock = 40000000;
	I2C_Init(MODULE3, MASTER, NON, 100000);
	uint8_t count;
	while (1)
	{
		for (count = 1; count < 4; count++)
		{
			I2C_MASTER_Byte_Write(MODULE3, 0x8, count);
			msDelay(2);
		}
	}
}
