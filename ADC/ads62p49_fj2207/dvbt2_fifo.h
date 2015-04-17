#ifndef DVBT2_FIFO_H_
#define DVBT2_FIFO_H_

#include <hal.h>

#define NUM_PARAMETERS	   4				//CFO ; SFO ; BER_lo ;BER_hi
#define NUM_TOTAL_ELEMENTS 2*NUM_PARAMETERS	//Each parameter consists of two 8-bits data, as the width of the SPI is 8-bit
#define DATA_SIZE 		   sizeof(char)
#define FIFO_DEPTH		   2*NUM_PARAMETERS


typedef struct {
	uint16 	fifoBuffer[FIFO_DEPTH];
	uint8 	*fifoIn;
	uint8	*fifoOut;
	uint16	numTotalElements;
	uint16	numElements;
} Fifo;

void 	fifo_init(Fifo *h) ;

uint8 	fifo_full(Fifo *h);

void	fifo_push(Fifo *h, uint8 data);

uint8 	fifo_pop(Fifo *h);

#endif /*DVBT2_FIFO_H_*/
