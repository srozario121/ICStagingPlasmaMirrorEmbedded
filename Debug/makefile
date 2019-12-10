################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 11
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
AutomatedTapedriveControl.elf \

EXECUTABLES_QUOTED += \
"AutomatedTapedriveControl.elf" \

EXECUTABLES_OS_FORMAT += \
AutomatedTapedriveControl.elf \

SECONDARY_FLASH += \
AutomatedTapedriveControl.srec \

SECONDARY_FLASH_QUOTED += \
"AutomatedTapedriveControl.srec" \

SECONDARY_FLASH_OS_FORMAT += \
AutomatedTapedriveControl.srec \

SECONDARY_SIZE += \
AutomatedTapedriveControl.siz \

SECONDARY_SIZE_QUOTED += \
"AutomatedTapedriveControl.siz" \

SECONDARY_SIZE_OS_FORMAT += \
AutomatedTapedriveControl.siz \


# All Target
all: warning-messages explicit-dependencies AutomatedTapedriveControl.elf secondary-outputs

# Tool invocations
AutomatedTapedriveControl.elf: $(OBJS) C:/Users/svr11/Documents/S32Kinetic/AutomatedTapedriveControl/Project_Settings/Linker_Files/SKEAZ_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #12 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "AutomatedTapedriveControl.elf" "@AutomatedTapedriveControl.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

AutomatedTapedriveControl.srec: $(EXECUTABLES)
	@echo 'Executing target #13 $@'
	@echo 'Invoking: Standard S32DS Create Flash Image'
	arm-none-eabi-objcopy -O srec $(EXECUTABLES)  "AutomatedTapedriveControl.srec"
	@echo 'Finished building: $@'
	@echo ' '

AutomatedTapedriveControl.siz: $(EXECUTABLES)
	@echo 'Executing target #14 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH_QUOTED) ./*/*/*.d ./*/*.d  ./*/*/*.o ./*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

