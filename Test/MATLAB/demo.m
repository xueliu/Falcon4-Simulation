% Demo
clear all;
close all;
clc


bitlength = 16;
f_sample = 10e6;
% 
% receive data-chunks
data=ez_usb_device(64, 32);

% data_i = real(data);
% data_q = imag(data);

data_i = data;

% [fft_data_i, f] = fftx(data_i+1i*data_q, f_sample);
[fft_data_i, f] = fftx(data_i, f_sample);
% [fft_data_q, f_q] = fftx(data_q, f_sample);

figure;
% subplot(211);
plot(f, 20*log10(abs(fft_data_i)));
title('inphase');
grid on;
% subplot(212);
% plot(f_q, 20*log10(abs(fft_data_q)));
% title('quadrature');
% grid on;
% return;

% figure;
% subplot(2,1,1)
% plot(data_i);
% grid on;
% subplot(2,1,2)
% plot(data_q);
% grid on;
% hold on;
% box on;

% plot periodogram
% plot(10*log10((abs(1/20480*fftshift(fft(imag(data)))).^2)))
% xlim([0 20480])
% ylim([-110 0])
% grid on
% drawnow;