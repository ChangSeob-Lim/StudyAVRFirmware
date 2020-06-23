/*
 * TimerWatch.c
 *
 * Created: 2020-06-16 오전 9:40:26
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};

volatile unsigned char time_s=0;
unsigned char timer0Cnt=0;

int main()
{
	DDRA = 0xFF;
	TCCR0 = 0x07; // 프리스케일러 1024 // TCCR0 = (1 << CS02) | (1 << CS01) | (1 << CS00);
	OCR0 = 72;//7372800/1024=7200 -> 72
	TIMSK = 0x02; // 출력비교 인터럽트 TIMSK = (1 << OCIE0);
	TIFR |=1 << OCF0;

	sei();

	while(1)
	{
		PORTA = FND_DATA_TBL[time_s];
	}

	return 0;
}

SIGNAL(TIMER0_COMP_vect)
{
	cli();

	OCR0+=72;
	timer0Cnt++;

	if(timer0Cnt == 100)
	{
		if(time_s >= 16) time_s = 0;
		else time_s++;

		timer0Cnt=0;
	}

	sei();
}