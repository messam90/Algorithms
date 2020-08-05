################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Stacks_Queues/Interanl.cpp \
../Stacks_Queues/Stacks_Quesus.cpp 

OBJS += \
./Stacks_Queues/Interanl.o \
./Stacks_Queues/Stacks_Quesus.o 

CPP_DEPS += \
./Stacks_Queues/Interanl.d \
./Stacks_Queues/Stacks_Quesus.d 


# Each subdirectory must supply rules for building sources it contributes
Stacks_Queues/%.o: ../Stacks_Queues/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/messam/workspaces/CDT/Training/Training" -I"/home/messam/workspaces/CDT/Training/Training/Hashing" -I"/home/messam/workspaces/CDT/Training/Training/Heaps_Maps" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


