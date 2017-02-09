

#define B_E 0x40
#define B_SELECT 0x04
#define B_RW 0x02
#define B_RS 0x01

void ascii_ctrl_bit_set(uint8_t bits);
void ascii_ctrl_bit_clear (uint8_t bits);
void ascii_write_controller (uint8_t data); 
void ascii_write_cmd(uint8_t command);
void ascii_write_data(uint8_t data);

uint8_t ascii_read_controller();
uint8_t ascii_read_status();
uint8_t ascii_read_data ();


void ascii_init();
void ascii_gotoxy(uint8_t x, uint8_t y);
void ascii_write_char(unsigned char c);  
