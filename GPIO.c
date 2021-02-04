#include "GPIO.h"

void config_pin(GPIO_TypeDef *port, uint32_t pinNum, uint32_t state)
{
	if(pinNum<8)
	{
		port->CRL &= ~(15<<(pinNum*4));
		port->CRL |= (state<<(pinNum*4));
		
	}
	else
	{
		pinNum-=8;
		port->CRH &= ~(15<<(pinNum*4));
		port->CRH |= (state<<(pinNum*4));
	}
	
}
void write_pin(GPIO_TypeDef *port, uint32_t pinNum, uint32_t state)
{
	if (state)
	{
		port->BSRR &= ~(1<<(pinNum+16));
		port->BSRR |= (1<<pinNum);
	}
	else
	{
		port->BSRR |= (1<<(pinNum+16));
		port->BSRR &= ~(1<<pinNum);
	}
}
	
