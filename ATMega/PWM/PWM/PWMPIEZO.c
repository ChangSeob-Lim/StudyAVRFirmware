/*
 * PWMPIEZO.c
 *
 * Created: 2020-06-17 오후 12:18:47
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

int main()
{
	unsigned char piano=0;

	DDRB = 0x80; // PWM 출력, OCR1C

	TCCR1A |= 0x0A; // COM1(1:0)="10", OC1C핀사용, WGM3(1:0)="10"
	TCCR1B |= 0x19; // WGM3(3:2)="11", CS3(2:0)="001", 1분주 사용
	TCCR1C = 0x00; // WGM3(3:0)="1110", Fast Pwm 모드 14
	TCNT1 = 0x0000; // 타이머1 카운트 초기화

	while(1)
	{
		ICR1 = 7372800/DoReMi[piano]; // 버튼에 맞는 음향 연주
		OCR1C = ICR1/10; // 10% 듀티비
		piano++;
		if(piano > 8) piano = 0;
		_delay_ms(500);
	}

	return 0;
}