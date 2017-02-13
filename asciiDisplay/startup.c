/*
 * 	startup.c
 *
 */

#include "gpio.h"
#include "ascii.h"

void startup(void) __attribute__((naked)) __attribute__((section (".start_section")) );

void startup ( void )
{
asm volatile(
	" LDR R0,=0x2001C000\n"		/* set stack */
	" MOV SP,R0\n"
	" BL main\n"				/* call main */
	".L1: B .L1\n"				/* never return */
	) ;
}

/*skriver ut texten på displayen*/
void main()

{
    char* s; 
    char test_1[]= "Alfanumerisk";
    char test_2[] = "Display - test"; 
    
    ascii_init(); 
    ascii_gotoxy(1,1); 
    s= test_1; 
    
    while (*(s))
    {
        ascii_write_char(*(s++)); 
    }
    
    ascii_gotoxy(1,2); 
    s= test_2; 
    
    while (*(s))
    {
        ascii_write_char(*(s++)); 
    }
}

