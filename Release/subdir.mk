################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TagStructs.cpp \
../httpp.cpp \
../mimetypes.cpp \
../page.cpp \
../request.cpp \
../util.cpp 

OBJS += \
./TagStructs.o \
./httpp.o \
./mimetypes.o \
./page.o \
./request.o \
./util.o 

CPP_DEPS += \
./TagStructs.d \
./httpp.d \
./mimetypes.d \
./page.d \
./request.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-4.7 -O3 -Wall -c -fmessage-length=0 --std=gnu++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


