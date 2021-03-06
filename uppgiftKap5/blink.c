#include "blink.h"

const int COUNTVALUE = 42;

void delay_250ns(void)
{
    SYS_TICK.ctrl = 0; /*nollställa CTRL. Återställa systick*/
    SYS_TICK.load = COUNTVALUE - 1;   /*1 microsec/4 -1 för en cyckel*/
    SYS_TICK.val = 0x00;         /*nolställa räknaren*/
    SYS_TICK.ctrl = 0x05; /* bit 0,2. Fullhastighet*/
    
    while((SYS_TICK.ctrl & 0x00010000)== 0) ;    /*Så länge bit 16(countflag) är 0, vänta. Man kan alltid kolla om en bit är sat genom att göra en AND med den här biten*/
    SYS_TICK.ctrl = 0;    /*stoppa räknaren*/
}

void delay_micro(uint32_t us)
{
    while (us--)
    {
        delay_250ns(); 
        delay_250ns(); 
        delay_250ns(); 
        delay_250ns(); 
    }
}

/*simulatorn är långsammare*/

void delay_ms(uint32_t ms)
{   
    /*räknar ner*/
    while (ms--){
    #ifdef SIMULATOR
        delay_micro(2);
    #else
        delay_micro(1000); 
    #endif
    }
}

void init_app (void)
{
    RCC_AHB1ENR = RCC_CCMDATARAMEN | RCC_GPIO_E;   /*aktivera klockan för port E*/
    
    GPIO_E.moder = 0x00005555;    /*utport minst signifikanta bitar*/
    GPIO_E.otyper = 0x0000;       /*push/pull*/
    GPIO_E.pupdr = 0x0000;
}

