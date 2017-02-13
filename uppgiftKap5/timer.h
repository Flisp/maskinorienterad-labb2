typedef struct sys_tick
{
    uint32_t ctrl;  /* Offset 0x00 */
    uint32_t load;  /* Offset 0x04 */
    uint32_t val;   /* Offset 0x08 */
    uint32_t calib; /* Offset 0x0c */
    
}Sys_tick; 


typedef volatile Sys_tick* systickptr; 

#define SYS_TICK (*((systickptr)0xe000e010))

