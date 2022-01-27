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
LDFLAGS = $(MCU) -T$(LDSCRIPT) -nostdlib -lc -lm

VPATH = $(dir $(C_SRCS))
OBJS = $(patsubst %.c, $(OUT)/%.o, $(notdir $(C_SRCS)))

all: $(OUT)/$(BIN)
# compile
$(OUT)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# link
$(OUT)/$(BIN): $(OUT) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SZ) $@

$(OUT):
	echo $(VPATH)
	mkdir $@

.PHONY: upload clean
upload:
	openocd -f interface/stlink-v2-1.cfg -f target/stm32f3x.cfg -c " program $(OUT)/$(BIN) verify exit "

clean:
	@-rm -r $(OUT)