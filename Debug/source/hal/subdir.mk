################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/hal/IRQN_Ports.c \
../source/hal/card.c \
../source/hal/display.c \
../source/hal/leds.c \
../source/hal/shift.c \
../source/hal/system.c \
../source/hal/timers.c \
../source/hal/uart.c \
../source/hal/wheel.c 

C_DEPS += \
./source/hal/IRQN_Ports.d \
./source/hal/card.d \
./source/hal/display.d \
./source/hal/leds.d \
./source/hal/shift.d \
./source/hal/system.d \
./source/hal/timers.d \
./source/hal/uart.d \
./source/hal/wheel.d 

OBJS += \
./source/hal/IRQN_Ports.o \
./source/hal/card.o \
./source/hal/display.o \
./source/hal/leds.o \
./source/hal/shift.o \
./source/hal/system.o \
./source/hal/timers.o \
./source/hal/uart.o \
./source/hal/wheel.o 


# Each subdirectory must supply rules for building sources it contributes
source/hal/%.o: ../source/hal/%.c source/hal/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DDEBUG -I../source -I../ -I../SDK/CMSIS -I../SDK/startup -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-hal

clean-source-2f-hal:
	-$(RM) ./source/hal/IRQN_Ports.d ./source/hal/IRQN_Ports.o ./source/hal/card.d ./source/hal/card.o ./source/hal/display.d ./source/hal/display.o ./source/hal/leds.d ./source/hal/leds.o ./source/hal/shift.d ./source/hal/shift.o ./source/hal/system.d ./source/hal/system.o ./source/hal/timers.d ./source/hal/timers.o ./source/hal/uart.d ./source/hal/uart.o ./source/hal/wheel.d ./source/hal/wheel.o

.PHONY: clean-source-2f-hal

