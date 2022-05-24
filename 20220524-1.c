/*
 * SH_USART_TX.cpp
 *
 * Created: 2022-05-24 오후 1:47:00
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>		// delay ㅎ마수 사용을 위한 헤더파일

// USART 제어를 위한 정의
#define BAUD_RATE 51		// Atmega128 데이터 시트 51 (192000bps) 값

void USART_Init();
void USART_Transmitter(unsigned char txData);

int main(void)
{
	
	unsigned char buffer[] = "Hello ATmega128!\r\n";
	int i;
	
	USART_Init();								// USART1 초기화
	
    /* Replace with your application code */
    while (1) 
    {
		for (i=0; i<sizeof(buffer); i++){		// 1바이트 씩 송신
			if (!buffer[i])	break;
			
			USART_Transmitter(buffer[i]);
		}
		_delay_ms(1000);
    }
	return 0;
}

// USART 초기화 함수
void USART_Init()
{
	UBRR1H = (unsigned char) BAUD_RATE >> 8;	// 전송 속도 설정
	UBRR1L = (unsigned char) BAUD_RATE;
	
	UCSR1B = (1<<TXEN1);					// 송신 기능 설정
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);		//  No parity, 1 Stop Bit, 8 bit Data
}

// USART Transmitter 함수
void USART_Transmitter(unsigned char txData){
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = txData;
}