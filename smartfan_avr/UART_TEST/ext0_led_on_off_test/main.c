/*
 * ext0_led_on_off_test.c
 *
 * Created: 2020-04-13 오전 11:47:41
 * Author : master
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int state = 0;			// 현재 LED의 상태

ISR(INT0_vect)      // PORTD.0에 연결된 ext interrupt  sw를 눌렀다 뗴면 ext inteerupt로 
                    // 자동적으로 이곳으로 온다. 버튼이 하강 에지로 떨어질때 자동으로 이곳으로
					// 들어 온다, 
{
	state = (state + 1) % 2;			// LED 상태 전환
		if(state == 1)
		{
			PORTA = 0xff;
		}
		else
		{
			PORTA = 0x00;
		}
}

void INIT_PORT(void)
{
	DDRA = 0xff;				// PA 핀을 출력으로 설정
	PORTA = 0x00;				// LED는 꺼진 상태에서 시작
	
	DDRD = 0x00;				// PD0 핀을 입력으로 설정
	PORTD = 0x01;			// PD0 핀의 풀업 저항 사용
	                        // 평소에 high상태를 유지 하다가 버튼을 누르면 low로 떨어 진다.
						 //  풀업을 연결 하는 목적은 플로팅을 방지 하기 위해서
						 //  평소에 high상태로 만들어서 오 동작 방지 
}
// ext 0 인터럽트 설정 루틴(함수)
void INIT_INT0(void)
{
	EIMSK |= (1 << INT0);			// 1. INT0 인터럽트 활성화
	                                // 76543210
									// 00000001
									// EIMSK |= 는 INT0비트 0번 비트를 set시킨다. 
	EICRA |= (1 << ISC01);			// 2. 하강 에지에서 인터럽트 발생
	sei();							// 3. 전역적으로 인터럽트 허용
}

int main(void)
{
	INIT_PORT();				// 포트 설정
	INIT_INT0();				// INT0 인터럽트 설정
	
	while(1)
	{
		;
	}
	return 0;
}

