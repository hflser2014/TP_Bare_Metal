.syntax unified
.arch armv7e-m
.cpu cortex-m4
.thumb

.global _start

_start:
  ldr sp, =_estack
  bl main
  b .
