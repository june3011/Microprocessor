#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/*#include <avr/iom128a.h>*/

#define LED_DDR DDRB
#define LED_PORT PORTB

void init_EINT();

//int flag = 1;

int main(void)
{
	// 초기화
	LED_DDR = 0xff;
	init_EINT();  
	
	// Global Interrupt 활성화
	sei();
	
	while(1)	
	{
		;
	}
	return 0;
}

void init_EINT()
{	// 인터럽트 관련 함수
	
// 	EICRB |= ((1<<ISC41) | (0<<ISC40));		// Falling Edge 입력이 인터럽트를 트리거
// 	EIMSK |= (1<<INT4);						// External Interrupt4 Enable
// 	EICRB |= ((1<<ISC51) | (0<<ISC50));
// 	EIMSK |= (1<<INT4);
	
	
	EICRB |= (((1<<ISC41) | (0<<ISC40)) | ((1<<ISC51) | (0<<ISC50)));
	EIMSK |= ((1<<INT4) | (1<<INT5));
	
}


// ISR(INT4_vect)
// {	// 인터럽트 들어올 때마다 자동 실행
// 	if (flag == 1){
// 		LED_PORT = 0x00;
// 		flag = 0;
// 	} else{
// 		LED_PORT = 0xff;
// 		flag = 1;
// 	}
// }

ISR(INT4_vect)
{
	
	LED_PORT = 0xff;
	
}

ISR(INT5_vect)
{
	
	LED_PORT = 0x00;
	
}