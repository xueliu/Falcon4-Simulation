/*!
 *	$Id: gpio_pin.h 241 2011-04-14 12:55:12Z kocks $
 *	$URL: https://versions1.kt.uni-due.de/svn/ktdsp/trunk/gpio_pin.h $
 *	$Revision: 241 $
 *	$Date: 2011-04-14 14:55:12 +0200 (Do, 14 Apr 2011) $
 *	$Author: kocks $
 *	@author Lehrstuhl fuer Kommunikationstechnik, Universitaet Duisburg-Essen
 *	@file
 *	@brief General module for controlling GPIO pins.
 *
 *	This module allows to control GPIO pins for arbitrary types of hardware.
 *
 */

#ifndef GPIO_PIN_H_
#define GPIO_PIN_H_

#include "hal.h"

/**
 *	This structure contains the function pointers to the various GPIO functions
 *	as well as the parameters depending on the underlying hardware type.
 */
typedef struct GpioPin 
{
	void	(*init)					(void* param);	/**< Pointer to the initialization function. */
	void 	(*set)					(void* param);	/**< Pointer to the set function. */
	void 	(*clear)				(void* param);	/**< Pointer to the clear function. */
	void 	(*toggle)				(void* param);	/**< Pointer to the toggle function. */
	uint8	(*get)					(void* param);	/**< Pointer to the get function. */
	void 	(*configure_as_input)	(void* param);	/**< Pointer to the configure-as-input function. */
	void 	(*configure_as_output)	(void* param);	/**< Pointer to the configure-as-output function. */
	void	(*set_highz)			(void* param);	/**< Pointer to the set-high-z function. */
	void 	*param;									/**< Pointer to the user-defined parameter structure. */
} GpioPin;

/**
 *	Initialization function for a GPIO pin.
 *	@param	p	Pointer to corresponding GpioPin structure.
 */
void	gpio_pin_init				(GpioPin *p);

/**
 *	Set the corresponding GPIO pin.
 *	@param	p	Pointer to corresponding GpioPin structure.
 */
void	gpio_pin_set				(GpioPin *p);

/**
 *	Clear the corresponding GPIO pin.
 *	@param	p	Pointer to corresponding GpioPin structure.
 */
void	gpio_pin_clear				(GpioPin *p);

/**
 *	Toggle the corresponding GPIO pin.
 *	@param	p	Pointer to corresponding GpioPin structure.
 */
void	gpio_pin_toggle				(GpioPin *p);

/**
 *	Read-out the corresponding GPIO pin.
 *	@param	p	Pointer to corresponding GpioPin structure.
 *	@return		Read-out value.
 */
uint8	gpio_pin_get				(GpioPin *p);

/**
 *	Configure the corresponding GPIO pin as input.
 *	@param	p	Pointer to corresponding GpioPin structure.
 */
void	gpio_pin_configure_as_input	(GpioPin *p);

/**
 *	Configure the corresponding GPIO pin as output.
 *	@param	p	Pointer to corresponding GpioPin structure.
 */
void	gpio_pin_configure_as_output(GpioPin *p);

/**
 *	Set the corresponding GPIO pin output to high impedance.
 *	@param	p	Pointer to corresponding GpioPin structure.
 */
void	gpio_pin_set_highz			(GpioPin *p);

#endif /*GPIO_PIN_H_*/
