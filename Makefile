# Default Variables (Can be overridden by projects)
MCU ?= atmega328p
F_CPU ?= 16000000UL
BAUD ?= 115200
PORT ?= /dev/ttyACM0
PROGRAMMER ?= arduino

# Compiler and Tools
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra $(EXTRA_FLAGS)
LDFLAGS = -mmcu=$(MCU)

# Files (Projects must define SRC and TARGET)
OBJ = $(SRC:.c=.o)
ELF = $(TARGET).elf
HEX = $(TARGET).hex

# Default Target: Compile Everything
all: $(HEX)

# Compile C file to Object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link Object file to ELF
$(ELF): $(OBJ)
	$(CC) $(LDFLAGS) $< -o $@

# Convert ELF to HEX
$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Flash to Arduino
flash: $(HEX)
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX):i

# Clean up
clean:
	rm -f $(OBJ) $(ELF) $(HEX)

