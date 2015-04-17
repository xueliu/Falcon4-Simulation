#ifndef _MSP430_GPIO_H_
#define _MSP430_GPIO_H_

#include <hal.h>

typedef enum {
	Msp430GpioInput = 0,
	Msp430GpioOutput = 1
} Msp430GpioDirection;

typedef struct {
	uint16				*pxout;
	uint16				*pxin;
	uint16				*pxdir;
	uint16				bitmask;
	Msp430GpioDirection	direction;
} Msp430GpioParamStruct;

void msp430_gpio_init(void* param);
void msp430_gpio_set(void* param);
void msp430_gpio_clear(void* param);
void msp430_gpio_toggle(void* param);
uint8 msp430_gpio_get(void* param);
void msp430_gpio_configure_as_input(void* param);
void msp430_gpio_configure_as_output(void* param);
void msp430_gpio_set_highz(void* param);

#endif /*_MSP430_GPIO_H_*/
