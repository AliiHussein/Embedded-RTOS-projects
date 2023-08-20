/*
 * LCD_cfg.h
 *
 * Created: 3/7/2023 3:12:17 PM
 *  Author: Ali
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "std_macros.h"

/*
D7--D4 --> A7--A4
EN --> A3
RS --> A2
PORTA(2--7) connected to LCD
*/
#define INIT_LCD_PINS() DDRA|= 0b11111100;
#define LCD_RS(x) if(x == 1) SETBIT(PORTA, 2); else CLRBIT(PORTA, 2);
#define LCD_EN(x) if(x == 1) SETBIT(PORTA, 3); else CLRBIT(PORTA, 3);
#define LCD_D4(x) if(x == 1) SETBIT(PORTA, 4); else CLRBIT(PORTA, 4);
#define LCD_D5(x) if(x == 1) SETBIT(PORTA, 5); else CLRBIT(PORTA, 5);
#define LCD_D6(x) if(x == 1) SETBIT(PORTA, 6); else CLRBIT(PORTA, 6);
#define LCD_D7(x) if(x == 1) SETBIT(PORTA, 7); else CLRBIT(PORTA, 7);

#endif /* LCD_CFG_H_ */