/*
 * EX_Push.c
 *
 * Created: 2022-04-05 오후 2:02:34
 * Author : DGSW
 */ 

#define LED_DDR DDRE
#define LED_PORT PORTE
#define SW_DDR DDRC
#define SW_PIN PINC
#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
	LED_DDR = 0xFF;		// 출력모드로 설정
	LED_PORT = 0x00;	// 다 꺼진 상태로 초기화
	SW_DDR = 0x00;		// 입력모드로 설정, 스위치는 입력장치라서 초기화 할 필요 없음
	BUZZ_DDR = 0x01;	// 출력모드로 설정
	BUZZ_PORT = 0x01;	// 1이 꺼진거 0이 켜진거
	
	
    /* Replace with your application code */
    while (1) 
    {	// 스위치는 안 눌렸을 때 1이고, 눌렸을 때 0이여서
		// 만약 스위치 0번을 눌렀다면 1 1 1 1 1 1 1 0 이므로
		// LED를						0 0 0 0 0 0 0 1로 바꿔서
		// 0번 스위치 켜주기
		// 즉, 누른 스위치의 해당하는 LED켜줌
		LED_PORT = ~SW_PIN;	
		int value=LED_PORT;
		
		
		// 모든 버튼을 누르면 부저 울리기
		//if(LED_PORT == 0xff){
			//BUZZ_PORT = 0x00;
		//}
		//else{
			//BUZZ_PORT = 0x01;
		//}
		
		
		if((value & 1)==1){
			BUZZ_PORT = 0x00;
		}else if(((value>>1)&1)==1){
			BUZZ_PORT = 0x01;
		}else if(((value>>2)&1)==1){
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
			_delay_ms(5000);
			
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
			_delay_ms(5000);
			
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
			_delay_ms(2500);
			
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
			_delay_ms(2500);
			
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
			_delay_ms(5000);
			
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
			_delay_ms(2500);
			
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
			_delay_ms(2500);
			
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
			_delay_ms(2500);
			
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
			_delay_ms(5000);
			
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
			_delay_ms(2000);
			
			BUZZ_PORT = 0x00;
			_delay_ms(1000);
			BUZZ_PORT = 0x01;
			
		}	}
		
		
	}
}