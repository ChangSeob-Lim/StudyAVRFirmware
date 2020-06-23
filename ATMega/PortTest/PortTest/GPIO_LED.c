/*
 * GPIO_LED.c
 *
 * Created: 2020-06-12 오후 4:23:54
 *  Author: PKNU
 */ 

 #include <avr/io.h>
 #include <util/delay.h>

 int main()
 {
	unsigned char LED_Data = 0x00;
	DDRC = 0x0F;

	while(1)
	{
		PORTC = LED_Data;
		LED_Data++;

		if(LED_Data > 0x0F)
			LED_Data = 0;
		_delay_ms(1000);
	}

	return 0;
 }