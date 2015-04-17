% ADC RAMP mode demo

clear all;
close all;
clc

packet_per_Xfer = 128;
Xfers_to_queue  = 64;
% receive data-chunks
data=ez_usb_device(packet_per_Xfer,  Xfers_to_queue, 'RAMP','OFFSET');

% plot real and imag data
max(data)
% subplot(2,1,1), 
plot(data);
title('ADC RAMP mode data');
grid on
% subplot(2,1,2), plot(imag(data));
% title('Imag');