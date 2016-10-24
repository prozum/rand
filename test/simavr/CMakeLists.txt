add_subdirectory(avr)
add_library(simavr avr_adc.h avr_bitbang.h avr_eeprom.h avr_extint.h
            avr_flash.h avr_ioport.h avr_uart.h sim_avr.h sim_io.h
            sim_elf.h sim_irq.h sim_regbit.h avr/avr_mcu_section.h libsimavr.a)
set_target_properties(simavr PROPERTIES LINKER_LANGUAGE CXX)