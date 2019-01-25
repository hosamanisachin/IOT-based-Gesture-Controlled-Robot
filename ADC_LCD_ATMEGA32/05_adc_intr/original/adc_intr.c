#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "adc_intr.h"

#define ADC_CHANNEL1	3 // x-axis
#define ADC_CHANNEL2 	4 // y-axis

volatile uint16_t adc_val=0;

volatile uint16_t adc_flag=0;

void adc_init(void)
{
	// set PORTA as input
	DDRA = 0x00; //~BV(ADC_CHANNEL);
	PORTA = 0xFF; // BV(ADC_CHANNEL);

	// enable adc and adc interrupt
	ADCSRA = BV(ADEN) | BV(ADIE);
	// enable global interrupt
	sei();
	// select adc channel, left adjust and select ref voltage
	//ADMUX = BV(MUX0) | BV(MUX1) | BV(ADLAR) | BV(REFS0);
	//ADMUX = BV(MUX2) | BV(MUX1) |BV(MUX0) | BV(ADLAR) | BV(REFS0);
	//ADMUX = 0x65;	// to select channel 5
}
/*
void adc_init2(void)
{
	// set PORTA as input
	DDRA = ~BV(ADC_CHANNEL2);
	PORTA = BV(ADC_CHANNEL2);

	// enable adc and adc interrupt
	ADCSRA = BV(ADEN) | BV(ADIE);
	// enable global interrupt
	sei();
	// select adc channel, left adjust and select ref voltage
	ADMUX = BV(MUX2) | BV(ADLAR) | BV(REFS0);
}
*/

int adc_select(int chan)
{	
	ADMUX = 0x00;
	//ADMUX |= chan & 0x1F;
	if(chan==2)
	{	
		ADMUX = 0x62; //BV(MUX0) | BV(MUX1) | BV(ADLAR) | BV(REFS0);
		ADCSRA |= BV(ADSC);
		return 1;
	}

	else if(chan==3)
	{
		ADMUX = 0x63; //BV(MUX2) | BV(ADLAR) | BV(REFS0);
		ADCSRA |= BV(ADSC);
		return 2;
	}
		//start conversion
}



uint16_t adc_read(void)
{
	// read value from adc
	uint16_t val = ADCH;
	//decide for left and right
	

	return val;
}

ISR(ADC_vect)
{
	adc_val = adc_read();
	adc_flag = 1;
}


