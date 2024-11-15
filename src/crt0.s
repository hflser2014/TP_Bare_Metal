  .syntax unified
  .arch armv7e-m
  .cpu cortex-m4
  .thumb

  .global _start
  .section .text.init
  .thumb_func
_start:
  ldr sp, =_estack @ Initialize the stack pointer
  bl init_memory   @ Initialize .bss; Copy .data, .text to RAM
  bl main
  b _exit          @ If main returns, go to a loop here to prevent undefined behavior

_exit:
  b _exit
