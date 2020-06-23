/*
 * UARTPCData.c
 *
 * Created: 2020-06-17 오후 3:46:40
 *  Author: PKNU
 */ 

#include <avr/io.h>

void putch(unsigned char data)
{
	while((UCSR0A & 0x20)==0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

int main()
{
	unsigned char text[] = "\r\nWelcome! edgeiLAB\r\n USART 0 Test Program.\r\n";
	unsigned char echo[] = "ECHO >> ";
	unsigned char i=0;

	DDRE = 0xFE;

	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;

	UBRR0H = 0x00;
	UBRR0L = 0x03;

	while(text[i]!='\0')
		putch(text[i++]);

	i=0;
	while(echo[i]!='\0')
		putch(echo[i++]);

	while(1)
	{
		putch(getch());
	}

	return 0;
}