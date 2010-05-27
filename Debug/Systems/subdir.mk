################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Systems/GraphicSystem.cpp \
../Systems/GuiSystem.cpp \
../Systems/InputSystem.cpp \
../Systems/PhysicSystem.cpp \
../Systems/SoundSystem.cpp 

OBJS += \
./Systems/GraphicSystem.o \
./Systems/GuiSystem.o \
./Systems/InputSystem.o \
./Systems/PhysicSystem.o \
./Systems/SoundSystem.o 

CPP_DEPS += \
./Systems/GraphicSystem.d \
./Systems/GuiSystem.d \
./Systems/InputSystem.d \
./Systems/PhysicSystem.d \
./Systems/SoundSystem.d 


# Each subdirectory must supply rules for building sources it contributes
Systems/%.o: ../Systems/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ockonal/Workspace/Pseudoform2" -I/usr/include -I/usr/include/boost -I/usr/include/OGRE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


