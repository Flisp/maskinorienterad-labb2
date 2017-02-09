#include "blink.h"

void delay_250ns(void)
{
    SYS_TICK.ctrl &= 0xfffffff8; /*nolställa bit 0,1,2. Återställa systick*/
    SYS_TICK.load = 168/4-1;   /*1 microsec/4 -1 för en cyckel*/
    SYS_TICK.val = 0x00;         /*nolställa räknaren*/
    SYS_TICK.ctrl |= 0x05; /* bit 0,2. Fullhastighet*/
    
    while((SYS_TICK.ctrl & 0x00010000)== 0) ;    /*Så länge bit 16(countflag) är 0, vänta. Man kan alltid kolla om en bit är sat genom att göra en AND med den här biten*/
    SYS_TICK.ctrl &= 0xfffffff8;    /*stoppa räknaren*/
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
    GPIO_E.moder = 0x00005555;    /*utport minst signifikanta bitar*/
    RCC_AHB1ENR |= RCC_GPIO_E;   /*aktivera klockan för port D*/
    GPIO_E.otyper = 0x00ff;       /*open drain*/

}

