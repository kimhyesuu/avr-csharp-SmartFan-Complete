// 하드웨어 구성
// HC-SR04 소음파 센서
// Trig 핀 : PORTE.6에 연결
// Echo 핀 : PE4(상승에지) 와 PE5(하강에지)에 연결
// 
#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include "uart0.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

unsigned int time_to_Cm(unsigned int time);
unsigned int Height(unsigned int time);
volatile int distance_time;
extern volatile int count;				// 오버플로가 발생한 횟수

ISR(INT4_vect)
{
	TCNT2 = 0;   // 상승에지에서 TCNT2를 clear
}
ISR(INT5_vect)
{
	distance_time = TCNT2;   // 하강에지에서 TCNT2값을 저장
}
void timer0_init(void)
{
	// 분주비를 1024로 설정
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	//  1024/16000000 = 256 / 16000 => 1/64 ==> 0.015625sec
	//  0.015625sec  ==> 15 ms 마다 over flow Int가 발생
	TIMSK |= (1 << TOIE0);			// 오버플로 인터럽트 허용
}
int utrasenor(void)
{
	unsigned int cm=0;
	
	stdout = &OUTPUT;
	//stdin  = &INPUT;
	UART0_init();
	
    EICRB = 0b00001011;
	//			  EXT4(PE4) 상승에지
	//            EXT5(PE5) 하강에지 비동기 
	EIMSK = 0b00110000;  // EXT5, EXT4 인터럽트를 enable 한다. 
	DDRE = 0b01000000;   // PORTE.6 번을 트리거 출력 모드로 setting 한다. 
	
	Timer2_Init();
	timer0_init();

	sei();
	printf("Ultra Sonic Test !!!!\n");
    while (1) 
    {
		if (distance_time != 0)
		{
			cm=time_to_Cm(distance_time);
			printf("%d: cm\r\n",  cm);
			distance_time=0;
		}
		if (count >= 64)      // 1000ms 
		{
			count = 0;
			PORTE |= 0b01000000;    // 트리거핀 PORTE.6번을 HIGH
			_delay_us(10);
			PORTE &= 0b10111111;    // 트리거핀 PORTE.6번을 LOW로 출력
			// _delay_ms(1000);
			// FND_update(Height(distance_time));			
		}
	}
}
unsigned int time_to_Cm(unsigned int time)
{	
 	unsigned int Cm=0;
	 
	Cm = (time+1)*64/58;
	return Cm;
}
unsigned int Height(unsigned int time)
{
	unsigned int Cm=0, height=0;
	
	Cm = (unsigned int)((time+1)*64/58);
	height = 200 - Cm;
	return height;
}
