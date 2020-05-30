//#define F_CPU 16000000L
//#include <avr/io.h>
//#include <avr/interrupt.h>

volatile int count1 = 0;				// 오버플로가 발생한 횟수
volatile int state1 = 0;				// LED 점멸 상태

// 이곳 ISR(TIMER0_OVF_vect)   약16ms 마다 들어 온다.
ISR(TIMER0_OVF_vect)
{
	count1++;
}


ISR(TIMER0_COMP_vect)
{			//AtmelStudio 사용시 인터럽트 서비스 루틴
	static char i=0;
	//FND_CONTROL_PORT &= 0b11110000;			
	//FND_CONTROL_PORT |= 0b00000001<<i;
	//FND_DATA_PORT = FND[i];
	i++;
	if(i==4)i=0;
}

void Timer0_Init(void)
{
	TCCR0 = 0b00001110;
	OCR0 = 255;
	//  1024/16000000 = 255 / 16000 => 1/64 ==> 0.015625sec
	//  0.015625sec  ==> 16 ms 마다 OCR Int가 발생
	TIMSK |= 1<<OCIE0;
	TIFR = 0x00;                                 // clear all interrupt flags
	ETIFR = 0x00;
}

void Timer2_Init(void)
{
	TCCR2 = 0b00000101;    // 분주비를 1024로 나눈다    // 16M/1024 ==> 16000000/1024 ==> 15,625 HZ  ==> 15,625 
	                                                  // T = 1/f ==> 1/15625Hz = 0.000064sec x 1000 = 0.064 ms 
													  // 0.064 x 1000 = 64us가 소요
													  // 그래서 TCN0 1이 64us 이므로 64를 곱해준것이다. 
													  // 1cm이동시 29us 소요
}	

