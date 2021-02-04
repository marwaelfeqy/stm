#include "stm32f10x.h"
#include "GPIO.h"
#include "I2C.h"

int main()
{
	uint8_t device_add=0x56;
	uint8_t buf[12];
	
	config_pin(GPIOA, 10, OUTPUT_MODE);
	write_pin(GPIOA, 10, HIGH);

	i2c1_init();
	i2c1_write(device_add,0x45,'y');
	i2c1_read(device_add,0x45,buf);

	while(1)
	{
			
		
	}
	
	return 0;
	
}

