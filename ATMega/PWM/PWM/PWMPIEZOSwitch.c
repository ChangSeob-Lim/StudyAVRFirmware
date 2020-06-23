/*
 * PWMPIEZOSwitch.c
 *
 * Created: 2020-06-17 오후 1:51:13
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};// {261, 293, 329, 349, 391, 440, 493, 523} {1046,1174,1318,1396,1567,1760,1975,2093}
volatile unsigned char sound_flag=1;

int main()
{
	DDRE = 0x08;
	DDRD = 0x00;

	TCCR3A = 0x00;
	TCCR3B = 0x19;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;

	EICRA = 0xFF;
	EICRB = 0xFF;
	EIMSK = 0xFF;
	EIFR = 0xFF;
	
	sei();

	while(1)
	{
		if(sound_flag)
		{
			_delay_ms(500);
			TCCR3A = 0x00;
			sound_flag=0;
		}
	}

	return 0;
}

SIGNAL(INT0_vect)
{
	cli();

	ICR3 = 7372800/DoReMi[0]/10;
	TCCR3A = 0x40;
	sound_flag=1;

	sei();
}

SIGNAL(INT1_vect)
{
	cli();

	ICR3 = 7372800/DoReMi[1]/10;
	TCCR3A = 0x40;
	sound_flag=1;

	sei();
}

SIGNAL(INT2_vect)
{
	cli();

	ICR3 = 7372800/DoReMi[2]/10;
	TCCR3A = 0x40;
	sound_flag=1;

	sei();
}

SIGNAL(INT3_vect)
{
	cli();

	ICR3 = 7372800/DoReMi[3]/10;
	TCCR3A = 0x40;
	sound_flag=1;

	sei();
}

SIGNAL(INT4_vect)
{
	cli();

	ICR3 = 7372800/DoReMi[4]/10;
	TCCR3A = 0x40;
	sound_flag=1;

	sei();
}

SIGNAL(INT5_vect)
{
	cli();

	ICR3 = 7372800/DoReMi[5]/10;
	TCCR3A = 0x40;
	sound_flag=1;

	sei();
}

SIGNAL(INT6_vect)
{
	cli();

	ICR3 = 7372800/DoReMi[6]/10;
	TCCR3A = 0x40;
	sound_flag=1;

	sei();
}

SIGNAL(INT7_vect)
{
	cli();

	ICR3 = 7372800/DoReMi[7]/10;
	TCCR3A = 0x40;
	sound_flag=1;

	sei();
}