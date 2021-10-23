#ifndef F_CPU

# define F_CPU 16000000UL // clock speed is 16MHz

#endif





#define LCD_DATA PORTB          // port B is selected as LCD data port

#define ctrl PORTA              //  port D is selected as LCD command port

#define en PA7                  // enable signal is connected to port D pin 7

#define rw PA6                  // read/write signal is connected to port D pin 6

#define rs PA5                  // register select signal is connected to port D pin 5





//**************sending command on LCD***************//


void LCD_Command(unsigned char cmd)

{

	LCD_DATA = cmd;      // data lines are set to send command*

	PORTA  &= ~(1<<rs);  // RS sets 0

	PORTA  &= ~(1<<rw);  // RW sets 0

	PORTA  |= (1<<en);   // make enable from high to low

	_delay_ms(10);

	PORTA  &= ~(1<<en);

	

	return;

}



//*****************write data on LCD*****************//

void Write(unsigned char data)

{

	LCD_DATA= data;       // data lines are set to send command

	PORTA  |= (1<<rs);    // RS sets 1

	PORTA  &= ~(1<<rw);   // RW sets 0

	PORTA  |= (1<<en);    // make enable from high to low

	_delay_ms(10);

	PORTA &= ~(1<<en);

	

	return ;

}

void init_LCD(void)

{

	LCD_Command(0x38);           // initialization in 8bit mode of 32X2 LCD

	_delay_ms(1);

	LCD_Command(0x01);          // make clear LCD

	_delay_ms(1);

	LCD_Command(0x02);          // return home

	_delay_ms(1);

	LCD_Command(0x06);          // make increment in cursor

	_delay_ms(1);

	LCD_Command(0x80);          // �8� go to first line and �0� is for 0th position

	_delay_ms(1);

	

	return;

}
//*****************write STRING on LCD*****************//

void LCD_Writer(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	{
		char big = a[i];
		Write(big);
	}
	
}