/*
 * FND_LED.c
 *
 * Created: 2020-06-15 오전 11:03:28
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 
									0x77, 0x7c, 0x39, 0x5E, 0x79, 0x71, 0x08, 0x80}; // 0b00111111 = 0x3f => 0, 0b00000110 = 0x06 => 1, 0b01011011 = 0x5b => 2 ...
	unsigned char cnt = 0;
	DDRA = 0xff;

	while(1)
	{
		PORTA = FND_DATA_TBL[cnt];
		cnt++;
		if(cnt>17) cnt=0;
		_delay_ms(500);
	}

	return 0;
}