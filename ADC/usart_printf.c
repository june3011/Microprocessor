#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart_printf.h"

#define LED_DDR DDRB
#define LED_PORT PORTB

#define CDS_MAX_VALUE 919


void Init_ADC() {
	// - ADC1 채널, AREF 기준 전압 및 채널을 선택
	ADMUX = 0x00;
	// - 채널, 활성화, 프리스케일 설정
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

unsigned int CDS_StartADConverter() {
	
	unsigned int result;
	
	cli();	// - ADC 변환 중 인터럽트 금지
	
	ADCSRA |= (1<<ADSC);	// - ADC 변환 시작
	while(!(ADCSRA & (1<<ADIF))) ;	// - ADC 변환 완료 신호 대기
	
	result = ADCL;	// - 변환 결과 저장
	result |= ((ADCH & 0x03) << 8);
	
	sei();		// - 인터럽트 허용
	
	return result;
}

int main(void) {
	unsigned int AdcResult;	// - 변환값 저장 변수
	
	Init_ADC();
	USART_Init();	// - USART1 초기화
	LED_DDR = 0xFF;
	LED_PORT = 0x00;
	
	stdout = &device;
	
    while (1) {
		AdcResult = CDS_StartADConverter();	// - ADC 변환 실행
		printf("AdcResult : %d\n", AdcResult);
		printf("??");
		if (AdcResult >= CDS_MAX_VALUE) {
			LED_PORT = 0xFF;
			
		} else {
			LED_PORT = 0x00;
		}
		
		_delay_ms(5000);
    }
	
	return 0;
}

