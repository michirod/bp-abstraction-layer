################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bp_implementations/bp_dtn.c \
../src/bp_implementations/bp_dtn_conversions.c \
../src/bp_implementations/bp_ion.c 

OBJS += \
./src/bp_implementations/bp_dtn.o \
./src/bp_implementations/bp_dtn_conversions.o \
./src/bp_implementations/bp_ion.o 

C_DEPS += \
./src/bp_implementations/bp_dtn.d \
./src/bp_implementations/bp_dtn_conversions.d \
./src/bp_implementations/bp_ion.d 


# Each subdirectory must supply rules for building sources it contributes
src/bp_implementations/%.o: ../src/bp_implementations/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/home/michele/Dropbox/Tirocinio/code/dtn/DTN2/applib -I/home/michele/Dropbox/Tirocinio/code/dtn/DTN2 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


