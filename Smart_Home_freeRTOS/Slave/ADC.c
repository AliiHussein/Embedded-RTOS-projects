/*
 * ADC.c
 *
 * Created: 3/23/2023 12:13:56 AM
 *  Author: Ali
 */ 

#include "ADC.h"

void ADC_init(){
	SETBIT(ADMUX, REFS0); // AVCC with external cap at AREF pin 
	
	SETBIT(ADCSRA, ADEN); // Enable ADC
	
	ADCSRA |= 0b111; // ADC Prescaler 128, 16Mhz/128 = 125Khz
		
}

uint16_t ADC_read(uint8_t ch){
	
	ADMUX &= 0b11100000;
	ADMUX |= ch;
	
	SETBIT(ADCSRA, ADSC); //Start conversion from analog to digital
	
	while(READBIT(ADCSRA, ADSC) == 1); // while ADC conversion is not complete
		
	return ADC;
}