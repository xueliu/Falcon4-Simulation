/*!
 *	$Id: i2c.h 310 2011-09-22 15:15:10Z podolski $
 *	$URL: https://versions1.kt.uni-due.de/svn/ktdsp/trunk/i2c.h $
 *	$Revision: 310 $
 *	$Date: 2011-09-22 17:15:10 +0200 (Do, 22 Sep 2011) $
 *	$Author: podolski $
 *	@author Lehrstuhl fuer Kommunikationstechnik, Universitaet Duisburg-Essen
 *	@file
 *	@brief I2c module.
 *
 *	I2c servicing module.
 *
 */

/**
 * I2C toutorial.
 * http://www.robot-electronics.co.uk/acatalog/I2C_Tutorial.html
 */
 
#ifndef I2C_H_
#define I2C_H_

#include <gpio_pin.h>
#include <msp430_gpio.h>
#include <hal.h>

#define	I2C_SLAVE_ACK_RESPONSE		0x00		/*<ACK Response type.*/
#define	I2C_SLAVE_NACK_RESPONSE		0x01		/*<NACK Response type.*/
#define	I2C_SDA_BUSY				0xFF		/*<Slave device is busy.*/

/**
 * GPIO pin structure.
 */
typedef struct {
	GpioPin 	*i2c_sda;	/*<Data line handle.*/
	GpioPin 	*i2c_scl;	/*<Serial clock handle.*/
} I2CHandle;

/**
 * Enum defines ways of device access.
 */
typedef enum {
	I2CSlaveAccessModeWrite = 0,	/*<Write data to the slave device.*/
	I2CSlaveAccessModeRead  = 1		/*<Read data from the slave device.*/
} I2CSlaveAccessMode;

/**
 * Enum defines error types.
 */
typedef enum {
	I2c_Success				=	0,	/*<Success.*/
	I2c_Error				=	1,	/*<Operation failed.*/
	I2c_More_Data			=	2,	/*<Slave device require data form master (ACK response).*/ 
	I2c_NACK_Error			=	3,	/*<Master device get nACK response.*/
	I2c_Timeout_Init_Error	=	4	/*<Timeout initialization error.*/
}I2cResponseType;

/**
 * Initialization of I2C pins.
 * 
 * @param h				Pointer to the pins handle structure.
 * @param i2c_sda	Pointer to the SDA pin.
 * @param i2c_scl			Pointer to the clock pin.
 */
void i2c_init(I2CHandle	*h, GpioPin *i2c_sda, GpioPin *i2c_scl);

/**
 * I2C start sequence.
 * 
 * @param h				Pointer to the pins handle structure.
 */
void i2c_send_start_sequence(I2CHandle *h);

/**
 * I2C stop sequence.
 * 
 * @param h				Pointer to the pins handle structure.
 */
void i2c_send_stop_sequence(I2CHandle *h);

/**
 * I2C stop sequence.
 * 
 * @param h				Pointer to the pins handle structure.
 * @param value			Pointer to the variable where get value would be saved.
 */
void i2c_get_bit(I2CHandle	*h, uint8 *value);

/**
 * Get byte function.
 * 
 * @param h				Pointer to the pins handle structure.
 * @param value			Pointer to the variable where byte would be saved.
 */
void i2c_get_byte(I2CHandle *h, uint8 *data);

/**
 * Send byte to the I2C.
 * 
 * @param h				Pointer to the pins handle structure.
 * @param data			Data to be sent.
 */
I2cResponseType i2c_write_byte(I2CHandle *h, uint8 data);

/**
 * Send the acknowledge bit.
 * 
 * @param h					Pointer to the pins handle structure.
 * @param response			Acknowledge bit is send depends on the response which user have to put as this value.
 */
void i2c_write_acknowledge_bit(I2CHandle *h, uint8 response);

/**
 * Initialization to work the device in write/read mode (first sequence).
 * 
 * @param h							Pointer to the pins handle structure.
 * @param device_address			Device address.
 * @param mode						Read/Write access.
 */
I2cResponseType i2c_choose_device(I2CHandle *h, uint8 device_address, I2CSlaveAccessMode mode);

#endif /*I2C_H_*/
