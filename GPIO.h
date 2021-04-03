#include "stm32f10x.h"


#define LOW 	((uint32_t)0)
#define HIGH 	((uint32_t)1)

//PIN CONFIG -- DIR
#define 	INPUT				0
#define 	OUTPUT			3
#define 	OUT10				1
#define 	OUT2				2
#define 	OUT50 			3

//INPUT MODE
#define 	ANALOG				0
#define 	FLOATING			1
#define 	PULLUP				2
#define 	PULLDOWN			2

//OUTPUT MODE
#define 	GEN_PP				0
#define 	GEN_OD				1
#define 	ALT_PP				2
#define 	ALT_OD				3


//CLK_ENABLE
#define CLK_EN_GPIOA()			(RCC->APB2ENR |=(1<<2))
#define CLK_EN_GPIOB()			(RCC->APB2ENR |=(1<<3))
#define CLK_EN_GPIOC()			(RCC->APB2ENR |=(1<<4))
#define CLK_EN_GPIOD()			(RCC->APB2ENR |=(1<<5))

void Init_GPIO(GPIO_TypeDef *port, uint32_t pinNum, uint32_t state);
void Config_GPIO(GPIO_TypeDef *port, uint32_t pinNum, uint32_t dir,uint32_t mode);
void Write_pin(GPIO_TypeDef *port, uint32_t pinNum, uint32_t state);
void Toggle_pin(GPIO_TypeDef *port, uint32_t pinNum);
int Read_pin(GPIO_TypeDef *port, uint32_t pinNum);
