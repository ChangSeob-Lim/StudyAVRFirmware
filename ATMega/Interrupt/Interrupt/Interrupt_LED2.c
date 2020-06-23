/*
 * Interrupt_LED2.c
 *
 * Created: 2020-06-15 오후 2:46:05
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Shift_flag = 1;
volatile unsigned char before_Shift_flag = 1;

int main(void)
{
    unsigned char LED_Data = 0x01;

	DDRC = 0xFF;
	DDRD = 0x00; // INT0 ~ INT3 까지 D0 ~ D3 사용
	DDRE = 0x00; // INT4 ~ INT7 까지 E4 ~ E7 사용

	EICRA = 0xC2;
	EICRB = 0x03;
	EIMSK = 0x19;
	EIFR = 0x19;
	
	sei();

    while (1) 
    {
		PORTC = LED_Data;
		if(Shift_flag == 1)
		{
			if(LED_Data == 0x80) LED_Data = 0x01;
			else LED_Data <<= 1;
		}
		else if(Shift_flag == 2)
		{
			if(LED_Data == 0x01) LED_Data = 0x80;
			else LED_Data >>= 1;
		}
		
		_delay_ms(100);
    }
}

SIGNAL(INT0_vect)
{
	cli();
	Shift_flag = 2;
	sei();
}

SIGNAL(INT3_vect)
{
	cli();
	Shift_flag = 1;
	sei();
}

SIGNAL(INT4_vect)
{
	cli();
	if(Shift_flag == 0)
		Shift_flag = before_Shift_flag;
	else
	{
		before_Shift_flag = Shift_flag;
		Shift_flag = 0;
	}
	sei();
}