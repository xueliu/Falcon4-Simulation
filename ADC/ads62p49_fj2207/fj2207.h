#ifndef FJ2207_H_
#define FJ2207_H_

#include <i2c.h>
#include <hal.h>
#include <string.h>

#define USE_ELOBARATE				0			/*<Program works in elaborate mode (added "work on the fields - not bytes" mode (;)).*/

#define BYTE_SIZE					8
#define FOUR_BITS_SIZE				4

#define FJ2207_CHIP_ADDRESS			0xC0		/*<Data line handle.*/

typedef enum{
	Fj2207Success 			= 0,
	Fj2207WriteForbiden		= 1,
	Fj2207FieldIsNoDefined	= 2,
	Fj2207FieldReadOnly		= 3
}Fj2207ReturnType;

typedef enum {
	Fj2207_IF_LEVEL_0_5V 	= 7,
	Fj2207_IF_LEVEL_0_6V 	= 6,
	Fj2207_IF_LEVEL_0_7V 	= 5,
	Fj2207_IF_LEVEL_0_85V 	= 4,
	Fj2207_IF_LEVEL_0_8V 	= 3,
	Fj2207_IF_LEVEL_0_1V 	= 2,
	Fj2207_IF_LEVEL_1_25V 	= 1,
	Fj2207_IF_LEVEL_2_0V 	= 0	
}Fj2207_IF_AGC_LEVEL;

typedef struct {
	I2CHandle	i2c_handle;			/*<I2c GPIO handle.*/
	/*<REGISTERS.*/
	uint8 ID_byte_1;				/*<Byte 0x00, Access: Read.*/
	uint8 ID_byte_2;				/*<Byte 0x01, Access: Read.*/
	uint8 ID_byte_3;				/*<Byte 0x02, Access: Read.*/
	uint8 Thermo_byte_1;			/*<Byte 0x03, Access: Read.*/
	uint8 Thermo_byte_2;			/*<Byte 0x04, Access: Write.*/
	uint8 Power_state_byte_1;		/*<Byte 0x05, Access: Read.*/
	uint8 Power_state_byte_2;		/*<Byte 0x06, Access: Read/Write.*/
	uint8 Input_Power_Level_byte;	/*<Byte 0x07, Access: Read.*/
	uint8 IF_Frequency_byte;		/*<Byte 0x15, Access: Read/Write.*/
	uint8 RF_Frequency_byte_1;		/*<Byte 0x16, Access: Read/Write.*/
	uint8 RF_Frequency_byte_2;		/*<Byte 0x17, Access: Read/Write.*/
	uint8 RF_Frequency_byte_3;		/*<Byte 0x18, Access: Read/Write.*/
	uint8 MSM_Byte_1;				/*<Byte 0x19, Access: Read/Write.*/
	uint8 MSM_Byte_2;				/*<Byte 0x1A, Access: Read/Write.*/
	uint8 AGCK_byte_1;				/*<Byte 0x0E, Access: Read/Write.*/
	uint8 IF_byte_1;				/*<Byte 0x13, Access: Read/Write.*/
	uint8 IF_AGC_byte;				/*<Byte 0x12, Access: Read/Write.*/
	uint8 Reference_byte;			/*<Byte 0x14, Access: Read/Write.*/
	uint8 Power_byte_2;				/*<Byte 0x14, Access: Read/Write.*/
	uint8 IR_MIXER_byte_2;			/*<Byte 0x23, Access: Read/Write.*/
	uint8 AGC1_byte_1;				/*<Byte 0x0C, Access: Read/Write.*/
	uint8 AGC1_byte_2;				/*<Byte 0x0D, Access: Read/Write.*/
	uint8 RF_AGC_byte_1;			/*<Byte 0x0F, Access: Read/Write.*/
	uint8 IR_MIXER_byte_1;			/*<Byte 0x10, Access: Read/Write.*/
	uint8 AGC5_byte_1;				/*<Byte 0x11, Access: Read/Write.*/
	uint8 PSM_byte_1;				/*<Byte 0x1B, Access: Read/Write.*/
	uint8 RF_AGC_Gain_byte_1;		/*<Byte 0x32, Access: Read.*/
	uint8 RF_AGC_Gain_byte_2; 		/*<Byte 0x33, Access: Read.*/
	uint8 IF_AGC_Gain_byte; 		/*<Byte 0x34, Access: Read.*/
	#ifdef USE_ELOBARATE
		uint16 Ident;				/*<Access: Read.*/
		uint8 Major_rev;			/*<Access: Read.*/
		uint8 Minor_rev;			/*<Access: Read.*/
		uint8 TM_D;					/*<Access: Read.*/
		uint8 TM_ON;				/*<Access: Write.*/
		uint8 POR;					/*<Access: Read.*/
		uint8 LO_Lock;				/*<Access: Read.*/
		uint8 SM_LNA;				/*<Access: Read/Write.*/
		uint8 SM_PLL;				/*<Access: Read/Write.*/
		uint8 SM;					/*<Access: Read/Write.*/
		uint8 Power_Level;			/*<Access: Read.*/
		uint8 IF_Freq;				/*<Access: Read/Write.*/
		uint32 RF_Freq;				/*<Access: Read/Write.*/
		uint8 POWER_Meas;			/*<Access: Read/Write.*/
		uint8 RF_CAL_AV;			/*<Access: Read/Write.*/
		uint8 RF_CAL;				/*<Access: Read/Write.*/
		uint8 IR_CAL;				/*<Access: Read/Write.*/
		uint8 RC_CAL;				/*<Access: Read/Write.*/
		uint8 Calc_PLL;				/*<Access: Read/Write.*/
		uint8 MSM_Launch;			/*<Access: Read/Write.*/
		uint8 AGCK_mode;			/*<Access: Read/Write.*/
		uint8 Pulse_Shaper_disable; /*<Access: Read/Write.*/
		uint8 IF_HP_Fc;				/*<Access: Read/Write.*/
		uint8 IF_Notch;				/*<Access: Read/Write.*/
		uint8 LP_FC_Offset;			/*<Access: Read/Write.*/
		uint8 LP_Fc;				/*<Access: Read/Write.*/
		uint8 IF_Level;				/*<Access: Read/Write.*/
		uint8 XTout;				/*<Access: Read/Write.*/
		uint8 Digital_Clock;		/*<Access: Read/Write.*/
		uint8 HI_Pass;				/*<Access: Read/Write.*/
		uint8 DC_NOTCH;				/*<Access: Read/Write.*/
		uint8 LT_Enable;			/*<Access: Read/Write.*/
		uint8 AGC1_6_15dB;			/*<Access: Read/Write.*/
		uint8 AGC1_TOP;				/*<Access: Read/Write.*/
		uint8 PD_RFAGC_Adapt;		/*<Access: Read/Write.*/
		uint8 RFAGC_Adapt_TOP;		/*<Access: Read/Write.*/
		uint8 RF_Atten_3dB;			/*<Access: Read/Write.*/
		uint8 AGC3_Top;				/*<Access: Read/Write.*/
		uint8 AGC4_Top;				/*<Access: Read/Write.*/
		uint8 AGC5_Top;				/*<Access: Read/Write.*/
		uint8 AGC5_HPF;				/*<Access: Read/Write.*/
		uint8 VHFIII;				/*<Access: Read/Write.*/
		uint8 RF_FILTER_GAIN;		/*<Access: Read.*/
		uint8 LNA_GAIN;				/*<Access: Read.*/
		uint8 TOP_Agc3_read;		/*<Access: Read.*/
		uint8 LPF_GAIN;				/*<Access: Read.*/
		uint8 IR_MIXER;				/*<Access: Read.*/
	#endif
} Fj2207Handle;

typedef enum {
	ID_byte_1				= 0x00,
	ID_byte_2				= 0x01,
	ID_byte_3				= 0x02,
	Thermo_byte_1			= 0x03,
	Thermo_byte_2			= 0x04,
	Power_state_byte_1		= 0x05,
	Power_state_byte_2		= 0x06,
	Input_Power_Level_byte	= 0x07,
	AGC1_byte_1				= 0x0C,
	AGC1_byte_2				= 0x0D,
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
	MSM_Byte_1				= 0x19,
	MSM_Byte_2				= 0x1A,
	PSM_byte_1				= 0x1B,	
	IR_MIXER_byte_2			= 0x23,
	Power_byte_2			= 0x36,
	RF_AGC_Gain_byte_1		= 0x32,
	RF_AGC_Gain_byte_2		= 0x33,
	IF_AGC_Gain_byte		= 0x34
	#ifdef USE_ELOBARATE
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


#ifdef USE_ELOBARATE
	Fj2207ReturnType fj2207_read_field(Fj2207Handle *fj2207Handle, Fj2207Ident field_id);
	Fj2207ReturnType fj2207_write_field(Fj2207Handle *fj2207Handle, Fj2207Ident field_id);
#endif

void fj2207_set(Fj2207Handle *h, uint32 r_frequency, uint32 i_frequency);
I2cResponseType fj2207_init(Fj2207Handle *h, GpioPin *i2c_sda,	GpioPin *i2c_scl);
I2cResponseType fj2207_write_byte_register(Fj2207Handle *h, uint8 reg, uint8 device_address, uint8 register_address);
I2cResponseType fj2207_get_byte_register(Fj2207Handle *h, uint8 *reg, uint8 device_address, uint8 register_address);
I2cResponseType fj2207_read_registers(Fj2207Handle *h);


#endif /*FJ2207_H_*/
