`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:41:30 06/02/2014 
// Design Name: 
// Module Name:    USB_68013A_module 
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
module USB_68013A_module(
	//----------------------
	// Input Ports
	//----------------------
	usb_write_event_input,
	usb_usb_data_input,
	
	//----------------------
	// Output Ports
	//----------------------	
	usb_data_output, 			// {USB_FD_15to8, USB_Flash_DQ}
	usb_read_output_n,					// slave-FIFO read (USB_SLRD_L)
	usb_write_output_n,			// slave-FIFO write (USB_SLWR_L)
	usb_output_enable_n,		// slave-FIFO output enable (USB_SLOE_L)
	usb_FifoAddr,		// slave-FIFO address select (USB_FIFOADDR[1:0])
	output				oUsbChipSelectN,	// slave-FIFO enable (USB_SLCS_L)
    );
		output	[15	: 0]	oUsbData, 			// {USB_FD_15to8, USB_Flash_DQ}
	
	output				oUsbReadN,			// slave-FIFO read (USB_SLRD_L)
	output				oUsbWriteN,			// slave-FIFO write (USB_SLWR_L)
	
	output				oUsbOutputEnableN,	// slave-FIFO output enable (USB_SLOE_L)
	output		[1:0]	oUsbFifoAddr,		// slave-FIFO address select (USB_FIFOADDR[1:0])
	output				oUsbChipSelectN,	// slave-FIFO enable (USB_SLCS_L)

endmodule
