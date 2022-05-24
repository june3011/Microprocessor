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

// USART 제어를 위한 전역 변수 선언
volatile unsigned char rxData;		// 송수신 데이터 저장 변수


void USART_Init();
void USART_Transmitter(unsigned char txData);



int main(void)
{
	
	USART_Init();						// USART1 초기화
	
	sei();								// 글로벌 인터럽트를 활성화
	
	USART_Transmitter('S');
	
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
	if (UCSR1A & (1<<RXC1))
	{
		rxData = UDR1;					// 수신 버퍼 데이터를 변수에 저장
		USART_Transmitter(rxData);		// PC로 전송해서 확인
	}
}