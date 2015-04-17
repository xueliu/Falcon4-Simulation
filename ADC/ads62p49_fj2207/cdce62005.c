 /*
 * PLL Description:
 *           
 *            -------------------        ---      -----       -----      ---------------          --------------------
 *  F_in --->|   Input divider   |----->| - |--->|  ~  |---->| VCO |--->| Prescaler (N) | ------>| Output Divider (P) | --------> F_out
 *            -------------------        ---      -----       -----      ---------------     |    --------------------     
 *                                  ^													 |					       
 * 				 	        	 	|           										 |						   
 * 				 	 		        |				    ---------------------- |		 |			   
 * 				  			           <----------------|FeedBack Divider (FB) |----------		
 *                                                       ----------------------
 */

 /*
	Prescaler Output Frequencies
	614_4	AIF related (multiple of 30.72)
	640		DVB-T2, OSR=1, set output divider to 70, 64/7*1 MHz
	1000	test clock
	1024	DVB-T2, OSR=4, set output divider to 28, 64/7*4 MHz
 */
 
 
#include "cdce62005.h"
#include "cdce62005_reg.h"
#include <hal.h>
#include <assert.h>

static CDCE62005_Device *_active_dev;

// _output_type_x variables are used to store the configuration before disabling the corresponding output to simplify the enabling procedure
OutputType	_output_type_0;
OutputType	_output_type_1;
OutputType	_output_type_2;
OutputType	_output_type_3;
OutputType	_output_type_4;

// Delay Function for Spi Clock --------------------------------------------------------------
void delayFunction(void) {
	unsigned long int i;
	int j = 0;
	for (i = 0; i < 800000; ++i) {
		j++;
	}
}
// -------------------------------------------------------------------------------------------

/* --- Internal functions declarations --- */
void		_write_byte(uint8 d);

#undef BITBANG_PREFIX
#define BITBANG_PREFIX dev->

void cdce62005_disable_all_outputs( CDCE62005_Device *dev ) {
	BITBANG_SET_VALUE(REG0_OUT0DIVSEL, 0);
	BITBANG_SET_VALUE(REG1_OUT1DIVSEL, 0);
	BITBANG_SET_VALUE(REG2_OUT2DIVSEL, 0);
	BITBANG_SET_VALUE(REG3_OUT3DIVSEL, 0);
	BITBANG_SET_VALUE(REG4_OUT4DIVSEL, 0);
	
	BITBANG_SET_VALUE(REG0_CMOSMODE0P, LVCMOS_Mode_3_State);
	BITBANG_SET_VALUE(REG1_CMOSMODE1P, LVCMOS_Mode_3_State);
	BITBANG_SET_VALUE(REG2_CMOSMODE2P, LVCMOS_Mode_3_State);
	BITBANG_SET_VALUE(REG3_CMOSMODE3P, LVCMOS_Mode_3_State);
	BITBANG_SET_VALUE(REG4_CMOSMODE4P, LVCMOS_Mode_3_State);
	
	BITBANG_SET_VALUE(REG0_CMOSMODE0N, LVCMOS_Mode_3_State);
	BITBANG_SET_VALUE(REG1_CMOSMODE1N, LVCMOS_Mode_3_State);
	BITBANG_SET_VALUE(REG2_CMOSMODE2N, LVCMOS_Mode_3_State);
	BITBANG_SET_VALUE(REG3_CMOSMODE3N, LVCMOS_Mode_3_State);
	BITBANG_SET_VALUE(REG4_CMOSMODE4N, LVCMOS_Mode_3_State);
	
	BITBANG_SET_VALUE(REG0_OUTBUFSEL0, OutputType_Disabled); 
	BITBANG_SET_VALUE(REG1_OUTBUFSEL1, OutputType_Disabled);
	BITBANG_SET_VALUE(REG2_OUTBUFSEL2, OutputType_Disabled);
	BITBANG_SET_VALUE(REG3_OUTBUFSEL3, OutputType_Disabled);
	BITBANG_SET_VALUE(REG4_OUTBUFSEL4, OutputType_Disabled);
	
	_output_type_0 = OutputType_Disabled;
	_output_type_1 = OutputType_Disabled;
	_output_type_2 = OutputType_Disabled;
	_output_type_3 = OutputType_Disabled;
	_output_type_4 = OutputType_Disabled;
	
	//cdce62005_spi_write	(dev, &dev->reg0);
	//cdce62005_spi_write	(dev, &dev->reg1);
	//cdce62005_spi_write	(dev, &dev->reg2);
	//cdce62005_spi_write	(dev, &dev->reg3);
	//cdce62005_spi_write	(dev, &dev->reg4);
}

void cdce62005_init(CDCE62005_Device *dev, GpioPin *spi_sclk, GpioPin *spi_mosi, GpioPin *spi_miso, GpioPin *spi_chip_enable) {
	dev->miso 	= spi_miso;
	dev->mosi 	= spi_mosi;
	dev->sclk 	= spi_sclk;
	dev->ce		= spi_chip_enable;

	dev->reg0 = BITBANG_REG0_RESET_VALUE;
	dev->reg1 = BITBANG_REG1_RESET_VALUE;
	dev->reg2 = BITBANG_REG2_RESET_VALUE;
	dev->reg3 = BITBANG_REG3_RESET_VALUE;
	dev->reg4 = BITBANG_REG4_RESET_VALUE;
	dev->reg5 = BITBANG_REG5_RESET_VALUE;
	dev->reg6 = BITBANG_REG6_RESET_VALUE;
	dev->reg7 = BITBANG_REG7_RESET_VALUE;
	dev->reg8 = BITBANG_REG8_RESET_VALUE;

	// write default values to device to be "synchronous" with driver program
	cdce62005_write_config(dev);
	
	cdce62005_disable_all_outputs(dev);
	cdce62005_aux_out_disable	 			(dev);				// Disable Auxiliary Output, Register 6.24 & 6.25
}


void cdce62005_basic_pll_setup(CDCE62005_Device *dev, PrescalerOutputFreq prescaler_output_freq)
{	
	int16 fb_divider, fb_bypass_divider, prescaler, input_divider;
	SelVCO 	vco_mode;	
	
	
	// Basic PLL setup
	cdce62005_set_LockWindow				(dev, LockWindow_Narrow);		// lock-detected window width, register 5, 5.22 - 5.25
	cdce62005_set_cp_current 				(dev, CP_Current_300uA);			// Charge Pump Current Select, Register 6, 6.16 - 6.19
	
	// Setup output buffer U0
	//cdce62005_set_output_mux(dev, 0,	OutputMux_VCO_Core);

	// f_vco = f_ref * prescaler * fb_divider * fb_bypass_divider / input_divider;
	// prescaler_output_freq = f_vco / presccaler
	switch (prescaler_output_freq) {
		case  PrescalerOutputFreq600MHz:
			// Fin = 20-MHz, M=1, P=40, FB=20, N=5, Register 0, Fout = 10MHz, 
			// f_vco = 20 * 5 * 20 * 1 / 1 = 2000 MHz -> VCO mode low
			// output_divider 		= OutPutDivider_40;

			cdce62005_pre_divider_pri_ref( dev, 	PreDivider_3_state);
			cdce62005_pre_divider_sec_ref( dev, 	PreDivider_3_state);

			// Reference selection
			cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVDS);		// LVDS,   Register 5, 5.0 & 5.1
			//cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS);		// LVDS,   Register 5, 5.0 & 5.1
			cdce62005_set_SmartMux					(dev, SmartMux_AuxSel);			// Register 5, 5.2 & 5.3 & 5.4

			
			fb_divider 			= FB_Divider_60;
			fb_bypass_divider	= FB_BypassDiv_1;
			prescaler 			= PreScaler_3;
			input_divider		= 2;
			//vco_mode 			= SelVCO_HighRange;
			vco_mode 			= SelVCO_LowRange;
			break;

		case PrescalerOutputFreq614_4MHz:
			
			cdce62005_pre_divider_pri_ref( dev, 	PreDivider_3_state);
			cdce62005_pre_divider_sec_ref( dev, 	PreDivider_3_state);

			
			// Reference selection
//			cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVDS);		// LVDS,   Register 5, 5.0 & 5.1
			cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS);		// LVDS,   Register 5, 5.0 & 5.1
//			cdce62005_set_SmartMux					(dev, SmartMux_AuxSel);			// Register 5, 5.2 & 5.3 & 5.4
			cdce62005_set_SmartMux					(dev, SmartMux_SecSel);			// Register 5, 5.2 & 5.3 & 5.4
		
			fb_divider 			= FB_Divider_20;
			fb_bypass_divider	= FB_BypassDiv_5;
			prescaler 			= PreScaler_3;
			input_divider		= 4;
			vco_mode 			= SelVCO_LowRange;
			break;
		
		case PrescalerOutputFreq640MHz:
			cdce62005_pre_divider_pri_ref( dev, 	PreDivider_3_state);
			cdce62005_pre_divider_sec_ref( dev, 	PreDivider_1);
			
			cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS);
			//cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS);		// LVDS,   Register 5, 5.0 & 5.1
			cdce62005_set_SmartMux					(dev, SmartMux_SecSel);			// Register 5, 5.2 & 5.3 & 5.4

			fb_divider 			= FB_Divider_64;
			fb_bypass_divider	= FB_BypassDiv_1;
			prescaler 			= PreScaler_3;
			input_divider		= 2;
			vco_mode 			= SelVCO_LowRange;
			break;

		case PrescalerOutputFreq768MHz:
			cdce62005_pre_divider_pri_ref( dev, 	PreDivider_3_state);
			cdce62005_pre_divider_sec_ref( dev, 	PreDivider_1);
		
			cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS);
			//cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS);		// LVDS,   Register 5, 5.0 & 5.1
			cdce62005_set_SmartMux					(dev, SmartMux_SecSel);			// Register 5, 5.2 & 5.3 & 5.4
		
			fb_divider 			= FB_Divider_96;
			fb_bypass_divider	= FB_BypassDiv_2;
			prescaler 			= PreScaler_3;
			input_divider		= 5;
			vco_mode 			= SelVCO_HighRange;
			break;
			
			
		case PrescalerOutputFreq1000MHz:
			cdce62005_pre_divider_pri_ref( dev, 	PreDivider_3_state);
			cdce62005_pre_divider_sec_ref( dev, 	PreDivider_3_state);
		
			// Reference selection
			cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVDS);		// LVDS,   Register 5, 5.0 & 5.1
			//cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS);		// LVDS,   Register 5, 5.0 & 5.1
			cdce62005_set_SmartMux					(dev, SmartMux_AuxSel);			// Register 5, 5.2 & 5.3 & 5.4
		
			fb_divider 			= FB_Divider_100;
			fb_bypass_divider	= FB_BypassDiv_1;
			prescaler 			= PreScaler_2;
			input_divider		= 2;
			vco_mode 			= SelVCO_LowRange;
			break;

		case PrescalerOutputFreq1024MHz:
			cdce62005_pre_divider_pri_ref( dev, 	PreDivider_3_state);
			cdce62005_pre_divider_sec_ref( dev, 	PreDivider_1);
		
			cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS);
			//cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS);		// LVDS,   Register 5, 5.0 & 5.1
			cdce62005_set_SmartMux					(dev, SmartMux_SecSel);			// Register 5, 5.2 & 5.3 & 5.4
		
			fb_divider 			= FB_Divider_256;
			fb_bypass_divider	= FB_BypassDiv_1;
			prescaler 			= PreScaler_2;
			input_divider		= 5;
			vco_mode 			= SelVCO_HighRange;
		
		break;

		case PrescalerOutputFreq960MHz:
			cdce62005_pre_divider_pri_ref( dev, 	PreDivider_3_state); 	// do not work for Aux input
			cdce62005_pre_divider_sec_ref( dev, 	PreDivider_1);			// do not work for Aux input

			cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS); // do not work for Aux input
			cdce62005_set_SmartMux					(dev, SmartMux_AuxSel);			// Register 5, 5.2 & 5.3 & 5.4

			fb_divider 			= FB_Divider_48;
			fb_bypass_divider	= FB_BypassDiv_1;
			prescaler 			= PreScaler_2;
			input_divider		= 1;
			vco_mode 			= SelVCO_LowRange;

		break;
		
		case PrescalerOutputFreq720MHz:
			cdce62005_pre_divider_pri_ref( dev, 	PreDivider_3_state); 	// do not work for Aux input
			cdce62005_pre_divider_sec_ref( dev, 	PreDivider_1);			// do not work for Aux input

			cdce62005_set_input_buff_sel			(dev, InputBuffSel_LVCMOS); // do not work for Aux input
			cdce62005_set_SmartMux					(dev, SmartMux_SecSel);			// Register 5, 5.2 & 5.3 & 5.4

			fb_divider 			= FB_Divider_36;
			fb_bypass_divider	= FB_BypassDiv_1;
			prescaler 			= PreScaler_3;
			input_divider		= 1;
			vco_mode 			= SelVCO_HighRange;

		break;

		default:
			assert(!"Prescaler output frequency configuration not implemented yet.");
			while(1);

	}
	
	cdce62005_set_VCO_sel 					(dev, vco_mode);			// VCO Range Select, Register 6, 6.0
																		// Low: 	1750-2046 MHz
																		// High: 	2040-2356 MHz																					
	cdce62005_set_input_divider				(dev, input_divider);
	cdce62005_set_feedback_divider			(dev, (FB_Divider)fb_divider);
	cdce62005_set_feedback_bypass_divider	(dev, (FB_BypassDiv)fb_bypass_divider);
	cdce62005_set_prescaler					(dev, (PreScaler)prescaler);

	cdce62005_loop_filter_init				(dev, LF_C1_0pF, LF_C2_473_5pF, LF_C3_0pF, LF_R2_9k, LF_R3_10k);				// 10-MHz
	
	//cdce62005_vco_calibration(dev);
}

// --------------------------------------------------------------------------------------------------------------------
// Reading 32-bit Data -----------
void cdce62005_spi_read(CDCE62005_Device *dev, const uint16 reg_base_addr, uint32 *d) {
	int16 i;
	int16 num_Bytes = 4;
	uint32 result = 0;
	uint32 read_instruction = 0x00000000;
	read_instruction |= reg_base_addr;
	read_instruction <<= 4;
	read_instruction |= 0x0E;

	_active_dev = dev;

// -----------------------
	//spi_ce_clear(dev);
	cdce62005_spi_chip_enable(dev, 0);
	
	for ( i = 0; i <= (num_Bytes - 1); i++) {
		if (i!= 0) {
			read_instruction >>= 8;
		}
		_write_byte(read_instruction);
	}
	cdce62005_spi_chip_enable(dev, 1);
// ------------------------
	//spi_sclk_up(dev);
	gpio_pin_set(_active_dev->sclk);
	
	//spi_ce_clear(dev);
	cdce62005_spi_chip_enable(dev, 0);

	//if (portPin_read(_activeDev.spi_miso)) {
	//	result |= 1;
	//}

	if (gpio_pin_get(_active_dev->miso)) {
		result |= 1;
	}

	for (i=1; i<32; i++ ) {
		//spi_sclk_down(dev);	
		gpio_pin_clear(_active_dev->sclk);	
		if (gpio_pin_get(_active_dev->miso)) {
			result |= ((int32)1<<(i));
		}
		//spi_sclk_up(dev);
		gpio_pin_set(_active_dev->sclk);
	}

//	spi_ce_set(dev);
	cdce62005_spi_chip_enable(dev, 1);
	*d = result;
}

void cdce62005_ram2eeprom_unlock(CDCE62005_Device *dev) {
	uint32 cmd = 0x0000001F;
	
	cdce62005_spi_write(dev, &cmd);
}

// --------------------------------------------------------------------------------------------------------------------
// Writing 32-bit Data -----------
void cdce62005_spi_write(CDCE62005_Device *dev, uint32 *d) {
	int16	i;
	int16	num_Bytes = 4;
	uint32	data_to_send = 0lu;  
///	uint16 temp;

	data_to_send |= *d;

///	temp = ~reg_base_addr;
	
	_active_dev = dev;

	//spi_ce_clear(dev);
	cdce62005_spi_chip_enable(dev, 0);
		
	for ( i = 0; i <= (num_Bytes - 1); i++) {
		if (i!= 0) {
			data_to_send >>= 8;
		}
		_write_byte(data_to_send);
	}
	//spi_ce_set(dev);
	cdce62005_spi_chip_enable(dev, 1);
}
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// writing one byte through spi
void _write_byte(uint8 d) {
	int16	i;
	//if (_activeDev.spiMode == SPI_SDIO) {
	//	portPin_setAsOutput(_activeDev.spi_mosi);
	//}

	for (i = 0; i < 8; i++)	{
		//spi_sclk_down(_activeDev);	
		gpio_pin_clear(_active_dev->sclk);
//		if (data & 0x80) {
		if (d & 0x01) {
			gpio_pin_set(_active_dev->mosi);
		} else {
			gpio_pin_clear(_active_dev->mosi);
		}

		//spi_sclk_up(_active_dev);
		gpio_pin_set(_active_dev->sclk);
		
// shift byte left, so that we can send the next bit
		d >>= 1;
	}
}

void cdce62005_spi_chip_enable	(CDCE62005_Device 	*dev, uint8 value) {
	if (value == 0) {
		gpio_pin_clear(dev->ce);
	} else {
		gpio_pin_set(dev->ce);
	}
}
// --------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------

// set charge-pump current, Register 6, 6.16 - 6.19
void cdce62005_set_cp_current(CDCE62005_Device *dev, CP_Current charge_pump_current) {
//	dev->Reg_6.ICPSEL = charge_pump_current;
//	bitbang_set_value(&(dev->REG6_ICPSEL), charge_pump_current);
	BITBANG_SET_VALUE(REG6_ICPSEL, charge_pump_current);
}
// ------------------------------------------------------------------------------------------------------------------

// set the prescaler N from {2, 3, 4, 5}, Register 6, 6.1 - 6.2
void cdce62005_set_prescaler(CDCE62005_Device *dev, PreScaler pre_scaler) {
//	dev->Reg_6.SELPRESC = pre_scaler;
	BITBANG_SET_VALUE(REG6_SELPRESC, pre_scaler);
	BITBANG_SET_VALUE(REG6_SELPRESC, pre_scaler);
}
// ------------------------------------------------------------------------------------------------------------------

// set feedback divider from {8 to 1280}, Register 6, 6.3 - 6.10
void cdce62005_set_feedback_divider		(CDCE62005_Device 	*dev, 	FB_Divider fbRatio) {
//	dev->Reg_6.SELFBDIV = fbRatio;
	BITBANG_SET_VALUE(REG6_SELFBDIV, fbRatio);
}
// ------------------------------------------------------------------------------------------------------------------

// set feedback divider bypass from {1, 2, 5, 8, 10, 15, 20}, Register 6.13 - 6.15
void cdce62005_set_feedback_bypass_divider	(CDCE62005_Device 	*dev, 	FB_BypassDiv feedback_bypass_div) {
//	dev->Reg_6.SELBPDIV = feedback_bypass_div;
	BITBANG_SET_VALUE(REG6_SELBPDIV, feedback_bypass_div);	
}
// ------------------------------------------------------------------------------------------------------------------

// set input divider M from {1,2,3,..., 256}, Register 5, 5.14 - 5.21
CDCE62005Return cdce62005_set_input_divider 	(CDCE62005_Device 	*dev, 	int divRatio) { 
	if (divRatio <= 256) {
//		dev->Reg_5.SELINDIV = (divRatio - 1);
		BITBANG_SET_VALUE(REG5_SELINDIV, (divRatio - 1));
	}
	else return CDCE62005_ERROR;
	return CDCE62005_OK;	
}
// ------------------------------------------------------------------------------------------------------------------

// set VCO range selection ------------------------------------------------------------------------------------------
// Low  = 1750 MHz - 2046 MHz 
// High = 2040 MHz - 2356 MHz
// Register 6, 6.0
void cdce62005_set_VCO_sel			(CDCE62005_Device 	*dev, 	SelVCO vco_sel) {
	BITBANG_SET_VALUE(REG6_SELVCO, vco_sel);
}
// ------------------------------------------------------------------------------------------------------------------

// select C1 in the loop filter, Register 7, 7.10 - 7.14
void cdce62005_set_LF_C1					(CDCE62005_Device 	*dev, 	LF_C1 c1) {
//	dev->Reg_6.EXLFSEL = 0;
	BITBANG_SET_VALUE(REG6_EXLFSEL, 0);
//	dev->Reg_7.LFRCSEL_C1 = c1;
	BITBANG_SET_VALUE(REG7_LFRCSEL_C1, c1);
}
// ------------------------------------------------------------------------------------------------------------------

// select C2 in the loop filter, Register 7, 7.0 - 7.4
void cdce62005_set_LF_C2 					(CDCE62005_Device 	*dev, 	LF_C2 c2) {
//	dev->Reg_6.EXLFSEL = 0;
	BITBANG_SET_VALUE(REG6_EXLFSEL, 0);
//	dev->Reg_7.LFRCSEL_C2 = c2;
	BITBANG_SET_VALUE(REG7_LFRCSEL_C2, c2);	
}
// ------------------------------------------------------------------------------------------------------------------

// select C3 in the loop filter, Register 7, 7.15 - 7.18
void cdce62005_set_LF_C3 					(CDCE62005_Device 	*dev, 	LF_C3 c3) {
//	dev->Reg_6.EXLFSEL = 0;
	BITBANG_SET_VALUE(REG6_EXLFSEL, 0);
//	dev->Reg_7.LFRCSEL_C3 = c3;
	BITBANG_SET_VALUE(REG7_LFRCSEL_C3, c3);
}
// ------------------------------------------------------------------------------------------------------------------

// select R2 in the loop filter, Register 7, 7.5 - 7.9
void cdce62005_set_LF_R2	 				(CDCE62005_Device 	*dev, 	LF_R2 r2) {
//	dev->Reg_6.EXLFSEL = 0;	
	BITBANG_SET_VALUE(REG6_EXLFSEL, 0);
//	dev->Reg_7.LFRCSEL_R2 = r2;
	BITBANG_SET_VALUE(REG7_LFRCSEL_R2, r2);
}
// ------------------------------------------------------------------------------------------------------------------

// select R3 in the loop filter, Register 7, 7.19 - 7.20
void cdce62005_set_LF_R3 					(CDCE62005_Device 	*dev, 	LF_R3 r3) {
//	dev->Reg_6.EXLFSEL = 0;	
	BITBANG_SET_VALUE(REG6_EXLFSEL, 0);
//	dev->Reg_7.LFRCSEL_R3 = r3;
	BITBANG_SET_VALUE(REG7_LFRCSEL_R3, r3);
}
// ------------------------------------------------------------------------------------------------------------------

// Lock-detect Window Width: LOCKW(3:0)
// = 0000 (narrow window),
// = 0001,0010,0100,0101 ...
// = 1110 (widest window)
// = XX11 (RESERVED)
void cdce62005_set_LockWindow				(CDCE62005_Device 	*dev, 	LockWindow		lock_window) {
//	dev->Reg_5.LOCKW = lock_window;
	BITBANG_SET_VALUE(REG5_LOCKW, lock_window);
}
// ------------------------------------------------------------------------------------------------------------------

// Input Buffer Select (LVPECL,LVDS or LVCMOS)
// XY(01 ) LVPECL, (11) LVDS, (00) LVCMOS- Input is Positive Pin
// Register 5, 5.0 & 5.1
void cdce62005_set_input_buff_sel				(CDCE62005_Device 	*dev, 	InputBuffSel	input_buffer_sel) {
//	dev->Reg_5.INBUFSEL = input_buffer_sel;
	BITBANG_SET_VALUE(REG5_INBUFSEL, input_buffer_sel);
}
// ------------------------------------------------------------------------------------------------------------------

// select Smart Mux
// WHEN EECLKSEL = 1;
// Bit (6,7,8) 100 – PRISEL, 010 – SECSEL , 001 – AUXSEL
// 110 – Auto Select ( PRI then SEC)
// 111 – Auto Select ( PRI then SEC and then AUX)
// When EECLKSEL = 0, REF_SEL pin determines the Reference Input to the Smart Mux
// circuitry.
// Register 5, 5.2 & 5.3 & 5.4
void cdce62005_set_SmartMux					(CDCE62005_Device 	*dev, 	SmartMux		smart_max) {
//	dev->Reg_5.SMART_MUX = smart_max;

	BITBANG_SET_VALUE(REG5_SMART_MUX, smart_max);
}
// ------------------------------------------------------------------------------------------------------------------

/*
OUTPUT TYPE 			RAM BITS
					22 23 24 25 26 27
LVPECL 				0  0  0  0  0  1
LVDS 				0  1  0  1  1  1
LVCMOS          	*  *  *  *  0  0
Output Disabled 	0  1  0  1  1  0

* Use Description for Bits 22,23,24 and 25 for setting the LVCMOS Outputs

Register n, n.26 & n.27 		 <----> (n <= 4), here 1.26 and 1.27
*/
CDCE62005Return cdce62005_set_output_type		(CDCE62005_Device 	*dev, 	int regNum,	OutputType 		output_type) {
	
	switch (regNum)
	{
		case 0: 
//			dev->Reg_0.OUTBUFSEL0 = output_type;
			BITBANG_SET_VALUE(REG0_OUTBUFSEL0, output_type);
			break;
		case 1:
//			dev->Reg_1.OUTBUFSEL1 = output_type;
			BITBANG_SET_VALUE(REG1_OUTBUFSEL1, output_type);
			break;
		case 2:
//			dev->Reg_2.OUTBUFSEL2 = output_type;
			BITBANG_SET_VALUE(REG2_OUTBUFSEL2, output_type);
			break;
		case 3:
//			dev->Reg_3.OUTBUFSEL3 = output_type;
			BITBANG_SET_VALUE(REG3_OUTBUFSEL3, output_type);
			break;
		case 4:
//			dev->Reg_4.OUTBUFSEL4 = output_type;
			BITBANG_SET_VALUE(REG4_OUTBUFSEL4, output_type);
			break;
		default: return CDCE62005_ERROR;
	}
	return CDCE62005_OK;	
}
// ------------------------------------------------------------------------------------------------------------------

// LVCMOS mode select for OUTPUT "3" Positive/Negative Pin.
// (X,Y)=00:Active, 10:Inverting, 11:Low, 01:3-State
CDCE62005Return cdce62005_set_LVCMOS_mode		(CDCE62005_Device 	*dev, 	int regNum,	LVCMOS_Mode 	lvcmos_mode) {
		
	switch (regNum)
	{
		case 0: 
//			dev->Reg_0.CMOSMODE0P = lvcmos_mode;
			BITBANG_SET_VALUE(REG0_CMOSMODE0P, lvcmos_mode);
//			dev->Reg_0.CMOSMODE0N = lvcmos_mode;
			BITBANG_SET_VALUE(REG0_CMOSMODE0N, lvcmos_mode);
			break;
		case 1:
//			dev->Reg_1.CMOSMODE1P = lvcmos_mode;
			BITBANG_SET_VALUE(REG1_CMOSMODE1P, lvcmos_mode);
//			dev->Reg_1.CMOSMODE1N = lvcmos_mode;
			BITBANG_SET_VALUE(REG1_CMOSMODE1N, lvcmos_mode);
			break;
		case 2:
//			dev->Reg_2.CMOSMODE2P = lvcmos_mode;
			BITBANG_SET_VALUE(REG2_CMOSMODE2P, lvcmos_mode);
//			dev->Reg_2.CMOSMODE2N = lvcmos_mode;
			BITBANG_SET_VALUE(REG2_CMOSMODE2N, lvcmos_mode);
			break;
		case 3:
//			dev->Reg_3.CMOSMODE3P = lvcmos_mode;
			BITBANG_SET_VALUE(REG3_CMOSMODE3P, lvcmos_mode);
//			dev->Reg_3.CMOSMODE3N = lvcmos_mode;
			BITBANG_SET_VALUE(REG3_CMOSMODE3N, lvcmos_mode);
			break;
		case 4:
//			dev->Reg_4.CMOSMODE4P = lvcmos_mode;
			BITBANG_SET_VALUE(REG4_CMOSMODE4P, lvcmos_mode);
//			dev->Reg_4.CMOSMODE4N = lvcmos_mode;
			BITBANG_SET_VALUE(REG4_CMOSMODE4N, lvcmos_mode);
			break;
		default: return CDCE62005_ERROR;
	}
	return CDCE62005_OK;
}
// ------------------------------------------------------------------------------------------------------------------

CDCE62005Return cdce62005_set_output_mux(CDCE62005_Device *dev, int output_port, OutputMux output_mux) {
	switch (output_port)
	{
		case 0: 
			BITBANG_SET_VALUE(REG0_OUTMUX0SEL, output_mux);
			//cdce62005_spi_write	(dev, &dev->reg0);
			break;
		case 1:
			BITBANG_SET_VALUE(REG1_OUTMUX1SEL, output_mux);
			//cdce62005_spi_write	(dev, &dev->reg1);
			break;
		case 2:
			BITBANG_SET_VALUE(REG2_OUTMUX2SEL, output_mux);
			//cdce62005_spi_write	(dev, &dev->reg2);
			break;
		case 3:
			BITBANG_SET_VALUE(REG3_OUTMUX3SEL, output_mux);
			//cdce62005_spi_write	(dev, &dev->reg3);
			break;
		case 4:
			BITBANG_SET_VALUE(REG4_OUTMUX4SEL, output_mux);
			////cdce62005_spi_write	(dev, &dev->reg4);
			break;
		default:
			assert(!"Invalid output port.");
			while(1);
	}

	return CDCE62005_OK;
}
// ------------------------------------------------------------------------------------------------------------------

// set output divider for each register from {1 to 80}
CDCE62005Return cdce62005_set_output_divider	(CDCE62005_Device 	*dev, 	int regNum,	OutputDivider 		output_div) {
	
	switch (regNum)
	{
		case 0: 
			BITBANG_SET_VALUE(REG0_OUT0DIVRSEL, output_div);
			//cdce62005_spi_write	(dev, &dev->reg0);
			break;
		case 1:
			BITBANG_SET_VALUE(REG1_OUT1DIVRSEL, output_div);
			//cdce62005_spi_write	(dev, &dev->reg1);
			break;
		case 2:
			BITBANG_SET_VALUE(REG2_OUT2DIVRSEL, output_div);
			//cdce62005_spi_write	(dev, &dev->reg2);
			break;
		case 3:
			BITBANG_SET_VALUE(REG3_OUT3DIVRSEL, output_div);
			//cdce62005_spi_write	(dev, &dev->reg3);
			break;
		case 4:
			BITBANG_SET_VALUE(REG4_OUT4DIVRSEL, output_div);
			//cdce62005_spi_write	(dev, &dev->reg4);
			break;
		default: return CDCE62005_ERROR;
	}
	return CDCE62005_OK;
}
// ------------------------------------------------------------------------------------------------------------------

// Enable Auxiliary Output when set to "1".
// Select the Output that will driving the AUX Output;
// Low for Selecting Output Divider "2" and High for Selecting Output Divider "3"
void cdce62005_aux_out_disable			(CDCE62005_Device 	*dev) {
//	dev->Reg_6.AUXOUTEN 		= 0;
	BITBANG_SET_VALUE(REG6_AUXOUTEN, 0);
//	dev->Reg_6.AUXFEEDSEL 	= 0;
	BITBANG_SET_VALUE(REG6_AUXFEEDSEL, 0);
}
// ------------------------------------------------------------------------------------------------------------------

// Enable Auxiliary Output when set to "1".
// Select the Output that will driving the AUX Output;
// Low for Selecting Output Divider "2" and High for Selecting Output Divider "3"


void cdce62005_aux_out_enable			(CDCE62005_Device 	*dev, 	int outputDivider) {
	switch (outputDivider)
	{
		case 2: 
//			dev->Reg_6.AUXOUTEN 		= 1;
			BITBANG_SET_VALUE(REG6_AUXOUTEN, 1);
//			dev->Reg_6.AUXFEEDSEL 	= 0;
			BITBANG_SET_VALUE(REG6_AUXFEEDSEL, 0);
			break;
		case 3:
//			dev->Reg_6.AUXOUTEN 		= 1;
			BITBANG_SET_VALUE(REG6_AUXOUTEN, 1);
//			dev->Reg_6.AUXFEEDSEL 	= 1;
			BITBANG_SET_VALUE(REG6_AUXFEEDSEL, 1);
			break;	
		default: 
//			dev->Reg_6.AUXOUTEN 		= 0;
			BITBANG_SET_VALUE(REG6_AUXOUTEN, 0);
//			dev->Reg_6.AUXFEEDSEL 	= 0;
			BITBANG_SET_VALUE(REG6_AUXFEEDSEL, 0);
	}
}
// ------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------

// set all the dividers (M, N, P, FB)

CDCE62005Return cdce62005_divider_init		(CDCE62005_Device 	*dev, 	int regNum, int inputDivider, OutputDivider 	output_div, FB_Divider 	fbRatio, FB_BypassDiv 	feedback_bypass_div, PreScaler 	pre_scaler) {
	if (regNum >= 0 && regNum <= 4) { 
		cdce62005_set_input_divider				(dev, inputDivider);
		cdce62005_set_output_divider			(dev, regNum, output_div);
		cdce62005_set_feedback_divider			(dev, fbRatio);
		cdce62005_set_feedback_bypass_divider	(dev, feedback_bypass_div);
		cdce62005_set_prescaler					(dev, pre_scaler);
	}
	else return CDCE62005_ERROR;
	return CDCE62005_OK;
}



// ------------------------------------------------------------------------------------------------------------------

// set all the loop filter components
void cdce62005_loop_filter_init		(CDCE62005_Device 	*dev, LF_C1 	c1, LF_C2 	c2, LF_C3 	c3, LF_R2 	r2, LF_R3 	r3) {
	cdce62005_set_LF_C1			(dev, c1);
	cdce62005_set_LF_C2 		(dev, c2);
	cdce62005_set_LF_C3 		(dev, c3);
	cdce62005_set_LF_R2	 		(dev, r2);
	cdce62005_set_LF_R3 		(dev, r3);
	BITBANG_SET_VALUE(REG6_EXLFSEL, 0);
}

// set the reference divider value
// was CDCE62005Return 	cdce62005_ref_divider		(SpiDevice spi_pll, CDCE62005_Device 	*dev, 	int		ref_divider)
CDCE62005Return 	cdce62005_ref_divider		(CDCE62005_Device 	*dev, 	int		ref_divider) {
	if (ref_divider > 8) {
		return CDCE62005_ERROR;
	}
	else {
		ref_divider--;
//		dev->Reg_2.REFDIV 		= ref_divider & 0x03;	
		BITBANG_SET_VALUE(REG2_REFDIV, (ref_divider & 0x03));
//		dev->Reg_3.REFDIV2 		= ref_divider & 0x04;
		BITBANG_SET_VALUE(REG3_REFDIV2, (ref_divider & 0x04));
//		dev->Reg_2.OUT2DIVSEL 	= 0;
		BITBANG_SET_VALUE(REG2_OUT2DIVSEL, 0);
//		dev->Reg_3.OUT3DIVSEL 	= 0;
		BITBANG_SET_VALUE(REG3_OUT3DIVSEL, 0);
		
		//cdce62005_spi_write	(dev, &dev->reg2);
		//cdce62005_spi_write	(dev, &dev->reg3);
	}
	return CDCE62005_OK;
}
// set the pre divider value for primary_reference signal
void cdce62005_pre_divider_pri_ref		(CDCE62005_Device 	*dev, 	PreDivider		pre_divider_primary) {
//	dev->Reg_0.DIV2PRI	=	pre_divider_primary;
	BITBANG_SET_VALUE(REG0_DIV2PRI, pre_divider_primary);
}
// set the pre divider value for secondary_reference signal
void cdce62005_pre_divider_sec_ref		(CDCE62005_Device 	*dev, 	PreDivider		pre_divider_secondary) {
//	dev->Reg_1.DIV2SEC	=	pre_divider_secondary;
	BITBANG_SET_VALUE(REG1_DIV2SEC, pre_divider_secondary);
}

void cdce62005_enable_output(CDCE62005_Device *dev, int output_port) {
	switch (output_port)
	{
		case 0:
			BITBANG_SET_VALUE(REG0_OUT0DIVSEL, 1);
			BITBANG_SET_VALUE(REG0_OUTBUFSEL0, _output_type_0);
			//cdce62005_spi_write	(dev, &dev->reg0);
			break;
			
		case 1:
			BITBANG_SET_VALUE(REG1_OUT1DIVSEL, 1);
			BITBANG_SET_VALUE(REG1_OUTBUFSEL1, _output_type_1);
			//cdce62005_spi_write	(dev, &dev->reg1);
			break;
			
		case 2:
			BITBANG_SET_VALUE(REG2_OUT2DIVSEL, 1);
			BITBANG_SET_VALUE(REG2_OUTBUFSEL2, _output_type_2);
			//cdce62005_spi_write	(dev, &dev->reg2);
			break;
			
		case 3:
			BITBANG_SET_VALUE(REG3_OUT3DIVSEL, 1);
			BITBANG_SET_VALUE(REG3_OUTBUFSEL3, _output_type_3);
			//cdce62005_spi_write	(dev, &dev->reg3);
			break;
			
		case 4:
			BITBANG_SET_VALUE(REG4_OUT4DIVSEL, 1);
			BITBANG_SET_VALUE(REG4_OUTBUFSEL4, _output_type_4);
			//cdce62005_spi_write	(dev, &dev->reg4);
			break;
			
		default:
			assert(!"Invalid output port.");
			while(1);
	}
}

void cdce62005_disable_output(CDCE62005_Device *dev, int output_port) {
	switch (output_port)
	{
		case 0:
			BITBANG_SET_VALUE(REG0_OUT0DIVSEL, 0);
			BITBANG_SET_VALUE(REG0_CMOSMODE0P, LVCMOS_Mode_3_State);
			BITBANG_SET_VALUE(REG0_CMOSMODE0N, LVCMOS_Mode_3_State);
			BITBANG_SET_VALUE(REG0_OUTBUFSEL0, OutputType_Disabled); 
			//cdce62005_spi_write	(dev, &dev->reg0);
			break;
	
		case 1:
			BITBANG_SET_VALUE(REG1_OUT1DIVSEL, 0);
			BITBANG_SET_VALUE(REG1_CMOSMODE1P, LVCMOS_Mode_3_State);
			BITBANG_SET_VALUE(REG1_CMOSMODE1N, LVCMOS_Mode_3_State);
			BITBANG_SET_VALUE(REG1_OUTBUFSEL1, OutputType_Disabled);
			//cdce62005_spi_write	(dev, &dev->reg1);
			break;
		
		case 2:
			BITBANG_SET_VALUE(REG2_OUT2DIVSEL, 0);
			BITBANG_SET_VALUE(REG2_CMOSMODE2P, LVCMOS_Mode_3_State);
			BITBANG_SET_VALUE(REG2_CMOSMODE2N, LVCMOS_Mode_3_State);
			BITBANG_SET_VALUE(REG2_OUTBUFSEL2, OutputType_Disabled);
			//cdce62005_spi_write	(dev, &dev->reg2);
			break;
			
		case 3:
			BITBANG_SET_VALUE(REG3_OUT3DIVSEL, 0);
			BITBANG_SET_VALUE(REG3_CMOSMODE3P, LVCMOS_Mode_3_State);
			BITBANG_SET_VALUE(REG3_CMOSMODE3N, LVCMOS_Mode_3_State);
			BITBANG_SET_VALUE(REG3_OUTBUFSEL3, OutputType_Disabled);
			//cdce62005_spi_write	(dev, &dev->reg3);
			break;
			
		case 4:
			BITBANG_SET_VALUE(REG4_OUT4DIVSEL, 0);
			BITBANG_SET_VALUE(REG4_CMOSMODE4P, LVCMOS_Mode_3_State);
			BITBANG_SET_VALUE(REG4_CMOSMODE4N, LVCMOS_Mode_3_State);
			BITBANG_SET_VALUE(REG4_OUTBUFSEL4, OutputType_Disabled);
			//cdce62005_spi_write	(dev, &dev->reg4);
			break;

		default:
			assert(!"Invalid output port.");
			while(1);
	}
}

void cdce62005_configure_output(CDCE62005_Device *dev, int output_port, OutputDivider output_divider, OutputType output_type, OutputMux output_mux) {
	switch (output_port)
	{
		case 0:
			BITBANG_SET_VALUE(REG0_OUT0DIVRSEL, output_divider);
			BITBANG_SET_VALUE(REG0_OUTBUFSEL0, output_type);
			BITBANG_SET_VALUE(REG0_OUTMUX0SEL, output_mux);
			_output_type_0 = output_type;
			
			if (output_type == OutputType_LVCMOS) {
				// set additional registers for LVCMOS outputs
				BITBANG_SET_VALUE(REG0_CMOSMODE0P, 0);
				BITBANG_SET_VALUE(REG0_CMOSMODE0N, 1);
			}
		
			//cdce62005_spi_write	(dev, &dev->reg0);
			break;
			
		case 1:
			BITBANG_SET_VALUE(REG1_OUT1DIVRSEL, output_divider);
			BITBANG_SET_VALUE(REG1_OUTBUFSEL1, output_type);
			BITBANG_SET_VALUE(REG1_OUTMUX1SEL, output_mux);
			_output_type_1 = output_type;
			
			if (output_type == OutputType_LVCMOS) {
				// set additional registers for LVCMOS outputs
				BITBANG_SET_VALUE(REG1_CMOSMODE1P, 0);
				BITBANG_SET_VALUE(REG1_CMOSMODE1N, 1);
			}
			
			//cdce62005_spi_write	(dev, &dev->reg1);
			break;
			
		case 2:
			BITBANG_SET_VALUE(REG2_OUT2DIVRSEL, output_divider);
			BITBANG_SET_VALUE(REG2_OUTBUFSEL2, output_type);
			BITBANG_SET_VALUE(REG2_OUTMUX2SEL, output_mux);
			_output_type_2 = output_type;
			//cdce62005_spi_write	(dev, &dev->reg2);
			
			if (output_type == OutputType_LVCMOS) {
				// set additional registers for LVCMOS outputs
				BITBANG_SET_VALUE(REG2_CMOSMODE2P, 0);
				BITBANG_SET_VALUE(REG2_CMOSMODE2N, 1);
			}
			break;
			
		case 3:
			BITBANG_SET_VALUE(REG3_OUT3DIVRSEL, output_divider);
			BITBANG_SET_VALUE(REG3_OUTBUFSEL3, output_type);
			BITBANG_SET_VALUE(REG3_OUTMUX3SEL, output_mux);
			_output_type_3 = output_type;
			
			if (output_type == OutputType_LVCMOS) {
				// set additional registers for LVCMOS outputs
				BITBANG_SET_VALUE(REG3_CMOSMODE3P, 0);
				BITBANG_SET_VALUE(REG3_CMOSMODE3N, 1);
			}
			
			//cdce62005_spi_write	(dev, &dev->reg3);
			break;
			
		case 4:
			BITBANG_SET_VALUE(REG4_OUT4DIVRSEL, output_divider);
			BITBANG_SET_VALUE(REG4_OUTBUFSEL4, output_type);
			BITBANG_SET_VALUE(REG4_OUTMUX4SEL, output_mux);
			_output_type_4 = output_type;
			
			if (output_type == OutputType_LVCMOS) {
				// set additional registers for LVCMOS outputs
				BITBANG_SET_VALUE(REG4_CMOSMODE4P, 0);
				BITBANG_SET_VALUE(REG4_CMOSMODE4N, 1);
			}
			
			//cdce62005_spi_write	(dev, &dev->reg4);
			break;
			
		default:
			assert(!"Invalid output port.");
			while(1);
	}
}

void cdce62005_write_config(CDCE62005_Device *dev) {
	/*cdce62005_reg0_remained_bits(dev);
	cdce62005_reg1_remained_bits(dev);
	cdce62005_reg2_remained_bits(dev);
	cdce62005_reg3_remained_bits(dev);
	cdce62005_reg4_remained_bits(dev);
	cdce62005_reg5_remained_bits(dev);
	cdce62005_reg6_remained_bits_pri(dev);
	cdce62005_reg6_remained_bits_sec(dev);
	cdce62005_reg7_remained_bits(dev);*/
	
	cdce62005_spi_write	(dev, &dev->reg0);
	cdce62005_spi_write	(dev, &dev->reg1);
	cdce62005_spi_write	(dev, &dev->reg2);
	cdce62005_spi_write	(dev, &dev->reg3);
	cdce62005_spi_write	(dev, &dev->reg4);
	cdce62005_spi_write	(dev, &dev->reg5);
	cdce62005_spi_write	(dev, &dev->reg6);
	cdce62005_spi_write	(dev, &dev->reg7);
	//cdce62005_spi_write	(dev, &dev->reg8);
	
	cdce62005_vco_calibration(dev);
}

void cdce62005_vco_calibration(CDCE62005_Device *dev) {
	BITBANG_SET_VALUE(REG6_ENCAL_MODE, 1);
	BITBANG_SET_VALUE(REG6_ENCAL, 0);
	cdce62005_spi_write(dev, &dev->reg6);
	BITBANG_SET_VALUE(REG6_ENCAL, 1);
	cdce62005_spi_write(dev, &dev->reg6);
}

uint8 cdce62005_pll_locked(CDCE62005_Device *dev) {
	uint32	temp;
	uint8	is_locked;
	cdce62005_spi_read(dev, 8, &temp);
	
	is_locked = (uint8)((temp >> BITBANG_REG8_PLLLOCKPIN_START_INDEX) & 0x00000001);
	return is_locked;
}

uint8 cdce62005_eeprom_locked(CDCE62005_Device *dev) {
	uint32	temp;
	uint8	is_locked;
	cdce62005_spi_read(dev, 7, &temp);
	
	is_locked = (uint8)((temp >> BITBANG_REG7_EPLOCK_START_INDEX) & 0x00000001);
	return is_locked;
}


CDCE62005Return cdce62005_set_cmos_mode_p(CDCE62005_Device *dev, int16 output_port, LVCMOS_Mode mode) {
	switch (output_port)
	{
		case 0: 
			BITBANG_SET_VALUE(REG0_CMOSMODE0P, mode);
			break;
		case 1:
			BITBANG_SET_VALUE(REG1_CMOSMODE1P, mode);
			break;
		case 2:
			BITBANG_SET_VALUE(REG2_CMOSMODE2P, mode);
			break;
		case 3:
			BITBANG_SET_VALUE(REG3_CMOSMODE3P, mode);
			break;
		case 4:
			BITBANG_SET_VALUE(REG4_CMOSMODE4P, mode);
			break;
		default: return CDCE62005_ERROR;
	}
	return CDCE62005_OK;
}

CDCE62005Return cdce62005_set_cmos_mode_n(CDCE62005_Device *dev, int16 output_port, LVCMOS_Mode mode) {
	switch (output_port)
	{
		case 0: 
			BITBANG_SET_VALUE(REG0_CMOSMODE0N, mode);
			break;
		case 1:
			BITBANG_SET_VALUE(REG1_CMOSMODE1N, mode);
			break;
		case 2:
			BITBANG_SET_VALUE(REG2_CMOSMODE2N, mode);
			break;
		case 3:
			BITBANG_SET_VALUE(REG3_CMOSMODE3N, mode);
			break;
		case 4:
			BITBANG_SET_VALUE(REG4_CMOSMODE4N, mode);
			break;
		default: return CDCE62005_ERROR;
	}
	return CDCE62005_OK;
}



CDCE62005Return cdce62005_output_divider_coarse_phase(CDCE62005_Device *dev, int16 output_port, int16 int_phase) {
	switch (output_port)
	{
		case 0: 
			BITBANG_SET_VALUE(REG0_PH0ADJC, int_phase);			
			break;
		case 1:
			BITBANG_SET_VALUE(REG1_PH1ADJC, int_phase);
			break;
		case 2:
			BITBANG_SET_VALUE(REG2_PH2ADJC, int_phase);
			break;
		case 3:
			BITBANG_SET_VALUE(REG3_PH3ADJC, int_phase);			
			break;
		case 4:
			BITBANG_SET_VALUE(REG4_PH4ADJC, int_phase);
			break;
		default: return CDCE62005_ERROR;
	}
	return CDCE62005_OK;
}




CDCE62005Return cdce62005_set_eeclksel(CDCE62005_Device *dev, EEClkSel sel) {
	BITBANG_SET_VALUE(REG5_EECLKSEL, sel);
	return CDCE62005_OK;
}

CDCE62005Return cdce62005_set_acdcsel(CDCE62005_Device *dev, ACDCSel sel) {
	BITBANG_SET_VALUE(REG5_ACDCSEL, sel);
	return CDCE62005_OK;
}

CDCE62005Return cdce62005_set_hysteresis(CDCE62005_Device *dev, Hysteresis sel)  {
	BITBANG_SET_VALUE(REG5_HYSTEN, sel);
	return CDCE62005_OK;
}

CDCE62005Return cdce62005_set_failsafe_mode(CDCE62005_Device *dev, FailSafeMode sel) {
	BITBANG_SET_VALUE(REG5_FAILSAFE, sel);
	return CDCE62005_OK;
}

CDCE62005Return cdce62005_set_sec_termsel(CDCE62005_Device *dev, TermSelMode sel) {
	BITBANG_SET_VALUE(REG6_SEC_TERMSEL, sel);
	return CDCE62005_OK;
}
