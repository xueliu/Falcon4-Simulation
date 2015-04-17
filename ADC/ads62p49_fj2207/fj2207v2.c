#include <fj2207v2.h>
//definitions of internal functions

I2cResponseType fj2207_reg_init(Fj2207Handle *h);
#if USE_ELOBARATE==1
	BitbangReturn fj2207_field_init(Fj2207Handle *h);
	//those functions are using to servicing fields such as ID or RF frequency
	void fj2207_temp_writing(Fj2207Handle *h, Fj2207Ident field_id);
	void fj2207_temp_reading(Fj2207Handle *h, Fj2207Ident field_id);
#endif

I2cResponseType fj2207_write_byte_register(Fj2207Handle *h, uint8 reg, uint8 device_address, uint8 register_address){
	uint8 timeout;
	I2cResponseType resp;
	timeout = 0;
	do{
		resp = i2c_choose_device(&(h->i2c_handle), device_address, I2CSlaveAccessModeWrite);
	} while(((resp) != I2c_Success) && (timeout++ < 7));
	if ((resp) || (timeout == 7)){
		return resp;
	}
	
	resp = i2c_write_byte(&(h->i2c_handle), register_address);
	if (resp != I2c_More_Data){
		return resp;
	}

	resp = i2c_write_byte(&(h->i2c_handle), reg);
	if (resp != I2c_More_Data){
		return resp;
	}	

	return I2c_Success;
}

I2cResponseType fj2207_get_byte_register(Fj2207Handle *h, uint8 *reg, uint8 device_address, uint8 register_address){
	uint8 timeout;
	I2cResponseType resp;
	timeout = 0;
	do{
		resp = i2c_choose_device(&(h->i2c_handle), device_address, I2CSlaveAccessModeWrite);
	} while(((resp) != I2c_Success) && (timeout++ < 7));
	if ((resp) || (timeout == 7)){
		return resp;
	}
	
	resp = i2c_write_byte(&(h->i2c_handle), register_address);
	if (resp != I2c_More_Data){
		return resp;
	}
	
	resp = i2c_choose_device(&(h->i2c_handle), device_address, I2CSlaveAccessModeRead);
	if (resp){
		return resp;
	}
	
	i2c_get_byte(&(h->i2c_handle), reg);
	
	return I2c_Success;
}

I2cResponseType fj2207_reg_init(Fj2207Handle *h){
	I2cResponseType resp; 
	//status control registers
	
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.ID_byte_1), FJ2207_CHIP_ADDRESS, ID_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.ID_byte_2), FJ2207_CHIP_ADDRESS, ID_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.ID_byte_3), FJ2207_CHIP_ADDRESS, ID_byte_3);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.Thermo_byte_1), FJ2207_CHIP_ADDRESS, Thermo_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.Thermo_byte_2), FJ2207_CHIP_ADDRESS, Thermo_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.Power_state_byte_1), FJ2207_CHIP_ADDRESS, Power_state_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.Power_state_byte_2), FJ2207_CHIP_ADDRESS, Power_state_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.AGCK_byte_1), FJ2207_CHIP_ADDRESS, AGCK_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.Reference_byte), FJ2207_CHIP_ADDRESS, Reference_byte);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.MSM_byte_1), FJ2207_CHIP_ADDRESS, MSM_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.MSM_byte_2), FJ2207_CHIP_ADDRESS, MSM_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.PSM_byte_1), FJ2207_CHIP_ADDRESS, PSM_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.IR_MIXER_byte_2), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->status_control_registers.Power_byte_2), FJ2207_CHIP_ADDRESS, Power_byte_2);
	if (resp){
		return resp;
	}
	
	//PLL control registers
	resp = fj2207_get_byte_register(h, &(h->pll_control_registers.IF_Frequency_byte), FJ2207_CHIP_ADDRESS, IF_Frequency_byte);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->pll_control_registers.RF_Frequency_byte_1), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->pll_control_registers.RF_Frequency_byte_2), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->pll_control_registers.RF_Frequency_byte_3), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_3);
	if (resp){
		return resp;
	}
	
	//Power control registers
	resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.Input_Power_Level_byte), FJ2207_CHIP_ADDRESS, Input_Power_Level_byte);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.AGC1_byte_1), FJ2207_CHIP_ADDRESS, AGC1_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.AGC2_byte_1), FJ2207_CHIP_ADDRESS, AGC2_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.IR_MIXER_byte_1), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.AGC5_byte_1), FJ2207_CHIP_ADDRESS, AGC5_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.IF_AGC_byte), FJ2207_CHIP_ADDRESS, IF_AGC_byte);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.RF_AGC_Gain_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_Gain_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.RF_AGC_Gain_byte_2), FJ2207_CHIP_ADDRESS, RF_AGC_Gain_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.IF_AGC_Gain_byte), FJ2207_CHIP_ADDRESS, IF_AGC_Gain_byte);
	if (resp){
		return resp;
	}
	//end of registers initialization
	
	//send stop sequence
	i2c_send_stop_sequence(&(h->i2c_handle));
	
	return I2c_Success;
}

#if USE_ELABORATE==1
	void fj2207_temp_writing(Fj2207Handle *h, Fj2207Ident field_id){
			uint32 temp;
			switch(field_id){
				case RF_Freq:
					temp = h->pll_control_fields.RF_Freq_temp;
					h->pll_control_registers.RF_Frequency_byte_2 = h->pll_control_fields.RF_Freq_temp;
					h->pll_control_fields.RF_Freq_temp >>= BYTE_SIZE;
					h->pll_control_registers.RF_Frequency_byte_3 = h->pll_control_fields.RF_Freq_temp;
					h->pll_control_fields.RF_Freq_temp >>= BYTE_SIZE;
					h->pll_control_registers.RF_Frequency_byte_1 = h->pll_control_fields.RF_Freq_temp;
					h->pll_control_fields.RF_Freq_temp = temp;
			}
	}
	
	Fj2207ReturnType fj2207_temp_reading(Fj2207Handle *h, Fj2207Ident field_id){
		switch(field_id){
			case Ident:
				h->status_control_fields.Ident_temp = h->status_control_registers.ID_byte_1;
				h->status_control_fields.Ident_temp &=	0x7F;
				h->status_control_fields.Ident_temp <<= BYTE_SIZE;
				h->status_control_fields.Ident_temp |= h->status_control_registers.ID_byte_2;
			return Fj2207Success;
			
			case RF_Freq:
				h->pll_control_fields.RF_Freq_temp = 0;
				h->pll_control_fields.RF_Freq_temp = h->pll_control_registers.RF_Frequency_byte_1;
				h->pll_control_fields.RF_Freq_temp &= 0x0F;
				h->pll_control_fields.RF_Freq_temp <<= BYTE_SIZE;
				h->pll_control_fields.RF_Freq_temp |= h->pll_control_registers.RF_Frequency_byte_3;
				h->pll_control_fields.RF_Freq_temp <<= BYTE_SIZE;
				h->pll_control_fields.RF_Freq_temp |= h->pll_control_registers.RF_Frequency_byte_2;
			return Fj2207Success;
			
			default:
			return Fj2207FieldIsNoDefined;
		}
	}

	BitbangReturn fj2207_field_init(Fj2207Handle *h){
		BitbangReturn ret;
		fj2207_temp_reading(h, Ident);
		//	Status control fields init
		ret = bitbang_init_field( 	&( (h->status_control_fields.Ident)), 
								&( (h->status_control_fields.Ident_temp)),
								2,
								0,
								15,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.Major_rev)), 
								&( (h->status_control_registers.ID_byte_3)),
								1,
								4,
								4,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.Minor_rev)), 
								&( (h->status_control_registers.ID_byte_3)),
								1,
								0,
								4,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.TM_D)), 
								&( (h->status_control_registers.Thermo_byte_1)),
								1,
								0,
								7,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.TM_ON)), 
								&( (h->status_control_registers.Thermo_byte_2)),
								1,
								0,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.POR)), 
								&( (h->status_control_registers.Power_state_byte_1)),
								1,
								1,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.LO_Lock)), 
								&( (h->status_control_registers.Power_state_byte_1)),
								1,
								0,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.SM)), 
								&( (h->status_control_registers.Power_state_byte_2)),
								1,
								3,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.SM_PLL)), 
								&( (h->status_control_registers.Power_state_byte_2)),
								1,
								2,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.SM_LNA)), 
								&( (h->status_control_registers.Power_state_byte_2)),
								1,
								1,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.Pulse_Shaper_disable)), 
								&( (h->status_control_registers.AGCK_byte_1)),
								1,
								4,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.AGCK_mode)), 
								&( (h->status_control_registers.AGCK_byte_1)),
								1,
								0,
								2,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.IF_HP_Fc)), 
								&( (h->status_control_registers.IF_byte_1)),
								1,
								6,
								2,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.IF_Notch)), 
								&( (h->status_control_registers.IF_byte_1)),
								1,
								5,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.LP_FC_Offset)), 
								&( (h->status_control_registers.IF_byte_1)),
								1,
								3,
								2,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.LP_Fc)), 
								&( (h->status_control_registers.IF_byte_1)),
								1,
								0,
								3,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.Digital_Clock)), 
								&( (h->status_control_registers.Reference_byte)),
								1,
								6,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.XTout)), 
								&( (h->status_control_registers.Reference_byte)),
								1,
								0,
								2,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.POWER_Meas)), 
								&( (h->status_control_registers.MSM_byte_1)),
								1,
								7,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.RF_CAL_AV)), 
								&( (h->status_control_registers.MSM_byte_1)),
								1,
								6,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.RF_CAL)), 
								&( (h->status_control_registers.MSM_byte_1)),
								1,
								5,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.IR_CAL)), 
								&( (h->status_control_registers.MSM_byte_1)),
								1,
								3,
								2,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.RC_CAL)), 
								&( (h->status_control_registers.MSM_byte_1)),
								1,
								1,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.Calc_PLL)), 
								&( (h->status_control_registers.MSM_byte_1)),
								1,
								0,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.MSM_Launch)), 
								&( (h->status_control_registers.MSM_byte_2)),
								1,
								0,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.VHFIII)), 
								&( (h->status_control_registers.PSM_byte_1)),
								1,
								5,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.HI_Pass)), 
								&( (h->status_control_registers.IR_MIXER_byte_2)),
								1,
								1,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.DC_NOTCH)), 
								&( (h->status_control_registers.IR_MIXER_byte_2)),
								1,
								0,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->status_control_fields.Power_byte_2)), 
								&( (h->status_control_registers.Power_byte_2)),
								1,
								0,
								8,
								0
							);
		if (ret) return ret;
		//PLL control fields
		
		ret = bitbang_init_field( 	&( (h->pll_control_fields.IF_Freq)), 
								&( (h->pll_control_registers.IF_Frequency_byte)),
								1,
								0,
								8,
								0
							);
		if (ret) return ret;
		
		fj2207_temp_reading(h, RF_Freq);
		ret = bitbang_init_field( 	&( (h->pll_control_fields.RF_Freq)), 
								&( (h->pll_control_fields.RF_Freq_temp)),
								4,
								0,
								32,
								0
							);
		if (ret) return ret;
		
		//Power and gain control fields
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.Power_Level)), 
								&( (h->power_gain_control_registers.Input_Power_Level_byte)),
								1,
								0,
								6,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.LT_Enable)), 
								&( (h->power_gain_control_registers.AGC1_byte_1)),
								1,
								7,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.AGC1_6_15dB)), 
								&( (h->power_gain_control_registers.AGC1_byte_1)),
								1,
								6,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.AGC1_TOP)), 
								&( (h->power_gain_control_registers.AGC1_byte_1)),
								1,
								0,
								4,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.AGC2_byte_1)), 
								&( (h->power_gain_control_registers.AGC2_byte_1)),
								1,
								0,
								8,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.PD_RFAGC_Adapt)), 
								&( (h->power_gain_control_registers.RF_AGC_byte_1)),
								1,
								7,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.RFAGC_Adapt_TOP)), 
								&( (h->power_gain_control_registers.RF_AGC_byte_1)),
								1,
								5,
								2,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.RF_Atten_3dB)), 
								&( (h->power_gain_control_registers.RF_AGC_byte_1)),
								1,
								3,
								1,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.AGC3_Top)), 
								&( (h->power_gain_control_registers.RF_AGC_byte_1)),
								1,
								0,
								3,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.AGC4_Top)), 
								&( (h->power_gain_control_registers.IR_MIXER_byte_1)),
								1,
								0,
								3,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.AGC5_HPF)), 
								&( (h->power_gain_control_registers.AGC5_byte_1)),
								1,
								4,
								1,
								0
							);
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.AGC5_Top)), 
								&( (h->power_gain_control_registers.AGC5_byte_1)),
								1,
								0,
								4,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.IF_Level)), 
								&( (h->power_gain_control_registers.IF_AGC_byte)),
								1,
								0,
								3,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.RF_FILTER_GAIN)), 
								&( (h->power_gain_control_registers.RF_AGC_Gain_byte_1)),
								1,
								4,
								2,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.LNA_GAIN)), 
								&( (h->power_gain_control_registers.RF_AGC_Gain_byte_1)),
								1,
								0,
								4,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.TOP_Agc3_read)), 
								&( (h->power_gain_control_registers.RF_AGC_Gain_byte_2)),
								1,
								0,
								3,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.LPF_GAIN)), 
								&( (h->power_gain_control_registers.IF_AGC_Gain_byte)),
								1,
								3,
								2,
								0
							);
		if (ret) return ret;
		
		ret = bitbang_init_field( 	&( (h->power_gain_control_fields.IR_MIXER)), 
								&( (h->power_gain_control_registers.IF_AGC_Gain_byte)),
								1,
								0,
								3,
								0
							);
		if (ret) return ret;
		
		return Bitbang_OK;
	}
	
	Fj2207ReturnType fj2207_read_field(Fj2207Handle *h, Fj2207Ident field_id, uint32 *value){
		I2cResponseType resp;
		BitbangReturn ret;
		switch(field_id){
			case Ident:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.ID_byte_1), FJ2207_CHIP_ADDRESS, ID_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.ID_byte_2), FJ2207_CHIP_ADDRESS, ID_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				fj2207_temp_reading(h, Ident);
				ret = bitbang_get(&(h->status_control_fields.Ident), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case Major_rev:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.ID_byte_3), FJ2207_CHIP_ADDRESS, ID_byte_3);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.Major_rev), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case Minor_rev:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.ID_byte_3), FJ2207_CHIP_ADDRESS, ID_byte_3);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.Minor_rev), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case TM_D:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.Thermo_byte_1), FJ2207_CHIP_ADDRESS, Thermo_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.TM_D), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case TM_ON:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.Thermo_byte_2), FJ2207_CHIP_ADDRESS, Thermo_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.TM_ON), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case POR:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.Power_state_byte_1), FJ2207_CHIP_ADDRESS, Power_state_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.POR), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case LO_Lock:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.Power_state_byte_1), FJ2207_CHIP_ADDRESS, Power_state_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.LO_Lock), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case SM_LNA:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.Power_state_byte_2), FJ2207_CHIP_ADDRESS, Power_state_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.SM_LNA), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case SM_PLL:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.Power_state_byte_2), FJ2207_CHIP_ADDRESS, Power_state_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.SM_PLL), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
	
			case SM:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.Power_state_byte_2), FJ2207_CHIP_ADDRESS, Power_state_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.SM), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case Pulse_Shaper_disable:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.AGCK_byte_1), FJ2207_CHIP_ADDRESS, AGCK_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.Pulse_Shaper_disable), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case AGCK_mode:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.AGCK_byte_1), FJ2207_CHIP_ADDRESS, AGCK_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.AGCK_mode), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case IF_HP_Fc:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.IF_HP_Fc), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case IF_Notch:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.IF_Notch), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case LP_FC_Offset:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.LP_FC_Offset), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
			
			case LP_Fc:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.LP_Fc), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
			
			case Digital_Clock:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.Reference_byte), FJ2207_CHIP_ADDRESS, Reference_byte);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.Digital_Clock), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
			
			case XTout:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.Reference_byte), FJ2207_CHIP_ADDRESS, Reference_byte);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.XTout), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case POWER_Meas:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.MSM_byte_1), FJ2207_CHIP_ADDRESS, MSM_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.POWER_Meas), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
			
			case RF_CAL_AV:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.MSM_byte_1), FJ2207_CHIP_ADDRESS, MSM_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.RF_CAL_AV), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
			
			case RF_CAL:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.MSM_byte_1), FJ2207_CHIP_ADDRESS, MSM_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.RF_CAL), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
							
			case IR_CAL:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.MSM_byte_1), FJ2207_CHIP_ADDRESS, MSM_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.IR_CAL), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
			
			case RC_CAL:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.MSM_byte_1), FJ2207_CHIP_ADDRESS, MSM_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.RC_CAL), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
			
			case Calc_PLL:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.MSM_byte_1), FJ2207_CHIP_ADDRESS, MSM_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.Calc_PLL), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
				
			case MSM_Launch:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.MSM_byte_2), FJ2207_CHIP_ADDRESS, MSM_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.MSM_Launch), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
			
			case VHFIII:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.PSM_byte_1), FJ2207_CHIP_ADDRESS, PSM_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.VHFIII), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
			
			case DC_NOTCH:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.IR_MIXER_byte_2), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.DC_NOTCH), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;	
			
			case HI_Pass:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.IR_MIXER_byte_2), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.HI_Pass), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case Power_byte_2:
				resp = fj2207_get_byte_register(h, &(h->status_control_registers.Power_byte_2), FJ2207_CHIP_ADDRESS, Power_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->status_control_fields.Power_byte_2), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			//PLL controls
			
			case IF_Freq:
				resp = fj2207_get_byte_register(h, &(h->pll_control_registers.IF_Frequency_byte), FJ2207_CHIP_ADDRESS, IF_Frequency_byte);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->pll_control_fields.IF_Freq), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case RF_Freq:
				resp = fj2207_get_byte_register(h, &(h->pll_control_registers.RF_Frequency_byte_1), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				resp = fj2207_get_byte_register(h, &(h->pll_control_registers.RF_Frequency_byte_3), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_3);
				if (resp) return (Fj2207ReturnType)resp;
				resp = fj2207_get_byte_register(h, &(h->pll_control_registers.RF_Frequency_byte_2), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				fj2207_temp_reading(h, RF_Freq);
				ret = bitbang_get(&(h->pll_control_fields.RF_Freq), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			//GAIN AND POWER controls
			
			case Power_Level:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.Input_Power_Level_byte), FJ2207_CHIP_ADDRESS, Input_Power_Level_byte);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.Power_Level), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case LT_Enable:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.AGC1_byte_1), FJ2207_CHIP_ADDRESS, AGC1_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.LT_Enable), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case AGC1_6_15dB:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.AGC1_byte_1), FJ2207_CHIP_ADDRESS, AGC1_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.AGC1_6_15dB), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
				
			case AGC1_TOP:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.AGC1_byte_1), FJ2207_CHIP_ADDRESS, AGC1_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.AGC1_TOP), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case AGC2_byte_1:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.AGC2_byte_1), FJ2207_CHIP_ADDRESS, AGC2_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.AGC2_byte_1), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case PD_RFAGC_Adapt:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.PD_RFAGC_Adapt), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case RFAGC_Adapt_TOP:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.RFAGC_Adapt_TOP), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case RF_Atten_3dB:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.RF_Atten_3dB), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case AGC3_Top:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.AGC3_Top), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case AGC4_Top:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.IR_MIXER_byte_1), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.AGC4_Top), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
									
			case AGC5_HPF:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.AGC5_byte_1), FJ2207_CHIP_ADDRESS, AGC5_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.AGC5_HPF), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case AGC5_Top:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.AGC5_byte_1), FJ2207_CHIP_ADDRESS, AGC5_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.AGC5_Top), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case IF_Level:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.IF_AGC_byte), FJ2207_CHIP_ADDRESS, IF_AGC_byte);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.IF_Level), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
										
			case RF_FILTER_GAIN:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.RF_AGC_Gain_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_Gain_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.RF_FILTER_GAIN), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case LNA_GAIN:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.RF_AGC_Gain_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_Gain_byte_1);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.LNA_GAIN), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
						
			case TOP_Agc3_read:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.RF_AGC_Gain_byte_2), FJ2207_CHIP_ADDRESS, RF_AGC_Gain_byte_2);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.TOP_Agc3_read), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case LPF_GAIN:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.IF_AGC_Gain_byte), FJ2207_CHIP_ADDRESS, IF_AGC_Gain_byte);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.LPF_GAIN), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
			
			case IR_MIXER:
				resp = fj2207_get_byte_register(h, &(h->power_gain_control_registers.IF_AGC_Gain_byte), FJ2207_CHIP_ADDRESS, IF_AGC_Gain_byte);
				if (resp) return (Fj2207ReturnType)resp;
				ret = bitbang_get(&(h->power_gain_control_fields.IR_MIXER), value);
				if (ret) return (Fj2207ReturnType) ret;
			return Fj2207Success;
													
			default:
			return Fj2207FieldIsNoDefined;
		}
	}
	
	Fj2207ReturnType fj2207_write_field(Fj2207Handle *h, Fj2207Ident field_id, uint32 value){
		I2cResponseType res;
		BitbangReturn ret;
		switch(field_id){
			case TM_ON:
				ret = bitbang_set_value(&(h->status_control_fields.TM_ON), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.Thermo_byte_2, FJ2207_CHIP_ADDRESS, Thermo_byte_2);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
				
			case SM:
				ret = bitbang_set_value(&(h->status_control_fields.SM), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.Power_state_byte_2, FJ2207_CHIP_ADDRESS, Power_state_byte_2);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case SM_LNA:
				ret = bitbang_set_value(&(h->status_control_fields.SM_LNA), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.Power_state_byte_2, FJ2207_CHIP_ADDRESS, Power_state_byte_2);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case SM_PLL:
				ret = bitbang_set_value(&(h->status_control_fields.SM_PLL), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.Power_state_byte_2, FJ2207_CHIP_ADDRESS, Power_state_byte_2);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case Pulse_Shaper_disable:
				ret = bitbang_set_value(&(h->status_control_fields.Pulse_Shaper_disable), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.AGCK_byte_1, FJ2207_CHIP_ADDRESS, AGCK_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case AGCK_mode:
				ret = bitbang_set_value(&(h->status_control_fields.AGCK_mode), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.AGCK_byte_1, FJ2207_CHIP_ADDRESS, AGCK_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case IF_HP_Fc:
				ret = bitbang_set_value(&(h->status_control_fields.IF_HP_Fc), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.IF_byte_1, FJ2207_CHIP_ADDRESS, IF_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case IF_Notch:
				ret = bitbang_set_value(&(h->status_control_fields.IF_Notch), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.IF_byte_1, FJ2207_CHIP_ADDRESS, IF_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case LP_FC_Offset:
				ret = bitbang_set_value(&(h->status_control_fields.LP_FC_Offset), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.IF_byte_1, FJ2207_CHIP_ADDRESS, IF_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case LP_Fc:
				ret = bitbang_set_value(&(h->status_control_fields.LP_Fc), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.IF_byte_1, FJ2207_CHIP_ADDRESS, IF_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case XTout:
				ret = bitbang_set_value(&(h->status_control_fields.XTout), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.Reference_byte, FJ2207_CHIP_ADDRESS, Reference_byte);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case Digital_Clock:
				ret = bitbang_set_value(&(h->status_control_fields.Digital_Clock), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.Reference_byte, FJ2207_CHIP_ADDRESS, Reference_byte);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case POWER_Meas:
				ret = bitbang_set_value(&(h->status_control_fields.POWER_Meas), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.MSM_byte_1, FJ2207_CHIP_ADDRESS, MSM_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case RF_CAL_AV:
				ret = bitbang_set_value(&(h->status_control_fields.RF_CAL_AV), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.MSM_byte_1, FJ2207_CHIP_ADDRESS, MSM_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case RF_CAL:
				ret = bitbang_set_value(&(h->status_control_fields.RF_CAL), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.MSM_byte_1, FJ2207_CHIP_ADDRESS, MSM_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case IR_CAL:
				ret = bitbang_set_value(&(h->status_control_fields.IR_CAL), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.MSM_byte_1, FJ2207_CHIP_ADDRESS, MSM_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case RC_CAL:
				ret = bitbang_set_value(&(h->status_control_fields.RC_CAL), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.MSM_byte_1, FJ2207_CHIP_ADDRESS, MSM_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case Calc_PLL:
				ret = bitbang_set_value(&(h->status_control_fields.Calc_PLL), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.MSM_byte_1, FJ2207_CHIP_ADDRESS, MSM_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case MSM_Launch:
				ret = bitbang_set_value(&(h->status_control_fields.MSM_Launch), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.MSM_byte_2, FJ2207_CHIP_ADDRESS, MSM_byte_2);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case VHFIII:
				ret = bitbang_set_value(&(h->status_control_fields.VHFIII), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.PSM_byte_1, FJ2207_CHIP_ADDRESS, PSM_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case DC_NOTCH:
				ret = bitbang_set_value(&(h->status_control_fields.DC_NOTCH), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.IR_MIXER_byte_2, FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case HI_Pass:
				ret = bitbang_set_value(&(h->status_control_fields.HI_Pass), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.IR_MIXER_byte_2, FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case Power_byte_2:
				ret = bitbang_set_value(&(h->status_control_fields.Power_byte_2), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->status_control_registers.Power_byte_2, FJ2207_CHIP_ADDRESS, Power_byte_2);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			//PLL
			
			case IF_Freq:
				ret = bitbang_set_value(&(h->pll_control_fields.IF_Freq), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->pll_control_registers.IF_Frequency_byte, FJ2207_CHIP_ADDRESS, IF_Frequency_byte);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case RF_Freq:
				ret = bitbang_set_value(&(h->pll_control_fields.RF_Freq), value);
				if (ret) return (Fj2207ReturnType) ret;
				fj2207_temp_writing(h, RF_Freq);
				res = fj2207_write_byte_register(h, h->pll_control_registers.RF_Frequency_byte_1, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_1);
				if (res) return (Fj2207ReturnType) res;
				res = fj2207_write_byte_register(h, h->pll_control_registers.RF_Frequency_byte_3, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_3);
				if (res) return (Fj2207ReturnType) res;
				res = fj2207_write_byte_register(h, h->pll_control_registers.RF_Frequency_byte_2, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_2);
				if (res) return (Fj2207ReturnType) res;
				i2c_send_stop_sequence(&(h->i2c_handle));
			return Fj2207Success;
			
			//GAIN AND POWER
			case LT_Enable:
				ret = bitbang_set_value(&(h->power_gain_control_fields.LT_Enable), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.AGC1_byte_1, FJ2207_CHIP_ADDRESS, AGC1_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case AGC1_6_15dB:
				ret = bitbang_set_value(&(h->power_gain_control_fields.AGC1_6_15dB), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.AGC1_byte_1, FJ2207_CHIP_ADDRESS, AGC1_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case AGC1_TOP:
				ret = bitbang_set_value(&(h->power_gain_control_fields.AGC1_TOP), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.AGC1_byte_1, FJ2207_CHIP_ADDRESS, AGC1_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case AGC2_byte_1:
				ret = bitbang_set_value(&(h->power_gain_control_fields.AGC2_byte_1), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.AGC2_byte_1, FJ2207_CHIP_ADDRESS, AGC2_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case PD_RFAGC_Adapt:
				ret = bitbang_set_value(&(h->power_gain_control_fields.PD_RFAGC_Adapt), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.RF_AGC_byte_1, FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case RFAGC_Adapt_TOP:
				ret = bitbang_set_value(&(h->power_gain_control_fields.RFAGC_Adapt_TOP), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.RF_AGC_byte_1, FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case RF_Atten_3dB:
				ret = bitbang_set_value(&(h->power_gain_control_fields.RF_Atten_3dB), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.RF_AGC_byte_1, FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case AGC3_Top:
				ret = bitbang_set_value(&(h->power_gain_control_fields.AGC3_Top), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.RF_AGC_byte_1, FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case AGC4_Top:
				ret = bitbang_set_value(&(h->power_gain_control_fields.AGC4_Top), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.IR_MIXER_byte_1, FJ2207_CHIP_ADDRESS, IR_MIXER_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case AGC5_HPF:
				ret = bitbang_set_value(&(h->power_gain_control_fields.AGC5_HPF), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.AGC5_byte_1, FJ2207_CHIP_ADDRESS, AGC5_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case AGC5_Top:
				ret = bitbang_set_value(&(h->power_gain_control_fields.AGC5_Top), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.AGC5_byte_1, FJ2207_CHIP_ADDRESS, AGC5_byte_1);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
			
			case IF_Level:
				ret = bitbang_set_value(&(h->power_gain_control_fields.IF_Level), value);
				if (ret) return (Fj2207ReturnType) ret;
				res = fj2207_write_byte_register(h, h->power_gain_control_registers.IF_AGC_byte, FJ2207_CHIP_ADDRESS, IF_AGC_byte);
				i2c_send_stop_sequence(&(h->i2c_handle));
				if (res) return (Fj2207ReturnType) res;
			return Fj2207Success;
						
			default:
			return Fj2207FieldReadOnly;
			
		}
	}
#endif

Fj2207ReturnType fj2207_init(Fj2207Handle *h,  DAC_handle *handle, GpioPin *i2c_sda, GpioPin *i2c_scl, GpioPin *spi_sclk, GpioPin *spi_simo, GpioPin *dac_cs){
	I2cResponseType ret;
	#if USE_ELABORATE==1
		BitbangReturn res;
	#endif
	//I2C INITIALIZATION
	i2c_init(&(h->i2c_handle), i2c_sda, i2c_scl);
	//DAC SPI INITIALIZATION
	dac_spi_init(handle, spi_sclk, spi_simo, dac_cs);
	//REGISTERS INITIALIZATION
	ret = fj2207_reg_init(h);
	if (ret) return (Fj2207ReturnType) ret;
	
	//FIELDS INITIALIZATION
	#if USE_ELABORATE==1
		res = fj2207_field_init(h);
		if (res) return (Fj2207ReturnType) res;
	#endif
	return Fj2207Success;
}

Fj2207ReturnType fj2207_set(Fj2207Handle *h, uint32 rf_frequency, uint32 if_frequency){
	#if USE_ELABORATE==1
		//transition 0
		Fj2207ReturnType ret;
		ret = fj2207_write_field(h, SM, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, SM_LNA, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, SM_PLL, 0);
		if (ret) return ret;
		
		ret = fj2207_write_field(h, POWER_Meas, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, RF_CAL_AV, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, RF_CAL, 1);
		if (ret) return ret;
		ret = fj2207_write_field(h, IR_CAL, 3);
		if (ret) return ret;
		ret = fj2207_write_field(h, RC_CAL, 1);
		if (ret) return ret;
		ret = fj2207_write_field(h, Calc_PLL, 1);
		if (ret) return ret;
		ret = fj2207_write_field(h, MSM_Launch, 1);
		if (ret) return ret;
		ret = fj2207_write_field(h, Digital_Clock, 1);
		if (ret) return ret;
		ret = fj2207_write_field(h, XTout, 2);
		if (ret) return ret;
		ret = fj2207_write_field(h, Power_byte_2, 0x0E);
		if (ret) return ret;
		ret = fj2207_write_field(h, SM, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, SM_LNA, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, SM_PLL, 1);
		if (ret) return ret;
		//transition 1
		ret = fj2207_write_field(h, IF_Freq, if_frequency/50000);
		if (ret) return ret;
		ret = fj2207_write_field(h, IF_HP_Fc, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, IF_Notch, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, LP_FC_Offset, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, LP_Fc, 3);//2);
		if (ret) return ret;
		ret = fj2207_write_field(h, HI_Pass, 0);//3);
		if (ret) return ret;
		ret = fj2207_write_field(h, DC_NOTCH, 0);//1);
		if (ret) return ret;
		
		//blabla
		ret = fj2207_write_field(h, IF_Level, 2);
		if (ret) return ret;		
		ret = fj2207_write_field(h, PD_RFAGC_Adapt, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, RFAGC_Adapt_TOP, 1);
		if (ret) return ret;
		ret = fj2207_write_field(h, AGC1_TOP, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, AGC3_Top, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, AGC5_Top, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, AGC4_Top, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, RF_Atten_3dB, 1);
		if (ret) return ret;
		ret = fj2207_write_field(h, AGC5_HPF, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, LT_Enable, 1);
		if (ret) return ret;
		ret = fj2207_write_field(h, AGC1_6_15dB, 0);
		if (ret) return ret;
		
		
		ret = fj2207_write_field(h, Pulse_Shaper_disable, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, AGCK_mode, 2);
		if (ret) return ret;
		ret = fj2207_write_field(h, VHFIII, 0);
		if (ret) return ret;
		
		//transition 2
		ret = fj2207_write_field(h, RF_Freq, rf_frequency/1000);
		if (ret) return ret;
		ret = fj2207_write_field(h, SM, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, SM_LNA, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, SM_PLL, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, Power_byte_2, 0x0E);
		if (ret) return ret;
		ret = fj2207_write_field(h, POWER_Meas, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, RF_CAL_AV, 1);
		if (ret) return ret;
		ret = fj2207_write_field(h, RF_CAL, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, IR_CAL, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, RC_CAL, 0);
		if (ret) return ret;
		ret = fj2207_write_field(h, Calc_PLL, 1);
		if (ret) return ret;
		ret = fj2207_write_field(h, MSM_Launch, 1);
		if (ret) return ret;
	#else
		uint32 temp;
		I2cResponseType res;
		//transition 0
		res = fj2207_write_byte_register(h, 0x00, FJ2207_CHIP_ADDRESS, Power_state_byte_2); //PLL and LNA on
		if (res) return (Fj2207ReturnType) res;
		res = fj2207_write_byte_register(h, 0x3B, FJ2207_CHIP_ADDRESS, MSM_byte_1);
		if (res) return (Fj2207ReturnType) res;
		res = fj2207_write_byte_register(h, 0x01, FJ2207_CHIP_ADDRESS, MSM_byte_2);
		if (res) return (Fj2207ReturnType) res;
		res = fj2207_write_byte_register(h, 0x4F, FJ2207_CHIP_ADDRESS, Reference_byte);
		if (res) return (Fj2207ReturnType) res;
		res = fj2207_write_byte_register(h, 0x0E, FJ2207_CHIP_ADDRESS, Power_byte_2); //default values
		if (res) return (Fj2207ReturnType) res; 
		res = fj2207_write_byte_register(h, 0x04, FJ2207_CHIP_ADDRESS, Power_state_byte_2); //standby
		if (res) return (Fj2207ReturnType) res;
		//transition 1
		res = fj2207_write_byte_register(h, (if_frequency/50000), FJ2207_CHIP_ADDRESS, IF_Frequency_byte);
		if (res) return (Fj2207ReturnType) res;
		res = fj2207_write_byte_register(h, 0x02, FJ2207_CHIP_ADDRESS, IF_AGC_byte); //1 V p-p - datasheet table 20
		if (res) return (Fj2207ReturnType) res;
		//high-pass cutoff freq - 0.4 Mhz - 0		
		//disable notch - 0 
		//no LPF cutoff offset - 0
		//LPF cutoff - 10 Mhz - 3 dec
		res = fj2207_write_byte_register(h, 0x03, FJ2207_CHIP_ADDRESS, IF_byte_1);
		if (res) return (Fj2207ReturnType) res;
		//notch off, hi pass off
		res = fj2207_write_byte_register(h, 0x00, FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2); //IR mixer byte 2
		if (res) return (Fj2207ReturnType) res;
		// agc1 byte 1 - not set - default values
		// agc2 byte 1 - not set - default values
		res = fj2207_write_byte_register(h, 0x02, FJ2207_CHIP_ADDRESS, AGCK_byte_1); //digital tv
		if (res) return (Fj2207ReturnType) res;
		// ir mixer byte 1 - not set - default values 
		// AGC5 byte 1 - not set - default values
		// here should be set PSM byte 1
		res = fj2207_write_byte_register(h, 0x20, FJ2207_CHIP_ADDRESS, PSM_byte_1);
		if (res) return (Fj2207ReturnType) res;
		//trans2
		
		temp = rf_frequency/1000;
		rf_frequency = temp & 0xFF;
		res = fj2207_write_byte_register(h, rf_frequency, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_2);
		if (res) return (Fj2207ReturnType) res;
		
		rf_frequency = temp & 0xFF00;
		rf_frequency >>= 8;
		res = fj2207_write_byte_register(h, rf_frequency, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_3);
		if (res) return (Fj2207ReturnType) res;
		
		rf_frequency = temp & 0xF0000;
		rf_frequency >>= 16;
		res = fj2207_write_byte_register(h, rf_frequency, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_1);
		if (res) return (Fj2207ReturnType) res;
	
		res = fj2207_write_byte_register(h, 0x00, FJ2207_CHIP_ADDRESS, Power_state_byte_2);
		if (res) return (Fj2207ReturnType) res;
		res = fj2207_write_byte_register(h, 0x00, FJ2207_CHIP_ADDRESS, Power_byte_2); //power byte
		if (res) return (Fj2207ReturnType) res;
		res = fj2207_write_byte_register(h, 0x41, FJ2207_CHIP_ADDRESS, MSM_byte_1); 
		if (res) return (Fj2207ReturnType) res;
		res = fj2207_write_byte_register(h, 0x01, FJ2207_CHIP_ADDRESS, MSM_byte_2);
		if (res) return (Fj2207ReturnType) res;
	#endif
	return Fj2207Success;
}

