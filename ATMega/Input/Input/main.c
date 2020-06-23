/*
 * Input.c
 *
 * Created: 2020-06-15 오전 9:19:11
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xff;
    while (1) 
    {
		PORTA = 0x01;
		_delay_ms(1000);
		PORTA = 0x02;
		_delay_ms(1000);
		PORTA = 0x04;
		_delay_ms(1000);
		PORTA = 0x08;
		_delay_ms(1000);
		PORTA = 16;
		_delay_ms(1000);
		PORTA = 32;
		_delay_ms(1000);
		PORTA = 64;
		_delay_ms(1000);
		PORTA = 128;
		_delay_ms(1000);
    }
	
	return 0;
}