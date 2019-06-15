all: clean comp

comp:
	msp430-elf-gcc -I/opt/msp_gcc/include -Wl,-L/opt/msp_gcc/include -mmcu=msp430f2274 -o main.elf main.c

clean:
	rm -rf *.elf

flash:
	sudo mspdebug uif
