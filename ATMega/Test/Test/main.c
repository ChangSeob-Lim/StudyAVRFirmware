/*
 * Test.c
 *
 * Created: 2020-06-18 오전 10:16:40
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

unsigned char STOP = 0; // 정지
unsigned int i;
volatile unsigned int ADC_result=0; // CDS의 ADC 변환값 저장 변수

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046}; // 음계 주파수
unsigned char CW[4] = {0x80, 0x40, 0x20, 0x10}; // 스텝 모터 시계 방향
unsigned char CCW[4] = {0x10, 0x20, 0x40, 0x80}; // 스텝 모터 반시계 방향

void putch(unsigned char data);
void putch_Str(char *str);
unsigned char getch();

void playLED();
void playCDS();
void playPiano();
void playStepMoter();

int main(void)
{
	unsigned char Menu;

	// 포트 설정
	DDRA = 0xFF; // LED 설정, PA -> LED 연결
	DDRB = 0x80; // PB7 -> 부저 연결
	DDRC = 0x20; // 스텝모터 설정
	DDRD = 0xF0; // PD4~7 -> 스텝모터 0~3 연결, 인터럽터 버튼 0번 설정
	DDRE = 0xFE; // UART 설정
	DDRF = 0x02; // CDS 설정 PF0-> cds_out 입력, PF1->cds_in 출력	
	
	// LED 설정
	PORTA = 0x00;

	// CDS 설정
	PORTF = 0x02; // cds_in VCC

	ADMUX = 0x00;
	ADCSRA = 0x87;
	
	// 피아노 설정
	TCCR1A |= 0x00;
	TCCR1B |= 0x19;
	TCCR1C = 0x00;
	TCNT1 = 0x0000;

	// 스텝모터 설정
	PORTC &= 0x20;

	// UART 설정
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;

	UBRR0H = 0x00;
	UBRR0L = 0x03; // 115200

	// 인터럽트 설정
	EICRA = 0x03;
	EIMSK = 0x01;
	EIFR = 0x01;

	sei();

    while (1) 
    {
		putch_Str("\n++++ Menu ++++\n");
		putch_Str("L : LED\n");
		putch_Str("C : CDS\n");
		putch_Str("P : Piano\n");
		putch_Str("S : Step Motor(f:CW, r:CCW)\n");

		Menu = getch();

		if(Menu == 'L' || Menu == 'l') // LED (키보드 L)
		{
			playLED(); // LED 동작 
		}
		else if(Menu == 'C' || Menu == 'c') // CDS (키보드 C)
		{
			playCDS(); // CDS 동작 
		}
		else if(Menu == 'P' || Menu == 'p') // 피아노 (키보드 P)
		{
			playPiano(); // 피아노 동작 (키보드 0~7번)
		}
		else if(Menu == 'S' || Menu == 's')
		{
			playStepMoter(Menu); // 스텝모터 동작 (키보드 S)
		}
    }

	return 0;
}

SIGNAL(INT0_vect)
{
	cli();

	STOP = 1;
	i = 9999;
	PORTA = 0x00;
	TCCR1A |= 0x00;

	sei();
}

void playLED()
{
	unsigned char LED_Data = 0x00;
	putch_Str("Play LED\nExit: Press Button\n");

	while(1)
	{
		if(STOP)
		{
			STOP=0;
			return;
		}

		LED_Data = 0x01;
		for(i=0; i<7; i++)
		{
			PORTA = LED_Data;
			LED_Data <<= 1;
			_delay_ms(500);
		}

		if(STOP)
		{
			STOP=0;
			return;
		}

		for(i=0; i<8; i++)
		{
			PORTA = LED_Data;
			LED_Data >>= 1;
			_delay_ms(500);
		}
		LED_Data = 0x00;
	}
}

void playCDS()
{
	unsigned int AdData = 0;
	char CDS_data[] = "0000";
	putch_Str("Play CDS\nExit: Press Button\n");

	while(1)
	{
		if(STOP)
		{
			STOP=0;
			return;
		}

		ADCSRA |= 0x40;
		while((ADCSRA & 0x01)==0x00);
		AdData = ADC;
		putch_Str("CDS ADC_Data: ");
		sprintf(CDS_data, "%d\n", AdData);
		putch_Str(CDS_data);
		_delay_ms(500);	
	}
}

void playPiano()
{
	putch_Str("Play Piano (Press 0 ~ 7, Exit: X)\n");
	
	unsigned char piano;

	while(1)
	{
		if(STOP)
		{
			STOP=0;
			TCCR1A |= 0x00;
			return;
		}

		piano = getch();

		if(piano == '8') // 도~도까지
		{
			TCCR1A |= 0x0A;
			for(i=0; i<8; i++)
			{
				ICR1 = 7372800/DoReMi[i];
				OCR1C = ICR1/10;
				_delay_ms(250);
				OCR1C = 0x00;
			}
			TCCR1A |= 0x00;
		}
		else if(piano >= '0' && piano <= '7') // 하나씩 출력 0~7
		{
			TCCR1A |= 0x0A;
			ICR1 = 7372800/DoReMi[piano-'0'];
			OCR1C = ICR1/10;
			_delay_ms(250);
			OCR1C = 0x00;
			TCCR1A |= 0x00;
		}
		else if(piano == 'X' || piano == 'x')
		{
			TCCR1A |= 0x00;
			break;
		}
	}
}

void playStepMoter()
{
	putch_Str("Play StepMoter (Press Clockwise: F, Counterclockwise: R, Exit: X)\n");
	unsigned char location;
	
	while(1)
	{
		if(STOP)
		{
			STOP=0;
			return;
		}

		location = getch();

		// 스텝모터 시계 방향 동작 (키보드 f)
		if(location == 'F' || location == 'f')
		{
			for(i=0; i<120; i++)
			{if(STOP) return;
				PORTD = CW[i%4];
				_delay_ms(10);
			}
		}

		// 스텝모터 반시계 방향 동작 (키보드 r)
		else if(location == 'R' || location == 'r')
		{
			for(i=0; i<120; i++)
			{if(STOP) return;
				PORTD = CCW[i%4];
				_delay_ms(10);
			}
		}

		else if(location == 'X' || location == 'x')
		{
			break;
		}
	}
}

void putch(unsigned char data)
{
	while((UCSR0A & 0x20)==0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

void putch_Str(char *str)
{
	unsigned char i=0;
	while(str[i]!=0)
		putch(str[i++]);
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}