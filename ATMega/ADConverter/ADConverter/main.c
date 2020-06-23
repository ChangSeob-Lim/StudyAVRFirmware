/*
 * ADConverter.c
 *
 * Created: 2020-06-16 오후 4:54:59
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "Lcd.h"

int main(void)
{
	unsigned int AdData = 0;
	Byte str[16] = " Cds : ";

	DDRA = 0xFF;
	DDRF = 0x02;
	PORTF = 0x02;

	LcdInit_4bit();

	Lcd_Pos(0, 0);
	Lcd_STR(str);

	ADMUX = 0x00; // ADC0선택, single mode, 0번 채널, 3.3V 외부 기준전압(AREF);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); //0x86; // ADC 허가, 64분주비

    while (1) 
    {
		ADCSRA |= 0x40;
		while((ADCSRA & 0x10) == 0x00);
		AdData = ADC;
		Lcd_Pos(0, 0);

		sprintf(str, " Cds: %d", AdData);
		Lcd_STR(str);

		_delay_ms(500);
		Lcd_Clear();
    }

	return 0;
}

