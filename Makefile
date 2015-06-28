all: clean comp

comp:
	msp430-gcc -Iusr/msp430/include -mmcu=msp430f2274 -o main.elf main.c

clean:
	rm -rf *.elf

flash:
	sudo mspdebug uif
