# ------------------------------------------------
# Generic Makefile
# 
# Author: Ri-Sheng Chen
# ------------------------------------------------

include makefile.rule

COMPILER = arm-none-eabi-
CC = $(COMPILER)gcc
AS = $(COMPILER)gcc -x assembler-with-cpp
SZ = $(COMPILER)size
MCU = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16

LDSCRIPT = STM32F303ZETX_FLASH.ld
CFLAGS = $(MCU) $(C_INCLUDES) -O3 -Wall -g
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) -lc -lm -lnosys

OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(C_SOURCES)))
vpath %.c $(dir $(C_SOURCES))
OBJECTS += $(patsubst %.s,$(BUILD_DIR)/%.o,$(notdir $(ASM_SOURCES)))
vpath %.s $(dir $(ASM_SOURCES))

all: clean $(BUILD_DIR)/$(notdir $(TARGET)).elf
$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
$(BUILD_DIR)/%.o: %.s
	$(AS) -c $(CFLAGS) $< -o $@
$(BUILD_DIR)/$(notdir $(TARGET)).elf: $(BUILD_DIR) $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@
$(BUILD_DIR):
	mkdir $@

.PHONY: disassembly load upload clean
disassembly: $(BUILD_DIR)/$(notdir $(TARGET)).elf
	$(COMPILER)objdump -d $^ > $(BUILD_DIR)/$(notdir $(TARGET)).S
load: 
	openocd -f board/st_nucleo_f3.cfg
upload:
	openocd -f interface/stlink-v2-1.cfg -f target/stm32f3x.cfg -c " program $(BUILD_DIR)/$(notdir $(TARGET)).elf verify exit "
clean:
	@-rm -r $(BUILD_DIR)