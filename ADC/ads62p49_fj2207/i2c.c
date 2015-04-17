#include <i2c.h>

//declarations
void _delay_ns(void); /*<set a value of the delay.*/


//functions
void _delay_ns(void){
}

void i2c_send_start_sequence(I2CHandle	*h){
	gpio_pin_configure_as_input(h->i2c_sda);
	_delay_ns();
	gpio_pin_set(h->i2c_scl);
	_delay_ns();
	gpio_pin_configure_as_output(h->i2c_sda);
	_delay_ns();
	gpio_pin_clear(h->i2c_scl);
	_delay_ns();
}

void i2c_init(I2CHandle	*h, GpioPin	 *i2c_sda,	GpioPin	 *i2c_scl){
	h->i2c_sda = i2c_sda;
	h->i2c_scl = i2c_scl;
	
	gpio_pin_clear(h->i2c_sda);
	
	gpio_pin_init(h->i2c_sda);
	gpio_pin_init(h->i2c_scl);
	
	gpio_pin_clear(h->i2c_sda);

	gpio_pin_configure_as_input(h->i2c_sda);
}

void i2c_send_stop_sequence(I2CHandle	*h){
	gpio_pin_configure_as_output(h->i2c_sda);
	_delay_ns();
	gpio_pin_set(h->i2c_scl);
	_delay_ns();
	gpio_pin_configure_as_input(h->i2c_sda);
	_delay_ns();
}

I2cResponseType i2c_write_byte(I2CHandle *h, uint8 data){
	uint8 i, cur_bit;
	for (i=0; i<8; ++i){
		gpio_pin_clear(h->i2c_scl);
		
		cur_bit = ((data >> (7-i) ) & 0x01);
		if (cur_bit) {
			gpio_pin_configure_as_input(h->i2c_sda);
		} else {
			gpio_pin_configure_as_output(h->i2c_sda);
		}
		_delay_ns();	
		gpio_pin_set(h->i2c_scl);
	}
	i2c_get_bit(h, &i);
	if (i != I2C_SLAVE_ACK_RESPONSE){
		i2c_send_stop_sequence(h);
		return I2c_NACK_Error; 
	}
	return I2c_More_Data;	
}

void i2c_get_bit(I2CHandle	*h, uint8 *value){
	gpio_pin_clear(h->i2c_scl);
	gpio_pin_configure_as_input(h->i2c_sda);
	
	*value = gpio_pin_get(h->i2c_sda);
	
	_delay_ns();
	gpio_pin_set((h->i2c_scl));
	_delay_ns();
	gpio_pin_clear((h->i2c_scl));
	_delay_ns();
}

I2cResponseType i2c_choose_device(I2CHandle	*h, uint8	device_address, I2CSlaveAccessMode mode){
	uint8 i;
	uint8 cur_bit;
	//START SIGNAL
	i2c_send_start_sequence(h);
	//Write address to the i2c bus
	for (i=0; i<7; i++){
		gpio_pin_clear((h->i2c_scl));
		
		cur_bit = ((device_address >> (7-i) ) & 0x01);
		if (cur_bit) {
			gpio_pin_configure_as_input(h->i2c_sda);
		} else {
			gpio_pin_configure_as_output(h->i2c_sda);
		}
		_delay_ns();
		gpio_pin_set(h->i2c_scl);
		
	}
	//Set the access mode
	gpio_pin_clear(h->i2c_scl);
	if (!mode){
		gpio_pin_configure_as_output(h->i2c_sda);
	}else {
		gpio_pin_configure_as_input(h->i2c_sda);
	}		
	_delay_ns();
	gpio_pin_set(h->i2c_scl);
	//get the response bit
	i2c_get_bit(h, &i);
	if (i != I2C_SLAVE_ACK_RESPONSE){
		i2c_send_stop_sequence(h);
		return I2c_NACK_Error;
	}
	return I2c_Success;
}

void i2c_get_byte(I2CHandle *h, uint8 *data){
	uint8 i, cur_bit;
	for (i=0; i<8; ++i){
		i2c_get_bit(h, &cur_bit);
		cur_bit &= 0x01;
		*data	= (*data << 1) | cur_bit; 
	}
	_delay_ns();
	gpio_pin_set(h->i2c_scl);
}

void i2c_write_acknowledge_bit(I2CHandle *h, uint8 response){
	gpio_pin_clear(h->i2c_scl);
	if (!response){
		gpio_pin_configure_as_input(h->i2c_sda);
	}else {
		gpio_pin_configure_as_output(h->i2c_sda);
	}		
	_delay_ns();
	gpio_pin_set(h->i2c_scl);
}
