/*
 * LCD.c
 *
 * Created: 2020-06-16 오후 1:51:34
 * Author : PKNU
 */ 
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

void gugudan(unsigned char a);

unsigned char switch_flag = 0;
unsigned char i;

int main(void)
{
    Byte str[16] = "GuGuDan!!";
	Byte str1[16] = "Press Button~!";
	DDRA = 0xFF;
	DDRD = 0x00;
	
	LcdInit_4bit(); // LCD 초기화 LCD[2][16]
	/*
	Lcd_Pos(0, 0);
	Lcd_STR(str);
	Lcd_Pos(1, 0);
	Lcd_STR(str1);
	*/
    while (1) 
    {
		sprintf(str, "%s", "GuGuDan!!");
		sprintf(str1, "%s", "Press Button~!");
		Lcd_Pos(0, 0);
		Lcd_STR(str);
		Lcd_Pos(1, 0);
		Lcd_STR(str1);
		switch_flag = PIND;

		switch(switch_flag)
		{
			case 0x01: // 2단
				gugudan(2);
				break;
			case 0x02: // 3단
				gugudan(3);
				break;
			case 0x04: // 4단
				gugudan(4);
				break;
			case 0x08: // 5단
				gugudan(5);
				break;
			case 0x10: // 6단
				gugudan(6);
				break;
			case 0x20: // 7단
				gugudan(7);
				break;
			case 0x40: // 8단
				gugudan(8);
				break;
			case 0x80: // 9단
				gugudan(9);
				break;
		}
    }

	return 0;
}

void gugudan(unsigned char a)
{
	Byte str[16], str1[16];
	unsigned char i;

	for(i=1; i<10; i++)
	{
		Lcd_Clear();
		Lcd_Pos(0, 0);
		sprintf(str, "%d%s", a, " Dan :");
		Lcd_STR(str);
		Lcd_Pos(1, 0);
		sprintf(str1, "%d%s%d%s%d", a, " * ", i, " = ", a*i);
		Lcd_STR(str1);
		_delay_ms(500);
	}Lcd_Clear();
}