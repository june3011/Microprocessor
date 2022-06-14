/*
 * EX_Light.c
 *
 * Created: 2021-12-06 오전 8:33:33
 * Author : anece
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart_printf.h"
#include "tlcd.h"

#define BAUD_RATE 51

// USART 제어를 위한 전역 변수 선언
volatile unsigned char rxData;		// 송수신 데이터 저장 변수

char flag=0;

/* == ADC 초기화 함수 구현 ============================================================================ */
void Init_ADC()
{
	//- ADC1 채널, AREF 기준 전압 => AVCC로 H/W 설정 
	ADMUX  = (1<<REFS0) | (1<<MUX0) | (1<<flag);	// 0 일 때는 조도센서, 1 일 때는 온도센서
			                          
	//- 채널, 활성화, 프리스케일 설정
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);	
}

/* == ADC 변환 함수 구현 ============================================================================== */
unsigned int startADConverter()
{
	unsigned int result;

	cli();									//- ADC 변환 중 인터럽트 금지

	ADCSRA |= (1<<ADSC);					//- ADC 변환 시작
	while(!(ADCSRA & (1<<ADIF))) ;			//- ADC 변환 완료 신호 대기

	result = ADCL;		            	 	//- 변환 결과 저장
	result |= ((ADCH & 0x03) << 8);

	sei();									//- 인터럽트 허용

	return result;
}



/* == Main 함수 구현 ================================================================================= */
int main(void)
{
	unsigned int AdcResult;							//- 변환값 저장 변수 

	USART_Init();		                            //- USART1 초기화
	stdout = &device;	                            //- 표준출력으로 사용할 장치 설정

	TXT_LCD_Init();

	
	while(1)
	{
		Init_ADC();										//- ADC 초기화
		
		AdcResult = startADConverter();				//- ADC 변환 실행
		
		if (flag == 1){
			printf("DEGREE %d\n", AdcResult);
			char str[20];
			sprintf(str, " DEGREE %d", AdcResult);
			SendText(DDRAM_ADDR | 0x00, str);
		}
		else if (flag == 0){
			printf("LIGHT %d\n", AdcResult);
			char str[20];
			sprintf(str, " LIGHT %d", AdcResult);
			SendText(DDRAM_ADDR | 0x00, str);
		}
		_delay_ms(2000);
		SendCommand(CMD_CLEAR_DISPLAY);
		_delay_us(2000);
	}
	return 0;
}


// USART Interrupt 함수
ISR(USART1_RX_vect)
{
	// 수신 버퍼에서 읽어 온 데이터를 다시 송신
	if (UCSR1A & (1<<RXC1))		// 읽지 않은 데이터가 있다면
	{
		rxData = UDR1;					// 수신 버퍼 데이터를 변수에 저장
		USART_Transmitter(rxData);		// PC로 전송해서 확인
		
		if (rxData == 'T'){
			flag = 1;
		}
		else if(rxData == 'L'){
			flag = 0;
		}
	}
}