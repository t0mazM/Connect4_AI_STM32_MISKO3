################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../X-CUBE-AI/App/python_model.c \
../X-CUBE-AI/App/python_model_data.c \
../X-CUBE-AI/App/python_model_data_params.c 

OBJS += \
./X-CUBE-AI/App/python_model.o \
./X-CUBE-AI/App/python_model_data.o \
./X-CUBE-AI/App/python_model_data_params.o 

C_DEPS += \
./X-CUBE-AI/App/python_model.d \
./X-CUBE-AI/App/python_model_data.d \
./X-CUBE-AI/App/python_model_data_params.d 


# Each subdirectory must supply rules for building sources it contributes
X-CUBE-AI/App/%.o X-CUBE-AI/App/%.su X-CUBE-AI/App/%.cyclo: ../X-CUBE-AI/App/%.c X-CUBE-AI/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"D:/Dokumenti/C/AI-project-con4/con4/system/Include" -I"D:/Dokumenti/C/AI-project-con4/con4/X-CUBE-AI/App" -I"D:/Dokumenti/C/AI-project-con4/con4/Aplication/INLCUDE" -I"D:/Dokumenti/C/c4_ai/Middlewares/ST/AI/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-X-2d-CUBE-2d-AI-2f-App

clean-X-2d-CUBE-2d-AI-2f-App:
	-$(RM) ./X-CUBE-AI/App/python_model.cyclo ./X-CUBE-AI/App/python_model.d ./X-CUBE-AI/App/python_model.o ./X-CUBE-AI/App/python_model.su ./X-CUBE-AI/App/python_model_data.cyclo ./X-CUBE-AI/App/python_model_data.d ./X-CUBE-AI/App/python_model_data.o ./X-CUBE-AI/App/python_model_data.su ./X-CUBE-AI/App/python_model_data_params.cyclo ./X-CUBE-AI/App/python_model_data_params.d ./X-CUBE-AI/App/python_model_data_params.o ./X-CUBE-AI/App/python_model_data_params.su

.PHONY: clean-X-2d-CUBE-2d-AI-2f-App

