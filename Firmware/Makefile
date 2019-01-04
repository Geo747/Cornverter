# Copyright George Rennie 2018

# make all = Make software and program and upload
# make clean = Clean out built project files.
# make compile = Compile but not download
# To rebuild project do "make clean" then "make all".

# Setup Info
MCU = atmega328p
AVRDUDE_PROGRAMMER = arduino
AVRDUDE_PORT = COM4
AVRDUDE_BAUD_RATE = 57600

# Target file name (without extension).
TARGET_FN = MIDI_to_CV
# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
EXTRAINCDIRS = 

SRC_DIR = src/
BUILD_DIR = build/
BIN_DIR = bin/

############# Don't need to change below here for most purposes 

$(shell mkdir $(SRC_DIR))
$(shell mkdir $(BUILD_DIR))
$(shell mkdir $(BIN_DIR))

TARGET = $(BIN_DIR)$(TARGET_FN)
SRC_ADDRESSES = $(wildcard $(SRC_DIR)*.c)
SRC_FILES = $(SRC_ADDRESSES:$(SRC_DIR)%=%)

# Optimization level, can be [0, 1, 2, 3, s]. 0 turns off optimization.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# List C source files here. (C dependencies are automatically generated.)
SRC = $(addprefix $(SRC_DIR),$(SRC_FILES))
BUILD = $(addprefix $(BUILD_DIR),$(SRC_FILES))

# Optional compiler flags.
#  -g:        generate debugging information (for GDB, or for COFF conversion)
#  -O*:       optimization level
#  -f...:     tuning, see gcc manual and avr-libc documentation
#  -Wall...:  warning level
#  -Wa,...:   tell GCC to pass this to the assembler.
CFLAGS = -g -O$(OPT) \
-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
-Wall -Wstrict-prototypes \
-Wa, \
$(patsubst %,-I%,$(EXTRAINCDIRS))

CFLAGS += -std=gnu99

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep

AVRDUDE_FLAGS = -p$(MCU) -P$(AVRDUDE_PORT) -c$(AVRDUDE_PROGRAMMER) -b$(AVRDUDE_BAUD_RATE)

SHELL=C:/Windows/System32/cmd.exe

CC = avr-gcc

OBJCOPY = avr-objcopy

# Programming support using avrdude.
AVRDUDE = avrdude

REMOVE = rm -f

# Define all object files.
OBJ = $(BUILD:.c=.o)

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)

# Program the device.  
all: $(TARGET).hex $(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)

# Just compile
compile: $(TARGET).hex $(TARGET).eep

# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

# Create eep from elf
%.eep: %.elf
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $@

# Compile: create object files from C source files.
$(BUILD_DIR)%.o : $(SRC_DIR)%.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@

clean:
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(OBJ)
	$(REMOVE) *~

# Listing of phony targets.
.PHONY : all \
	clean program