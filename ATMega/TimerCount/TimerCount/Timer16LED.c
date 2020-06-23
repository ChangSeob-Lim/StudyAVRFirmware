/*
 * Timer16LED.c
 *
 * Created: 2020-06-16 오전 11:21:13
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer1Cnt=0;

int main()
{
	DDRA = 0xFF;

	TCCR1A = 0; // 타이머카운터1 일반 동작모드 사용
	TCCR1B = 1 << CS10; // 프리스케일러 1

	TCNT1 = 0; // 0 -> 1/225초 마다 한번씩 인터럽트 발생
	TIMSK = 1 << TOIE1;
	TIFR |= 1 << TOV1;

	sei();

	while(1)
	{
		PORTA = LED_Data;
	}

	return 0;
}

SIGNAL(TIMER1_OVF_vect)
{
	cli();

	timer1Cnt++;

	if(timer1Cnt == 113)
	{
		LED_Data++;
		if(LED_Data>0xFF) LED_Data=0;

		timer1Cnt=0;
	}

	sei();
}