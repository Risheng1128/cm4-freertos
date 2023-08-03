/**
 * @file   : link.ld
 * @brief  : Linker script for NUCLEO-F303ZE Board embedding STM32F303ZETx Device
 *           - 512Kbytes FLASH
 *           - 16Kbytes CCMRAM (No used)
 *           - 64Kbytes RAM
 */

/* entry point */
ENTRY(Reset_Handler)

/* highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* memory definition */
MEMORY
{
    RAM (xrw): ORIGIN = 0x20000000, LENGTH = 64K
    FLASH (rx): ORIGIN = 0x8000000, LENGTH = 512K
}

/* sections */
SECTIONS
{
    .text :
    {
        *(.isr_vector) /* vector table */
        *(.text)       /* code sections */
        *(.text.*)
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
        _etext = .;    /* end of text */
    } >FLASH

    _sidata = LOADADDR(.data);
    .data :
    {
        _sdata = .; /* start of data */
        *(.data)    /* data section */
        *(.data.*)
        . = ALIGN(4);
        _edata = .; /* end of data */
    } >RAM AT> FLASH

    .bss :
    {
        _sbss = .; /* start of bss */
        __bss_start__ = _sbss;
        *(.bss)    /* bss section */
        *(.bss.*)
        . = ALIGN(4);
        _ebss = .; /* end of bss */
        __bss_end__ = _ebss;
        . = ALIGN(4);
        end = .;
    } >RAM
}
