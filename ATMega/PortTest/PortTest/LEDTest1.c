/*
 * LEDTest1.c
 *
 * Created: 2020-06-12 오후 3:39:37
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	while(1)
	{
		DDRC = 0x53; // LED0, 1 출력모드,  LED2, 3 입력모드로 설정
		PORTC= 0xFF; // LED0~3 모두 1 출력
		_delay_ms(500);

		PORTC = 0x00; // LED0~3 모두 0 출력 
		_delay_ms(500);

		DDRC = 0xAC; // LED0, 1 입력모드,  LED2, 3 출력모드로 설정
		PORTC = 0xFF; // LED0~3 모두 1 출력
		_delay_ms(500);

		PORTC = 0x00; // LED0~3 모두 0 출력 
		_delay_ms(500);
	}

	return 0;
}