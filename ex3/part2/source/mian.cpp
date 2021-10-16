#include <avr/io.h>
#include <avr/delay.h>

void display7seg(int num);
unsigned char i;
unsigned char j;
unsigned char dsp[10] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};
unsigned char timer0[4] = {0b00000001, 0b00000010, 0b00000100, 0b00001000};

int main()
{
    // timer 1
    TCCR1B = (1 << CS10) | (1 << CS12);
    OCR1A = 100;

    // timer 0
    TCCR0 = (1 << CS00) | (1 << CS02);
    TCNT0 = 0;

    DDRD = 0xFF;
    DDRC = 0xFF;
    PORTC = 0b00001111;
    PORTD = dsp[0];

    int main_number = 0;
    int digit = 0;
    int status = 0;

    while (true)
    {
        status = TCNT0 % 4;

        if (status == 0)
            digit = main_number % 10;
        else if (status == 1)
            digit = (main_number / 10) % 10;
        else if (status == 2)
            digit = (main_number / 100) % 10;
        else
            digit = (main_number / 1000) % 10;

        PORTC = timer0[status];
        PORTD = dsp[digit];

        while ((TIFR & (1 << OCF1A)) == 0);
        if (main_number <= 9999)
        {
            main_number = main_number + 1;
            TCNT1 = 0;
            TIFR |= (1 << OCF1A);
        }
    }
    return 0;
}