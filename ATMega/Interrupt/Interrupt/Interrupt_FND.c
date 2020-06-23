/*
 * Interrupt_FND.c
 *
 * Created: 2020-06-15 오후 3:22:25
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_STOP = 0;

int main()
{
	unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,
									0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c,
									0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
	unsigned char cnt=0;
	
	DDRC = 0xff;
	DDRE = 0x00;
	EICRB = 0xc0;
	EIMSK = 0x80;
	EIFR = 0x80;
	sei();

	while(1)
	{
		PORTC = FND_DATA_TBL[cnt];

		if(Time_STOP == 0)
		{
			cnt++;
			if(cnt>17) cnt=0;
		}
		_delay_ms(200);
	}
}

SIGNAL(INT7_vect)
{
	cli();
	if(Time_STOP == 0) Time_STOP = 1;
	else Time_STOP = 0;
	sei();
}