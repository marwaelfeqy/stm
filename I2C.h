#ifndef I2C
#define I2C

#include "stm32f10x.h"


#define CLK_EN_I2C1()			(RCC->APB1ENR |=(1<<21))
#define CLK_EN_GPIOB()			(RCC->APB2ENR |=(1<<3))



void i2c1_init(void);
void i2c1_write(uint8_t device_add, uint8_t in_add, uint8_t data);
void i2c1_read(uint8_t device_add, uint8_t in_add, uint8_t *buf);
void i2c1_read_dma(uint8_t device_add, uint8_t in_add, uint8_t *buf);


#endif

