APP=blinky_timer

all: clean comp


comp:
	/opt/msp/msp430-gcc/bin/msp430-elf-gcc -I/opt/msp/msp430-gcc-headers/include -Wl,-L/opt/msp/msp430-gcc-headers/include -mmcu=msp430f2274 -o ${APP}.elf ${APP}.c

clean:
	rm -rf ${APP}.elf

flash:
	sudo mspdebug uif
