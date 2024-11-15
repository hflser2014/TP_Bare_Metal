PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
LD    = $(PREFIX)ld
CC    = $(PREFIX)gcc
GDB   = $(PREFIX)gdb

INCLUDES = -I ./CMSIS/Include -I ./CMSIS/Device/ST/STM32L4xx/Include -I ./Include
CFLAGS = -Wall -g -O1 -ffreestanding $(INCLUDES)
TARGET_ARCH = -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb
LDFLAGS = -T ld_ram.lds
LDLIBS = -nostdlib

BUILD_DIR = build
SRC_DIR = src
TARGET = $(BUILD_DIR)/main.elf

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) $(BUILD_DIR)/crt0.o $(BUILD_DIR)/image.o
DEPENDENCIES = $(addprefix $(BUILD_DIR),$(OBJS:.o=.d))

all: $(BUILD_DIR) $(OBJS) $(TARGET) 

$(TARGET) : $(OBJS) $(LDS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Générer les fichiers indiquant les dépendances
-include $(subst .c,.d,$(SRCS))
%.d : %.c
# Comme ces lignes ne sont pas inclues dans l'énoncé de l'exercice,
# on ajoute @ pour masquer l'affichage de ces commandes
	@$(CC) $(CFLAGS) $(CPPFLAGS)  -MM -MF $@ -MP $<

# The Makefile became more complex, but the folder structure is more clear
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(TARGET_ARCH) -c $< -o $@

$(BUILD_DIR)/crt0.o: $(SRC_DIR)/crt0.s
	$(AS) $(TARGET_ARCH) $< -o $@

$(BUILD_DIR)/image.o: image.raw
	$(PREFIX)objcopy -I binary -O elf32-littlearm -B arm $< $@

startgdbserver:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug: $(TARGET) 
	$(GDB) -x se203.gdb $<

clean:
	rm -rf $(BUILD_DIR) 
	rm -f $(SRC_DIR)/*.d $(TARGET)
