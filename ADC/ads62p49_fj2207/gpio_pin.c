/*!
 *	$Id: gpio_pin.c 234 2011-04-05 16:39:09Z kocks $
 *	$URL: https://versions1.kt.uni-due.de/svn/ktdsp/trunk/gpio_pin.c $
 *	$Revision: 234 $
 *	$Date: 2011-04-05 18:39:09 +0200 (Di, 05 Apr 2011) $
 *	$Author: kocks $
 *	@author Lehrstuhl fuer Kommunikationstechnik, Universitaet Duisburg-Essen
 *	@file
 *	@brief General module for controlling GPIO pins.
 *
 *	@sa gpio_pin.h
 *
 */

#include "gpio_pin.h"
#include "hal.h"

// initialize gpio pin
void gpio_pin_init	(GpioPin *p) {
	(*(p->init))(p->param);
}

// set the gpio_pin
void gpio_pin_set(GpioPin *p) {
	(*(p->set))(p->param);
}

// clear the gpio_pin
void gpio_pin_clear(GpioPin *p) {
	(*(p->clear))(p->param);
}

// read the value on the gpio_pin
uint8 gpio_pin_get(GpioPin *p) {
	return (*(p->get))(p->param);
}

// toggle the value of gpio_pin
void gpio_pin_toggle(GpioPin *p) {
	(*(p->toggle))(p->param);
}

// defing the gpio_pin as an output
void gpio_pin_configure_as_output(GpioPin *p) {
	(*(p->configure_as_output))(p->param);
}

// define the gpio_pin as an input
void gpio_pin_configure_as_input(GpioPin *p) {
	(*(p->configure_as_input))(p->param);
}

// set output to high z
void gpio_pin_set_highz(GpioPin *p) {
	(*(p->set_highz))(p->param);
}
