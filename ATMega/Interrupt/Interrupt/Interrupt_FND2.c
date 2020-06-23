/*
 * Interrupt_FND2.c
 *
 * Created: 2020-06-15 오후 3:43:17
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_STOP = 0;
volatile unsigned char cnt = 0;

int main()
{
	unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,
									0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c,
									0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
	
	DDRC = 0xFF;
	DDRD = 0x00;

	EICRA = 0xC3;
	EIMSK = 0x09;
	EIFR = 0x09;
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

SIGNAL(INT0_vect)
{
	cli();

	Time_STOP = 1;
	cnt = 0;

	sei();
}

SIGNAL(INT3_vect)
{
	cli();

	if(Time_STOP == 0) Time_STOP = 1;
	else Time_STOP = 0;

	sei();
}