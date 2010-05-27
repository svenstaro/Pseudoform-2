################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/GameApplication.cpp \
../Core/Utils.cpp 

OBJS += \
./Core/GameApplication.o \
./Core/Utils.o 

CPP_DEPS += \
./Core/GameApplication.d \
./Core/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ockonal/Workspace/Pseudoform2" -I/usr/include -I/usr/include/boost -I/usr/include/OGRE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


