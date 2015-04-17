`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:31:15 05/27/2014
// Design Name:   ADC_ADS62P49_module
// Module Name:   C:/Users/xue liu/Desktop/spectrum_sensing/falcon4/module/ADC_ADS62P49_module/ADC_ADS62P49_testbench.v
// Project Name:  ADC_ADS62P49_module
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: ADC_ADS62P49_module
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module ADC_ADS62P49_testbench;

	// Inputs
	reg adc_clk_p_src;
	reg adc_clk_m_src;
	reg [6:0] adc_da_p;
	reg [6:0] adc_da_m;
	reg [6:0] adc_db_p;
	reg [6:0] adc_db_m;

	// Outputs
	wire adc_clk_drv;
	wire adc_clk_drv_n;
	wire [15:0] adc_da_output;
	wire [15:0] adc_db_output;
	
	// Internal signals
	reg [13:0] counter;
	
	reg clk;

	// Instantiate the Unit Under Test (UUT)
	ADC_ADS62P49_module uut (
		.adc_clk_p_src(adc_clk_p_src), 
		.adc_clk_m_src(adc_clk_m_src), 
		.adc_da_p(adc_da_p), 
		.adc_da_m(adc_da_m), 
		.adc_db_p(adc_db_p), 
		.adc_db_m(adc_db_m), 
		.adc_clk_drv(adc_clk_drv), 
		.adc_clk_drv_n(adc_clk_drv_n), 
		.adc_da_output(adc_da_output), 
		.adc_db_output(adc_db_output)
	);

	initial begin
		// Initialize Inputs
		adc_clk_p_src = 0;
		adc_clk_m_src = 1;
		adc_da_p = 7'b000_0000;
		adc_da_m = 7'b111_1111;
		adc_db_p = 7'b000_0000;
		adc_db_m = 7'b111_1111;
		clk = 0;
		counter = 14'd0;

		// Wait 100 ns for global reset to finish
		#20;
        
		// Add stimulus here
		forever #10 
			begin
				clk 				<= ~clk;
				// a litte delay to simulate the delay between CLKM and CLKOUTM, datasheet p.12
				#1 adc_clk_m_src <= ~adc_clk_m_src;
				adc_clk_p_src 	<= ~adc_clk_p_src;
			end

	end
	

	always @ ( posedge clk )
		begin
			counter = counter + 1'b1;
		end
		
	always @ ( posedge clk )
		begin
			adc_da_p[0]		<= counter[0];	adc_da_m[0]	<= ~counter[0];
			adc_da_p[1] 	<= counter[2]; 	adc_da_m[1]	<= ~counter[2];
			adc_da_p[2] 	<= counter[4]; 	adc_da_m[2]	<= ~counter[4];
			adc_da_p[3] 	<= counter[6]; 	adc_da_m[3]	<= ~counter[6];
			adc_da_p[4] 	<= counter[8]; 	adc_da_m[4]	<= ~counter[8];
			adc_da_p[5]  	<= counter[10]; adc_da_m[5]	<= ~counter[10];
			adc_da_p[6]  	<= counter[12];	adc_da_m[6]	<= ~counter[12];
		end
		
	always @ ( negedge clk )
		begin
			adc_da_p[0]		<= counter[1];	adc_da_m[0]	<= ~counter[1];
			adc_da_p[1] 	<= counter[3]; 	adc_da_m[1]	<= ~counter[3];
			adc_da_p[2] 	<= counter[5]; 	adc_da_m[2]	<= ~counter[5];
			adc_da_p[3] 	<= counter[7]; 	adc_da_m[3]	<= ~counter[7];
			adc_da_p[4] 	<= counter[9]; 	adc_da_m[4]	<= ~counter[9];
			adc_da_p[5]  	<= counter[11]; adc_da_m[5]	<= ~counter[11];
			adc_da_p[6]  	<= counter[13];	adc_da_m[6]	<= ~counter[13];
		end		

	always @ ( posedge clk )
		begin
			adc_db_p[0]		<= counter[0];	adc_db_m[0]	<= ~counter[0];
			adc_db_p[1] 	<= counter[2]; 	adc_db_m[1]	<= ~counter[2];
			adc_db_p[2] 	<= counter[4]; 	adc_db_m[2]	<= ~counter[4];
			adc_db_p[3] 	<= counter[6]; 	adc_db_m[3]	<= ~counter[6];
			adc_db_p[4] 	<= counter[8]; 	adc_db_m[4]	<= ~counter[8];
			adc_db_p[5]  	<= counter[10]; adc_db_m[5]	<= ~counter[10];
			adc_db_p[6]  	<= counter[12];	adc_db_m[6]	<= ~counter[12];
		end
		
	always @ ( negedge clk )
		begin
			adc_db_p[0]		<= counter[1];	adc_db_m[0]	<= ~counter[1];
			adc_db_p[1] 	<= counter[3]; 	adc_db_m[1]	<= ~counter[3];
			adc_db_p[2] 	<= counter[5]; 	adc_db_m[2]	<= ~counter[5];
			adc_db_p[3] 	<= counter[7]; 	adc_db_m[3]	<= ~counter[7];
			adc_db_p[4] 	<= counter[9]; 	adc_db_m[4]	<= ~counter[9];
			adc_db_p[5]  	<= counter[11]; adc_db_m[5]	<= ~counter[11];
			adc_db_p[6]  	<= counter[13];	adc_db_m[6]	<= ~counter[13];
		end
				
endmodule

