################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/msp430_4.1.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./msp430_gpio.obj" \
"./main.obj" \
"./lcd_16x2.obj" \
"./i2c.obj" \
"./gpio_pin.obj" \
"./fj2207.obj" \
"./dvbt2_fifo.obj" \
"./dac8830.obj" \
"./cdce62005.obj" \
"./bitbang.obj" \
"./ads62p49.obj" \
"../lnk_msp430f4618.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ads62p49_fj2207.out

# Tool invocations
ads62p49_fj2207.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx --abi=coffabi -g --define=__MSP430F4618__ --define=BITBANG_MACRO_IMPLEMENTATION --define=CPU_TYPE_MSP430 --diag_warning=225 --printf_support=minimal -z --stack_size=80 -m"ads62p49_fj2207.map" --heap_size=80 --use_hw_mpy=16 -i"C:/ti/ccsv5/ccs_base/msp430/include" -i"C:/Users/xue liu/Desktop/MyDSPProject/ktdsp" -i"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/lib" -i"C:/ti/ccsv5/tools/compiler/msp430_4.1.5/include" --reread_libs --warn_sections --xml_link_info="ads62p49_fj2207_linkInfo.xml" --rom_model -o "ads62p49_fj2207.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(MSP430_EXECUTABLE_OUTPUTS__QUOTED) "ads62p49_fj2207.out"
	-$(RM) "ads62p49.pp" "bitbang.pp" "cdce62005.pp" "dac8830.pp" "dvbt2_fifo.pp" "fj2207.pp" "gpio_pin.pp" "i2c.pp" "lcd_16x2.pp" "main.pp" "msp430_gpio.pp" 
	-$(RM) "ads62p49.obj" "bitbang.obj" "cdce62005.obj" "dac8830.obj" "dvbt2_fifo.obj" "fj2207.obj" "gpio_pin.obj" "i2c.obj" "lcd_16x2.obj" "main.obj" "msp430_gpio.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

