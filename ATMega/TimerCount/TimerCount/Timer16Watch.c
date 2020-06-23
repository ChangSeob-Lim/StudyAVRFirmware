/*
 * Timer16Watch.c
 *
 * Created: 2020-06-17 오전 9:14:20
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
unsigned char time_s=0;

int main()
{
	DDRA = 0xFF;

	TCCR1A = 0; // 0x00 // 16bit TimerCounter1 사용
	TCCR1B = (1 << CS12) | (1 << CS10); // 0x05 // 프리스케일러 1024 CS 101로 설정

	OCR1A = 7200; // 7372800/1024
	TIMSK = 1 << OCIE1A; // 출력비교 인터럽트 Enable
	TIFR |= 1 << OCF1A; // Timer/Counter1 Output Compare flag 클리어
	
	sei();
	
	while(1)
	{
		PORTA = FND_DATA_TBL[time_s];
	} 

	return 0;
}

SIGNAL(TIMER1_COMPA_vect)
{
	cli();

	OCR1A += 7200;
	if(time_s >= 17) time_s=0;
	else time_s++;

	sei();
}