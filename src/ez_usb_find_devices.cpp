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
    Find ez usb devices attached to the host.
*/

/* Simulink includes */
#include <simstruc.h>
#include <mex.h>

/* misc */
#include "utilities.h"
#include <string>
#include <windows.h>

#include <stdio.h>
#include "cyapi.h"
#include <conio.h>

/* ez-usb includes */
#include <CyAPI.h>

using namespace std;

/* Entry point to C/C++ */
void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    int_T i, j, ret;
    char vendor[256], product[256], serial[256];
    char buf[512];
    string s;
    CCyUSBDevice *USBDevice;
    USB_DEVICE_DESCRIPTOR descr;

    /* Create an instance of CCyUSBDevice */
    USBDevice = new CCyUSBDevice(NULL);

    /* ================================================================= */
    /* check input and ouput
    /* ================================================================= */
            
    if (nrhs != 0) {
        mexErrMsgTxt("No arguments required.");
    }            
    
    /* ================================================================= */
    /* find devices
    /* ================================================================= */
    
    mexPrintf("\n");
  
    /* get number of connected devices */
    int_T device_count = USBDevice->DeviceCount();
    if (!device_count) {
        mexPrintf("No supported devices found.\n");
        return;
    }
    mexPrintf("Found %d device(s):\n", device_count);
    
    /* for each detected device print dev info */
    for (int i=0; i < device_count; i++)
    {
        if (USBDevice->Open(i))
        {
            USBDevice->GetDeviceDescriptor(&descr);

            mexPrintf("bLength \t\t 0x%02x\n",descr.bLength);
            mexPrintf("bDescriptorType \t 0x%02x\n",descr.bDescriptorType);
            mexPrintf("bcdUSB \t\t\t 0x%04x\n",descr.bcdUSB);
            mexPrintf("bDeviceClass \t\t 0x%02x\n",descr.bDeviceClass);
            mexPrintf("bDeviceSubClass \t 0x%02x\n",descr.bDeviceSubClass);
            mexPrintf("bDeviceProtocol \t 0x%02x\n",descr.bDeviceProtocol);
            mexPrintf("bMaxPacketSize0 \t %d\n",descr.bMaxPacketSize0);
            mexPrintf("idVendor \t\t 0x%04x\n",descr.idVendor);
            mexPrintf("idProduct \t\t 0x%04x\n",descr.idProduct);
            mexPrintf("bcdDevice \t\t 0x%04x\n",descr.bcdDevice);
            mexPrintf("iManufacturer \t\t 0x%02x\n",descr.iManufacturer);
            mexPrintf("iProduct \t\t 0x%02x\n",descr.iProduct);
            mexPrintf("iSerialNumber \t\t 0x%02x\n",descr.iSerialNumber);
            mexPrintf("bNumConfigurations \t 0x%02x\n\n",descr.bNumConfigurations);

            //USBDevice->Close();
        }
        else
        {
            printf("unable to open device\n");
        }
    }

    // This code lists all the endpoints reported
    // for all the interfaces reported
    // for all the configurations reported
    // by the device.
    /* get number of usb config */
    int_T config_count = USBDevice->ConfigCount();
    if (!config_count) {
        mexPrintf("No USB config found.\n");
        return;
    }
    mexPrintf("Found %d USB config(s):\n", device_count);
    for (int c=0; c < config_count; c++) {
        CCyUSBConfig cfg = USBDevice->GetUSBConfig(c);

        sprintf_s(buf,"bLength: 0x%x\n",cfg.bLength); s.append(buf);
        sprintf_s(buf,"bDescriptorType: %d\n",cfg.bDescriptorType); s.append(buf);
        sprintf_s(buf,"wTotalLength: %d (0x%x)\n",cfg.wTotalLength,cfg.wTotalLength);
        s.append(buf);
        sprintf_s(buf,"bNumInterfaces: %d\n",cfg.bNumInterfaces); s.append(buf);
        sprintf_s(buf,"bConfigurationValue: %d\n",cfg.bConfigurationValue); s.append(buf);
        sprintf_s(buf,"iConfiguration: %d\n",cfg.iConfiguration); s.append(buf);
        sprintf_s(buf,"bmAttributes: 0x%x\n",cfg.bmAttributes); s.append(buf);
        sprintf_s(buf,"MaxPower: %d\n",cfg.MaxPower); s.append(buf);
        s.append("**********************************\n");
        mexPrintf("%s\n", s.c_str());
        s.clear();
        for (int i=0; i<cfg.AltInterfaces; i++)
        { 
            CCyUSBInterface * ifc = cfg.Interfaces[i];
            sprintf_s(buf,"Interface Descriptor:%d\n",(i+1));s.append(buf);
            sprintf_s(buf,"--------------------------------\n");s.append(buf);
            sprintf_s(buf,"bLength: 0x%x\n",ifc->bLength); s.append(buf);
            sprintf_s(buf,"bDescriptorType: %d\n",ifc->bDescriptorType); s.append(buf);
            sprintf_s(buf,"bInterfaceNumber: %d\n",ifc->bInterfaceNumber); s.append(buf);
            sprintf_s(buf,"bAlternateSetting: %d\n",ifc->bAlternateSetting); s.append(buf);
            sprintf_s(buf,"bNumEndpoints: %d\n",ifc->bNumEndpoints); s.append(buf);
            sprintf_s(buf,"bInterfaceClass: %d\n",ifc->bInterfaceClass); s.append(buf);
            sprintf_s(buf,"**********************************\n");s.append(buf);
            mexPrintf("%s\n", s.c_str());
            s.clear();
            for (int e=0; e<ifc->bNumEndpoints; e++) {
                CCyUSBEndPoint * ept = ifc->EndPoints[e+1];
                sprintf_s(buf,"EndPoint Descriptor:%d\n",(e+1));s.append(buf);
                sprintf_s(buf,"--------------------------------\n");s.append(buf);
                sprintf_s(buf,"bLength: 0x%x\n",ept->DscLen); s.append(buf);
                sprintf_s(buf,"bDescriptorType: %d\n",ept->DscType); s.append(buf);
                sprintf_s(buf,"bEndpointAddress: 0x%x\n",ept->Address); s.append(buf);
                sprintf_s(buf,"bmAttributes: 0x%x\n",ept->Attributes); s.append(buf);
                sprintf_s(buf,"wMaxPacketSize: %d\n",ept->MaxPktSize); s.append(buf);
                sprintf_s(buf,"bInterval: %d\n",ept->Interval); s.append(buf);
                s.append("**********************************\n");
                mexPrintf("%s\n", s.c_str());
                s.clear();
            } // End of for loop for USB endpoints 
        } // End of for loop for USB interfaces 
    } // End of for loop for USB configs 
    
    USBDevice->Close();
}
