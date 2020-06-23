/*
 * TimerAndInterruptFND.c
 *
 * Created: 2020-06-16 오전 10:18:51
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};

volatile unsigned char time_s=0;
volatile unsigned char Time_STOP=0;

unsigned char timer0Cnt=0;

int main()
{
	DDRA = 0xFF;									// 포트A 출력포트로 설정
	DDRE = 0x00;									// 포트E 입력포트로 설정

	TCCR2 = (1 << CS22) | (1 << CS20);//0x05;		//프리스케일러 1024, 일반모드
	OCR2 = 72;										// 비교일치 R2에 72값 저장
	TIMSK = (1 << OCIE2);//0x80;					// 타이머카운터2 비교일치 인터럽트 인에이블
	TIFR |=1 << OCF2;								// 타이머카운터2 비교일치 플래그 리셋

	EICRB = (1 << ISC41) | (1 << ISC40);//0x03;		// 외부인터럽트4 트리거 설정
	EIMSK = (1 << INT4);//0x10;						// 외부인터럽트4 인에이블
	EIFR = (1 << INT4);//0x10;						// 외부인터럽트4 플래그 리셋

	sei();											// 전체 인터럽트 인에이블

	while(1)
	{
		PORTA = FND_DATA_TBL[time_s];
	}

	return 0;
}

SIGNAL(TIMER2_COMP_vect)
{
	cli();

	OCR2+=72;
	timer0Cnt++;

	if(timer0Cnt == 50)
	{
		if(Time_STOP == 0)
		{
			if(time_s >= 16) time_s = 0;
			else time_s++;
		}
		timer0Cnt=0;
	}

	sei();
}

SIGNAL(INT4_vect)
{
	cli();

	if(Time_STOP == 0) Time_STOP = 1;
	else Time_STOP = 0;

	sei();
}