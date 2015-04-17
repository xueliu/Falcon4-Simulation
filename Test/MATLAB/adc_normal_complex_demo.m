% adc_normal_mode_demo

clear all;
close all;
clc

packet_per_Xfer = 32;
Xfers_to_queue  = 32;
bitLength       = 16;


% receive data-chunks
rx_dec_signal = ez_usb_device(packet_per_Xfer, Xfers_to_queue);

% data		  = zeros(length(rx_dec_signal), 1);
% get scaling_factor
% scaling_factor = (2^(bitlength-1)-1 ) / max(abs(rx_signal));

for idx = 1:size(rx_dec_signal,1)
	if ( real(rx_dec_signal(idx)) < 2^(bitlength-1))
		real(data(idx,1)) = real(rx_dec_signal(idx));
	else
		real(data(idx,1)) = real(rx_dec_signal(idx)) - 2^bitlength;
    end
    
    if ( imag(rx_dec_signal(idx)) < 2^(bitlength-1))
		imag(data(idx,1)) = imag(rx_dec_signal(idx));
	else
		imag(data(idx,1)) = imag(rx_dec_signal(idx)) - 2^bitlength;
	end
end

