################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/LED.c \
../system/SCI.c \
../system/buf.c \
../system/joystick.c \
../system/kbd.c \
../system/lcd.c \
../system/lcd_backlight.c \
../system/lcd_ili9341.c \
../system/periodic_services.c \
../system/timing_utils.c \
../system/ugui.c 

OBJS += \
./system/LED.o \
./system/SCI.o \
./system/buf.o \
./system/joystick.o \
./system/kbd.o \
./system/lcd.o \
./system/lcd_backlight.o \
./system/lcd_ili9341.o \
./system/periodic_services.o \
./system/timing_utils.o \
./system/ugui.o 

C_DEPS += \
./system/LED.d \
./system/SCI.d \
./system/buf.d \
./system/joystick.d \
./system/kbd.d \
./system/lcd.d \
./system/lcd_backlight.d \
./system/lcd_ili9341.d \
./system/periodic_services.d \
./system/timing_utils.d \
./system/ugui.d 


# Each subdirectory must supply rules for building sources it contributes
system/%.o system/%.su system/%.cyclo: ../system/%.c system/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"D:/Dokumenti/C/AI-project-con4/con4/system/Include" -I"D:/Dokumenti/C/AI-project-con4/con4/X-CUBE-AI/App" -I"D:/Dokumenti/C/AI-project-con4/con4/Aplication/INLCUDE" -I"D:/Dokumenti/C/c4_ai/Middlewares/ST/AI/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-system

clean-system:
	-$(RM) ./system/LED.cyclo ./system/LED.d ./system/LED.o ./system/LED.su ./system/SCI.cyclo ./system/SCI.d ./system/SCI.o ./system/SCI.su ./system/buf.cyclo ./system/buf.d ./system/buf.o ./system/buf.su ./system/joystick.cyclo ./system/joystick.d ./system/joystick.o ./system/joystick.su ./system/kbd.cyclo ./system/kbd.d ./system/kbd.o ./system/kbd.su ./system/lcd.cyclo ./system/lcd.d ./system/lcd.o ./system/lcd.su ./system/lcd_backlight.cyclo ./system/lcd_backlight.d ./system/lcd_backlight.o ./system/lcd_backlight.su ./system/lcd_ili9341.cyclo ./system/lcd_ili9341.d ./system/lcd_ili9341.o ./system/lcd_ili9341.su ./system/periodic_services.cyclo ./system/periodic_services.d ./system/periodic_services.o ./system/periodic_services.su ./system/timing_utils.cyclo ./system/timing_utils.d ./system/timing_utils.o ./system/timing_utils.su ./system/ugui.cyclo ./system/ugui.d ./system/ugui.o ./system/ugui.su

.PHONY: clean-system

