# Definerer værktøjer
AVR_GCC = avr-gcc
AVR_OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# MCU og programmeringsmetode
MCU = atmega328p
PROGRAMMER = arduino
PORT = /dev/tty.usbserial-110
F_CPU = 16000000UL

# Kilde- og objektfiler
SRC = main.c scenarios.c logic.c timer.c
OBJ = $(SRC:.c=.o)

# Header-filer
HEADERS = ports.h scenarios.h logic.h timer.h

# Output filer
ELF = trafficlight.elf
HEX = trafficlight.hex

# Kompileringsflaggene
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -I.

# Opsætning af mål
all: $(HEX)

# Kompilering af kildefiler til objektfiler
%.o: %.c $(HEADERS)
	$(AVR_GCC) $(CFLAGS) -c $< -o $@

# Linkning af objektfiler til en ELF-fil
$(ELF): $(OBJ)
	$(AVR_GCC) $(CFLAGS) -o $@ $(OBJ)

# Konvertering af ELF til HEX
$(HEX): $(ELF)
	$(AVR_OBJCOPY) -O ihex -R .eeprom $< $@

# Upload til Arduino
upload: $(HEX)
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -U flash:w:$<:i

# Ryd op
clean:
	rm -f $(OBJ) $(ELF) $(HEX)

.PHONY: all upload clean
