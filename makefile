CC=avr-g++
MCU=atmega32u4
LINKER=avr-objcopy
FLAGS=-mmcu=$(MCU) -std=gnu++17 -Os
OBJS=main.o MSB.o I2C.o
MAIN=main.bin

all: clean $(OBJS) bin hex size

bin: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(MAIN)

hex: $(MAIN)
	$(LINKER) -R eeprom -O ihex $(MAIN) main.hex

%.o: %.cpp
	$(CC) $(FLAGS) -c $^ -o $@

burn: all
	avrdude -c usbasp -p $(MCU) -B 0.5 -U flash:w:main.hex:i 

size: $(MAIN)
	avr-size -C --mcu=$(MCU) $(MAIN)

clean:
	rm -rf *.hex *.bin *.o
