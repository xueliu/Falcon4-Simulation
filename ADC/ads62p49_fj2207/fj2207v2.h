/*!
 *	$Id: fj2207v2.h 324 2011-12-22 11:24:00Z viessmann $
 *	$URL: https://versions1.kt.uni-due.de/svn/ktdsp/trunk/fj2207v2.h $
 *	$Revision: 324 $
 *	$Date: 2011-12-22 12:24:00 +0100 (Do, 22 Dez 2011) $
 *	$Author: viessmann $
 *	@author Lehrstuhl fuer Kommunikationstechnik, Universitaet Duisburg-Essen
 *	@file
 *	@brief FJ2207 module.
 *
 *	Module handle the FJ2207 tuner.
 *
 */

#ifndef FJ2207_H_
#define FJ2207_H_

#include <i2c.h>
#include <hal.h>
#include <bitbang.h>
#include <dac8830.h>

#define USE_ELABORATE				1			/*<Program works in elaborate mode (added "work on the fields - not byte registers").*/

#define BYTE_SIZE					8
#define FOUR_BITS_SIZE				4

#define FJ2207_CHIP_ADDRESS			0xC0		/*<Data line handle.*/

/**
* Enum describes an error / succes return values.
*/
typedef enum{
	Fj2207Success 			= 0,
	Fj2207FieldIsNoDefined	= 1,
	Fj2207FieldReadOnly		= 2
}Fj2207ReturnType;

/**
 * Structure handles all status controll registers.
 */
typedef struct {
	uint8 ID_byte_1;				/*<Byte 0x00, Access: Read.*/
	uint8 ID_byte_2;				/*<Byte 0x01, Access: Read.*/
	uint8 ID_byte_3;				/*<Byte 0x02, Access: Read.*/
	uint8 Thermo_byte_1;			/*<Byte 0x03, Access: Read.*/
	uint8 Thermo_byte_2;			/*<Byte 0x04, Access: Write.*/
	uint8 Power_state_byte_1;		/*<Byte 0x05, Access: Read.*/
	uint8 Power_state_byte_2;		/*<Byte 0x06, Access: Read/Write.*/
	uint8 IRQ_status;				/*<Byte 0x08, Access: Read/Write.*/	
	uint8 IRQ_enable;				/*<Byte 0x09, Access: Read/Write.*/
	uint8 IRQ_clear;				/*<Byte 0x0A, Access: Read/Write.*/
	uint8 IRQ_set;					/*<Byte 0x0B, Access: Read/Write.*/
	uint8 AGCK_byte_1;				/*<Byte 0x0E, Access: Read/Write.*/
	uint8 IF_byte_1;				/*<Byte 0x13, Access: Read/Write.*/
	uint8 Reference_byte;			/*<Byte 0x14, Access: Read/Write.*/
	uint8 MSM_byte_1;				/*<Byte 0x19, Access: Read/Write.*/
	uint8 MSM_byte_2;				/*<Byte 0x1A, Access: Read/Write.*/	
	uint8 PSM_byte_1;				/*<Byte 0x1B, Access: Read/Write.*/
	uint8 IR_MIXER_byte_2;			/*<Byte 0x23, Access: Read/Write.*/	
	uint8 Power_byte_2;				/*<Byte 0x36, Access: Read/Write.*/	
}	fj2207_status_control_registers;

/**
 * Structure handles PLL control registers.
 */
typedef struct {
	uint8 IF_Frequency_byte;		/*<Byte 0x15, Access: Read/Write.*/
	uint8 RF_Frequency_byte_1;		/*<Byte 0x16, Access: Read/Write.*/
	uint8 RF_Frequency_byte_2;		/*<Byte 0x17, Access: Read/Write.*/
	uint8 RF_Frequency_byte_3;		/*<Byte 0x18, Access: Read/Write.*/
} fj2207_pll_control_registers;

/**
 * Structure handles Power control registers.
 */
typedef struct {
	uint8 Input_Power_Level_byte;	/*<Byte 0x07, Access: Read.*/
	uint8 AGC1_byte_1;				/*<Byte 0x0C, Access: Read/Write.*/
	uint8 AGC2_byte_1;				/*<Byte 0x0D, Access: Read/Write.*/
	uint8 RF_AGC_byte_1;			/*<Byte 0x0F, Access: Read/Write.*/
	uint8 IR_MIXER_byte_1;			/*<Byte 0x10, Access: Read/Write.*/
	uint8 AGC5_byte_1;				/*<Byte 0x11, Access: Read/Write.*/
	uint8 IF_AGC_byte;				/*<Byte 0x12, Access: Read/Write.*/	
	uint8 RF_AGC_Gain_byte_1;		/*<Byte 0x32, Access: Read.*/
	uint8 RF_AGC_Gain_byte_2; 		/*<Byte 0x33, Access: Read.*/
	uint8 IF_AGC_Gain_byte; 		/*<Byte 0x34, Access: Read.*/
} fj2207_power_gain_control_registers;

#if USE_ELABORATE==1
/**
 * Structure handles status control fields.
 */
	typedef struct {
		uint16		Ident_temp;
		BitField 	Ident;
		BitField 	Major_rev;	
		BitField 	Minor_rev;
		BitField	TM_D;
		BitField	TM_ON;
		BitField	POR;
		BitField	LO_Lock;
		BitField	SM;
		BitField	SM_PLL;
		BitField	SM_LNA;
		BitField	Pulse_Shaper_disable;
		BitField	AGCK_mode;
		BitField	IF_HP_Fc;
		BitField	IF_Notch;
		BitField	LP_FC_Offset;
		BitField	LP_Fc;
		BitField	Digital_Clock;
		BitField	XTout;
		BitField	POWER_Meas;
		BitField	RF_CAL_AV;
		BitField	RF_CAL;
		BitField	IR_CAL;
		BitField	RC_CAL;
		BitField	Calc_PLL;
		BitField	MSM_Launch;
		BitField	VHFIII;
		BitField	HI_Pass;
		BitField	DC_NOTCH;
		BitField	Power_byte_2;	
	} fj2207_status_control_fields;
/**
 * Structure handles PLL control fields.
 */
	typedef struct {
		uint32		RF_Freq_temp;
		BitField	IF_Freq;
		BitField	RF_Freq;
	} fj2207_pll_control_fields;
/**
 * Structure handles Power control fields.
 */
	typedef struct {
		BitField	Power_Level;
		BitField	LT_Enable;
		BitField	AGC1_6_15dB;
		BitField	AGC1_TOP;
		BitField	AGC2_byte_1;
		BitField	PD_RFAGC_Adapt;
		BitField	RFAGC_Adapt_TOP;
		BitField	RF_Atten_3dB;
		BitField	AGC3_Top;
		BitField	AGC4_Top;
		BitField	AGC5_HPF;
		BitField	AGC5_Top;
		BitField	RF_FILTER_GAIN;
		BitField	LNA_GAIN;
		BitField	TOP_Agc3_read;
		BitField	LPF_GAIN;
		BitField	IR_MIXER;
		BitField	IF_Level;
	} fj2207_power_gain_control_fields;
	
#endif


/**
 * Structure handles all stuff connected with FJ2207.
 */
typedef struct {
	I2CHandle	i2c_handle;			/*<I2c GPIO handle.*/
	
	/*<REGISTERS.*/	
	fj2207_status_control_registers					status_control_registers;
	fj2207_pll_control_registers			 			pll_control_registers;
	fj2207_power_gain_control_registers			power_gain_control_registers;
	
	/*<Fields.*/
	#if USE_ELABORATE==1
		fj2207_status_control_fields					status_control_fields;
		fj2207_pll_control_fields							pll_control_fields;
		fj2207_power_gain_control_fields			power_gain_control_fields;
	#endif	
} Fj2207Handle;

/**
 * Enum contain addresses of the registers.
 */
typedef enum {
	ID_byte_1				= 0x00,
	ID_byte_2				= 0x01,
	ID_byte_3				= 0x02,
	Thermo_byte_1			= 0x03,
	Thermo_byte_2			= 0x04,
	Power_state_byte_1		= 0x05,
	Power_state_byte_2		= 0x06,
	Input_Power_Level_byte	= 0x07,
	IRQ_status				= 0x08,
	IRQ_enable				= 0x09,
	IRQ_clear				= 0x0A,
	IRQ_set					= 0x0B,
	AGC1_byte_1				= 0x0C,
	AGC2_byte_1				= 0x0D,
	AGCK_byte_1				= 0x0E,
	RF_AGC_byte_1			= 0x0F,
	IR_MIXER_byte_1			= 0x10,
	AGC5_byte_1				= 0x11,
	IF_AGC_byte				= 0x12,
	IF_byte_1				= 0x13,
	Reference_byte			= 0x14,	
	IF_Frequency_byte		= 0x15,
	RF_Frequency_byte_1		= 0x16,
	RF_Frequency_byte_2		= 0x17,
	RF_Frequency_byte_3		= 0x18,	
	MSM_byte_1				= 0x19,
	MSM_byte_2				= 0x1A,
	PSM_byte_1				= 0x1B,	
	IR_MIXER_byte_2			= 0x23,
	Power_byte_2			= 0x36,
	RF_AGC_Gain_byte_1		= 0x32,
	RF_AGC_Gain_byte_2		= 0x33,
	IF_AGC_Gain_byte		= 0x34
	#if USE_ELABORATE==1
		,	/* trailing comma of last line */
		Ident 					= 60,
		Major_rev 				= 61,
		Minor_rev				= 62,
		TM_D					= 63,
		TM_ON					= 64,
		POR						= 65,
		LO_Lock					= 66,
		SM_LNA					= 67,
		SM_PLL					= 68,
		SM						= 69,
		Power_Level				= 70,
		IF_Freq					= 71,
		RF_Freq					= 72,
		POWER_Meas				= 73,
		RF_CAL_AV				= 74,
		RF_CAL					= 75,
		IR_CAL					= 76,
		RC_CAL					= 77,
		Calc_PLL				= 78,
		MSM_Launch				= 79,
		AGCK_mode				= 80,
		Pulse_Shaper_disable	= 81,
		IF_HP_Fc				= 82,
		IF_Notch				= 83,
		LP_FC_Offset			= 84,
		LP_Fc					= 85,
		IF_Level				= 86,
		XTout					= 87,
		Digital_Clock			= 88,
		HI_Pass					= 89,
		DC_NOTCH				= 90,
		LT_Enable				= 91,
		AGC1_6_15dB				= 92,
		AGC1_TOP				= 93,
		PD_RFAGC_Adapt			= 94,
		RFAGC_Adapt_TOP			= 95,
		RF_Atten_3dB			= 96,
		AGC3_Top				= 97,
		AGC4_Top				= 98,
		AGC5_HPF				= 99,
		AGC5_Top				= 100,
		VHFIII					= 101,
		RF_FILTER_GAIN			= 102,
		LNA_GAIN				= 103,
		TOP_Agc3_read			= 104,
		LPF_GAIN				= 105,
		IR_MIXER				= 106
	#endif
} Fj2207Ident;

/**
 * Initialization of GPIO pins.
 *
 * Initialization to work with DAC8830 and FJ2207 over SPI and I2C protocol.
 * Function also initialize all of the registers.
 * 
 * @param h				Pointer to the I2C pins handle structure.
 * @param handle		Pointer to the SPI pins handle structure.
 * @param i2c_sda		Pointer to the I2C sda line.
 * @param i2c_scl		Pointer to the I2C clock line.
 * @param spi_clk		Pointer to the SPI clock line.
 * @param spi_simo		Pointer to the Slave input, master output line.
 * @param dac_cs		Pointer to the DAC8830 chip select line.
 */
Fj2207ReturnType fj2207_init(Fj2207Handle *h,  DAC_handle *handle, GpioPin *i2c_sda, GpioPin *i2c_scl, GpioPin *spi_sclk, GpioPin *spi_simo, GpioPin *dac_cs);

/**
 * Get the FJ2207 internal register.
 *
 * Functions reads 8bit register from internal memory of the device.
 * 
 * @param h						Pointer to the I2C pins handle structure.
 * @param reg					Pointer to the variable where the values of the registers would be saved.
 * @param device_address		Device address.	
 * @param register_address		Address of the internal register.
 */
Fj2207ReturnType fj2207_get_byte_register(Fj2207Handle *h, uint8 *reg, uint8 device_address, uint8 register_address);

/**
 * Write the FJ2207 internal register.
 *
 * Function overwrite the internal 8 bit registers.
 * 
 * @param h						Pointer to the I2C pins handle structure.
 * @param reg					Value to be written.
 * @param device_address		Device address.	
 * @param register_address		Address of the internal register.
 */
I2cResponseType fj2207_write_byte_register(Fj2207Handle *h, uint8 reg, uint8 device_address, uint8 register_address);

/**
 * Configuration of the FJ2207.
 *
 * Functions sets work parameters of the tuner. User can easily modifiy those parameters. 
 * Meanings of the values you can find in FJ2207 datasheet. Different code is executed in the case of using ELABORATE_MODE or no.
 * 
 * @param h						Pointer to the I2C pins handle structure.
 * @param rf_frequency			Radio frequency (carrier frequency).
 * @param if_frequency			Intermediate frequency (downconvertion frequency).	
 */
Fj2207ReturnType fj2207_set(Fj2207Handle *h, uint32 rf_frequency, uint32 if_frequency);

#if USE_ELABORATE==1
/**
 * Set the field.
 *
 * Function sets value of the field (fields are described in datasheet).
 * 
 * @param h						Pointer to the I2C pins handle structure.
 * @param field_id				Name of the field (described in datasheet).
 * @param value					Value to be written.	
 */
	Fj2207ReturnType fj2207_write_field(Fj2207Handle *h, Fj2207Ident field_id, uint32 value);
/**
 * Set the field.
 *
 * Function sets value of the field (fields are described in datasheet).
 * 
 * @param h						Pointer to the I2C pins handle structure.
 * @param field_id				Name of the field (described in datasheet).
 * @param value					Value to be written.	
 */
	Fj2207ReturnType fj2207_read_field(Fj2207Handle *h, Fj2207Ident field_id, uint32 *value);
#endif

#endif /*FJ2207_H_*/
