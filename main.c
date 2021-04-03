#include "stm32f10x.h"
#include "GPIO.h"
#include "I2C.h"
//uint8_t c=0;
//uint8_t arr[]={0,0,0,0,0};
void Delay(void);
	//int i=0;
int main ()
{
	
	CLK_EN_GPIOA();
	CLK_EN_GPIOC();
	Config_GPIO(GPIOA, 1, OUTPUT,GEN_PP);
	Config_GPIO(GPIOC, 13, OUTPUT,GEN_PP);
	Write_pin(GPIOC, 13, LOW);
	
	I2C_Init(1, FM);

				
	while(1)
	{
		I2C_Slave_Write(1,8,5);
		Delay();
		
	}
	
	
	
	//return 0;
}

void Delay(void)
{
	for(int p=0;p<3000000;p++);
}
