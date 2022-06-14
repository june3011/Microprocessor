/*
 * EX_Assignment01.c
 *
 * Created: 2022-06-14 오후 2:57:23
 * Author : user
 */ 

// ex01 스위치 버튼 8개를 활용하여 FND & LED를 제어하는 문제입니다.

#include <avr/io.h>
#include <util/delay.h>

#define SW_DDR DDRC
#define SW_PIN PINC
#define LED_DDR DDRE
#define LED_PORT PORTE
#define FND_DDR DDRB
#define FND_PORT PORTB



int main(void)
{
    /* Replace with your application code */
	SW_DDR = 0x00;
	LED_DDR = 0xff;
	FND_DDR = 0x00;
	
	LED_PORT = 0x00;
	FND_PORT = 0x00;

	int FND_ARR[8] = {0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F};
		
    while (1) 
    {
		for (int i=0; i<8; i++){
			if (((SW_PIN^0xff) >> i) == 1) {
				LED_PORT = 0x01;
				for (int j=0; j<i; j++){
					LED_PORT <<= 1;
					LED_PORT |= 1;
				}
				FND_PORT = FND_ARR[i];
			}
		}
    }
}

