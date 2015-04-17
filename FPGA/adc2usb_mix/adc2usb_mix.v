`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:56:50 06/03/2014 
// Design Name: 
// Module Name:    adc2usb_mix 
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
module adc2usb_mix(
	//----------------------
	// Input Ports
	//----------------------
	EXP2_ADS_CLKOUT,
	EXP2_ADS_CLKOUTM,
	EXP2_ADS_DA_P,
	EXP2_ADS_DA_M,
//	EXP2_ADS_DB_P,
//	EXP2_ADS_DB_M, 
	
	USB_FIFO_FLAG_A_LVL,
	USB_FIFO_FLAG_B_FULL_L,
	USB_FIFO_FLAG_C_EMPTY_L,
	USB_IFCLK,
	RESET_N,
	
	iDipSwitchN,
	
	//----------------------
	// Output Ports
	//----------------------
	oLed,
//	input	[2	: 0]	iPushButtonN,
//	input	[7	: 0]	iDipSwitchN,
	ADC_DATA_CLOCK,
	USB_DATA_BUS,
	USB_FIFO_SLRD_L,
	USB_FIFO_SLWR_L,
	USB_FIFO_SLOE_L,
	USB_FIFO_ADDR,
	USB_SLCS_L,
	USB_RST_L
    );

	//----------------------
	// Parameters
	//----------------------	
	parameter FIFO_ADDRESS_EP2			= 2'b00; // EP2
	
	//----------------------
	// Input Ports
	//----------------------
	input				EXP2_ADS_CLKOUT;
	input				EXP2_ADS_CLKOUTM;
	input	[6	: 0]	EXP2_ADS_DA_P;
	input	[6	: 0]	EXP2_ADS_DA_M;
//	input	[6	: 0]	EXP2_ADS_DB_P;
//	input	[6	: 0]	EXP2_ADS_DB_M;
	
	input				USB_FIFO_FLAG_A_LVL;
	input				USB_FIFO_FLAG_B_FULL_L;
	input				USB_FIFO_FLAG_C_EMPTY_L;
	input				USB_IFCLK;
	input				RESET_N;
	input	[7	: 0]	iDipSwitchN;
	//----------------------
	// Output Ports
	//----------------------
	output	[7	: 0]	oLed;
//	input	[2	: 0]	iPushButtonN,

	output	[15	: 0]	USB_DATA_BUS;
	output				USB_FIFO_SLRD_L;
	output				USB_FIFO_SLWR_L;
	output				USB_FIFO_SLOE_L;
	output	[1	: 0]	USB_FIFO_ADDR;
	output				USB_SLCS_L;
	output				USB_RST_L;
	output 				ADC_DATA_CLOCK;
	
	//----------------------
	// Internal Signals
	//----------------------
	wire 				usb_write_event;
	wire 				adc_clk_drv;
	wire 	[15	: 0]	adc_da_output;
	wire 				fifo_almost_full_signal;
	wire				fifo_almost_empty_signal;
	wire				fifo_re_signal;
	wire				fifo_we_signal;
	wire 	[15 : 0]    fifo_data_output;
	reg 				fifo_output_valid_ff;
	//----------------------
	// Instantiate Modules
	//----------------------
	USB_68013A_control usb_control (
		.usb_write_event(usb_write_event),
//		.usb_data_input(fifo_data_output), 
		.usb_clkout_drv(USB_IFCLK), 
		.usb_fifo_flag_b_full_n(USB_FIFO_FLAG_B_FULL_L), 
		.usb_fifo_addr_input(FIFO_ADDRESS_EP2), 
		.usb_slcs_n_input(1'b0),  // any value is OK
		.usb_reset_n_input(RESET_N), 
//		.usb_data_output(USB_DATA_BUS), 
		.usb_fifo_slrd_n(USB_FIFO_SLRD_L), 
		.usb_fifo_slwr_n(USB_FIFO_SLWR_L), 
		.usb_fifo_sloe_n(USB_FIFO_SLOE_L), 
		.usb_fifo_addr(USB_FIFO_ADDR), 
		.usb_slcs_n(USB_SLCS_L),
		.usb_reset_n_output(USB_RST_L)
    );
	
	
	ADC_ADS62P49_module adc_module (
		.adc_clk_p_src(EXP2_ADS_CLKOUT), 
		.adc_clk_m_src(EXP2_ADS_CLKOUTM), 
		.adc_da_p(EXP2_ADS_DA_M), 
		.adc_da_m(EXP2_ADS_DA_P), 
		.adc_db_p(EXP2_ADS_DA_M), 
		.adc_db_m(EXP2_ADS_DA_P), 
		.adc_clk_drv(adc_clk_drv), 
		.adc_clk_drv_n(), 
		.adc_da_output(adc_da_output), 
		.adc_db_output()
    );
	
	FIFO_FSM usb_fifo_control (
		.iClk(adc_clk_drv), 
		.iRst_N(RESET_N), 
		.iEmpty(fifo_almost_empty_signal), 
		.iFull(fifo_almost_full_signal), 
		.oFIFO_WR_EN(fifo_we_signal)
    );
	
	usb_fifo_16x16 fifo_module (
	  .rst(!RESET_N), // input rst
	  .wr_clk(adc_clk_drv), // input wr_clk
	  .din(adc_da_output), // input [15 : 0] din	  
	  .wr_en(fifo_we_signal), // input wr_en	
	  
	  .rd_clk(USB_IFCLK), // input rd_clk	  
	  .dout(fifo_data_output), // output [15 : 0] dout
	  .rd_en(fifo_re_signal), // input rd_en

	  .full(), // output full
	  .almost_full(fifo_almost_full_signal), // output almost_full
	  .empty(), // output empty
	  .almost_empty(fifo_almost_empty_signal) // output almost_empty
	);

	//----------------------
	// Assignment Blocks
	//----------------------
	
	assign fifo_re_signal 		= USB_FIFO_FLAG_B_FULL_L & (!fifo_almost_empty_signal);
	assign usb_write_event		= fifo_output_valid_ff;
	assign USB_DATA_BUS 		= fifo_data_output;
	assign ADC_DATA_CLOCK       = adc_clk_drv;  // output adc data clock to X3 port in Falcon4 board for testing
	
	assign oLed[0]				= fifo_almost_empty_signal;
	assign oLed[1]				= fifo_almost_full_signal;		
	assign oLed[2]				= usb_write_event;	
	assign oLed[3]				= fifo_re_signal;	
	assign oLed[4]				= 1'b0;
	assign oLed[5]				= !USB_FIFO_FLAG_C_EMPTY_L;
	assign oLed[6]				= !USB_FIFO_FLAG_B_FULL_L;
	assign oLed[7]				= !RESET_N;
	
	//----------------------
	// Always Blocks
	//----------------------
	always @ (posedge USB_IFCLK)
		begin
			fifo_output_valid_ff	<= fifo_re_signal;
		end
endmodule
