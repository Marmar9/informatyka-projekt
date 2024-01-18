CC = em++
CFLAGS = -s WASM=1 -s EXPORTED_FUNCTIONS="[ '_encryptRailFence', '_freeMemory', '_decryptRailFence']" -O3

TARGET = main
PUBLIC_DIR = ../public

all: $(PUBLIC_DIR)/$(TARGET).wasm

$(PUBLIC_DIR)/$(TARGET).wasm: $(TARGET).cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(PUBLIC_DIR)/$(TARGET).wasm