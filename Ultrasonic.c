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
#include "Ultrasonic.h"
#include <util/delay.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8 edgecounts = 0;//count the number of falling and rising edges
uint32 echo_time = 0;//store the time taken by sound wave to travel from and to the sensor

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/


/*
 * Ultrasonic_Init:
 * setup PINB5 for output to trigger the sensor
 * Configure ICU with F_CPU/8 clock and interrupt on rising edge
 * set Ultrasonic_edgeProcessing as the call back function
 * */
void Ultrasonic_Init(){
	GPIO_setupPinDirection(TRIGGER_PORT,TRIGGER_PIN,PIN_OUTPUT);
	ICU_ConfigType Config = {PRE8,RISING};
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	ICU_init(&Config);

}
/*
 * trigger the sensor with a pulse with duration of 10 us
 *
 */


void Ultrasonic_Trigger(){
	GPIO_writePin(TRIGGER_PORT,TRIGGER_PIN,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT,TRIGGER_PIN,LOGIC_LOW);
}


/*
 * Calculate the distance given the time taken by echo to travel from and to the sensor
 * */
uint16 Ultrasonic_readDistance(){

	uint32 distance = 0;
	Ultrasonic_Trigger();

	if(edgecounts == 2)
	{
		edgecounts = 0;
	}
	distance = echo_time/58.8;
	return distance;
}


/*
 * process the edge events
 * on first rising edge start the timer count and set the next interrupt event to be falling edge
 *
 * on falling edge store the value of timer and start another timer count with interrupt event on rising edge
 * */
void Ultrasonic_edgeProcessing(){
	edgecounts++;
	if(edgecounts == 1){
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(edgecounts == 2){
		echo_time = ICU_getICUvalue();
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(RISING);

	}

}
