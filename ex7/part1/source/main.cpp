#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "keypad.h"

//Timer0
void Timer0(void)
{
	TCNT0 = 0;
	BitSet(TCCR0, WGM01);
	BitSet(TCCR0, CS01);
	BitSet(TCCR0, CS00);
	BitSet(TIMSK, OCIE0);	
}

ISR(TIMER0_COMP_vect)
{
	command(MOVE_CURSOR_2nd_LINE);
	write_char(keyfind());  
}

int main()
{
	init();
	write_str("Press key...");
	command(MOVE_CURSOR_2nd_LINE);
	KP_Setup();
	Timer0();
	sei();

    while(1)
	{
	};
}