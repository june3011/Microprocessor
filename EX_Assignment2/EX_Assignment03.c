/*
 * EX_Assignment03.c
 *
 * Created: 2022-06-14 오후 3:54:15
 * Author : user
 */ 

// UART로 입력받은 값에 따라 LED & BUZZER 제어하는 문제입니다.

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_DDR DDRE
#define LED_PORT PORTE
#define BUZZ_DDR DDRD0
#define BUZZ_PORT PORTD0

#define BAUD_RATE 51

// USART 제어를 위한 전역 변수 선언
volatile unsigned char rxData;		// 송수신 데이터 저장 변수



void USART_Init();
void USART_Transmitter(unsigned char txData);



int main(void)
{
    /* Replace with your application code */
	LED_DDR = 0xff;
	
	USART_Init();
	
	sei();		// 글로벌 인터럽트를 활성화
	
	USART_Transmitter();
	
    while (1) 
    {
		
    }
}


// USART Interrupt 함수
ISR(USART1_RX_vect)
{
	// 수신 버퍼에서 읽어 온 데이터를 다시 송신
	if (UCSR1A & (1<<RXC1))		// 읽지 않은 데이터가 있다면
	{
		int temp = 0x00;
		rxData = UDR1;					// 수신 버퍼 데이터를 변수에 저장
		USART_Transmitter(rxData);		// PC로 전송해서 확인
		
		if (rxData[0] == 'L'){
			if (rxData[2] == '1'){
				for (int i=0; i<rxData[1]-'0'; i++){
					if (i == 0){
						LED_PORT == 0x00;
					}
					LED_PORT <<= 1;
					LED_PORT |= 1;
				}
			} else if (rxData[2] == '0'){
				temp = 0x00;
				for (int i=0; i<rxData[1]-'0'; i++){
					LED_PORT = temp << i;
				}
			}
		} else if(rxData[0] == 'B'){
			if (rxData[1] == '1'){
				BUZZ_PORT = 0;
			}
			else if(rxData[1] == '0'){
				BUZZ_PORT = 1;
			}
		} else {
			;
		}
		
	}
}


// USART 초기화 함수
void USART_Init()
{
	UBRR1H = (unsigned char) BAUD_RATE >> 8;	// 전송 속도 설정
	UBRR1L = (unsigned char) BAUD_RATE;
	
	/*UCSR1B = (1<<TXEN1);					// 송신 기능 설정*/
	UCSR1B = (1<<TXEN1) | (1<<RXEN1) | (1<<RXCIE1);		// 송신, 수신, 수신인터럽트 기능 설정
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);		//  No parity, 1 Stop Bit, 8 bit Data
}

// USART Transmitter 함수
void USART_Transmitter(unsigned char txData){
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = txData;
}
