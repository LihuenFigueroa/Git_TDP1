/*
 * lcd.c
 *
 *  Created on: 30/07/2013
 *      Author: pc2
 */
/**************************************************************************
 * Basic int8_tacter LCD functions
 * By F�bio Pereira
 * 01/15/08
 **************************************************************************
 * 
 */
#include "lcd.h"
#include "stdint.h"                /* <= Standar Integer data types header */
#include "chip.h"                  /* <= LPCopen header */
#include "sapi.h"


#define SIZE_BUFFER_OUT 32U


#define INPUT     0
#define OUTPUT    1


/* Define the number of cycles for 1ms */
#define INACCURATE_TO_MS 20400

union ubyte {
	int8_t _byte;
	struct {
		uint8_t b0 :1;
		uint8_t b1 :1;
		uint8_t b2 :1;
		uint8_t b3 :1;
		uint8_t b4 :1;
		uint8_t b5 :1;
		uint8_t b6 :1;
		uint8_t b7 :1;
	} bit;
};

// Display configuration global variable
static int8_t lcd_mode;
static uint8_t poscur;
static uint8_t pos;
static uint8_t buffer[32];
//**************************************************************************
//* A simple delay function (used by LCD functions)
//**************************************************************************
//* Calling arguments
//* uint8_t time: aproximate delay time in microseconds
//**************************************************************************

//*************************************************************************//
void LCD_Set_PosCur(uint8_t x,uint8_t y)
{
	poscur = (16*y)+(x);
}
void LCD_delay_ms(uint64_t delay_ms) {
   volatile uint64_t i;
   volatile uint64_t delay;

   delay = INACCURATE_TO_MS * delay_ms;

   for( i=delay; i>0; i-- );
}
//**************************************************************************
//* Send a nibble to the LCD
//**************************************************************************
//* Calling arguments
//* int8_t data : data to be sent to the display
//**************************************************************************
void LCD_send_nibble(int8_t data) {
	union ubyte my_union;
	my_union._byte = data;
	// Output the four data bits
	//Chip_GPIO_SetPinState( LPC_GPIO_PORT, LCD_D1_GPIO, LCD_D1_PIN,
	//		my_union.bit.b0);
	gpioWrite(LCD_1, my_union.bit.b0);
	gpioWrite(LCD_2, my_union.bit.b1);
	gpioWrite(LCD_3, my_union.bit.b2);
	gpioWrite(LCD_4, my_union.bit.b3);

	// pulse the LCD enable line
	gpioWrite(LCD_EN, ON);
	for (data = 255; data; data--);
	gpioWrite(LCD_EN, OFF);
}

//**************************************************************************
//* Write a byte into the LCD
//**************************************************************************
//* Calling arguments:
//* int8_t address : 0 for instructions, 1 for data
//* int8_t data : command or data to be written
//**************************************************************************
void LCD_send_byte(int8_t address, int8_t data) {
	uint16_t temp;
	if (address == 0)
		gpioWrite(LCD_RS, OFF);
	else
		gpioWrite(LCD_RS, ON);
	gpioWrite(LCD_EN, OFF); // set LCD enable line to 0
	LCD_send_nibble(data >> 4); // send the higher nibble
	LCD_send_nibble(data & 0x0f); // send the lower nibble
	for (temp = 255; temp; temp--);
}

//**************************************************************************
//* LCD initialization
//**************************************************************************
//* Calling arguments:
//* int8_t mode1 : display mode (number of lines and int8_tacter size)
//* int8_t mode2 : display mode (cursor and display state)
//**************************************************************************
void LCD_init(int8_t mode1, int8_t mode2) {
	int8_t aux;
	uint8_t i;
	//Inicializacion del Buffer de Salida
	for (i = 0; i < SIZE_BUFFER_OUT; i++) {
		//Inicializa el buffer con todos espacios
		buffer[i] = ' ';
	}
	pos = 0;
	//Inicializacion del dispositivo LCD

	/* Config EDU-CIAA-NXP LCD Pins as GPIOs */
	//Chip_SCU_PinMux(LCD_ENABLE_P, LCD_ENABLE_P_, MD_PUP, FUNC4); /* P4_9,  GPIO5[13],LCD_ENABLE*/
	//Chip_SCU_PinMux(LCD_RS_P, LCD_RS_P_, MD_PUP, FUNC4); /* P4_8,  GPIO5[12],LCD_RS */
	//Chip_SCU_PinMux(LCD_D1_P, LCD_D1_P_, MD_PUP, FUNC0); /* P4_4,  GPIO2[4],LCD_D1 */
	//Chip_SCU_PinMux(LCD_D2_P, LCD_D2_P_, MD_PUP, FUNC0); /* P4_5, GPIO2[5],LCD_D2*/
	//Chip_SCU_PinMux(LCD_D3_P, LCD_D3_P_, MD_PUP, FUNC0); /* P4_6, GPIO2[6],LCD_D3 */
	//Chip_SCU_PinMux(LCD_D4_P, LCD_D4_P_, MD_PUP, FUNC4); /* P4_10, GPIO5[14],LCD_D4 */

	/* Config EDU-CIAA-NXP LCD Pins as Outputs */
	gpioConfig( LCD_EN, GPIO_OUTPUT );
	gpioConfig( LCD_1, GPIO_OUTPUT );
	gpioConfig( LCD_2, GPIO_OUTPUT );
	gpioConfig( LCD_3, GPIO_OUTPUT );
	gpioConfig( LCD_4, GPIO_OUTPUT );
	gpioConfig( LCD_RS, GPIO_OUTPUT );

	/* Init EDU-CIAA-NXP LCD Pins OFF */
	gpioWrite(LCD_1,OFF);
	gpioWrite(LCD_2,OFF);
	gpioWrite(LCD_3,OFF);
	gpioWrite(LCD_4,OFF);
	gpioWrite(LCD_RS,OFF);
	gpioWrite(LCD_EN,OFF);

	LCD_delay_ms(16); // retardo de 15 ms
	// LCD 4-bit mode initialization sequence
	// send three times 0x03 and then 0x02 to finish configuring the LCD
	for (aux = 0; aux < 3; ++aux) {
		LCD_send_nibble(3);
		LCD_delay_ms(5);
	}
	LCD_send_nibble(2);
	// Now send the LCD configuration data
	LCD_send_byte(0, 0x20 | mode1);
	LCD_send_byte(0, 0x08 | mode2);
	lcd_mode = 0x08 | mode2;

	LCD_send_byte(0, 1);
	LCD_delay_ms(5);
	LCD_send_byte(0, 6); //entry mode set I/D=1 S=0
}

//**************************************************************************
//* LCD cursor position set
//**************************************************************************
//* Calling arguments:
//* int8_t x : column (starting by 0)
//* int8_t y : line (0 or 1)
//**************************************************************************
void LCD_pos_xy(int8_t x, int8_t y) {
	int8_t address;
	if (y)
		address = LCD_SEC_LINE;
	else
		address = 0;
	address += x;
	LCD_send_byte(0, 0x80 | address);
}

//**************************************************************************
//* Write a int8_tacter on the display
//**************************************************************************
//* Calling arguments:
//* int8_t c : int8_tacter to be written
//**************************************************************************
//* Notes :
//* \f clear the display
//* \n and \r return the cursor to line 1 column 0
//**************************************************************************
void LCD_write_int8_t(int8_t c) {
	switch (c) {
	case '\f':
		LCD_send_byte(0, 1);
		LCD_delay_ms(5);
		break;
	case '\n':
	case '\r':
		LCD_pos_xy(0, 1);
		break;
	default:
		LCD_send_byte(1, c);
	}
}

//**************************************************************************
//* Write a string on the display
//**************************************************************************
//* Calling arguments:
//* int8_t *c : pointer to the string
//**************************************************************************
void LCD_write_string(int8_t *c) {
	while (*c) {
		LCD_write_int8_t(*c);
		c++;
	}
}

//**************************************************************************
//* Turn the display on
//**************************************************************************
void LCD_display_on(void) {
	lcd_mode |= 4;
	LCD_send_byte(0, lcd_mode);
}

//**************************************************************************
//* Turn the display off
//**************************************************************************
void LCD_display_off(void) {
	lcd_mode &= 0b11111011;
	LCD_send_byte(0, lcd_mode);
}

//**************************************************************************
//* Turn the cursor on
//**************************************************************************
void LCD_cursor_on(void) {
	lcd_mode |= 2;
	LCD_send_byte(0, lcd_mode);
}

//**************************************************************************
//* Turn the cursor off
//**************************************************************************
void LCD_cursor_off(void) {
	lcd_mode &= 0b11111101;
	LCD_send_byte(0, lcd_mode);
}

//**************************************************************************
//* Turn on the cursor blink function
//**************************************************************************
void LCD_cursor_blink_on(void) {
	lcd_mode |= 1;
	LCD_send_byte(0, lcd_mode);
}

//**************************************************************************
//* Turn off the cursor blink function
//**************************************************************************
void LCD_cursor_blink_off(void) {
	lcd_mode &= 0b11111110;
	LCD_send_byte(0, lcd_mode);
}
void LCD_Write_Buffer(uint8_t data[SIZE_BUFFER_OUT]) {
	uint8_t i;
	for (i = 0; i < SIZE_BUFFER_OUT; i++) {
		buffer[i] = data[i];
	}
}
void LCD_Write_Buffer_At_Pos(uint8_t data, uint8_t pos) {
	buffer[pos] = data;
}
void LCD_Write_Buffer_Line(uint8_t data[SIZE_BUFFER_OUT / 2],
		uint8_t line) {
	uint8_t i;
	for (i = 16 * line; i < (SIZE_BUFFER_OUT / 2) * (line + 1); i++) {
		if (i >= SIZE_BUFFER_OUT / 2) {
			buffer[i] = data[i - (SIZE_BUFFER_OUT / 2)];
		} else {
			buffer[i] = data[i];
		}
	}
}
void LCD_Interrupt(void) {
	uint8_t i;
	LCD_pos_xy(pos % (SIZE_BUFFER_OUT / 2), pos / (SIZE_BUFFER_OUT / 2));
	for (i=255;i>0;i--);
	LCD_write_int8_t(buffer[pos]);
	pos = (pos + 1) % SIZE_BUFFER_OUT;
	LCD_pos_xy(poscur % (SIZE_BUFFER_OUT / 2), poscur / (SIZE_BUFFER_OUT / 2));
}
void LCD_Reset_Pos(void) {
	pos = 0;
}
void LCD_Clear_Buffer(void) {
	uint8_t i;
	//Inicializacion del Buffer de Salida
	for (i = 0; i < SIZE_BUFFER_OUT; i++) {
		//Inicializa el buffer con todos espacios
		buffer[i] = ' ';
	}
	pos = 0;
}

