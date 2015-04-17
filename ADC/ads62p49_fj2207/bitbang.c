#include "bitbang.h"
#include "hal.h"
//#include <assert.h>

#ifndef BITBANG_MACRO_IMPLEMENTATION

BitbangReturn bitbang_init_field( BitField *bf, void *reg_addr, uint8 reg_size, uint8 start_index, uint8 field_length, uint32 reset_value ) 
{
	uint32 temp_shift = 0;
	BitbangReturn ret_val=Bitbang_OK;
	if (bf==NULL) {
	 	ret_val = Bitbang_ERROR;
	} else if (!((reg_size==1)||(reg_size==2)||(reg_size==4))) {
		ret_val = Bitbang_ERROR;
	} else 
	{
		
		temp_shift			= ((1<<field_length)-1);	
		bf->reg_addr 		= reg_addr;
		bf->reg_size		= reg_size;
		bf->start_index 	= start_index;
		bf->field_length 	= field_length;
//		bf->bit_mask 		= ((uint32*)((1<<field_length)-1))<<start_index;
		bf->bit_mask 		= temp_shift<<start_index;
		bitbang_set_value(bf, reset_value);
	}
	return ret_val;
}

BitbangReturn bitbang_set_value	( BitField *bf, uint32 value )
{
	BitbangReturn ret_val=Bitbang_OK;

 	switch (bf->reg_size)
			{
				case 1:
					*((uint8*)(bf->reg_addr)) &= ~bf->bit_mask;
					*((uint8*)(bf->reg_addr)) |= ((value << bf->start_index) & bf->bit_mask);
			        break;
			    case 2:
			        *((uint16*)(bf->reg_addr)) &= ~bf->bit_mask;
					*((uint16*)(bf->reg_addr)) |= ((value << bf->start_index) & bf->bit_mask);
			        break;
				case 4:
			        *((uint32*)(bf->reg_addr)) &= ~bf->bit_mask;
					*((uint32*)(bf->reg_addr)) |= ((value << bf->start_index) & bf->bit_mask);
			        break;
				default:
					return Bitbang_ERROR;
					
			        
			}


//	*(bf->reg_addr) &= ~bf->bit_mask;
//	*(bf->reg_addr) |= ((value << bf->start_index) & bf->bit_mask);
	return ret_val;
}

BitbangReturn bitbang_set		( BitField *bf )
{
	BitbangReturn ret_val=Bitbang_OK;
	switch (bf->reg_size)
			{
				case 1:
					*((uint8*)(bf->reg_addr))	|= bf->bit_mask;
					break;
			    case 2:
			        *((uint16*)(bf->reg_addr))	|= bf->bit_mask;
					break;
				case 4:
			        *((uint32*)(bf->reg_addr))	|= bf->bit_mask;
			        break;
				default:
					return Bitbang_ERROR;
												        
			}
	
		
//	*(bf->reg_addr) |= bf->bit_mask;
	return ret_val;
}

BitbangReturn bitbang_clear		( BitField *bf )
{
	BitbangReturn ret_val=Bitbang_OK;
	switch (bf->reg_size)
			{
				case 1:
					*((uint8*)(bf->reg_addr))	&= ~bf->bit_mask;
					break;
			    case 2:
			        *((uint16*)(bf->reg_addr))	&= ~bf->bit_mask;
					break;
				case 4:
			        *((uint32*)(bf->reg_addr))	&= ~bf->bit_mask;
			        break;
				default:
					return Bitbang_ERROR;
												        
			}
	
//	*(bf->reg_addr) &= ~bf->bit_mask;
	return ret_val;
}

BitbangReturn bitbang_get		( BitField *bf, void *value )
{
	BitbangReturn ret_val=Bitbang_OK;
	switch (bf->reg_size)
			{
				case 1:
					*(uint8*)value = (*((uint8*)(bf->reg_addr)) & bf->bit_mask) >>  bf->start_index;
					break;
			    case 2:
			        *(uint16*)value = (*((uint16*)(bf->reg_addr)) & bf->bit_mask) >>  bf->start_index;
					break;
				case 4:
			        *(uint32*)value = (*((uint32*)(bf->reg_addr)) & bf->bit_mask) >>  bf->start_index;
			        break;
				default:
					return Bitbang_ERROR;

												        
			}


	
	
	
//	*(uint8*)value = (*((uint8*)(bf->reg_addr)) & bf->bit_mask) >>  bf->start_index;
//	*value = (*(bf->reg_addr) & bf->bit_mask) >>  bf->start_index;
	return ret_val;
}
#else

void _bitbang_dummy_function(void) {
}

#endif
