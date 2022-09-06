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
#ifndef ICU_H_
#define ICU_H_
/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ICU_INPUT_PIN PIN6_ID
/*******************************************************************************
 *                               Type declaration                              *
 *******************************************************************************/
typedef enum{
	NO_CLOCK,PRE1,PRE8,PRE64,PRE256,PRE1024,EXTERNAL_CLOCK_FALLING,EXTERNAL_CLOCK_RISING
}Prescaler;
typedef enum{
	FALLING,RISING
}Edge;

typedef struct{
	Prescaler PRE;
	Edge EDGE;
}ICU_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void ICU_init(const ICU_ConfigType *Config1);
void ICU_setCallBack(void (*function_ptr)(void));
void ICU_setEdgeDetectionType(const Edge edge1);
uint16 ICU_getICUvalue();
void ICU_clearTimerValue();
void ICU_deInit();



#endif /* ICU_H_ */
