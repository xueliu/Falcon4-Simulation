#ifndef MAIN_H_
#define MAIN_H_

#define CLOCK_FREQUENCY	(7995400)
#define CLOCK_FREQUENCY_KHZ (7995)
#define WAIT_US(_t)	__delay_cycles(_t*CLOCK_FREQUENCY_KHZ/1000)
#define WAIT_MS(_t)	__delay_cycles(_t*CLOCK_FREQUENCY_KHZ)

typedef enum {
	fsm_adc_outputs_enabled,
	fsm_adc_outputs_disabled
} Fsm_state;

#endif /*MAIN_H_*/
