MEMORY
 {
    Flash (rx) : ORIGIN = 0x08000000, LENGTH = 1M
    SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
    SRAM2 (rwx) : ORIGIN = 0x10000000, LENGTH = 32K
 }

SECTIONS
 {
    .vtor :{
        _vtor_LMA = LOADADDR(.vtor);
        _vtor = . ;
        KEEP(*(.vtor))
        _evtor = . ;
    } > SRAM1 AT > Flash
    
    .text.init :{
        _init = . ;
        KEEP(*(.text.init))
        _einit = . ;
    } > Flash

    .text :{
        _text_LMA = LOADADDR(.text);
        _text = . ;
        *(.text)
	    _etext = . ;
    } > SRAM1 AT > Flash

    .rodata :{
        _rodata = . ;
	    *(.rodata)
	    _erodata = .;
    } > Flash

    .data :{
        _data_LMA = LOADADDR(.data);
	    _data = . ;
        *(.data)
	    _edata = . ;
    } > SRAM1 AT > Flash

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

