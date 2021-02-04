#ifndef GPIO
#define GPIO

#include "stm32f10x.h"


#define LOW 	((uint32_t)0)
#define HIGH 	((uint32_t)1)


//PIN MODE
#define INPUT_MODE				((uint32_t)0x00)
#define OUTPUT_MODE				((uint32_t)0x01)
#define OUTPUT_MODE_10		((uint32_t)0x01)
#define OUTPUT_MODE_2			((uint32_t)0x02)
#define OUTPUT_MODE_50		((uint32_t)0x03)

//OUTPUT MODES
#define OUTPUT_GEN 				((uint32_t)0x00)
#define OUTPUT_OD					((uint32_t)0x01)
#define OUTPUT_ALT				((uint32_t)0x02)
#define OUTPUT_ALT_OD			((uint32_t)0x03)

//INPUT MODES
#define INPUT_ANALOG			((uint32_t)0x00)
#define INPUT_FLOAT				((uint32_t)0x01)
#define INPUT_PULL				((uint32_t)0x02)

//CLK_ENABLE
#define CLK_EN_GPIOA()			(RCC->APB2ENR |=(1<<2))
#define CLK_EN_GPIOB()			(RCC->APB2ENR |=(1<<3))
#define CLK_EN_GPIOC()			(RCC->APB2ENR |=(1<<4))
#define CLK_EN_GPIOD()			(RCC->APB2ENR |=(1<<5))

void config_pin(GPIO_TypeDef *port, uint32_t pinNum, uint32_t state);
void write_pin(GPIO_TypeDef *port, uint32_t pinNum, uint32_t state);


#endif

