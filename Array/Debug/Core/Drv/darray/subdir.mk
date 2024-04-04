################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Drv/darray/darray.c 

OBJS += \
./Core/Drv/darray/darray.o 

C_DEPS += \
./Core/Drv/darray/darray.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Drv/darray/%.o Core/Drv/darray/%.su Core/Drv/darray/%.cyclo: ../Core/Drv/darray/%.c Core/Drv/darray/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/plante/STM_STMCUBEIDE/H750/Book_1/Array/Core/Drv/darray" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Drv-2f-darray

clean-Core-2f-Drv-2f-darray:
	-$(RM) ./Core/Drv/darray/darray.cyclo ./Core/Drv/darray/darray.d ./Core/Drv/darray/darray.o ./Core/Drv/darray/darray.su

.PHONY: clean-Core-2f-Drv-2f-darray

