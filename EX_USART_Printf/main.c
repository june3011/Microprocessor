#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart_printf.h"


int main() {
	USART_Init();	// - USART1 초기화
	stdout = &device;
	
	while (1) {
		printf("Hello World\n");
		_delay_ms(1000);
	}
	return 0;
}
