#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
	lcd_init();
	lcd_putstring(0, "HELLO AVR ARM");	
	lcd_putstring(1, "SUNBEAM INFOTECH");	
	while(1);
	return 0;
}

