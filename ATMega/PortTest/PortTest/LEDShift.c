/*
 * LEDShift.c
 *
 * Created: 2020-06-12 오후 4:43:21
 *  Author: PKNU
 */ 

 #include <avr/io.h>
 #include <util/delay.h>

 int main()
 {
	unsigned char LED_Data = 0x01, i;
	DDRC = 0xFF;

	while(1)
	{
		LED_Data = 0x01;
		// 왼쪽으로 이동
		for(i=0; i<7; i++)
		{
			PORTC = LED_Data;
			LED_Data <<= 1;
			_delay_ms(500);
		}
		// 오른쪽으로 이동
		for(i=0; i<7; i++)
		{
			PORTC = LED_Data;
			LED_Data >>= 1;
			_delay_ms(500);
		}

		LED_Data = 0x00;
		PORTC = LED_Data;
		_delay_ms(1000);
		
		for(i=0; i<8; i++)
		{
			LED_Data = (LED_Data << 1) + 1;
			PORTC = LED_Data;
			_delay_ms(500);
		}
		
		for(i=0; i<8; i++)
		{
			LED_Data = LED_Data << 1;
			PORTC = LED_Data;
			_delay_ms(500);
		}
	}

	return 0;
 }