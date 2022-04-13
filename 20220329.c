/*
 * Hello_LED.c
 *
 * Created: 2022-03-29 오후 2:04:20
 * Author : DGSW
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdio.h>

// SENSOR PIN 선언 -----------------------------------------
#define LED_DDR DDRE	// 입력 & 출력 모드 설정 레지스터
#define LED_PORT PORTE	// 출력 데이터 저장 레지스터

void allLED();
void stairLED();
void stepByStepLED();


// 엔트로 포인트 함수 ---------------------------------------
int main() {
	stepByStepLED();
}


void allLED(){
	int cnt=0;
	// LED 초기화
	LED_DDR = 0xFF;		// 0b1111 1111  => 출력모드 설정
	LED_PORT = 0xFF;	// 0b1111 1111  => 0번~7번포트에 HIGH 출력
	
	/* Replace with your application code */
	while(cnt<10) {
		// LED ON
		LED_PORT = 0xFF;
		_delay_ms(1000);
		
		// LED OFF
		LED_PORT = 0x00;
		_delay_ms(1000);
		cnt++;
	}
}


void stairLED(){
	LED_DDR = 0xFF;		// 0b1111 1111 => 출력모드 설정
	LED_PORT = 0x01;	// 0b0000 0000
	for(int i=0;i<8;i++){
		_delay_ms(500);
		LED_PORT <<= 1;		// 한 칸 밀고 
		LED_PORT += 1;		// 1 더해주기
		
	}
	for(int i=7;i>=0;i--){
		LED_PORT >>= 1;		// 한 칸 반대로 밀기
		_delay_ms(500);
	}
}


void stepByStepLED(){
	{
	DDRB = 0xFF;
	LED_DDR = 0xFF;
	LED_PORT = 0x01;
	for(int i=0;i<8;i++){
		_delay_ms(1000);
		LED_PORT <<= 1;	// 한 칸 밀기
		PORTB = !PORTB;
		}
	PORTB=0x01;
	}
}