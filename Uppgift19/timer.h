typedef struct sys_tick
{
    uint16_t ctrl_low; 
    uint16_t ctrl_high;
    uint32_t load; 
    uint32_t val; 
    uint32_t calib;
    
}Sys_tick; 


typedef volatile Sys_tick* systickptr; 

#define SYS_TICK (*((systickptr)0xe0000e010))

