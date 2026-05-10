################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/app/App.c \
../source/app/display_intensity.c \
../source/app/id_input.c \
../source/app/pass_input.c \
../source/app/user.c \
../source/app/utils.c 

C_DEPS += \
./source/app/App.d \
./source/app/display_intensity.d \
./source/app/id_input.d \
./source/app/pass_input.d \
./source/app/user.d \
./source/app/utils.d 

OBJS += \
./source/app/App.o \
./source/app/display_intensity.o \
./source/app/id_input.o \
./source/app/pass_input.o \
./source/app/user.o \
./source/app/utils.o 


# Each subdirectory must supply rules for building sources it contributes
source/app/%.o: ../source/app/%.c source/app/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -D__USE_CMSIS -DDEBUG -I../source -I../ -I../SDK/CMSIS -I../SDK/startup -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-app

clean-source-2f-app:
	-$(RM) ./source/app/App.d ./source/app/App.o ./source/app/display_intensity.d ./source/app/display_intensity.o ./source/app/id_input.d ./source/app/id_input.o ./source/app/pass_input.d ./source/app/pass_input.o ./source/app/user.d ./source/app/user.o ./source/app/utils.d ./source/app/utils.o

.PHONY: clean-source-2f-app

