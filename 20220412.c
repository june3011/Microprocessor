/*
 * Segment.c
 *
 * Created: 2022-04-12 오후 2:02:09
 * Author : DGSW
 */ 

#include <util/delay.h>
#include <avr/io.h>
#define SW_DDR DDRC
#define SW_PIN PINC
#define SGMENT_DDR DDRB
#define SGMENT_PORT PORTB

int number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int abc[6] = {0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void AllFND();
void NumAndEng();
void EachNumber();

int main(void)
{
	SW_DDR = 0x00;
	SGMENT_DDR = 0xff;
	SGMENT_PORT = 0x00;
	
	//AllFND();
	//NumAndEng();
	EachNumber();
	
	
    /* Replace with your application code */
    
}

void AllFND()
{
	while(1)
	{
		SGMENT_PORT = 0xff;
		_delay_ms(2000);
		SGMENT_PORT = 0x00;
		_delay_ms(2000);
	}
}

void NumAndEng()
{
	while(1)	
	{
		// 숫자 0~9까지 출력
		for(int i=0; i<10; i++){
			SGMENT_PORT = number[i];
			_delay_ms(3000);
			SGMENT_PORT = 0x00;
			_delay_ms(3000);
		}
		
		for(int i=0; i<6; i++){
			SGMENT_PORT = abc[i];
			_delay_ms(3000);
			SGMENT_PORT = 0x00;
			_delay_ms(3000);
		}
	}
}

void EachNumber()
{
	while (1)
	{
		// 1111 1011
		// 0000 0001
		// 0000 0001
		//int number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
		for(int i=0;i<8;i++){
			if((SW_PIN^0xff)>>i==1){
				SGMENT_PORT = number[i+1];
			}
		}
		// 		if(SW_PIN==1){
		// 			SGMENT_PORT = number[1];
		// 			}else if(SW_PIN>>1==1){
		// 			SGMENT_PORT = number[2];
		// 			}else if(SW_PIN>>2==1){
		// 			SGMENT_PORT = number[3];
		// 			}else if(SW_PIN>>3==1){
		// 			SGMENT_PORT = number[4];
		// 			}else if(SW_PIN>>4==1){
		// 			SGMENT_PORT = number[5];
		// 			}else if(SW_PIN>>5==1){
		// 			SGMENT_PORT = number[6];
		// 			}else if(SW_PIN>>6==1){
		// 			SGMENT_PORT = number[7];
		// 			}else if(SW_PIN>>7==1){
		// 			SGMENT_PORT = number[8];
		// 		}
	}
}