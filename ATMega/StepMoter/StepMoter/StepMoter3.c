/*
 * StepMoter3.c
 *
 * Created: 2020-06-18 오전 10:04:28
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

unsigned char Step[8] = {0x90, 0x80, 0xC0, 0x40, 0x60, 0x20, 0x30, 0x10};

int main()
{
	unsigned char i, t=0;

	DDRC = 0x20;
	//DDRB = 0x20; // MOTOR1_EN를 출력 포트로 설정
	DDRD = 0xF0; // STEP 0 ~ 3을 출력 포트로 설정
	//PORTB &= ~0x20; // M1 Disable, DC 모터 정지
	PORTC &= ~0x20;
	while(1)
	{
		for(i=0; i<24; i++) // 3.75도 회전, 90도 회전하려면 24개 필요
		{
			PORTD = Step[t];
			t++;
			if(t>7) t=0;
			_delay_ms(10);
		}
		_delay_ms(1000);
	}
}