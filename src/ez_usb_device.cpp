/*
* Copyright 2013 Department of Communication Technologies, University of Duisburg-Essen
*
* This is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This software is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this software; see the file COPYING. If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street,
* Boston, MA 02110-1301, USA.
*/

#include "mex.h" /* Always include this */

/* misc */
#include "utilities.h"
#include <string>
#include <windows.h>

#include <stdio.h>
#include "cyapi.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <cstring>
#include <atlstr.h>
#include <stdint.h>
#include "ez_usb_device.h"

/* ez-usb includes */
#include <CyAPI.h>

using namespace std;

/* interface */
// #define DEVICE_INDEX  prhs[0]
#define PKT_PER_XFER    prhs[0]
#define XFER_TO_QUEQUE  prhs[1]
#define ADC_MODE        prhs[2]
#define ADC_FORMAT      prhs[3]

#define RECEIVE_DATA  plhs[0]
#define NUM_INPUTS    4
#define NUM_OUTPUTS   1

/* defines */
// #define NUM_SUPPORT	  20
// #define TUNE_AUTO     0
// #define TUNE_MANUAL   1
// #define MAX_NO_GAINS  100

/* global variables */
// int _sample_rates[NUM_SUPPORT];
// int _frequencies[NUM_SUPPORT];
// int _gains[NUM_SUPPORT];
// int _agcs_on[NUM_SUPPORT];
// int _buf_lengths[NUM_SUPPORT];

void mexFunction(int nlhs, mxArray* plhs[],         /* Output variables */
                 int nrhs, const mxArray* prhs[]) { /* Input variables */

    const int		MAX_QUEUE_SZ    = 64;
    const int		VENDOR_ID       = 0x0547;
    const int		PRODUCT_ID      = 0x1004;

    const int       ADC_SCALING     = 0x3FFF;   /* 16383 APS62P49 P.25 Largest 
                                                 number for TestPattern_Normal and TestPattern_Ramp */
    const int       bitlength       = 16; // 16 bit output data from DDC
    CCyUSBDevice*   USBDevice;
    CCyUSBEndPoint* EndPt;
    int				PPX             = 0;
    int				QueueSize       = 0;
    int				TimeOut         = 300;
    bool			bShowData       = true;
    bool			bStreaming      = true;
    bool            bVerifyData     = true;
    bool            bOffsetFormat   = true;
	char            errmsg[250];
    
    int16_t* ramp = NULL;
    double * outr = NULL;
    double * outi = NULL;
    
    verify_counter  verify_adc_counter;

    string s;

    /* ================================================================= */
    /* create an instance of CCyUSBDevic
    /* ================================================================= */
    USBDevice = new CCyUSBDevice(NULL);

    /* ================================================================= */
    /* check inputs and ouputs
    /* ================================================================= */
    if (nrhs != 4) {
        mexErrMsgTxt("4 parameters are requires!");
    }
    
    if (nlhs != 1) {
        mexErrMsgTxt("Data output is required.");
    }
    
    CHECK_PKT_PER_XFER(PKT_PER_XFER);
    CHECK_XFER_TO_QUEUE(XFER_TO_QUEQUE);
    CHECK_ADC_MODE(ADC_MODE);
    CHECK_ADC_FORMAT(ADC_FORMAT);
    
    /* Check ADC Mode Setting */
    /* Get the length of the input ADC_MODE string. */
    size_t mod_len = (mxGetM(ADC_MODE) * mxGetN(ADC_MODE)) + 1;

    /* Allocate memory for ADC_MODE strings. */
    char * mode_buf = (char *) mxCalloc(mod_len, sizeof(char));
    
    /* Copy the string data from ADC_MODE into a C string 
   * input_buf. */
    int status = mxGetString(ADC_MODE, mode_buf, mod_len);
    if (status != 0) 
        mexWarnMsgTxt("Not enough space. String is truncated.");
//     mexPrintf("ADC_MODE: %s \n", mode_buf);
    
    if (strcmp(mode_buf, "NORMAL") == 0)
        bVerifyData = false;
    else if (strcmp(mode_buf, "RAMP") == 0)
        bVerifyData = true;
    else
        mexErrMsgTxt("ADC_MODE must be either NORMAL or RAMP");
    
    /* Check ADC Data Format Setting */
    /* Get the length of the input ADC_FORMAT string. */
    size_t format_len = (mxGetM(ADC_FORMAT) * mxGetN(ADC_FORMAT)) + 1;

    /* Allocate memory for ADC_FORMAT strings. */
    char * format_buf = (char *) mxCalloc(format_len, sizeof(char));
    
    /* Copy the string data from ADC_FORMAT into a C string 
   * input_buf. */
    status = mxGetString(ADC_FORMAT, format_buf, format_len);
    if (status != 0) 
        mexWarnMsgTxt("Not enough space. String is truncated.");
//     mexPrintf("ADC_FORMAT: %s \n", format_buf);
    
    if (strcmp(format_buf, "OFFSET") == 0)
        bOffsetFormat = true;
    else if (strcmp(format_buf, "COMPLEMENT") == 0)
        bOffsetFormat = false;
    else
        mexErrMsgTxt("ADC_FORMAT must be either COMPLEMENT or OFFSET");

    /* ================================================================= */
    /* set packets per Xfer
    /* ================================================================= */                    
    PPX         = (int)mxGetScalar(PKT_PER_XFER);
    QueueSize   = (int)mxGetScalar(XFER_TO_QUEQUE);
    
    /* ================================================================= */
    /* find devices
    /* ================================================================= */

//     mexPrintf("\n");
    
    /* ================================================================= */
    /* get number of connected devices
    /* ================================================================= */
    int_T device_count = USBDevice->DeviceCount();
    if (!device_count) {
        mexPrintf("No supported devices found.\n");
        return;
    }
//     mexPrintf("Found %d device(s):\n", device_count);
    
    /* ================================================================= */
    /* looking for a device having VID = 0547, PID = 1004
    /* ================================================================= */
    int vID, pID;
    int d = 0;
    do {
        USBDevice->Open(d); // Open automatically calls Close() if necessary
        vID = USBDevice->VendorID;
        pID = USBDevice->ProductID;
        d++;
    } while ((d < device_count) && (vID != VENDOR_ID) && (pID != PRODUCT_ID));

    EndPt = USBDevice->BulkInEndPt;

    long BytesXferred = 0;
    unsigned long Successes = 0;
    unsigned long Failures = 0;
    int i = 0;
    
    /* ================================================================= */
    /* allocate the arrays needed for queueing
    /* ================================================================= */
    PUCHAR* buffers             = new PUCHAR[QueueSize];
    CCyIsoPktInfo** isoPktInfos	= new CCyIsoPktInfo*[QueueSize];
    PUCHAR* contexts            = new PUCHAR[QueueSize];
    OVERLAPPED		inOvLap[MAX_QUEUE_SZ];

    long len = EndPt->MaxPktSize * PPX; // Each xfer request will get PPX isoc packets

    EndPt->SetXferSize(len);

    /* ================================================================= */
    /* allocate all the buffers for the queues
    /* ================================================================= */    
    for (i = 0; i < QueueSize; i++) {
        buffers[i] = new UCHAR[len];
        isoPktInfos[i] = new CCyIsoPktInfo[PPX];
        inOvLap[i].hEvent = CreateEvent(NULL, false, false, NULL);

        memset(buffers[i], 0, len);
    }
    
    /* ================================================================= */
    /* queue-up the first batch of transfer requests
    /* ================================================================= */
    for (i = 0; i < QueueSize; i++)	{
        contexts[i] = EndPt->BeginDataXfer(buffers[i], len, &inOvLap[i]);
        if (EndPt->NtStatus || EndPt->UsbdStatus) { // BeginDataXfer failed
		    sprintf(errmsg,"Xfer request rejected. NTSTATUS = 0x%x.\n",EndPt->NtStatus); mexErrMsgTxt(errmsg);            
            AbortXferLoop(PPX, QueueSize, TimeOut, bStreaming, EndPt, i + 1, buffers, isoPktInfos, contexts, inOvLap);
            return;
        }
    }
    
    /* ================================================================= */
    /* create output complex data
    /* ================================================================= */
    int len_receive_data = len / 2;
    int len_receive_complex_data = len / 4;
    if (bVerifyData||bOffsetFormat) {
        /* Get only real values from Channel A */
        RECEIVE_DATA = mxCreateNumericArray(1, &len_receive_data, mxUINT16_CLASS, mxREAL);
        ramp = (int16_t *) mxGetPr(RECEIVE_DATA);
    } else {
        /* Get complex values from Channel A */
        RECEIVE_DATA = mxCreateDoubleMatrix(len_receive_complex_data, 1, mxCOMPLEX); 
        outr = (double*)mxGetPr(RECEIVE_DATA);
        outi = (double*)mxGetPi(RECEIVE_DATA);
    }

    i = 0;

    // The finite xfer loop.
    for (; bStreaming;)		{
        long rLen = len;    // Reset this each time through because
                            // FinishDataXfer may modify it

        if (!EndPt->WaitForXfer(&inOvLap[i], TimeOut)) {
            EndPt->Abort();
            if (EndPt->LastError == ERROR_IO_PENDING)
                WaitForSingleObject(inOvLap[i].hEvent, 2000);
        }

        if (EndPt->Attributes == 1) { // ISOC Endpoint
            if (EndPt->FinishDataXfer(buffers[i], rLen, &inOvLap[i], contexts[i], isoPktInfos[i])) {
                CCyIsoPktInfo* pkts = isoPktInfos[i];
                for (int j = 0; j < PPX; j++) {
                    if (pkts[j].Status == 0) {
                        BytesXferred += pkts[j].Length;

                        //if (bShowData)
                           // Display16Bytes(buffers[i], rLen);

                        Successes++;
                    } else
                        Failures++;

                    pkts[j].Length = 0; // Reset to zero for re-use.
                }

            } else
                Failures++;

        } else { // BULK Endpoint
            if (EndPt->FinishDataXfer(buffers[i], rLen, &inOvLap[i], contexts[i])) {
                Successes++;
                BytesXferred += len;
                
                /* Conver buffered data to real data */
                //
				if (bOffsetFormat || bVerifyData) {
                    Offset2Decimal(buffers[i], rLen, len_receive_data, ramp);
                } else {
//                     Conver2Complex(buffers[i], rLen, len_receive_complex_data, 1, outr, outi);
                    Complement2Decimal(buffers[i], rLen, len_receive_data, ramp, ADC_SCALING);
                }
                
                /* Conver buffered channel A data */
//                 Offset2Decimal(buffers[i], rLen, len_receive_data, outr);
//                 if (bShowData) {
//                     //Conver2Double(buffers[i], rLen, len_receive_data, ADC_SCALING, outr);
//                     mexPrintf("Length of recieved data: %d\n", rLen);
//                     mexPrintf("Length of output data: %d\n", len_receive_data);                    
//                 }
                
                if (bVerifyData) {
                   verify_adc_counter = verify_adc_ramp_data(ramp, len_receive_data);
                   mexPrintf("Number of Error: %d, %.2f %% \n", verify_adc_counter.error_counter, verify_adc_counter.error_percent);
                   mexPrintf("Number of Success: %d, %.2f %% \n", verify_adc_counter.success_counter, verify_adc_counter.success_percent);     
                }
            } else
                Failures++;
        }
        /* ================================================================= */
        /* re-submit this queue element to keep the queue full
        /* ================================================================= */
        contexts[i] = EndPt->BeginDataXfer(buffers[i], len, &inOvLap[i]);
        if (EndPt->NtStatus || EndPt->UsbdStatus) { // BeginDataXfer failed
		    sprintf(errmsg,"Xfer request rejected. NTSTATUS = 0x%x.\n",EndPt->NtStatus); mexErrMsgTxt(errmsg);             
            AbortXferLoop(PPX, QueueSize, TimeOut, bStreaming, EndPt, i + 1, buffers, isoPktInfos, contexts, inOvLap);
            return;
        }
        
        /* run only once */
        i++;
        if (i == 1)
            bStreaming = false;


    }  // End of the infinite loop

    /* ================================================================= */
    /* memory clean-up
    /* ================================================================= */
    AbortXferLoop(PPX, QueueSize, TimeOut, bStreaming, EndPt, i + 1, buffers, isoPktInfos, contexts, inOvLap);

    USBDevice->Close();

    bStreaming = true;

    return;
}

void Display16Bytes(PUCHAR data, int length) {
    int len_output_data = length / 2;
    unsigned __int16* data16 = new unsigned __int16[len_output_data];

    for (int i = 0; i < len_output_data; i += 1)
        data16[i] = (__int16)data[i * 2 + 1] * 256 + data[i * 2];

    for (int i = 0; i < len_output_data; i += 8)
        mexPrintf("0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x \n", data16[i], data16[i + 1], data16[i + 2], data16[i + 3], data16[i + 4], data16[i + 5], data16[i + 6], data16[i + 7]);

    delete[] data16;
}

void Offset2Decimal(const PUCHAR indata, const int receive_data_length, const int len_outr, int16_t* outr) {
    for (int i = 0; i < len_outr; i += 1)
        outr[i] = ((int16_t)indata[i * 2 + 1] * 256 + indata[i * 2]) & 0x3FFF;
}

void Complement2Decimal(const PUCHAR indata, const int receive_data_length, const int len_outr, int16_t* outr, const int scaling) {
    for (int i = 0; i < len_outr; i += 1)
        outr[i] = (((int16_t)indata[i * 2 + 1] * 256 + indata[i * 2]) & 0x3FFF) + scaling;
}

void Conver2Double(const PUCHAR indata, const int receive_data_length, const int len_outr, const int scaling, double* outr) {
    for (int i = 0; i < len_outr; i += 1)
        outr[i] = ((double)((int16_t)indata[i * 2 + 1] * 256 + indata[i * 2])) / scaling;
}

void Conver2Complex(const PUCHAR indata, const int receive_data_length, const int len_complex, const int scaling, double* outr, double* outi) {
    for (int i = 0; i < len_complex; i += 1) {
        outr[i] = ((double)((int16_t)indata[i * 4 + 1] * 256 + indata[i * 4]))      / scaling;
        outi[i] = ((double)((int16_t)indata[i * 4 + 3] * 256 + indata[i * 4 + 2]))  / scaling;
    }
}

void AbortXferLoop(const int PPX, const int QueueSize, const int TimeOut, bool bStreaming, CCyUSBEndPoint* EndPt, int pending, PUCHAR* buffers, CCyIsoPktInfo** isoPktInfos, PUCHAR* contexts, OVERLAPPED inOvLap[]) {
    EndPt->Abort();
    long len = EndPt->MaxPktSize * PPX;

    for (int j = 0; j < QueueSize; j++) {
        if (j < pending) {
            if (!EndPt->WaitForXfer(&inOvLap[j], TimeOut)) {
                EndPt->Abort();
                if (EndPt->LastError == ERROR_IO_PENDING)
                    WaitForSingleObject(inOvLap[j].hEvent, 2000);
            }

            EndPt->FinishDataXfer(buffers[j], len, &inOvLap[j], contexts[j]);
        }

        CloseHandle(inOvLap[j].hEvent);

        delete[] buffers[j];
        delete[] isoPktInfos[j];
    }

    delete[] buffers;
    delete[] isoPktInfos;
    delete[] contexts;

    bStreaming = false;
}

verify_counter verify_adc_ramp_data ( const int16_t* outr, const int size) {
	int k = 0;
	int error_counter = 0;
	int success_counter = 0;
    
	verify_counter counter_tmp;

	for (k = 1; k < size; ++k) {
		if ( outr[k] != (outr[k-1] + 1)) {
			if( (outr[k] == 0) & (outr[k-1] == 16383) ) { 
                success_counter++;
            } else {
                error_counter++;
            }
		} else {
			success_counter++;
		}
    }
    
//     for (k = 0; k < size-1; k++) {
// 		if ( outr[k] == (outr[k+1] + 1)) {
//             success_counter++;
// 		} else if( (outr[k] == 16383) && (outr[k+1] == 0) ) {
// 			success_counter++;
// 		} else {
//             error_counter++;
//         }
//     }
	  
    counter_tmp.error_counter   = error_counter;
    counter_tmp.success_counter = success_counter;
    
	counter_tmp.error_percent   = (float) error_counter / size * 100;
    counter_tmp.success_percent = (float) success_counter / size * 100;
	return counter_tmp;
}

verify_counter verify_adc_ramp_data_complex ( const int16_t* outr, const int16_t* outi, const int size) {
	int k = 0;
	int error_counter = 0;
	int success_counter = 0;
    
	verify_counter counter_tmp;

	for (k = 1; k < size; ++k) {
		if ( outr[k] != (outr[k-1] + 1)) { //-5462 or 5461
			if( (outr[k] == 16383) & (outr[k-1] == 0) ) { 
                success_counter++;
            } else {
                error_counter++;
            }
		} else {
			success_counter++;
		}
    }
	
    for (k = 1; k < size; ++k) {
		if ( outi[k] != (outi[k-1] + 1)) { //-5462 or 5461
			if( (outi[k] == 16383) & (outi[k-1] == 0) ) { 
                success_counter++;
            } else {
                error_counter++;
            }
		} else {
			success_counter++;
		}
	}
    
    counter_tmp.error_counter   = error_counter;
    counter_tmp.success_counter = success_counter;
    
	counter_tmp.error_percent   = (float) error_counter / size * 100;
    counter_tmp.success_percent = (float) success_counter / size * 100;
	return counter_tmp;
}