#ifndef PLL_H_
#define PLL_H_

//#include "cdce62005_registers.h"
#include <hal.h>
#include <gpio_pin.h>
#include <bitbang.h>


#ifndef SPI_DEFAULT_WAIT_COUNTER_MAX
	#define SPI_DEFAULT_WAIT_COUNTER_MAX (20)
#endif

#ifndef NULL
	#define NULL (0)
#endif

typedef struct {
	uint32		reg0;
	uint32		reg1;
	uint32 		reg2;
	uint32		reg3;
	uint32		reg4;
	uint32 		reg5;
	uint32 		reg6;
	uint32 		reg7;
	uint32 		reg8;

#ifndef BITBANG_MACRO_IMPLEMENTATION
	// bit field in register 0
	BitField	REG0_ADDR;
	BitField	REG0_DIV2PRI;
	BitField	REG0_RESERVED;
	BitField	REG0_OUTMUX0SEL;
	BitField	REG0_PH0ADJC;
	BitField	REG0_OUT0DIVRSEL;
	BitField	REG0_OUT0DIVSEL;
	BitField	REG0_HISWINGLVPECL0;
	BitField	REG0_CMOSMODE0P;
	BitField	REG0_CMOSMODE0N;
	BitField	REG0_OUTBUFSEL0;
	
	// bit field in register 1
	BitField	REG1_ADDR;
	BitField	REG1_DIV2SEC;
	BitField	REG1_RESERVED;
	BitField	REG1_OUTMUX1SEL;
	BitField	REG1_PH1ADJC;
	BitField	REG1_OUT1DIVRSEL;
	BitField	REG1_OUT1DIVSEL;
	BitField	REG1_HISWINGLVPECL1;
	BitField	REG1_CMOSMODE1P;
	BitField	REG1_CMOSMODE1N;
	BitField	REG1_OUTBUFSEL1;
	
	// bit field in register 2
	BitField	REG2_ADDR;
	BitField	REG2_REFDIV;
	BitField	REG2_RESERVED;
	BitField	REG2_OUTMUX2SEL;
	BitField	REG2_PH2ADJC;
	BitField	REG2_OUT2DIVRSEL;
	BitField	REG2_OUT2DIVSEL;
	BitField	REG2_HISWINGLVPEC2;
	BitField	REG2_CMOSMODE2P;
	BitField	REG2_CMOSMODE2N;
	BitField	REG2_OUTBUFSEL2;
	
	// bit field in register 3
	BitField	REG3_ADDR;
	BitField	REG3_REFDIV2;
	BitField	REG3_RESERVED;
	BitField	REG3_OUTMUX3SEL;
	BitField	REG3_PH3ADJC;
	BitField	REG3_OUT3DIVRSEL;
	BitField	REG3_OUT3DIVSEL;
	BitField	REG3_HISWINGLVPEC3;
	BitField	REG3_CMOSMODE3P;
	BitField	REG3_CMOSMODE3N;
	BitField	REG3_OUTBUFSEL3;
	
	// bit field in register 4
	BitField	REG4_ADDR;
	BitField	REG4_RESERVED0;
	BitField	REG4_ATETEST;
	BitField	REG4_RESERVED1;
	BitField	REG4_OUTMUX4SEL;
	BitField	REG4_PH4ADJC;
	BitField	REG4_OUT4DIVRSEL;
	BitField	REG4_OUT4DIVSEL;
	BitField	REG4_HISWINGLVPEC4;
	BitField	REG4_CMOSMODE4P;
	BitField	REG4_CMOSMODE4N;
	BitField	REG4_OUTBUFSEL4;
		
	// bit field in register 5
	BitField	REG5_ADDR;
	BitField	REG5_INBUFSEL;
	BitField	REG5_SMART_MUX;
	BitField	REG5_EECLKSEL;
	BitField	REG5_ACDCSEL;
	BitField	REG5_HYSTEN;
	BitField	REG5_PRI_TERMSEL;
	BitField	REG5_PRIINVBB;
	BitField	REG5_SECINVBB;
	BitField	REG5_FAILSAFE;
	BitField	REG5_RESERVED;
	BitField	REG5_SELINDIV;
	BitField	REG5_LOCKW;
	BitField	REG5_LOCKDET;
	BitField	REG5_ADLOCK;
		
	// bit field in register 6
	BitField	REG6_ADDR;
	BitField	REG6_SELVCO;
	BitField	REG6_SELPRESC;
	BitField	REG6_SELFBDIV;
	BitField	REG6_RESERVED0;
	BitField	REG6_SEC_TERMSEL;
	BitField	REG6_SELBPDIV;
	BitField	REG6_ICPSEL;
	BitField	REG6_RESERVED1;
	BitField	REG6_CPPULSEWIDTH;
	BitField	REG6_ENCAL;
	BitField	REG6_RESERVED2;
	BitField	REG6_AUXOUTEN;
	BitField	REG6_AUXFEEDSEL;
	BitField	REG6_EXLFSEL;
	BitField	REG6_ENCAL_MODE;
		
	// bit field in register 7
	BitField	REG7_ADDR;
	BitField	REG7_LFRCSEL_C2;
	BitField	REG7_LFRCSEL_R2;
	BitField	REG7_LFRCSEL_C1;
	BitField	REG7_LFRCSEL_C3;
	BitField	REG7_LFRCSEL_R3;
	BitField	REG7_RESERVED0;
	BitField	REG7_TESTMUX1;
	BitField	REG7_SEL_DEL2;
	BitField	REG7_TEXTMUX2;
	BitField	REG7_SEL_DEL1;
	BitField	REG7_EPLOCK;
	BitField	REG7_RESERVED1;

	// bit field in register 8
	BitField	REG8_ADDR;
	BitField	REG8_CALWORD;
	BitField	REG8_PLLLOCKPIN;
	BitField	REG8__SLEEP;
	BitField	REG8__SYNC;
	BitField	REG8_RESERVED0;
	BitField	REG8_VERSION;
	BitField	REG8_RESERVED1;
	BitField	REG8_CALWORD_IN;
	BitField	REG8_RESERVED2;
	BitField	REG8_TITSTCFG;
	BitField	REG8_PRIACTIVITY;
	BitField	REG8_SECACTIVITY;
	BitField	REG8_AUXACTIVITY;
#endif
	
	// Spi pins
	GpioPin 	*miso;
	GpioPin 	*mosi;
	GpioPin 	*sclk;
	GpioPin 	*ce;
}	CDCE62005_Device;

typedef enum CDCE62005Return {
	CDCE62005_OK 		= 0,
	CDCE62005_ERROR 	= 1
} CDCE62005Return;
    
typedef enum CP_Current {
	CP_Current_50uA			= 0,
	CP_Current_100uA		= 1,
	CP_Current_150uA		= 2,
	CP_Current_200uA		= 3,
	CP_Current_300uA		= 4,
	CP_Current_400uA		= 5,
	CP_Current_600uA		= 6,
	CP_Current_750uA		= 7,
	CP_Current_1mA			= 8,
	CP_Current_1_25mA		= 9,
	CP_Current_1_5mA		= 10,
	CP_Current_2mA			= 11,
	CP_Current_2_5mA		= 12,
	CP_Current_3mA			= 13,
	CP_Current_3_5mA		= 14,
	CP_Current_3_75mA		= 15
} CP_Current;

typedef enum PreScaler {	
	PreScaler_2				= 3,
	PreScaler_3				= 1,
	PreScaler_4				= 2,
	PreScaler_5				= 0
} PreScaler;

typedef enum FB_BypassDiv {
	FB_BypassDiv_1			= 7,
	FB_BypassDiv_2			= 0,
	FB_BypassDiv_5			= 1,
	FB_BypassDiv_8			= 2,
	FB_BypassDiv_10			= 3,
	FB_BypassDiv_16			= 4,
	FB_BypassDiv_20			= 5
} FB_BypassDiv;

typedef enum FB_Divider {
	FB_Divider_8			= 0,
	FB_Divider_12			= 1,
	FB_Divider_16			= 2,
	FB_Divider_20			= 3,
	FB_Divider_24			= 5,
	FB_Divider_32			= 6,
	FB_Divider_36			= 9,
	FB_Divider_40			= 7,
	FB_Divider_48			= 10,
	FB_Divider_56			= 24,
	FB_Divider_60			= 11,
	FB_Divider_64			= 14,
	FB_Divider_72			= 21,
	FB_Divider_80			= 15,
	FB_Divider_84			= 25,
	FB_Divider_96			= 22,
	FB_Divider_100			= 19,
	FB_Divider_108			= 73,
	FB_Divider_112			= 26,
	FB_Divider_120			= 23,
	FB_Divider_128			= 30,
	FB_Divider_140			= 27,
	FB_Divider_144			= 53,
	FB_Divider_160			= 31,
	FB_Divider_168			= 57,
	FB_Divider_180			= 75,
	FB_Divider_192			= 54,
	FB_Divider_200			= 51,
	FB_Divider_216			= 85,
	FB_Divider_224			= 58,
	FB_Divider_240			= 55,
	FB_Divider_252			= 89,
	FB_Divider_256			= 62,
	FB_Divider_280			= 59,
	FB_Divider_288			= 86,
	FB_Divider_300			= 83,
	FB_Divider_320			= 63,
	FB_Divider_336			= 90,
	FB_Divider_360			= 87,
	FB_Divider_384			= 94,
	FB_Divider_392			= 216,
	FB_Divider_400			= 115,
	FB_Divider_420			= 91,
	FB_Divider_432			= 181,
	FB_Divider_448			= 122,
	FB_Divider_480			= 95,
	FB_Divider_500			= 147,
	FB_Divider_504			= 185,
	FB_Divider_512			= 126,
	FB_Divider_560			= 123,
	FB_Divider_576			= 182,
	FB_Divider_588			= 217,
	FB_Divider_600			= 151,
	FB_Divider_640			= 127,
	FB_Divider_672			= 186,
	FB_Divider_700			= 155,
	FB_Divider_720			= 183,
	FB_Divider_768			= 190,
	FB_Divider_784			= 218,
	FB_Divider_800			= 159,
	FB_Divider_840			= 187,
	FB_Divider_896			= 222,
	FB_Divider_960			= 191,
	FB_Divider_980			= 219,
	FB_Divider_1024			= 254,
	FB_Divider_1120			= 223,
	FB_Divider_1280			= 255
}FB_Divider;

typedef enum SelVCO {
	SelVCO_LowRange			= 0,
	SelVCO_HighRange		= 1
}SelVCO;

typedef enum LF_C1 {
	LF_C1_0pF				= 0,
	LF_C1_1_5pF				= 1,
	LF_C1_6_5pF				= 2,
	LF_C1_8pF				= 3,
	LF_C1_10pF				= 4,
	LF_C1_11_5pF			= 5,
	LF_C1_16_5pF			= 6,
	LF_C1_18pF				= 7,
	LF_C1_21_5pF			= 8,
	LF_C1_23pF				= 9,
	LF_C1_69pF				= 28,
	LF_C1_70_5pF			= 29,
	LF_C1_75_5pF			= 30,
	LF_C1_77pF				= 31
}LF_C1;

typedef enum LF_C2 {
	LF_C2_0pF				= 0,
	LF_C2_12_5pF			= 1,
	LF_C2_25pF				= 2,
	LF_C2_37_5pF			= 3,
	LF_C2_87pF				= 4,
	LF_C2_99_5pF			= 5,
	LF_C2_112pF				= 6,
	LF_C2_124_5pF			= 7,
	LF_C2_123pF				= 8,
	LF_C2_135_5pF			= 9,
	LF_C2_436pF				= 28,
	LF_C2_448_5pF			= 29,
	LF_C2_461pF				= 30,
	LF_C2_473_5pF			= 31
}LF_C2;

typedef enum LF_C3 {
	LF_C3_0pF				= 0,
	LF_C3_2_5pF				= 1,
	LF_C3_5_5pF				= 2,
	LF_C3_8pF				= 3,
	LF_C3_19_5pF			= 4,
	LF_C3_22pF				= 5,
	LF_C3_25pF				= 6,
	LF_C3_27_5pF			= 7,
	LF_C3_85pF				= 8,
	LF_C3_87_5pF			= 9,
	LF_C3_104_5pF			= 14,
	LF_C3_107pF				= 15,
	LF_C3_110pF				= 14,
	LF_C3_112_5pF			= 15
}LF_C3;	

typedef enum LF_R2 {
	LF_R2_127_6k			= 0,
	LF_R2_123_6k			= 1,
	LF_R2_118_6k			= 2,
	LF_R2_114_6k			= 3,
	LF_R2_107_6k			= 4,
	LF_R2_103_6k			= 5,
	LF_R2_98_6k				= 6,
	LF_R2_94_6k				= 7,
	LF_R2_89_4k				= 8,
	LF_R2_85_4k				= 9,
	LF_R2_13k				= 28,
	LF_R2_9k				= 29,
	LF_R2_4k				= 30,
	LF_R2_0k				= 31
}LF_R2;	

typedef enum LF_R3 {
	LF_R3_20k				= 0,
	LF_R3_15k				= 1,
	LF_R3_10k				= 2,
	LF_R3_5k				= 3
}LF_R3;

typedef enum InputBuffSel {
	InputBuffSel_LVPECL		= 1,	
	InputBuffSel_LVDS		= 3,
	InputBuffSel_LVCMOS		= 0
}InputBuffSel;

typedef enum SmartMux {
	SmartMux_PriSel				= 1,
	SmartMux_SecSel				= 2,
	SmartMux_AuxSel				= 4,
	SmartMux_AutoSel_PriSec		= 3,
	SmartMux_AutoSel_PriSecAux	= 7
}SmartMux;

typedef enum LockWindow {
	LockWindow_Narrow 		= 0,
	LockWindow_Widest		= 14
}LockWindow;

typedef enum OutputType {
	OutputType_LVPECL 		= 2,
	OutputType_LVDS 		= 3,
	OutputType_LVCMOS		= 0,
	OutputType_Disabled 	= 1
}OutputType;

typedef enum LVCMOS_Mode {
	LVCMOS_Mode_Active 		= 0,
	LVCMOS_Mode_Inverting	= 1,
	LVCMOS_Mode_Low			= 3,
	LVCMOS_Mode_3_State 	= 2
}LVCMOS_Mode;

typedef enum OutputMux {
	OutputMux_Pri_In		= 0,
	OutputMux_Sec_In		= 2,	
	OutputMux_Smart_Mux		= 1,
	OutputMux_VCO_Core		= 3
}OutputMux;

typedef enum OutputDivider {
	OutPutDivider_1			= 32,
	OutPutDivider_2			= 64,
	OutPutDivider_3			= 65,
	OutPutDivider_4			= 66,
	OutPutDivider_5			= 67,
	OutPutDivider_6			= 1,
	OutPutDivider_8			= 2,
	OutPutDivider_10		= 3,
	OutPutDivider_12		= 5,
	OutPutDivider_16		= 6,
	OutPutDivider_20		= 7,
	OutPutDivider_18		= 9,
	OutPutDivider_24		= 10,
	OutPutDivider_30		= 11,
	OutPutDivider_32		= 14,
	OutPutDivider_40		= 15,
	OutPutDivider_50		= 19,
	OutPutDivider_36		= 21,
	OutPutDivider_48		= 22,
	OutPutDivider_60		= 23,
	OutPutDivider_28		= 24,
	OutPutDivider_42		= 25,
	OutPutDivider_56		= 26,
	OutPutDivider_70		= 27,
	OutPutDivider_64		= 30,
	OutPutDivider_80		= 31
}OutputDivider;

typedef enum PreDivider {
	PreDivider_3_state		= 0,
	PreDivider_1			= 2,
	PreDivider_2			= 1	
}PreDivider;

typedef enum {
	EEClkSelExternal = 0,
	EEClkSelInternal = 1
} EEClkSel;

typedef enum {
	ACDCSelAC = 0,
	ACDCSelDC = 1
} ACDCSel;

typedef enum {
	HysteresisDisable = 0,
	HysteresisEnable = 1
} Hysteresis;

typedef enum {
	FailSafeDisable = 0,
	FailSafeEnable = 1
} FailSafeMode;

typedef enum {
	PrescalerOutputFreq600MHz,
	PrescalerOutputFreq614_4MHz,
	PrescalerOutputFreq640MHz,
	PrescalerOutputFreq768MHz,
	PrescalerOutputFreq1000MHz,
	PrescalerOutputFreq1024MHz,
	PrescalerOutputFreq960MHz,
	PrescalerOutputFreq720MHz
} PrescalerOutputFreq;

typedef enum {
	TermSelModeEnable = 0,
	TermSelModeDisable = 1
} TermSelMode;

/**
 * Function prototypes
 */

void cdce62005_init(CDCE62005_Device *dev, GpioPin *spi_sclk, GpioPin *spi_mosi, GpioPin *spi_miso, GpioPin *spi_chip_enable);
void cdce62005_basic_pll_setup(CDCE62005_Device *dev, PrescalerOutputFreq prescaler_output_freq);
void delayFunction							(void);
void _write_byte							(uint8 d);

void cdce62005_spi_read 					(CDCE62005_Device 	*dev, const uint16 reg_base_addr, uint32 *d);
void cdce62005_spi_write 					(CDCE62005_Device 	*dev, uint32 *d);
void cdce62005_spi_chip_enable				(CDCE62005_Device 	*dev, uint8 value);

// --------------------------------------------------------------------------------------------------------------------------------------


//void cdce62005_regInitRead 		(SpiDevice 			spi_pll, 		CDCE62005_Device 	*dev); -> init integrieren
void cdce62005_set_cp_current 				(CDCE62005_Device 	*dev, 	CP_Current		charge_pump_current);
void cdce62005_set_prescaler 				(CDCE62005_Device 	*dev, 	PreScaler 		pre_scaler);

void cdce62005_set_feedback_bypass_divider	(CDCE62005_Device 	*dev, 	FB_BypassDiv 	feedback_bypass_div);
void cdce62005_set_feedback_divider 		(CDCE62005_Device 	*dev, 	FB_Divider 		fbRatio);
void cdce62005_set_VCO_sel 					(CDCE62005_Device 	*dev, 	SelVCO 			vco_sel);
void cdce62005_set_LF_C1					(CDCE62005_Device 	*dev, 	LF_C1 			c1);
void cdce62005_set_LF_C2 					(CDCE62005_Device 	*dev, 	LF_C2 			c2);
void cdce62005_set_LF_C3 					(CDCE62005_Device 	*dev, 	LF_C3 			c3);
void cdce62005_set_LF_R2	 				(CDCE62005_Device 	*dev, 	LF_R2 			r2);
void cdce62005_set_LF_R3 					(CDCE62005_Device 	*dev, 	LF_R3 			r3);

void cdce62005_set_input_buff_sel			(CDCE62005_Device 	*dev, 	InputBuffSel	input_buffer_sel);
void cdce62005_set_SmartMux					(CDCE62005_Device 	*dev, 	SmartMux		smart_max);
void cdce62005_set_LockWindow				(CDCE62005_Device 	*dev, 	LockWindow		lock_window);

CDCE62005Return	cdce62005_set_output_type	(CDCE62005_Device 	*dev, 	int 		regNum,	OutputType 		output_type);
CDCE62005Return	cdce62005_set_LVCMOS_mode	(CDCE62005_Device 	*dev, 	int 		regNum,	LVCMOS_Mode 	lvcmos_mode);
CDCE62005Return cdce62005_set_output_mux	(CDCE62005_Device 	*dev, 	int output_port,	OutputMux		output_mux);

void cdce62005_aux_out_enable				(CDCE62005_Device 	*v, 	int 		outputDivider);
void cdce62005_aux_out_disable				(CDCE62005_Device 	*dev);

CDCE62005Return	cdce62005_set_input_divider	(CDCE62005_Device 	*dev, 	int 		divRatio);
CDCE62005Return	cdce62005_set_output_divider(CDCE62005_Device 	*dev, 	int 		regNum,	OutputDivider 	output_div);

CDCE62005Return 	cdce62005_divider_init	(CDCE62005_Device 	*dev, 	int regNum, int inputDivider, OutputDivider 	output_div, FB_Divider 	fbRatio, FB_BypassDiv 	feedback_bypass_div, PreScaler 	pre_scaler);
void cdce62005_loop_filter_init				(CDCE62005_Device 	*dev, 	LF_C1 	c1, LF_C2 	c2, LF_C3 	c3, LF_R2 	r2, LF_R3 	r3);


CDCE62005Return 	cdce62005_ref_divider	(CDCE62005_Device 	*dev, 	int		ref_divider);
void cdce62005_pre_divider_pri_ref			(CDCE62005_Device 	*dev, 	PreDivider		pre_divider_primary);
void cdce62005_pre_divider_sec_ref			(CDCE62005_Device 	*dev, 	PreDivider		pre_divider_secondary);
////
void cdce62005_reg0_remained_bits			(CDCE62005_Device 	*dev);
void cdce62005_reg1_remained_bits			(CDCE62005_Device 	*dev);
void cdce62005_reg2_remained_bits			(CDCE62005_Device 	*dev);
void cdce62005_reg3_remained_bits			(CDCE62005_Device 	*dev);
void cdce62005_reg4_remained_bits			(CDCE62005_Device 	*dev);
void cdce62005_reg5_remained_bits			(CDCE62005_Device 	*dev);
void cdce62005_reg6_remained_bits_pri		(CDCE62005_Device 	*dev);
void cdce62005_reg6_remained_bits_sec		(CDCE62005_Device 	*dev);
void cdce62005_reg7_remained_bits			(CDCE62005_Device 	*dev);

CDCE62005Return cdce62005_run_PLL 			(CDCE62005_Device 	*dev, int output_port);
void cdce62005_enable_output(CDCE62005_Device *dev, int output_port);
void cdce62005_disable_output(CDCE62005_Device *dev, int output_port);
void cdce62005_configure_output(CDCE62005_Device *dev, int output_port, OutputDivider output_divider, OutputType output_type, OutputMux output_mux);
void cdce62005_write_config(CDCE62005_Device *dev);
void cdce62005_vco_calibration(CDCE62005_Device *dev);
uint8 cdce62005_pll_locked(CDCE62005_Device *dev);
CDCE62005Return cdce62005_set_cmos_mode_p(CDCE62005_Device *dev, int16 output_port, LVCMOS_Mode mode);
CDCE62005Return cdce62005_set_cmos_mode_n(CDCE62005_Device *dev, int16 output_port, LVCMOS_Mode mode);
CDCE62005Return cdce62005_output_divider_coarse_phase(CDCE62005_Device *dev, int16 output_port, int16 int_phase);
CDCE62005Return cdce62005_set_eeclksel(CDCE62005_Device *dev, EEClkSel sel);
CDCE62005Return cdce62005_set_acdcsel(CDCE62005_Device *dev, ACDCSel sel);
CDCE62005Return cdce62005_set_hysteresis(CDCE62005_Device *dev, Hysteresis sel);
CDCE62005Return cdce62005_set_failsafe_mode(CDCE62005_Device *dev, FailSafeMode sel);
CDCE62005Return cdce62005_set_sec_termsel(CDCE62005_Device *dev, TermSelMode sel);
void cdce62005_ram2eeprom_unlock(CDCE62005_Device *dev);
uint8 cdce62005_eeprom_locked(CDCE62005_Device *dev);

// --------------------------------------------------------------------------------------------------------------------------------------

#endif /*PLL_H_*/
