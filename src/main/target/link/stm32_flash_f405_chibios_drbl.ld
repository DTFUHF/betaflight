/*
*****************************************************************************
**
**  File        : stm32_flash_f405_chibios_drbl.ld
**
**  Abstract    : Linker script for STM32F405 Device with
**                1024KByte FLASH, 128KByte RAM
**
*****************************************************************************
*/

/* Entry Point */
ENTRY(ResetHandler)

/*
0x08000000 to 0x08100000 1024K full flash,
0x08000000 to 0x08007FFF 32kb dRonin BL / empty
0x08008000 to 0x0801FFFF 96kb settings
0x08020000 to 0x0807FFFF 384kb firmware
*/

__main_stack_size__     = 0x0F00;
__process_stack_size__  = 0x0400;

/*    FLASH (rx)      : ORIGIN = 0x08020000, LENGTH = 384K */

/* Specify the memory areas */
MEMORY
{
    FLASH (rx)      : ORIGIN = 0x08020000, LENGTH = 384K
    RAM (rwx)       : ORIGIN = 0x20000000, LENGTH = 128K
    MEMORY_B1 (rx)  : ORIGIN = 0x60000000, LENGTH = 0K
    ram1            : ORIGIN = 0x00000000, LENGTH = 0
    ram2            : ORIGIN = 0x00000000, LENGTH = 0
    ram3            : ORIGIN = 0x00000000, LENGTH = 0
    ram4            : ORIGIN = 0x00000000, LENGTH = 0
    ram5            : ORIGIN = 0x00000000, LENGTH = 0
    ram6            : ORIGIN = 0x00000000, LENGTH = 0
    ram7            : ORIGIN = 0x00000000, LENGTH = 0
}

/* RAM region to be used for Main stack. This stack accommodates the processing
   of all exceptions and interrupts*/
REGION_ALIAS("MAIN_STACK_RAM", RAM);

/* RAM region to be used for the process stack. This is the stack used by
   the main() function.*/
REGION_ALIAS("PROCESS_STACK_RAM", RAM);

/* RAM region to be used for data segment.*/
REGION_ALIAS("DATA_RAM", RAM);

/* RAM region to be used for BSS segment.*/
REGION_ALIAS("BSS_RAM", RAM);

/* RAM region to be used for the default heap.*/
REGION_ALIAS("HEAP_RAM", RAM);

REGION_ALIAS("STACKRAM", RAM)

INCLUDE "stm32f405xg_chibios_sections.ld"
