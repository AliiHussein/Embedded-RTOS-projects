/*
 * LCD.h
 *
 * Created: 3/7/2023 2:24:20 PM
 *  Author: Ali
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "std_macros.h"

void LCD_init(void);
void LCD_write_char(uint8_t);
void LCD_write_command(uint8_t);
void LCD_write_number(int32_t);
void LCD_write_string(uint8_t *);


#endif /* LCD_H_ */