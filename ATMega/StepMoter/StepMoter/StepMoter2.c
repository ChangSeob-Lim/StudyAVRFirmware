/*
 * StepMoter2.c
 *
 * Created: 2020-06-18 오전 9:41:16
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char i;

	DDRB = 0x20; // MOTOR1_EN를 출력 포트로 설정
	DDRD = 0xF0; // STEP 0 ~ 3을 출력 포트로 설정
	PORTB &= ~0x20; // M1 Disable, DC 모터 정지

	while(1)
	{
		for(i=0; i<12; i++) // 12주기가 한바퀴
		{
			PORTD = 0x30; // 1 step
			_delay_ms(10);
			PORTD = 0x90; // 2 step
			_delay_ms(10);
			PORTD = 0xC0; // 3 step
			_delay_ms(10);
			PORTD = 0x60; // 4 step
			_delay_ms(10);
		}
		_delay_ms(100);

		for(i=0; i<12; i++) // 12주기가 한바퀴
		{
			PORTD = 0x30; // 1 step
			_delay_ms(10);
			PORTD = 0x60; // 2 step
			_delay_ms(10);
			PORTD = 0xC0; // 3 step
			_delay_ms(10);
			PORTD = 0x90; // 4 step
			_delay_ms(10);
		}
		_delay_ms(500);
	}
}