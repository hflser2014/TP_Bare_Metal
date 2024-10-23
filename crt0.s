  .syntax unified
  .arch armv7e-m
  .cpu cortex-m4
  .thumb

  .global _start

_start:
  ldr sp, =_estack @ Initialize the stack pointer
  bl init_bss      @ Initialize the .bss section
  bl main
  b _exit          @ If main returns, go to a loop here to prevent undefined behavior

_exit:
  b .
