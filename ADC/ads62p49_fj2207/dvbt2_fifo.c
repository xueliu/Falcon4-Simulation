#include "dvbt2_fifo.h"

uint8 fifoBuffer[FIFO_DEPTH];
uint16 *fifoBuffer16;

void fifo_init(Fifo *h) {
	h->fifoIn = fifoBuffer;
	h->fifoOut = fifoBuffer;
	h->numElements = 0;
}

uint8 fifo_full(Fifo *h) {
	uint8 full;
	if (h->numElements < NUM_TOTAL_ELEMENTS) {
		full = 0;
	} else {
		full = 1;
	}
	return full;
}

void fifo_push(Fifo *h, uint8 data){
	fifoBuffer[h->numElements] = data;
	//h->fifoIn = h->fifoIn + DATA_SIZE;
	h->numElements = h->numElements + 1;
}

uint8 fifo_pop(Fifo *h){
	if ( fifo_full(h) == 1){	
		fifoBuffer16 = (uint16*)fifoBuffer;			
		memcpy(h->fifoBuffer,fifoBuffer16,NUM_TOTAL_ELEMENTS*DATA_SIZE);
		h->numElements = 0;		
		return 1;
	}else{
		return 0;
	}
}
