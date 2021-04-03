#include "stm32f10x.h"
#include "GPIO.h"


void Config_GPIO(GPIO_TypeDef *port, uint32_t pinNum, uint32_t dir,uint32_t mode)
{
	dir = dir|(mode<<2);
	if(pinNum<8)
		{
			port->CRL &= ~((uint32_t)0x000F <<(4*pinNum));
			port->CRL |= (dir<<(pinNum*4));
		}
		else
		{
			pinNum -=8;
			port->CRH &= ~((uint32_t)0x000F <<(4*pinNum));
			port->CRH |= (dir<<(pinNum*4));
		}
}

void Write_pin(GPIO_TypeDef *port, uint32_t pinNum, uint32_t state)
{
	if (state)
	{
		port->BSRR &= ~(1<<(pinNum+16));
		port->BSRR |= (1<<pinNum);
	}
	else
	{
		port->BSRR &= ~(1<<pinNum);
		port->BSRR |= (1<<(pinNum+16));
		
	}
}
void Toggle_pin(GPIO_TypeDef *port, uint32_t pinNum)
{
	port->ODR ^= (uint32_t)(1<<pinNum);
}


int Read_pin(GPIO_TypeDef *port, uint32_t pinNum)
{
	return (int)(((port->IDR>>pinNum)&(1)));
}	

void Init_GPIO(GPIO_TypeDef *port, uint32_t pinNum, uint32_t state)
{
	if(pinNum<8)
		{
			port->CRL &= ~((uint32_t)0x000F <<(4*pinNum));
			port->CRL |= (state<<(pinNum*4));
		}
		else
		{
			pinNum -=8;
			port->CRH &= ~((uint32_t)0x000F <<(4*pinNum));
			port->CRH |= (state<<(pinNum*4));
		}
}
