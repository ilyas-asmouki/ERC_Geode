################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/Thread/Src/FDCANTerminal.cpp \
../System/Thread/Src/PowerMonitor.cpp \
../System/Thread/Src/Thread.cpp 

OBJS += \
./System/Thread/Src/FDCANTerminal.o \
./System/Thread/Src/PowerMonitor.o \
./System/Thread/Src/Thread.o 

CPP_DEPS += \
./System/Thread/Src/FDCANTerminal.d \
./System/Thread/Src/PowerMonitor.d \
./System/Thread/Src/Thread.d 


# Each subdirectory must supply rules for building sources it contributes
System/Thread/Src/%.o System/Thread/Src/%.su System/Thread/Src/%.cyclo: ../System/Thread/Src/%.cpp System/Thread/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32G483xx -c -I../Core/Inc -I../System/Libraries/INA239/Inc -I../System/Thread/Inc -I../System/Core/Inc -I../USB_Device/App -I../USB_Device/Target -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-System-2f-Thread-2f-Src

clean-System-2f-Thread-2f-Src:
	-$(RM) ./System/Thread/Src/FDCANTerminal.cyclo ./System/Thread/Src/FDCANTerminal.d ./System/Thread/Src/FDCANTerminal.o ./System/Thread/Src/FDCANTerminal.su ./System/Thread/Src/PowerMonitor.cyclo ./System/Thread/Src/PowerMonitor.d ./System/Thread/Src/PowerMonitor.o ./System/Thread/Src/PowerMonitor.su ./System/Thread/Src/Thread.cyclo ./System/Thread/Src/Thread.d ./System/Thread/Src/Thread.o ./System/Thread/Src/Thread.su

.PHONY: clean-System-2f-Thread-2f-Src

