#include "gpio.h"
#include "ascii.h"
#include "timer.h"


/*skriv till styrregistret*/
void ascii_ctrl_bit_set(uint8_t bits)
{
    GPIO_E.odr_low |= (B_SELECT | bits);  /*alltid select bit satt*/
}

/*nolställa bitar i styrregister*/
void ascii_ctrl_bit_clear(uint8_t bits)
{
    GPIO_E.odr_low &= (B_SELECT |~bits);  /*nollställ aldrig select bit. Nollställa bitar som skickas in*/ 
}


/*skriv till display, kommando eller data, generellt*/
void ascii_write_controller(uint8_t data)
{
    delay_ns(40);
    ascii_ctrl_bit_set(B_E);  /*enable bit, bit6 */
    GPIO_E.odr_high = data; 
    delay_ns(250); 
    ascii_ctrl_bit_clear(B_E);   /*färdig med skrivningen*/
    /*delay_10ns(); Det behövs inte. Tiden är så kort*/
}

/*skriv kommando till display*/
void ascii_write_cmd(uint8_t command)
{
    ascii_ctrl_bit_clear(B_RS | B_RW);  /*nollställ bit 0 och 1*/
    ascii_write_controller(command);    /*info som ska skickas*/
    delay_ns(250);    /*enligt tidsdiagrammet*/
}

void ascii_write_data(uint8_t data)
{
    ascii_ctrl_bit_set(B_RS); 
    ascii_ctrl_bit_clear(B_RW);  
    ascii_write_controller(data);    
    delay_ns(250);    
}

uint8_t ascii_read_controller()
{
    uint8_t rv; 
    delay_ns(60);
    ascii_ctrl_bit_set(B_E);
    delay_ns(360);
    rv= GPIO_E.idr_high;   /*läser från data bussen*/
    delay_ns(90);  /*1000 -360-550*/
    ascii_ctrl_bit_clear(B_E); 
    /*vänta 550ns*/
    delay_ns(550);
    return rv; 
}

uint8_t ascii_read_status()
{   
    uint8_t rv;
    GPIO_E.moder &= 0x0000ffff;    /*konfigurerar port E, bit8-15 som ingångar*/
    ascii_ctrl_bit_clear(B_RS);
    ascii_ctrl_bit_set(B_RW); 
    rv = ascii_read_controller(); 
    GPIO_E.moder |= 0x55550000;    /*port E bit 8-15 utgångar*/
    return rv; 
}

uint8_t ascii_read_data()
{   
    uint8_t rv;
    GPIO_E.moder &= 0x0000ffff;    /*konfigurerar port E*/
    ascii_ctrl_bit_set(B_RS);
    ascii_ctrl_bit_set(B_RW); 
    rv = ascii_read_controller(); 
    GPIO_E.moder |= 0x55550000;
    return rv; 
}

void ascii_command (uint8_t command, uint32_t delay)
{
    while((ascii_read_status() & 0x080)== 0x080) ;
   delay_ns(8000);
   ascii_write_cmd(command);
   delay_ns(delay);   /*tid att vänta är olika för olika kommando*/
}

void ascii_init()
{
    GPIO_E.moder = 0x55555555; 
    RCC_AHB1ENR |= RCC_GPIO_E;   /*aktivera klockan för port E*/
    GPIO_E.otyper = 0xffff;       /*open drain*/
    
    ascii_command(0x38, 39000);/*för att ha 2 rader och en viss storlek, måste kommandot function set vara 0011 1000 alltså N=1, F=0*/
    ascii_command (0x0e, 39000); /*kommando:display control, D=1,C=1, B=0  --> 0000 1110*/
    ascii_command (0x04, 39000); /*Kommando: entry mode set, ID=0, SH= 0  --> 0000 0100*/
    ascii_command (0x01, 1530000); /*kommando: clear display*/
}

void ascii_gotoxy(uint8_t x, uint8_t y)
{
     uint8_t adress= x-1;
      
    /*om raden är 2, sätt adress till adress + 0x40;*/
    if (y ==2) {
        adress= adress+0x40; 
    }
    ascii_command((0x80| adress), 39000);
 
}
void ascii_write_char(unsigned char c)
{
    while((ascii_read_status() & 0x080)== 0x080) ;
    delay_ns(8000);
    ascii_write_data(c);
    delay_ns(43000);
}




