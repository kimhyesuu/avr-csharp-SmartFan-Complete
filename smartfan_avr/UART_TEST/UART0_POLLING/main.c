/*
 * UART0_POLLING.c
 *
 * Created: 2020-04-10 오전 11:56:02
 * Author : master
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>    
#include <stdio.h>			  // printf 첫번째 설정 
#include <avr/interrupt.h>    // #1. intrrupt 라이브러리를 include 한다. 
                              // Add rx_Interrupt 
#include <stdbool.h>
#include "uart0.h"
#include "DHT.h"        // #1_DHT11 헤더를 추가 한다. 
/*--------- spi rfid rc522 통신 헤더 화일 ------------*/
#include "mfrc522.h"    // rfid 관련헤더 화일
#include "spi.h"        // spi 통신을 위한 헤더 화일 
#include "I2C.h" // LCD 사용을 위한 헤더파일
#include "I2C_LCD.h"

#define YES							1 //값을 읽으면 들어가게 만든다.
#define PE7							7 //모터 제어핀 정의
#define PE2							2 //모터 제어핀 정의
#define PE3							3 //모터 제어핀 정의
#define MAX_LEN						5// rfid 
#define ROTATION_DELAY 	1000	// 1초 대기
#define PULSE_MIN		1300	// 최소 펄스 길이
#define PULSE_MID		3000
#define PULSE_MAX		4700	// 최대 펄스 길이

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);  // 2.printf로 설정하기 위한 작업

void smartfan_main(void); // 선풍기 동작 함수
void init_pwm1(void);     // 모터 동작 설정(DC모터)
int rfid_read(void);	  // RFID 카드 입력 확인하는 것	

// UART0 USART1_RX_vect가 호출 한다.
extern volatile int i;   // buffer 의 index 변수
extern volatile unsigned char buffer[100];   // UART 부터 읽어온 data를 \r 이나 \n을 만날때 까지 저장할 공간
extern volatile int rxReadyFlag;   // \r이나 \n을 만났다는 인디케이터 flag변수
unsigned char dht11_on_off = YES;    // #3_DHT11  dht11의 정보를 PC로 올려 줄건지 말건지를 indicator flag
unsigned char fan_on_off = 0;
unsigned char fan_count = 0;
unsigned char rotate_servo = 0;
unsigned char temp[2], hum[2];   // #4_DHT11  온도.습도를 읽어서 저장할 공간 정의
unsigned int mycard[4][5] ={{217, 163, 183, 193, 12},{201,236,219,193,63},{228, 57, 175, 42, 88},{-20986, 7068, 47, 32, 32}};
int first_compare_count = 0; // 처음 댄 카드가 일치하는 여부 판단
int next_compare_count = 0;  // 태그를 유지할 경우, 일치하는 카드인지 판단
volatile int count = 0;   // 오버플로우 인터럽트 발생 횟수를 세는 counter

 
ISR(USART0_RX_vect)   // UART1로 부터 1byte가 들어 오면 interrupt가 발생되어 이곳으로 들어 온다.
{
	UART0_ISR_Receive(); 
}
// TIMER0 overflow interrupt service 함수 
// 16KHZ 인 경우 약 16ms 마다 이곳으로 들어 온다. 


int main(void)
{	
	smartfan_main();    //5. 온.습도 정보를 읽어서 UART0에 출력해서 putty로 나오도록 한다.  
}
/*
결선방법 

RFID-RC522  ATMEGA128A
  SDA  ----- PORTB.0   // 슬레이브 선택
  SCK  ----- PORTB.1   // 시리얼클럭
  MOSI ----- PORTB.2   // 마스터 --> 슬레이브
  MISO ----- PORTB.3   // 슬레이브-->마스터  
  IRQ  ----- 연결안함 
  GND  ----- GND
  RST  ----- +3.3V               
  VCC  ----- +3.3v
*/

void init_pwm1(void)
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

void InitializeTimer1(void)
{
	// 모드 14, 고속 PWM 모드
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	
	// 비반전 모드
	// TOP : ICR1, 비교일치값 : OCR1A 레지스터
	TCCR1A |= (1 << COM1A1);
	
	TCCR1B |= (1 << CS11);		// 분주율 8, 2MHz
	// T=1/16000000 ==> 0.0000000625 Sec x 8분주 ==> 0.0000005 Sec (1 clock 주기)
	// 16bit TImer 이므로 최대 65535까지 count할 수 있으므로
	// 0.0000005 x  65535 ==> 0.0327675초(32.76ms)마다 OV interrupt
	//  0.0000005(1clock주기) x 40000 ==> 0.02sec (20ms)
	ICR1 = 39999;				// 20ms 주기
}


unsigned int mycard[4][5] ={{217, 163, 183, 193, 12},{201,236,219,193,63},{228, 57, 175, 42, 88},{-20986, 7068, 47, 32, 32}};

int rfid_read()
{
	unsigned char byte_rfid; // rfid 읽은 상태 체크 변수
	unsigned char str[MAX_LEN]; // rfid 값을 읽어을 string 변수
	unsigned char fail_save_str[5];
	unsigned char Lcd_buffer[15];	
	int pass_flag = 0;
		
	spi_init();       // spi 초기화
	mfrc522_init();   // rfid rc522을 초기화	
	
	byte_rfid = 0x55;      // 01010101
	// 10101010  0xaa
	_delay_ms(1500);       //datasheets에 써져있는 클럭 주파수에 맞추기위해 사용 
	
	byte_rfid = mfrc522_read(VersionReg);    // rfid 버젼을 읽는다.
	
	if (byte_rfid == 0x92)					
	{
		printf("RC522v2 Detected!!!!\r\n");
	}
	else if (byte_rfid == 0x91 || byte_rfid == 0x90)
	{
		printf("RC522v1 Detected!!!!\r\n");
	}
	else
	{
		printf("No reader Found!!!!\r\n");
	}	
	
	_delay_ms(1500); //datasheets에 써져있는 클럭 주파수에 맞추기위해 사용 
	
	byte_rfid = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg, byte_rfid|0x20);
	byte_rfid = mfrc522_read(DivIEnReg);
	mfrc522_write(ComIEnReg, byte_rfid|0x80);
	_delay_ms(1500);

	UART0_printf_string("spi rfid_rc522 test\r\n");  // 2,
	
	while (1)
	{
		byte_rfid = mfrc522_request(PICC_REQALL, str);
		
		if(byte_rfid == CARD_FOUND)
		{
			for (int j = 0; j < MAX_LEN; j++)
			str[j] = ' ';
			byte_rfid = mfrc522_get_card_serial(str);
			
			for (int j = 0; j < 4; j++)
			{
				first_compare_count = 0;
				int k;		
						
				for (k = 0; k < 5; k++)
				{
					if (str[k] == mycard[j][k])				
						first_compare_count++;	
					else 
						break;									
				}//리시브받은 데이터(str[k])와 배열에 저장된 값(mycard[j][k]) 5개가 일치하면(각 고유 넘버 당 5개의 숫자를 가지고 있음)
				
				if (first_compare_count == 5)//이 부분 사용
				{									
					if(str[k-1] == mycard[2][k-1]) //이 카드를 가진 사람을 인식하는 것이지만 db에서 받아서 써도 되는 부분
					{
						PORTA = 0x01;
						printf("GOODBYE\r\n");
						pass_flag = 2;
						sprintf(Lcd_buffer, "%d %d %d %d %d\r\n", mycard[j][0],mycard[j][1],mycard[j][2],mycard[j][3],mycard[j][4]);
						
						printf("%s",Lcd_buffer);
						I2C_LCD_write_string_XY(0, 0,"GOODBYE");
						I2C_LCD_write_string_XY(1, 0,Lcd_buffer);
						_delay_ms(30);
						break;
					}
					if(str[k-1] == mycard[1][k-1])	 
					{
						PORTA = 0x02;
						printf("HELLOW KIMHYESU\r\n");
						pass_flag = 1;
						sprintf(Lcd_buffer, "%d %d %d %d %d\r\n", mycard[j][0],mycard[j][1],mycard[j][2],mycard[j][3],mycard[j][4]);
						
						printf("%s",Lcd_buffer);
						I2C_LCD_write_string_XY(0, 0,"KIMHYESU COME");
						I2C_LCD_write_string_XY(1, 0,Lcd_buffer);
						_delay_ms(30);
						break;
					}	
					if(str[k-1] == mycard[0][k-1])
					{
						PORTA = 0x01;
						printf("HELLOW JINSUBRO\r\n");
						pass_flag = 1;
						sprintf(Lcd_buffer, "%d %d %d %d %d\r\n", mycard[j][0],mycard[j][1],mycard[j][2],mycard[j][3],mycard[j][4]);
						
						printf("%s",Lcd_buffer);
						I2C_LCD_write_string_XY(0, 0,"JINSUBRO COME");
						I2C_LCD_write_string_XY(1, 0,Lcd_buffer);
						_delay_ms(30);
						break;
					}	
																
				}				
			}		
		}		
		if(pass_flag == 1 || pass_flag == 2)//이 부분에서 출입 통제 기능 
		break;
	}	
	return pass_flag;//return 받은 값으로 핸들링 할 것
}
/*
* UART0로부터 수신하는 문자는 INTERRUPT로 받고
* 송신 하는 문자는 polling으로 처리 한다.
*/
void smartfan_main()
{
	unsigned char *receiveData;	
    char buffer_TH[50];				 // 온도.습도 정보를 statamet로 구성 하기 위한 공간		
	DDRA = 0xFF;					// 포트a led 설정
	PORTA |= 0b00000000;			// 포트a led 제어
	DDRB |= 0xf0;					// rfid 설정 	
	DDRE |=(1 << PE7)|(1 << PE2)|(1 << PE3); //모터 동작 설정
		
	InitializeTimer1(); //서보모터 
	UART0_init();   //1 UART1 초기화
	I2C_LCD_init();  // lcd 초기화		
	init_pwm1();
	sei();          // global interrupt enable
	stdout = &OUTPUT;   // 3.printf 설정을 위한 3번째 작업: OUTPUT 포인터를 stdout에 설정을 하는 작업 	
	while(1)
	{
		int rfid_success = rfid_read();	
			
		if(rfid_success == 1)
		{		
			UART0_printf_string("SMART FAN START\r\n");  // 2
		
			while(1) //0이 아니면 돌아라
			{
				PORTE &= 0b00000100;
				PORTE |= 0b00000100;       // 정방향 회전 PE7:1  PE2: 0
			
				if(fan_count == 1) OCR3A = 127;//미풍												
				if(fan_count == 2) OCR3A = 190;//중풍												
				if(fan_count == 3) OCR3A = 255;//강풍	
				if(rotate_servo == 1) //서보모터
				{
					OCR1A = 1000;		// -90도  500us
					_delay_ms(ROTATION_DELAY);

					OCR1A = 1660;		// -60도  833us
					_delay_ms(ROTATION_DELAY);

					OCR1A = 2320;		// -30도  1160us
					_delay_ms(ROTATION_DELAY);
					
					OCR1A = 3000;		// 0도 1500us(1.5ms)
					_delay_ms(ROTATION_DELAY);
					
					OCR1A = 5000;		// +90 2500us(2.5ms)
					_delay_ms(ROTATION_DELAY);
					
					OCR1A = 3000;		// 0도 1500us(1.5ms)
					_delay_ms(ROTATION_DELAY);
				}
																		
				if (rxReadyFlag == YES)   // #4 완전한 message가 buffer에 들어 왔는지 check
				{
					receiveData = getRxString();//값을 입력받으면
					if (strncmp(receiveData,"motoroff",sizeof("motoroff")) == 0)
					{
						while(1)
						{
							PORTE |= 0b000000100;
							OCR3A = 0;	
																							
							if (strncmp(receiveData,"motorona",sizeof("motorona")) == 0)
							{
								fan_count = 1;							
								break;
							}
							if (strncmp(receiveData,"motoronb",sizeof("motoronb")) == 0)
							{
								fan_count = 2;
								break;
							}
							if (strncmp(receiveData,"motoronc",sizeof("motoronc")) == 0)
							{
								fan_count = 3;
								break;
							}
						}
					}										
					if (strncmp(receiveData,"motorona",sizeof("motorona")) == 0)
					{
						fan_count = 1;
					}
					if (strncmp(receiveData,"motoronb",sizeof("motoronb")) == 0)
					{
						fan_count = 2;
					}
					if (strncmp(receiveData,"motoronc",sizeof("motoronc")) == 0)
					{
						fan_count = 3;					
					}
					if (strncmp(receiveData,"rotate",sizeof("rotate")) == 0)
					{
						rotate_servo = 1;
					}
				}			
						
			}		
			
		}	
		else if(rfid_success == 2)
		{
			break;
		}
	}						
}
	








	
	
	
	