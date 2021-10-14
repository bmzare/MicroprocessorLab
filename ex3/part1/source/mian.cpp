#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/delay.h>

unsigned char i;
unsigned char dsp[10] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};

int main()
{
    // timer 1
    TCCR1B = (1 << CS10) | (1 << CS12);
    OCR1A = 312;

    DDRD = 0xFF;
    PORTD = dsp[0];

    while (true)
    {
        for (i = 0; i < 10; i++)
        {
            while ((TIFR & (1 << OCF1A)) == 0);

            PORTD = dsp[i];

            TCNT1 = 0;
            TIFR |= (1 << OCF1A);
        }
    }
    return 0;
}