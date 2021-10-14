#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/delay.h>

int main() {
    DDRA = 0;
    DDRB = 0xFF;

    while (true) {
        if ((PINA & 1) == 1) {
            PORTB ^= 0xFF;
            _delay_ms(500);
        }
    }
    return 0;
}
