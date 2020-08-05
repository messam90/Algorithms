################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Heaps_Maps/Heaps_Maps.cpp 

OBJS += \
./Heaps_Maps/Heaps_Maps.o 

CPP_DEPS += \
./Heaps_Maps/Heaps_Maps.d 


# Each subdirectory must supply rules for building sources it contributes
Heaps_Maps/%.o: ../Heaps_Maps/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/messam/workspaces/CDT/Training/Training" -I"/home/messam/workspaces/CDT/Training/Training/Hashing" -I"/home/messam/workspaces/CDT/Training/Training/Heaps_Maps" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


