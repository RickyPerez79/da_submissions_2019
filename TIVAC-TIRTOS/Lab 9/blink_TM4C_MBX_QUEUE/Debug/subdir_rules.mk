################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1525282577:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1525282577-inproc

build-1525282577-inproc: ../empty.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_32_00_06_core/xs" --xdcpath="C:/ti/tirtos_tivac_2_16_00_08/packages;C:/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages;C:/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages;C:/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages;C:/ti/tirtos_tivac_2_16_00_08/products/uia_2_00_05_50/packages;C:/ti/tirtos_tivac_2_16_00_08/products/ns_1_11_00_10/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.tiva:TM4C123GH6PM -r release -c "C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS" --compileOptions "-mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path=\"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include\" --include_path=\"C:/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b\" --define=PART_TM4C123GH6PM --define=ccs --define=TIVAWARE --define=ccs=\"ccs\" -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1525282577 ../empty.cfg
configPkg/compiler.opt: build-1525282577
configPkg/: build-1525282577

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS/include" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --define=PART_TM4C123GH6PM --define=ccs --define=TIVAWARE --define=ccs="ccs" -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


