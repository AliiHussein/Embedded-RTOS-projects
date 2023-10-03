/*
 * SPI.h
 *
 * Created: 8/27/2022 11:29:30 AM
 *  Author: safifi
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "std_macros.h"


#define SS   PB4
#define MOSI PB5
#define MISO PB6
#define SCK  PB7

void SPI_init_master(void); // MOSI,SS, SCK output
void SPI_init_slave(void);  // MISO output

void SPI_write(uint8_t data);
uint8_t SPI_read(void);






#endif /* SPI_H_ */