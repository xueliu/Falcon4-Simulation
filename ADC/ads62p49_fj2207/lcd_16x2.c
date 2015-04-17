#include <lcd_16x2.h>
#include <hal.h>
#include <gpio_pin.h>
#include <assert.h>

// private function prototypes
void lcd_set_pos(LcdHandle *h, uint16 x, uint8 y);
void lcd_write_init(LcdHandle *h, uint8 cmd);
void delay_us(uint16 us);
void lcd_device_init(LcdHandle *h);
void lcd_define_kt_logo(LcdHandle *h);

void lcd_init(LcdHandle *h, GpioPin *rs, GpioPin *rw, GpioPin *enable, GpioPin *bit_0, GpioPin *bit_1, GpioPin *bit_2, GpioPin *bit_3, GpioPin *bit_4, GpioPin *bit_5, GpioPin *bit_6, GpioPin *bit_7, LcdMode mode){
	uint8	i;

	h->rs				= rs;
	h->rw				= rw;
	h->enable			= enable;
	h->bit_0			= bit_0;
	h->bit_1			= bit_1;
	h->bit_2			= bit_2;
	h->bit_3			= bit_3;
	h->bit_4			= bit_4;
	h->bit_5			= bit_5;
	h->bit_6			= bit_6;
	h->bit_7			= bit_7;
	h->mode				= mode;
	
	// initialize GPIOs
	gpio_pin_init(h->rs);
	gpio_pin_init(h->rw);
	gpio_pin_init(h->enable);
	if (mode == Lcd8BitMode){
		gpio_pin_init(h->bit_0);
		gpio_pin_init(h->bit_1);
		gpio_pin_init(h->bit_2);
		gpio_pin_init(h->bit_3);
	}
	gpio_pin_init(h->bit_4);
	gpio_pin_init(h->bit_5);
	gpio_pin_init(h->bit_6);
	gpio_pin_init(h->bit_7);
	
	gpio_pin_clear(h->rs);
	gpio_pin_clear(h->rw);
	gpio_pin_set(h->enable);
	if (mode == Lcd8BitMode){
		gpio_pin_set(h->bit_0);
		gpio_pin_set(h->bit_1);
		gpio_pin_set(h->bit_2);
		gpio_pin_set(h->bit_3);
	}
	gpio_pin_set(h->bit_4);
	gpio_pin_set(h->bit_5);
	gpio_pin_set(h->bit_6);
	gpio_pin_set(h->bit_7);
	
	h->kt_logo_defined = 0;
	
	// init LCD device to work in 4bit mode
	if (mode == Lcd4BitMode){
		gpio_pin_clear(h->rs);
		gpio_pin_clear(h->rw);
		delay_us(2000);
		for (i=0; i<3; ++i){
			lcd_write_init(h, 0x03);
		}
		lcd_write_init(h, 0x02);
		lcd_write_cmd(h, LCD_16x2_COMMAND_WORK_IN_4BIT);
		lcd_write_cmd(h, LCD_16x2_COMMAND_DISABLE_DISPLAY);
		lcd_write_cmd(h, LCD_16X2_COMMAND_CLEAR_DISPLAY);
		lcd_write_cmd(h, LCD_16x2_COMMAND_SHIFT_TO_RIGHT);
		lcd_write_cmd(h, LCD_16x2_COMMAND_ENABLE_DISPLAY);	
		delay_us(150);
	} else {
		gpio_pin_clear(h->rs);
		gpio_pin_clear(h->rw);
		delay_us(2000);
		for (i=0; i<3; ++i){
			lcd_write_init(h, 0x03);
		}
		lcd_write_cmd(h, LCD_16x2_COMMAND_WORK_IN_8BIT);
		lcd_write_cmd(h, LCD_16X2_COMMAND_CLEAR_DISPLAY);
		lcd_write_cmd(h, LCD_16x2_COMMAND_SHIFT_TO_RIGHT);
		lcd_write_cmd(h, LCD_16x2_COMMAND_DISABLE_DISPLAY);
		lcd_write_cmd(h, LCD_16X2_COMMAND_CLEAR_DISPLAY);
		lcd_write_cmd(h, LCD_16x2_COMMAND_SHIFT_TO_RIGHT);
		lcd_write_cmd(h, LCD_16x2_COMMAND_ENABLE_DISPLAY);
	}
		
	
}

void delay_us(uint16 us){
	uint16 i;
	for (i = 0; i < us; ++i) {
		__delay_cycles(8);
	}
}

//function usefull only in initialization to work in 4 bit mode
void lcd_write_init(LcdHandle *h, uint8 cmd){
	cmd <<= 4;
	gpio_pin_clear(h->rs);
	gpio_pin_clear(h->rw);

	gpio_pin_set(h->enable);		//set enable pin

	if (cmd & 0x10){
		gpio_pin_set(h->bit_4);
	} else {
		gpio_pin_clear(h->bit_4);
	}
		
	if (cmd & 0x20){
		gpio_pin_set(h->bit_5);
	} else {
		gpio_pin_clear(h->bit_5);
	}

	if (cmd & 0x40){
		gpio_pin_set(h->bit_6);
	} else {
		gpio_pin_clear(h->bit_6);
	}
		
	if (cmd & 0x80){
		gpio_pin_set(h->bit_7);
	} else {
		gpio_pin_clear(h->bit_7);
	}
	gpio_pin_clear(h->enable);		//clear enable pin
	delay_us(2000);
}

void lcd_write_cmd(LcdHandle *h, uint8 cmd){
	uint8 i;
	
	gpio_pin_clear(h->rs);
	gpio_pin_clear(h->rw);
	if (h->mode == Lcd4BitMode){	
		for (i = 0; i<2; ++i){
			gpio_pin_set(h->enable);		//set enable pin
		
			if (cmd & 0x10){
				gpio_pin_set(h->bit_4);
			} else {
				gpio_pin_clear(h->bit_4);
			}
			
			if (cmd & 0x20){
				gpio_pin_set(h->bit_5);
			} else {
				gpio_pin_clear(h->bit_5);
			}
			
			if (cmd & 0x40){
				gpio_pin_set(h->bit_6);
			} else {
				gpio_pin_clear(h->bit_6);
			}
				
			if (cmd & 0x80){
				gpio_pin_set(h->bit_7);
			} else {
				gpio_pin_clear(h->bit_7);
			}	
			gpio_pin_clear(h->enable);		//clear enable pin
			delay_us(2000);
			cmd <<= 4;
		}
	} else {
		gpio_pin_clear(h->rs);
		gpio_pin_clear(h->rw);
		
		gpio_pin_set(h->enable);		//set enable pin
		
		if (cmd & 0x01){
			gpio_pin_set(h->bit_0);
		} else {
			gpio_pin_clear(h->bit_0);
		}
		
		if (cmd & 0x02){
			gpio_pin_set(h->bit_1);
		} else {
			gpio_pin_clear(h->bit_1);
		}
		
		if (cmd & 0x04){
			gpio_pin_set(h->bit_2);
		} else {
			gpio_pin_clear(h->bit_2);
		}
			
		if (cmd & 0x08){
			gpio_pin_set(h->bit_3);
		} else {
			gpio_pin_clear(h->bit_3);
		}
		
		if (cmd & 0x10){
			gpio_pin_set(h->bit_4);
		} else {
			gpio_pin_clear(h->bit_4);
		}
		
		if (cmd & 0x20){
			gpio_pin_set(h->bit_5);
		} else {
			gpio_pin_clear(h->bit_5);
		}
		
		if (cmd & 0x40){
			gpio_pin_set(h->bit_6);
		} else {
			gpio_pin_clear(h->bit_6);
		}
			
		if (cmd & 0x80){
			gpio_pin_set(h->bit_7);
		} else {
			gpio_pin_clear(h->bit_7);
		}

		gpio_pin_clear(h->enable);		//clear enable pin
		delay_us(2000);
	}

}

void lcd_write_char(LcdHandle *h, uint8 cmd){
	uint8 i;
	if ((h->mode) == Lcd4BitMode){
		gpio_pin_set(h->rs);
		gpio_pin_clear(h->rw);
		for (i = 0; i<2; ++i){
			gpio_pin_set(h->enable);		//set enable pin
		
			if (cmd & 0x10){
				gpio_pin_set(h->bit_4);
			} else {
				gpio_pin_clear(h->bit_4);
			}
			
			if (cmd & 0x20){
				gpio_pin_set(h->bit_5);
			} else {
				gpio_pin_clear(h->bit_5);
			}
			
			if (cmd & 0x40){
				gpio_pin_set(h->bit_6);
			} else {
				gpio_pin_clear(h->bit_6);
			}
				
			if (cmd & 0x80){
				gpio_pin_set(h->bit_7);
			} else {
				gpio_pin_clear(h->bit_7);
			}
	
			
			gpio_pin_clear(h->enable);		//clear enable pin
			delay_us(40);
			cmd <<= 4;
		}
	} else {
		gpio_pin_set(h->rs);
		gpio_pin_clear(h->rw);
		
		gpio_pin_set(h->enable);		//set enable pin
		
		if (cmd & 0x01){
			gpio_pin_set(h->bit_0);
		} else {
			gpio_pin_clear(h->bit_0);
		}
		
		if (cmd & 0x02){
			gpio_pin_set(h->bit_1);
		} else {
			gpio_pin_clear(h->bit_1);
		}
		
		if (cmd & 0x04){
			gpio_pin_set(h->bit_2);
		} else {
			gpio_pin_clear(h->bit_2);
		}
			
		if (cmd & 0x08){
			gpio_pin_set(h->bit_3);
		} else {
			gpio_pin_clear(h->bit_3);
		}
		
		if (cmd & 0x10){
			gpio_pin_set(h->bit_4);
		} else {
			gpio_pin_clear(h->bit_4);
		}
		
		if (cmd & 0x20){
			gpio_pin_set(h->bit_5);
		} else {
			gpio_pin_clear(h->bit_5);
		}
		
		if (cmd & 0x40){
			gpio_pin_set(h->bit_6);
		} else {
			gpio_pin_clear(h->bit_6);
		}

		if (cmd & 0x80){
			gpio_pin_set(h->bit_7);
		} else {
			gpio_pin_clear(h->bit_7);
		}
		gpio_pin_clear(h->enable);		//clear enable pin
		delay_us(40);
	}
}

void lcd_set_pos(LcdHandle *h, uint16 x, uint8 y){
	assert(x>=1 && x<=16);
	assert(y == 1 || y == 2);
	--x; // actual indexing starts from zero
	if (y==2) { // add offset for second line
		x=x+0x40;
	}
	lcd_write_cmd(h, x | 0x80);
}

void lcd_write_string(LcdHandle *h, char s[], uint8 row_number, uint8 pos_number){
	uint8 i = 0;
	uint8 c;
	
	lcd_set_pos(h, pos_number, row_number);
	c = s[i];
	while (c) {
		lcd_write_char(h, c);
		i++;
		c = s[i];
	} 
}

void lcd_clean_line(LcdHandle *h, uint8 line_number){
	uint8 i;
	lcd_set_pos(h, 1, line_number);
	for (i = 0; i < 15; i++){
		lcd_write_char(h, ' ');	
	}
}

void lcd_define_kt_logo(LcdHandle *h) {
	uint8 i;
	
	uint8 sign11[8]={0x00, 0x00, 0x00, 0x00, 0x08, 0x14, 0x12, 0x11};
	uint8 sign12[8]={0x00, 0x00, 0x18, 0x14, 0x12, 0x09, 0x08, 0x04};
	uint8 sign13[8]={0x1F, 0x03, 0x0D, 0x11, 0x11, 0x10, 0x00, 0x00};
	uint8 sign21[8]={0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x00};
	uint8 sign22[8]={0x12, 0x09, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00};
	
	for (i=0; i<8; i++){
		lcd_write_cmd(h, 0x40+i);
		lcd_write_char(h, sign11[i]);
	}
	for (i=0; i<8; i++){
		lcd_write_cmd(h, 0x48+i);
		lcd_write_char(h, sign12[i]);
	}
	for (i=0; i<8; i++){
		lcd_write_cmd(h, 0x50+i);
		lcd_write_char(h, sign13[i]);
	}
	for (i=0; i<8; i++){
		lcd_write_cmd(h, 0x58+i);
		lcd_write_char(h, sign21[i]);
	}
	for (i=0; i<8; i++){
		lcd_write_cmd(h, 0x60+i);
		lcd_write_char(h, sign22[i]);
	}
	
	h->kt_logo_defined = 1;
}

void lcd_write_kt_logo(LcdHandle *h, uint8 x){
	if (h->kt_logo_defined == 0) {
		lcd_define_kt_logo(h);
	}
	lcd_set_pos(h, x, 1);
	lcd_write_char(h, 0x00);
	lcd_write_char(h, 0x01);
	lcd_write_char(h, 0x02);
	lcd_set_pos(h, x, 2);
	lcd_write_char(h, 0x03);
	lcd_write_char(h, 0x04);
}

void lcd_write_unsigned_number(LcdHandle *h, uint32 number, uint8 num_digits, uint8 line_number, uint8 starting_position, LcdLeadingZeros leading_zeros) {
	uint32	temp = number;
	uint8	digit;
	uint8	ctr = 0;
	
	do {
		digit 	= temp % 10;
		temp	= temp / 10;
		lcd_set_pos(h, starting_position + num_digits - 1 - ctr, line_number);
		lcd_write_char(h, '0' + digit);
		ctr++;
	} while (temp != 0);
	
	// fill missing digits with zero (in case it's desired)
	if (leading_zeros == LcdLeadingZerosOn) {
		for (ctr = ctr; ctr < num_digits; ++ctr) {
			lcd_set_pos(h, starting_position + num_digits - 1 - ctr, line_number);
			lcd_write_char(h, '0');
		}
	} 
}
 
