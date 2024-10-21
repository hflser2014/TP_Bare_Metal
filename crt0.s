  .syntax unified
  .arch armv7e-m
  .cpu cortex-m4
  .thumb

  .global _start

_start:
  ldr sp, =_estack
  bl init_bss
  bl main
  b .
