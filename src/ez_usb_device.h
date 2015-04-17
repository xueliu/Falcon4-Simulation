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

/*
    Header file for ez_usb_device
*/

#ifndef EZ_USB_DEVICE_H
#define EZ_USB_DEVICE_H

typedef struct {
    int error_counter;
    int success_counter;
    float error_percent;
    float success_percent;
} verify_counter;

/* Functions */

void Display16Bytes(PUCHAR data, int length);
void Offset2Decimal(const PUCHAR indata, const int receive_data_length, const int len_outr, int16_t* outr);
void Complement2Decimal(const PUCHAR indata, const int receive_data_length, const int len_outr, int16_t* outr, const int scaling);
void Conver2Double(const PUCHAR indata, const int receive_data_length, const int len_outr, const int scaling, double* outr);
void Conver2Complex(const PUCHAR indata, const int receive_data_length, const int len_complex, const int scaling, double* outr, double* outi);
void AbortXferLoop(const int PPX, const int QueueSize, const int TimeOut, bool bStreaming, CCyUSBEndPoint* EndPt, int pending, PUCHAR* buffers, CCyIsoPktInfo** isoPktInfos, PUCHAR* contexts, OVERLAPPED inOvLap[]);
verify_counter verify_adc_ramp_data ( const int16_t* outr, const int size);
verify_counter verify_adc_ramp_data_complex ( const int16_t* outr, const int16_t* outi, const int size);

#endif /* EZ_USB_DEVICE */