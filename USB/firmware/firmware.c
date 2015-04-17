#pragma NOIV               // Do not generate interrupt vectors
//////////////////////////////////////////////////////////////////////////////////
// 
// Revision: 1.3 $
// Date: 
// Author: Xue Liu
// For USB chip test
// Firmware for Cypress USB controller
//////////////////////////////////////////////////////////////////////////////////
#include "fx2.h"
#include "fx2regs.h"
#include "fx2sdly.h"            // SYNCDELAY macro

extern BOOL GotSUD;             // Received setup data flag
extern BOOL Sleep;
extern BOOL Rwuen;
extern BOOL Selfpwr;

BYTE Configuration;             // Current configuration
BYTE AlternateSetting;          // Alternate settings

BOOL done_frm_fpga = 0;

#define VR_NAKALL_ON    0xD0
#define VR_NAKALL_OFF   0xD1

//-----------------------------------------------------------------------------
// Task Dispatcher hooks
//   The following hooks are called by the task dispatcher.
//-----------------------------------------------------------------------------

#define USE_EXTERNAL_CLOCK 0

void TD_Init(void)             // Called once at startup
{

	// Registers which require a synchronization delay, see section 15.14
	// FIFORESET        FIFOPINPOLAR
	// INPKTEND         OUTPKTEND
	// EPxBCH:L         REVCTL
	// GPIFTCB3         GPIFTCB2
	// GPIFTCB1         GPIFTCB0
	// EPxFIFOPFH:L     EPxAUTOINLENH:L
	// EPxFIFOCFG       EPxGPIFFLGSEL
	// PINFLAGSxx       EPxFIFOIRQ
	// EPxFIFOIE        GPIFIRQ
	// GPIFIE           GPIFADRH:L
	// UDMACRCH:L       EPxGPIFTRIG
	// GPIFTRIG
  
	// Note: The pre-REVE EPxGPIFTCH/L register are affected, as well...
	//      ...these have been replaced by GPIFTC[B3:B0] registers

	// set the CPU clock to 48MHz
 	CPUCS = ((CPUCS & ~bmCLKSPD) | bmCLKSPD1 | bmCLKOE) ;

	// set the slave FIFO interface to 48MHz
	// IFCLK pin is driven by the internal 48Mhz clock wth inverted polarity
#if USE_EXTERNAL_CLOCK == 1
	// 0111 0011 0x73 for external clock (original)
	// 0100 0011 0x43 for external clock
	IFCONFIG = 0x03; // 0000 0011   
#else
	// 1111 0011 0xF3 for internal clock (original)
	IFCONFIG = 0xF3; //   
#endif

                    // Bit      Value   Register    Function  
                    // bit.7    1       IFCLKSRC    0  : External clock on the IFCLK pin  
                    //                              1  : Internal 30 or 48MHz (default)  
                    // bit.6    1       3048MHZ     0  : 30M Hz  
                    //                              1  : 48M Hz  
                    // bit.5    1       IFCLKOE     0  : Tri-state  
                    //                              1  : Drive  
                    // bit.4    1       IFCLKOL     0  : clock not inverted  
                    //                              1  : clock is inverted  
                    // bit.3    0       ASYNC       0  : FIFO/GPIF operate synchronously  
                    //                              1  : FIFO/GPIF operate asynchronously  
                    // bit.2    0       GSTATE      1  : GPIF states, Port E Alternate Functions.  
                    //                                   PE0 GSTATE[0]  
                    //                                   PE1 GSTATE[1]  
                    //                                   PE2 GSTATE[2]  
                    // bit.1:0  11      IFCFG[1:0]  00 : Ports  
                    //                              01 : Reserved  
                    //                              10 : GPIF Interface (internal master)  
                    //                              11 : Slave FIFO Interface(external mast

	SYNCDELAY;
	REVCTL = 0x03;	// see TRM p.131
	SYNCDELAY;

  // default: all endpoints have their VALID bit set
  // default: TYPE1 = 1 and TYPE0 = 0 --> BULK  
  // default: EP2 and EP4 DIR bits are 0 (OUT direction)
  // default: EP6 and EP8 DIR bits are 1 (IN direction)
  // default: EP2, EP4, EP6, and EP8 are double buffered

	// configuration of endpoints
	// endpoint 1
 	EP1OUTCFG 	= 0xA0;
	EP1INCFG 	= 0xA0;
	SYNCDELAY;                    // see TRM section 15.14

	// endpoint 2
	EP2CFG = 0xEA;  // 1110 1010, (Size = 1024, buf = Quad (Buf x4), BULK)  
                    // Bit      Value   Register    Function  
                    // bit.7    1       VALID       0  : Does not respond to any USB traffic.  
                    //                              1  : Activate an endpoint(default)  
                    // bit.6    1       DIR         0  : OUT  
                    //                              1  : IN  
                    // bit.5:4  10      TYPE[1:0]   0  : Invalid  
                    //                              01 : ISOCHRONOUS  
                    //                              10 : BULK (default)  
                    //                              11 : INTERRUPT  
                    // bit.3    1       SIZE        0  : 512 bytes  
                    //                              1  : 1024 bytes  
                    // bit.2    0       reserved  
                    // bit.1:0  10      BUF[1:0]    00 : Quad  
                    //                              01 : Invalid  
                    //                              10 : Double  
                    //                              11 : Triple 
	SYNCDELAY;                    

	// endpoint 4 (disabled)
	EP4CFG = 0x62;
	SYNCDELAY;                    

	// endpoint 6
	EP6CFG = 0xAA;  // 1010 1010, (Size = 1024, buf = Quad (Buf x4), BULK)  
                    // Bit      Value   Register    Function  
                    // bit.7    1       VALID       0  : Does not respond to any USB traffic.  
                    //                              1  : Activate an endpoint(default)  
                    // bit.6    0       DIR         0  : OUT  
                    //                              1  : IN  
                    // bit.5:4  10      TYPE[1:0]   0  : Invalid  
                    //                              01 : ISOCHRONOUS  
                    //                              10 : BULK (default)  
                    //                              11 : INTERRUPT  
                    // bit.3    1       SIZE        0  : 512 bytes  
                    //                              1  : 1024 bytes  
                    // bit.2    0       reserved  
                    // bit.1:0  10      BUF[1:0]    00 : Quad  
                    //                              01 : Invalid  
                    //                              10 : Double  
                    //                              11 : Triple 
	SYNCDELAY;                    

	// endpoint 8 (disabled)
	EP8CFG = 0x62;
	SYNCDELAY;

	// reset all FIFOs
	FIFORESET = 0x80;
	SYNCDELAY;

	FIFORESET = 0x02;
	SYNCDELAY;

	FIFORESET = 0x04;
	SYNCDELAY;

	FIFORESET = 0x06;
	SYNCDELAY;

	FIFORESET = 0x08;
	SYNCDELAY;

	FIFORESET = 0x00;
	SYNCDELAY;

	// configure FIFOs for AUTOIN-mode
	EP2FIFOCFG = 0x4D;
		// bit 6:	INFM1		== 0x01: assert full flag one sample earlier than when the full condition occurs
		// bit 5:	OEP1		== 0x00
		// bit 4:	AUTOOUT		== 0x00
		// bit 3:	AUTOIN		== 0x01: incoming data is automatically packetized and transmitted, without CPU intervention
		// bit 2:	ZEROLENIN	== 0x01: enable zero length IN packets
		// bit 0:	WORDWIDE	== 0x01: 16 bit word width
	SYNCDELAY;

	// configure FIFOs for AUTOOUT-mode
	EP6FIFOCFG = 0x55;
		// bit.7    0 
		// bit 6:	INFM1		== 0x01: assert full flag one sample earlier than when the full condition occurs
		// bit 5:	OEP1		== 0x00
		// bit 4:	AUTOOUT		== 0x01
		// bit 3:	AUTOIN		== 0x00: incoming data is automatically packetized and transmitted, without CPU intervention
		// bit 2:	ZEROLENIN	== 0x01: enable zero length IN packets
        // bit.1    0 
		// bit 0:	WORDWIDE	== 0x01: 16 bit word width

	SYNCDELAY;
	EP6FIFOCFG = 0x4D;
	SYNCDELAY;
	PINFLAGSAB = 0x00; 	// defines FLAGA as prog-level flag, pointed to by FIFOADR[1:0]
	SYNCDELAY; 			// FLAGB as full flag, as pointed to by FIFOADR[1:0]
	PINFLAGSCD = 0x00; 	// FLAGC as empty flag, as pointed to by FIFOADR[1:0]
						// won't generally need FLAGD
	PORTACFG = 0x00; 	// used PA7/FLAGD as a port pin, not as a FIFO flag
	SYNCDELAY;

	// set block length to 1024 (only permitted for EP2 and EP6)
	EP2AUTOINLENH = 0x04;
	SYNCDELAY;
	EP2AUTOINLENL = 0x00;
	SYNCDELAY;

	EP6AUTOINLENH = 0x04;
	SYNCDELAY;
	EP6AUTOINLENL = 0x00;
	SYNCDELAY;
	
//  Rwuen = TRUE;                 // Enable remote-wakeup
}


void TD_Poll(void)              // Called repeatedly while the device is idle
{
	// this function is empty since the USB controller is operating in FIFO slave mode
//		if(!(IOC & 0x02))
//		{
//			done_frm_fpga = 1;
//		}
//		if ((done_frm_fpga) && (IOA & 0x80))
//		{
//			IOC|=0x01; //output 1 on PC.3...SYNC signal is HIGH 
//			SYNCDELAY;
//			IOC|=0x00; //output 1 on PC.3...SYNC signal is HIGH 
//			SYNCDELAY;
//			// set again
//			PINFLAGSAB = 0x00; 	// defines FLAGA as prog-level flag, pointed to by FIFOADR[1:0]
//			SYNCDELAY; 			// FLAGB as full flag, as pointed to by FIFOADR[1:0]
//			PINFLAGSCD = 0x00; 	// FLAGC as empty flag, as pointed to by FIFOADR[1:0]
//								// won't generally need FLAGD
//			PORTACFG = 0x00; 	// used PA7/FLAGD as a port pin, not as a FIFO flag
//			SYNCDELAY;
//			EP2FIFOCFG = 0x4D;
//			SYNCDELAY;
//			EP6FIFOCFG = 0x55;
//			SYNCDELAY;			
//		}
}

BOOL TD_Suspend(void)          // Called before the device goes into suspend mode
{
   return(TRUE);
}

BOOL TD_Resume(void)          // Called after the device resumes
{
   return(TRUE);
}

//-----------------------------------------------------------------------------
// Device Request hooks
//   The following hooks are called by the end point 0 device request parser.
//-----------------------------------------------------------------------------

BOOL DR_GetDescriptor(void)
{
   return(TRUE);
}

BOOL DR_SetConfiguration(void)   // Called when a Set Configuration command is received
{
// inserted recently
  if( EZUSB_HIGHSPEED( ) )
  { // ...FX2 in high speed mode
    EP2AUTOINLENH = 0x04;
    SYNCDELAY;
    EP6AUTOINLENH = 0x04;   // set core AUTO commit len = 512 bytes
    SYNCDELAY;
    EP2AUTOINLENL = 0x00;
    SYNCDELAY;
    EP6AUTOINLENL = 0x00;
  }
  else
  { // ...FX2 in full speed mode
    EP2AUTOINLENH = 0x00;
    SYNCDELAY;
    EP6AUTOINLENH = 0x00;   // set core AUTO commit len = 64 bytes
    SYNCDELAY;
    EP2AUTOINLENL = 0x40;
    SYNCDELAY;
    EP6AUTOINLENL = 0x40;
  }
   Configuration = SETUPDAT[2];
   return(TRUE);            // Handled by user code
}

BOOL DR_GetConfiguration(void)   // Called when a Get Configuration command is received
{
   EP0BUF[0] = Configuration;
   EP0BCH = 0;
   EP0BCL = 1;
   return(TRUE);            // Handled by user code
}

BOOL DR_SetInterface(void)       // Called when a Set Interface command is received
{
   AlternateSetting = SETUPDAT[2];
   return(TRUE);            // Handled by user code
}

BOOL DR_GetInterface(void)       // Called when a Set Interface command is received
{
   EP0BUF[0] = AlternateSetting;
   EP0BCH = 0;
   EP0BCL = 1;
   return(TRUE);            // Handled by user code
}

BOOL DR_GetStatus(void)
{
   return(TRUE);
}

BOOL DR_ClearFeature(void)
{
   return(TRUE);
}

BOOL DR_SetFeature(void)
{
   return(TRUE);
}

BOOL DR_VendorCmnd(void)
{
	return(FALSE);
}

//-----------------------------------------------------------------------------
// USB Interrupt Handlers
//   The following functions are called by the USB interrupt jump table.
//-----------------------------------------------------------------------------

// Setup Data Available Interrupt Handler
void ISR_Sudav(void) interrupt 0
{
   GotSUD = TRUE;            // Set flag
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUDAV;         // Clear SUDAV IRQ
}

// Setup Token Interrupt Handler
void ISR_Sutok(void) interrupt 0
{
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUTOK;         // Clear SUTOK IRQ
}

void ISR_Sof(void) interrupt 0
{
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSOF;            // Clear SOF IRQ
}

void ISR_Ures(void) interrupt 0
{
   // whenever we get a USB reset, we should revert to full speed mode
   pConfigDscr = pFullSpeedConfigDscr;
   ((CONFIGDSCR xdata *) pConfigDscr)->type = CONFIG_DSCR;
   pOtherConfigDscr = pHighSpeedConfigDscr;
   ((CONFIGDSCR xdata *) pOtherConfigDscr)->type = OTHERSPEED_DSCR;

   EZUSB_IRQ_CLEAR();
   USBIRQ = bmURES;         // Clear URES IRQ
}

void ISR_Susp(void) interrupt 0
{
   Sleep = TRUE;
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUSP;
}

void ISR_Highspeed(void) interrupt 0
{
   if (EZUSB_HIGHSPEED())
   {
      pConfigDscr = pHighSpeedConfigDscr;
      ((CONFIGDSCR xdata *) pConfigDscr)->type = CONFIG_DSCR;
      pOtherConfigDscr = pFullSpeedConfigDscr;
      ((CONFIGDSCR xdata *) pOtherConfigDscr)->type = OTHERSPEED_DSCR;
   }

   EZUSB_IRQ_CLEAR();
   USBIRQ = bmHSGRANT;
}
void ISR_Ep0ack(void) interrupt 0
{
}
void ISR_Stub(void) interrupt 0
{
}
void ISR_Ep0in(void) interrupt 0
{
}
void ISR_Ep0out(void) interrupt 0
{
}
void ISR_Ep1in(void) interrupt 0
{
}
void ISR_Ep1out(void) interrupt 0
{
}
void ISR_Ep2inout(void) interrupt 0
{
}
void ISR_Ep4inout(void) interrupt 0
{
}
void ISR_Ep6inout(void) interrupt 0
{
}
void ISR_Ep8inout(void) interrupt 0
{
}
void ISR_Ibn(void) interrupt 0
{
}
void ISR_Ep0pingnak(void) interrupt 0
{
}
void ISR_Ep1pingnak(void) interrupt 0
{
}
void ISR_Ep2pingnak(void) interrupt 0
{
}
void ISR_Ep4pingnak(void) interrupt 0
{
}
void ISR_Ep6pingnak(void) interrupt 0
{
}
void ISR_Ep8pingnak(void) interrupt 0
{
}
void ISR_Errorlimit(void) interrupt 0
{
}
void ISR_Ep2piderror(void) interrupt 0
{
}
void ISR_Ep4piderror(void) interrupt 0
{
}
void ISR_Ep6piderror(void) interrupt 0
{
}
void ISR_Ep8piderror(void) interrupt 0
{
}
void ISR_Ep2pflag(void) interrupt 0
{
}
void ISR_Ep4pflag(void) interrupt 0
{
}
void ISR_Ep6pflag(void) interrupt 0
{
}
void ISR_Ep8pflag(void) interrupt 0
{
}
void ISR_Ep2eflag(void) interrupt 0
{
}
void ISR_Ep4eflag(void) interrupt 0
{
}
void ISR_Ep6eflag(void) interrupt 0
{
}
void ISR_Ep8eflag(void) interrupt 0
{
}
void ISR_Ep2fflag(void) interrupt 0
{
}
void ISR_Ep4fflag(void) interrupt 0
{
}
void ISR_Ep6fflag(void) interrupt 0
{
}
void ISR_Ep8fflag(void) interrupt 0
{
}
void ISR_GpifComplete(void) interrupt 0
{
}
void ISR_GpifWaveform(void) interrupt 0
{
}

//	$Log: not supported by cvs2svn $
//	Revision 1.2  2008/11/11 11:10:07  kocks
//	added preprocessor define for external struct
//	
//	Revision 1.1  2008/10/14 11:33:59  kocks
//	*** empty log message ***
//	
//	Revision 1.2  2008/10/14 09:37:34  kocks
//	cleaned up
//	
//	Revision 1.1  2008/10/14 09:11:06  kocks
//	*** empty log message ***
//	
