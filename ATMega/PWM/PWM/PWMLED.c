/*
 * PWM.c
 *
 * Created: 2020-06-17 오전 11:20:37
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char Light=0;

	DDRB = 0x10;

	TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << COM00) | (1 << CS02) | (1 << CS01);// | (1 << CS00); // 0x77 // PC PWM 모드, 1024분주 -> 256분주가 이쁘게 나옴
	TCNT0 = 0; //0x00

    while (1) 
    {
		for(Light=0; Light<255; Light++)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
		for(Light=255; Light>0; Light--)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
    }

	return 0;
}

