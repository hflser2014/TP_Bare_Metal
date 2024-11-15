MEMORY
 {
    Flash (rx) : ORIGIN = 0x08000000, LENGTH = 1M
    SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
    SRAM2 (rwx) : ORIGIN = 0x10000000, LENGTH = 32K
 }

SECTIONS
 {
    .vtor :{
        KEEP(*(.vtor))
    } > Flash 

    .text :{
        *(.text)
	    _etext = . ;
    } > Flash

    .rodata :{
        _rodata = . ;
	    *(.rodata)
	    _erodata = .;
    } > Flash

    .data :{
	    _data = . ;
        *(.data)
	    _edata = . ;
    } > SRAM1

    .bss :{
	    _bstart = . ;
        *(.bss) *(COMMON)
	    _bend = . ;
    } > SRAM1
    
    .stack :{
        _stack = . ;
        _estack = _stack + LENGTH(SRAM2) ;
    } > SRAM2
 }

ENTRY(_start)

