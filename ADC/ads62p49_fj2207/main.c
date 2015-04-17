#include <msp430fg4618.h>
#include <cdce62005.h>
#include <ads62p49.h>
#include <msp430fg4618.h>
#include <gpio_pin.h>
#include <hal.h>
#include "main.h"
#include <msp430_gpio.h>
#include <lcd_16x2.h>
#include <fj2207.h>
#include <dac8830.h>
//#include <fj2207v2.h>
#include "dvbt2_fifo.h"
#include <string.h>


Msp430GpioParamStruct	spi_miso_param				= {(uint16*)&P4OUT,  	(uint16*)&P4IN,  	(uint16*)&P4DIR,  	0x10,   Msp430GpioInput};
Msp430GpioParamStruct	spi_mosi_param				= {(uint16*)&P4OUT,  	(uint16*)&P4IN,  	(uint16*)&P4DIR,  	0x08,   Msp430GpioOutput};
Msp430GpioParamStruct	spi_sclk_param				= {(uint16*)&P4OUT,	 	(uint16*)&P4IN,  	(uint16*)&P4DIR,  	0x20,   Msp430GpioOutput};
Msp430GpioParamStruct	spi_pll_dev_1_ce_param		= {(uint16*)&P10OUT, 	(uint16*)&P10IN, 	(uint16*)&P10DIR, 	0x4000,	Msp430GpioOutput};
Msp430GpioParamStruct	spi_ads_dev_1_ce_param		= {(uint16*)&P9OUT, 	(uint16*)&P9IN, 	(uint16*)&P9DIR, 	0x40, 	Msp430GpioOutput};
Msp430GpioParamStruct	spi_ads_dev_1_reset_param	= {(uint16*)&P9OUT, 	(uint16*)&P9IN, 	(uint16*)&P9DIR, 	0x80, 	Msp430GpioOutput};
Msp430GpioParamStruct	spi_pll_dac_ce_param		= {(uint16*)&P7OUT, 	(uint16*)&P7IN, 	(uint16*)&P7DIR, 	0x80, 	Msp430GpioOutput};

Msp430GpioParamStruct	spi_msp_sw_0_param			= {(uint16*)&P1OUT, 	(uint16*)&P1IN, 	(uint16*)&P1DIR, 	0x08, 	Msp430GpioInput};
Msp430GpioParamStruct	spi_msp_sw_1_param			= {(uint16*)&P1OUT, 	(uint16*)&P1IN, 	(uint16*)&P1DIR, 	0x04, 	Msp430GpioInput};
Msp430GpioParamStruct	spi_msp_sw_2_param			= {(uint16*)&P1OUT, 	(uint16*)&P1IN, 	(uint16*)&P1DIR, 	0x02, 	Msp430GpioInput};
Msp430GpioParamStruct	spi_msp_sw_3_param			= {(uint16*)&P1OUT, 	(uint16*)&P1IN, 	(uint16*)&P1DIR, 	0x00, 	Msp430GpioInput};

Msp430GpioParamStruct	msp_led0_param				= {(uint16*)&P4OUT,  	(uint16*)&P4IN,  	(uint16*)&P4DIR,  	0x01,   Msp430GpioOutput};
Msp430GpioParamStruct	push_button0_n_param		= {(uint16*)&P1OUT,  	(uint16*)&P1IN,  	(uint16*)&P1DIR,  	0x01,   Msp430GpioInput};

//Tuner
Msp430GpioParamStruct	dac_cs_param				= {(uint16*)&P9OUT,  	(uint16*)&P9IN,  	(uint16*)&P9DIR,  	0x08,   Msp430GpioOutput};
Msp430GpioParamStruct	i2c_sda_param				= {(uint16*)&P3OUT,  	(uint16*)&P3IN,  	(uint16*)&P3DIR,  	0x02,   Msp430GpioOutput};
Msp430GpioParamStruct	i2c_scl_param				= {(uint16*)&P3OUT,  	(uint16*)&P3IN,  	(uint16*)&P3DIR,  	0x04,   Msp430GpioOutput};

// LCD
#if 0
Msp430GpioParamStruct	lcd_bit_0_param				= {(uint16*)&P2OUT,  	(uint16*)&P2IN,  	(uint16*)&P2DIR,  	0x01,   Msp430GpioOutput};
Msp430GpioParamStruct	lcd_bit_1_param				= {(uint16*)&P2OUT,  	(uint16*)&P2IN,  	(uint16*)&P2DIR,  	0x02,   Msp430GpioOutput};
Msp430GpioParamStruct	lcd_bit_2_param				= {(uint16*)&P2OUT,  	(uint16*)&P2IN,  	(uint16*)&P2DIR,  	0x04,   Msp430GpioOutput};
Msp430GpioParamStruct	lcd_bit_3_param				= {(uint16*)&P2OUT,  	(uint16*)&P2IN,  	(uint16*)&P2DIR,  	0x08,   Msp430GpioOutput};
#endif
Msp430GpioParamStruct	lcd_bit_4_param				= {(uint16*)&P2OUT,  	(uint16*)&P2IN,  	(uint16*)&P2DIR,  	0x10,   Msp430GpioOutput};
Msp430GpioParamStruct	lcd_bit_5_param				= {(uint16*)&P2OUT,  	(uint16*)&P2IN,  	(uint16*)&P2DIR, 	0x20,   Msp430GpioOutput};
Msp430GpioParamStruct	lcd_bit_6_param				= {(uint16*)&P2OUT,  	(uint16*)&P2IN,  	(uint16*)&P2DIR,  	0x40,   Msp430GpioOutput};
Msp430GpioParamStruct	lcd_bit_7_param				= {(uint16*)&P2OUT,  	(uint16*)&P2IN,  	(uint16*)&P2DIR,  	0x80,   Msp430GpioOutput};
Msp430GpioParamStruct	lcd_enable_param			= {(uint16*)&P3OUT,  	(uint16*)&P3IN,  	(uint16*)&P3DIR,  	0x10,   Msp430GpioOutput};
Msp430GpioParamStruct	lcd_rw_param				= {(uint16*)&P3OUT,  	(uint16*)&P3IN,  	(uint16*)&P3DIR,  	0x08,   Msp430GpioOutput};
Msp430GpioParamStruct	lcd_rs_param				= {(uint16*)&P3OUT,  	(uint16*)&P3IN,  	(uint16*)&P3DIR,  	0x01,   Msp430GpioOutput};


GpioPin				spi_miso			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_miso_param}; 
GpioPin				spi_mosi			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_mosi_param};
GpioPin				spi_sclk			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_sclk_param};
GpioPin				spi_pll_dev_1_ce	= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_pll_dev_1_ce_param};
GpioPin				spi_ads_dev_1_ce	= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_ads_dev_1_ce_param};
GpioPin				spi_ads_dev_1_reset	= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_ads_dev_1_reset_param};
GpioPin				spi_pll_dac_ce		= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_pll_dac_ce_param};

GpioPin				spi_msp_sw0			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_msp_sw_0_param};
GpioPin				spi_msp_sw1			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_msp_sw_1_param};
GpioPin				spi_msp_sw2			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_msp_sw_2_param};
GpioPin				spi_msp_sw3			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&spi_msp_sw_3_param};

GpioPin				msp_led0			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&msp_led0_param};
GpioPin				push_button0_n		= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&push_button0_n_param};

// LCD
#if 0
GpioPin				lcd_bit_0			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_bit_0_param}; 
GpioPin				lcd_bit_1			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_bit_1_param};
GpioPin				lcd_bit_2			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_bit_2_param};
GpioPin				lcd_bit_3			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_bit_3_param};
#endif
GpioPin				lcd_bit_4			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_bit_4_param}; 
GpioPin				lcd_bit_5			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_bit_5_param};
GpioPin				lcd_bit_6			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_bit_6_param};
GpioPin				lcd_bit_7			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_bit_7_param};
GpioPin				lcd_enable			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_enable_param};
GpioPin				lcd_rw				= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_rw_param};
GpioPin				lcd_rs				= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&lcd_rs_param};



//Tuner
GpioPin				dac_cs				= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&dac_cs_param};
GpioPin				i2c_sda			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&i2c_sda_param}; 
GpioPin				i2c_scl			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&i2c_scl_param};

//Handler
LcdHandle			lcd_handle;
CDCE62005_Device	pll_dev_1;
ADS62P49_Device		ads_dev_1;
CDCE62005Return		result;

//Tuner_handle
Fj2207Handle fj2207_h;
DAC_handle dac_handle;
I2cResponseType res;

void clock_init(void);
void SPI_Initialization(void);
void int2string(char* string, unsigned int integer);
void update_lcd (uint16 *data);

uint8 SPI_Data;
char buf[2];
uint8 flag = 0;
Msp430GpioParamStruct	debug_pin_param		= {(uint16*)&P7OUT,  	(uint16*)&P7IN,  	(uint16*)&P7DIR,  	0x10,   Msp430GpioOutput};
GpioPin				debug_pin			= {msp430_gpio_init, msp430_gpio_set, msp430_gpio_clear, msp430_gpio_toggle, msp430_gpio_get, msp430_gpio_configure_as_input, msp430_gpio_configure_as_output, msp430_gpio_set_highz, (void*)&debug_pin_param};

Fifo 			fifo_handle;
void wait() {
	double d = 0.1, e = 0.2;
	for (d = 0.0; d < 100.0; d+=0.01) {
		e+=d;
	}
}

#define DTMB

void main(void) {
	int32 i;
	uint8 temp;
	Fsm_state 		fsm_state = fsm_adc_outputs_enabled;
	
	uint16 			dac_ctrl_word;
	
	DAC_handle 		pll_dac;
			
	// disable watchdog timer
	WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
	_BIS_SR(OSCOFF + SCG0 + GIE);             // Disable LFXT1 xtal osc & FLL loop
	
	FLL_CTL1 &= ~XT2OFF;                      // Activate XT2 high freq xtal
	
// Wait for xtal to stabilize
	do {
		IFG1 &= ~OFIFG;                       // Clear OSCFault flag
		for (i = 5; i > 0; i--);              // Time for flag to set
	}
	while ((IFG1 & OFIFG));                   // OSCFault flag still set?
	
	FLL_CTL1 |= SELM1;                        // MCLK = XT2

	gpio_pin_init(&spi_msp_sw0);
	
	while (0) {
		temp = gpio_pin_get(&spi_msp_sw0);
	}
	temp++;

	/*
	 * CONFIGURE GPIO PINS
	 */
	gpio_pin_init(&spi_sclk);
	gpio_pin_init(&spi_mosi);
	gpio_pin_init(&spi_miso);
	gpio_pin_init(&spi_pll_dev_1_ce);
	gpio_pin_init(&spi_pll_dac_ce);

	gpio_pin_init(&spi_ads_dev_1_ce);
	gpio_pin_init(&spi_ads_dev_1_reset);
	
	gpio_pin_init(&msp_led0);
	gpio_pin_init(&push_button0_n);
	gpio_pin_init(&debug_pin);
	
	dac_spi_init( &pll_dac , &spi_sclk, &spi_mosi, &spi_pll_dac_ce);
	dac_ctrl_word = 32768; //35000
	dac_write_word( &pll_dac, dac_ctrl_word);
	
	while(0) {
		dac_write_word( &pll_dac, dac_ctrl_word);
 		dac_ctrl_word += 1000;
		if(dac_ctrl_word > 60000) {
			dac_ctrl_word = 0;
		}	
	} 
  
	
		/*
		 * INITIALIZE LCD
		 */
		 #if 1
		//lcd_init(&lcd_handle, &lcd_rs, &lcd_rw, &lcd_enable, &lcd_bit_0, &lcd_bit_1, &lcd_bit_2, &lcd_bit_3, &lcd_bit_4, &lcd_bit_5, &lcd_bit_6, &lcd_bit_7, Lcd8BitMode);
		lcd_init(&lcd_handle, &lcd_rs, &lcd_rw, &lcd_enable, NULL, NULL, NULL, NULL, &lcd_bit_4, &lcd_bit_5, &lcd_bit_6, &lcd_bit_7, Lcd4BitMode);
		lcd_write_kt_logo(&lcd_handle, 1);
		lcd_write_string(&lcd_handle, "Kommunikations", 2, 3);
		__delay_cycles(16000000);
		lcd_write_string(&lcd_handle, "              ", 2, 3);
		lcd_write_string(&lcd_handle, "Technik", 2, 5);
		for (i = 2002; i <= 2014; ++i) {
		lcd_write_unsigned_number(&lcd_handle, i, 4, 2, 13, LcdLeadingZerosOff);
			__delay_cycles(1500000);
		}
		__delay_cycles(1500000);
		lcd_write_cmd(&lcd_handle, LCD_16X2_COMMAND_CLEAR_DISPLAY);
		lcd_write_kt_logo(&lcd_handle, 1);
		lcd_write_string(&lcd_handle, "Spectrum Sensing", 1, 1);
		lcd_write_string(&lcd_handle, "DEMO", 2, 1);
		//lcd_write_cmd(&lcd_handle, LCD_16X2_COMMAND_CLEAR_DISPLAY);
		
		//DISPLAY SFO & CFO
		//lcd_write_string(&lcd_handle, "CFO:", 2, 1);
		//__delay_cycles(16000000);
		//lcd_write_string(&lcd_handle, "  ", 2, 7);
		//lcd_write_string(&lcd_handle, "SFO:", 2, 9);
		//lcd_write_string(&lcd_handle, "Hz", 2, 15);
		//__delay_cycles(15000000);
		//lcd_write_cmd(&lcd_handle, LCD_16X2_COMMAND_CLEAR_DISPLAY);
		//lcd_write_string(&lcd_handle, "BER:", 1, 1);
		//lcd_write_string(&lcd_handle, ".", 1, 6);
		//lcd_write_string(&lcd_handle, "e-", 1, 9);
		//__delay_cycles(16000000);
		//lcd_write_cmd(&lcd_handle, LCD_16X2_COMMAND_CLEAR_DISPLAY);
		
	SPI_Initialization();                     // Initialize SPI
		#endif
	
	/*
	 * CONFIGURE CDCE62005
	 */
	cdce62005_init(&pll_dev_1, &spi_sclk, &spi_mosi, &spi_miso, &spi_pll_dev_1_ce);
	#if 0
	cdce62005_basic_pll_setup(&pll_dev_1, PrescalerOutputFreq1024MHz);
	cdce62005_configure_output(&pll_dev_1, 0, OutPutDivider_28, OutputType_LVDS, OutputMux_VCO_Core);
	cdce62005_configure_output(&pll_dev_1, 1, OutPutDivider_28, OutputType_LVCMOS, OutputMux_VCO_Core);
	#else
//	cdce62005_basic_pll_setup(&pll_dev_1, PrescalerOutputFreq640MHz);
//	cdce62005_configure_output(&pll_dev_1, 0, OutPutDivider_64, OutputType_LVDS, OutputMux_VCO_Core);

	// For DTMB System - Symbol Rate-7.5MHz * OSR-2 = 15MSPS 	= Prescaler Output Frequency-720MHz / OutPutDivider_48
	// For DTMB System - Symbol Rate-7.5MHz * OSR-3 = 22.5MSPS 	= Prescaler Output Frequency-720MHz / OutPutDivider_32
	cdce62005_basic_pll_setup(&pll_dev_1, PrescalerOutputFreq720MHz);
	cdce62005_configure_output(&pll_dev_1, 0, OutPutDivider_32, OutputType_LVDS, OutputMux_VCO_Core);

	#endif
	
	cdce62005_enable_output(&pll_dev_1, 0);
	cdce62005_enable_output(&pll_dev_1, 1);
	cdce62005_write_config(&pll_dev_1);
	
	/*
	 * CONFIGURE ADC
	 */
		
	ads62p49_init				(&ads_dev_1, &spi_sclk, &spi_mosi, &spi_miso, &spi_ads_dev_1_ce, &spi_ads_dev_1_reset);
	ads62p49_set_low_speed_mode	(&ads_dev_1, LowSpeedMode_Enable);
	ads62p49_set_lvds_cmos		(&ads_dev_1, InterfaceMode_LVDS);
	//ads62p49_set_power_down_mode(&ads_dev_1, PowerDownMode_Normal); // open channel A and B
	ads62p49_set_power_down_mode(&ads_dev_1, PowerDownMode_ChB_Standby);
	//ads62p49_set_clk_edge_ctl	(&ads_dev_1, CLKOUT_RisingEdgeShift_4_26Ts_N, CLKOUT_FallingEdgeShift_4_26Ts_P);
	//ads62p49_set_clk_edge_ctl	(&ads_dev_1, CLKOUT_RisingEdgeShift_4_26Ts_P, CLKOUT_FallingEdgeShift_4_26Ts_N);
	//ads62p49_set_clk_edge_ctl	(&ads_dev_1, CLKOUT_RisingEdgeShift_Default_100, CLKOUT_FallingEdgeShift_Default_100);
	ads62p49_set_channel_control(&ads_dev_1, ChannelCtl_Independent, DataFormat_OffsetBinary);
		
	//ads62p49_set_custom_pattern	(&ads_dev_1, 0x2AAA);
	ads62p49_set_test_mode		(&ads_dev_1, ADS62P49_CHANNEL_A, TestPattern_Normal);
	//ads62p49_set_test_mode		(&ads_dev_1, ADS62P49_CHANNEL_B, TestPattern_Ramp);
	ads62p49_set_offset_correction (&ads_dev_1, CH_A, OffsetCorrection_Enable);
	ads62p49_set_gain			   (&ads_dev_1, CH_A, Gain_0dB);
	ads62p49_set_offset_corr_time  (&ads_dev_1, CH_A, OffsetCorrectionTime_512M);
	ads62p49_set_offset_pedestal   (&ads_dev_1,	CH_A, OffsetPedestal_0_LSB_P);
	
	//ads62p49_set_offset_correction (&ads_dev_1, CH_B, OffsetCorrection_Enable);
	//ads62p49_set_gain			   (&ads_dev_1, CH_B, Gain_0dB);
	//ads62p49_set_offset_corr_time  (&ads_dev_1, CH_B, OffsetCorrectionTime_512M);
	//ads62p49_set_offset_pedestal   (&ads_dev_1,	CH_B, OffsetPedestal_0_LSB_P);
	
	
	gpio_pin_set_highz(&spi_sclk);
	gpio_pin_set_highz(&spi_mosi);
	gpio_pin_set_highz(&spi_pll_dac_ce);
	
	
	/*
	 *  Enable LED
	 */
	gpio_pin_set(&msp_led0);
	
		
	/*
	 * Tuner
	 */
	fj2207_init(&fj2207_h, &i2c_sda, &i2c_scl);
 	fj2207_set(&fj2207_h, 400000000, 5000000);
 	
 	uint32 rf_frequency_new;
 	uint32 temp_new;
 	
 	rf_frequency_new = 400000000;
 	temp_new = rf_frequency_new/1000;
	rf_frequency_new = temp_new & 0xFF;
	fj2207_write_byte_register(&fj2207_h, rf_frequency_new, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_2);
	rf_frequency_new = temp_new & 0xFF00;
	rf_frequency_new >>= 8;
	fj2207_write_byte_register(&fj2207_h, rf_frequency_new, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_3);
	rf_frequency_new = temp_new & 0xF0000;
	rf_frequency_new >>= 16;
	fj2207_write_byte_register(&fj2207_h, rf_frequency_new, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_1);

	fj2207_write_byte_register(&fj2207_h, 0x41, FJ2207_CHIP_ADDRESS, MSM_Byte_1); 
	fj2207_write_byte_register(&fj2207_h, 0x01, FJ2207_CHIP_ADDRESS, MSM_Byte_2);
	
	
	fj2207_write_byte_register(&fj2207_h, 0x01, FJ2207_CHIP_ADDRESS, MSM_Byte_1); 
	fj2207_write_byte_register(&fj2207_h, 0x01, FJ2207_CHIP_ADDRESS, MSM_Byte_2); 	
 	
 	SPI_Initialization();                     // Initialize SPI
 	
	//res = fj2207_init(&fj2207_h,  &dac_handle, &i2c_sda, &i2c_scl, &spi_sclk, &spi_mosi, &dac_cs);
	//res = fj2207_set(&fj2207_h, 200000000, 5000000); //RF-->200M;IF -->5M
    fifo_init(&fifo_handle);                                        
	while(1)
	{
		
		_BIS_SR(GIE);
		//int2string(buf,(SPI_Data&0x3F));
		
		if (fifo_handle.numElements >= NUM_TOTAL_ELEMENTS) {	
			fifo_pop(&fifo_handle);	
			//memcpy(&temp2,fifo_handle.fifoBuffer,NUM_TOTAL_ELEMENTS*DATA_SIZE);	
			update_lcd (fifo_handle.fifoBuffer);
		} 
		
		while(0){
			/*			
			update_lcd (0x3F);		
			update_lcd (0x7F);			
			update_lcd (0xB0);
			update_lcd (0xF0);
			update_lcd (0x02);
			update_lcd (0x53);*/
		}
		
		//_BIS_SR(LPM0_bits + GIE);               // Enter LPM0 w/ interrupt        
	                                            // Remain in LPM0 until master
	                                            // finishes TX
	    //_NOP();                                 // Set breakpoint >>here<< and read
	                                            // read out the UART_Data and 
                                                // SPI_Data variables
                                          
		if (fsm_state == fsm_adc_outputs_enabled) {
			if (gpio_pin_get(&push_button0_n) == 0) {
				// disable outputs
				ads62p49_set_power_down_mode(&ads_dev_1, PowerDownMode_OutBuffDis_ChAB);
				
				// disable LED
				gpio_pin_clear(&msp_led0);
				
				// set next state
				fsm_state = fsm_adc_outputs_disabled;
				
				wait();
			}
		} else if (fsm_state == fsm_adc_outputs_disabled) {
			if (gpio_pin_get(&push_button0_n) == 0) {
				// disable outputs
				ads62p49_set_power_down_mode(&ads_dev_1, PowerDownMode_Normal);
				
				// enable LED
				gpio_pin_set(&msp_led0);
				
				// set next state
				fsm_state = fsm_adc_outputs_enabled;
				
				wait();
			}
		}
	}				
}


void clock_init(void) {
	int i;
	_BIS_SR(OSCOFF + SCG0 + GIE);             // Disable LFXT1 xtal osc & FLL loop
	
	FLL_CTL1 &= ~XT2OFF;                      // Activate XT2 high freq xtal
	
	// Wait for xtal to stabilize
	do {
		IFG1 &= ~OFIFG;                       // Clear OSCFault flag
		for (i = 5; i > 0; i--);              // Time for flag to set
	}
	while ((IFG1 & OFIFG));                   // OSCFault flag still set?
	
	FLL_CTL1 |= SELM1;                        // MCLK = XT2
}

void SPI_Initialization(void){
 //P5OUT = 0x02;                             // P5 setup for LED and slave reset
 //P5DIR |= 0x02;                            //
  //while(!(P7IN&0x08));                      // If clock sig from mstr stays low,
                                            // it is not yet in SPI mode
  P7SEL |= 0x0F;                            // P3.3,2,1 option select
  UCA0CTL1 = UCSWRST;                       // **Put state machine in reset**
  UCA0CTL0 |= UCSYNC+UCMSB+UCMODE_2; // 3-pin, 8-bit SPI master //UCCKPL
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_B0 RX interrupt
  
  //P7OUT |= 0x02;                // Load TX buffer
}

void int2string(char* string, unsigned int integer){
	//if (integer < 999) {
		string[2] = 48 + integer%10;
		string[1] = 48 + (integer/10)%10;
		string[0] = 48 + (integer/100)%10;
	/*}else{		
		string[0] = 105;
		string[1] = 110;
		string[2] = 102;
	}*/
}
#if 0
void update_lcd ( uint8 *data){
	//gpio_pin_set(&debug_pin);
	char string[3];
	uint16 temp,temp2;
	uint16 combine;
	uint16* data16;
	//temp = data&0x3F;		
	//int2string(string,temp);
	//for (i=0;i<NUM_TOTAL_ELEMENTS;i++){
		//temp = data[i]&0x3F;
		/*temp = (data[0]<<8)&(0xFF00);
		temp2 = (data[1])&(0x00FF);	
		combine = (temp | temp2) & 0x3FFF;*/	
		data16 = (uint16*)data;
		combine = *data16 & 0x3FFF;
		int2string(string,combine);		
		switch ( (*data16>>14) ){
		    	case 0://CFO	    
		    		if (combine<999)			    					    			
		    			lcd_write_unsigned_number(&lcd_handle, combine, 3, 2, 5, LcdLeadingZerosOn);
		    			//lcd_write_string(&lcd_handle, string, 2, 5);
		    		else
		    			lcd_write_string(&lcd_handle, "inf", 2, 5);
		    		break;	    		
		    	case 1://SFO
		    		if (combine<999)
		    			lcd_write_unsigned_number(&lcd_handle, combine, 3, 2, 13, LcdLeadingZerosOn);
		    			//lcd_write_string(&lcd_handle, string, 2, 13);
		    		else
		    			lcd_write_string(&lcd_handle, "inf", 2, 13);
		    		break;
		    	case 2://BER_low
		    		if (combine<999)
		    			lcd_write_unsigned_number(&lcd_handle, combine%100, 1, 1, 11, LcdLeadingZerosOff);
		    			//lcd_write_string(&lcd_handle, string, 1, 12);
		    		else
		    			lcd_write_string(&lcd_handle, "   ", 1, 11);
		    		break;	 
		    	case 3: //BER_high
		    		if (combine<999){ 
		    			lcd_write_unsigned_number(&lcd_handle, combine/100, 1, 1, 5, LcdLeadingZerosOff);
		    			lcd_write_unsigned_number(&lcd_handle, combine%100, 2, 1, 7, LcdLeadingZerosOn);	 	
		    			//lcd_write_unsigned_number(&lcd_handle, combine/100, 1, 1, 5, 0);
						//lcd_write_unsigned_number(&lcd_handle, combine%100, 2, 1, 7, 0);	
		    		}else{
		    			lcd_write_string(&lcd_handle, " ", 1, 5);
						lcd_write_string(&lcd_handle, "  ", 1, 7);	
		    		}    		
		    		break;	
				}
	    //}	    
		//gpio_pin_clear(&debug_pin);
}
#endif

void update_lcd ( uint16 data[NUM_PARAMETERS]){
	//gpio_pin_set(&debug_pin);
	char 	string[3];
	uint8	i;
	for (i=0; i<NUM_PARAMETERS ; i++){
		uint16 combine;
		combine = data[i] & 0x3FFF;
		int2string(string,combine);
		switch ( data[i]>>14 ){
		    	case 0://CFO	    
		    		if (combine<999)			    					    			
		    			lcd_write_unsigned_number(&lcd_handle, combine, 3, 2, 5, LcdLeadingZerosOn);
		    			//lcd_write_string(&lcd_handle, string, 2, 5);
		    		else
		    			lcd_write_string(&lcd_handle, "inf", 2, 5);
		    		break;	    		
		    	case 1://SFO
		    		if (combine<999)
		    			lcd_write_unsigned_number(&lcd_handle, combine, 3, 2, 13, LcdLeadingZerosOn);
		    			//lcd_write_string(&lcd_handle, string, 2, 13);
		    		else
		    			lcd_write_string(&lcd_handle, "inf", 2, 13);
		    		break;
		    	case 2://BER_low
		    		if (combine<999)
		    			lcd_write_unsigned_number(&lcd_handle, combine%100, 1, 1, 11, LcdLeadingZerosOff);
		    			//lcd_write_string(&lcd_handle, string, 1, 12);
		    		else
		    			lcd_write_string(&lcd_handle, "   ", 1, 11);
		    		break;	 
		    	case 3: //BER_high
		    		if (combine<999){ 
		    			lcd_write_unsigned_number(&lcd_handle, combine/100, 1, 1, 5, LcdLeadingZerosOff);
		    			lcd_write_unsigned_number(&lcd_handle, combine%100, 2, 1, 7, LcdLeadingZerosOn);	 	
		    			//lcd_write_unsigned_number(&lcd_handle, combine/100, 1, 1, 5, 0);
						//lcd_write_unsigned_number(&lcd_handle, combine%100, 2, 1, 7, 0);	
		    		}else{
		    			lcd_write_string(&lcd_handle, " ", 1, 5);
						lcd_write_string(&lcd_handle, "  ", 1, 7);	
		    		}    		
		    		break;	
				}
	}
    //}	    
	//gpio_pin_clear(&debug_pin);
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR(void)
{	
	//flag = 1;
	if(IFG2&UCA0RXIFG){		
	    SPI_Data = UCA0RXBUF; 
	    if (!fifo_full(&fifo_handle)) { 
	    	fifo_push(&fifo_handle, SPI_Data) ;	    	
	    }
	    
	                   // Store RX'ed SPI data		    
	    //lcd_write_cmd(&lcd_handle, LCD_16X2_COMMAND_CLEAR_DISPLAY);
	    //lcd_write_string(&lcd_handle, buf, 1, 5);
	    //lcd_write_string(&lcd_handle, "  ", 2, 13);
	    
	     	
	}
}

