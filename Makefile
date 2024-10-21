PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
LD    = $(PREFIX)ld
CC    = $(PREFIX)gcc
GDB   = $(PREFIX)gdb

CFLAGS = -Wall -g -O1
TARGET_ARCH = -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb
LDFLAGS = -T ld_ram.lds
LDLIBS = -nostdlib

TARGET = main
SOURCES = main.c
OBJS = $(subst .c,.o,$(SOURCES)) crt0.o

all: $(OBJS) $(TARGET)

$(TARGET) : $(OBJS) $(LDS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

startgdbserver:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

# JLinkGDBServerExe:
# 	JLinkGDBServerExe -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug: 
	$(GDB) -x se203.gdb

clean : 
	rm -f *.o $(TARGET)
