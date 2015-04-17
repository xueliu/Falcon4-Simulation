`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:18:52 05/26/2014 
// Design Name: 
// Module Name:    ADC_ADS62P49_module 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module ADC_ADS62P49_module (
	//----------------------
	// Input Ports
	//----------------------	
	adc_clk_p_src,
	adc_clk_m_src,
	adc_da_p,
	adc_da_m,
	adc_db_p,
	adc_db_m,
	
	//----------------------
	// Output Ports
	//----------------------	
	adc_clk_drv,
	adc_clk_drv_n,
	adc_da_output,
	adc_db_output
    );
	
	//----------------------
	// Parameters
	//----------------------	
	
	//----------------------
	// Input Ports
	//----------------------
	input				adc_clk_p_src;
	input				adc_clk_m_src;
	input	[6	:	0]	adc_da_p;
	input	[6	:	0]	adc_da_m;
	input	[6	:	0]	adc_db_p;
	input	[6	:	0]	adc_db_m;	
	
	//----------------------
	// Output Ports
	//----------------------
	output				adc_clk_drv;
	output				adc_clk_drv_n;
	output	[15	: 	0]	adc_da_output;
	output	[15	: 	0] 	adc_db_output;
	
	//----------------------
	// Internal Signals
	//----------------------
	reg		[13	: 	0]	adc_da_ff_reg;
	reg		[13	: 	0] 	adc_db_ff_reg;
	reg		[15	: 	0]	adc_da_2nd_ff_reg;
	reg		[15	: 	0] 	adc_db_2nd_ff_reg;		
	wire 	[6	: 	0]	adc_da_nxt;
//	wire 	[6	: 	0]	adc_da_nxt_n;
	wire 	[6	: 	0]	adc_db_nxt;
//	wire 	[6	: 	0]	adc_db_nxt_n;
	
	//----------------------
	// Instantiate Modules
	//----------------------
	// ADC ADS62P49 differential clock inputs
	IBUFGDS_DIFF_OUT #(
		.DIFF_TERM("TRUE"), 		// Differential termination
		.IBUF_LOW_PWR("FALSE"),
		.IOSTANDARD("LVDS_25") 		// Specify the input I/O standard
	) IBUFGDS_INST0 (
		.O (adc_clk_drv), 			// ADC clock buffer ouput
		.OB (adc_clk_drv_n),		// ADC clock buffer inverse output
		.I (adc_clk_p_src), 	// Diff input, p-channel
		.IB(adc_clk_m_src) 		// Diff input, n-channel
	);
	
	// ADC ADS62P49 differential data inputs
	// 3x reversing polarity in ucf, data input and data output
	IBUFDS_DIFF_OUT #(
		.DIFF_TERM("TRUE"), 		// Differential termination
		.IBUF_LOW_PWR("FALSE"),
		.IOSTANDARD("LVDS_25") 		// Specify the input I/O standard
	) IBUFDS_INST1 [6:0] (
		.O (), 			// ADC channel A buffer ouput
		.OB(adc_da_nxt),						// ADC channel A buffer inverse ouput
		.I (adc_da_p), 		// diff input, p-channel
		.IB(adc_da_m) 			// diff input, n-channel
	);
	
	// 3x reversing polarity in ucf, data input and data output
	IBUFDS_DIFF_OUT #(
		.DIFF_TERM("TRUE"), 		// Differential termination
		.IBUF_LOW_PWR("FALSE"),
		.IOSTANDARD("LVDS_25") 		// Specify the input I/O standard
	) IBUFDS_INST2 [6:0] (
		.O (), 			// ADC channel B buffer ouput
		.OB(adc_db_nxt),						// ADC channel B buffer inverse ouput
		.I (adc_db_p),			// diff input, p-channel
		.IB(adc_db_m) 			// diff input, n-channel
	);
	
	//----------------------
	// Always Blocks
	//----------------------	
	always @ (posedge adc_clk_drv)		
		begin 
			adc_da_ff_reg[0]	<= adc_da_nxt[0];
			adc_da_ff_reg[2] 	<= adc_da_nxt[1];
			adc_da_ff_reg[4] 	<= adc_da_nxt[2];
			adc_da_ff_reg[6] 	<= adc_da_nxt[3];
			adc_da_ff_reg[8] 	<= adc_da_nxt[4];
			adc_da_ff_reg[10]  	<= adc_da_nxt[5];
			adc_da_ff_reg[12]  	<= adc_da_nxt[6];
			
			adc_db_ff_reg[0] 	<= adc_db_nxt[0];
			adc_db_ff_reg[2] 	<= adc_db_nxt[1];
			adc_db_ff_reg[4] 	<= adc_db_nxt[2];
			adc_db_ff_reg[6] 	<= adc_db_nxt[3];
			adc_db_ff_reg[8] 	<= adc_db_nxt[4];
			adc_db_ff_reg[10]  	<= adc_db_nxt[5];
			adc_db_ff_reg[12]  	<= adc_db_nxt[6];
		end
	
	always @ (negedge adc_clk_drv)
		begin
			adc_da_ff_reg[1] 	<= adc_da_nxt[0];
			adc_da_ff_reg[3] 	<= adc_da_nxt[1];
			adc_da_ff_reg[5] 	<= adc_da_nxt[2];
			adc_da_ff_reg[7] 	<= adc_da_nxt[3];
			adc_da_ff_reg[9] 	<= adc_da_nxt[4];
			adc_da_ff_reg[11]  	<= adc_da_nxt[5];
			adc_da_ff_reg[13]  	<= adc_da_nxt[6];
			
			adc_db_ff_reg[1] 	<= adc_db_nxt[0];
			adc_db_ff_reg[3] 	<= adc_db_nxt[1];
			adc_db_ff_reg[5] 	<= adc_db_nxt[2];
			adc_db_ff_reg[7] 	<= adc_db_nxt[3];
			adc_db_ff_reg[9] 	<= adc_db_nxt[4];
			adc_db_ff_reg[11]  	<= adc_db_nxt[5];
			adc_db_ff_reg[13]  	<= adc_db_nxt[6];
		end
		
	always @ (posedge adc_clk_drv)		
		begin
			adc_da_2nd_ff_reg[15:0] <= {adc_da_ff_reg[13], adc_da_ff_reg[13], adc_da_ff_reg[13:0]};	// Channel A 2's complement output
			adc_db_2nd_ff_reg[15:0] <= {adc_db_ff_reg[13], adc_db_ff_reg[13], adc_db_ff_reg[13:0]};	// Channel B 2's complement output		
		end
	
	//----------------------
	// Assignment Blocks
	//----------------------		
	assign adc_da_output = adc_da_2nd_ff_reg;
	assign adc_db_output = adc_db_2nd_ff_reg;
endmodule
