/*
 * eeprom.c
 *
 * Created: 3/9/2023 5:02:57 PM
 *  Author: Ali
 */ 

#include "eeprom.h"

void eeprom_write(uint16_t add, uint8_t data){
	while(READBIT(EECR, EEWE) != 0); // wait until EEWE becomes zero
	EEAR = add;
	EEDR = data;
	SETBIT(EECR, EEMWE);
	SETBIT(EECR, EEWE);
}

uint8_t eeprom_read(uint16_t add){
	while(READBIT(EECR, EEWE) != 0); // wait until EEWE becomes zero
	EEAR = add;
	SETBIT(EECR, EERE);
	return EEDR;
}
