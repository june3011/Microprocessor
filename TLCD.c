/*
 * EX_TLCD.c
 *
 * Created: 2022-05-31 오후 2:27:36
 * Author : user
 */ 

#include "tlcd.h"
#include <avr/io.h>
#include <util/delay.h>		// delay 함수 사용을 위한 헤더파일
#include <avr/interrupt.h>	// RX 수신 처리 인터럽트
#include <string.h>			// strcpy

#define BAUD_RATE 51		// Atmega128 데이터 시트 51 (192000bps) 값


volatile unsigned char rxData;		// 송수신 데이터 저장 변수


void USART_Init();
void USART_Transmitter(unsigned char txData);

int count = 0x00;

int main(void)
{
    
	TXT_LCD_Init();									// LCD 제어 설정 및 초기화
	
	USART_Init();						// USART1 초기화
	
	sei();								// 글로벌 인터럽트를 활성화
	
	USART_Transmitter('S');
	
    while (1) 
    {
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

// USART Interrupt 함수
ISR(USART1_RX_vect)
{
	// 수신 버퍼에서 읽어 온 데이터를 다시 송신
	if (UCSR1A & (1<<RXC1))
	{
		rxData = UDR1;					// 수신 버퍼 데이터를 변수에 저장
		USART_Transmitter(rxData);		// PC로 전송해서 확인
		
		int n = 0;
		
		//if (rxData != '\n'){
				//SendData(rxData);
			//if (SendCommand(DDRAM_FE_ADDR)){
				//SendCommand(DDRAM_SS_ADDR);
				//SendData(rxData);
			//}
		//}
		
		
		
		if (rxData != '\n'){
			if (count == 0x10){
				count = 0x40;
			}
			//if (count == 0x50){
				//SendCommand(CMD_CLEAR_DISPLAY);
				//SendCommand(DDRAM_ADDR | 0x00);
				//count = -0x01;
			//}
			if (count == 0x50){
				count = 0x00;
				SendCommand(CMD_CLEAR_DISPLAY);
				SendCommand(DDRAM_ADDR | count);
				_delay_ms(2000);
				SendData(rxData);
				count++;
				return;
			}
			SendCommand(DDRAM_ADDR | count++);
			SendData(rxData);
		}
		
		
		
		
		n++;
		
		//SendText(DDRAM_ADDR | 0x00, "hihihhi");			// 1행에 문자 출력
		//SendText(DDRAM_ADDR | 0x40, "hihi");				// 2행에 문자 출력	
		
	}
}
