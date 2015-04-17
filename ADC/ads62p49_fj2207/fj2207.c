#include <fj2207.h>

//internal declarations

Fj2207ReturnType fj2207_update_handle(Fj2207Handle *h, Fj2207Ident field_id);
#ifdef USE_ELABORATE
	Fj2207ReturnType fj2207_write_field_to_handle(Fj2207Handle *h, Fj2207Ident field_id);
	Fj2207ReturnType fj2207_write_field_from_handle(Fj2207Handle *h, Fj2207Ident field_id);
#endif

//after calling of this function required stop sequence to end transmission
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
//after calling of this function required stop sequence to end transmission
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

	//fj2207_update_handle(h, (Fj2207Ident)register_address);	

	return I2c_Success;
}

I2cResponseType fj2207_read_registers(Fj2207Handle *h){
#ifdef USE_ELOBARATE
	Fj2207ReturnType resp;
	uint16 i;
	for (i=60; i<=105; i++){
		resp = fj2207_read_field(h, (Fj2207Ident) i);
		if (resp){
			return (I2cResponseType) resp;
		}
	}
#else
	I2cResponseType resp;
	resp = fj2207_get_byte_register(h, &(h->ID_byte_1), FJ2207_CHIP_ADDRESS, ID_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->ID_byte_2), FJ2207_CHIP_ADDRESS, ID_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->ID_byte_3), FJ2207_CHIP_ADDRESS, ID_byte_3);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h,  &(h->Thermo_byte_1), FJ2207_CHIP_ADDRESS, Thermo_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->Thermo_byte_2), FJ2207_CHIP_ADDRESS, Thermo_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->Power_state_byte_1), FJ2207_CHIP_ADDRESS, Power_state_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->Power_state_byte_2), FJ2207_CHIP_ADDRESS, Power_state_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->Input_Power_Level_byte), FJ2207_CHIP_ADDRESS, Input_Power_Level_byte);
	if (resp){
		return resp;
	}	
	resp = fj2207_get_byte_register(h, &(h->IF_Frequency_byte), FJ2207_CHIP_ADDRESS, IF_Frequency_byte);
	if (resp){
		return resp;
	}	
	resp = fj2207_get_byte_register(h, &(h->RF_Frequency_byte_1), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_1);
	if (resp){
		return resp;
	}	
	resp = fj2207_get_byte_register(h, &(h->RF_Frequency_byte_2), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->RF_Frequency_byte_3), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_3);	
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->MSM_Byte_1), FJ2207_CHIP_ADDRESS, MSM_Byte_1);	
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->MSM_Byte_2), FJ2207_CHIP_ADDRESS, MSM_Byte_2);	
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->AGCK_byte_1), FJ2207_CHIP_ADDRESS, AGCK_byte_1);	
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);	
	if (resp){
		return resp;
	}		
	resp = fj2207_get_byte_register(h, &(h->IF_AGC_byte), FJ2207_CHIP_ADDRESS, IF_AGC_byte);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->Reference_byte), FJ2207_CHIP_ADDRESS, Reference_byte);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->IR_MIXER_byte_2), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->Power_byte_2), FJ2207_CHIP_ADDRESS, Power_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->AGC1_byte_1), FJ2207_CHIP_ADDRESS, AGC1_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->AGC1_byte_2), FJ2207_CHIP_ADDRESS, AGC1_byte_2);
	if (resp){
		return resp;
	}
	
	resp = fj2207_get_byte_register(h, &(h->RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
	if (resp){
		return resp;
	}
	
	resp = fj2207_get_byte_register(h, &(h->IR_MIXER_byte_1), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_1);
	if (resp){
		return resp;
	}
	
	resp = fj2207_get_byte_register(h, &(h->AGC5_byte_1), FJ2207_CHIP_ADDRESS, AGC5_byte_1);
	if (resp){
		return resp;
	}
	
	resp = fj2207_get_byte_register(h, &(h->PSM_byte_1), FJ2207_CHIP_ADDRESS, PSM_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->RF_AGC_Gain_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_Gain_byte_1);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->RF_AGC_Gain_byte_2), FJ2207_CHIP_ADDRESS, RF_AGC_Gain_byte_2);
	if (resp){
		return resp;
	}
	resp = fj2207_get_byte_register(h, &(h->IF_AGC_Gain_byte), FJ2207_CHIP_ADDRESS, IF_AGC_Gain_byte);
	if (resp){
		return resp;
	}
	//end of registers initialization
	
	//send stop sequence
	i2c_send_stop_sequence(&(h->i2c_handle));
#endif
	return I2c_Success;
}

I2cResponseType fj2207_init(Fj2207Handle *h, GpioPin *i2c_sda, GpioPin *i2c_scl){
	I2cResponseType resp;
	
	/*i2c initialization*/
	i2c_init(&(h->i2c_handle), i2c_sda, i2c_scl);

	/*handle the registers*/
	resp = fj2207_read_registers(h);
	if (resp){
		return resp;
	}
	return I2c_Success;
}

Fj2207ReturnType fj2207_read_field(Fj2207Handle *h, Fj2207Ident field_id){
	I2cResponseType resp;
	switch(field_id){
		case Ident:
			resp = fj2207_get_byte_register(h, &(h->ID_byte_1), FJ2207_CHIP_ADDRESS, ID_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->Ident = h->ID_byte_1;
			h->Ident &=	0x7F;
			h->Ident <<= BYTE_SIZE;
			h->Ident |= h->ID_byte_2;
		return Fj2207Success;
		
		case Major_rev:
			resp = fj2207_get_byte_register(h, &(h->ID_byte_2), FJ2207_CHIP_ADDRESS, ID_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->Major_rev = h->ID_byte_3;
			h->Major_rev >>= FOUR_BITS_SIZE;
		return Fj2207Success;
		
		case Minor_rev:
			resp = fj2207_get_byte_register(h, &(h->ID_byte_3), FJ2207_CHIP_ADDRESS, ID_byte_3);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->Minor_rev = h->ID_byte_3;
			h->Minor_rev &=	0x0F;
		return Fj2207Success;
		
		case TM_D:
			resp = fj2207_get_byte_register(h, &(h->Thermo_byte_1), FJ2207_CHIP_ADDRESS, Thermo_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->TM_D = h->Thermo_byte_1;
			h->TM_D &= 0x7F;
		return Fj2207Success;
		
		case TM_ON:
			resp = fj2207_get_byte_register(h, &(h->Thermo_byte_2), FJ2207_CHIP_ADDRESS, Thermo_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->TM_ON = h->Thermo_byte_2;
			h->TM_ON &=	0x01;
		return Fj2207Success;
		
		case POR:
			resp = fj2207_get_byte_register(h, &(h->Power_state_byte_1), FJ2207_CHIP_ADDRESS, Power_state_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->POR = h->Power_state_byte_1;
			h->POR &=	0x02;
			h->POR >>= 1;
		return Fj2207Success;
		
		case LO_Lock:
			resp = fj2207_get_byte_register(h, &(h->Power_state_byte_1), FJ2207_CHIP_ADDRESS, Power_state_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->LO_Lock = h->Power_state_byte_1;
			h->LO_Lock &=	0x01;
		return Fj2207Success;
		
		case SM_LNA:
			resp = fj2207_get_byte_register(h, &(h->Power_state_byte_2), FJ2207_CHIP_ADDRESS, Power_state_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->SM_LNA = h->Power_state_byte_2;
			h->SM_LNA &=	0x02;
			h->SM_LNA >>= 1;
		return Fj2207Success;
		
		case SM_PLL:
			resp = fj2207_get_byte_register(h, &(h->Power_state_byte_2), FJ2207_CHIP_ADDRESS, Power_state_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->SM_PLL = h->Power_state_byte_2;
			h->SM_PLL &= 0x04;
			h->SM_PLL >>= 2;
		return Fj2207Success;

		case SM:
			resp = fj2207_get_byte_register(h, &(h->Power_state_byte_2), FJ2207_CHIP_ADDRESS, Power_state_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->SM = h->Power_state_byte_2;
			h->SM &= 0x08;
			h->SM >>= 3;
		return Fj2207Success;
		
		case Power_Level:
			resp = fj2207_get_byte_register(h, &(h->Input_Power_Level_byte), FJ2207_CHIP_ADDRESS, Input_Power_Level_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->Power_Level = h->Input_Power_Level_byte;
			h->Power_Level &= 0x7F;
		return Fj2207Success;
		
		case IF_Freq:
			resp = fj2207_get_byte_register(h, &(h->IF_Frequency_byte), FJ2207_CHIP_ADDRESS, IF_Frequency_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->IF_Freq = h->IF_Frequency_byte;
		return Fj2207Success;
		
		case RF_Freq:
			h->RF_Freq = 0;
			resp = fj2207_get_byte_register(h, &(h->RF_Frequency_byte_1), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_1);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->RF_Freq = h->RF_Frequency_byte_1;
			h->RF_Freq &= 0x0F;
			h->RF_Freq <<= BYTE_SIZE;
			resp = fj2207_get_byte_register(h, &(h->RF_Frequency_byte_3), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_3);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->RF_Freq |= h->RF_Frequency_byte_3;
			h->RF_Freq <<= BYTE_SIZE;
			resp = fj2207_get_byte_register(h, &(h->RF_Frequency_byte_2), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_2);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			i2c_send_stop_sequence(&(h->i2c_handle));
			h->RF_Freq |= h->RF_Frequency_byte_2;
		return Fj2207Success;
			
		case POWER_Meas:
			resp = fj2207_get_byte_register(h, &(h->MSM_Byte_1), FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->MSM_Byte_1 &= 0xFB;
			h->POWER_Meas = h->MSM_Byte_1;
			h->POWER_Meas &= 0x80;
			h->POWER_Meas >>= 7;
		return Fj2207Success;
		
		case RF_CAL_AV:
			resp = fj2207_get_byte_register(h, &(h->MSM_Byte_1), FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->MSM_Byte_1 &= 0xFB;
			h->RF_CAL_AV = h->MSM_Byte_1;
			h->RF_CAL_AV &= 0x40;
			h->RF_CAL_AV >>= 6;
		return Fj2207Success;
		
		case RF_CAL:
			resp = fj2207_get_byte_register(h, &(h->MSM_Byte_1), FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->MSM_Byte_1 &= 0xFB;
			h->RF_CAL = h->MSM_Byte_1;
			h->RF_CAL &= 0x20;
			h->RF_CAL >>= 5;
		return Fj2207Success;
		
		case IR_CAL:
			resp = fj2207_get_byte_register(h, &(h->MSM_Byte_1), FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->MSM_Byte_1 &= 0xFB;
			h->IR_CAL = h->MSM_Byte_1;
			h->IR_CAL &= 0x18;
			h->IR_CAL >>= 3;
		return Fj2207Success;
		
		case RC_CAL:
			resp = fj2207_get_byte_register(h, &(h->MSM_Byte_1), FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->MSM_Byte_1 &= 0xFB;
			h->RC_CAL = h->MSM_Byte_1;
			h->RC_CAL &= 0x02;
			h->RC_CAL >>= 1;
		return Fj2207Success;
		
		case Calc_PLL:
			resp = fj2207_get_byte_register(h, &(h->MSM_Byte_1), FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->MSM_Byte_1 &= 0xFB;
			h->Calc_PLL = h->MSM_Byte_1;
			h->Calc_PLL &= 0x01;
		return Fj2207Success;
		
		case MSM_Launch:
			resp = fj2207_get_byte_register(h, &(h->MSM_Byte_2), FJ2207_CHIP_ADDRESS, MSM_Byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->MSM_Launch = h->MSM_Byte_2;
			h->MSM_Launch &= 0x01;
		return Fj2207Success;
		
		case Pulse_Shaper_disable:
			resp = fj2207_get_byte_register(h, &(h->AGCK_byte_1), FJ2207_CHIP_ADDRESS, AGCK_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->Pulse_Shaper_disable = h->AGCK_byte_1;
			h->Pulse_Shaper_disable &= 0x10;
			h->Pulse_Shaper_disable >>= 4;
		return Fj2207Success;
		
		case AGCK_mode:
			resp = fj2207_get_byte_register(h, &(h->AGCK_byte_1), FJ2207_CHIP_ADDRESS, AGCK_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->AGCK_mode = h->AGCK_byte_1;
			h->AGCK_mode &= 0x03;
		return Fj2207Success;
		
		case IF_HP_Fc:
			resp = fj2207_get_byte_register(h, &(h->IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->IF_HP_Fc = h->IF_byte_1;
			h->IF_HP_Fc &= 0xC0;
			h->IF_HP_Fc >>= 6;
		return Fj2207Success;
		
		case IF_Notch:
			resp = fj2207_get_byte_register(h, &(h->IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->IF_Notch = h->IF_byte_1;
			h->IF_Notch &= 0x20;
			h->IF_Notch >>= 5;
		return Fj2207Success;
		
		case LP_FC_Offset:
			resp = fj2207_get_byte_register(h, &(h->IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->LP_FC_Offset = h->IF_byte_1;
			h->LP_FC_Offset &= 0x18;
			h->LP_FC_Offset >>= 3;
		return Fj2207Success;
		
		case LP_Fc:
			resp = fj2207_get_byte_register(h, &(h->IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->LP_Fc = h->IF_byte_1;
			h->LP_Fc &= 0x07;
		return Fj2207Success;
		
		case IF_Level:
			resp = fj2207_get_byte_register(h, &(h->IF_AGC_byte), FJ2207_CHIP_ADDRESS, IF_AGC_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->IF_Level = h->IF_AGC_byte;
			h->IF_Level &= 0x07;
		return Fj2207Success;
		
		case XTout:
			resp = fj2207_get_byte_register(h, &(h->Reference_byte), FJ2207_CHIP_ADDRESS, Reference_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->XTout = h->Reference_byte;
			h->XTout &= 0x03;
		return Fj2207Success;
		
		case Digital_Clock:
			resp = fj2207_get_byte_register(h, &(h->Reference_byte), FJ2207_CHIP_ADDRESS, Reference_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->Digital_Clock = h->Reference_byte;
			h->Digital_Clock &= 0x40;
			h->Digital_Clock >>= 6;
		return Fj2207Success;
		
		case HI_Pass:
			resp = fj2207_get_byte_register(h, &(h->IR_MIXER_byte_2), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->HI_Pass = h->IR_MIXER_byte_2;
			h->HI_Pass &= 0x02;
			h->HI_Pass >>= 1;
		return Fj2207Success;
		
		case DC_NOTCH:
			resp = fj2207_get_byte_register(h, &(h->IR_MIXER_byte_2), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->DC_NOTCH = h->IR_MIXER_byte_2;
			h->DC_NOTCH &= 0x01;
		return Fj2207Success;		

		case LT_Enable:
			resp = fj2207_get_byte_register(h, &(h->AGC1_byte_1), FJ2207_CHIP_ADDRESS, AGC1_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->LT_Enable = h->AGC1_byte_1;
			h->LT_Enable &= 0x80;
			h->LT_Enable >>= 7;
		return Fj2207Success;
		
		case AGC1_6_15dB:
			resp = fj2207_get_byte_register(h, &(h->AGC1_byte_1), FJ2207_CHIP_ADDRESS, AGC1_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->AGC1_6_15dB = h->AGC1_byte_1;
			h->AGC1_6_15dB &= 0x40;
			h->AGC1_6_15dB >>= 6;
		return Fj2207Success;		
		
		case AGC1_TOP:
			resp = fj2207_get_byte_register(h, &(h->AGC1_byte_1), FJ2207_CHIP_ADDRESS, AGC1_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->AGC1_TOP = h->AGC1_byte_1;
			h->AGC1_TOP &= 0x0F;
		return Fj2207Success;		
		
		case AGC1_byte_2:
			resp = fj2207_get_byte_register(h, &(h->AGC1_byte_2), FJ2207_CHIP_ADDRESS, AGC1_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->AGC1_byte_2 &= 0x1F; 
		return Fj2207Success;
		
		case Power_byte_2:
			resp = fj2207_get_byte_register(h, &(h->Power_byte_2), FJ2207_CHIP_ADDRESS, Power_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->Power_byte_2 &= 0x2F; 
		return Fj2207Success;
			
		case PD_RFAGC_Adapt:
			resp = fj2207_get_byte_register(h, &(h->RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->PD_RFAGC_Adapt = h->RF_AGC_byte_1;
			h->PD_RFAGC_Adapt >>= 7;
		return Fj2207Success;
			
		case RFAGC_Adapt_TOP:
			resp = fj2207_get_byte_register(h, &(h->RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->RFAGC_Adapt_TOP = RF_AGC_byte_1;
			h->RFAGC_Adapt_TOP >>= 5;
			h->RFAGC_Adapt_TOP &= 0x03;
		return Fj2207Success;
		
		case RF_Atten_3dB:
			resp = fj2207_get_byte_register(h, &(h->RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->RF_Atten_3dB = h->RF_AGC_byte_1;
			h->RF_Atten_3dB >>= 3;
			h->RF_Atten_3dB &= 0x01;
		return Fj2207Success;
		
		case AGC3_Top:
			resp = fj2207_get_byte_register(h, &(h->RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->AGC3_Top = h->RF_AGC_byte_1;
			h->AGC3_Top &= 0x07;
		return Fj2207Success;
		
		case AGC4_Top:
			resp = fj2207_get_byte_register(h, &(h->IR_MIXER_byte_1), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->AGC4_Top = h->IR_MIXER_byte_1;
			h->AGC4_Top &= 0x0F;
		return Fj2207Success;
		
		case AGC5_Top:
			resp = fj2207_get_byte_register(h, &(h->AGC5_byte_1), FJ2207_CHIP_ADDRESS, AGC5_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->AGC5_Top = h->AGC5_byte_1;
			h->AGC5_Top &= 0x0F;
		return Fj2207Success;
			
		case AGC5_HPF:
			resp = fj2207_get_byte_register(h, &(h->AGC5_byte_1), FJ2207_CHIP_ADDRESS, AGC5_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->AGC5_HPF = h->AGC5_byte_1;
			h->AGC5_HPF &= 0x80;
			h->AGC5_HPF >>= 3;
		return Fj2207Success;
		
		case VHFIII:
			resp = fj2207_get_byte_register(h, &(h->PSM_byte_1), FJ2207_CHIP_ADDRESS, PSM_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->VHFIII = h->PSM_byte_1;
			h->VHFIII &= 0x20;
			h->VHFIII >>= 5;
		return Fj2207Success;
		
		case RF_FILTER_GAIN:
			resp = fj2207_get_byte_register(h, &(h->RF_AGC_Gain_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_Gain_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->RF_FILTER_GAIN = h->RF_AGC_Gain_byte_1;
			h->RF_FILTER_GAIN &= 0x30;
			h->RF_FILTER_GAIN >>= 4;
		return Fj2207Success;
		
		case LNA_GAIN:
			resp = fj2207_get_byte_register(h, &(h->RF_AGC_Gain_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_Gain_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->LNA_GAIN = h->RF_AGC_Gain_byte_1;
			h->LNA_GAIN &= 0x0F;
		return Fj2207Success;
		
		case TOP_Agc3_read:
			resp = fj2207_get_byte_register(h, &(h->RF_AGC_Gain_byte_2), FJ2207_CHIP_ADDRESS, RF_AGC_Gain_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->TOP_Agc3_read = h->RF_AGC_Gain_byte_2;
			h->TOP_Agc3_read &= 0x07;
		return Fj2207Success;
		
		case LPF_GAIN:
			resp = fj2207_get_byte_register(h, &(h->IF_AGC_Gain_byte), FJ2207_CHIP_ADDRESS, IF_AGC_Gain_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->LPF_GAIN = h->IF_AGC_Gain_byte;
			h->LPF_GAIN &= 0x18;
			h->LPF_GAIN >>= 3;
		return Fj2207Success;
		
		case IR_MIXER:
			resp = fj2207_get_byte_register(h, &(h->IF_AGC_Gain_byte), FJ2207_CHIP_ADDRESS, IF_AGC_Gain_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			h->IR_MIXER = h->IF_AGC_Gain_byte;
			h->IR_MIXER &= 0x07;
		return Fj2207Success;
		
		default:
		return Fj2207FieldIsNoDefined;				
	}
}

Fj2207ReturnType fj2207_write_field(Fj2207Handle *h, Fj2207Ident field_id){
	uint32 temp;
	switch(field_id){
		case TM_ON:
			h->Thermo_byte_1 = h->TM_D;
			fj2207_write_byte_register(h, h->Thermo_byte_1, FJ2207_CHIP_ADDRESS, Thermo_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;

		case SM_LNA:
			if (h->SM_LNA){
				h->SM_LNA <<= 1;
				h->Power_state_byte_2 |= h->SM_LNA;
				h->SM_LNA = 0x01;		
			} else {
				h->SM_LNA = 0x02;
				h->Power_state_byte_2 &= ~(h->SM_LNA);
				h->SM_LNA = 0x00;
			}
			fj2207_write_byte_register(h, h->Power_state_byte_2, FJ2207_CHIP_ADDRESS, Power_state_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case SM_PLL:
			if (h->SM_LNA){
				h->SM_PLL <<= 2;
				h->Power_state_byte_2 |= h->SM_PLL;
				h->SM_PLL = 0x01;	
			} else {
				h->SM_PLL = 0x01;
				h->SM_PLL <<= 2;
				h->Power_state_byte_2 &= ~(h->SM_PLL);
				h->SM_PLL = 0x00;
			}
			fj2207_write_byte_register(h, h->Power_state_byte_2, FJ2207_CHIP_ADDRESS, Power_state_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case SM:
			if (h->SM){
				h->SM <<= 3;
				h->Power_state_byte_2 |= h->SM;
				h->SM = 0x01;
			} else {
				h->SM = 0x01;
				h->SM <<= 3;
				h->Power_state_byte_2 &= ~(h->SM);
				h->SM = 0x00;
			}
			fj2207_write_byte_register(h, h->Power_state_byte_2, FJ2207_CHIP_ADDRESS, Power_state_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case IF_Freq:
			h->IF_Frequency_byte = h->IF_Freq;
			fj2207_write_byte_register(h, h->IF_Frequency_byte, FJ2207_CHIP_ADDRESS, IF_Frequency_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;

		case RF_Freq:
			temp = h->RF_Freq;
			h->RF_Frequency_byte_2 = h->RF_Freq;
			fj2207_write_byte_register(h, h->RF_Frequency_byte_2, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_2);
			h->RF_Freq >>= BYTE_SIZE;
			h->RF_Frequency_byte_3 = h->RF_Freq;
			fj2207_write_byte_register(h, h->RF_Frequency_byte_3, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_3);
			h->RF_Freq >>= BYTE_SIZE;
			h->RF_Frequency_byte_1 = h->RF_Freq;
			h->RF_Freq = temp;
			fj2207_write_byte_register(h, h->RF_Frequency_byte_1, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
			
		case POWER_Meas:
				if (h->POWER_Meas){
				h->POWER_Meas <<= 7;
				h->MSM_Byte_1 |= h->RF_CAL;	
				h->POWER_Meas = 0x01;	
			} else {
				h->POWER_Meas = 0x01;
				h->POWER_Meas <<= 7;
				h->MSM_Byte_1 &= ~(h->RF_CAL);
				h->POWER_Meas = 0x00;
			}
			fj2207_write_byte_register(h, h->MSM_Byte_1, FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case RF_CAL_AV:
			if (h->RF_CAL_AV){
				h->RF_CAL_AV <<= 6;
				h->MSM_Byte_1 |= h->RF_CAL_AV;
				h->RF_CAL_AV = 0x01;		
			} else {
				h->RF_CAL_AV = 0x40;
				h->MSM_Byte_1 &= ~(h->RF_CAL_AV);
				h->RF_CAL_AV = 0x00;
			}
			fj2207_write_byte_register(h, h->MSM_Byte_1, FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case RF_CAL:
			if (h->RF_CAL){
				h->RF_CAL <<= 5;
				h->MSM_Byte_1 |= h->RF_CAL;
				h->RF_CAL = 0x01;		
			} else {
				h->RF_CAL = 0x01;
				h->RF_CAL <<= 5;
				h->MSM_Byte_1 &= ~(h->RF_CAL);
				h->RF_CAL = 0x00;
			}
			fj2207_write_byte_register(h, h->MSM_Byte_1, FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case IR_CAL:
			temp = h->IR_CAL;
			h->IR_CAL &= 0x02;
			if (h->IR_CAL){
				h->IR_CAL <<= 3;
				h->MSM_Byte_1 |= h->IR_CAL;	
			} else {
				h->IR_CAL = 0x02;
				h->IR_CAL <<= 3;
				h->MSM_Byte_1 &= ~(h->IR_CAL);
			}
			h->IR_CAL = temp;
			h->IR_CAL &= 0x01;
			if (h->IR_CAL){
				h->IR_CAL <<= 3;
				h->MSM_Byte_1 |= h->IR_CAL;		
			} else {
				h->IR_CAL = 0x01;
				h->IR_CAL <<= 3;
				h->MSM_Byte_1 &= ~(h->IR_CAL);
			}
			h->IR_CAL = temp;
			fj2207_write_byte_register(h, h->MSM_Byte_1, FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case RC_CAL:
			if (h->RC_CAL){
				h->RC_CAL <<= 1;
				h->MSM_Byte_1 |= h->RC_CAL;
				h->RC_CAL = 0x01;		
			} else {
				h->RC_CAL = 0x01;
				h->RC_CAL <<= 1;
				h->MSM_Byte_1 &= ~(h->RC_CAL);
				h->RC_CAL = 0x00;
			}
			fj2207_write_byte_register(h, h->MSM_Byte_1, FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case Calc_PLL:
			if (h->Calc_PLL){
				h->MSM_Byte_1 |= h->Calc_PLL;		
			} else {
				h->Calc_PLL = 0x01;
				h->MSM_Byte_1 &= ~(h->Calc_PLL);
				h->Calc_PLL = 0x00;
			}
			fj2207_write_byte_register(h, h->MSM_Byte_1, FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case MSM_Launch:
			if (h->MSM_Launch){
				h->MSM_Byte_2 |= h->MSM_Launch;		
			} else {
				h->MSM_Launch = 0x01;
				h->MSM_Byte_2 &= ~(h->MSM_Launch);
				h->MSM_Launch = 0x00;
			}
			fj2207_write_byte_register(h, h->MSM_Byte_2, FJ2207_CHIP_ADDRESS, MSM_Byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));	
		return Fj2207Success;
		
		case Pulse_Shaper_disable:
			if (h->Pulse_Shaper_disable){
				h->Pulse_Shaper_disable <<= 4;
				h->Pulse_Shaper_disable |= h->AGCK_byte_1;
				h->Pulse_Shaper_disable = 0x01;
			} else {
				h->Pulse_Shaper_disable = 0x01;
				h->Pulse_Shaper_disable <<= 4;
				h->AGCK_byte_1 &= ~(h->Pulse_Shaper_disable);
				h->Pulse_Shaper_disable = 0x00;
			}
			fj2207_write_byte_register(h, h->AGCK_byte_1, FJ2207_CHIP_ADDRESS, AGCK_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));	
		return Fj2207Success;
			
		case AGCK_mode:
			temp = h->AGCK_mode;
			h->AGCK_mode &= 0x02;
			if (h->AGCK_mode){
				h->AGCK_byte_1 |= h->AGCK_mode;	
			} else {
				h->AGCK_mode = 0x02;
				h->AGCK_byte_1 &= ~(h->AGCK_mode);
			}
			h->AGCK_mode = temp;
			h->AGCK_mode &= 0x01;
			if (h->AGCK_mode){
				h->AGCK_byte_1 |= h->AGCK_mode;		
			} else {
				h->AGCK_mode = 0x01;
				h->AGCK_byte_1 &= ~(h->AGCK_mode);
			}
			h->AGCK_mode = temp;
			fj2207_write_byte_register(h, h->AGCK_byte_1, FJ2207_CHIP_ADDRESS, AGCK_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case IF_HP_Fc:
			temp = h->IF_HP_Fc;
			h->IF_HP_Fc &= 0x02;
			if (h->IF_HP_Fc){
				h->IF_HP_Fc <<= 6;
				h->IF_byte_1 |= h->IF_HP_Fc;	
			} else {
				h->IF_HP_Fc = 0x02;
				h->IF_HP_Fc <<= 6;
				h->IF_byte_1 &= ~(h->IF_HP_Fc);
			}
			h->IF_HP_Fc = temp;
			h->IF_HP_Fc &= 0x01;
			if (h->IF_HP_Fc){
				h->IF_HP_Fc <<= 6;
				h->IF_byte_1 |= h->IF_HP_Fc;	
			} else {
				h->IF_HP_Fc = 0x01;
				h->IF_HP_Fc <<= 6;
				h->IF_byte_1 &= ~(h->IF_HP_Fc);
			}
			h->IF_HP_Fc = temp;
			fj2207_write_byte_register(h, h->IF_byte_1, FJ2207_CHIP_ADDRESS, IF_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case IF_Notch:
			if (h->IF_Notch){
				h->IF_Notch <<= 5;
				h->IF_byte_1 |= h->IF_Notch;
				h->IF_Notch = 0x01;
			} else {
				h->IF_Notch = 0x01;
				h->IF_Notch <<= 5;
				h->IF_byte_1 &= ~(h->IF_Notch);
				h->IF_Notch = 0x00;
			}
			fj2207_write_byte_register(h, h->IF_byte_1, FJ2207_CHIP_ADDRESS, IF_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case LP_FC_Offset:
			temp = h->LP_FC_Offset;
			h->LP_FC_Offset &= 0x02;
			if (h->LP_FC_Offset){
				h->LP_FC_Offset <<= 3;
				h->IF_byte_1 |= h->LP_FC_Offset;	
			} else {
				h->LP_FC_Offset = 0x02;
				h->LP_FC_Offset <<= 3;
				h->IF_byte_1 &= ~(h->LP_FC_Offset);
			}
			h->LP_FC_Offset = temp;
			h->LP_FC_Offset &= 0x01;
			if (h->LP_FC_Offset){
				h->LP_FC_Offset <<= 3;
				h->IF_byte_1 |= h->LP_FC_Offset;	
			} else {
				h->LP_FC_Offset = 0x01;
				h->LP_FC_Offset <<= 3;
				h->IF_byte_1 &= ~(h->LP_FC_Offset);
			}
			h->IF_HP_Fc = temp;
			fj2207_write_byte_register(h, h->IF_byte_1, FJ2207_CHIP_ADDRESS, IF_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case LP_Fc:
			temp = h->LP_Fc;
			h->LP_Fc &= 0x04;
			if (h->LP_Fc){
				h->IF_byte_1 |= h->LP_Fc;	
			} else {
				h->LP_Fc = 0x04;
				h->IF_byte_1 &= ~(h->LP_Fc);
			}
			h->LP_Fc = temp;
			h->LP_Fc &= 0x02;
			if (h->LP_Fc){
				h->IF_byte_1 |= h->LP_Fc;	
			} else {
				h->LP_Fc = 0x02;
				h->IF_byte_1 &= ~(h->LP_Fc);
			}
			h->LP_Fc = temp;
			h->LP_Fc &= 0x01;
			if (h->LP_Fc){
				h->IF_byte_1 |= h->LP_Fc;	
			} else {
				h->LP_Fc = 0x01;
				h->IF_byte_1 &= ~(h->LP_Fc);
			}
			h->LP_Fc = temp;
			fj2207_write_byte_register(h, h->IF_byte_1, FJ2207_CHIP_ADDRESS, IF_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case IF_Level:
			h->IF_AGC_byte = h->IF_Level;	
			fj2207_write_byte_register(h, h->IF_AGC_byte, FJ2207_CHIP_ADDRESS, IF_AGC_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case XTout:
			temp = h->XTout;
			h->XTout &= 0x01; 
			if (h->XTout){
				h->XTout |= h->Reference_byte;	
			} else {
				h->XTout = 0x01;
				h->Reference_byte &= ~(h->XTout);
			}
			h->XTout = temp;
			h->XTout &= 0x02;
			if (h->XTout){
				h->XTout |= h->Reference_byte;	
			} else {
				h->XTout = 0x02;
				h->Reference_byte &= ~(h->XTout);
			}
			h->XTout = temp;
			fj2207_write_byte_register(h, h->Reference_byte, FJ2207_CHIP_ADDRESS, Reference_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case Digital_Clock:
			if (h->Digital_Clock){
				h->Digital_Clock <<= 6;
				h->Digital_Clock |= h->Reference_byte;
				h->Digital_Clock = 0x01;
			} else {
				h->Digital_Clock = 0x40;
				h->Reference_byte &= ~(h->Digital_Clock);
				h->Digital_Clock = 0x00;
			}
			fj2207_write_byte_register(h, h->Reference_byte, FJ2207_CHIP_ADDRESS, Reference_byte);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case HI_Pass:
			if (h->HI_Pass){
				h->HI_Pass <<= 1;
				h->IR_MIXER_byte_2 |= h->HI_Pass;
				h->HI_Pass = 0x01;
			} else {
				h->HI_Pass = 0x02;
				h->IR_MIXER_byte_2 &= ~(h->HI_Pass);
				h->HI_Pass = 0x00;
			}
			fj2207_write_byte_register(h, h->IR_MIXER_byte_2, FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case DC_NOTCH:
			if (h->DC_NOTCH){
				h->IR_MIXER_byte_2 |= h->DC_NOTCH;
				h->DC_NOTCH = 0x01;
			} else {
				h->DC_NOTCH = 0x01;
				h->IR_MIXER_byte_2 &= ~(h->DC_NOTCH);
				h->DC_NOTCH = 0x00;
			}
			fj2207_write_byte_register(h, h->IR_MIXER_byte_2, FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case LT_Enable:
			if (h->LT_Enable){
				h->LT_Enable <<= 7;
				h->AGC1_byte_1 |= h->LT_Enable;
				h->LT_Enable = 0x01;
			} else {
				h->LT_Enable = 0x80;
				h->AGC1_byte_1 &= ~(h->LT_Enable);
				h->LT_Enable = 0x00;
			}
			fj2207_write_byte_register(h, h->AGC1_byte_1, FJ2207_CHIP_ADDRESS, AGC1_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case AGC1_6_15dB:
			if (h->AGC1_6_15dB){
				h->AGC1_6_15dB <<= 6;
				h->AGC1_byte_1 |= h->AGC1_6_15dB;
				h->AGC1_6_15dB = 0x01;
			} else {
				h->AGC1_6_15dB = 0x40;
				h->AGC1_byte_1 &= ~(h->AGC1_6_15dB);
				h->AGC1_6_15dB = 0x00;
			}
			fj2207_write_byte_register(h, h->AGC1_byte_1, FJ2207_CHIP_ADDRESS, AGC1_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;		
		
		case AGC1_TOP:
			temp = h->AGC1_TOP;
			h->AGC1_TOP &= 0x08;
			if (h->AGC1_6_15dB){
				h->AGC1_byte_1 |= h->AGC1_TOP;
				h->AGC1_TOP = temp;
			} else {
				h->AGC1_6_15dB = 0x08;
				h->AGC1_byte_1 &= ~(h->AGC1_TOP);
				h->AGC1_TOP = temp;
			}
			h->AGC1_TOP &= 0x04;
			if (h->AGC1_6_15dB){
				h->AGC1_byte_1 |= h->AGC1_TOP;
				h->AGC1_TOP = temp;
			} else {
				h->AGC1_6_15dB = 0x04;
				h->AGC1_byte_1 &= ~(h->AGC1_TOP);
				h->AGC1_TOP = temp;
			}
			h->AGC1_TOP &= 0x02;
			if (h->AGC1_6_15dB){
				h->AGC1_byte_1 |= h->AGC1_TOP;
				h->AGC1_TOP = temp;
			} else {
				h->AGC1_6_15dB = 0x02;
				h->AGC1_byte_1 &= ~(h->AGC1_TOP);
				h->AGC1_TOP = temp;
			}
			h->AGC1_TOP &= 0x01;
			if (h->AGC1_6_15dB){
				h->AGC1_byte_1 |= h->AGC1_TOP;
				h->AGC1_TOP = temp;
			} else {
				h->AGC1_6_15dB = 0x01;
				h->AGC1_byte_1 &= ~(h->AGC1_TOP);
				h->AGC1_TOP = temp;
			}
			fj2207_write_byte_register(h, h->AGC1_byte_1, FJ2207_CHIP_ADDRESS, AGC1_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;	
		
		case AGC1_byte_2:
			fj2207_write_byte_register(h, h->AGC1_byte_2, FJ2207_CHIP_ADDRESS, AGC1_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case Power_byte_2:
			fj2207_write_byte_register(h, h->Power_byte_2, FJ2207_CHIP_ADDRESS, Power_byte_2);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case PD_RFAGC_Adapt:
			h->PD_RFAGC_Adapt <<= 7;
			if (h->PD_RFAGC_Adapt){
				h->RF_AGC_byte_1 |= h->PD_RFAGC_Adapt;
				h->PD_RFAGC_Adapt = 0x01;
			}else{
				h->RF_AGC_byte_1 &= ~(h->PD_RFAGC_Adapt);
				h->PD_RFAGC_Adapt = 0x00;
			}
			fj2207_write_byte_register(h, h->RF_AGC_byte_1, FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
			
		case RFAGC_Adapt_TOP:
			temp = h->RFAGC_Adapt_TOP;
			h->RFAGC_Adapt_TOP &= 0x02;
			if (h->RFAGC_Adapt_TOP){
				h->RFAGC_Adapt_TOP <<= 5;
				h->RF_AGC_byte_1 |= h->RFAGC_Adapt_TOP;
				h->PD_RFAGC_Adapt = temp;
			}else{
				h->RFAGC_Adapt_TOP = 0x02;
				h->RFAGC_Adapt_TOP <<= 5;
				h->RF_AGC_byte_1 &= ~(h->RFAGC_Adapt_TOP);
				h->PD_RFAGC_Adapt = temp;
			}
			h->RFAGC_Adapt_TOP &= 0x01;
			if (h->RFAGC_Adapt_TOP){
				h->RFAGC_Adapt_TOP <<= 5;
				h->RF_AGC_byte_1 |= h->RFAGC_Adapt_TOP;
				h->PD_RFAGC_Adapt = temp;
			}else{
				h->RFAGC_Adapt_TOP = 0x01;
				h->RFAGC_Adapt_TOP <<= 5;
				h->RF_AGC_byte_1 &= ~(h->RFAGC_Adapt_TOP);
				h->PD_RFAGC_Adapt = temp;
			}
			fj2207_write_byte_register(h, h->RF_AGC_byte_1, FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case RF_Atten_3dB:
			if (h->RF_Atten_3dB){
				h->RF_Atten_3dB <<= 3;
				h->RF_AGC_byte_1 |= h->RF_Atten_3dB;
				h->RF_Atten_3dB = 0x01;
			}else{
				h->RF_Atten_3dB = 0x01;
				h->RF_Atten_3dB <<= 3;
				h->RF_AGC_byte_1 &= ~(h->RF_Atten_3dB);
				h->RF_Atten_3dB = 0x00;
			}
			fj2207_write_byte_register(h, h->RF_AGC_byte_1, FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case AGC3_Top:
			temp = h->AGC3_Top;
			h->AGC3_Top &= 0x04;
			if (h->AGC3_Top){
				h->RF_AGC_byte_1 |= h->AGC3_Top;
				h->AGC3_Top = temp;
			}else{
				h->AGC3_Top = 0x04;
				h->RF_AGC_byte_1 &= ~(h->AGC3_Top);
				h->AGC3_Top = temp;
			}
			h->AGC3_Top &= 0x02;
			if (h->AGC3_Top){
				h->RF_AGC_byte_1 |= h->AGC3_Top;
				h->AGC3_Top = temp;
			}else{
				h->AGC3_Top = 0x02;
				h->RF_AGC_byte_1 &= ~(h->AGC3_Top);
				h->AGC3_Top = temp;
			}
			h->AGC3_Top &= 0x01;
			if (h->AGC3_Top){
				h->RF_AGC_byte_1 |= h->AGC3_Top;
				h->AGC3_Top = temp;
			}else{
				h->AGC3_Top = 0x01;
				h->RF_AGC_byte_1 &= ~(h->AGC3_Top);
				h->AGC3_Top = temp;
			}
			fj2207_write_byte_register(h, h->RF_AGC_byte_1, FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;		
		
		case AGC4_Top:
			temp = h->AGC4_Top;
			if (h->AGC4_Top){
				h->AGC4_Top &= 0x04;
				h->IR_MIXER_byte_1 |= h->AGC4_Top;
				h->AGC4_Top = temp;
			} else {
				h->AGC4_Top = 0x04;
				h->IR_MIXER_byte_1 &= ~(h->AGC4_Top);
				h->AGC4_Top = temp;
			}
			h->AGC4_Top &= 0x02;
			if (h->AGC4_Top){
				h->IR_MIXER_byte_1 |= h->AGC4_Top;
				h->AGC4_Top = temp;
			} else {
				h->AGC4_Top = 0x02;
				h->IR_MIXER_byte_1 &= ~(h->AGC4_Top);
				h->AGC4_Top = temp;
			}
			h->AGC4_Top &= 0x01;
			if (h->AGC4_Top){
				h->IR_MIXER_byte_1 |= h->AGC4_Top;
				h->AGC4_Top = temp;
			} else {
				h->AGC4_Top = 0x01;
				h->IR_MIXER_byte_1 &= ~(h->AGC4_Top);
				h->AGC4_Top = temp;
			}
			fj2207_write_byte_register(h, h->IR_MIXER_byte_1, FJ2207_CHIP_ADDRESS, IR_MIXER_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case AGC5_Top:
			temp = h->AGC5_Top;
			if (h->AGC5_Top){
				h->AGC5_Top &= 0x04;
				h->AGC5_byte_1 |= h->AGC5_Top;
				h->AGC5_Top = temp;
			} else {
				h->AGC5_Top = 0x04;
				h->AGC5_byte_1 &= ~(h->AGC5_Top);
				h->AGC5_Top = temp;
			}
			h->AGC1_TOP &= 0x02;
			if (h->AGC5_Top){
				h->AGC5_byte_1 |= h->AGC5_Top;
				h->AGC5_Top = temp;
			} else {
				h->AGC5_Top = 0x02;
				h->AGC5_byte_1 &= ~(h->AGC5_Top);
				h->AGC5_Top = temp;
			}
			h->AGC1_TOP &= 0x01;
			if (h->AGC5_Top){
				h->AGC5_byte_1 |= h->AGC5_Top;
				h->AGC5_Top = temp;
			} else {
				h->AGC5_Top = 0x01;
				h->AGC5_byte_1 &= ~(h->AGC5_Top);
				h->AGC5_Top = temp;
			}
			fj2207_write_byte_register(h, h->AGC5_byte_1, FJ2207_CHIP_ADDRESS, AGC5_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case AGC5_HPF:
			if (h->AGC5_HPF){
				h->AGC5_HPF <<= 4;
				h->AGC5_HPF &= 0x10;
				h->AGC5_byte_1 |= h->AGC5_HPF;
			} else {
				h->AGC5_HPF = 0x10;
				h->AGC5_byte_1 &= ~(h->AGC5_HPF);
				h->AGC5_HPF = 0x00;		
			}
			fj2207_write_byte_register(h, h->AGC5_byte_1, FJ2207_CHIP_ADDRESS, AGC5_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		case VHFIII:
			if (h->VHFIII){
				h->PSM_byte_1 = 0x20; //the rest bits should be set to the zero
			}
			else{
				h->PSM_byte_1 = 0;
			}
			fj2207_write_byte_register(h, h->PSM_byte_1, FJ2207_CHIP_ADDRESS, PSM_byte_1);
			i2c_send_stop_sequence(&(h->i2c_handle));
		return Fj2207Success;
		
		default:
		return Fj2207FieldReadOnly;
	}
}

Fj2207ReturnType fj2207_write_field_from_handle(Fj2207Handle *h, Fj2207Ident field_id){
	uint32 temp;
	switch(field_id){
		case TM_ON:
			h->Thermo_byte_1 = h->TM_D;
		return Fj2207Success;

		case SM_LNA:
			if (h->SM_LNA){
				h->SM_LNA <<= 1;
				h->Power_state_byte_2 |= h->SM_LNA;
				h->SM_LNA = 0x01;		
			} else {
				h->SM_LNA = 0x01;
				h->SM_LNA <<= 1;
				h->Power_state_byte_2 &= ~(h->SM_LNA);
				h->SM_LNA = 0x00;
			}
		return Fj2207Success;
		
		case SM_PLL:
			if (h->SM_LNA){
				h->SM_PLL <<= 2;
				h->Power_state_byte_2 |= h->SM_PLL;
				h->SM_PLL = 0x01;	
			} else {
				h->SM_PLL = 0x01;
				h->SM_PLL <<= 2;
				h->Power_state_byte_2 &= ~(h->SM_PLL);
				h->SM_PLL = 0x00;
			}
		return Fj2207Success;
		
		case SM:
			if (h->SM){
				h->SM <<= 3;
				h->Power_state_byte_2 |= h->SM;
				h->SM = 0x01;
			} else {
				h->SM = 0x01;
				h->SM <<= 3;
				h->Power_state_byte_2 &= ~(h->SM);
				h->SM = 0x00;
			}
		return Fj2207Success;
		
		case IF_Freq:
			h->IF_Frequency_byte = h->IF_Freq;
		return Fj2207Success;

		case RF_Freq:
			temp = h->RF_Freq;
			h->RF_Frequency_byte_2 = h->RF_Freq;
			h->RF_Freq >>= BYTE_SIZE;
			h->RF_Frequency_byte_3 = h->RF_Freq;
			h->RF_Freq >>= BYTE_SIZE;
			h->RF_Frequency_byte_1 = h->RF_Freq;
			h->RF_Freq = temp;
		return Fj2207Success;
			
		case POWER_Meas:
				if (h->POWER_Meas){
				h->POWER_Meas <<= 7;
				h->MSM_Byte_1 |= h->RF_CAL;	
				h->POWER_Meas = 0x01;	
			} else {
				h->POWER_Meas = 0x01;
				h->POWER_Meas <<= 7;
				h->MSM_Byte_1 &= ~(h->RF_CAL);
				h->POWER_Meas = 0x00;
			}
		return Fj2207Success;
		
		case RF_CAL_AV:
			if (h->RF_CAL_AV){
				h->RF_CAL_AV <<= 6;
				h->MSM_Byte_1 |= h->RF_CAL;
				h->RF_CAL_AV = 0x01;		
			} else {
				h->RF_CAL_AV = 0x01;
				h->RF_CAL_AV <<= 6;
				h->MSM_Byte_1 &= ~(h->RF_CAL);
				h->RF_CAL_AV = 0x00;
			}
		return Fj2207Success;
		
		case RF_CAL:
			if (h->RF_CAL){
				h->RF_CAL <<= 5;
				h->MSM_Byte_1 |= h->RF_CAL;
				h->RF_CAL = 0x01;		
			} else {
				h->RF_CAL = 0x01;
				h->RF_CAL <<= 5;
				h->MSM_Byte_1 &= ~(h->RF_CAL);
				h->RF_CAL = 0x00;
			}
		return Fj2207Success;
		
		case IR_CAL:
			temp = h->IR_CAL;
			h->IR_CAL &= 0x02;
			if (h->IR_CAL){
				h->IR_CAL <<= 3;
				h->MSM_Byte_1 |= h->IR_CAL;	
			} else {
				h->IR_CAL = 0x02;
				h->IR_CAL <<= 3;
				h->MSM_Byte_1 &= ~(h->IR_CAL);
			}
			h->IR_CAL = temp;
			h->IR_CAL &= 0x01;
			if (h->IR_CAL){
				h->IR_CAL <<= 3;
				h->MSM_Byte_1 |= h->IR_CAL;		
			} else {
				h->IR_CAL = 0x01;
				h->IR_CAL <<= 3;
				h->MSM_Byte_1 &= ~(h->IR_CAL);
			}
			h->IR_CAL = temp;
		return Fj2207Success;
		
		case RC_CAL:
			if (h->RC_CAL){
				h->RC_CAL <<= 1;
				h->MSM_Byte_1 |= h->RC_CAL;
				h->RC_CAL = 0x01;		
			} else {
				h->RC_CAL = 0x01;
				h->RC_CAL <<= 1;
				h->MSM_Byte_1 &= ~(h->RC_CAL);
				h->RC_CAL = 0x00;
			}
		return Fj2207Success;
		
		case Calc_PLL:
			if (h->Calc_PLL){
				h->MSM_Byte_1 |= h->Calc_PLL;		
			} else {
				h->Calc_PLL = 0x01;
				h->MSM_Byte_1 &= ~(h->Calc_PLL);
				h->Calc_PLL = 0x00;
			}
		return Fj2207Success;
		
		case MSM_Launch:
			if (h->MSM_Launch){
				h->MSM_Byte_2 |= h->MSM_Launch;		
			} else {
				h->MSM_Launch = 0x01;
				h->MSM_Byte_2 &= ~(h->MSM_Launch);
				h->MSM_Launch = 0x00;
			}
		return Fj2207Success;
		
		case Pulse_Shaper_disable:
			if (h->Pulse_Shaper_disable){
				h->Pulse_Shaper_disable |= h->AGCK_byte_1;		
			} else {
				h->Pulse_Shaper_disable = 0x01;
				h->Pulse_Shaper_disable <<= 4;
				h->AGCK_byte_1 &= ~(h->Pulse_Shaper_disable);
				h->Pulse_Shaper_disable = 0x00;
			}
		return Fj2207Success;
			
		case AGCK_mode:
			temp = h->AGCK_mode;
			h->AGCK_mode &= 0x02;
			if (h->AGCK_mode){
				h->AGCK_byte_1 |= h->AGCK_mode;	
			} else {
				h->AGCK_mode = 0x02;
				h->AGCK_byte_1 &= ~(h->AGCK_mode);
			}
			h->AGCK_mode = temp;
			h->AGCK_mode &= 0x01;
			if (h->AGCK_mode){
				h->AGCK_byte_1 |= h->AGCK_mode;		
			} else {
				h->AGCK_mode = 0x01;
				h->AGCK_byte_1 &= ~(h->AGCK_mode);
			}
			h->AGCK_mode = temp;
		return Fj2207Success;
		
		case IF_HP_Fc:
			temp = h->IF_HP_Fc;
			h->IF_HP_Fc &= 0x02;
			if (h->IF_HP_Fc){
				h->IF_HP_Fc <<= 6;
				h->IF_byte_1 |= h->IF_HP_Fc;	
			} else {
				h->IF_HP_Fc = 0x02;
				h->IF_HP_Fc <<= 6;
				h->IF_byte_1 &= ~(h->IF_HP_Fc);
			}
			h->IF_HP_Fc = temp;
			h->IF_HP_Fc &= 0x01;
			if (h->IF_HP_Fc){
				h->IF_HP_Fc <<= 6;
				h->IF_byte_1 |= h->IF_HP_Fc;	
			} else {
				h->IF_HP_Fc = 0x01;
				h->IF_HP_Fc <<= 6;
				h->IF_byte_1 &= ~(h->IF_HP_Fc);
			}
			h->IF_HP_Fc = temp;
		return Fj2207Success;
		
		case IF_Notch:
			if (h->IF_Notch){
				h->IF_Notch <<= 5;
				h->IF_byte_1 |= h->IF_Notch;
				h->IF_Notch = 0x01;
			} else {
				h->IF_Notch = 0x01;
				h->IF_Notch <<= 5;
				h->IF_byte_1 &= ~(h->IF_Notch);
				h->IF_Notch = 0x00;
			}
		return Fj2207Success;
		
		case LP_FC_Offset:
			temp = h->LP_FC_Offset;
			h->LP_FC_Offset &= 0x02;
			if (h->LP_FC_Offset){
				h->LP_FC_Offset <<= 3;
				h->IF_byte_1 |= h->LP_FC_Offset;	
			} else {
				h->LP_FC_Offset = 0x02;
				h->LP_FC_Offset <<= 3;
				h->IF_byte_1 &= ~(h->LP_FC_Offset);
			}
			h->LP_FC_Offset = temp;
			h->LP_FC_Offset &= 0x01;
			if (h->LP_FC_Offset){
				h->LP_FC_Offset <<= 3;
				h->IF_byte_1 |= h->LP_FC_Offset;	
			} else {
				h->LP_FC_Offset = 0x01;
				h->LP_FC_Offset <<= 3;
				h->IF_byte_1 &= ~(h->LP_FC_Offset);
			}
			h->IF_HP_Fc = temp;
		return Fj2207Success;
		
		case LP_Fc:
			temp = h->LP_Fc;
			h->LP_Fc &= 0x04;
			if (h->LP_Fc){
				h->IF_byte_1 |= h->LP_Fc;	
			} else {
				h->LP_Fc = 0x04;
				h->IF_byte_1 &= ~(h->LP_Fc);
			}
			h->LP_Fc = temp;
			h->LP_Fc &= 0x02;
			if (h->LP_Fc){
				h->IF_byte_1 |= h->LP_Fc;	
			} else {
				h->LP_Fc = 0x02;
				h->IF_byte_1 &= ~(h->LP_Fc);
			}
			h->LP_Fc = temp;
			h->LP_Fc &= 0x01;
			if (h->LP_Fc){
				h->IF_byte_1 |= h->LP_Fc;	
			} else {
				h->LP_Fc = 0x01;
				h->IF_byte_1 &= ~(h->LP_Fc);
			}
			h->LP_Fc = temp;
		return Fj2207Success;
		
		case IF_Level:
			h->IF_AGC_byte = h->IF_Level;
		return Fj2207Success;
		
		case XTout:
			temp = h->XTout;
			h->XTout &= 0x01; 
			if (h->XTout){
				h->XTout |= h->Reference_byte;	
			} else {
				h->XTout = 0x01;
				h->Reference_byte &= ~(h->XTout);
			}
			h->XTout = temp;
			h->XTout &= 0x02;
			if (h->XTout){
				h->XTout |= h->Reference_byte;	
			} else {
				h->XTout = 0x02;
				h->Reference_byte &= ~(h->XTout);
			}
			h->XTout = temp;
		return Fj2207Success;
		
		case Digital_Clock:
			if (h->Digital_Clock){
				h->Digital_Clock <<= 6;
				h->Digital_Clock |= h->Reference_byte;
				h->Digital_Clock = 0x01;
			} else {
				h->Digital_Clock = 0x40;
				h->Reference_byte &= ~(h->Digital_Clock);
				h->Digital_Clock = 0x00;
			}
		return Fj2207Success;
			
		case HI_Pass:
			if (h->HI_Pass){
				h->HI_Pass <<= 1;
				h->IR_MIXER_byte_2 |= h->HI_Pass;
				h->HI_Pass = 0x01;
			} else {
				h->HI_Pass = 0x02;
				h->IR_MIXER_byte_2 &= ~(h->HI_Pass);
				h->HI_Pass = 0x00;
			}
		return Fj2207Success;
		
		case DC_NOTCH:
			if (h->DC_NOTCH){
				h->IR_MIXER_byte_2 |= h->DC_NOTCH;
				h->DC_NOTCH = 0x01;
			} else {
				h->DC_NOTCH = 0x01;
				h->IR_MIXER_byte_2 &= ~(h->DC_NOTCH);
				h->DC_NOTCH = 0x00;
			}
		return Fj2207Success;
		
		case LT_Enable:
			if (h->LT_Enable){
				h->LT_Enable <<= 7;
				h->AGC1_byte_1 |= h->LT_Enable;
				h->LT_Enable = 0x01;
			} else {
				h->LT_Enable = 0x80;
				h->AGC1_byte_1 &= ~(h->LT_Enable);
				h->LT_Enable = 0x00;
			}
		return Fj2207Success;
		
		case AGC1_6_15dB:
			if (h->AGC1_6_15dB){
				h->AGC1_6_15dB <<= 6;
				h->AGC1_byte_1 |= h->AGC1_6_15dB;
				h->AGC1_6_15dB = 0x01;
			} else {
				h->AGC1_6_15dB = 0x40;
				h->AGC1_byte_1 &= ~(h->AGC1_6_15dB);
				h->AGC1_6_15dB = 0x00;
			}
		return Fj2207Success;		
		
		case AGC1_TOP:
			temp = h->AGC1_TOP;
			h->AGC1_TOP &= 0x08;
			if (h->AGC1_6_15dB){
				h->AGC1_byte_1 |= h->AGC1_TOP;
				h->AGC1_TOP = temp;
			} else {
				h->AGC1_TOP = 0x08;
				h->AGC1_byte_1 &= ~(h->AGC1_TOP);
				h->AGC1_TOP = temp;
			}
			h->AGC1_TOP &= 0x04;
			if (h->AGC1_TOP){
				h->AGC1_byte_1 |= h->AGC1_TOP;
				h->AGC1_TOP = temp;
			} else {
				h->AGC1_TOP = 0x04;
				h->AGC1_byte_1 &= ~(h->AGC1_TOP);
				h->AGC1_TOP = temp;
			}
			h->AGC1_TOP &= 0x02;
			if (h->AGC1_TOP){
				h->AGC1_byte_1 |= h->AGC1_TOP;
				h->AGC1_TOP = temp;
			} else {
				h->AGC1_TOP = 0x02;
				h->AGC1_byte_1 &= ~(h->AGC1_TOP);
				h->AGC1_TOP = temp;
			}
			h->AGC1_TOP &= 0x01;
			if (h->AGC1_TOP){
				h->AGC1_byte_1 |= h->AGC1_TOP;
				h->AGC1_TOP = temp;
			} else {
				h->AGC1_TOP = 0x01;
				h->AGC1_byte_1 &= ~(h->AGC1_TOP);
				h->AGC1_TOP = temp;
			}
		return Fj2207Success;
		
		case PD_RFAGC_Adapt:
			h->PD_RFAGC_Adapt <<= 7;
			if (h->PD_RFAGC_Adapt){
				h->RF_AGC_byte_1 |= h->PD_RFAGC_Adapt;
				h->PD_RFAGC_Adapt = 0x01;
			}else{
				h->PD_RFAGC_Adapt = 0x80;
				h->RF_AGC_byte_1 &= ~(h->PD_RFAGC_Adapt);
				h->PD_RFAGC_Adapt = 0x00;
			}
		return Fj2207Success;
			
		case RFAGC_Adapt_TOP:
			temp = h->RFAGC_Adapt_TOP;
			h->RFAGC_Adapt_TOP &= 0x02;
			if (h->RFAGC_Adapt_TOP){
				h->RFAGC_Adapt_TOP <<= 5;
				h->RF_AGC_byte_1 |= h->RFAGC_Adapt_TOP;
				h->PD_RFAGC_Adapt = temp;
			}else{
				h->RFAGC_Adapt_TOP = 0x02;
				h->RFAGC_Adapt_TOP <<= 5;
				h->RF_AGC_byte_1 &= ~(h->RFAGC_Adapt_TOP);
				h->PD_RFAGC_Adapt = temp;
			}
			h->RFAGC_Adapt_TOP &= 0x01;
			if (h->RFAGC_Adapt_TOP){
				h->RFAGC_Adapt_TOP <<= 5;
				h->RF_AGC_byte_1 |= h->RFAGC_Adapt_TOP;
				h->PD_RFAGC_Adapt = temp;
			}else{
				h->RFAGC_Adapt_TOP = 0x01;
				h->RFAGC_Adapt_TOP <<= 5;
				h->RF_AGC_byte_1 &= ~(h->RFAGC_Adapt_TOP);
				h->PD_RFAGC_Adapt = temp;
			}
		return Fj2207Success;
		
		case RF_Atten_3dB:
			if (h->RF_Atten_3dB){
				h->RF_Atten_3dB <<= 3;
				h->RF_AGC_byte_1 |= h->RF_Atten_3dB;
				h->RF_Atten_3dB = 0x01;
			}else{
				h->RF_Atten_3dB = 0x01;
				h->RF_Atten_3dB <<= 3;
				h->RF_AGC_byte_1 &= ~(h->RF_Atten_3dB);
				h->RF_Atten_3dB = 0x00;
			}
		return Fj2207Success;
		
		case AGC3_Top:
			temp = h->AGC3_Top;
			h->AGC3_Top &= 0x04;
			if (h->AGC3_Top){
				h->RF_AGC_byte_1 |= h->AGC3_Top;
				h->AGC3_Top = temp;
			}else{
				h->AGC3_Top = 0x04;
				h->RF_AGC_byte_1 &= ~(h->AGC3_Top);
				h->AGC3_Top = temp;
			}
			h->AGC3_Top &= 0x02;
			if (h->AGC3_Top){
				h->RF_AGC_byte_1 |= h->AGC3_Top;
				h->AGC3_Top = temp;
			}else{
				h->AGC3_Top = 0x02;
				h->RF_AGC_byte_1 &= ~(h->AGC3_Top);
				h->AGC3_Top = temp;
			}
			h->AGC3_Top &= 0x01;
			if (h->AGC3_Top){
				h->RF_AGC_byte_1 |= h->AGC3_Top;
				h->AGC3_Top = temp;
			}else{
				h->AGC3_Top = 0x01;
				h->RF_AGC_byte_1 &= ~(h->AGC3_Top);
				h->AGC3_Top = temp;
			}
		return Fj2207Success;		
		
		case AGC4_Top:
			temp = h->AGC4_Top;
			if (h->AGC4_Top){
				h->AGC4_Top &= 0x04;
				h->IR_MIXER_byte_1 |= h->AGC4_Top;
				h->AGC4_Top = temp;
			} else {
				h->AGC4_Top = 0x04;
				h->IR_MIXER_byte_1 &= ~(h->AGC4_Top);
				h->AGC4_Top = temp;
			}
			h->AGC4_Top &= 0x02;
			if (h->AGC4_Top){
				h->IR_MIXER_byte_1 |= h->AGC4_Top;
				h->AGC4_Top = temp;
			} else {
				h->AGC4_Top = 0x02;
				h->IR_MIXER_byte_1 &= ~(h->AGC4_Top);
				h->AGC4_Top = temp;
			}
			h->AGC4_Top &= 0x01;
			if (h->AGC4_Top){
				h->IR_MIXER_byte_1 |= h->AGC4_Top;
				h->AGC4_Top = temp;
			} else {
				h->AGC4_Top = 0x01;
				h->IR_MIXER_byte_1 &= ~(h->AGC4_Top);
				h->AGC4_Top = temp;
			}
		return Fj2207Success;
		
		case AGC5_Top:
			temp = h->AGC5_Top;
			if (h->AGC5_Top){
				h->AGC5_Top &= 0x04;
				h->AGC5_byte_1 |= h->AGC5_Top;
				h->AGC5_Top = temp;
			} else {
				h->AGC5_Top = 0x04;
				h->AGC5_byte_1 &= ~(h->AGC5_Top);
				h->AGC5_Top = temp;
			}
			h->AGC1_TOP &= 0x02;
			if (h->AGC5_Top){
				h->AGC5_byte_1 |= h->AGC5_Top;
				h->AGC5_Top = temp;
			} else {
				h->AGC5_Top = 0x02;
				h->AGC5_byte_1 &= ~(h->AGC5_Top);
				h->AGC5_Top = temp;
			}
			h->AGC1_TOP &= 0x01;
			if (h->AGC5_Top){
				h->AGC5_byte_1 |= h->AGC5_Top;
				h->AGC5_Top = temp;
			} else {
				h->AGC5_Top = 0x01;
				h->AGC5_byte_1 &= ~(h->AGC5_Top);
				h->AGC5_Top = temp;
			}
		return Fj2207Success;
		
		case AGC5_HPF:
			if (h->AGC5_HPF){
				h->AGC5_HPF <<= 4;
				h->AGC5_HPF &= 0x10;
				h->AGC5_byte_1 |= h->AGC5_HPF;
			} else {
				h->AGC5_HPF = 0x10;
				h->AGC5_byte_1 &= ~(h->AGC5_HPF);
				h->AGC5_HPF = 0x00;		
			}
		return Fj2207Success;
		
		case VHFIII:
			if (h->VHFIII){
				h->PSM_byte_1 = 0x20; //the rest bits should be set to the zero
			}
			else{
				h->PSM_byte_1 = 0;
			}
		return Fj2207Success;
		
		default:
		return Fj2207FieldReadOnly;
	}
}

Fj2207ReturnType fj2207_write_field_to_handle(Fj2207Handle *h, Fj2207Ident field_id){
	switch(field_id){
		case Ident:
			h->Ident = h->ID_byte_1;
			h->Ident &=	0x7F;
			h->Ident <<= BYTE_SIZE;
			h->Ident |= h->ID_byte_2;
		return Fj2207Success;
		
		case Major_rev:
			h->Major_rev = h->ID_byte_3;
			h->Major_rev >>= FOUR_BITS_SIZE;
		return Fj2207Success;
		
		case Minor_rev:
			h->Minor_rev = h->ID_byte_3;
			h->Minor_rev &=	0x0F;
		return Fj2207Success;
		
		case TM_D:
			h->TM_D = h->Thermo_byte_1;
			h->TM_D &= 0x7F;
		return Fj2207Success;
		
		case TM_ON:
			h->TM_ON = h->Thermo_byte_2;
			h->TM_ON &=	0x01;
		return Fj2207Success;
		
		case POR:
			h->POR = h->Power_state_byte_1;
			h->POR &=	0x02;
			h->POR >>= 1;
		return Fj2207Success;
		
		case LO_Lock:
			h->LO_Lock = h->Power_state_byte_1;
			h->LO_Lock &=	0x01;
		return Fj2207Success;
		
		case SM_LNA:
			h->SM_LNA = h->Power_state_byte_2;
			h->SM_LNA &=	0x02;
			h->SM_LNA >>= 1;
		return Fj2207Success;
		
		case SM_PLL:
			h->SM_PLL = h->Power_state_byte_2;
			h->SM_PLL &= 0x04;
			h->SM_PLL >>= 2;
		return Fj2207Success;

		case SM:
			h->SM = h->Power_state_byte_2;
			h->SM &= 0x08;
			h->SM >>= 3;
		return Fj2207Success;
		
		case Power_Level:
			h->Power_Level = h->Input_Power_Level_byte;
			h->Power_Level &= 0x7F;
		return Fj2207Success;
		
		case IF_Freq:
			h->IF_Freq = h->IF_Frequency_byte;
		return Fj2207Success;
		
		case RF_Freq:
			h->RF_Freq = 0;
			h->RF_Freq = h->RF_Frequency_byte_1;
			h->RF_Freq &= 0x0F;
			h->RF_Freq <<= BYTE_SIZE;
			h->RF_Freq |= h->RF_Frequency_byte_3;
			h->RF_Freq <<= BYTE_SIZE;
			i2c_send_stop_sequence(&(h->i2c_handle));
			h->RF_Freq |= h->RF_Frequency_byte_2;
		return Fj2207Success;
			
		case POWER_Meas:
			h->MSM_Byte_1 &= 0xFB;
			h->POWER_Meas = h->MSM_Byte_1;
			h->POWER_Meas &= 0x80;
			h->POWER_Meas >>= 7;
		return Fj2207Success;
		
		case RF_CAL_AV:
			h->MSM_Byte_1 &= 0xFB;
			h->RF_CAL_AV = h->MSM_Byte_1;
			h->RF_CAL_AV &= 0x40;
			h->RF_CAL_AV >>= 6;
		return Fj2207Success;
		
		case RF_CAL:
			h->MSM_Byte_1 &= 0xFB;
			h->RF_CAL = h->MSM_Byte_1;
			h->RF_CAL &= 0x20;
			h->RF_CAL >>= 5;
		return Fj2207Success;
		
		case IR_CAL:
			h->MSM_Byte_1 &= 0xFB;
			h->IR_CAL = h->MSM_Byte_1;
			h->IR_CAL &= 0x18;
			h->IR_CAL >>= 3;
		return Fj2207Success;
		
		case RC_CAL:
			h->MSM_Byte_1 &= 0xFB;
			h->RC_CAL = h->MSM_Byte_1;
			h->RC_CAL &= 0x02;
			h->RC_CAL >>= 1;
		return Fj2207Success;
		
		case Calc_PLL:
			h->MSM_Byte_1 &= 0xFB;
			h->Calc_PLL = h->MSM_Byte_1;
			h->Calc_PLL &= 0x01;
		return Fj2207Success;
		
		case MSM_Launch:
			h->MSM_Launch = h->MSM_Byte_2;
			h->MSM_Launch &= 0x01;
		return Fj2207Success;
		
		case Pulse_Shaper_disable:
			h->Pulse_Shaper_disable = h->AGCK_byte_1;
			h->Pulse_Shaper_disable &= 0x10;
			h->Pulse_Shaper_disable >>= 4;
		return Fj2207Success;
		
		case AGCK_mode:
			h->AGCK_mode = h->AGCK_byte_1;
			h->AGCK_mode &= 0x03;
		return Fj2207Success;
		
		case IF_HP_Fc:
			h->IF_HP_Fc = h->IF_byte_1;
			h->IF_HP_Fc &= 0xC0;
			h->IF_HP_Fc >>= 6;
		return Fj2207Success;
		
		case IF_Notch:
			h->IF_Notch = h->IF_byte_1;
			h->IF_Notch &= 0x20;
			h->IF_Notch >>= 5;
		return Fj2207Success;
		
		case LP_FC_Offset:
			h->LP_FC_Offset = h->IF_byte_1;
			h->LP_FC_Offset &= 0x18;
			h->LP_FC_Offset >>= 3;
		return Fj2207Success;
		
		case LP_Fc:
			h->LP_Fc = h->IF_byte_1;
			h->LP_Fc &= 0x07;
		return Fj2207Success;
		
		case IF_Level:
			h->IF_Level = h->IF_AGC_byte;
			h->IF_Level &= 0x07;
		return Fj2207Success;
		
		case XTout:
			h->XTout = h->Reference_byte;
			h->XTout &= 0x03;
		return Fj2207Success;
		
		case Digital_Clock:
			h->Digital_Clock = h->Reference_byte;
			h->Digital_Clock &= 0x40;
			h->Digital_Clock >>= 6;
		return Fj2207Success;
		
		case HI_Pass:
			h->HI_Pass = h->IR_MIXER_byte_2;
			h->HI_Pass &= 0x02;
			h->HI_Pass >>= 1;
		return Fj2207Success;
		
		case DC_NOTCH:
			h->DC_NOTCH = h->IR_MIXER_byte_2;
			h->DC_NOTCH &= 0x01;
		return Fj2207Success;		

		case LT_Enable:
			h->LT_Enable = h->AGC1_byte_1;
			h->LT_Enable &= 0x80;
			h->LT_Enable >>= 7;
		return Fj2207Success;
		
		case AGC1_6_15dB:
			h->AGC1_6_15dB = h->AGC1_byte_1;
			h->AGC1_6_15dB &= 0x40;
			h->AGC1_6_15dB >>= 6;
		return Fj2207Success;		
		
		case AGC1_TOP:
			h->AGC1_TOP = h->AGC1_byte_1;
			h->AGC1_TOP &= 0x0F;
		return Fj2207Success;		
		
		case AGC1_byte_2:
			h->AGC1_byte_2 &= 0x1F; 
		return Fj2207Success;
		
		case Power_byte_2:
			h->Power_byte_2 &= 0x2F; 
		return Fj2207Success;
			
		case PD_RFAGC_Adapt:
			h->PD_RFAGC_Adapt = h->RF_AGC_byte_1;
			h->PD_RFAGC_Adapt >>= 7;
		return Fj2207Success;
			
		case RFAGC_Adapt_TOP:
			h->RFAGC_Adapt_TOP = RF_AGC_byte_1;
			h->RFAGC_Adapt_TOP >>= 5;
			h->RFAGC_Adapt_TOP &= 0x03;
		return Fj2207Success;
		
		case RF_Atten_3dB:
			h->RF_Atten_3dB = h->RF_AGC_byte_1;
			h->RF_Atten_3dB >>= 3;
			h->RF_Atten_3dB &= 0x01;
		return Fj2207Success;
		
		case AGC3_Top:
			h->AGC3_Top = h->RF_AGC_byte_1;
			h->AGC3_Top &= 0x07;
		return Fj2207Success;
		
		case AGC4_Top:
			h->AGC4_Top = h->IR_MIXER_byte_1;
			h->AGC4_Top &= 0x0F;
		return Fj2207Success;
		
		case AGC5_Top:
			h->AGC5_Top = h->AGC5_byte_1;
			h->AGC5_Top &= 0x0F;
		return Fj2207Success;
			
		case AGC5_HPF:
			h->AGC5_HPF = h->AGC5_byte_1;
			h->AGC5_HPF &= 0x80;
			h->AGC5_HPF >>= 3;
		return Fj2207Success;
		
		case VHFIII:
			h->VHFIII = h->PSM_byte_1;
			h->VHFIII &= 0x20;
			h->VHFIII >>= 5;
		return Fj2207Success;
		
		case RF_FILTER_GAIN:
			h->RF_FILTER_GAIN = h->RF_AGC_Gain_byte_1;
			h->RF_FILTER_GAIN &= 0x30;
			h->RF_FILTER_GAIN >>= 4;
		return Fj2207Success;
		
		case LNA_GAIN:
			h->LNA_GAIN = h->RF_AGC_Gain_byte_1;
			h->LNA_GAIN &= 0x0F;
		return Fj2207Success;
		
		case TOP_Agc3_read:
			h->TOP_Agc3_read = h->RF_AGC_Gain_byte_2;
			h->TOP_Agc3_read &= 0x07;
		return Fj2207Success;
		
		case LPF_GAIN:
			h->LPF_GAIN = h->IF_AGC_Gain_byte;
			h->LPF_GAIN &= 0x18;
			h->LPF_GAIN >>= 3;
		return Fj2207Success;
		
		case IR_MIXER:
			h->IR_MIXER = h->IF_AGC_Gain_byte;
			h->IR_MIXER &= 0x07;
		return Fj2207Success;
		
		default:
		return Fj2207FieldIsNoDefined;				
	}
}

Fj2207ReturnType fj2207_update_handle(Fj2207Handle *h, Fj2207Ident field_id){
	I2cResponseType resp;
	switch(field_id){	
		case Thermo_byte_2:	
			resp = fj2207_get_byte_register(h, &(h->Thermo_byte_2), FJ2207_CHIP_ADDRESS, Thermo_byte_2);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, TM_ON);
			#endif		
		return Fj2207Success;	
				
		case Power_state_byte_2:
			resp = fj2207_get_byte_register(h, &(h->Power_state_byte_2), FJ2207_CHIP_ADDRESS, Power_state_byte_2);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, SM);
				fj2207_write_field_to_handle(h, SM_PLL);
				fj2207_write_field_to_handle(h, SM_LNA);
			#endif
		return Fj2207Success;	
		
		case IF_Frequency_byte:
			resp = fj2207_get_byte_register(h, &(h->IF_Frequency_byte), FJ2207_CHIP_ADDRESS, IF_Frequency_byte);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, IF_Freq);
			#endif
		return Fj2207Success;
		
		case RF_Frequency_byte_1:
			resp = fj2207_get_byte_register(h, &(h->RF_Frequency_byte_1), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_1);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, RF_Freq);
			#endif
		return Fj2207Success;	
			
		case RF_Frequency_byte_2:
			resp = fj2207_get_byte_register(h, &(h->RF_Frequency_byte_2), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_2);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, RF_Freq);
			#endif
		return Fj2207Success;	
			
		case RF_Frequency_byte_3:
			resp = fj2207_get_byte_register(h, &(h->RF_Frequency_byte_3), FJ2207_CHIP_ADDRESS, RF_Frequency_byte_3);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, RF_Freq);
			#endif
		return Fj2207Success;	
			
		case MSM_Byte_1:
			resp = fj2207_get_byte_register(h, &(h->MSM_Byte_1), FJ2207_CHIP_ADDRESS, MSM_Byte_1);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, POWER_Meas);
				fj2207_write_field_to_handle(h, RF_CAL_AV);
				fj2207_write_field_to_handle(h, RF_CAL);
				fj2207_write_field_to_handle(h, IR_CAL);
				fj2207_write_field_to_handle(h, RC_CAL);
				fj2207_write_field_to_handle(h, Calc_PLL);
			#endif
		return Fj2207Success;	
				
		case MSM_Byte_2:
			resp = fj2207_get_byte_register(h, &(h->MSM_Byte_2), FJ2207_CHIP_ADDRESS, MSM_Byte_2);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, MSM_Launch);
			#endif
		return Fj2207Success;	
				
		case AGCK_byte_1:
			resp = fj2207_get_byte_register(h, &(h->AGCK_byte_1), FJ2207_CHIP_ADDRESS, AGCK_byte_1);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, Pulse_Shaper_disable);
				fj2207_write_field_to_handle(h, AGCK_mode);
			#endif
		return Fj2207Success;	
				
		case IF_byte_1:
			resp = fj2207_get_byte_register(h, &(h->IF_byte_1), FJ2207_CHIP_ADDRESS, IF_byte_1);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, IF_HP_Fc);
				fj2207_write_field_to_handle(h, IF_Notch);
				fj2207_write_field_to_handle(h, LP_FC_Offset);
				fj2207_write_field_to_handle(h, LP_Fc);
			#endif
		return Fj2207Success;	
			
		case IF_AGC_byte:
			resp = fj2207_get_byte_register(h, &(h->IF_AGC_byte), FJ2207_CHIP_ADDRESS, IF_AGC_byte);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, IF_Level);
			#endif
		return Fj2207Success;	
				
		case Reference_byte:
			resp = fj2207_get_byte_register(h, &(h->Reference_byte), FJ2207_CHIP_ADDRESS, Reference_byte);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, Digital_Clock);
				fj2207_write_field_to_handle(h, XTout);
			#endif
		return Fj2207Success;	
				
		case IR_MIXER_byte_2:
			resp = fj2207_get_byte_register(h, &(h->IR_MIXER_byte_2), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, HI_Pass);
				fj2207_write_field_to_handle(h, DC_NOTCH);
			#endif
		return Fj2207Success;	
				
		case AGC1_byte_1:
			resp = fj2207_get_byte_register(h, &(h->AGC1_byte_1), FJ2207_CHIP_ADDRESS, AGC1_byte_1);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, LT_Enable);
				fj2207_write_field_to_handle(h, AGC1_6_15dB);
				fj2207_write_field_to_handle(h, AGC1_TOP);
			#endif
		return Fj2207Success;	
					
		case RF_AGC_byte_1:
			resp = fj2207_get_byte_register(h, &(h->RF_AGC_byte_1), FJ2207_CHIP_ADDRESS, RF_AGC_byte_1);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, PD_RFAGC_Adapt);
				fj2207_write_field_to_handle(h, RFAGC_Adapt_TOP);
				fj2207_write_field_to_handle(h, RF_Atten_3dB);
				fj2207_write_field_to_handle(h, AGC3_Top);
			#endif
		return Fj2207Success;
				
		case IR_MIXER_byte_1:
			resp = fj2207_get_byte_register(h, &(h->IR_MIXER_byte_1), FJ2207_CHIP_ADDRESS, IR_MIXER_byte_1);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, AGC4_Top);
			#endif
		return Fj2207Success;	
			
		case AGC5_byte_1:
			resp = fj2207_get_byte_register(h, &(h->AGC5_byte_1), FJ2207_CHIP_ADDRESS, AGC5_byte_1);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, AGC5_Top);
			#endif
		return Fj2207Success;	
			
		case PSM_byte_1:
			resp = fj2207_get_byte_register(h, &(h->PSM_byte_1), FJ2207_CHIP_ADDRESS, PSM_byte_1);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
			#ifdef USE_ELOBARATE
				fj2207_write_field_to_handle(h, VHFIII);
			#endif
		return Fj2207Success;	
		
		case Power_byte_2:
			resp = fj2207_get_byte_register(h, &(h->Power_byte_2), FJ2207_CHIP_ADDRESS, Power_byte_2);
				if (resp){
					return (Fj2207ReturnType) resp;
				}
		return Fj2207Success;
		
		case AGC1_byte_2:
			resp = fj2207_get_byte_register(h, &(h->AGC1_byte_2), FJ2207_CHIP_ADDRESS, AGC1_byte_2);
			if (resp){
				return (Fj2207ReturnType) resp;
			}
		return Fj2207Success;
		
		default:
		return Fj2207FieldReadOnly;
	}
}

void fj2207_set(Fj2207Handle *h, uint32 rf_frequency, uint32 if_frequency){
#ifdef USE_ELOBARATE
	//transition 0
	h->SM = 0;
	h->SM_PLL = 0;
	h->SM_LNA = 0;
	fj2207_write_field(h, SM);
	fj2207_write_field(h, SM_LNA);
	fj2207_write_field(h, SM_PLL);
	
	h->POWER_Meas = 0;
	h->RF_CAL_AV = 0;
	h->RF_CAL = 1;
	h->IR_CAL = 3;
	h->RC_CAL = 1;
	h->Calc_PLL = 1;
	fj2207_write_field(h, POWER_Meas);
	fj2207_write_field(h, RF_CAL_AV);
	fj2207_write_field(h, RF_CAL);
	fj2207_write_field(h, IR_CAL);
	fj2207_write_field(h, RC_CAL);
	fj2207_write_field(h, Calc_PLL);
	
	h->MSM_Launch = 1;
	fj2207_write_field(h, MSM_Launch);
	
	h->Digital_Clock = 1;
	h->XTout = 1;
	fj2207_write_field(h, Digital_Clock);
	fj2207_write_field(h, XTout);
	
	h->Power_byte_2 = 0x0E;
	fj2207_write_field(h, Power_byte_2);
	
	h->SM = 0;
	h->SM_PLL = 1;
	h->SM_LNA = 0;
	fj2207_write_field(h, SM);
	fj2207_write_field(h, SM_LNA);
	fj2207_write_field(h, SM_PLL);
	
	//transition 1
	h->IF_Freq = if_frequency/50000;
	fj2207_write_field(h, IF_Freq);
	
	h->IF_Level = 7;
	fj2207_write_field(h, IF_Level);
	
	h->IF_HP_Fc = 0;
	h->IF_Notch = 0;
	h->LP_FC_Offset = 0;
	h->LP_Fc = 3;
	fj2207_write_field(h, IF_HP_Fc);
	fj2207_write_field(h, IF_Notch);
	fj2207_write_field(h, LP_FC_Offset);
	fj2207_write_field(h, LP_Fc);
	
	h->HI_Pass = 0;
	h->DC_NOTCH = 0;
	fj2207_write_field(h, HI_Pass);
	fj2207_write_field(h, DC_NOTCH);
	// agc1 byte 1 - not set - default values
	// agc2 byte 1 - not set - default values
	
	h->Pulse_Shaper_disable = 0;
	h->AGCK_mode = 2;
	fj2207_write_field(h, Pulse_Shaper_disable);
	fj2207_write_field(h, AGCK_mode);
	
	h->VHFIII = 0;
	fj2207_write_field(h, VHFIII);
	
	//transition 2
	h->RF_Freq = rf_frequency/1000;
	fj2207_write_field(h, RF_Freq);
	
	h->SM = 0;
	h->SM_PLL = 0;
	h->SM_LNA = 0;
	fj2207_write_field(h, SM);
	fj2207_write_field(h, SM_LNA);
	fj2207_write_field(h, SM_PLL);
	
	h->Power_byte_2 = 0x0E;
	fj2207_write_field(h, Power_byte_2);
	
	h->POWER_Meas = 0;
	h->RF_CAL_AV = 1;
	h->RF_CAL = 0;
	h->IR_CAL = 0;
	h->RC_CAL = 0;
	h->Calc_PLL = 1;
	fj2207_write_field(h, POWER_Meas);
	fj2207_write_field(h, RF_CAL_AV);
	fj2207_write_field(h, RF_CAL);
	fj2207_write_field(h, IR_CAL);
	fj2207_write_field(h, RC_CAL);
	fj2207_write_field(h, Calc_PLL);
	
	h->MSM_Launch = 1;
	fj2207_write_field(h, MSM_Launch);
#else
		uint32 temp;
		//transition 0
		fj2207_write_byte_register(h, 0x00, FJ2207_CHIP_ADDRESS, Power_state_byte_2); //PLL and LNA on
		fj2207_write_byte_register(h, 0x3B, FJ2207_CHIP_ADDRESS, MSM_Byte_1);
		fj2207_write_byte_register(h, 0x01, FJ2207_CHIP_ADDRESS, MSM_Byte_2);
		fj2207_write_byte_register(h, 0x4F, FJ2207_CHIP_ADDRESS, Reference_byte);
		fj2207_write_byte_register(h, 0x0E, FJ2207_CHIP_ADDRESS, Power_byte_2); //default values 
		fj2207_write_byte_register(h, 0x04, FJ2207_CHIP_ADDRESS, Power_state_byte_2); //standby
		//transition 1
		fj2207_write_byte_register(h, (if_frequency/50000), FJ2207_CHIP_ADDRESS, IF_Frequency_byte);
		fj2207_write_byte_register(h, 0x02, FJ2207_CHIP_ADDRESS, IF_AGC_byte); //1 V p-p - datasheet table 20
		//high-pass cutoff freq - 0.4 Mhz - 0		
		//disable notch - 0 
		//no LPF cutoff offset - 0
		//LPF cutoff - 10 Mhz - 3 dec
		fj2207_write_byte_register(h, 0x03, FJ2207_CHIP_ADDRESS, IF_byte_1);
		//notch off, hi pass off
		fj2207_write_byte_register(h, 0x00, FJ2207_CHIP_ADDRESS, IR_MIXER_byte_2); //IR mixer byte 2
		// agc1 byte 1 - not set - default values
		// agc2 byte 1 - not set - default values
		fj2207_write_byte_register(h, 0x02, FJ2207_CHIP_ADDRESS, AGCK_byte_1); //digital tv
		// ir mixer byte 1 - not set - default values 
		// AGC5 byte 1 - not set - default values
		// here should be set PSM byte 1
		fj2207_write_byte_register(h, 0x20, FJ2207_CHIP_ADDRESS, PSM_byte_1);
		//trans2
		
		temp = rf_frequency/1000;
		rf_frequency = temp & 0xFF;
		fj2207_write_byte_register(h, rf_frequency, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_2);
		rf_frequency = temp & 0xFF00;
		rf_frequency >>= 8;
		fj2207_write_byte_register(h, rf_frequency, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_3);
		rf_frequency = temp & 0xF0000;
		rf_frequency >>= 16;
		fj2207_write_byte_register(h, rf_frequency, FJ2207_CHIP_ADDRESS, RF_Frequency_byte_1);
	
		fj2207_write_byte_register(h, 0x00, FJ2207_CHIP_ADDRESS, Power_state_byte_2);
		fj2207_write_byte_register(h, 0x00, FJ2207_CHIP_ADDRESS, Power_byte_2); //power byte
		fj2207_write_byte_register(h, 0x41, FJ2207_CHIP_ADDRESS, MSM_Byte_1); 
		fj2207_write_byte_register(h, 0x01, FJ2207_CHIP_ADDRESS, MSM_Byte_2);
#endif	
}



