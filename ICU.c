/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: ICU.c
 *
 * Description: Source file for the ICU
 *
 * Author: Elsayed Ayman Elsayed Ali Habib
 *
 *******************************************************************************/
/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "ICU.h"
#include "gpio.h"
#include <avr/io.h>
#include "common_macros.h"
#include <avr/interrupt.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*global_callBackPtr)(void) = NULL_PTR;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	if(global_callBackPtr != NULL_PTR)
	{

		(*global_callBackPtr)();
	}
}
/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/
void ICU_init(const ICU_ConfigType *Config1) {
	GPIO_setupPinDirection(PORTD_ID, ICU_INPUT_PIN, PIN_INPUT);
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);

	TCCR1B = (TCCR1B & 0Xf8) | (Config1->PRE);
	TCCR1B = (TCCR1B & 0xbf) | ((Config1->EDGE) << 6);
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK |= (1 << TICIE1);
}
void ICU_setCallBack(void (*function_ptr)(void)) {
	global_callBackPtr = function_ptr;
}
void ICU_setEdgeDetectionType(const Edge edge1) {
	TCCR1B = (TCCR1B & 0xbf) | (edge1 << 6);
}
uint16 ICU_getICUvalue() {
	return ICR1;
}
void ICU_clearTimerValue() {
	TCNT1 = 0;
}
void ICU_deInit() {
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK &= ~(1 << TICIE1);

}
