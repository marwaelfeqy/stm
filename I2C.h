#include "stm32f10x.h"

#define FM 0x2D
#define SM 0xB4

void I2C_Init(uint8_t i2c, uint16_t mode);
void I2C_Start(uint8_t i2c);

void I2C_Write(uint8_t i2c,uint8_t add,uint8_t data);
uint8_t I2C_Read(uint8_t i2c,uint8_t add);
void I2C_Read_n(uint8_t i2c,uint8_t add,uint8_t arr[],uint16_t num);

void I2C_Addr(uint8_t i2c, uint8_t add, uint8_t rw);
void I2C_Data(uint8_t i2c,uint8_t data);
void I2C_Stop(uint8_t i2c);

void I2C_Slave(uint8_t i2c, uint8_t add);
void I2C_Slave_Write(uint8_t i2c, uint8_t add, uint8_t data);
