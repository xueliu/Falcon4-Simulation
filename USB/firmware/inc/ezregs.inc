; This file contains essentially the same 
; information as EzRegs.h, except EzRegs.h also contains bit masks for individual bits 
; Do not modify one without modifying the other.
; 
; Register Assignments 3/18/99 TPM 
OUT7BUF         XDATA        7B40H
IN7BUF          XDATA        7B80H
OUT6BUF         XDATA        7BC0H
IN6BUF          XDATA        7C00H
OUT5BUF         XDATA        7C40H
IN5BUF          XDATA        7C80H
OUT4BUF         XDATA        7CC0H
IN4BUF          XDATA        7D00H
OUT3BUF         XDATA        7D40H
IN3BUF          XDATA        7D80H
OUT2BUF         XDATA        7DC0H
IN2BUF          XDATA        7E00H
OUT1BUF         XDATA        7E40H
IN1BUF          XDATA        7E80H
OUT0BUF         XDATA        7EC0H
IN0BUF          XDATA        7F00H
OUT8DATA        XDATA        7F60H
OUT9DATA        XDATA        7F61H
OUT10DATA       XDATA        7F62H
OUT11DATA       XDATA        7F63H
OUT12DATA       XDATA        7F64H
OUT13DATA       XDATA        7F65H
OUT14DATA       XDATA        7F66H
OUT15DATA       XDATA        7F67H
IN8DATA         XDATA        7F68H
IN9DATA         XDATA        7F69H
IN10DATA        XDATA        7F6AH
IN11DATA        XDATA        7F6BH
IN12DATA        XDATA        7F6CH
IN13DATA        XDATA        7F6DH
IN14DATA        XDATA        7F6EH
IN15DATA        XDATA        7F6FH
OUT8BCH         XDATA        7F70H
OUT8BCL         XDATA        7F71H
OUT9BCH         XDATA        7F72H
OUT9BCL         XDATA        7F73H
OUT10BCH        XDATA        7F74H
OUT10BCL        XDATA        7F75H
OUT11BCH        XDATA        7F76H
OUT11BCL        XDATA        7F77H
OUT12BCH        XDATA        7F78H
OUT12BCL        XDATA        7F79H
OUT13BCH        XDATA        7F7AH
OUT13BCL        XDATA        7F7BH
OUT14BCH        XDATA        7F7CH
OUT14BCL        XDATA        7F7DH
OUT15BCH        XDATA        7F7EH
OUT15BCL        XDATA        7F7FH
SPARE1          XDATA        7F90H
SPARE2          XDATA        7F91H
CPUCS           XDATA        7F92H
PORTACFG        XDATA        7F93H
PORTBCFG        XDATA        7F94H
PORTCCFG        XDATA        7F95H
OUTA            XDATA        7F96H
OUTB            XDATA        7F97H
OUTC            XDATA        7F98H
PINSA           XDATA        7F99H
PINSB           XDATA        7F9AH
PINSC           XDATA        7F9BH
OEA             XDATA        7F9CH
OEB             XDATA        7F9DH
OEC             XDATA        7F9EH
UART230         XDATA        7F9FH
ISOERR          XDATA        7FA0H
ISOCTL          XDATA        7FA1H
ZBCOUT          XDATA        7FA2H
ZBCIN           XDATA        7FA3H
SPARE4          XDATA        7FA4H
I2CS            XDATA        7FA5H
I2DAT           XDATA        7FA6H
SPARE5          XDATA        7FA7H
IVEC            XDATA        7FA8H
IN07IRQ         XDATA        7FA9H
OUT07IRQ        XDATA        7FAAH
USBIRQ          XDATA        7FABH
IN07IEN         XDATA        7FACH
OUT07IEN        XDATA        7FADH
USBIEN          XDATA        7FAEH
USBBAV          XDATA        7FAFH
AVADDRH         XDATA        7FB0H
AVADDRL         XDATA        7FB1H
BPADDRH         XDATA        7FB2H
BPADDRL         XDATA        7FB3H
EPIO            XDATA        7FB4H
;
EP0CS 	       XDATA        7FB4H
IN0BC          XDATA        7FB5H
IN1CS          XDATA        7FB6H
IN1BC          XDATA        7FB7H
IN2CS          XDATA        7FB8H
IN2BC          XDATA        7FB9H
IN3CS          XDATA        7FBAH
IN3BC          XDATA        7FBBH
IN4CS          XDATA        7FBCH
IN4BC          XDATA        7FBDH
IN5CS          XDATA        7FBEH
IN5BC          XDATA        7FBFH
IN6CS          XDATA        7FC0H
IN6BC          XDATA        7FC1H
IN7CS          XDATA        7FC2H
IN7BC          XDATA        7FC3H
;
OUT0BC         XDATA        7FC5H
OUT1CS         XDATA        7FC6H
OUT1BC         XDATA        7FC7H
OUT2CS         XDATA        7FC8H
OUT2BC         XDATA        7FC9H
OUT3CS         XDATA        7FCAH
OUT3BC         XDATA        7FCBH
OUT4CS         XDATA        7FCCH
OUT4BC         XDATA        7FCDH
OUT5CS         XDATA        7FCEH
OUT5BC         XDATA        7FCFH
OUT6CS         XDATA        7FD0H
OUT6BC         XDATA        7FD1H
OUT7CS         XDATA        7FD2H
OUT7BC         XDATA        7FD3H
;
SUDPTRH         XDATA        7FD4H
SUDPTRL         XDATA        7FD5H
USBCS           XDATA        7FD6H
TOGCTL          XDATA        7FD7H
USBFRAMEL       XDATA        7FD8H
USBFRAMEH       XDATA        7FD9H
SPARE6          XDATA        7FDAH
FNADDR          XDATA        7FDBH
SPARE7          XDATA        7FDCH
USBPAIR         XDATA        7FDDH
IN07VAL         XDATA        7FDEH
OUT07VAL        XDATA        7FDFH
INISOVAL        XDATA        7FE0H
OUTISOVAL       XDATA        7FE1H
FASTXFR         XDATA        7FE2H
AUTOPTRH        XDATA        7FE3H
AUTOPTRL        XDATA        7FE4H
AUTODATA        XDATA        7FE5H
SPARE8          XDATA        7FE6H
SPARE9          XDATA        7FE7H
SETUPDAT        XDATA        7FE8H
OUT8ADDR        XDATA        7FF0H
OUT9ADDR        XDATA        7FF1H
OUT10ADDR       XDATA        7FF2H
OUT11ADDR       XDATA        7FF3H
OUT12ADDR       XDATA        7FF4H
OUT13ADDR       XDATA        7FF5H
OUT14ADDR       XDATA        7FF6H
OUT15ADDR       XDATA        7FF7H
IN8ADDR         XDATA        7FF8H
IN9ADDR         XDATA        7FF9H
IN10ADDR        XDATA        7FFAH
IN11ADDR        XDATA        7FFBH
IN12ADDR        XDATA        7FFCH
IN13ADDR        XDATA        7FFDH
IN14ADDR        XDATA        7FFEH
IN15ADDR        XDATA        7FFFH

; SFR Special Function Registers
; BYTE and BIT Registers 3/18/99 TPM
SP      DATA 081H
DPL     DATA 082H
DPH     DATA 083H
DPL1    DATA 084H
DPH1    DATA 085H
DPS     DATA 086H
			;/*  DPS  */
			SEL   BIT 086H
PCON    DATA 087H	;/*  PCON  */
			;IDLE   BIT 087H+0H
			;STOP   BIT 087H+1H
			;GF0    BIT 087H+2H
			;GF1    BIT 087H+3H
			;SMOD0  BIT 087H+4H
TCON    DATA 088H
			;/*  TCON  */
			IT0    BIT 088H+0H
			IE0    BIT 088H+1H
			IT1    BIT 088H+2H
			IE1    BIT 088H+3H
			TR0    BIT 088H+4H
			TF0    BIT 088H+5H
			TR1    BIT 088H+6H
			TF1    BIT 088H+7H
TMOD    DATA 089H
			;/*  TMOD  */
			;M00    BIT 089H+0H
			;M10    BIT 089H+1H
			;CT0    BIT 089H+2H
			;GATE0  BIT 089H+3H
			;M01    BIT 089H+4H
			;M11    BIT 089H+5H
			;CT1    BIT 089H+6H
			;GATE1  BIT 089H+7H
TL0     DATA 08AH
TL1     DATA 08BH
TH0     DATA 08CH
TH1     DATA 08DH
CKCON   DATA 08EH
			;/*  CKCON  */
			;MD0    BIT 089H+0H
			;MD1    BIT 089H+1H
			;MD2    BIT 089H+2H
			;T0M    BIT 089H+3H
			;T1M    BIT 089H+4H
			;T2M    BIT 089H+5H
SPC_FNC DATA 08FH ;// Was WRS in Reg320
			;/*  CKCON  */
			;WRS    BIT 08FH+0H
EXIF    DATA 091H ;// EXIF Bit Values differ from Reg320
			;/*  EXIF  */
			;USBINT BIT 091H+4H
			;I2CINT BIT 091H+5H
			;IE4    BIT 091H+6H
			;IE5    BIT 091H+7H
MPAGE  DATA 092H
SCON0  DATA 098H
			;/*  SCON0  */
			RI    BIT 098H+0H
			TI    BIT 098H+1H
			RB8   BIT 098H+2H
			TB8   BIT 098H+3H
			REN   BIT 098H+4H
			SM2   BIT 098H+5H
			SM1   BIT 098H+6H
			SM0   BIT 098H+7H
SBUF0  DATA 099H
IE     DATA 0A8H
			;/*  IE  */  
			EX0   BIT 0A8H+0H
			ET0   BIT 0A8H+1H
			EX1   BIT 0A8H+2H
			ET1   BIT 0A8H+3H
			ES0   BIT 0A8H+4H
			ET2   BIT 0A8H+5H
			ES1   BIT 0A8H+6H
			EA    BIT 0A8H+7H
IP     DATA 0B8H
			;/*  IP  */
			PX0   BIT 0B8H+0H
			PT0   BIT 0B8H+1H
			PX1   BIT 0B8H+2H
			PT1   BIT 0B8H+3H
			PS0   BIT 0B8H+4H
			PT2   BIT 0B8H+5H
			PS1   BIT 0B8H+6H
SCON1  DATA 0C0H
			;/*  SCON1  */
			RI1   BIT 0C0H+0H	
			TI1   BIT 0C0H+1H	
			RB81  BIT 0C0H+2H
			TB81  BIT 0C0H+3H
			REN1  BIT 0C0H+4H
			SM21  BIT 0C0H+5H
			SM11  BIT 0C0H+6H
			SM01  BIT 0C0H+7H
SBUF1  DATA 0C1H
T2CON  DATA 0C8H
			;/*  T2CON  */
			CP_RL2 BIT 0C8H+0H
			C_T2  BIT 0C8H+1H
			TR2   BIT 0C8H+2H
			EXEN2 BIT 0C8H+3H
			TCLK  BIT 0C8H+4H
			RCLK  BIT 0C8H+5H
			EXF2  BIT 0C8H+6H
			TF2   BIT 0C8H+7H	
RCAP2L DATA 0CAH
RCAP2H DATA 0CBH
TL2    DATA 0CCH
TH2    DATA 0CDH
PSW    DATA 0D0H
			;/*  PSW  */
			P     BIT 0D0H+0H
			FL    BIT 0D0H+1H
			OV    BIT 0D0H+2H
			RS0   BIT 0D0H+3H
			RS1   BIT 0D0H+4H
			F0    BIT 0D0H+5H
			AC    BIT 0D0H+6H
			CY    BIT 0D0H+7H
EICON  DATA 0D8H ;// Was WDCON in DS80C320
			;/*  EICON  */
			INT6 	BIT 0D8H+3H
			RESI 	BIT 0D8H+4H	
			ERESI  	BIT 0D8H+5H	
			SMOD1   BIT 0D8H+7H
ACC    DATA 0E0H
EIE    DATA 0E8H ;// EIE Bit Values differ from Reg320
                        ;/*  EIE  */
			EUSB    BIT 0E8H+0H	
			EI2C    BIT 0E8H+1H	
			EIEX4   BIT 0E8H+2H
			EIEX5   BIT 0E8H+3H
			EIEX6   BIT 0E8H+4H	
B      DATA 0F0H
EIP    DATA 0F8H ;// EIP Bit Values differ from Reg320
                        ;/*  EIP  */
			PUSB    BIT 0F8H+0H	
			PI2C    BIT 0F8H+1H	
			EIPX4   BIT 0F8H+2H
			EIPX5   BIT 0F8H+3H
			EIPX6   BIT 0F8H+4H	

