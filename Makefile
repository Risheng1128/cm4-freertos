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

CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = -mthumb $(CPU) $(FLOAT-ABI) $(FPU)

C_DEFS = -DUSE_HAL_DRIVER -DSTM32F303xE
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) -O3 -Wall -fdata-sections -ffunction-sections
CFLAGS += -g -gdwarf-2
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(notdir $(TARGET)).map,--cref -Wl,--gc-sections

LDSCRIPT = STM32F303ZETX_FLASH.ld # linker script
LIBS = -lc -lm -lnosys

OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(C_SOURCES))) 	# C code .o檔
vpath %.c $(dir $(C_SOURCES))
OBJECTS += $(patsubst %.s,$(BUILD_DIR)/%.o,$(notdir $(ASM_SOURCES)))  # ASM .o檔
vpath %.s $(dir $(ASM_SOURCES))

all: clean $(BUILD_DIR)/$(notdir $(TARGET)).elf
$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
$(BUILD_DIR)/%.o: %.s
	$(AS) -c $(CFLAGS) $< -o $@
$(BUILD_DIR)/$(notdir $(TARGET)).elf: $(BUILD_DIR) $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@
$(BUILD_DIR):
	mkdir $@

.PHONY: disassembly load upload clean
disassembly: $(BUILD_DIR)/$(notdir $(TARGET)).elf
	$(COMPILER)objdump.exe -d $^ > $(BUILD_DIR)/$(notdir $(TARGET)).S
load: 
	openocd -f board/st_nucleo_f3.cfg
upload:
	openocd -f interface/stlink.cfg -f target/stm32f3x.cfg -c " program $(BUILD_DIR)/$(notdir $(TARGET)).elf verify exit "
clean:
	@-rm -r $(BUILD_DIR)