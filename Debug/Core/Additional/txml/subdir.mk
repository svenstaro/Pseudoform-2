################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Additional/txml/tinystr.cpp \
../Core/Additional/txml/tinyxml.cpp \
../Core/Additional/txml/tinyxmlerror.cpp \
../Core/Additional/txml/tinyxmlparser.cpp 

OBJS += \
./Core/Additional/txml/tinystr.o \
./Core/Additional/txml/tinyxml.o \
./Core/Additional/txml/tinyxmlerror.o \
./Core/Additional/txml/tinyxmlparser.o 

CPP_DEPS += \
./Core/Additional/txml/tinystr.d \
./Core/Additional/txml/tinyxml.d \
./Core/Additional/txml/tinyxmlerror.d \
./Core/Additional/txml/tinyxmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Additional/txml/%.o: ../Core/Additional/txml/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ockonal/Workspace/Pseudoform2" -I/usr/include -I/usr/include/boost -I/usr/include/OGRE -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


