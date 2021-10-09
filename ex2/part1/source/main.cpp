#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/delay.h>

int main() {
    DDRA = 1;

    while (true) {
        PORTA ^= 1;
        _delay_ms(500);
    }
    return 0;
}
