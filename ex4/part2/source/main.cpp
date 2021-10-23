#include <avr/io.h>
#include <stdio.h>
#include <util/atomic.h>
#include <avr/delay.h>
#include "lcd.h"

unsigned int timer_counter = 0;

unsigned int second = 0;
unsigned int minute = 0;
unsigned int hour = 0;

char time[9] = "";
void counter()
{
    second++;

    if (second == 60)
    {
        second = 0;
        minute++;
    }
    if (minute == 60)
    {
        minute = 0;
        hour++;
    }
}

ISR(TIMER2_OVF_vect)
{
    timer_counter++;

    if (timer_counter % 1953 == 0)
    {
        counter();

        LCD_Command(0x01);

        char hourD = hour;
        char minuteD = minute;
        char secondD = second;

        if (trunc(log10(hour)) + 1)
        {
            hourD = "0" + hour;
        }

        if (trunc(log10(minute)) + 1)
        {
            minuteD = "0" + minute;
        }

        if (trunc(log10(second)) + 1)
        {
            secondD = "0" + second;
        }
        sprintf(time, "%d:%d:%d", hourD, minuteD, secondD);
        LCD_Writer(time);
    }
}
int main()
{
    DDRB = 0xFF;
    DDRD = 0xE0;
    init_LCD();
    LCD_Command(0x0C);

    // timer 2
    TIMSK = (1 << TOIE2);
    TCCR2 = (1 << CS20);
    sei();

    while (1)
    {
    }
    return 0;
}