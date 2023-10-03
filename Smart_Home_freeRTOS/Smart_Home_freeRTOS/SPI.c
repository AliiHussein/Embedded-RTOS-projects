/*
 * SPI.c
 *
 * Created: 9/4/2023 11:29:13 AM
 *  Author: Ali
 */ 

#include "SPI.h"

void SPI_init_master(void){
	SETBIT(DDRB,MOSI);
	SETBIT(DDRB,SS); // slave select 1
	SETBIT(DDRB, PB3); // slave select 2
	SETBIT(DDRB,SCK);
	
	SPCR = 1<<MSTR | 1<<SPE;
}
void SPI_init_slave(void){
	SETBIT(DDRB,MISO);
	SPCR =  1<<SPE;
}

void SPI_write(uint8_t data){
	SPDR = data;
	while(READBIT(SPSR,SPIF) == 0);
}
uint8_t SPI_read(void){
	while(READBIT(SPSR,SPIF) == 0);
	return SPDR;		
}

uint8_t SPI_RX_TX(uint8_t data){
	SPDR = data;
	while(READBIT(SPSR,SPIF) == 0);
	return SPDR;	
}

