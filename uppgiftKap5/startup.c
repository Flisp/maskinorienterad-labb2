/*
 * 	startup.c
 *
 */
 
 #include "gpio.h"
 #include "timer.h"
 
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


void main(void)
{
    init_app(); 
    while(1)
    {
        GPIO_E.odr_low = 0x00; 
        delay_ms(500); 
        GPIO_E.odr_low = 0xff; 
        delay_ms (500); 
    }
}

