#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define COUNT 19.5f

float counter = 0;
int step = 0;
bool direction = true;

unsigned char steps[] = {0b0101, 0b0110, 0b1010, 0b1001};

void move()
{
    if (direction)
    {
        if (++step >= 4)
        {
            step = 0;
        }
    }
    else
    {
        if (--step <= -1)
        {
            step = 3;
        }
    }
    PORTA = steps[step];
}

ISR (TIMER0_OVF_vect)
{
    counter += 0.5f;
    if (counter >= COUNT)
    {
        counter = 0;
    }
}

ISR (TIMER0_COMP_vect)
{
    counter += 0.5f;
    if (counter >= COUNT)
    {
        counter = 0;
        move();
    }
}

int main ()
{
    DDRC = 0;
    DDRA = 0xFF;
    PORTA = 0x00;
    
    //timer0
    TCCR0 = (1 << CS00) | (1 << CS02);
    TIMSK = (1 << TOIE0) | (1 << OCIE0);
    TCNT0 = 0x00;
    OCR0 = 128;

    sei();
    while (true)
    {
        if ((PINC & 0x04) == 0x04)
        {
            direction = true;
        }
        else
        {
            direction = false;
        }
    }
}
