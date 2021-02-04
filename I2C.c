#include "I2C.h"

void i2c1_init()
{
	//ENABLE CLK FOR PORTB & I2C
	CLK_EN_I2C1();			
	CLK_EN_GPIOB();
	
	
	I2C1->CR2|=4; 				//APB1 FREQ
	
	I2C1->CCR|=20; 				//Standard 100KH
	
	I2C1->TRISE |= 5; 		//Maximum rise time 
	
	I2C1->CR1 |= I2C_CR1_ACK; //ENABLE ACKS
	
	//PIN6,7 OUTPUT-ALT-OD
	GPIOB->CRL |= (15<<(24));
	GPIOB->CRL |= (15<<(28));
	// OUTPUT PULLUP
	GPIOB->ODR |=(1<<6)|(1<<7);
	
	//ENABLE PERIPHERAL
	I2C1->CR1 |=I2C_CR1_PE; //PE
}

void i2c1_write(uint8_t device_add, uint8_t in_add, uint8_t data)
{
	uint32_t temp;
	I2C1->CR1 |= (1<<8); 								//Generate start condition
	while(!(I2C1->SR1&1)); 							//wait to generate start
	
	I2C1->DR = device_add;
	while(!(I2C1->SR1 & I2C_SR1_ADDR)); //Wait-Receive address matched.
	temp = I2C1->SR2 ; 									//CLEAR ADDR Flag

	
	I2C1->DR = in_add; 									//Internal addrsse to write to
	while(!(I2C1->SR1 & I2C_SR1_TXE));	// Set when DR is empty in transmission.

	I2C1->DR =data;											//Send Data
	while(!(I2C1->SR1 & I2C_SR1_TXE));	// Set when DR is empty in transmission.

	I2C1->CR1|=I2C_CR1_STOP;						//end process
} 



	


void i2c1_read(uint8_t device_add, uint8_t in_add, uint8_t *buf)
{
	uint32_t temp;
	I2C1->CR1 |= I2C_CR1_ACK; //ENABLE ACKS
	
	
	I2C1->CR1 |= (1<<8); 								//Generate start condition
	while(!(I2C1->SR1&1)); 							//wait to generate start
	
	I2C1->DR = device_add;
	while(!(I2C1->SR1 & I2C_SR1_ADDR)); //Wait-Receive address matched.
	temp = I2C1->SR2 ; 									//CLEAR ADDR Flag
	
	I2C1->DR = in_add; 									//Internal addrsse to write to
	while(!(I2C1->SR1 & I2C_SR1_TXE));	// Set when DR is empty in transmission.

	
	
	I2C1->CR1 |= (1<<8); 								//Generate Restart condition
	while(!(I2C1->SR1&1)); 							//wait to generate start
	
	I2C1->DR = device_add+1;
	while(!(I2C1->SR1 & I2C_SR1_ADDR)); //Wait-Receive address matched.
	temp = I2C1->SR2 ; 									//CLEAR ADDR Flag

	while(!(I2C1->SR1 & I2C_SR1_RXNE));// received
		
	buf[0] = ((uint8_t)(0x0f&I2C1->DR));
	
	I2C1->CR1|=I2C_CR1_STOP;	
	
}	

void i2c1_read_dma(uint8_t device_add, uint8_t in_add, uint8_t *buf)
{
	uint32_t temp;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	I2C1->CR2 |= I2C_CR2_DMAEN;
	I2C1->CR1 |= I2C_CR1_ACK; //ENABLE ACKS
	DMA1_Channel5->CMAR = (uint32_t)buf;
	DMA1_Channel5->CPAR = (uint32_t)&I2C1->DR;
	DMA1_Channel5->CNDTR = 1;
	DMA1_Channel5->CCR |= DMA_CCR4_TCIE|DMA_CCR5_MINC |DMA_CCR5_EN;
	
	I2C1->CR1 |= (1<<8); 								//Generate start condition
	while(!(I2C1->SR1&1)); 							//wait to generate start
	
	I2C1->DR = device_add;
	while(!(I2C1->SR1 & I2C_SR1_ADDR)); //Wait-Receive address matched.
	temp = I2C1->SR2 ; 									//CLEAR ADDR Flag
	
	I2C1->DR = in_add; 									//Internal addrsse to write to
	while(!(I2C1->SR1 & I2C_SR1_TXE));	// Set when DR is empty in transmission.

	
	
	I2C1->CR1 |= (1<<8); 								//Generate Restart condition
	while(!(I2C1->SR1&1)); 							//wait to generate start
	
	I2C1->DR = device_add+1;
	while(!(I2C1->SR1 & I2C_SR1_ADDR)); //Wait-Receive address matched.
	temp = I2C1->SR2 ; 									//CLEAR ADDR Flag

	while((DMA1->ISR & DMA_ISR_TCIF5)==0)// Transfer done
		
	I2C1->CR1|=I2C_CR1_STOP;	
	
}	

