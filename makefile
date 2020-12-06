CC=avr-g++
MCU=m32u4
CCMCU=atmega32u4
LINKER=avr-objcopy
FLAGS=-mmcu=$(CCMCU) -std=gnu++17 -Os
OBJS=main.o I2C.o
MAIN=main.bin

all: clean $(OBJS) bin hex size

bin: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(MAIN)

hex: $(MAIN)
	$(LINKER) -j .text -j .data -O ihex $(MAIN) main.hex

%.o: %.cpp
	$(CC) $(FLAGS) -c $^ -o $@

burn: all
	avrdude -v -c usbasp -p $(MCU) -B 0.5 -U flash:w:main.hex:i 

size: $(MAIN)
	avr-size -C --mcu=$(CCMCU) $(MAIN)

clean:
	rm -rf *.hex *.bin *.o
