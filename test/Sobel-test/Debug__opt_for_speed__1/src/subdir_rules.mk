################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/fuzzy.obj: C:/Users/lucas/lab_sisem/src/fuzzy.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=1 --use_hw_mpy=none --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/lab_sisem/include" --include_path="C:/Users/lucas/lab_sisem/test/Sobel-test" --include_path="C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/ports_init.obj: C:/Users/lucas/lab_sisem/src/ports_init.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=1 --use_hw_mpy=none --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/lab_sisem/include" --include_path="C:/Users/lucas/lab_sisem/test/Sobel-test" --include_path="C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/queue.obj: C:/Users/lucas/lab_sisem/src/queue.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=1 --use_hw_mpy=none --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/lab_sisem/include" --include_path="C:/Users/lucas/lab_sisem/test/Sobel-test" --include_path="C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/sobel.obj: C:/Users/lucas/lab_sisem/src/sobel.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=1 --use_hw_mpy=none --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/lab_sisem/include" --include_path="C:/Users/lucas/lab_sisem/test/Sobel-test" --include_path="C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/temp.obj: C:/Users/lucas/lab_sisem/src/temp.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=1 --use_hw_mpy=none --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/lab_sisem/include" --include_path="C:/Users/lucas/lab_sisem/test/Sobel-test" --include_path="C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/temperatura.obj: C:/Users/lucas/lab_sisem/src/temperatura.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=1 --use_hw_mpy=none --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/lab_sisem/include" --include_path="C:/Users/lucas/lab_sisem/test/Sobel-test" --include_path="C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/timer.obj: C:/Users/lucas/lab_sisem/src/timer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=1 --use_hw_mpy=none --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/lab_sisem/include" --include_path="C:/Users/lucas/lab_sisem/test/Sobel-test" --include_path="C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/timer_hw.obj: C:/Users/lucas/lab_sisem/src/timer_hw.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=1 --use_hw_mpy=none --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/lab_sisem/include" --include_path="C:/Users/lucas/lab_sisem/test/Sobel-test" --include_path="C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/uart.obj: C:/Users/lucas/lab_sisem/src/uart.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=1 --use_hw_mpy=none --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/lab_sisem/include" --include_path="C:/Users/lucas/lab_sisem/test/Sobel-test" --include_path="C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/utils.obj: C:/Users/lucas/lab_sisem/src/utils.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --opt_for_speed=1 --use_hw_mpy=none --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/ti/ccs/ccs_base/msp430/include" --include_path="C:/Users/lucas/lab_sisem/include" --include_path="C:/Users/lucas/lab_sisem/test/Sobel-test" --include_path="C:/Users/lucas/ti/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


