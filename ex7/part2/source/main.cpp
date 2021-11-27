#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "lcd.h"
#include "keypad.h"

bool logedIn = false;

int main()
{
	DDRB = DDRB | (1 << PINB3) | (1 << PINB6);

	init();
	write_str("Login");
	command(MOVE_CURSOR_2nd_LINE);
	write_str("ID: ");
	KP_Setup();

	char admin_id  [5] = "0258";
	char admin_pass[5] = "0258";

    while(1){
		while(!logedIn)
		{
			char id[5];
			for(uint8_t i = 0; i < 4; i++)	
			{
				id[i] = keyfind();
				write_char(id[i]);
			}	

			command(CLEAR_DISPLAY);
			write_str("Login");
			command(MOVE_CURSOR_2nd_LINE);
			write_str("Pass: ");

			char pass[5];
			for(uint8_t i = 0; i < 4; i++)
			{
				pass[i] = keyfind();
				write_char(pass[i]);
			}	
			
			command(CLEAR_DISPLAY);

			bool checked = true;
			for(int i = 0; i < 4; i++)
			{
				if(admin_id[i] != id[i]) checked = false;
				if(admin_pass[i] != pass[i]) checked = false;
			}

			if(checked)
			{	
				write_str("Loged In!");
				logedIn = true;

				PORTB |= (1 << PINB3);
			}
			else
			{
				PORTB |= (1 << PINB6);

				write_str("Wrong Info!");
				command(MOVE_CURSOR_2nd_LINE);
				write_str("ID: ");
			}
		}
	};
}