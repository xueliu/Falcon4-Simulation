% adc_normal_mode_demo

clear all;
close all;
clc

packet_per_Xfer = 16;
Xfers_to_queue  = 16;
bitLength       = 16;

f_sample        = 20e6; % Sampling Frequency : 20MHz
f_center        = 5e6;


% receive data-chunks
rx_dec_signal = ez_usb_device(packet_per_Xfer, Xfers_to_queue, 'NORMAL', 'OFFSET');

[fft_rx_signal, f1]		= fftx(rx_dec_signal, f_sample);

figure;
plot(f1, 20*log10(abs(fft_rx_signal)));
grid on;
title('Bandpass signal');

dt	= 1 / f_sample;

rx_signal_down		= double(rx_dec_signal) .* exp(1i*2*pi*(f_center)*dt*((0 : length(rx_dec_signal)-1) )');

rx_filter           = dtmb_lp_20MHz; % lowpass filter
rx_filter_coeff     = rx_filter.Numerator;
rx_filter_length    = length(rx_filter_coeff);

rx_signal_filtered_temp		= conv(rx_signal_down, rx_filter_coeff); % matched filter
rx_signal_filtered			= rx_signal_filtered_temp(rx_filter_length : end - rx_filter_length + 1);

[fft_rx_signal_down, f1]		= fftx(rx_signal_down, f_sample);
[fft_rx_signal_filtered, f2]	= fftx(rx_signal_filtered, f_sample);
figure;
plot(f1, 20*log10(abs(fft_rx_signal_down)));
grid on;
hold on;
plot(f2, 20*log10(abs(fft_rx_signal_filtered)), 'g');
title('Rx signal');

F_SYMBOL_ORG    = 500;  % /10 kHz
F_SYMBOL_DEST   = 2000; % /10 kHz

dtmb_make('dtmb_prbs', { 'dtmb_prbs_mex.c', 'dtmb_prbs.c', 'dtmb_prbs.h', 'pn420_init_states.h', 'pn945_init_states.h'});

prbs_seq_length         = [255, 595, 511];
frame_header_length     = [420, 595, 945];

% Calculate original sequences
sync_seq_mode1_org = 1-2*dtmb_prbs(1, 0, prbs_seq_length(1));
sync_seq_mode2_org = 1-2*dtmb_prbs(2, 0, prbs_seq_length(2));
sync_seq_mode3_org = 1-2*dtmb_prbs(3, 0, prbs_seq_length(3));


f_gcd           = gcd(F_SYMBOL_ORG, F_SYMBOL_DEST);
F_SYMBOL_ORG    = F_SYMBOL_ORG/f_gcd;
F_SYMBOL_DEST   = F_SYMBOL_DEST/f_gcd;
if (F_SYMBOL_DEST>F_SYMBOL_ORG)
    upsample_factor     = F_SYMBOL_DEST;
    downsample_factor   = F_SYMBOL_ORG;
else
    upsample_factor     = F_SYMBOL_ORG;
    downsample_factor   = F_SYMBOL_DEST;
end

% Calculate resampled sequences
sync_seq_mode1_dest = resample(repmat(sync_seq_mode1_org,3,1), upsample_factor, downsample_factor);
sync_seq_mode2_dest = resample(repmat(sync_seq_mode2_org,2,1), upsample_factor, downsample_factor);
sync_seq_mode3_dest = resample(repmat(sync_seq_mode3_org,3,1), upsample_factor, downsample_factor);

% cut size to radix8 and make complex
seq_mode1_dest_size = ceil(((frame_header_length(1)+prbs_seq_length(1))*upsample_factor/downsample_factor)/8)*8;
seq_mode2_dest_size = ceil((prbs_seq_length(2)*upsample_factor/downsample_factor)/8)*8;
seq_mode3_dest_size = ceil(((frame_header_length(3)+prbs_seq_length(3))*upsample_factor/downsample_factor)/8)*8;

dtmb_mode1_frameheader_20mhz    = sync_seq_mode1_dest(1:seq_mode1_dest_size)*(1+1i);
dtmb_mode2_frameheader_20mhz    = sync_seq_mode2_dest(1:seq_mode2_dest_size)*(1+1i);
dtmb_mode3_frameheader_20mhz    = sync_seq_mode3_dest(1:seq_mode3_dest_size)*(1+1i);

% For mode 2 signal only
xcorr_result    = cross_corr(complex(rx_signal_filtered,0), dtmb_mode2_frameheader_20mhz);

xcorr_comb_p1   = comb_corr_omp(xcorr_result, prbs_seq_length(2)*2);
figure
plot(abs(xcorr_result));
grid on;
title('Cross Correlation of Received Symbol and Local Sequence (10 MHz)');

max(abs(xcorr_comb_p1))

figure
plot(abs(xcorr_comb_p1));
grid on;
title('Comb Results (10 MHz)');

