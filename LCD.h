/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: Header file for the LCD
 *
 * Author: Elsayed Ayman Elsayed Ali Habib
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DATA_LINE PORTA_ID
#define COMMAND_LINE PORTB_ID
#define RS_ID PIN0_ID
#define RW_ID PIN1_ID
#define E_ID PIN2_ID
/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void LCD_sendCommand(uint8 command);
void LCD_init();
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char * string);
void LCD_moveCursor(uint8 r, uint8 c);
void LCD_displayStringRowColumn(uint8 r, uint8 c, const char *string);
void LCD_clearScreen();
void LCD_integerToString(int data);
#endif /* LCD_H_ */
