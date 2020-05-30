/*
 * uart0.c
 *
 * Created: 2020-04-10 오전 11:59:28
 *  Author: master
 */ 
#include <avr/io.h>

// UART0 USART0_RX_vect가 호출 한다. 
volatile int i=0;   // buffer 의 index 변수
volatile unsigned char buffer[100]={0};   // UART 부터 읽어온 data를 \r 이나 \n을 만날때 까지 저장할 공간
volatile int rxReadyFlag=0;   // \r이나 \n을 만났다는 인디케이터 flag변수
unsigned char *getRxString()
{
	rxReadyFlag = 0;   // 또 다른 message를 처리 하기 위하여 rxReadyFlag를 clear한다.
	return buffer;

}
// #3 인터럽트 코드를 작성 한다. 
void UART0_ISR_Receive()
{
	unsigned char data;    // UART RX register로 부터 읽어온 1byte를 저장할 변수

	data = UDR0;  // UART0의 H/W register부터 1byte읽어서 data라는 변수에 저장
	
	if (data == '\r' || data == '\n')   // string의 끝이면
	{
		buffer[i] = '\0';   // 종료 문자를 NULL
		rxReadyFlag = 1;  // end message를 나타내는 flag를 set한다.
		i = 0;
	}
	else
	{
		buffer[i++] = data;   // UART로 부터 읽어온 byte를 string buffer에 save한다.
	}	
}
void UART0_init(void)
{
	UBRR0H = 0x00;
	UBRR0L = 207;   // 9600 bps로 설정 
	
	UCSR0A |= (1 << U2X0);   // 2배속 통신	
	UCSR0C |= 0x06;  // Async(비동기). Data길이 8bits. Non Parity(패리티비트 사용 안함). stop 1 bit
	UCSR0B = ((1<<RXEN0)|(1<<TXEN0) | (1 << RXCIE0));   // #2. 송.수신 가능 하고록 설정을 하는것이다. 
	         // RXEN0 : UART0로 수신을 가능 하게 설정
			 // TXEN0 : UART0 송신을 가능 하게 설정
			 // #2. RXCIE0 : UART0로 부터 데이터(1Byte)가 들어 오면 수신(Rx) interrupt가 발생 되도록 설정
	//  RXEN0 : 수신을 가능 하도록 설정  	TXEN0: 송신을 가능 하도록 설정  
}
/*
*  UART0로 1 byte를 보내는 함수 이다. 
*/  
void UART0_transmit(char data)
{
	while ( !(UCSR0A & (1 << UDRE0)) )
		;
	UDR0 = data;	
}
/*
*  UART0로부터 1 byte를 읽어오는 함수 이다.
*/
unsigned char UART0_receive(void)
{
#if 1
    //  76543210
	//         1
	//  10000000
	//  1
	if  ( (UCSR0A & (1 << RXC0)) == 0)    // PC 부터 data가 들어 왔는지를 check한다.  
		return 0;    // 없으면 0을 리턴한다. 
	else 
		return UDR0;		       // PC로 부터 들어온 data를 읽어서 리턴한다.
#else // orgianl code 
	while ( !(UCSR0A & (1 << RXC0)) )   // putty로 부터 data가 들어 올때까지 기다리는것이다. 
		;
	return UDR0;		                // PC로 부터 들어온 data를 읽어서 리턴한다. 
#endif 
}
/*
*  UART0로 string을 출력 하는 함수
*/
void UART0_printf_string(char *str)
{
	for (int i=0; str[i] != '\0'; i++)
		UART0_transmit(str[i]);	
}