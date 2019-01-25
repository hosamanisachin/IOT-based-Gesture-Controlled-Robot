#include <avr/io.h>
#include <string.h>
#include "uart.h"
#include "lcd.h"
#include <util/delay.h>
#include "adc_intr.h"

//char *(strchr)(const char *s, int c)

volatile uint16_t adc_val1=0;
volatile uint16_t adc_val2=0;

volatile uint16_t adc_flag1=0;
volatile uint16_t adc_flag2=0;
volatile int ch=0,ch1=5;
char str2[32];
int ADC_1=2; // x-axis
int ADC_2 =3; // y-axis


void func(int x);
void print();
void esp();
void adc();

char str[20];

void func(int x)
{
		if(x==0)
	{	
		if(adc_flag)
		{
			_delay_ms(100);
			adc_val1 = adc_val;
			adc_flag = 0;
			adc_flag1 = 0;
			adc_flag2 = 1;
			
		}
		else
		{
			
			// Nothing to do
		}
	}
		else if(x==1)
	{
		if(adc_flag)
		{
			_delay_ms(100);
			adc_val2 = adc_val;
			adc_flag = 0;
			adc_flag2= 0;
			adc_flag1 = 1;			
		}
		else
		{
			
			//Nothing to do
		}
		
	}
		_delay_ms(200);
		
}

void print()
{
	if(adc_val1<=152 && adc_val1>=147 && adc_val2<=159 && adc_val2>=152)
		ch=2;
	else if(adc_val1>=159 && adc_val1<=163 && adc_val2<=159 && adc_val2>=152)
		ch=1;
	if(adc_val2<=152 && adc_val2>=147 && adc_val1<=159 && adc_val1>=152)
		ch=4;
	else if(adc_val2>=159 && adc_val2<=163 && adc_val1<=159 && adc_val1>=152 )
		ch=3;
	else if (adc_val1<=159 && adc_val1>=152 && adc_val2<=159 && adc_val2>=152)
		ch=0;
	
	sprintf(str, "Move: %d", ch);
	lcd_putstring(1, str);
	
	
	sprintf(str, "1:%4d 2:%4d",adc_val1,adc_val2);
	lcd_putstring(0, str);
	//sprintf(str, "val2:%4d",adc_val2);
	//lcd_putstring(1, str);
	
}

void esp()
	{
				
		uart_puts("AT+CIPSTART=0,\"TCP\",\"192.168.43.241\",4500\r\n");
		_delay_ms(2000);

		uart_puts("AT+CIPSEND=0,15\r\n");
		_delay_ms(2000);

		sprintf(str2, "GET /cart/%d\r\n", ch1);

		uart_puts(str2);
		_delay_ms(2000);

		uart_puts("\r\n");
		_delay_ms(1000);
	
		uart_puts("AT+CIPCLOSE\r\n");
		_delay_ms(2000);
		ch1=ch;	
	}

void adc()
	{	
		if(adc_flag2==0)
		{	
		adc_flag1 = adc_select(ADC_1);
		func(0);
		} 	
		else
		_delay_ms(200); // need this delay so as to select ADC 2
		
		
		if(adc_flag1==0){
		adc_flag2 = adc_select(ADC_2);
		func(1);
		}
		else
		_delay_ms(200);
	}
int main()
{
	char str[32],str1[32]="On LCD";
	const char ch='\r';
	char *ret;

	adc_init();
	lcd_init();
	uart_init(9600);

	lcd_putstring(0, str1);
	_delay_ms(1000);
	uart_puts("AT\r\n");
	_delay_ms(2000);
	//uart_puts("AT+UART_CUR=9600,8,1,0,0\r\n");

	uart_puts("AT+CIPMODE=0\r\n");
	_delay_ms(1000);

	uart_puts("AT+CIPMUX=1\r\n");
	_delay_ms(1000);


	//uart_puts("AT+CWJAP=”B0XT-8J+RvVdBUkU”,””");   //192.168.43.241:4500/cart/0,1,2,3 //207 ESP  
	//	_delay_ms(10000);
	//	uart_gets(str);
	//	lcd_putstring(1, str);	

	
	while(1)
	{
		
		
		adc();
		print(); //print both the ADC obtained value


		uart_puts("AT\r\n");
		_delay_ms(200);
		
		if(ch!=ch1)
		{
		//send data to esp
		esp();

		}
		
		else{
		//no change
		
		}
		
		
		//uart_puts("AT+CIPMODE=0\r\n");
		//_delay_ms(1000);

		//uart_puts("AT+CIPMUX=1\r\n");
		//_delay_ms(1000);

	
		
	}
	return 0;
}

