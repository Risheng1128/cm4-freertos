# Generic Makefile

-include makefile.rule

# toolchain
TOOLCHAIN = arm-none-eabi-
CC = $(TOOLCHAIN)gcc
DUMP = $(TOOLCHAIN)objdump
SZ = $(TOOLCHAIN)size

# toolchain options
MCU = -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS = $(MCU) -mthumb $(C_INCS) -O0 -Wall -g
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) -lc -lm -lnosys

VPATH = $(dir $(C_SRCS))
VPATH += $(dir $(ASM_SRCS))

OBJS = $(patsubst %.c, $(OUT)/%.o, $(notdir $(C_SRCS)))
OBJS += $(patsubst %.S, $(OUT)/%.o, $(notdir $(ASM_SRCS)))

all: patch $(OUT)/$(BIN)
# compile
$(OUT)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
$(OUT)/%.o: %.S
	$(CC) -c $(CFLAGS) $< -o $@

# link
$(OUT)/$(BIN): $(OUT) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SZ) $@

$(OUT):
	mkdir $@

.PHONY: patch upload clean
# update patches about freertos and systemview
patch:
	-git apply --directory=$(FREERTOS)/ $(FREERTOS_PATCH) 2>/dev/null
	-git apply --directory=$(SYSTEMVIEW)/ $(SYSTEMVIEW_PATCH) 2>/dev/null

upload:
	openocd -f interface/stlink-v2-1.cfg -f target/stm32f3x.cfg -c " program $(OUT)/$(BIN) verify exit "

clean:
	@-rm -r $(OUT)