vlog ADC_ADS62P49_testbench.v
vlog ADC_ADS62P49_module.v

vsim ADC_ADS62P49_testbench -L unisims_ver -L XilinxCoreLib_ver

view wave 
add wave * 
view structure 
view signals 
run 1000ns 

