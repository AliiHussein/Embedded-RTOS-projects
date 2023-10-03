/*
 * Smart_Home_freeRTOS.c
 *
 * Created: 10/3/2023 11:24:37 PM
 * Author : Ali
 */ 

#include "std_macros.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "eeprom.h"
#include "SPI.h"

// Functions prototype
void lock_system(void);
uint8_t get_input_from_user(void);
uint8_t get_password_from_user(void);
uint8_t enter_password(uint8_t);
void admin_control(void);
void guest_control(void);

void lock_system(void){
	while(1){
		// first time
		if(eeprom_read(100) != 4){
			LCD_write_command(1);
			LCD_write_string("Login for");
			LCD_write_command(0xc0);
			LCD_write_string("first time");
			_delay_ms(400);
			
			eeprom_write(100, 4);
			
			// Setting Admin password
			LCD_write_command(1);
			LCD_write_string("Set Admin pass");
			LCD_write_command(0xc0);
			LCD_write_string("Admin pass: ");
			
			eeprom_write(20, get_password_from_user());
			eeprom_write(21, get_password_from_user());
			eeprom_write(22, get_password_from_user());
			eeprom_write(23, get_password_from_user());
			
			// Setting Guest password
			LCD_write_command(1);
			LCD_write_string("Set Guest pass");
			LCD_write_command(0xc0);
			LCD_write_string("Guest pass: ");
			
			eeprom_write(30, get_password_from_user());
			eeprom_write(31, get_password_from_user());
			eeprom_write(32, get_password_from_user());
			eeprom_write(33, get_password_from_user());
			
		}
		
		LCD_write_command(1);
		LCD_write_string("Select mode: ");
		LCD_write_command(0xc0);
		LCD_write_string("0:Admin  1:Guest");
		
		uint8_t mode = get_input_from_user();
		
		LCD_write_command(1);
		if(mode == '0'){
			LCD_write_string("Admin Mode");
			LCD_write_command(0xc0);
			LCD_write_string("Enter pass: ");
			
		}
		else if(mode == '1'){
			LCD_write_string("Guest Mode");
			LCD_write_command(0xc0);
			LCD_write_string("Enter pass: ");
		}
		
		if(enter_password(mode) == 0){
			LCD_write_command(1);
			LCD_write_string("Correct pass");
			_delay_ms(200);
			if(mode == '0'){
				admin_control();
			}
			else{
				guest_control();
			}
		}
		else{
			LCD_write_command(1);
			LCD_write_string("Wrong pass");
			_delay_ms(500);
			// turn block led on
			SETBIT(PORTD, 2);  // PD2 high
			_delay_ms(2000);
			CLRBIT(PORTD, 2);
		}
	}
	
	
}

int main(void)
{
	// Initializations
	KEYPAD_init();
	LCD_init();
	SPI_init_master();
	
	LCD_write_string("Hi, Im master");
	_delay_ms(400);
	
	//set pins
	SETBIT(DDRD, 0);  // PD0 output
	SETBIT(DDRD, 1);  // PD1 output
	SETBIT(DDRD, 2);  // PD2 output
	
	
    xTaskCreate(lock_system, "T1", 80, NULL, 1, NULL);
    //xTaskCreate(led_button, "T2", 80, NULL, 1, NULL);
    vTaskStartScheduler(); // to start the scheduler
}

uint8_t get_password_from_user(){
	int8_t key;
	
	do{
		key = KEYPAD_read();
	}while(key == -1);
	
	LCD_write_char(key);
	_delay_ms(200);
	LCD_write_command(16);
	LCD_write_char('*');
	while(KEYPAD_read() != -1);
	
	return key;
}

uint8_t get_input_from_user(){
	int8_t key;
	
	do{
		key = KEYPAD_read();
	}while(key == -1);
	
	//LCD_write_char(key);
	
	while(KEYPAD_read() != -1);
	
	return key;
}

uint8_t enter_password(uint8_t mode){
	int password[4];
	int temp[4];
	// Loading the password
	if(mode == '0'){
		for(int i = 0; i < 4; i++){
			password[i] = eeprom_read(20+i);
		}
	}
	else{
		for(int i = 0; i < 4; i++){
			password[i] = eeprom_read(30+i);
		}
	}
	
	
	// enter password
	for(int i = 0; i < 4; i++){
		temp[i] = get_password_from_user();
	}

	//check
	for(int i = 0; i < 4; i++){
		if(temp[i] != password[i]){
			return 1;
		}
	}
	return 0;
}

void admin_control(){
	// turn admin led on
	SETBIT(PORTD, 0);  // PD0 high
	
	uint8_t menu = 0;
	uint8_t exit = 0;
	
	do{
		int input;
		
		LCD_write_command(1);
		if(menu == 0){
			LCD_write_string("1:Room1 2:Room2");
			LCD_write_command(0xc0);
			LCD_write_string("3:Room3 4:more");
			input = get_input_from_user();
			
			LCD_write_command(1);
			switch(input){
				case '1': LCD_write_string("Room 1 chosen"); SPI_write(1); _delay_ms(200); break;
				case '2': LCD_write_string("Room 2 chosen"); SPI_write(2); _delay_ms(200); break;
				case '3': LCD_write_string("Room 3 chosen"); SPI_write(3); _delay_ms(200); break;
				default: break;
			}
		}
		else{
			LCD_write_string("5:TV 6:AC");
			LCD_write_command(0xc0);
			LCD_write_string("7:back 8:Exit");
			input = get_input_from_user();
			
			LCD_write_command(1);
			switch(input){
				case '5': LCD_write_string("TV chosen"); SPI_write(5); _delay_ms(200); break;
				case '6': LCD_write_string("AC chosen"); SPI_write(6); _delay_ms(200); break;
				case '8': LCD_write_string("Exit"); exit = 1 ; _delay_ms(200); break;
				default: break;
			}
		}
		
		
		
		if((input == '4') || (input == '7')){
			if(menu == 0){
				menu = 1;
			}
			else{
				menu = 0;
			}
		}

	}while(exit != 1);
	
	// turn admin led off
	CLRBIT(PORTD, 0);  // PD0 low
}

void guest_control(){
	// turn guest led on
	SETBIT(PORTD, 1);  // PD1 high
	
	uint8_t exit = 0;
	
	do{
		int input;
		LCD_write_command(1);
		LCD_write_string("1:Room1 2:Room2");
		LCD_write_command(0xc0);
		LCD_write_string("3:Room3 4:Exit");
		input = get_input_from_user();
		
		LCD_write_command(1);
		switch(input){
			case '1': LCD_write_string("Room 1 chosen"); SPI_write(1); _delay_ms(200); break;
			case '2': LCD_write_string("Room 2 chosen"); SPI_write(2); _delay_ms(200); break;
			case '3': LCD_write_string("Room 3 chosen"); SPI_write(3); _delay_ms(200); break;
			case '4': LCD_write_string("Exit"); exit = 1 ; _delay_ms(200); break;
			default: break;
		}
		
	}while(exit != 1);
	
	// turn guest led off
	CLRBIT(PORTD, 1);  // PD1 low
	
}
