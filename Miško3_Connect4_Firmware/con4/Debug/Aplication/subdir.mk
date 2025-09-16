################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplication/DEBUG_functions.c \
../Aplication/ai_model.c \
../Aplication/game.c \
../Aplication/graphics.c \
../Aplication/state_machine.c 

OBJS += \
./Aplication/DEBUG_functions.o \
./Aplication/ai_model.o \
./Aplication/game.o \
./Aplication/graphics.o \
./Aplication/state_machine.o 

C_DEPS += \
./Aplication/DEBUG_functions.d \
./Aplication/ai_model.d \
./Aplication/game.d \
./Aplication/graphics.d \
./Aplication/state_machine.d 


# Each subdirectory must supply rules for building sources it contributes
Aplication/%.o Aplication/%.su Aplication/%.cyclo: ../Aplication/%.c Aplication/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"D:/Dokumenti/C/AI-project-con4/con4/system/Include" -I"D:/Dokumenti/C/AI-project-con4/con4/X-CUBE-AI/App" -I"D:/Dokumenti/C/AI-project-con4/con4/Aplication/INLCUDE" -I"D:/Dokumenti/C/c4_ai/Middlewares/ST/AI/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Aplication

clean-Aplication:
	-$(RM) ./Aplication/DEBUG_functions.cyclo ./Aplication/DEBUG_functions.d ./Aplication/DEBUG_functions.o ./Aplication/DEBUG_functions.su ./Aplication/ai_model.cyclo ./Aplication/ai_model.d ./Aplication/ai_model.o ./Aplication/ai_model.su ./Aplication/game.cyclo ./Aplication/game.d ./Aplication/game.o ./Aplication/game.su ./Aplication/graphics.cyclo ./Aplication/graphics.d ./Aplication/graphics.o ./Aplication/graphics.su ./Aplication/state_machine.cyclo ./Aplication/state_machine.d ./Aplication/state_machine.o ./Aplication/state_machine.su

.PHONY: clean-Aplication

