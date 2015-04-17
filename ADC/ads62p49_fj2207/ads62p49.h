#ifndef ADS62P49_H_
#define ADS62P49_H_

#include "hal.h"
#include "gpio_pin.h"
#include "bitbang.h"

#ifndef SPI_DEFAULT_WAIT_COUNTER_MAX
	#define SPI_DEFAULT_WAIT_COUNTER_MAX (20)
#endif


#ifndef NULL
#define NULL (0)
#endif

#define uint16_t 	unsigned short
#define uint8_t 	unsigned char
#define uint32_t 	unsigned int
#define uint32_l 	unsigned long int

/*!
 * @brief A helper function to convert a bitfield struct of 1 byte to an uint8_t pointer
 */
 /*
#define ToUint8Ptr(regName) 	((uint8_t*)	&regName)
#define ToUint32Ptr(regName) 	((uint32_t*)&regName)
#define ToUint32lPtr(regName) 	((uint32_l*)&regName)
*/
typedef struct {
	uint8	reg_00;
	uint8	reg_20;
	uint8	reg_3F;
	uint8	reg_40;
	uint8	reg_41;
	uint8	reg_44;
	uint8	reg_50;
	uint8	reg_51;
	uint8	reg_52;
	uint8	reg_53;
	uint8	reg_55;
	uint8	reg_57;
	uint8	reg_62;
	uint8	reg_63;
	uint8	reg_66;
	uint8	reg_68;
	uint8	reg_6A;
	uint8	reg_75;
	uint8	reg_76;
		
	// Spi pins
	GpioPin 	*miso;
	GpioPin 	*mosi;
	GpioPin 	*sclk;
	GpioPin 	*ce;
	GpioPin 	*reset;
	
	GpioPin 	*sw_0;	
	GpioPin 	*sw_1;	
	GpioPin 	*sw_2;	
	GpioPin 	*sw_3;	
}	ADS62P49_Device;

typedef enum ADS62P49Return {
	ADS62P49_OK 		= 0,
	ADS62P49_ERROR 	= 1
} ADS62P49Return;

typedef enum {
	ADS62P49_CHANNEL_A	= 0,
	ADS62P49_CHANNEL_B	= 1
} ADS62P49_CHSEL;

/*
typedef enum ADS62P49_RegAddr {
	REG_00	= 0x00,
	REG_20	= 0x20,
	REG_3F	= 0x3F,
	REG_40	= 0x40,
	REG_41	= 0x41,
	REG_44	= 0x44,
	REG_50	= 0x50,
	REG_51	= 0x51,
	REG_52	= 0x52,
	REG_53	= 0x53,
	REG_55	= 0x55,
	REG_57	= 0x57,
	REG_62	= 0x62,
	REG_63	= 0x63,
	REG_66	= 0x66,
	REG_68	= 0x68,	
	REG_6A	= 0x6A,
	REG_75	= 0x75,
	REG_76	= 0x76
}ADS62P49_RegAddr;
*/

typedef struct Reg_00 {
	uint8_t
		SERIAL_READOUT		: 1,
		D1_D6				: 6,
		RESET				: 1;
}Reg_00;

typedef struct Reg_20 {
	uint8_t
		D0_D1				: 2,
		EN_LOW_SPEED_MODE	: 1,
		D3_D7				: 5;
}Reg_20;

typedef struct Reg_3F {
	uint8_t
		D0					: 1,
		STANDBY				: 1,
		D2_D5				: 4,
		REF					: 1,
		D7					: 1;
}Reg_3F;	
	
typedef struct Reg_40 {	
	uint8_t	
		POWER_DOWN_MODES	: 4,
		D4_D7				: 4;
}Reg_40;	
	
	
typedef struct Reg_41 {	
	uint8_t	
		D0_D6				: 7,
		LVDS_CMOS			: 1;
}Reg_41;	
	
typedef struct Reg_44 {	
	uint8_t	
		D0_D1					: 2,
		CLKOUT_EDGE_CTL_D2_D4	: 3,
		CLKOUT_EDGE_CTL_D5_D7	: 3;
}Reg_44;	
	
typedef struct Reg_50 {	
	uint8_t	
		D0					: 1,
		DATA_FORMAT			: 2,
		D3_D5				: 3,
		EN_IND_CHANNEL_CTL	: 1,
		D7					: 1;
}Reg_50;	
	
typedef struct Reg_51 {	
	uint8_t	
		CUSTOM_PATTERN_LOW	: 8;
}Reg_51;	
	
typedef struct Reg_52 {	
	uint8_t	
		CUSTOM_PATTERN_HIGH	: 6,
		D6_D7				: 2;
}Reg_52;	
	
typedef struct Reg_53 {	
	uint8_t	
		D0_D5				: 6,
		EN_OFFSET_CORR_CHA	: 1,
		D7					: 1;
}Reg_53;	

typedef struct Reg_55 {
	uint8_t
		OFFSET_CORR_TIME_CONST_CHA	: 4,
		GAIN_PROGRAM_CHA			: 4;
}Reg_55;

typedef struct Reg_57 {
	uint8_t
		FINE_GAIN_ADJUST_CHA		: 7,
		D7							: 1;
}Reg_57;

typedef struct Reg_62 {
	uint8_t
		TEST_PATTERN_CHA	: 3,
		D3_D7				: 5;
}Reg_62;

typedef struct Reg_63 {
	uint8_t
		OFFSET_PEDESTAL_CHA	: 6,
		D6_D7				: 2;
}Reg_63;

typedef struct Reg_66 {
	uint8_t
		D0_D5				: 6,
		EN_OFFSET_CORR_CHB	: 1,
		D7					: 1;
}Reg_66;

typedef struct Reg_68 {
	uint8_t
		OFFSET_CORR_TIME_CONST_CHB	: 4,
		GAIN_PROGRAM_CHB			: 4;
}Reg_68;

typedef struct Reg_6A {
	uint8_t
		FINE_GAIN_ADJUST_CHB	: 7,
		D7						: 1;
}Reg_6A;

typedef struct Reg_75 {
	uint8_t
		TEST_PATTERN_CHB	: 3,
		D3_D7				: 5;
}Reg_75;

typedef struct Reg_76 {
	uint8_t
		OFFSET_PEDESTAL_CHB	: 6,
		D6_D7				: 2;
}Reg_76;
// -----------------------------------------------------------------

typedef	enum SDOUT {
	SDOUT_Disable 		= 0,
	SDOUT_Enable 		= 1
}SDOUT;

typedef	enum LowSpeedMode {
	LowSpeedMode_Disable	= 0,
	LowSpeedMode_Enable		= 1
}LowSpeedMode;

typedef	enum RefSel {
	RefSel_Internal		= 1,
	RefSel_External		= 3
}RefSel;

typedef	enum Standby {
	Standby_Disable		= 0,
	Standby_Enable		= 1
}Standby;

typedef	enum PowerDownMode {
	PowerDownMode_CTL_Pins			= 0,
	PowerDownMode_Normal			= 8,
	PowerDownMode_OutBuffDis_ChB	= 9,
	PowerDownMode_OutBuffDis_ChA	= 10,
	PowerDownMode_OutBuffDis_ChAB	= 11,
	PowerDownMode_GlobalPowerDown	= 12,
	PowerDownMode_ChB_Standby		= 13,
	PowerDownMode_ChA_Standby		= 14,
	PowerDownMode_MUX_Mode			= 15
}PowerDownMode;

typedef	enum InterfaceMode {
	InterfaceMode_CMOS		= 0,
	InterfaceMode_LVDS		= 1
}InterfaceMode;

typedef	enum CLKOUT_RisingEdgeShift {
	CLKOUT_RisingEdgeShift_Default_000	= 0,
	CLKOUT_RisingEdgeShift_Default_100	= 4,
	CLKOUT_RisingEdgeShift_4_26Ts_P		= 5,
	CLKOUT_RisingEdgeShift_6_26Ts_N		= 6,
	CLKOUT_RisingEdgeShift_4_26Ts_N		= 7
}CLKOUT_RisingEdgeShift;

typedef	enum CLKOUT_FallingEdgeShift {
	CLKOUT_FallingEdgeShift_Default_000	= 0,
	CLKOUT_FallingEdgeShift_Default_100	= 4,
	CLKOUT_FallingEdgeShift_4_26Ts_P	= 5,
	CLKOUT_FallingEdgeShift_6_26Ts_N	= 6,
	CLKOUT_FallingEdgeShift_4_26Ts_N	= 7
}CLKOUT_FallingEdgeShift;

typedef	enum ChannelCtl {
	ChannelCtl_Common		= 0,
	ChannelCtl_Independent	= 1
}ChannelCtl;

typedef	enum DataFormat {
	DataFormat_Complement	= 2,
	DataFormat_OffsetBinary	= 3
}DataFormat;

typedef	enum OffsetCorrection {
	OffsetCorrection_Disable	= 0,
	OffsetCorrection_Enable		= 1
}OffsetCorrection;

typedef	enum Gain {
	Gain_0dB			= 0,
	Gain_0_5dB			= 1,
	Gain_1dB			= 2,
	Gain_1_5dB			= 3,
	Gain_2dB			= 4,
	Gain_2_5dB			= 5,
	Gain_3dB			= 6,
	Gain_3_5dB			= 7,
	Gain_4dB			= 8,
	Gain_4_5dB			= 9,
	Gain_5dB			= 10,
	Gain_5_5dB			= 11,
	Gain_6dB			= 12
}Gain;

typedef	enum OffsetCorrectionTime {
	OffsetCorrectionTime_256K	= 0,
	OffsetCorrectionTime_512K	= 1,
	OffsetCorrectionTime_1M		= 2,
	OffsetCorrectionTime_2M		= 3,
	OffsetCorrectionTime_4M		= 4,
	OffsetCorrectionTime_8M		= 5,
	OffsetCorrectionTime_16M	= 6,
	OffsetCorrectionTime_32M	= 7,
	OffsetCorrectionTime_64M	= 8,
	OffsetCorrectionTime_128M	= 9,
	OffsetCorrectionTime_256M	= 10,
	OffsetCorrectionTime_512M	= 11
}OffsetCorrectionTime;

typedef	enum TestPattern {
	TestPattern_Normal		= 0,
	TestPattern_All_Zeros	= 1,
	TestPattern_All_Ones	= 2,
	TestPattern_Toggle		= 3,
	TestPattern_Ramp		= 4,
	TestPattern_Custom		= 5
}TestPattern;

typedef	enum OffsetPedestal {
	OffsetPedestal_31_LSB_P		= 31,
	OffsetPedestal_30_LSB_P		= 30,
	OffsetPedestal_29_LSB_P		= 29,
	OffsetPedestal_28_LSB_P		= 28,
	OffsetPedestal_27_LSB_P		= 27,
	OffsetPedestal_26_LSB_P		= 26,
	OffsetPedestal_25_LSB_P		= 25,
	OffsetPedestal_24_LSB_P		= 24,
	OffsetPedestal_23_LSB_P		= 23,
	OffsetPedestal_22_LSB_P		= 22,
	OffsetPedestal_21_LSB_P		= 21,
	OffsetPedestal_20_LSB_P		= 20,
	OffsetPedestal_19_LSB_P		= 19,
	OffsetPedestal_18_LSB_P		= 18,
	OffsetPedestal_17_LSB_P		= 17,
	OffsetPedestal_16_LSB_P		= 16,
	OffsetPedestal_15_LSB_P		= 15,
	OffsetPedestal_14_LSB_P		= 14,
	OffsetPedestal_13_LSB_P		= 13,
	OffsetPedestal_12_LSB_P		= 12,
	OffsetPedestal_11_LSB_P		= 11,
	OffsetPedestal_10_LSB_P		= 10,
	OffsetPedestal_9_LSB_P		= 9,
	OffsetPedestal_8_LSB_P		= 8,
	OffsetPedestal_7_LSB_P		= 7,
	OffsetPedestal_6_LSB_P		= 6,
	OffsetPedestal_5_LSB_P		= 5,
	OffsetPedestal_4_LSB_P		= 4,
	OffsetPedestal_3_LSB_P		= 3,
	OffsetPedestal_2_LSB_P		= 2,
	OffsetPedestal_1_LSB_P		= 1,
	OffsetPedestal_0_LSB_P		= 0,
	OffsetPedestal_1_LSB_N		= 63,
	OffsetPedestal_2_LSB_N		= 62,
	OffsetPedestal_3_LSB_N		= 61,
	OffsetPedestal_4_LSB_N		= 60,
	OffsetPedestal_5_LSB_N		= 59,
	OffsetPedestal_6_LSB_N		= 58,
	OffsetPedestal_7_LSB_N		= 57,
	OffsetPedestal_8_LSB_N		= 56,
	OffsetPedestal_9_LSB_N		= 55,
	OffsetPedestal_10_LSB_N		= 54,
	OffsetPedestal_11_LSB_N		= 53,
	OffsetPedestal_12_LSB_N		= 52,
	OffsetPedestal_13_LSB_N		= 51,
	OffsetPedestal_14_LSB_N		= 50,
	OffsetPedestal_15_LSB_N		= 49,
	OffsetPedestal_16_LSB_N		= 48,
	OffsetPedestal_17_LSB_N		= 47,
	OffsetPedestal_18_LSB_N		= 46,
	OffsetPedestal_19_LSB_N		= 45,
	OffsetPedestal_20_LSB_N		= 44,
	OffsetPedestal_21_LSB_N		= 43,
	OffsetPedestal_22_LSB_N		= 42,
	OffsetPedestal_23_LSB_N		= 41,
	OffsetPedestal_24_LSB_N		= 40,
	OffsetPedestal_25_LSB_N		= 39,
	OffsetPedestal_26_LSB_N		= 38,
	OffsetPedestal_27_LSB_N		= 37,
	OffsetPedestal_28_LSB_N		= 36,
	OffsetPedestal_29_LSB_N		= 35,
	OffsetPedestal_30_LSB_N		= 34,
	OffsetPedestal_31_LSB_N		= 33,
	OffsetPedestal_32_LSB_N		= 32
}OffsetPedestal;

typedef enum ADS_Channel {
	CH_A	= 1,
	CH_B	= 0
}ADS_Channel;
    

void ads62p49_delay_function				(void);

void ads62p49_init				(ADS62P49_Device 	*dev, 	GpioPin *spi_sclk, 	GpioPin *spi_mosi, 	GpioPin *spi_miso, GpioPin *spi_chip_enable, GpioPin *ads_reset);
void ads62p49_spi_read 			(ADS62P49_Device 	*dev, 	const 	uint16 	regBaseAddr, 		uint8 *data);
void ads62p49_spi_write			(ADS62P49_Device 	*dev, 	const 	uint16 	regBaseAddr, 		const uint8 data);
void ads62p49_spi_chip_enable	(ADS62P49_Device 	*dev, uint8 value);

// void ads62p49_Spi_Init		(SpiDevice dev, 	PortPin 	spi_sclk,	PortPin 		spi_mosi,	PortPin 	spi_miso,	PortPin 	spi_ads_chip_enable);  



void ads62p49_regInitRead 		(ADS62P49_Device 	*ads_number);
void ads_reset_reg_init			(ADS62P49_Device 	*ads_number);
void ads62p49_set_serial_readout			(ADS62P49_Device 	*ads_number, 	SDOUT 			sdout);
void ads62p49_set_low_speed_mode			(ADS62P49_Device 	*ads_number, 	LowSpeedMode 	low_speed_mode);
void ads62p49_set_ref_sel				(ADS62P49_Device 	*ads_number, 	RefSel 			reference_sel);
void ads62p49_set_standby				(ADS62P49_Device 	*ads_number, 	Standby			standby);
void ads62p49_set_power_down_mode		(ADS62P49_Device 	*ads_number, 	PowerDownMode 	power_down_mode);
void ads62p49_set_lvds_cmos				(ADS62P49_Device 	*ads_number,	InterfaceMode	lvds_cmos);
void ads62p49_set_channel_ctl			(ADS62P49_Device 	*ads_number,	ChannelCtl		channel_control);
void ads62p49_set_data_format			(ADS62P49_Device 	*ads_number,	DataFormat		data_format);
//void set_custom_pattern_low		(ADS62P49_Device 	*ads_number,	uint8			custom_pattern_low_data);
//void set_custom_pattern_high	(ADS62P49_Device 	*ads_number,	uint8			custom_pattern_high_data);
ADS62P49Return ads62p49_set_custom_pattern	(ADS62P49_Device 	*ads_number,	uint16			custom_pattern_data);
void ads62p49_set_offset_correction		(ADS62P49_Device 	*ads_number,	ADS_Channel		ads_channel,	OffsetCorrection		offset_correction);
void ads62p49_set_gain					(ADS62P49_Device 	*ads_number,	ADS_Channel		ads_channel,	Gain					gain);
void ads62p49_set_offset_corr_time		(ADS62P49_Device 	*ads_number,	ADS_Channel		ads_channel,	OffsetCorrectionTime	offset_correction_time);
void ads62p49_set_fine_gain_adjust		(ADS62P49_Device 	*ads_number,	ADS_Channel		ads_channel,	int						fine_gain_adjust);
void ads62p49_set_test_mode(ADS62P49_Device *ads_number, ADS62P49_CHSEL channel, TestPattern test_pattern);
void ads62p49_set_offset_pedestal		(ADS62P49_Device 	*ads_number,	ADS_Channel		ads_channel,	OffsetPedestal			offset_pedestal);
//void set_clk_rising_edge_ctl	(ADS62P49_Device 	*ads_number,	InterfaceMode	lvds_cmos,		CLKOUT_RisingEdgeShift	clkout_rising_edge_shift);
void ads62p49_set_clk_edge_ctl			(ADS62P49_Device 	*ads_number,	CLKOUT_RisingEdgeShift	clkout_rising_edge_shift, CLKOUT_FallingEdgeShift clkout_falling_edge_shift);
//void set_clk_falling_edge_ctl	(ADS62P49_Device 	*ads_number,	CLKOUT_FallingEdgeShift clkout_falling_edge_shift);
//void set_clk_falling_edge_ctl	(ADS62P49_Device 	*ads_number,	CLKOUT_FallingEdgeShift clkout_falling_edge_shift);

//void ads_reset				(SpiDevice 		spi_ads, 		ADS62P49_Device		*ads_number);
//void ads_reset				(PortPin		*ads_reset_pin);
//	void ads_write_direct			(SpiDevice 		spi_ads, 		ADS62P49_Device		*ads_number, ADS62P49_RegAddr 	regBaseAddr, 	const uint8 data);
void ads_write_direct			(ADS62P49_Device		*ads_number, uint8 	regBaseAddr, 	const uint8 data);
void ads_write					(ADS62P49_Device		*ads_number);
//	void ads_write					(SpiDevice		spi_ads, 		ADS62P49_Device		*ads_number);
//void RunADS 					(SpiDevice 		spi_ads, 		ADS62P49_Device 	*ads_number, int reg_num);

void ads62p49_set_channel_control(ADS62P49_Device *dev, ChannelCtl channel_control, DataFormat data_format);
//void ads62p49_set_gain_offset_time (ADS62P49_Device *ads_number, ADS_Channel	ads_channel, Gain gain, OffsetCorrectionTime offset_correction_time);


#endif /*ADS62P49_H_*/
