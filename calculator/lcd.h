#pragma once

#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h> 
#include <avr/pgmspace.h>

//--------------------------------CONFIGURE LCD------------------------------------------------------//
#define LCD_LINES		             2			 // number of visible lines of the display
#define LCD_DISP_LENGTH          16      // visibles characters per line of the display 
#define LCD_START_LINE1  		     0x00    // DDRAM address of first char of line 1 
#define LCD_START_LINE2  		     0x40    // DDRAM address of first char of line 2 
#define LCD_START_LINE3  		     0x14    // DDRAM address of first char of line 3 
#define LCD_START_LINE4  		     0x54    // DDRAM address of first char of line 4 

//Purpose: work with a LCD display
#define LCD_DATA0_PORT           PORTD   // port for 4bit data bit 0 		//D5 poz:3 connector...[digits 0,1,...]
#define LCD_DATA1_PORT           PORTD   // port for 4bit data bit 1 		//D6
#define LCD_DATA2_PORT           PORTD   // port for 4bit data bit 2 		//D7
#define LCD_DATA3_PORT           PORTD   // port for 4bit data bit 3 		//B0
#define LCD_DATA0_PIN            3       // pin for 4bit data bit 0  		
#define LCD_DATA1_PIN            2       // pin for 4bit data bit 1  
#define LCD_DATA2_PIN            1       // pin for 4bit data bit 2  
#define LCD_DATA3_PIN            0       // 0 for 4bit data bit 3  
#define LCD_RS_PORT              PORTD   // port for RS line         		//D3 poz:1 connector
#define LCD_RS_PIN               5       // pin  for RS line         
#define LCD_E_PORT               PORTD   // port for Enable line     		//D4 poz:2 connector
#define LCD_E_PIN                4       // pin  for Enable line     
//#define LCD_RW_PORT              LCD_PORT // port for RW line UNUSED - we only WRITE
//#define LCD_RW_PIN               5        // pin  for RW line UNUSED - we only WRITE
//---------------------------------------------------------------------------------------------------//

#define LCD_CLR                  0x0     // DB0: clear display                  
#define LCD_HOME                 0x1     // DB1: return to home position        
#define LCD_ENTRY_MODE           0x2     // DB2: set entry mode                 
#define LCD_ENTRY_INC            0x1     // DB1: 1=increment, 0=decrement     
#define LCD_ENTRY_SHIFT          0x0     // DB2: 1=display shift on           
#define LCD_ON                   0x3     // DB3: turn lcd/cursor on             
#define LCD_ON_DISPLAY           0x2     // DB2: turn display on              
#define LCD_ON_CURSOR            0x1     // DB1: turn cursor on               
#define LCD_ON_BLINK             0x0     // DB0: blinking cursor ?          
#define LCD_MOVE                 0x4     // DB4: move cursor/display            
#define LCD_MOVE_DISP            0x3     // DB3: move display (0-> cursor) ?  
#define LCD_MOVE_RIGHT           0x2     // DB2: move right (0-> left) ?      
#define LCD_FUNCTION             0x5     // DB5: function set                   
#define LCD_FUNCTION_8BIT        0x4     // DB4: set 8BIT mode (0->4BIT mode) 
#define LCD_FUNCTION_2LINES      0x3     // DB3: two lines (0->one line)      
#define LCD_FUNCTION_10DOTS      0x2     // DB2: 5x10 font (0->5x7 font)      
#define LCD_CGRAM                0x6     // DB6: set CG RAM address             
#define LCD_DDRAM                0x7     // DB7: set DD RAM address             
#define LCD_BUSY                 0x7     // DB7: LCD is busy                    

// set entry mode: display shift on/off, dec/inc cursor move direction 
#define LCD_ENTRY_DEC            0x04	   // display shift off, dec cursor move dir 
#define LCD_ENTRY_DEC_SHIFT      0x05    // display shift on,  dec cursor move dir 
#define LCD_ENTRY_INC_           0x06    // display shift off, inc cursor move dir 
#define LCD_ENTRY_INC_SHIFT      0x07    // display shift on,  inc cursor move dir 

// display on/off, cursor on/off, blinking char at cursor position 
#define LCD_DISP_OFF             0x08    // display off                            
#define LCD_DISP_ON              0x0C    // display on, cursor off                 
#define LCD_DISP_ON_BLINK        0x0D    // display on, cursor off, blink char     
#define LCD_DISP_ON_CURSOR       0x0E    // display on, cursor on                  
#define LCD_DISP_ON_CURSOR_BLINK 0x0F    // display on, cursor on, blink char      

// move cursor/shift display 
#define LCD_MOVE_CURSOR_LEFT     0x10    // move cursor left  (decrement)          
#define LCD_MOVE_CURSOR_RIGHT    0x14    // move cursor right (increment)          
#define LCD_MOVE_DISP_LEFT       0x18    // shift display left                     
#define LCD_MOVE_DISP_RIGHT      0x1C    // shift display right                    

// function set: set interface data length and number of display lines 
#define LCD_FUNCTION_4BIT_1LINE  0x20    // 4-bit interface, single line, 5x7 dots 
#define LCD_FUNCTION_4BIT_2LINES 0x28    // 4-bit interface, dual line,   5x7 dots 
#define LCD_FUNCTION_8BIT_1LINE  0x30    // 8-bit interface, single line, 5x7 dots 
#define LCD_FUNCTION_8BIT_2LINES 0x38    // 8-bit interface, dual line,   5x7 dots 
#define LCD_MODE_DEFAULT         ((1<<LCD_ENTRY_MODE) | (1<<LCD_ENTRY_INC) )

// functional macros
#define lcd_e_high()             LCD_E_PORT  |=  _BV(LCD_E_PIN);
#define lcd_e_low()              LCD_E_PORT  &= ~_BV(LCD_E_PIN);
#define lcd_rs_high()            LCD_RS_PORT |=  _BV(LCD_RS_PIN)
#define lcd_rs_low()             LCD_RS_PORT &= ~_BV(LCD_RS_PIN)
#define LCD_DDR(x) 		           (*(&x - 1))

//delay functions
#define F_CPU                    8000000UL//Your clock speed in Hz (8Mhz here)
#define LOOP_CYCLES              8        //Number of cycles that the loop takes
#define delay_us(num)            delay_int(num/(LOOP_CYCLES*(1/(F_CPU/1000000.0))))

#define PORT_ON(port_letter, number)      port_letter |= (1<<number)
#define PORT_OFF(port_letter, number)     port_letter &= ~(1<<number)
#define PORT_ALL_ON(port_letter, number)  port_letter |= (number)
#define PORT_ALL_OFF(port_letter, number) port_letter &= ~(number)
#define FLIP_PORT(port_letter, number)    port_letter ^= (1<<number)
#define PORT_IS_ON(port_letter, number)   (port_letter & (1<<number))
#define PORT_IS_OFF(port_letter, number)  !(port_letter & (1<<number))

void lcd_toggle_e(void);
void lcd_write(uint8_t data,uint8_t rs) ;
void lcd_instr(uint8_t instr);
void lcd_char(uint8_t data);
void lcd_init();
void lcd_setline(uint8_t line);
extern int g_nCurrentLine;
void lcd_string(char *text);
void lcd_string_format(char *szFormat, ...);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_clrscr(void);
void lcd_clrline(int);
void lcd_home(void);
void delay_int(unsigned long delay);
