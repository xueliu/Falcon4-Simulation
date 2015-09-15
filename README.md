Falcon4-Simulation
================

The Falcon4-Simulation project is an Open Source Software Package that enables owners of Falcon4 SDR platform to build models in MATLAB (Simulink in future) that interface with the device in real-time. Falcon4-Simulation uses the *CyAPI* library from Cypress and some code fragments from *Simulink-RTL-SDR* to receive IQ samples from the FJ2207 TV tuner. It is thus possible to build a wide variety of signal processing and wireless communication applications directly in MATLAB (Simulink in future) while being able to test them on real hardware at the same time.

The Simulink-RTL-SDR project was initiated at the *Department of Communication Technologies (KT))* at the *University of Duisburg-Essen*, Germany, <http://www.kt.uni-due.de/>.

This README.md is based on the one from [rtl-sdr](https://github.com/kit-cel/simulink-rtl-sdr) 

Requirements
------------

- MATLAB/Simulink (R2009b or newer) and *MEX* compatible [compiler](http://www.mathworks.de/support/compilers)

- *CyAPI* library from the [Cypress](http://www.cypress.com/?rID=34870 "Cypress SuiteUSB 3.4")

Build/Install instructions for Microsoft Windows
------------------------------------

1. Get and install the *Cypress SuiteUSB 3.4* library. See the [Cypress](http://www.cypress.com/?rID=34870) for instructions.

2. Install property USB driver from folder USB/usb-driver of the Falcon4-Simulation directory according to the type of your system.

3. Get the Falcon4-Simulation source code

		$ git clone https://github.com/xueliu/Falcon4-Simulation.git
        
	If you aren't using *git*, you can download a [compressed file](https://github.com/xueliu/Falcon4-Simulation) from the project page directly. Extract the archive to any folder you want.
		
4. Run MATLAB and setup the *MEX* compiler
	
		>> mex -setup

5. Switch to your Simulink-RTL-SDR directory.
		
6. Run MATLAB, switch to your Falcon4-Simulation directory and start the build process

		>> make.m

7. Add the *bin* directory to the MATLAB path environment.

8. Modify make.m to point to the *CyAPI* include and lib directory. If you are using a 64-bit MATLAB, make sure to use a 64-bit build of the *CyAPI* library.

		EZ_USB_INC_DIR  = <path to Falcon-simulation\USB\CyAPI\inc>
		EZ_USB_LIB_DIR  = <path to Falcon-simulation\USB\CyAPI\lib\x64>

	Also adjust the lib paths for the *Windows SDK* library.

		WINDOWS_SDK_LIB_DIR = <path to SetupAPI.Lib>

9. Start the build process (in MATLAB)

		>> make.m

10. You will now find two new MATLAB functions and use the demo programs.

Copyright
---------

GNU General Public License
