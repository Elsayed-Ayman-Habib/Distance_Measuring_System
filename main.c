/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: main.c
 *
 * Author: Elsayed Ayman Elsayed Ali Habib
 *
 *******************************************************************************/
/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/

#include "LCD.h"
#include "Ultrasonic.h"
#include <avr/io.h>


int main() {

	SREG |= (1<<7);        //enable interrupts
	LCD_init();            //initialize LCD
	Ultrasonic_Init();     //initialize Ultrasonic
	LCD_displayString("Distance= ");
	LCD_displayStringRowColumn(0,14,"cm");
	while (1) {
		LCD_moveCursor(0,11);
		if(Ultrasonic_readDistance() <= 57){
			/*the following if conditions are used to calibrate the distance to be accurate*/
			LCD_integerToString(Ultrasonic_readDistance()+1);
			/*when distance is below 57 cm there is a negative error of 1 cm*/
		}
		else if((Ultrasonic_readDistance() >= 57) && (Ultrasonic_readDistance() <= 150)){
			LCD_integerToString(Ultrasonic_readDistance()+2);

			/*when distance is more than 57 cm and less than 150 cm there is a negative error of 2 cm*/
		}
		else{
			LCD_integerToString(Ultrasonic_readDistance()+3);
			/*when distance is more than 150 cm there is a negative error of 3 cm*/
		}
		LCD_displayCharacter(' ');  //to prevent error in number display when going below 3 digit number ex: 100 --> 990
	}

}
