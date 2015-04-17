/*!
 *	$Id: lcd_16x2.h 284 2011-08-18 13:56:41Z podolski $
 *	$URL: https://versions1.kt.uni-due.de/svn/ktdsp/trunk/lcd_16x2.h $
 *	$Revision: 284 $
 *	$Date: 2011-08-18 15:56:41 +0200 (Do, 18 Aug 2011) $
 *	$Author: podolski $
 *	@author Lehrstuhl fuer Kommunikationstechnik, Universitaet Duisburg-Essen
 *	@file
 *	@brief LCD card driver.
 *
 *	This module allow to use a LCD 16x2 characters
 *
 */

#ifndef LCD_16X2_H_
#define LCD_16X2_H_

#include <gpio_pin.h>
#include <hal.h>


/**
 *  Commands
 */
#define LCD_16X2_COMMAND_CLEAR_DISPLAY		0x01	/**<Clear display command.*/
#define LCD_16X2_COMMAND_ENABLE_CURSOR		0x0F	/**<Enable cursor command.*/
#define LCD_16X2_COMMAND_DISABLE_CURSOR		0x0D	/**<Disable cursor command.*/
#define LCD_16x2_COMMAND_WORK_IN_4BIT		0x28	/**<Work in 4 bit command.*/
#define LCD_16x2_COMMAND_WORK_IN_8BIT		0x38	/**<Work in 8 bit command.*/
#define LCD_16x2_COMMAND_DISABLE_DISPLAY	0x08	/**<Disable display command.*/
#define LCD_16x2_COMMAND_ENABLE_DISPLAY		0x0C	/**<Enable display command.*/
#define LCD_16x2_COMMAND_SHIFT_TO_RIGHT		0x06	/**<During writing shift characters to the right.*/
#define LCD_16x2_COMMAND_SHIFT_TO_LEFT		0x07	/**<During writing shift characters to the left.*/

/**
 * LCD using mode
 */
typedef enum {
	Lcd4BitMode	= 0, /**<Lcd would work in 4 bit mode.*/
	Lcd8BitMode	= 1	 /**<Lcd would work in 8 bit mode.*/
} LcdMode;


/**
 * Unsigned integer writing mode
 */
typedef enum {
	LcdLeadingZerosOff	= 0, /**<Do not write zeros in empty places.*/
	LcdLeadingZerosOn	= 1	 /**<Do write zeros.*/
} LcdLeadingZeros;

/**
 * LCD handle structure
 */
typedef struct {
	GpioPin	*rs; 		/**<Register select.*/			
	GpioPin	*rw;		/**<Read/Write Option.*/			
	GpioPin	*enable;	/**<Enable pin.*/		
	GpioPin	*bit_0;		/**<Bit0 pin, in 4 bit option initialize with NULL.*/				
	GpioPin	*bit_1;		/**<Bit1 pin, in 4 bit option initialize with NULL.*/
	GpioPin	*bit_2;		/**<Bit2 pin, in 4 bit option initialize with NULL.*/
	GpioPin	*bit_3;		/**<Bit3 pin, in 4 bit option initialize with NULL.*/					
	GpioPin	*bit_4;		/**<Bit4 pin.*/				
	GpioPin	*bit_5;		/**<Bit5 pin.*/	
	GpioPin	*bit_6;		/**<Bit6 pin.*/	
	GpioPin	*bit_7;		/**<Bit7 pin.*/	
	LcdMode	mode;		/**<LCD using mode, using options defined in enum.*/
	uint8	kt_logo_defined;	/**<Definition of KT logo.*/
} LcdHandle;

/**
 * Initialization function.
 * 
 * Initialization funtions initialize GPIO pins and also LCD (execute the initialization sequence).
 * Exists possibility to choose the work mode (4 or 8 bit mode).
 * 
 * @param h			Pointer to the LCD handle structure.
 * @param rs		Pointer to the register select pin.
 * @param rw		Pointer to the read/write pin.
 * @param enable	Pointer to the enable pin.
 * @param bit_0		Pointer to the bit0 pin.
 * @param bit_1		Pointer to the bit1 pin.
 * @param bit_2		Pointer to the bit2 pin.
 * @param bit_3		Pointer to the bit3 pin.
 * @param bit_4		Pointer to the bit4 pin.
 * @param bit_5		Pointer to the bit5 pin.
 * @param bit_6		Pointer to the bit6 pin.
 * @param bit_7		Pointer to the bit7 pin.
 * @param mode		LCD work mode.
 */
void lcd_init(LcdHandle *h, GpioPin *rs, GpioPin *rw, GpioPin *enable, GpioPin *bit_0, GpioPin *bit_1, GpioPin *bit_2, GpioPin *bit_3, GpioPin *bit_4, GpioPin *bit_5, GpioPin *bit_6, GpioPin *bit_7, LcdMode mode);

/**
 * Write character on the LCD.
 * 
 * @param h					Pointer to the LCD handle structure.
 * @param cmd				Character (can be written in ascii code, or in ' ').
 */
void lcd_write_char(LcdHandle *h, uint8 cmd);

/**
 * Display string on the LCD.
 * 
 * @param h					Pointer to the LCD handle structure.
 * @param string			Pointer to the string to be written.
 * @param row_number		Start row position (y).
 * @param pos_number		Start position (x).
 */
void lcd_write_string(LcdHandle *h, char *string, uint8 row_number, uint8 pos_number);

/**
 * Write command to the LCD.
 * 
 * @param h					Pointer to the LCD handle structure.
 * @param cmd				Command (commands are defined). 
 */
void lcd_write_cmd(LcdHandle *h, uint8 cmd);

/**
 * Clear the line (horizontal).
 * 
 * @param h					Pointer to the LCD handle structure.
 * @param line_number		Number of the line to be cleared. 
 */
void lcd_clean_line(LcdHandle *h, uint8 line_number);

/**
 * Display Kommunikations Technik logo.
 * 
 * @param h					Pointer to the LCD handle structure.
 * @param x					Start position (only in the first line). 
 */
void lcd_write_kt_logo(LcdHandle *h, uint8 x);

/**
 * Display the unsigned number.
 * 
 * Functions display those numbers in two ways. You can fill the empty fields with zeros or no (leave the empty square). 
 * 
 * @param h						Pointer to the LCD handle structure.
 * @param number				Number to be written.
 * @param num_digits			Amount of using digits.
 * @param line_number			Define the starting position.
 * @param starting_position		Define the starting position.
 * @param leading_zeros			Choose the option of displaying. (fill in with zeros or no). 
 */
void lcd_write_unsigned_number(LcdHandle *h, uint32 number, uint8 num_digits, uint8 line_number, uint8 starting_position, LcdLeadingZeros leading_zeros);

#endif /*LCD_16X2_H_*/
