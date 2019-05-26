all: clean comp

comp:
	/opt/msp/msp430-gcc/bin/msp430-elf-gcc -I/opt/msp/msp430-gcc-headers/include -Wl,-L/opt/msp/msp430-gcc-headers/include -mmcu=msp430f2274 -o main.elf main.c

clean:
	rm -rf *.elf

flash:
	sudo mspdebug uif
