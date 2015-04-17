%
% Copyright 2010 Communications Engineering Lab, KIT
%
% This is free software; you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation; either version 3, or (at your option)
% any later version.
%
% This software is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
% GNU General Public License for more details.
%
% You should have received a copy of the GNU General Public License
% along with this software; see the file COPYING. If not, write to
% the Free Software Foundation, Inc., 51 Franklin Street,
% Boston, MA 02110-1301, USA.
%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% make script for Simulink Falcon4
% use "make -v" to get a verbose output
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function make(varargin)

EZ_USB_BIN_DIR = fullfile(pwd,'bin');

if ispc
    % this should point to the directory of rtl-sdr.h
    %RTL_SDR_INC_DIR = fullfile(pwd,'deps','rtl-sdr-release');
    EZ_USB_INC_DIR = 'C:\Users\xue liu\Desktop\Falcon-simulation\CyAPI\inc';
    % this should point to the directory of rtlsdr.lib
    %RTL_SDR_LIB_DIR = fullfile(pwd,'deps','rtl-sdr-release','x64');
    EZ_USB_LIB_DIR = 'C:\Users\xue liu\Desktop\Falcon-simulation\CyAPI\lib\x64';
    
    WINDOWS_SDK_LIB_DIR = 'C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib'; % To find libary SetupAPI.Lib
    
    % this should point to the directory of pthread.h
    %PTHREAD_INC_DIR = fullfile(pwd,'deps','pthread','include');
    PTHREAD_INC_DIR = 'C:\Users\xue liu\Desktop\RTL SDR\pthreads-w32-2-9-1-release\Pre-built.2\include';
    % this should point to the directory of pthreadVC.lib
    %PTHREAD_LIB_DIR = fullfile(pwd,'deps','pthread','lib','x64');
    PTHREAD_LIB_DIR = 'C:\Users\xue liu\Desktop\RTL SDR\pthreads-w32-2-9-1-release\Pre-built.2\lib\x64';
    
    % make sure the other required DLLS are in your PATH 
    % (e.g. place them in the bin directory)
    
    options = { ...
        ['-I' pwd]; ...
        ['-I' EZ_USB_INC_DIR]; ...
        ['-L' EZ_USB_LIB_DIR]; ...
        ['-L' WINDOWS_SDK_LIB_DIR]; ...          
        ['-l' 'CyAPI']; ...
        ['-l' 'SetupAPI']; ...
        ['-g']; ...        
    };
    options_pthread = { ...
        ['-I' PTHREAD_INC_DIR]; ...
        ['-L' PTHREAD_LIB_DIR]; ...
        ['-l' 'pthreadVC2'] ...
    };
elseif isunix
    options = { ...
        ['-l' 'rtlsdr']
    };
    options_pthread = { ...
        ['-l' 'pthread'] ...
    };
else
    error('Platform not supported')
end

% create bin order if not exist
if (~exist(EZ_USB_BIN_DIR,'dir'))
    mkdir(EZ_USB_BIN_DIR);
end

% add command line args if exist
if ~isempty(varargin)
    options = [options; char(varargin)];
end

% Set path hint

% compile source and find_devices
% fprintf('\nCompiling ez_usb_source.cpp ... ');
% mex(options{:},options_pthread{:},'-outdir',RTL_SDR_BIN_DIR,'src/ez_usb_source.cpp')
% fprintf('Done.\n');

fprintf('\nCompiling ez_usb_find_devices.cpp ... ');
mex(options{:},'-outdir',EZ_USB_BIN_DIR,'src/ez_usb_find_devices.cpp')
fprintf('Done.\n');

fprintf('\nCompiling ezusb_dev.cpp ... ');
mex(options{:},'-outdir',EZ_USB_BIN_DIR,'src/ez_usb_device.cpp')
fprintf('Done.\n');

% % copy help file
% copyfile(fullfile(pwd,'src','rtlsdr_dev.m'),fullfile(EZ_USB_BIN_DIR,'rtlsdr_dev.m'));
    

% Set path hint
% fprintf('\nBuild successful.\n\nSet path to:\n -> %s\n -> %s\n',RTL_SDR_BIN_DIR,fullfile(pwd,'blockset'));