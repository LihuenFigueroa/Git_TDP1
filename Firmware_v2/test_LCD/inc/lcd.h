/*
 * lcd.h
 *
 *  Created on: 30/07/2013
 *      Author: pc2
 */

#ifndef LCD_H_
#define LCD_H_


// The following defines set the default pins for the LCD display
#ifndef LCD_ENABLE_P			 // if LCD_ENABLE_P is not defined

#include "stdint.h"                /* <= Standar Integer data types header */
#include "chip.h"                  /* <= LPCopen header */
#include "sapi.h"

#endif

#define LCD_SEC_LINE    0x40    // Address of the second line of the LCD

// LCD configuration constants
#define CURSOR_ON       2
#define CURSOR_OFF      0
#define CURSOR_BLINK    1
#define CURSOR_NOBLINK  0
#define DISPLAY_ON      4
#define DISPLAY_OFF     0
#define DISPLAY_8X5     0
#define DISPLAY_10X5    4
#define _2_LINES        8
#define _1_LINE         0

#define LCD_RS			ENET_RXD1
#define LCD_EN			ENET_TXEN
#define LCD_1			ENET_MDC
#define LCD_2			ENET_CRS_DV
#define LCD_3			ENET_MDIO
#define LCD_4			ENET_TXD0

//**************************************************************************
//* Prototypes
//**************************************************************************
void LCD_delay_ms (uint64_t delay_ms);
void LCD_send_nibble(char data);
void LCD_send_byte(char address, char data);
void LCD_init(char mode1, char mode2);
void LCD_pos_xy(char x, char y);
void LCD_write_char(char c);
void LCD_write_string (char *c);
void LCD_display_on(void);
void LCD_display_off(void);
void LCD_cursor_on(void);
void LCD_cursor_off(void);
void LCD_cursor_blink_on(void);
void LCD_cursor_blink_off(void);

// New Part
void LCD_Write_Buffer(unsigned char data[32]);
void LCD_Write_Buffer_Line(unsigned char data[32],unsigned char line);
void LCD_Interrupt(void);
void LCD_Reset_Pos(void);
void LCD_Clear_Buffer(void);
void LCD_Write_Buffer_At_Pos(unsigned char data, unsigned char pos);
#define BUS_CLOCK 8000

#endif /* LCD_H_ */
