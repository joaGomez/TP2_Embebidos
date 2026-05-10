################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/mcal/SysTick.c \
../source/mcal/gpio.c 

C_DEPS += \
./source/mcal/SysTick.d \
./source/mcal/gpio.d 

OBJS += \
./source/mcal/SysTick.o \
./source/mcal/gpio.o 


# Each subdirectory must supply rules for building sources it contributes
source/mcal/%.o: ../source/mcal/%.c source/mcal/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DDEBUG -I../source -I../ -I../SDK/CMSIS -I../SDK/startup -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-mcal

clean-source-2f-mcal:
	-$(RM) ./source/mcal/SysTick.d ./source/mcal/SysTick.o ./source/mcal/gpio.d ./source/mcal/gpio.o

.PHONY: clean-source-2f-mcal

