#include <avr/io.h>
#include <avr/delay.h>
#include "lcd.h"

int main() {

    DDRA = 0xE0;
    DDRB = 0xFF;

    init_LCD();
    _delay_ms(10);
	LCD_Command(0x0E);
	_delay_ms(10);
	

	LCD_Writer("Hello BehnamZare");
    while (1) {}
    return 0;
}