/*
 * FND4.c
 *
 * Created: 2020-04-09 오후 2:44:05
 * Author : master
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define SEGMENT_DELAY 5		// LED가 완전히 켜지기 위한 시간
#if 1   // common 캐소우드 방식 HSN-5643AS-H
uint8_t numbers[] =  {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 
	                 0b01111101, 0b00100111, 0b01111111, 0b01100111};
#else  // common 애노우드 방식 HSN3641BS
 uint8_t numbers[] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010,
	                 0b10000010, 0b11011000, 0b10000000, 0b10011000}; 
#endif 
                     
void display_digit(int position, int number)
{
	// position : 출력할 자리 (1 ~ 4)
	// number : 출력할 숫자 (0 ~ 9)
  

#if 1 // common 캐소우드 방식 HSN-5643AS-H
	PORTB |= 0xF0;
	PORTB &= ~(1 << (position+4)-1);	// 자리 선택
#else // common 애노우드 방식 HSN3641BS
	PORTB &= 0x0F;
	PORTB |= (1 << (position+4)-1);	// 자리 선택
#endif 
	
	PORTC = numbers[number];		// 숫자 출력
}

int main(void)
{
	DDRC = 0xFF;				// 세그먼트 제어 핀 8개를 출력으로 설정
	DDRB = 0xF0;				// 자릿수 선택 핀 4개를 출력으로 설정
	
	while(1)
	{
		display_digit(1, 1);			// 첫 번째 자리에 ‘1’ 출력
		_delay_ms(SEGMENT_DELAY);
		display_digit(2, 2);			// 두 번째 자리에 ‘2’ 출력
		_delay_ms(SEGMENT_DELAY);
		display_digit(3, 3);			// 세 번째 자리에 ‘3’ 출력
		_delay_ms(SEGMENT_DELAY);
		display_digit(4, 4);			// 네 번째 자리에 ‘4’ 출력
		_delay_ms(SEGMENT_DELAY);
	}
	
	return 0;
}



