/*
 * 2022 1s 1st performanceEvaluation.c
 *
 * Created: 2022-04-19 오후 1:35:58
 * Author : DGSW
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define SW_DDR DDRC	
#define SW_PIN PINC
#define FND_DDR DDRB
#define FND_PORT PORTB
#define LED_DDR DDRE
#define LED_PORT PORTE
#define BUZZ_DDR DDRD
#define BUZZ_PORT PORTD


int number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int abc[6] = {0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
int NumAndEng[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
					//0		1		2	3		4	5		6	7		8	9		a	b		c	d		e	f

void Question1(){
	while (1)
	{
		if((SW_PIN^0xff)==0x01){	// 1번스위치를 누르면
			for(int i=1;i<10;i++){	// 1 ~ 9
				FND_PORT = number[i];
				_delay_ms(1000);
				if(((SW_PIN^0xff)>>4)==0x01){	// 중간에 5번째 버튼이 눌리면 불끄기
					FND_PORT = 0x00;
					break;
				}
			}
			} else if(((SW_PIN^0xff)>>1)==0x01){	// 2번스위치를 누르면
			for(int i=2;i<10;i+=2){					// 2, 4, 6, 8
				FND_PORT = number[i];
				_delay_ms(1000);
				if(((SW_PIN^0xff)>>4)==0x01){	// 중간에 5번째 버튼이 눌리면 불끄기
					FND_PORT = 0x00;
					break;
				}
			}
			} else if(((SW_PIN^0xff)>>2)==0x01){	// 3번스위치를 누르면
			for(int i=3;i<10;i+=3){					// 3, 6, 9
				FND_PORT = number[i];
				_delay_ms(1000);
				if(((SW_PIN^0xff)>>4)==0x01){	// 중간에 5번째 버튼이 눌리면 불끄기
					FND_PORT = 0x00;
					break;
				}
			}
			} else if(((SW_PIN^0xff)>>3)==0x01){	// 4번스위치를 누르면
			for(int i=0;i<6;i++){					// a ~ f
				FND_PORT = abc[i];
				_delay_ms(1000);
				if(((SW_PIN^0xff)>>4)==0x01){	// 중간에 5번째 버튼이 눌리면 불끄기
					FND_PORT = 0x00;
					break;
				}
			}
			} else if(((SW_PIN^0xff)>>4)==0x01){
			FND_PORT = 0x00;
		}
	}
}


void Question2(){
	while(1)
	{	// 무한반복하지 않을 것이라면 while문 벗기기
		// ON
		for(int i=0;i<8;i++){
			LED_PORT <<= 1;
			LED_PORT += 1;
			if(i==7){
				BUZZ_PORT = 0x00;
			}
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
		}
		// OFF
		for(int i=0;i<8;i++){
			LED_PORT >>= 1;
			if(i==7){
				BUZZ_PORT = 0x00;
			}
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
		}
	}
}


void Question3(){
	
	int arr[6] = {0x06, 0x4F, 0x6D, 0x07, 0x77, 0x71};
	for(int i=0;i<3;i++)
	{
		for(int i=0;i<6;i++){
			FND_PORT = arr[i];
			if(i<1){
				LED_PORT += 1;
				} else if(i<4){
				LED_PORT <<= 2;
				LED_PORT += 3;
				} else if(i==4) {
				LED_PORT = 0xff;
				} else {
				LED_PORT = 0x00;
			}
			_delay_ms(1000);
		}
	}
}


int main(void)
{
	SW_DDR = 0x00;
	FND_DDR = 0xff;
	FND_PORT = 0x00;
	LED_DDR = 0xff;
	LED_PORT = 0x00;
	BUZZ_DDR = 0xff;
	BUZZ_PORT = 0x01;	// 부저는 0이 켜진거
	
    /* Replace with your application code */
	
	
    //Question1();
	//Question2();
	Question3();
	
	
}

