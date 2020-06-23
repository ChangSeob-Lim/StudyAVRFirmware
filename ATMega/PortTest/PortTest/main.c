/*
 * PortTest.c
 *
 * Created: 2020-06-12 오후 2:10:39
 * Author : PKNU
 */ 

#include <avr/io.h>

int main()
{
	DDRA = 0xFF; // 포트A를 출력으로 설정
	DDRB = 0xFF; // 포트B를 출력으로 설정
	DDRC = 0xFF; // 포트C를 출력으로 설정
	DDRD = 0xFF; // 포트D를 출력으로 설정
	DDRE = 0xFF; // 포트E를 출력으로 설정
	DDRF = 0xFF; // 포트F를 출력으로 설정
	DDRG = 0x1F; // 포트G를 출력으로 설정
	
	while(1)
	{
		PORTA = 0xFF; // A 출력 설정
		PORTB = 0xFF; // B 출력 설정
		PORTC = 0xFF; // C 출력 설정
		PORTD = 0xFF; // D 출력 설정
		PORTE = 0xFF; // E 출력 설정
		PORTF = 0xFF; // F 출력 설정
		PORTG = 0x1F; // G 출력 설정
	}
	
	return 0;
}