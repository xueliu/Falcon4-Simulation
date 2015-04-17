#include <msp430_gpio.h>

void msp430_gpio_init(void* param) {
	if (((Msp430GpioParamStruct*)param)->direction == Msp430GpioOutput) {
		msp430_gpio_configure_as_output(param);
	} else {
		msp430_gpio_configure_as_input(param);
	}	
}

void msp430_gpio_set(void* param) {
	*(((Msp430GpioParamStruct*)param)->pxout) |= ((Msp430GpioParamStruct*)param)->bitmask;	
}

void msp430_gpio_clear(void* param) {
	*(((Msp430GpioParamStruct*)param)->pxout) &= ~(((Msp430GpioParamStruct*)param)->bitmask);
}

void msp430_gpio_toggle(void* param) {
	*(((Msp430GpioParamStruct*)param)->pxout) ^= ((Msp430GpioParamStruct*)param)->bitmask;
}

uint8 msp430_gpio_get(void* param) {
	uint8 temp;
	temp = (*(((Msp430GpioParamStruct*)param)->pxin) & ((Msp430GpioParamStruct*)param)->bitmask) != 0;
	return temp;
}

void msp430_gpio_configure_as_input(void* param) {
	*(((Msp430GpioParamStruct*)param)->pxdir) &= ~(((Msp430GpioParamStruct*)param)->bitmask);
}

void msp430_gpio_configure_as_output(void* param) {
	*(((Msp430GpioParamStruct*)param)->pxdir) |= ((Msp430GpioParamStruct*)param)->bitmask;
}

void msp430_gpio_set_highz(void* param) {
	msp430_gpio_configure_as_input(param);
}
