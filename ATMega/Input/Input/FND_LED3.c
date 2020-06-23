/*
 * FND_LED3.c
 *
 * Created: 2020-06-15 오전 11:44:46
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <time.h>

int main()
{
	unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,
									0x7c, 0x07, 0x7f, 0x67};
	unsigned int cnt = 0;
	unsigned int i = 0;
	DDRA = 0xff;
	DDRD = 0x0f;
	PORTA = 0x00;
	PORTD = 0x00;

	while(1)
	{
		if(cnt < 10)
		{
			for(i=0; i<10000; i++)
			{
				DDRD = 0x08;
				PORTA = FND_DATA_TBL[cnt];
			}
		}

		else if(cnt >= 10 && cnt < 100)
		{
			for(i=0; i<10000; i++)
			{
				DDRD = 0x04;
				PORTA = FND_DATA_TBL[cnt/10];
				DDRD = 0x08;
				PORTA = FND_DATA_TBL[cnt%10];
			}
		}

		else if(cnt >= 100 && cnt < 1000)
		{
			for(i=0; i<10000; i++)
			{
				DDRD = 0x02;
				PORTA = FND_DATA_TBL[cnt/100];
				DDRD = 0x04;
				PORTA = FND_DATA_TBL[(cnt%100)/10];
				DDRD = 0x08;
				PORTA = FND_DATA_TBL[cnt%10];
			}
		}

		else if(cnt >= 1000)
		{
			for(i=0; i<10000; i++)
			{
				DDRD = 0x01;
				PORTA = FND_DATA_TBL[cnt/1000];
				DDRD = 0x02;
				PORTA = FND_DATA_TBL[(cnt%1000)/100];
				DDRD = 0x04;
				PORTA = FND_DATA_TBL[(cnt%100)/10];
				DDRD = 0x08;
				PORTA = FND_DATA_TBL[cnt%10];
			}
		}
		
		cnt++;
	}

	return 0;
}