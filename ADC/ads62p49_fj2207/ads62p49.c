#include "ads62p49.h"

static ADS62P49_Device *_active_dev;

// Delay Function for Spi Clock --------------------------------------------------------------
void ads62p49_delay_function(void) {
	int i;
	int j = 0;
	for (i = 0; i < SPI_DEFAULT_WAIT_COUNTER_MAX; ++i) {
		j++;
	}
}

/* --- Internal functions declarations --- */
static void		_write_byte(uint8_t data);
uint8	temp_gain = 0;


void ads62p49_init(ADS62P49_Device 	*dev, 	GpioPin *spi_sclk, 	GpioPin *spi_mosi, 	GpioPin *spi_miso, GpioPin *spi_chip_enable, GpioPin *ads_reset) {
	dev->miso 	= spi_miso;
	dev->mosi 	= spi_mosi;
	dev->sclk 	= spi_sclk;
	dev->ce		= spi_chip_enable;
	dev->reset	= ads_reset;
	
	// reset device
	gpio_pin_set	(dev->reset);
	ads62p49_delay_function();
	gpio_pin_clear	(dev->reset);
}

// --------------------------------------------------------------------------------------------------------------------
// Reading 32-bit Data -----------
void ads62p49_spi_read 	(ADS62P49_Device 	*dev, 	const 	uint16 	regBaseAddr, 		uint8 *data) {

/*	
	set_serial_readout(ads_number, SDOUT_Enable);
	ads_number->reg_00.RESET	= 0;
	ads_number->reg_00.D1_D6	= 0;
	ads62p49_Spi_Write(spi_ads, REG_00, *ToUint8Ptr(ads_number->reg_00));
*/	
	int 			i;
	unsigned char 	result = 0;
	unsigned char 	read_instruction = 0x00;
	read_instruction |= regBaseAddr;

	_active_dev = dev;
	
	// set bit 0 of register 0x00 to 1 to enable serial readout
	ads62p49_spi_write(dev, 0x00, 0x01);

// -----------------------
	gpio_pin_set(_active_dev->sclk); // Added -----
///	spi_sclk_down(_activeDev); // Added -----
	
	ads62p49_spi_chip_enable(dev, 0);

	_write_byte(read_instruction);
	
//	spi_ce_set(dev);
// ------------------------
//	spi_sclk_up(dev);
	
//	spi_ce_clear(dev);

//	if (portPin_read(_activeDev.spi_miso)) {
//		result |= 1;
//	}
	for (i = 0; i < 8; i++ ) {
//		spi_mosi_up(dev);
		gpio_pin_clear(_active_dev->sclk);
		result = (result << i); // added
		if (gpio_pin_get(_active_dev->miso)) {
//			result |= ((long int)1<<(i));
			result |= 1;
		}
		gpio_pin_set(_active_dev->sclk);
	}
	ads62p49_spi_chip_enable(dev, 1);
	
	// set bit 0 of register 0x00 to 0 to disable serial readout
	ads62p49_spi_write(dev, 0x00, 0x00);
	
	*data = result;
}
// --------------------------------------------------------------------------------------------------------------------
// Writing 32-bit Data -----------
void ads62p49_spi_write	(ADS62P49_Device 	*dev, 	const 	uint16 	regBaseAddr, 		const uint8 data) {
	
/*	
	set_serial_readout(dev, SDOUT_Disable);
	ads_number->reg_00.D1_D6	= 0;
	ads62p49_Spi_Write(spi_ads, REG_00, *ToUint8Ptr(ads_number->reg_00));
	ads_number->reg_62.TEST_PATTERN_CHA	 = 3;	
	ads_number->reg_62.D3_D7	= 0;
	ads62p49_Spi_Write(spi_ads, REG_62, *ToUint8Ptr(ads_number->reg_62));
	
	set_serial_readout(ads_number, SDOUT_Disable);
	ads62p49_Spi_Write(spi_ads, REG_00, *ToUint8Ptr(ads_number->reg_00));
	ads62p49_Spi_Write(spi_ads, regBaseAddr, *ToUint8Ptr(data));
*/	
	
	unsigned char 	data_to_send = 0x00;
	unsigned char 	addr_to_send = 0x00;
	addr_to_send |= regBaseAddr;
	data_to_send |= data;
	
	_active_dev = dev;

	gpio_pin_set(_active_dev->sclk); // Added -----
///	spi_sclk_down(_activeDev); // Added -----
	
// write address to the AD -------
	ads62p49_spi_chip_enable(dev, 0);
	
	_write_byte(addr_to_send);
	
//	spi_ce_set(dev);

// write data to the AD -----------
//	spi_ce_clear(dev);

	_write_byte(data_to_send);

///	spi_sclk_down	(_activeDev); // Added -----
///	spi_sclk_up		(_activeDev); // Added -----

	ads62p49_spi_chip_enable(dev, 1);
}
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// writing one byte through spi
void _write_byte(uint8_t data) {
	int i;
//	if (_active_dev.spiMode == SPI_SDIO) {
//		portPin_setAsOutput(_active_dev.spi_mosi);
//	}

	for (i = 0; i < 8; i++)	{
//		spi_sclk_down(_activeDev);	
		if (data & 0x80) {
///		if (data & 0x01) {
			gpio_pin_set(_active_dev->mosi);
		} else {
			gpio_pin_clear(_active_dev->mosi);
		}
		gpio_pin_clear(_active_dev->sclk);
		ads62p49_delay_function();
		gpio_pin_set(_active_dev->sclk);
///		spi_sclk_up(_activeDev);
///		delayFunction();
///		spi_sclk_down(_activeDev);
		
		
// shift byte left, so that we can send the next bit
		data <<= 1;
///		data >>= 1;
	}
}


void ads62p49_spi_chip_enable	(ADS62P49_Device 	*dev, uint8 value) {
	if (value == 0) {
		gpio_pin_clear(dev->ce);
	} else {
		gpio_pin_set(dev->ce);
	}
}


void ads62p49_set_low_speed_mode			(ADS62P49_Device 	*ads_number, 	LowSpeedMode 	low_speed_mode) {
	uint8 temp = 0;
	temp = temp | (low_speed_mode << 2);
	ads62p49_spi_write(ads_number, 0x20, temp);	
}

/*
void set_custom_pattern_low		(ADS62P49_Device 	*ads_number,	uint8	custom_pattern_low_data) {
	ads62p49_spi_write(ads_number, REG_51, custom_pattern_low_data);
}

void set_custom_pattern_high	(ADS62P49_Device 	*ads_number,	uint8	custom_pattern_high_data) {
	uint8 temp = 0;
	temp = temp | (custom_pattern_high_data & 0x3F);
	ads62p49_spi_write(ads_number, REG_52, temp);
}
*/
ADS62P49Return 	ads62p49_set_custom_pattern	(ADS62P49_Device 	*ads_number,	uint16			custom_pattern_data) {
	uint16 	data_backup = custom_pattern_data;
	uint8 	temp 		= 0;
	if (custom_pattern_data < 16384) {
		temp = custom_pattern_data;
		ads62p49_spi_write(ads_number, 0x51, temp);
		data_backup = (custom_pattern_data >> 8);
		temp = data_backup;
		ads62p49_spi_write(ads_number, 0x52, temp);
	}	
	else return ADS62P49_ERROR;	
	return ADS62P49_OK;
}


void ads62p49_set_test_mode(ADS62P49_Device *dev, ADS62P49_CHSEL channel, TestPattern test_pattern) {
	if (channel == ADS62P49_CHANNEL_A) {
		ads62p49_spi_write(dev, 0x62, test_pattern & 0x07);
	} else {
		ads62p49_spi_write(dev, 0x75, test_pattern & 0x07);
	}
}

void ads62p49_set_lvds_cmos				(ADS62P49_Device 	*ads_number,	InterfaceMode	lvds_cmos) {
	uint8 temp = 0;
	temp = temp | ((lvds_cmos << 7) & 0x80);
	ads62p49_spi_write(ads_number, 0x41, temp);
}

void ads62p49_set_power_down_mode		(ADS62P49_Device 	*ads_number, 	PowerDownMode 	power_down_mode) {
	uint8 temp = 0;
	temp = temp | (power_down_mode & 0x0F);
	ads62p49_spi_write(ads_number, 0x40, temp);	
}

void ads62p49_set_clk_edge_ctl	(ADS62P49_Device 	*ads_number,	CLKOUT_RisingEdgeShift	clkout_rising_edge_shift, CLKOUT_FallingEdgeShift clkout_falling_edge_shift) {
	uint8 temp = 0;
	temp = temp | ((clkout_rising_edge_shift << 5) & 0xFC);
	temp = temp | ((clkout_falling_edge_shift << 2) & 0xFC);
	ads62p49_spi_write(ads_number, 0x44, temp);
}

void ads62p49_soft_reset(ADS62P49_Device *dev) {
	ads62p49_spi_write(dev, 0x00, 0x00);			
	ads62p49_spi_write(dev, 0x00, 0x80);
	ads62p49_spi_write(dev, 0x00, 0x00);
}

void ads62p49_set_channel_control(ADS62P49_Device *dev, ChannelCtl channel_control, DataFormat data_format) {
	uint8 temp = 0;
	temp |= channel_control << 6;
	temp |= data_format << 1;
	ads62p49_spi_write(dev, 0x50, temp);
} 
/*
void ads62p49_set_gain_offset_time (ADS62P49_Device *ads_number, ADS_Channel	ads_channel, Gain gain, OffsetCorrectionTime offset_correction_time){
	uint8 gain_temp = 0;
	uint8 offset_time = 0;
	uint8 temp = 0;
	
	gain_temp 		= ((gain << 4) & 0xF0);
	offset_time 	= ((offset_correction_time) & 0x0F);
	temp = gain_temp | offset_time;
	
	if ( ads_channel == CH_A ){
		ads62p49_spi_write(ads_number, 0x55, temp);
	} else {
		ads62p49_spi_write(ads_number, 0x68, temp);
	}	
}
*/

void ads62p49_set_gain(ADS62P49_Device *ads_number, ADS_Channel	ads_channel, Gain gain){
	temp_gain = ((gain << 4) & 0xF0);
	if ( ads_channel == CH_A ){
		ads62p49_spi_write(ads_number, 0x55, temp_gain);
	} else {
		ads62p49_spi_write(ads_number, 0x68, temp_gain);
	}
}


void ads62p49_set_offset_correction	(ADS62P49_Device *ads_number, ADS_Channel ads_channel, OffsetCorrection offset_correction){
	uint8 temp = 0;
	temp = temp | ((offset_correction << 6) & 0x40);
	if ( ads_channel == CH_A ){
		ads62p49_spi_write(ads_number, 0x53, temp);
	} else {
		ads62p49_spi_write(ads_number, 0x66, temp);
	}
}


void ads62p49_set_offset_corr_time (ADS62P49_Device *ads_number, ADS_Channel ads_channel, OffsetCorrectionTime offset_correction_time){
	uint8 temp = 0;
	temp = temp_gain | ((offset_correction_time) & 0x0F);
	if ( ads_channel == CH_A ){
		ads62p49_spi_write(ads_number, 0x55, temp);
	} else {
		ads62p49_spi_write(ads_number, 0x68, temp);
	}
}


void ads62p49_set_offset_pedestal (ADS62P49_Device *ads_number,	ADS_Channel	ads_channel, OffsetPedestal	offset_pedestal){
	uint8 temp = 0;
	temp = temp | ((offset_pedestal) & 0x3F);
	if ( ads_channel == CH_A ){
		ads62p49_spi_write(ads_number, 0x63, temp);
	} else {
		ads62p49_spi_write(ads_number, 0x76, temp);
	}
}
