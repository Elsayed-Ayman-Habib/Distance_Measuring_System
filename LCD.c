/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: Source file for the LCD
 *
 * Author: Elsayed Ayman Elsayed Ali Habib
 *
 *******************************************************************************/
/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "LCD.h"
#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */
#include "avr/delay.h"
#include <stdlib.h>
/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/
void LCD_sendCommand(uint8 command) {/*FUNCTION TO SEND SPECIFIC COMMANDS TO CONTROL LCD */

	GPIO_writePin(COMMAND_LINE, RS_ID, LOGIC_LOW);

	GPIO_writePin(COMMAND_LINE, RW_ID, LOGIC_LOW );
	_delay_ms(1);

	GPIO_writePin(COMMAND_LINE, E_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePort(DATA_LINE, command);
	_delay_ms(1);

	GPIO_writePin(COMMAND_LINE, E_ID, LOGIC_LOW);
	_delay_ms(1);
}
void LCD_init() {
	GPIO_setupPinDirection(COMMAND_LINE, RS_ID, PIN_OUTPUT); //RS INIT
	GPIO_setupPinDirection(COMMAND_LINE, RW_ID, PIN_OUTPUT); // RW INIT
	GPIO_setupPinDirection(COMMAND_LINE, E_ID, PIN_OUTPUT); // ENABLE INIT
	GPIO_setupPortDirection(DATA_LINE, PORT_OUTPUT); //INIT PORTC FOR DATA BUS
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
	LCD_sendCommand(LCD_CURSOR_OFF );
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
void LCD_displayCharacter(uint8 data) {

	GPIO_writePin(COMMAND_LINE, RS_ID, LOGIC_HIGH);//RS SET FOR DISPLAYING DATA

	GPIO_writePin(COMMAND_LINE, RW_ID, LOGIC_LOW);//WRITE MODE
	_delay_ms(1);

	GPIO_writePin(COMMAND_LINE, E_ID, LOGIC_HIGH);//SET ENABLE
	_delay_ms(1);

	GPIO_writePort(DATA_LINE, data);//PASSING DATA TO DISPLAY
	_delay_ms(1);

	GPIO_writePin(COMMAND_LINE, E_ID, LOGIC_LOW);//CLEAR ENABLE
	_delay_ms(1);
}
void LCD_displayString(const char *string) {/*FUNCTION TO DISPLAY STRING CHAR BY CHAR*/
	uint8 i = 0;
	while (string[i] != '\0') {
		LCD_displayCharacter(string[i]);
		i++;
	}

}
void LCD_moveCursor(uint8 r, uint8 c) {/*FUNCTION TO MOVE CURSOR TO SPECIFIC LOCATION USING ROW AND COLUMN*/
	uint8 LCD_address = 0;
	switch (r) {
	case 0:
		LCD_address = c;
		break;
	case 1:
		LCD_address = c + 0x40;
		break;
	case 2:
		LCD_address = c + 0x10;
		break;
	case 3:
		LCD_address = c + 0x50;
		break;
	}
	LCD_sendCommand(LCD_address | LCD_SET_CURSOR_LOCATION);
}
void LCD_displayStringRowColumn(uint8 r, uint8 c, const char *string) {/*DISPLAY STRING STARTING FROM A SPECIFIC LOCATION USING ROW AND COLUMN*/
	LCD_moveCursor(r, c);
	LCD_displayString(string);
}
void LCD_clearScreen() {/*FUNCTION TO CLEAR DISPLAY*/
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
void LCD_integerToString(int data) {/*FUNCTION TO DISPLAY INTEGER RESULTS*/
	char buffer[16];
	itoa(data, buffer, 10);
	LCD_displayString(buffer);

}
