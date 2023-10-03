/*
 * KEYPAD_cfg.h
 *
 * Created: 3/7/2023 3:13:46 PM
 *  Author: Ali
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#include "std_macros.h"

/*
PORTC 0 to 3 pulled up input
PORTC 4 to 7 Output

*/
#define INIT_KEYPAD_PINS() DDRC |= 0b11110000; PORTC =  0b11111111;

#define K0() READBIT(PINC, 0)
#define K1() READBIT(PINC, 1)
#define K2() READBIT(PINC, 2)
#define K3() READBIT(PINC, 3)
#define K4(x) if(x == 1) SETBIT(PORTC, 4); else CLRBIT(PORTC, 4);
#define K5(x) if(x == 1) SETBIT(PORTC, 5); else CLRBIT(PORTC, 5);
#define K6(x) if(x == 1) SETBIT(PORTC, 6); else CLRBIT(PORTC, 6);
#define K7(x) if(x == 1) SETBIT(PORTC, 7); else CLRBIT(PORTC, 7);


#endif /* KEYPAD_CFG_H_ */