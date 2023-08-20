/*
 * App1.c
 *
 * Created: 8/20/2023 8:12:46 PM
 * Author : Ali
 */ 

#include "std_macros.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LCD.h"
#include "semphr.h"

SemaphoreHandle_t lcd_flag = 0; // creating a semaphore variable

void task1(void){
	uint8_t count = 0;
	while(1){
		if(xSemaphoreTake(lcd_flag, 1000) == 1){
			LCD_write_command(0x80);
			LCD_write_number(count++);
			xSemaphoreGive(lcd_flag);
			vTaskDelay(100);
		}
		
	}
}

void task2(void){
	uint8_t count = 0;
	while(1){
		if(xSemaphoreTake(lcd_flag, 1000) == 1){
			LCD_write_command(0xc0);
			LCD_write_number(count++);
			xSemaphoreGive(lcd_flag);
			vTaskDelay(200);
		}
		
	}
}

void led_button(void){
	SETBIT(DDRB, 1); // PB1 output
	CLRBIT(DDRB, 2); // PB2 input
	SETBIT(PORTB, 2); // PB2 is pulled up
	while(1){
		if(READBIT(PINB, 2) == 1){
			SETBIT(PORTB, 1);
		}
		else{
			CLRBIT(PORTB, 1);
		}
		vTaskDelay(10);
		
	}
}

int main(void)
{
	LCD_init();
	vSemaphoreCreateBinary(lcd_flag);
    xTaskCreate(task1, "T1", 80, NULL, 1, NULL);
	xTaskCreate(task2, "T2", 80, NULL, 1, NULL);
	xTaskCreate(led_button, "T3", 80, NULL, 1, NULL);
	vTaskStartScheduler();
}

