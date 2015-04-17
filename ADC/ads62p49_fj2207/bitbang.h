/*!
 *	@file
 *	@brief Bit bang module.
 *
 *	The bit bang module is implemented in a function based fashion as well as in a macro based fashion.
 *	It can be selected using the preprocessor definition BITBANG_MACRO_IMPLEMENTATION.
 *
 *	For each single bit field, the following preprocessor definitions have to be defined:
 *	The following example applies the the bit field named BF0:
 *		#define BITBANG_BF0_START_INDEX		(2)		// start index of the bit field
 *		#define BITBANG_BF0_FIELD_LENGTH	(4)		// length of the bit field (in bits)
 *		#define BITBANG_BF0_RESET_VALUE		(0)		// reset value of the bit field
 *		#define BITBANG_BF0_REG				reg0	// corresponding register name
 *
 */
#ifndef _BITBANG_H_
#define _BITBANG_H_

#include "hal.h"

/**
 *	By defining the preprocessor definitino BITBANG_MACRO_IMPLEMENTATION, the whole bit bang module is implemented as
 *	macros with the advantage of reducing the required code size.
 */

//#define BITBANG_MACRO_IMPLEMENTATION

/**
 *	BITBANG_PREFIX is necessary to allow access to bit fields in structs. Per default, it is an empty definition.
 *	For example:
 *		typedef struct {
 *			uint32		reg0;
 *			BitField	bf0;
 *		} my_struct_type;
 *
 *		my_struct_type s0;
 *		
 *		#undef BITBANG_PREFIX
 *		#define BITBANG_PREFIX s0.
 */

#define BITBANG_PREFIX // create empty definition
//#define BITBANG_PREFIX dev->

#ifdef BITBANG_MACRO_IMPLEMENTATION

	/**
	 *	bitbang high-level macros
	 */

	//#define BITBANG_INIT_REG(_reg)

	#define BITBANG_INIT_FIELD(_bf) \
				BITBANG_SET_VALUE(_bf, BITBANG_##_bf##_RESET_VALUE)

	#define BITBANG_SET_VALUE(_bf, _value) \
				BITBANG_LOW_LEVEL_FIELD_INSERT(BITBANG_LOW_LEVEL_REG_GET(_bf), _bf, _value)

	#define BITBANG_SET(_bf) \
				BITBANG_LOW_LEVEL_FIELD_INSERT(BITBANG_LOW_LEVEL_REG_GET(_bf), _bf, BITBANG_LOW_LEVEL_BITMASK_GET(_bf)>>BITBANG_##_bf##_START_INDEX)

	#define BITBANG_CLEAR(_bf) \
				BITBANG_LOW_LEVEL_FIELD_INSERT(BITBANG_LOW_LEVEL_REG_GET(_bf), _bf, 0)

	#define BITBANG_GET(_bf, _value) \
				(_value) = BITBANG_LOW_LEVEL_FIELD_EXTRACT(BITBANG_LOW_LEVEL_REG_GET(_bf), _bf)

#else

	/**
	 *	bitbang high-level macros
	 */

	#define BITBANG_INIT_FIELD(_bf) \
				bitbang_init_field(\
					&(BITBANG_PREFIX _bf),\
					&(BITBANG_##_bf##_REG),\
					sizeof(BITBANG_##_bf##_REG),\
					BITBANG_##_bf##_START_INDEX,\
					BITBANG_##_bf##_FIELD_LENGTH,\
					BITBANG_##_bf##_RESET_VALUE\
				);
				
//				BitField *bf, void *reg_addr, uint8 reg_size, uint8 start_index, uint8 field_length, uint32 reset_value
// (irrelevant)		BITBANG_SET_VALUE(_bf, BITBANG_##_bf##_RESET_VALUE)


	#define BITBANG_SET_VALUE(_bf, _value) \
				bitbang_set_value(\
					&(BITBANG_PREFIX _bf),\
					_value\
				)

	#define BITBANG_SET(_bf) \
				bitbang_set(\
					&(BITBANG_PREFIX _bf)\
				)

	#define BITBANG_CLEAR(_bf) \
				bitbang_clear(\
					&(BITBANG_PREFIX _bf)\
				)

	#define BITBANG_GET(_bf, _value) \
				bitbang_get(\
					&(BITBANG_PREFIX _bf),\
					&(_value)\
				)

	typedef struct {
		void 		*reg_addr;
		uint8		reg_size;
		uint8		start_index;
		uint8		field_length;
		uint32  	bit_mask;
	} BitField;

	typedef enum BitbangReturn {
		Bitbang_OK 		= 0,
		Bitbang_ERROR 	= 1
	} BitbangReturn;

	BitbangReturn bitbang_init_field( BitField *bf, void *reg_addr, uint8 reg_size, uint8 start_index, uint8 field_length, uint32 reset_value	);
	BitbangReturn bitbang_set_value	( BitField *bf, uint32 value );
	BitbangReturn bitbang_set		( BitField *bf );
	BitbangReturn bitbang_clear		( BitField *bf );
	BitbangReturn bitbang_get		( BitField *bf, void *value );

#endif

/**
 *	bitbang low-level macros - for internal use only
 */

#define BITBANG_LOW_LEVEL_FIELD_MAKE(_field, _val) \
	(((uint32)(_val) << BITBANG_##_field##_START_INDEX) & BITBANG_LOW_LEVEL_BITMASK_GET(_field))

#define BITBANG_LOW_LEVEL_FIELD_INSERT(_reg, _field, _val) \
	((_reg) = ((_reg) & ~BITBANG_LOW_LEVEL_BITMASK_GET(_field))                          \
	| BITBANG_LOW_LEVEL_FIELD_MAKE(_field, _val))

#define BITBANG_LOW_LEVEL_FIELD_EXTRACT(_reg, _field) \
	(((_reg) & BITBANG_LOW_LEVEL_BITMASK_GET(_field)) >> BITBANG_##_field##_START_INDEX)

	#define BITBANG_LOW_LEVEL_BITMASK_GET(_field) \
	((uint32)((1<<BITBANG_##_field##_FIELD_LENGTH)-1)<<BITBANG_##_field##_START_INDEX)

#define BITBANG_LOW_LEVEL_REG_GET(_field) \
	(BITBANG_##_field##_REG)

#endif
