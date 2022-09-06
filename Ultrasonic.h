
/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: ICU.h
 *
 * Description: Header file for the ICUs
 *
 * Author: Elsayed Ayman Elsayed Ali Habib
 *
 *******************************************************************************/
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TRIGGER_PORT PORTB_ID/*PINB5 used as triggering pin*/
#define TRIGGER_PIN PIN5_ID


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void Ultrasonic_Init();
void Ultrasonic_Trigger();
uint16 Ultrasonic_readDistance();
void Ultrasonic_edgeProcessing();


#endif
