/*
 * eeprom.h
 *
 * Created: 3/9/2023 5:04:03 PM
 *  Author: Ali
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_macros.h"

void eeprom_write(uint16_t add, uint8_t data);
uint8_t eeprom_read(uint16_t add);

#endif /* EEPROM_H_ */