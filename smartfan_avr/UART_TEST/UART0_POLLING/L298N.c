   /*
 * L298N_TEST.c
 *
 * Created: 2020-04-16 오후 4:58:47
 * Author : kccistc
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DELAY					2000
#define PE0							0
#define PE2							2
#define PE3							3
#define PE4							4

// 3번 Timer / Counter 설정
void init_pwm(void)
{
	// 모드 14, 8비트 고속 PWM 모드  Timer counter 3번 
	TCCR3A |= (1 << WGM30);
	TCCR3B |= (1 << WGM32);
	
	// 비반전 모드  TOP : 0xFF  비교일치값 : OCR3B 레지스터
	TCCR3A |= (1 << COM3A1);
	
	TCCR3B |= (1 << CS31) | (1 << CS30);		// 분주율 64
	                                            // 16000000HZ / 64 ==> 250000Hz
											    // 256 / 250000 ==> 1.02ms 
												// 127 / 250000 ==> 0.5ms 

	OCR3A = 0;
}
/*
* 1. DC 모터드라이버 L298N 과 Atmega128 결선방법
     (DC 5V 모터 연결)
	 1) LN298N DC5V와 DC12V 연결 단자를 쇼트 시킨다.
	 2) LN298N의 OUT1에 DC모터 +단자를 OUT2에 모터의 -단자를 연결 한다.
	    주의: DC모터에 DC 5v인가시 모터가 시계방향으로 회전 기준으로 + - 를 구분
	 3) LN298N ENA단자에 연결된 딥 스위치를  뺴낸다.
	 4) LN298N   ATMEGA128A
	    ------   -----------
		 ENA       PORTE.4
		 IN1       PORTE.0
		 IN2       PORTE.2      
	 
2. 모터 제어를 위한 핀들을 출력으로 설정
  PE0 : 방향 설정
  PE2 : Enable 단자
  PE4 : PWM 제어 단자
  in1(PE0) in2(PE2)
    0         1   :  역방향 회전
    1         0   :  정방향 회전
    1         1   : 브레이크
*/
int motor(void)
{

	DDRE |=(1 << PE0)|(1 << PE2)|(1 << PE3);
	
	init_pwm();  
	
	while(1)
	{
		OCR3A = 0;          // 모터정지  
		PORTE |= 0b00000101;  // PE0:1 PE2:1  모터 정지
		_delay_ms(DELAY);   // 2초 
		
		PORTE &= 0b11111011;       // POTE.2 : 0
		_delay_ms(1);
		PORTE |= 0b00000001;       // 정방향 회전 PE0:1  PE2: 0   
		OCR3A = 127;        // 0.5ms 되면 비교 일치 발생 될 수 있도록 한다. 
		_delay_ms(DELAY);   // 2초 
		OCR3A = 255;        // 1ms    
		_delay_ms(DELAY);   // 2초 
	
		OCR3A = 0;          // 모터 정지 	
		PORTE |= 0b00000101;  // PE0:1 PE2:1  모터 정지
		_delay_ms(2000);
		PORTE &= 0b11111110;
		PORTE |= 0b00000100;       // 역회전 PE0: 0 PE2: 1
		OCR3B = 127;
		_delay_ms(DELAY);
		OCR3A = 255;
		_delay_ms(DELAY);
		 
	}
	return 0;
}
