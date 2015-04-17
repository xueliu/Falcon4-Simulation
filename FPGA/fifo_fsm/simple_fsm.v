/* 
(C) OOMusou 2011 http://oomusou.cnblogs.com

Filename    : fifo_fsm.v
Synthesizer : ISE 14.5
Description : 3 always block for moore fsm (BEST)
Release     : Feb.27,2014 v0.1
*/

module FIFO_FSM (
  iClk,
  iRst_N,
  iEmpty,
  iFull,
  oFIFO_WR_EN
);

input iClk;
input iRst_N;
input iEmpty;
input iFull;
output oFIFO_WR_EN;


parameter EMPTY 	= 2'b00;
parameter TRANS   = 2'b01;
parameter FULL		= 2'b10;

reg [1:0] curr_state;
reg [1:0] next_state;
reg oFIFO_WR_EN;

// state reg
always@(posedge iClk or negedge iRst_N)
  if (~iRst_N) curr_state <= EMPTY;
  else        	curr_state <= next_state;
    
// next state logic    
always@(*)
  case (curr_state)
    EMPTY   : if 			(iFull) 		next_state = FULL;
              else if	(iEmpty)   	next_state = TRANS;
				  else 						next_state = EMPTY;
    TRANS   : if 			(iFull) 		next_state = FULL;
				  else if   (iEmpty)		next_state = TRANS;
              else     					next_state = TRANS;
    FULL		: if 			(iFull) 		next_state = FULL;
              else if   (iEmpty)		next_state = EMPTY;
              else     					next_state = FULL;				  
    default : next_state = EMPTY;
  endcase    

// output logic
always@(*)
  case (curr_state)
    EMPTY   : oFIFO_WR_EN = 1'b0;
    TRANS   : oFIFO_WR_EN = 1'b1;
    FULL   	: oFIFO_WR_EN = 1'b0;
    default : oFIFO_WR_EN = 1'b0;
  endcase
  
endmodule