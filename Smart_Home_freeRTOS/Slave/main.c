/*
 * Slave.c
 *
 * Created: 10/3/2023 11:28:45 PM
 * Author : Ali
 */ 

#include "SPI.h"
#include "LCD.h"
#include "ADC.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LCD.h"

#define min_temp 35

int AC_flag = 0;

void room_control(void){
	while (1)
	{
		switch(SPI_read()){
			
			case 1: TOGBIT(PORTD, 4); LCD_write_command(0x83); LCD_write_char(READBIT(PORTD, 4) + '0'); break;
			case 2: TOGBIT(PORTD, 5); LCD_write_command(0x88); LCD_write_char(READBIT(PORTD, 5) + '0'); break;
			case 3: TOGBIT(PORTD, 6); LCD_write_command(0x8d); LCD_write_char(READBIT(PORTD, 6) + '0'); break;
			case 5: TOGBIT(PORTD, 3); LCD_write_command(0xc8); LCD_write_char(READBIT(PORTD, 3) + '0'); break;
			case 6: AC_flag = (AC_flag == 0)? 1: 0; break;
		}
	}
}

void Temp_readings(void){
	// Variables initializations
	int value = 0;
	int temp = 0;
	while (1)
	{
		value = ADC_read(0);
		temp = value / 10.23;
		
	
		if(temp >= min_temp && AC_flag){
			SETBIT(PORTD, 2);
			LCD_write_command(0xc3);
			LCD_write_char('1');
		}
		else{
			CLRBIT(PORTD, 2);
			LCD_write_command(0xc3);
			LCD_write_char('0');
		}


		
		
			
		vTaskDelay(200);
	}
}

int main(void)
{
	SPI_init_slave();
	LCD_init();
	ADC_init();
	
	LCD_write_string("Hi, Im slave");
	_delay_ms(400);
	
	//set pins
	SETBIT(DDRD, 2);  // PD2 output
	SETBIT(DDRD, 3);  // PD3 output
	SETBIT(DDRD, 4);  // PD4 output
	SETBIT(DDRD, 5);  // PD5 output
	SETBIT(DDRD, 6);  // PD6 output
	SETBIT(DDRD, 7);  // PD7 output
	
	LCD_write_command(1);
	LCD_write_string("R1:0 R2:0 R3:0");
	LCD_write_command(0xc0);
	LCD_write_string("AC:0 TV:0");
	
	xTaskCreate(room_control, "T1", 80, NULL, 1, NULL);
	xTaskCreate(Temp_readings, "T2", 80, NULL, 2, NULL);
	vTaskStartScheduler();
	
	
	
	
}

