`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:41:30 06/02/2014 
// Design Name: 
// Module Name:    USB_68013A_control
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
module USB_68013A_control(
	//----------------------
	// Input Ports
	//----------------------
	usb_write_event,
//	usb_data_input,
	usb_clkout_drv,
//	usb_clk_select,
//	usb_fifo_flag_a_lvl,
	usb_fifo_flag_b_full_n,
//	usb_fifo_flag_c_empty_n,
	usb_fifo_addr_input,
	usb_slcs_n_input,
	usb_reset_n_input,
	
	//----------------------
	// Output Ports
	//----------------------
//	usb_ifclk_src,
//	usb_data_output, 			// {USB_FD_15to8, USB_Flash_DQ}
	usb_fifo_slrd_n,			// slave-FIFO read (USB_SLRD_L)
	usb_fifo_slwr_n,			// slave-FIFO write (USB_SLWR_L)
	usb_fifo_sloe_n,		// slave-FIFO output enable (USB_SLOE_L)
	usb_fifo_addr,		// slave-FIFO address select (USB_FIFOADDR[1:0])
	usb_slcs_n,			// slave-FIFO enable (USB_SLCS_L)
//	usb_pkt_end_n 		// slave-FIFO packet end
	usb_reset_n_output
    );
	
	//----------------------
	// Parameters
	//----------------------	
	parameter DEFAULT_FIFO_ADDRESS			= 2'b00; // EP2
	
	//----------------------
	// Input Ports
	//----------------------
	input				usb_write_event;
//	input	[15	:	0]	usb_data_input;
	input 				usb_clkout_drv;		// IFCLK
//	input 				usb_clk_select;
//	input 				usb_fifo_flag_a_lvl;
	input 				usb_fifo_flag_b_full_n;
//	input 				usb_fifo_flag_c_empty_n;
	input 	[1	:	0]	usb_fifo_addr_input;
	input 				usb_slcs_n_input;
	input 				usb_reset_n_input;
	
	//----------------------
	// Output Ports
	//----------------------
//	output 				usb_ifclk_src;		// IFCLK, the clock for the synchronous interface with 48MHz and is generated by the FX2LP
//	output	[15	: 	0]	usb_data_output;	// {USB_FD_15to8, USB_Flash_DQ}
	output				usb_fifo_slrd_n;	// slave-FIFO read (USB_SLRD_L)
	output				usb_fifo_slwr_n;	// slave-FIFO write (USB_SLWR_L)
	output				usb_fifo_sloe_n;	// slave-FIFO output enable (USB_SLOE_L)
	output	[1	:	0]	usb_fifo_addr;		// slave-FIFO address select (USB_FIFOADDR[1:0])
	output				usb_slcs_n;			// slave-FIFO enable (USB_SLCS_L)
//	output 				usb_pkt_end_n;		// slave-FIFO packet end
	output 				usb_reset_n_output;
	//----------------------
	// Internal Signals
	//----------------------
//	reg 	[15	: 	0]	usb_data_ff;
//	wire 	[15	: 	0]  usb_data_nxt;
	//----------------------
	// Instantiate Modules
	//----------------------
	
	//----------------------
	// Always Blocks
	//----------------------
//	always@(posedge usb_clkout_drv or negedge usb_reset_n_input) begin
//		if(usb_reset_n_input == 1'b0) begin
//			usb_data_ff	<= 15'b000_0000_0000;
//		end else if (usb_fifo_slwr_n == 1'b0) begin
//			usb_data_ff <= usb_data_nxt;
//		end
//	end
	
	//----------------------
	// Assignment Blocks
	//----------------------
//	assign usb_data_output 		= usb_data_ff;
//	assign usb_data_nxt 		= usb_data_input;
	assign usb_fifo_slwr_n		= !usb_write_event;
//	assign usb_data_output 		= usb_data_input;
	assign usb_slcs_n 			= usb_slcs_n_input;
	assign usb_fifo_addr 		= usb_fifo_addr_input;
	assign usb_fifo_sloe_n 		= 1'b1;
	assign usb_fifo_slrd_n  	= 1'b1;
//	assign usb_fifo_slwr_n 		= usb_fifo_flag_b_full_n == 1'b0 ?  1'b1 : 1'b0;
	assign usb_reset_n_output 	= usb_reset_n_input;
endmodule
