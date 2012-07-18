################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bp_abstraction_api.c \
../src/bp_errno.c 

OBJS += \
./src/bp_abstraction_api.o \
./src/bp_errno.o 

C_DEPS += \
./src/bp_abstraction_api.d \
./src/bp_errno.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/home/michele/Dropbox/Tirocinio/code/dtn/DTN2/applib -I/home/michele/Dropbox/Tirocinio/code/dtn/DTN2 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


