V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: balatro64.z64
.PHONY: all

OBJS = $(BUILD_DIR)/main.o

balatro64.z64: N64_ROM_TITLE="Balatro64"

$(BUILD_DIR)/balatro64.elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)