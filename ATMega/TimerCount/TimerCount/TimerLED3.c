/*
 * TimerLed3.c
 *
 * Created: 2020-06-16 오전 9:21:28
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned int timer0cnt=0;

SIGNAL(TIMER0_OVF_vect); //ISR(TIMER0_OVF_vect);

int main()
{
	DDRC = 0xFF;

	TCCR0 = 0x06;

	TCNT0 = 0xFF - 72; // 7372800/256=28800 -> 28800/400=72(0.0025초(2.5ms) * 400 = 1초(1s))
	TIMSK = 0x01;
	TIFR |=1 << TOV0;

	sei();

	while(1)
	{
		PORTC = LED_Data;
	}
	
	return 0;
}

SIGNAL(TIMER0_OVF_vect)
{
	cli();

	TCNT0 = 183;
	timer0cnt++;

	if(timer0cnt == 400)
	{
		LED_Data++;
		if(LED_Data>0xFF) LED_Data = 0;
		timer0cnt=0;
	}

	sei();
}