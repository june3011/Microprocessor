/*
 * EX_USART_RTX.c
 *
 * Created: 2022-05-24 오후 2:58:31
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>		// delay 함수 사용을 위한 헤더파일
#include <avr/interrupt.h>	// RX 수신 처리 인터럽트

// USART 제어를 위한 정의
#define BAUD_RATE 51		// Atmega128 데이터 시트 51 (192000bps) 값

#define LED_DDR DDRB
#define LED_PORT PORTB

// USART 제어를 위한 전역 변수 선언
volatile unsigned char rxData;		// 송수신 데이터 저장 변수


void USART_Init();
void USART_Transmitter(unsigned char txData);



int main(void)
{
	
	USART_Init();						// USART1 초기화
	
	sei();								// 글로벌 인터럽트를 활성화
	
	USART_Transmitter('S');
	
	LED_PORT = 0x00;
	
	/* Replace with your application code */
	while (1)
	{
		;
	}
	return 0;
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

// USART Interrupt 함수
ISR(USART1_RX_vect)
{
	// 수신 버퍼에서 읽어 온 데이터를 다시 송신
	if (UCSR1A & (1<<RXC1))		// 읽지 않은 데이터가 있다면
	{

		rxData = UDR1;					// 수신 버퍼 데이터를 변수에 저장
		USART_Transmitter(rxData);		// PC로 전송해서 확인
		
		// 입력하면 뒤에 엔터까지 같이 처리되서 
		// 그냥 LED_PORT = 0x00; 을 해버리면 켜졌다가 금방 다시 꺼지게 됨
		// 엔터가 아닐 때 LED_PORT 초기화
		//if (rxData != '\n'){	
			//LED_PORT = 0x00;
		//}

		for (int i=0; i<rxData-'0'; i++){	// '0' = 48
			if (i == 0){			// 처음에 초기화 해주고 시작
				LED_PORT = 0x00;
			}
			LED_PORT <<= 1;
			LED_PORT |= 1;
		}
	}
}



// USART Interrupt 함수
//ISR(USART1_RX_vect)
//{
	//// 수신 버퍼에서 읽어 온 데이터를 다시 송신
	//if (UCSR1A & (1<<RXC1))
	//{
		//rxData = UDR1;					// 수신 버퍼 데이터를 변수에 저장
		//USART_Transmitter(rxData);		// PC로 전송해서 확인
		//
		//
		//switch(rxData)
		//{
			//case '1':
				//for (int i; i<1; i++){
					//LED_PORT <<= 1;
					//LED_PORT += 1;
				//}
				//break;
			//case '2':
				//for (int i; i<2; i++){
					//LED_PORT <<= 1;
					//LED_PORT += 1;
				//}
				//break;
			//case '3':
				//for (int i; i<3; i++){
					//LED_PORT <<= 1;
					//LED_PORT += 1;
				//}
				//break;
			//case '4':
				//for (int i; i<4; i++){
					//LED_PORT <<= 1;
					//LED_PORT += 1;
				//}
				//break;
			//case '5':
				//for (int i; i<5; i++){
					//LED_PORT <<= 1;
					//LED_PORT += 1;
				//}
				//break;
			//case '6':
				//for (int i; i<6; i++){
					//LED_PORT <<= 1;
					//LED_PORT += 1;
				//}
				//break;
			//case '7':
				//for (int i; i<7; i++){
					//LED_PORT <<= 1;
					//LED_PORT += 1;
				//}
				//break;
			//case '8':
				//for (int i; i<8; i++){
					//LED_PORT <<= 1;
					//LED_PORT += 1;
				//}
				//break;
		//}
	//}
//}