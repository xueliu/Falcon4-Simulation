#ifndef _CDCE62005_REG_H_
#define _CDCE62005_REG_H_



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 		Register 0
//		100000011000010000


#define BITBANG_REG0_RESET_VALUE					(0x68060100)
#define BITBANG_REG1_RESET_VALUE					(0x69060301)
#define BITBANG_REG2_RESET_VALUE					(0x68060302)
#define BITBANG_REG3_RESET_VALUE					(0x68060303)
#define BITBANG_REG4_RESET_VALUE					(0xe8060304)
#define BITBANG_REG5_RESET_VALUE					(0x009c0b35)
#define BITBANG_REG6_RESET_VALUE					(0x844e19c6)
#define BITBANG_REG7_RESET_VALUE					(0x34a9c917)
#define BITBANG_REG8_RESET_VALUE					(0x80001808)

#define BITBANG_REG0_ADDR_REG 						(dev->reg0)
#define BITBANG_REG0_ADDR_START_INDEX 				(0)
#define BITBANG_REG0_ADDR_FIELD_LENGTH 				(4)
#define BITBANG_REG0_ADDR_RESET_VALUE 				(0)

#define BITBANG_REG0_DIV2PRI_REG 					(dev->reg0)	
#define BITBANG_REG0_DIV2PRI_START_INDEX 			(4)
#define BITBANG_REG0_DIV2PRI_FIELD_LENGTH 			(2)
#define BITBANG_REG0_DIV2PRI_RESET_VALUE 			(0)
	
#define BITBANG_REG0_RESERVED_REG 					(dev->reg0)	
#define BITBANG_REG0_RESERVED_START_INDEX 			(6)
#define BITBANG_REG0_RESERVED_FIELD_LENGTH 			(2)
#define BITBANG_REG0_RESERVED_RESET_VALUE 			(0)

#define BITBANG_REG0_OUTMUX0SEL_REG 				(dev->reg0)	
#define BITBANG_REG0_OUTMUX0SEL_START_INDEX 		(8)
#define BITBANG_REG0_OUTMUX0SEL_FIELD_LENGTH 		(2)
#define BITBANG_REG0_OUTMUX0SEL_RESET_VALUE 		(0x11)

#define BITBANG_REG0_PH0ADJC_REG 					(dev->reg0)	
#define BITBANG_REG0_PH0ADJC_START_INDEX 			(10)
#define BITBANG_REG0_PH0ADJC_FIELD_LENGTH 			(7)
#define BITBANG_REG0_PH0ADJC_RESET_VALUE 			(0)
		
#define BITBANG_REG0_OUT0DIVRSEL_REG 				(dev->reg0)	
#define BITBANG_REG0_OUT0DIVRSEL_START_INDEX 		(17)
#define BITBANG_REG0_OUT0DIVRSEL_FIELD_LENGTH 		(7)
#define BITBANG_REG0_OUT0DIVRSEL_RESET_VALUE 		(0x3)
	
#define BITBANG_REG0_OUT0DIVSEL_REG 				(dev->reg0)	
#define BITBANG_REG0_OUT0DIVSEL_START_INDEX 		(24)
#define BITBANG_REG0_OUT0DIVSEL_FIELD_LENGTH 		(1)
#define BITBANG_REG0_OUT0DIVSEL_RESET_VALUE 		(1)
	
#define BITBANG_REG0_HISWINGLVPECL0_REG 			(dev->reg0)	
#define BITBANG_REG0_HISWINGLVPECL0_START_INDEX 	(25)
#define BITBANG_REG0_HISWINGLVPECL0_FIELD_LENGTH 	(1)
#define BITBANG_REG0_HISWINGLVPECL0_RESET_VALUE 	(0)
	
#define BITBANG_REG0_CMOSMODE0P_REG 				(dev->reg0)	
#define BITBANG_REG0_CMOSMODE0P_START_INDEX 		(26)
#define BITBANG_REG0_CMOSMODE0P_FIELD_LENGTH 		(2)
#define BITBANG_REG0_CMOSMODE0P_RESET_VALUE 		(0x2)
	
#define BITBANG_REG0_CMOSMODE0N_REG 				(dev->reg0)
#define BITBANG_REG0_CMOSMODE0N_START_INDEX 		(28)
#define BITBANG_REG0_CMOSMODE0N_FIELD_LENGTH 		(2)
#define BITBANG_REG0_CMOSMODE0N_RESET_VALUE 		(0x2)
	
#define BITBANG_REG0_OUTBUFSEL0_REG 				(dev->reg0)	
#define BITBANG_REG0_OUTBUFSEL0_START_INDEX 		(30)
#define BITBANG_REG0_OUTBUFSEL0_FIELD_LENGTH 		(2)
#define BITBANG_REG0_OUTBUFSEL0_RESET_VALUE 		(0x1)

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//		Register 1
//		???

#define BITBANG_REG1_ADDR_REG 						(dev->reg1)
#define BITBANG_REG1_ADDR_START_INDEX 				(0)
#define BITBANG_REG1_ADDR_FIELD_LENGTH 				(4)
#define BITBANG_REG1_ADDR_RESET_VALUE 				(1)
	
#define BITBANG_REG1_DIV2SEC_REG 					(dev->reg1)	
#define BITBANG_REG1_DIV2SEC_START_INDEX 			(4)
#define BITBANG_REG1_DIV2SEC_FIELD_LENGTH 			(2)
#define BITBANG_REG1_DIV2SEC_RESET_VALUE 			(0)

#define BITBANG_REG1_RESERVED_REG 					(dev->reg1)
#define BITBANG_REG1_RESERVED_START_INDEX 			(6)
#define BITBANG_REG1_RESERVED_FIELD_LENGTH 			(2)
#define BITBANG_REG1_RESERVED_RESET_VALUE 			(0)

#define BITBANG_REG1_OUTMUX1SEL_REG 				(dev->reg1)	
#define BITBANG_REG1_OUTMUX1SEL_START_INDEX 		(8)
#define BITBANG_REG1_OUTMUX1SEL_FIELD_LENGTH 		(2)
#define BITBANG_REG1_OUTMUX1SEL_RESET_VALUE 		(0x3)

#define BITBANG_REG1_PH1ADJC_REG 					(dev->reg1)
#define BITBANG_REG1_PH1ADJC_START_INDEX 			(10)
#define BITBANG_REG1_PH1ADJC_FIELD_LENGTH 			(7)
#define BITBANG_REG1_PH1ADJC_RESET_VALUE 			(0x0)

#define BITBANG_REG1_OUT1DIVRSEL_REG 				(dev->reg1)	
#define BITBANG_REG1_OUT1DIVRSEL_START_INDEX 		(17)
#define BITBANG_REG1_OUT1DIVRSEL_FIELD_LENGTH 		(7)
#define BITBANG_REG1_OUT1DIVRSEL_RESET_VALUE 		(0x03)

#define BITBANG_REG1_OUT1DIVSEL_REG 				(dev->reg1)	
#define BITBANG_REG1_OUT1DIVSEL_START_INDEX 		(24)
#define BITBANG_REG1_OUT1DIVSEL_FIELD_LENGTH 		(1)
#define BITBANG_REG1_OUT1DIVSEL_RESET_VALUE 		(1)

#define BITBANG_REG1_HISWINGLVPECL1_REG 			(dev->reg1)	
#define BITBANG_REG1_HISWINGLVPECL1_START_INDEX 	(25)
#define BITBANG_REG1_HISWINGLVPECL1_FIELD_LENGTH 	(1)
#define BITBANG_REG1_HISWINGLVPECL1_RESET_VALUE 	(0)

#define BITBANG_REG1_CMOSMODE1P_REG 				(dev->reg1)
#define BITBANG_REG1_CMOSMODE1P_START_INDEX 		(26)
#define BITBANG_REG1_CMOSMODE1P_FIELD_LENGTH 		(2)
#define BITBANG_REG1_CMOSMODE1P_RESET_VALUE 		(0x2)

#define BITBANG_REG1_CMOSMODE1N_REG 				(dev->reg1)	
#define BITBANG_REG1_CMOSMODE1N_START_INDEX 		(28)
#define BITBANG_REG1_CMOSMODE1N_FIELD_LENGTH 		(2)
#define BITBANG_REG1_CMOSMODE1N_RESET_VALUE 		(0x2)

#define BITBANG_REG1_OUTBUFSEL1_REG 				(dev->reg1)
#define BITBANG_REG1_OUTBUFSEL1_START_INDEX 		(30)
#define BITBANG_REG1_OUTBUFSEL1_FIELD_LENGTH 		(2)
#define BITBANG_REG1_OUTBUFSEL1_RESET_VALUE 		(0x1)


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//		Register 2
//		1000000110000110000000110000

#define BITBANG_REG2_ADDR_REG 						(dev->reg2)	
#define BITBANG_REG2_ADDR_START_INDEX 				(0)
#define BITBANG_REG2_ADDR_FIELD_LENGTH 				(4)
#define BITBANG_REG2_ADDR_RESET_VALUE 				(2)

#define BITBANG_REG2_REFDIV_REG 					(dev->reg2)	
#define BITBANG_REG2_REFDIV_START_INDEX 			(4)
#define BITBANG_REG2_REFDIV_FIELD_LENGTH 			(2)
#define BITBANG_REG2_REFDIV_RESET_VALUE 			(0)

#define BITBANG_REG2_RESERVED_REG 					(dev->reg2)
#define BITBANG_REG2_RESERVED_START_INDEX 			(6)
#define BITBANG_REG2_RESERVED_FIELD_LENGTH 			(2)
#define BITBANG_REG2_RESERVED_RESET_VALUE 			(0)

#define BITBANG_REG2_OUTMUX2SEL_REG 				(dev->reg2)	
#define BITBANG_REG2_OUTMUX2SEL_START_INDEX 		(8)
#define BITBANG_REG2_OUTMUX2SEL_FIELD_LENGTH 		(2)
#define BITBANG_REG2_OUTMUX2SEL_RESET_VALUE 		(0x3)

#define BITBANG_REG2_PH2ADJC_REG 					(dev->reg2)	
#define BITBANG_REG2_PH2ADJC_START_INDEX 			(10)
#define BITBANG_REG2_PH2ADJC_FIELD_LENGTH 			(7)
#define BITBANG_REG2_PH2ADJC_RESET_VALUE 			(0)

#define BITBANG_REG2_OUT2DIVRSEL_REG 				(dev->reg2)	
#define BITBANG_REG2_OUT2DIVRSEL_START_INDEX 		(17)
#define BITBANG_REG2_OUT2DIVRSEL_FIELD_LENGTH 		(7)
#define BITBANG_REG2_OUT2DIVRSEL_RESET_VALUE 		(0x3)

#define BITBANG_REG2_OUT2DIVSEL_REG 				(dev->reg2)	
#define BITBANG_REG2_OUT2DIVSEL_START_INDEX 		(24)
#define BITBANG_REG2_OUT2DIVSEL_FIELD_LENGTH 		(1)
#define BITBANG_REG2_OUT2DIVSEL_RESET_VALUE 		(1)

#define BITBANG_REG2_HISWINGLVPEC2_REG 				(dev->reg2)
#define BITBANG_REG2_HISWINGLVPEC2_START_INDEX 		(25)
#define BITBANG_REG2_HISWINGLVPEC2_FIELD_LENGTH 	(1)
#define BITBANG_REG2_HISWINGLVPEC2_RESET_VALUE 		(0)

#define BITBANG_REG2_CMOSMODE2P_REG 				(dev->reg2)	
#define BITBANG_REG2_CMOSMODE2P_START_INDEX 		(26)
#define BITBANG_REG2_CMOSMODE2P_FIELD_LENGTH 		(2)
#define BITBANG_REG2_CMOSMODE2P_RESET_VALUE 		(0x2)

#define BITBANG_REG2_CMOSMODE2N_REG 				(dev->reg2)	
#define BITBANG_REG2_CMOSMODE2N_START_INDEX 		(28)
#define BITBANG_REG2_CMOSMODE2N_FIELD_LENGTH 		(2)
#define BITBANG_REG2_CMOSMODE2N_RESET_VALUE 		(0x2)

#define BITBANG_REG2_OUTBUFSEL2_REG 				(dev->reg2)	
#define BITBANG_REG2_OUTBUFSEL2_START_INDEX 		(30)
#define BITBANG_REG2_OUTBUFSEL2_FIELD_LENGTH 		(2)
#define BITBANG_REG2_OUTBUFSEL2_RESET_VALUE 		(0x1)

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//		Register 3
//		1110101110000110000000110000

#define BITBANG_REG3_ADDR_REG 						(dev->reg3)
#define BITBANG_REG3_ADDR_START_INDEX 				(0)
#define BITBANG_REG3_ADDR_FIELD_LENGTH 				(4)
#define BITBANG_REG3_ADDR_RESET_VALUE 				(3)

#define BITBANG_REG3_REFDIV2_REG 					(dev->reg3)	
#define BITBANG_REG3_REFDIV2_START_INDEX 			(4)
#define BITBANG_REG3_REFDIV2_FIELD_LENGTH 			(1)
#define BITBANG_REG3_REFDIV2_RESET_VALUE 			(0)

#define BITBANG_REG3_RESERVED_REG 					(dev->reg3)	
#define BITBANG_REG3_RESERVED_START_INDEX 			(5)
#define BITBANG_REG3_RESERVED_FIELD_LENGTH 			(3)
#define BITBANG_REG3_RESERVED_RESET_VALUE 			(0)

#define BITBANG_REG3_OUTMUX3SEL_REG 				(dev->reg3)
#define BITBANG_REG3_OUTMUX3SEL_START_INDEX 		(8)
#define BITBANG_REG3_OUTMUX3SEL_FIELD_LENGTH 		(2)
#define BITBANG_REG3_OUTMUX3SEL_RESET_VALUE 		(0x3)

#define BITBANG_REG3_PH3ADJC_REG 					(dev->reg3)	
#define BITBANG_REG3_PH3ADJC_START_INDEX 			(10)
#define BITBANG_REG3_PH3ADJC_FIELD_LENGTH 			(7)
#define BITBANG_REG3_PH3ADJC_RESET_VALUE 			(0)

#define BITBANG_REG3_OUT3DIVRSEL_REG 				(dev->reg3)	
#define BITBANG_REG3_OUT3DIVRSEL_START_INDEX 		(17)
#define BITBANG_REG3_OUT3DIVRSEL_FIELD_LENGTH 		(7)
#define BITBANG_REG3_OUT3DIVRSEL_RESET_VALUE 		(0x3)

#define BITBANG_REG3_OUT3DIVSEL_REG 				(dev->reg3)	
#define BITBANG_REG3_OUT3DIVSEL_START_INDEX 		(24)
#define BITBANG_REG3_OUT3DIVSEL_FIELD_LENGTH 		(1)
#define BITBANG_REG3_OUT3DIVSEL_RESET_VALUE 		(1)

#define BITBANG_REG3_HISWINGLVPEC3_REG 				(dev->reg3)	
#define BITBANG_REG3_HISWINGLVPEC3_START_INDEX 		(25)
#define BITBANG_REG3_HISWINGLVPEC3_FIELD_LENGTH 	(1)
#define BITBANG_REG3_HISWINGLVPEC3_RESET_VALUE 		(0)

#define BITBANG_REG3_CMOSMODE3P_REG 				(dev->reg3)	
#define BITBANG_REG3_CMOSMODE3P_START_INDEX 		(26)
#define BITBANG_REG3_CMOSMODE3P_FIELD_LENGTH 		(2)
#define BITBANG_REG3_CMOSMODE3P_RESET_VALUE 		(0x2)

#define BITBANG_REG3_CMOSMODE3N_REG 				(dev->reg3)	
#define BITBANG_REG3_CMOSMODE3N_START_INDEX 		(28)
#define BITBANG_REG3_CMOSMODE3N_FIELD_LENGTH 		(2)
#define BITBANG_REG3_CMOSMODE3N_RESET_VALUE 		(0x2)

#define BITBANG_REG3_OUTBUFSEL3_REG 				(dev->reg3)	
#define BITBANG_REG3_OUTBUFSEL3_START_INDEX 		(30)
#define BITBANG_REG3_OUTBUFSEL3_FIELD_LENGTH 		(2)
#define BITBANG_REG3_OUTBUFSEL3_RESET_VALUE 		(0x1)

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//		Register 4
//		110000110000000110001

#define BITBANG_REG4_ADDR_REG 						(dev->reg4)
#define BITBANG_REG4_ADDR_START_INDEX 				(0)
#define BITBANG_REG4_ADDR_FIELD_LENGTH 				(4)
#define BITBANG_REG4_ADDR_RESET_VALUE 				(0x4)

#define BITBANG_REG4_RESERVED0_REG 					(dev->reg4)	
#define BITBANG_REG4_RESERVED0_START_INDEX 			(4)
#define BITBANG_REG4_RESERVED0_FIELD_LENGTH 		(1)
#define BITBANG_REG4_RESERVED0_RESET_VALUE 			(0)

#define BITBANG_REG4_ATETEST_REG 					(dev->reg4)	
#define BITBANG_REG4_ATETEST_START_INDEX 			(5)
#define BITBANG_REG4_ATETEST_FIELD_LENGTH 			(1)
#define BITBANG_REG4_ATETEST_RESET_VALUE 			(0)

#define BITBANG_REG4_RESERVED1_REG 					(dev->reg4)
#define BITBANG_REG4_RESERVED1_START_INDEX 			(6)
#define BITBANG_REG4_RESERVED1_FIELD_LENGTH 		(2)
#define BITBANG_REG4_RESERVED1_RESET_VALUE 			(0)

#define BITBANG_REG4_OUTMUX4SEL_REG 				(dev->reg4)	
#define BITBANG_REG4_OUTMUX4SEL_START_INDEX 		(8)
#define BITBANG_REG4_OUTMUX4SEL_FIELD_LENGTH 		(2)
#define BITBANG_REG4_OUTMUX4SEL_RESET_VALUE 		(0x3)

#define BITBANG_REG4_PH4ADJC_REG 					(dev->reg4)
#define BITBANG_REG4_PH4ADJC_START_INDEX 			(10)
#define BITBANG_REG4_PH4ADJC_FIELD_LENGTH 			(7)
#define BITBANG_REG4_PH4ADJC_RESET_VALUE 			(0)

#define BITBANG_REG4_OUT4DIVRSEL_REG 				(dev->reg4)	
#define BITBANG_REG4_OUT4DIVRSEL_START_INDEX 		(17)
#define BITBANG_REG4_OUT4DIVRSEL_FIELD_LENGTH 		(7)
#define BITBANG_REG4_OUT4DIVRSEL_RESET_VALUE 		(0x3)

#define BITBANG_REG4_OUT4DIVSEL_REG 				(dev->reg4)	
#define BITBANG_REG4_OUT4DIVSEL_START_INDEX 		(24)
#define BITBANG_REG4_OUT4DIVSEL_FIELD_LENGTH 		(1)
#define BITBANG_REG4_OUT4DIVSEL_RESET_VALUE 		(1)

#define BITBANG_REG4_HISWINGLVPEC4_REG 				(dev->reg4)	
#define BITBANG_REG4_HISWINGLVPEC4_START_INDEX 		(25)
#define BITBANG_REG4_HISWINGLVPEC4_FIELD_LENGTH 	(1)
#define BITBANG_REG4_HISWINGLVPEC4_RESET_VALUE 		(0)

#define BITBANG_REG4_CMOSMODE4P_REG 				(dev->reg4)	
#define BITBANG_REG4_CMOSMODE4P_START_INDEX 		(26)
#define BITBANG_REG4_CMOSMODE4P_FIELD_LENGTH 		(2)
#define BITBANG_REG4_CMOSMODE4P_RESET_VALUE 		(2)

#define BITBANG_REG4_CMOSMODE4N_REG 				(dev->reg4)
#define BITBANG_REG4_CMOSMODE4N_START_INDEX 		(28)
#define BITBANG_REG4_CMOSMODE4N_FIELD_LENGTH 		(2)
#define BITBANG_REG4_CMOSMODE4N_RESET_VALUE 		(2)

#define BITBANG_REG4_OUTBUFSEL4_REG 				(dev->reg4)	
#define BITBANG_REG4_OUTBUFSEL4_START_INDEX 		(30)
#define BITBANG_REG4_OUTBUFSEL4_FIELD_LENGTH 		(2)
#define BITBANG_REG4_OUTBUFSEL4_RESET_VALUE 		(0x3)			//Port 4 is LVDS output and is enabled

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------				
//
//		Register 5	                                                    	
//		1000000011100000010111110

#define BITBANG_REG5_ADDR_REG 						(dev->reg5)	
#define BITBANG_REG5_ADDR_START_INDEX 				(0)
#define BITBANG_REG5_ADDR_FIELD_LENGTH 				(4)
#define BITBANG_REG5_ADDR_RESET_VALUE 				(5)


#define BITBANG_REG5_INBUFSEL_REG 					(dev->reg5)	
#define BITBANG_REG5_INBUFSEL_START_INDEX 			(4)
#define BITBANG_REG5_INBUFSEL_FIELD_LENGTH 			(2)
#define BITBANG_REG5_INBUFSEL_RESET_VALUE 			(11)

#define BITBANG_REG5_SMART_MUX_REG 					(dev->reg5)	
#define BITBANG_REG5_SMART_MUX_START_INDEX 			(6)
#define BITBANG_REG5_SMART_MUX_FIELD_LENGTH 		(3)
#define BITBANG_REG5_SMART_MUX_RESET_VALUE 			(0x4)

#define BITBANG_REG5_EECLKSEL_REG 					(dev->reg5)	
#define BITBANG_REG5_EECLKSEL_START_INDEX 			(9)
#define BITBANG_REG5_EECLKSEL_FIELD_LENGTH			(1)
#define BITBANG_REG5_EECLKSEL_RESET_VALUE 			(1)

#define BITBANG_REG5_ACDCSEL_REG 					(dev->reg5)	
#define BITBANG_REG5_ACDCSEL_START_INDEX 			(10)
#define BITBANG_REG5_ACDCSEL_FIELD_LENGTH 			(1)
#define BITBANG_REG5_ACDCSEL_RESET_VALUE 			(1)

#define BITBANG_REG5_HYSTEN_REG 					(dev->reg5)	
#define BITBANG_REG5_HYSTEN_START_INDEX 			(11)
#define BITBANG_REG5_HYSTEN_FIELD_LENGTH 			(1)
#define BITBANG_REG5_HYSTEN_RESET_VALUE 			(0)				//all inputs are disabled

#define BITBANG_REG5_PRI_TERMSEL_REG 				(dev->reg5)	
#define BITBANG_REG5_PRI_TERMSEL_START_INDEX 		(12)
#define BITBANG_REG5_PRI_TERMSEL_FIELD_LENGTH 		(1)
#define BITBANG_REG5_PRI_TERMSEL_RESET_VALUE 		(0)

#define BITBANG_REG5_PRIINVBB_REG 					(dev->reg5)	
#define BITBANG_REG5_PRIINVBB_START_INDEX 			(13)
#define BITBANG_REG5_PRIINVBB_FIELD_LENGTH 			(1)
#define BITBANG_REG5_PRIINVBB_RESET_VALUE 			(1)

#define BITBANG_REG5_SECINVBB_REG 					(dev->reg5)
#define BITBANG_REG5_SECINVBB_START_INDEX 			(14)
#define BITBANG_REG5_SECINVBB_FIELD_LENGTH 			(1)
#define BITBANG_REG5_SECINVBB_RESET_VALUE 			(1)

#define BITBANG_REG5_FAILSAFE_REG 					(dev->reg5)	
#define BITBANG_REG5_FAILSAFE_START_INDEX 			(15)
#define BITBANG_REG5_FAILSAFE_FIELD_LENGTH 			(1)
#define BITBANG_REG5_FAILSAFE_RESET_VALUE 			(0)

#define BITBANG_REG5_RESERVED_REG 					(dev->reg5)
#define BITBANG_REG5_RESERVED_START_INDEX 			(16)
#define BITBANG_REG5_RESERVED_FIELD_LENGTH 			(2)
#define BITBANG_REG5_RESERVED_RESET_VALUE 			(0)

#define BITBANG_REG5_SELINDIV_REG 					(dev->reg5)	
#define BITBANG_REG5_SELINDIV_START_INDEX 			(18)
#define BITBANG_REG5_SELINDIV_FIELD_LENGTH 			(8)
#define BITBANG_REG5_SELINDIV_RESET_VALUE 			(0x27)

#define BITBANG_REG5_LOCKW_REG 						(dev->reg5)	
#define BITBANG_REG5_LOCKW_START_INDEX 				(26)
#define BITBANG_REG5_LOCKW_FIELD_LENGTH 			(4)
#define BITBANG_REG5_LOCKW_RESET_VALUE 				(4)

#define BITBANG_REG5_LOCKDET_REG 					(dev->reg5)	
#define BITBANG_REG5_LOCKDET_START_INDEX 			(30)
#define BITBANG_REG5_LOCKDET_FIELD_LENGTH 			(1)
#define BITBANG_REG5_LOCKDET_RESET_VALUE 			(1)				// trigger after 64th tic

#define BITBANG_REG5_ADLOCK_REG 					(dev->reg5)	
#define BITBANG_REG5_ADLOCK_START_INDEX 			(31)
#define BITBANG_REG5_ADLOCK_FIELD_LENGTH 			(1)
#define BITBANG_REG5_ADLOCK_RESET_VALUE 			(0)

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//		Register 6
//		10010111110000110011010

#define BITBANG_REG6_ADDR_REG 						(dev->reg6)	
#define BITBANG_REG6_ADDR_START_INDEX 				(0)
#define BITBANG_REG6_ADDR_FIELD_LENGTH 				(4)
#define BITBANG_REG6_ADDR_RESET_VALUE 				(6)

#define BITBANG_REG6_SELVCO_REG 					(dev->reg6)	
#define BITBANG_REG6_SELVCO_START_INDEX 			(4)
#define BITBANG_REG6_SELVCO_FIELD_LENGTH 			(1)
#define BITBANG_REG6_SELVCO_RESET_VALUE 			(0)

#define BITBANG_REG6_SELPRESC_REG 					(dev->reg6)	
#define BITBANG_REG6_SELPRESC_START_INDEX 			(5)
#define BITBANG_REG6_SELPRESC_FIELD_LENGTH			(2)
#define BITBANG_REG6_SELPRESC_RESET_VALUE 			(0x2)

#define BITBANG_REG6_SELFBDIV_REG 					(dev->reg6)	
#define BITBANG_REG6_SELFBDIV_START_INDEX 			(7)
#define BITBANG_REG6_SELFBDIV_FIELD_LENGTH 			(8)
#define BITBANG_REG6_SELFBDIV_RESET_VALUE 			(0x33)			// feedback buffer divider is 200
	
#define BITBANG_REG6_RESERVED0_REG 					(dev->reg6)	
#define BITBANG_REG6_RESERVED0_START_INDEX 			(15)
#define BITBANG_REG6_RESERVED0_FIELD_LENGTH 		(1)
#define BITBANG_REG6_RESERVED0_RESET_VALUE 			(0)

#define BITBANG_REG6_SEC_TERMSEL_REG 				(dev->reg6)
#define BITBANG_REG6_SEC_TERMSEL_START_INDEX 		(16)
#define BITBANG_REG6_SEC_TERMSEL_FIELD_LENGTH 		(1)
#define BITBANG_REG6_SEC_TERMSEL_RESET_VALUE 		(0)

#define BITBANG_REG6_SELBPDIV_REG 					(dev->reg6)	
#define BITBANG_REG6_SELBPDIV_START_INDEX 			(17)
#define BITBANG_REG6_SELBPDIV_FIELD_LENGTH 			(3)
#define BITBANG_REG6_SELBPDIV_RESET_VALUE 			(0x7)			// bypass divider is 1

#define BITBANG_REG6_ICPSEL_REG 					(dev->reg6)
#define BITBANG_REG6_ICPSEL_START_INDEX 			(20)
#define BITBANG_REG6_ICPSEL_FIELD_LENGTH 			(4)
#define BITBANG_REG6_ICPSEL_RESET_VALUE 			(0x4)

#define BITBANG_REG6_RESERVED1_REG 					(dev->reg6)	
#define BITBANG_REG6_RESERVED1_START_INDEX 			(24)
#define BITBANG_REG6_RESERVED1_FIELD_LENGTH 		(1)
#define BITBANG_REG6_RESERVED1_RESET_VALUE 			(0)

#define BITBANG_REG6_CPPULSEWIDTH_REG 				(dev->reg6)	
#define BITBANG_REG6_CPPULSEWIDTH_START_INDEX 		(25)
#define BITBANG_REG6_CPPULSEWIDTH_FIELD_LENGTH 		(1)
#define BITBANG_REG6_CPPULSEWIDTH_RESET_VALUE 		(0)

#define BITBANG_REG6_ENCAL_REG 						(dev->reg6)	
#define BITBANG_REG6_ENCAL_START_INDEX 				(26)
#define BITBANG_REG6_ENCAL_FIELD_LENGTH 			(1)
#define BITBANG_REG6_ENCAL_RESET_VALUE 				(1)

#define BITBANG_REG6_RESERVED2_REG 					(dev->reg6)	
#define BITBANG_REG6_RESERVED2_START_INDEX 			(27)
#define BITBANG_REG6_RESERVED2_FIELD_LENGTH 		(1)
#define BITBANG_REG6_RESERVED2_RESET_VALUE 			(0)

#define BITBANG_REG6_AUXOUTEN_REG 					(dev->reg6)	
#define BITBANG_REG6_AUXOUTEN_START_INDEX 			(28)
#define BITBANG_REG6_AUXOUTEN_FIELD_LENGTH 			(1)
#define BITBANG_REG6_AUXOUTEN_RESET_VALUE 			(0)

#define BITBANG_REG6_AUXFEEDSEL_REG 				(dev->reg6)
#define BITBANG_REG6_AUXFEEDSEL_START_INDEX 		(29)
#define BITBANG_REG6_AUXFEEDSEL_FIELD_LENGTH 		(1)
#define BITBANG_REG6_AUXFEEDSEL_RESET_VALUE 		(0)

#define BITBANG_REG6_EXLFSEL_REG 					(dev->reg6)
#define BITBANG_REG6_EXLFSEL_START_INDEX 			(30)
#define BITBANG_REG6_EXLFSEL_FIELD_LENGTH 			(1)
#define BITBANG_REG6_EXLFSEL_RESET_VALUE 			(0)
	
#define BITBANG_REG6_ENCAL_MODE_REG 				(dev->reg6)	
#define BITBANG_REG6_ENCAL_MODE_START_INDEX 		(31)
#define BITBANG_REG6_ENCAL_MODE_FIELD_LENGTH 		(1)
#define BITBANG_REG6_ENCAL_MODE_RESET_VALUE 		(0)

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//		Register 7
//		1011110100000000001101111111	

#define BITBANG_REG7_ADDR_REG 						(dev->reg7)	
#define BITBANG_REG7_ADDR_START_INDEX 				(0)
#define BITBANG_REG7_ADDR_FIELD_LENGTH 				(4)
#define BITBANG_REG7_ADDR_RESET_VALUE 				(6)

#define BITBANG_REG7_LFRCSEL_C2_REG 				(dev->reg7)	
#define BITBANG_REG7_LFRCSEL_C2_START_INDEX 		(4)
#define BITBANG_REG7_LFRCSEL_C2_FIELD_LENGTH 		(5)
#define BITBANG_REG7_LFRCSEL_C2_RESET_VALUE 		(0x11)

#define BITBANG_REG7_LFRCSEL_R2_REG 				(dev->reg7)	
#define BITBANG_REG7_LFRCSEL_R2_START_INDEX 		(9)
#define BITBANG_REG7_LFRCSEL_R2_FIELD_LENGTH		(5)
#define BITBANG_REG7_LFRCSEL_R2_RESET_VALUE 		(0x4)

#define BITBANG_REG7_LFRCSEL_C1_REG 				(dev->reg7)	
#define BITBANG_REG7_LFRCSEL_C1_START_INDEX 		(14)
#define BITBANG_REG7_LFRCSEL_C1_FIELD_LENGTH 		(5)
#define BITBANG_REG7_LFRCSEL_C1_RESET_VALUE 		(0x7)

#define BITBANG_REG7_LFRCSEL_C3_REG 				(dev->reg7)	
#define BITBANG_REG7_LFRCSEL_C3_START_INDEX 		(19)
#define BITBANG_REG7_LFRCSEL_C3_FIELD_LENGTH 		(4)
#define BITBANG_REG7_LFRCSEL_C3_RESET_VALUE 		(0x5)

#define BITBANG_REG7_LFRCSEL_R3_REG 				(dev->reg7)	
#define BITBANG_REG7_LFRCSEL_R3_START_INDEX 		(23)
#define BITBANG_REG7_LFRCSEL_R3_FIELD_LENGTH 		(2)
#define BITBANG_REG7_LFRCSEL_R3_RESET_VALUE 		(0x1)

#define BITBANG_REG7_RESERVED0_REG 					(dev->reg7)	
#define BITBANG_REG7_RESERVED0_START_INDEX 			(25)
#define BITBANG_REG7_RESERVED0_FIELD_LENGTH 		(1)
#define BITBANG_REG7_RESERVED0_RESET_VALUE 			(0)

#define BITBANG_REG7_TESTMUX1_REG 					(dev->reg7)
#define BITBANG_REG7_TESTMUX1_START_INDEX 			(14)
#define BITBANG_REG7_TESTMUX1_FIELD_LENGTH 			(1)
#define BITBANG_REG7_TESTMUX1_RESET_VALUE 			(1)

#define BITBANG_REG7_SEL_DEL2_REG 					(dev->reg7)
#define BITBANG_REG7_SEL_DEL2_START_INDEX 			(26)
#define BITBANG_REG7_SEL_DEL2_FIELD_LENGTH 			(1)
#define BITBANG_REG7_SEL_DEL2_RESET_VALUE 			(1)

#define BITBANG_REG7_TEXTMUX2_REG 					(dev->reg7)	
#define BITBANG_REG7_TEXTMUX2_START_INDEX 			(28)
#define BITBANG_REG7_TEXTMUX2_FIELD_LENGTH 			(1)
#define BITBANG_REG7_TEXTMUX2_RESET_VALUE 			(1)
	
#define BITBANG_REG7_SEL_DEL1_REG 					(dev->reg7)	
#define BITBANG_REG7_SEL_DEL1_START_INDEX 			(29)
#define BITBANG_REG7_SEL_DEL1_FIELD_LENGTH 			(1)
#define BITBANG_REG7_SEL_DEL1_RESET_VALUE 			(1)
	
#define BITBANG_REG7_EPLOCK_REG 					(dev->reg7)
#define BITBANG_REG7_EPLOCK_START_INDEX 			(30)
#define BITBANG_REG7_EPLOCK_FIELD_LENGTH 			(4)
#define BITBANG_REG7_EPLOCK_RESET_VALUE 			(0)

#define BITBANG_REG7_RESERVED1_REG 					(dev->reg7)	
#define BITBANG_REG7_RESERVED1_START_INDEX 			(31)
#define BITBANG_REG7_RESERVED1_FIELD_LENGTH 		(1)
#define BITBANG_REG7_RESERVED1_RESET_VALUE 			(1)

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//		Register 8
//		1000000000000000010111011101                                         		

#define BITBANG_REG8_ADDR_REG 						(dev->reg8)
#define BITBANG_REG8_ADDR_START_INDEX 				(0)
#define BITBANG_REG8_ADDR_FIELD_LENGTH 				(4)
#define BITBANG_REG8_ADDR_RESET_VALUE 				(8)

#define BITBANG_REG8_CALWORD_REG 					(dev->reg8)
#define BITBANG_REG8_CALWORD_START_INDEX 			(4)
#define BITBANG_REG8_CALWORD_FIELD_LENGTH 			(6)
#define BITBANG_REG8_CALWORD_RESET_VALUE 			(0)

#define BITBANG_REG8_PLLLOCKPIN_REG 				(dev->reg8)
#define BITBANG_REG8_PLLLOCKPIN_START_INDEX 		(10)
#define BITBANG_REG8_PLLLOCKPIN_FIELD_LENGTH		(1)
#define BITBANG_REG8_PLLLOCKPIN_RESET_VALUE 		(0)

#define BITBANG_REG8__SLEEP_REG 					(dev->reg8)	
#define BITBANG_REG8__SLEEP_START_INDEX 			(11)
#define BITBANG_REG8__SLEEP_FIELD_LENGTH 			(1)
#define BITBANG_REG8__SLEEP_RESET_VALUE 			(1)

#define BITBANG_REG8__SYNC_REG 						(dev->reg8)	
#define BITBANG_REG8__SYNC_START_INDEX 				(12)
#define BITBANG_REG8__SYNC_FIELD_LENGTH 			(1)
#define BITBANG_REG8__SYNC_RESET_VALUE 				(1)

#define BITBANG_REG8_RESERVED0_REG 					(dev->reg8)	
#define BITBANG_REG8_RESERVED0_START_INDEX 			(13)
#define BITBANG_REG8_RESERVED0_FIELD_LENGTH 		(1)
#define BITBANG_REG8_RESERVED0_RESET_VALUE 			(0)

#define BITBANG_REG8_VERSION_REG 					(dev->reg8)	
#define BITBANG_REG8_VERSION_START_INDEX 			(14)
#define BITBANG_REG8_VERSION_FIELD_LENGTH 			(3)
#define BITBANG_REG8_VERSION_RESET_VALUE 			(0)

#define BITBANG_REG8_RESERVED1_REG 					(dev->reg8)
#define BITBANG_REG8_RESERVED1_START_INDEX 			(17)
#define BITBANG_REG8_RESERVED1_FIELD_LENGTH 		(1)
#define BITBANG_REG8_RESERVED1_RESET_VALUE 			(0)

#define BITBANG_REG8_CALWORD_IN_REG 				(dev->reg8)	
#define BITBANG_REG8_CALWORD_IN_START_INDEX 		(18)
#define BITBANG_REG8_CALWORD_IN_FIELD_LENGTH 		(6)
#define BITBANG_REG8_CALWORD_IN_RESET_VALUE 		(0)

#define BITBANG_REG8_RESERVED2_REG 					(dev->reg8)	
#define BITBANG_REG8_RESERVED2_START_INDEX 			(24)
#define BITBANG_REG8_RESERVED2_FIELD_LENGTH 		(1)
#define BITBANG_REG8_RESERVED2_RESET_VALUE 			(0)

#define BITBANG_REG8_TITSTCFG_REG 					(dev->reg8)	
#define BITBANG_REG8_TITSTCFG_START_INDEX 			(25)
#define BITBANG_REG8_TITSTCFG_FIELD_LENGTH 			(4)
#define BITBANG_REG8_TITSTCFG_RESET_VALUE 			(0)				// TI test cfg ??? =

#define BITBANG_REG8_PRIACTIVITY_REG 				(dev->reg8)	
#define BITBANG_REG8_PRIACTIVITY_START_INDEX 		(29)
#define BITBANG_REG8_PRIACTIVITY_FIELD_LENGTH 		(1)
#define BITBANG_REG8_PRIACTIVITY_RESET_VALUE 		(0)

#define BITBANG_REG8_SECACTIVITY_REG 				(dev->reg8)	
#define BITBANG_REG8_SECACTIVITY_START_INDEX 		(30)
#define BITBANG_REG8_SECACTIVITY_FIELD_LENGTH 		(1)
#define BITBANG_REG8_SECACTIVITY_RESET_VALUE 		(0)

#define BITBANG_REG8_AUXACTIVITY_REG 				(dev->reg8)	
#define BITBANG_REG8_AUXACTIVITY_START_INDEX 		(31)
#define BITBANG_REG8_AUXACTIVITY_FIELD_LENGTH 		(1)
#define BITBANG_REG8_AUXACTIVITY_RESET_VALUE 		(1)






#endif
