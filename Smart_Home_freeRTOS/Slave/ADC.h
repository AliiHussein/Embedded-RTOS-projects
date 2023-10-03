/*
 * ADC.h
 *
 * Created: 3/23/2023 12:14:07 AM
 *  Author: Ali
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "std_macros.h"

void ADC_init(void);
uint16_t ADC_read(uint8_t ch);


#endif /* ADC_H_ */