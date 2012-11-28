#include <avr/io.h> 
#include "lcd.h"

/**
 * Flush channel E
 */
void lcd_toggle_e(void)
{
  lcd_e_high();
  delay_us(10);
  lcd_e_low();
}

/**
 * Loops while lcd is busy, returns address counter
 */
static void lcd_waitbusy(void)
{
    /* the address counter is updated 4us after the busy flag is cleared */
    delay_us(1000);   
}

/**
 * Send a character or an instruction to the LCD
 */
void lcd_write(uint8_t data,uint8_t rs) 
{
	lcd_waitbusy();
	
  //check write type
  if (rs) {
    lcd_rs_high(); //write data
  } else {     
    lcd_rs_low();  //write instruciton
  }
        
  // configure data pins as output 
  LCD_DDR(LCD_DATA0_PORT) |= _BV(LCD_DATA0_PIN);
  LCD_DDR(LCD_DATA1_PORT) |= _BV(LCD_DATA1_PIN);
  LCD_DDR(LCD_DATA2_PORT) |= _BV(LCD_DATA2_PIN);
  LCD_DDR(LCD_DATA3_PORT) |= _BV(LCD_DATA3_PIN);

  // output high nibble first 
  LCD_DATA3_PORT &= ~_BV(LCD_DATA3_PIN);
  LCD_DATA2_PORT &= ~_BV(LCD_DATA2_PIN);
  LCD_DATA1_PORT &= ~_BV(LCD_DATA1_PIN);
  LCD_DATA0_PORT &= ~_BV(LCD_DATA0_PIN);
	if (data & 0x80) LCD_DATA3_PORT |= _BV(LCD_DATA3_PIN);
	if (data & 0x40) LCD_DATA2_PORT |= _BV(LCD_DATA2_PIN);
	if (data & 0x20) LCD_DATA1_PORT |= _BV(LCD_DATA1_PIN);
	if (data & 0x10) LCD_DATA0_PORT |= _BV(LCD_DATA0_PIN);   
  lcd_toggle_e();

  // output low nibble 
  LCD_DATA3_PORT &= ~_BV(LCD_DATA3_PIN);
  LCD_DATA2_PORT &= ~_BV(LCD_DATA2_PIN);
  LCD_DATA1_PORT &= ~_BV(LCD_DATA1_PIN);
  LCD_DATA0_PORT &= ~_BV(LCD_DATA0_PIN);
	if (data & 0x08) LCD_DATA3_PORT |= _BV(LCD_DATA3_PIN);
	if (data & 0x04) LCD_DATA2_PORT |= _BV(LCD_DATA2_PIN);
	if (data & 0x02) LCD_DATA1_PORT |= _BV(LCD_DATA1_PIN);
	if (data & 0x01) LCD_DATA0_PORT |= _BV(LCD_DATA0_PIN);
  lcd_toggle_e();        

  // all data pins high (inactive) 
  LCD_DATA0_PORT |= _BV(LCD_DATA0_PIN);
  LCD_DATA1_PORT |= _BV(LCD_DATA1_PIN);
  LCD_DATA2_PORT |= _BV(LCD_DATA2_PIN);
  LCD_DATA3_PORT |= _BV(LCD_DATA3_PIN);
}

/**
 * Send a character to the LCD
 */
void lcd_char(uint8_t data)
{
	if (data=='\n') {
		if (g_nCurrentLine >= LCD_LINES - 1) {
			lcd_setline(0);
		} else {
			lcd_setline(g_nCurrentLine+1);
    }
	} else {
  	lcd_write(data,1);
  }
}

/**
 * Send an instruction to the LCD
 */
void lcd_instr(uint8_t instr)
{
	lcd_write(instr,0);
}

/**
 * Initialize LCD to 4 bit I/O mode
 */
void lcd_init()
{
  // configure all port bits as output (LCD data and control lines on different ports 
  LCD_DDR(LCD_RS_PORT)    |= _BV(LCD_RS_PIN);
  LCD_DDR(LCD_E_PORT)     |= _BV(LCD_E_PIN);
  LCD_DDR(LCD_DATA0_PORT) |= _BV(LCD_DATA0_PIN);
  LCD_DDR(LCD_DATA1_PORT) |= _BV(LCD_DATA1_PIN);
  LCD_DDR(LCD_DATA2_PORT) |= _BV(LCD_DATA2_PIN);
  LCD_DDR(LCD_DATA3_PORT) |= _BV(LCD_DATA3_PIN);
  // wait 25ms or more after power-on
  delay_us(25000);

  // initial write to lcd is 8bit 
  LCD_DATA1_PORT |= _BV(LCD_DATA1_PIN);  // _BV(LCD_FUNCTION)>>4;
  LCD_DATA0_PORT |= _BV(LCD_DATA0_PIN);  // _BV(LCD_FUNCTION_8BIT)>>4;
  lcd_toggle_e();
  delay_us(2000); //2000        // delay, busy flag can't be checked here 
    
	// repeat last command 
  lcd_toggle_e();      
  delay_us(64); //64          // delay, busy flag can't be checked here 
    
	// now configure for 4bit mode 
  LCD_DATA0_PORT &= ~_BV(LCD_DATA0_PIN);   // LCD_FUNCTION_4BIT_1LINE>>4
  lcd_toggle_e();
  delay_us(2000);           // some displays need this additional delay 

	// set 4 bit IO
  lcd_instr(LCD_FUNCTION_4BIT_2LINES); // 4-bit interface, dual line,   5x7 dots 
  lcd_toggle_e();
	delay_us(2000);           // some displays need this additional delay 
	
	lcd_instr(LCD_ENTRY_INC_);//cursor move right, no shift display
	lcd_toggle_e();
	delay_us(2500);           // some displays need this additional delay 

	lcd_instr(LCD_DISP_ON);   // display on, cursor off     
	lcd_toggle_e();
	delay_us(2500);           // some displays need this additional delay 

  lcd_home();
}

/**
 * Move cursor on specified line
 */
void lcd_setline(uint8_t line)
{
  uint8_t addressCounter = 0;
	switch(line)
	{
		case 0: addressCounter = LCD_START_LINE1; break;
		case 1: addressCounter = LCD_START_LINE2; break;
		case 2: addressCounter = LCD_START_LINE3; break;
		case 3: addressCounter = LCD_START_LINE4; break;
		default:addressCounter = LCD_START_LINE1; break;
	}
	g_nCurrentLine = line;

    lcd_instr((1<<LCD_DDRAM)+addressCounter);
}

int g_nCurrentLine = 0;

/**
 * Send a null terminated string to the LCD eg. char x[10]="hello!";
 */
void lcd_string(char *text)
{
	char c;
  while ((c = *text++)) {
    lcd_char(c);
  }
}

void lcd_string_format(char *szFormat, ...)
{	
  char szBuffer[256]; //in this buffer we form the message
  int NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
  // int LASTCHAR = NUMCHARS - 1;
  va_list pArgs;
  va_start(pArgs, szFormat);
  vsnprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
  va_end(pArgs);
	
	lcd_string(szBuffer);
}

/**
 * Set cursor to specified position
 * Input:    x  horizontal position  (0: left most position)
 *           y  vertical position    (0: first line)
 */
void lcd_gotoxy(uint8_t x, uint8_t y)
{
  #if LCD_LINES==1
    lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE1+x);
  #elif LCD_LINES==2
   	switch (y) {
  		case 0:
        lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE1+x);
        break;
    	case 1:
        lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE2+x);
        break;
  		default:
        break;
  	}
  #elif LCD_LINES==4
   	switch (y) {
  		case 0:
        lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE1+x);
        break;
    	case 1:
        lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE2+x);
        break;
    	case 2:
        lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE3+x);
        break;
    	case 3:
        lcd_instr((1<<LCD_DDRAM)+LCD_START_LINE4+x);
        break;
  		default:
        break;
  	}
  #endif
}

/**
 * Clear display and set cursor to home position
 */
void lcd_clrscr(void)
{
	g_nCurrentLine = 0;
 	lcd_instr(1<<LCD_CLR);
	delay_us(500);
}

/**
 * Set cursor to home position
 */
void lcd_home(void)
{
	g_nCurrentLine = 0;
  lcd_instr(1<<LCD_HOME);
}

/**
 * Delay function
 */
void delay_int(unsigned long delay)
{
  while(delay--) asm volatile("nop");
}
