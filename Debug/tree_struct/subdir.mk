################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tree_struct/xml_tree.cpp 

OBJS += \
./tree_struct/xml_tree.o 

CPP_DEPS += \
./tree_struct/xml_tree.d 


# Each subdirectory must supply rules for building sources it contributes
tree_struct/%.o: ../tree_struct/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


