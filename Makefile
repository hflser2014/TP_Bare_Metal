PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
LD    = $(PREFIX)ld
CC    = $(PREFIX)gcc
GDB   = $(PREFIX)gdb

INCLUDES = -I ./CMSIS/Include -I ./CMSIS/Device/ST/STM32L4xx/Include
CFLAGS = -Wall -g -O1 -ffreestanding $(INCLUDES)
TARGET_ARCH = -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb
LDFLAGS = -T ld_ram.lds
LDLIBS = -nostdlib

TARGET = main
SOURCES = main.c init.c memfuncs.c led.c
OBJS = $(subst .c,.o,$(SOURCES)) crt0.o clocks.o

all: $(OBJS) $(TARGET)

$(TARGET) : $(OBJS) $(LDS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

# Générer les fichiers indiquant les dépendances
-include $(subst .c,.d,$(SOURCES))
%.d : %.c
# Comme ces lignes ne sont pas inclues dans l'énoncé de l'exercice,
# on ajoute @ pour masquer l'affichage de ces commandes
	@$(CC) $(CFLAGS) $(CPPFLAGS)  -MM -MF $@ -MP $<


startgdbserver:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug: 
	$(GDB) -x se203.gdb

clean: 
	rm -f $(filter-out clocks.o, $(wildcard *.o)) *.d $(TARGET)
