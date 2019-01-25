#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void) {
   //Set the Data Direction Register to output
   DDRC |= (1<<5);
   while (1) {
      //Set the signal to high
      PORTC |= (1<<5);
      //wait 0.5 sec
      _delay_ms(300);
      //Set the signal to low
      PORTC &= ~(1<<5);
      //wait 0.5 sec
      _delay_ms(300);
   }
}
