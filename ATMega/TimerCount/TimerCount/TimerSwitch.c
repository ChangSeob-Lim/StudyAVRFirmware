/*
 * TimerSwitch.c
 *
 * Created: 2020-06-17 오전 9:43:09
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};

volatile unsigned char time_s=0;
volatile unsigned char FND_flag=0, edge_flag=0;

int main()
{
	DDRA = 0xFF;
	DDRE = 0x00;

	TCCR3A = 0; // 0x00
	TCCR3B = (1 << ICES3) | (1 << CS32) | (1 << CS30); // 0x45 // 프리스케일러 1024, 상승에지 캡처 트리거 설정
	ETIMSK = 1 << TICIE3; // 0x20
	ETIFR |= 1 << ICF3;

	sei();

	PORTA = FND_DATA_TBL[0];
	while(1)
	{
		if(FND_flag)
		{
			if(time_s > 15) time_s=15; // 최대 15초까지 표시(F)
			
			PORTA = FND_DATA_TBL[time_s];
			FND_flag=0;
		}
	}

	return 0;
}

SIGNAL(TIMER3_CAPT_vect)
{
	cli();

	unsigned int count_check;

	// 스위치가 눌린시간 측정을 위해 상승에지에서 하강에지까지의 시간 계산
	if(edge_flag==0) // 상승 에지(스위치를 누르면)
	{
		TCCR3B = (1 << CS32) | (1 << CS30);; // 0x05 // 프리스케일러 1024, 하강에지 캡처 트리거 설정
		TCNT3 = 0; // TCNT3 레지스터 0으로 초기화
		ICR3 = 0; // ICR3 레지스터 0으로 초기화
		edge_flag=1;
	}
	else // 하강 에지
	{
		TCCR3B = (1 << ICES3) | (1 << CS32) | (1 << CS30); // 0x45 // 프리스케일러 1024, 상승에지 캡처 트리거 설정
		count_check = ICR3;

		// 7372800/1024 = 7200 Hz, 1초동안 TCNT의 값은 7200
		time_s = count_check/3600; // 누를 시간을 0.5초 단위로 변경

		FND_flag=1;
		edge_flag=0;
	}

	sei();
}