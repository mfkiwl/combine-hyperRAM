################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/micrium_os/common/source/lib/lib_ascii.c \
../platform/micrium_os/common/source/lib/lib_math.c \
../platform/micrium_os/common/source/lib/lib_mem.c \
../platform/micrium_os/common/source/lib/lib_str.c 

OBJS += \
./platform/micrium_os/common/source/lib/lib_ascii.o \
./platform/micrium_os/common/source/lib/lib_math.o \
./platform/micrium_os/common/source/lib/lib_mem.o \
./platform/micrium_os/common/source/lib/lib_str.o 

C_DEPS += \
./platform/micrium_os/common/source/lib/lib_ascii.d \
./platform/micrium_os/common/source/lib/lib_math.d \
./platform/micrium_os/common/source/lib/lib_mem.d \
./platform/micrium_os/common/source/lib/lib_str.d 


# Each subdirectory must supply rules for building sources it contributes
platform/micrium_os/common/source/lib/lib_ascii.o: ../platform/micrium_os/common/source/lib/lib_ascii.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --silent --no_wrap_diagnostics -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emlib\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emlib\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\halconfig" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\CMSIS\Include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\uartdrv\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\ring_buf" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\cpu\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\tempdrv\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\bsp" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\bootloader\api" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\logging" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\common\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\lib" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\drivers" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\kernel\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\protocol\ble" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\sleep\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\cpu\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\rtos" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\sleep\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\collections" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\bsp\siliconlabs\generic\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\kernel\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\app\bluetooth\common\util" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\common\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\ports\source\iar" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\platform_mgr" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Source\IAR" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\halconfig\inc\hal-config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\kal" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\common\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\bsp\siliconlabs\generic\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\preprocessor" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\src\soc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\iar" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os" -e --cpu Cortex-M4 --fpu VFPv4_sp --debug --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling '-D__StackLimit=0x20000000' '-DHAL_CONFIG=1' '-D__STACK_SIZE=0x800' '-DEFR32BG13P632F512GM48=1' --diag_suppress pa050 --diag_error pe223 --no_path_in_file_macros --no_dwarf4 --dependencies=m platform/micrium_os/common/source/lib/lib_ascii.d
	@echo 'Finished building: $<'
	@echo ' '

platform/micrium_os/common/source/lib/lib_math.o: ../platform/micrium_os/common/source/lib/lib_math.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --silent --no_wrap_diagnostics -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emlib\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emlib\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\halconfig" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\CMSIS\Include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\uartdrv\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\ring_buf" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\cpu\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\tempdrv\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\bsp" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\bootloader\api" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\logging" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\common\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\lib" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\drivers" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\kernel\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\protocol\ble" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\sleep\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\cpu\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\rtos" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\sleep\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\collections" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\bsp\siliconlabs\generic\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\kernel\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\app\bluetooth\common\util" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\common\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\ports\source\iar" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\platform_mgr" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Source\IAR" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\halconfig\inc\hal-config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\kal" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\common\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\bsp\siliconlabs\generic\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\preprocessor" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\src\soc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\iar" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os" -e --cpu Cortex-M4 --fpu VFPv4_sp --debug --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling '-D__StackLimit=0x20000000' '-DHAL_CONFIG=1' '-D__STACK_SIZE=0x800' '-DEFR32BG13P632F512GM48=1' --diag_suppress pa050 --diag_error pe223 --no_path_in_file_macros --no_dwarf4 --dependencies=m platform/micrium_os/common/source/lib/lib_math.d
	@echo 'Finished building: $<'
	@echo ' '

platform/micrium_os/common/source/lib/lib_mem.o: ../platform/micrium_os/common/source/lib/lib_mem.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --silent --no_wrap_diagnostics -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emlib\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emlib\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\halconfig" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\CMSIS\Include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\uartdrv\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\ring_buf" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\cpu\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\tempdrv\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\bsp" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\bootloader\api" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\logging" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\common\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\lib" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\drivers" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\kernel\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\protocol\ble" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\sleep\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\cpu\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\rtos" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\sleep\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\collections" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\bsp\siliconlabs\generic\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\kernel\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\app\bluetooth\common\util" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\common\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\ports\source\iar" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\platform_mgr" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Source\IAR" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\halconfig\inc\hal-config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\kal" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\common\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\bsp\siliconlabs\generic\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\preprocessor" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\src\soc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\iar" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os" -e --cpu Cortex-M4 --fpu VFPv4_sp --debug --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling '-D__StackLimit=0x20000000' '-DHAL_CONFIG=1' '-D__STACK_SIZE=0x800' '-DEFR32BG13P632F512GM48=1' --diag_suppress pa050 --diag_error pe223 --no_path_in_file_macros --no_dwarf4 --dependencies=m platform/micrium_os/common/source/lib/lib_mem.d
	@echo 'Finished building: $<'
	@echo ' '

platform/micrium_os/common/source/lib/lib_str.o: ../platform/micrium_os/common/source/lib/lib_str.c
	@echo 'Building file: $<'
	@echo 'Invoking: IAR C/C++ Compiler for ARM'
	iccarm "$<" -o "$@" --silent --no_wrap_diagnostics -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emlib\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emlib\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\halconfig" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\CMSIS\Include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\uartdrv\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\ring_buf" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\cpu\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\tempdrv\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\bsp" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\bootloader\api" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\logging" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\common\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\lib" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\hardware\kit\common\drivers" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\kernel\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\protocol\ble" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\sleep\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\cpu\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\rtos" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\sleep\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\collections" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\bsp\siliconlabs\generic\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\kernel\include" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\app\bluetooth\common\util" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\common\src" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\common" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\ports\source\iar" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\platform_mgr" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\Device\SiliconLabs\EFR32BG13P\Source\IAR" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\halconfig\inc\hal-config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\kal" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\emdrv\common\inc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\bsp\siliconlabs\generic\source" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os\common\source\preprocessor" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\service\sleeptimer\config" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\protocol\bluetooth\ble_stack\src\soc" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\iar" -I"C:\Users\Matthew Fonken\Desktop\marbl\Techincal\combine\master\C13_master\platform\micrium_os" -e --cpu Cortex-M4 --fpu VFPv4_sp --debug --endian little --cpu_mode thumb -On --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering --no_scheduling '-D__StackLimit=0x20000000' '-DHAL_CONFIG=1' '-D__STACK_SIZE=0x800' '-DEFR32BG13P632F512GM48=1' --diag_suppress pa050 --diag_error pe223 --no_path_in_file_macros --no_dwarf4 --dependencies=m platform/micrium_os/common/source/lib/lib_str.d
	@echo 'Finished building: $<'
	@echo ' '


