################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AntiDiagnoals.cpp \
../ExcelColumnNumber.cpp \
../FizzBuzz.cpp \
../GreatestCommonDivisor.cpp \
../GridUniquePaths.cpp \
../Internal.cpp \
../LargestCoprimeDivisor.cpp \
../Main.cpp \
../PalindromeInteger.cpp \
../PascalTriangle.cpp \
../PrimeSum.cpp \
../RearrangeArray.cpp \
../ReverseInteger.cpp \
../SpiralMatrix.cpp \
../TrailingZerosInFactorial.cpp 

OBJS += \
./AntiDiagnoals.o \
./ExcelColumnNumber.o \
./FizzBuzz.o \
./GreatestCommonDivisor.o \
./GridUniquePaths.o \
./Internal.o \
./LargestCoprimeDivisor.o \
./Main.o \
./PalindromeInteger.o \
./PascalTriangle.o \
./PrimeSum.o \
./RearrangeArray.o \
./ReverseInteger.o \
./SpiralMatrix.o \
./TrailingZerosInFactorial.o 

CPP_DEPS += \
./AntiDiagnoals.d \
./ExcelColumnNumber.d \
./FizzBuzz.d \
./GreatestCommonDivisor.d \
./GridUniquePaths.d \
./Internal.d \
./LargestCoprimeDivisor.d \
./Main.d \
./PalindromeInteger.d \
./PascalTriangle.d \
./PrimeSum.d \
./RearrangeArray.d \
./ReverseInteger.d \
./SpiralMatrix.d \
./TrailingZerosInFactorial.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/messam/workspaces/CDT/Training/Training" -I"/home/messam/workspaces/CDT/Training/Training/Hashing" -I"/home/messam/workspaces/CDT/Training/Training/Heaps_Maps" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


