/*
 * Timer16LED2.c
 *
 * Created: 2020-06-16 오후 12:16:54
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;

int main()
{
	DDRC = 0xFF;

	TCCR3A = 0; // 타이머카운터3 노말 모드 설정
	TCCR3B = (1 << CS32) | (1 << CS30); // 프리스케일러 1024

	TCNT3 = 58336; // 65536 - 7200(73728/1024) = 58336
	ETIMSK = 1 << TOIE3;
	ETIFR |= 1 << TOV3;

	sei();

	while(1)
	{
		PORTC = LED_Data;
	}

	return 0;
}

SIGNAL(TIMER3_OVF_vect)
{
	cli();

	TCNT3 = 58336;
	LED_Data++;

	if(LED_Data>0xFF) LED_Data = 0;

	sei();
}