################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/ADC.c" \
"../src/CLK.c" \
"../src/FTM.c" \
"../src/GPIO.c" \
"../src/UART.c" \
"../src/main.c" \
"../src/motorfuncs.c" \
"../src/parsecommands.c" \
"../src/statisticsfunc.c" \

C_SRCS += \
../src/ADC.c \
../src/CLK.c \
../src/FTM.c \
../src/GPIO.c \
../src/UART.c \
../src/main.c \
../src/motorfuncs.c \
../src/parsecommands.c \
../src/statisticsfunc.c \

C_DEPS_QUOTED += \
"./src/ADC.d" \
"./src/CLK.d" \
"./src/FTM.d" \
"./src/GPIO.d" \
"./src/UART.d" \
"./src/main.d" \
"./src/motorfuncs.d" \
"./src/parsecommands.d" \
"./src/statisticsfunc.d" \

OBJS_QUOTED += \
"./src/ADC.o" \
"./src/CLK.o" \
"./src/FTM.o" \
"./src/GPIO.o" \
"./src/UART.o" \
"./src/main.o" \
"./src/motorfuncs.o" \
"./src/parsecommands.o" \
"./src/statisticsfunc.o" \

C_DEPS += \
./src/ADC.d \
./src/CLK.d \
./src/FTM.d \
./src/GPIO.d \
./src/UART.d \
./src/main.d \
./src/motorfuncs.d \
./src/parsecommands.d \
./src/statisticsfunc.d \

OBJS_OS_FORMAT += \
./src/ADC.o \
./src/CLK.o \
./src/FTM.o \
./src/GPIO.o \
./src/UART.o \
./src/main.o \
./src/motorfuncs.o \
./src/parsecommands.o \
./src/statisticsfunc.o \

OBJS += \
./src/ADC.o \
./src/CLK.o \
./src/FTM.o \
./src/GPIO.o \
./src/UART.o \
./src/main.o \
./src/motorfuncs.o \
./src/parsecommands.o \
./src/statisticsfunc.o \


# Each subdirectory must supply rules for building sources it contributes
src/ADC.o: ../src/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/ADC.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/CLK.o: ../src/CLK.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/CLK.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/CLK.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FTM.o: ../src/FTM.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/FTM.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/FTM.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/GPIO.o: ../src/GPIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/GPIO.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/UART.o: ../src/UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/UART.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/motorfuncs.o: ../src/motorfuncs.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/motorfuncs.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/motorfuncs.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/parsecommands.o: ../src/parsecommands.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/parsecommands.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/parsecommands.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/statisticsfunc.o: ../src/statisticsfunc.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/statisticsfunc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/statisticsfunc.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


