/*
 * AD5752.cpp
 *
 *  Created on: 22 Aug 2017
 *      Author: Lukas Martisiunas
 *      Description: Basic library to initialise and use AD5752 with Arduino
 */

#include "AD5752.h"
#include "Arduino.h"
#include "SPI.h"

char DAC_CS_pin = slave_pin_DAC;

void init_DAC(char sel_DAC, char range){

	char temp_set_DAC;

  SPI.begin(); // initialize SPI, covering MOSI,MISO,SCK signals
  SPI.setBitOrder(MSBFIRST);  // data is clocked in MSB first
  SPI.setDataMode(SPI_MODE0);  // SCLK idle low (CPOL=0), MOSI read on rising edge (CPHI=0)
  SPI.setClockDivider(SPI_CLOCK_DIV32);  // system clock = 16 MHz, chip max = 1 MHz
  pinMode (DAC_CS_pin, OUTPUT);
  digitalWrite(DAC_CS_pin, HIGH); // chip select is active low
  delay(10);

  switch (sel_DAC) {
	case DAC_A:
		temp_set_DAC = 1;
		break;
	case DAC_B:
		temp_set_DAC = 4;
		break;
	case DAC_AB:
		temp_set_DAC = 5;
		break;
	default:
		temp_set_DAC = 5;
		break;
}
  for (int var = 0; var < 2; ++var) {
	  digitalWrite(DAC_CS_pin, LOW); // chip select is active low
	  SPI.transfer(0x10);
	  SPI.transfer(0x00);
	  SPI.transfer(temp_set_DAC);
	  delay(10);
	  digitalWrite(DAC_CS_pin, HIGH);
	  delay(10);
  }

  digitalWrite(DAC_CS_pin, LOW); // chip select is active low
  SPI.transfer(0x0C);
  SPI.transfer(0x00);
  SPI.transfer(range);
  delay(10);
  digitalWrite(DAC_CS_pin, HIGH);
  delay(10);
}

void set_DAC_value(unsigned int DAC_value, char DAC)
{
  digitalWrite(DAC_CS_pin, LOW);
  delay(1);
  SPI.transfer(DAC);
  SPI.transfer((DAC_value & 0xFF00) >> 8);
  SPI.transfer(DAC_value & 0x00FF);
  delay(1);
  digitalWrite(DAC_CS_pin, HIGH);
  delay(1);

  digitalWrite(DAC_CS_pin, LOW);
  delay(1);
  SPI.transfer(0x1D);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  delay(1);
  digitalWrite(DAC_CS_pin, HIGH);
  delay(1);
}
