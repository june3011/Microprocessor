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

#define LED_DDR DDRE
#define LED_PORT PORTE


/* == ADC 초기화 함수 구현 ============================================================================ */
void Init_ADC()
{
	//- ADC1 채널, AREF 기준 전압 => AVCC로 H/W 설정 
	ADMUX  = (1<<REFS0) | (1<<MUX0);	
			                          
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

	Init_ADC();										//- ADC 초기화
	
	LED_DDR = 0xff;
	
	while(1)
	{
		AdcResult = startADConverter();				//- ADC 변환 실행
		printf("LIGHT %d\n", AdcResult);
		if (AdcResult > 400)	{
			LED_PORT = 0xff;
		}
		else {
			LED_PORT = 0x00;
		}
	}
	return 0;
}