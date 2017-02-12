#include "gpio.h"
#include "timer.h"

void delay_ns(uint32_t ns)
{
    SYS_TICK.ctrl &= 0xfffffff8; /*nolställa bit 0,1,2. Återställa systick*/
    SYS_TICK.load = ((ns*43)>> 8)-1;   /*1 ns beräkning*/
    SYS_TICK.val = 0x00;         /*nolställa räknaren*/
    SYS_TICK.ctrl |= 0x05; /* bit 0,2. Fullhastighet*/
    
    while((SYS_TICK.ctrl & 0x00010000)== 0) ;    /*Så länge bit 16(countflag) är 0, vänta. Man kan alltid kolla om en bit är sat genom att göra en AND med den här biten*/
    SYS_TICK.ctrl &= 0xfffffff8;    /*stoppa räknaren*/
}
