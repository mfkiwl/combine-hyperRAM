################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/rtos/Source/portable/RVDS/ARM_CM4_MPU/port.c 

OBJS += \
./app/rtos/Source/portable/RVDS/ARM_CM4_MPU/port.o 

C_DEPS += \
./app/rtos/Source/portable/RVDS/ARM_CM4_MPU/port.d 


# Each subdirectory must supply rules for building sources it contributes
app/rtos/Source/portable/RVDS/ARM_CM4_MPU/port.o: ../app/rtos/Source/portable/RVDS/ARM_CM4_MPU/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --silent --no_wrap_diagnostics -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\hardware\kit\common\halconfig" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\hardware\kit\common\drivers" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\emlib\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\emdrv\sleep\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\emlib\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\hardware\kit\common\bsp" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\CMSIS\Include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\bluetooth\common\util" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\service\sleeptimer\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\halconfig\inc\hal-config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\Device\SiliconLabs\EFR32BG13P\Source\IAR" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\emdrv\sleep\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\bootloader\api" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\radio\rail_lib\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\emdrv\common\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\emdrv\uartdrv\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\radio\rail_lib\protocol\ble" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\service\sleeptimer\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\common\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\service\sleeptimer\config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\iar" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\platform\bootloader" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\system\core" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\system\interfaces" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\system\sysiocontroller" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\system\specific" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\system\types" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\application\tau" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\application" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\application\debug" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\global" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\peripherals" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\peripherals\drivers\hapticcontroller" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\peripherals\sensors\batterymonitor" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\peripherals\sensors\motionsensor" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\peripherals\sensors\rhoclient" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C12_master\app\peripherals\sensors\touchcontroller" -e --cpu Cortex-M4 --fpu VFPv4_sp --debug --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling '-DHAL_CONFIG=1' '-DEFR32BG13P632F512GM48=1' --diag_suppress pa050 --diag_error pe223 --no_path_in_file_macros --no_dwarf4 --dependencies=m app/rtos/Source/portable/RVDS/ARM_CM4_MPU/port.d
	@echo 'Finished building: $<'
	@echo ' '

