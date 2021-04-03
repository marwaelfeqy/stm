#include "I2C.h"
#include "GPIO.h"


void I2C_Init(uint8_t i2c, uint16_t speed_mode)
{
	
	RCC->APB2ENR |=1;  				//ENABLE ALTERNATIVE FUNCTION CLK
	CLK_EN_GPIOB();
	if(i2c==1)
	{
		RCC->APB1ENR |= 0x00200000;
		Config_GPIO(GPIOB, 6, OUT50 ,ALT_OD); //SCL
		Config_GPIO(GPIOB, 7, OUT50 ,ALT_OD); //SDA
		
		I2C1->CR1 |= 0x80000;
		I2C1->CR1 &= ~0x80000; 	//Toggle RESET BIT to reinitialize the peripheral
		
		I2C1->CR2 = 0x8; 				//SET PERIPHRAL CLK FREQUENCY
		
		I2C1->CCR = speed_mode;
		
		I2C1->TRISE=0x09;				//Maximum rise time
		//TRISE[5:0] must be configured only when the I2C is disabled (PE = 0).
		
		
		
		I2C1->CR1 |=1; 					//ENABLE THE PERIPHERAL
		
		
	}
}



void I2C_Slave_Write(uint8_t i2c, uint8_t add, uint8_t data)
{
	uint16_t tmp;
	if(i2c==1)
	{
	
		I2C1->OAR1=(uint16_t)(add<<1);
		
		I2C1->CR1|= 1<<10;
		while (!(I2C1->SR1 &2)){} //wait until ADDR==1 ACK "Received address matched"
		
		
		while ((I2C1->SR1 &2))//clear by software
		{
			tmp=I2C1->SR1;
			tmp=I2C1->SR2;
		}
		while((I2C1->SR1 &(1<<7))==0); //wait until dataReg is empty "TxE==1"
		I2C1->DR=data;
		I2C_Stop(1);
	}
}

void I2C_Write(uint8_t i2c,uint8_t add,uint8_t data)
{
	if(i2c ==1)
	{
		I2C_Start(i2c);
		Write_pin(GPIOA,1,HIGH);
		I2C_Addr(i2c,add,0);
		I2C_Data(i2c,data);
		I2C_Stop(1);
	}
}

uint8_t I2C_Read(uint8_t i2c,uint8_t add)
{
	uint8_t c=0;
	if(i2c==1)
	{
		I2C_Start(i2c);
		I2C_Addr(i2c,add,1);
		
		I2C1->CR1 |=(1<<10); //ACK
		while((I2C1->SR1 &(1<<6))==0){}  //wait for ReX
		c = (uint8_t) I2C1->DR;
		
		
		I2C1->CR1 &=~(1<<10); //NACK
		I2C_Stop(1);		
	}
	return c;
}



void I2C_Read_n(uint8_t i2c,uint8_t add,uint8_t arr[],uint16_t num)
{
	if(i2c==1)
	{
		I2C_Start(i2c);
		I2C_Addr(i2c,add,1);
		
		for(int i=0;i<num;i++)
		{
		I2C1->CR1 |=(1<<10); //ACK
		while((I2C1->SR1 &(1<<6))==0){}  //wait for ReX
		arr[i] = (uint8_t) I2C1->DR;	
		}
		I2C1->CR1 &=~(1<<10); //NACK
		I2C_Stop(1);		
	}

}






void I2C_Start(uint8_t i2c)
{
	if(i2c ==1)
	{
		I2C1->CR1 |= 0x100; //Start Generation
		while(! (I2C1->SR1 &1)); //wait Start condition generated.
		//Set when a Start condition generated.
	}
}



void I2C_Addr(uint8_t i2c, uint8_t add, uint8_t rw)
{
	volatile int tmp;
	if(i2c==1)
	{
		I2C1->DR = add|rw; //read or write
		while (!(I2C1->SR1 &2)){} //wait until ADDR==1 ACK "Received address matched"
		
		
		while ((I2C1->SR1 &2))//clear by software
		{
			tmp=I2C1->SR1;
			tmp=I2C1->SR2;
		}
		
	}
}

void I2C_Data(uint8_t i2c,uint8_t data)
{
	if(i2c==1)
	{
		while((I2C1->SR1 &(1<<7))==0); //wait until dataReg is empty "TxE==1"
		I2C1->DR=data;
		while((I2C1->SR1 &(1<<7))==0); //wait until dataReg is empty "TxE==1"

	}
}



void I2C_Stop(uint8_t i2c)
{
	volatile int tmp;
	if(i2c ==1)
	{
		tmp=I2C1->SR1;
		tmp=I2C1->SR2;
		I2C1->CR1 |= 0x200;
	}
}

