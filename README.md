# MSP430 Tools Linux


_rf2500
Muestras y POCs con la tarjeta RF2500


# Makefile
En este makefile esta la muestra para compilar y linkear el codigo que
esta en `main.c`.
Genera como salida el archivo `main.elf`
Para cargar este archivo en el uC es necesario usar `mspdebug` pero para 
esto es necesario tener permisos de root, por que se accesa al HW directamente


## Toolchain set up

Even when the official version of CSS does not support eZ430 in linux, what is
not supported is the flashing of the device, coding and compilation is possible.

### Set up `mspgcc`

Install the `mspgcc` tools which include the compiler, assembler and linker
plus the debugger and some other tools.

For fedora 30
```
dnf install mspdebug msp430-libc
dnf install msp430-gcc msp430-libc msp430mcu msp430-binutils
wget software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/latest/exports/msp430-gcc-support-files-1.207.zip 
```

### Flash

```
mspdebug uif
prog main.elf
```


Then download the tool chaing from TI: http://www.ti.com/tool/msp430-gcc-opensource
or the open source from sourceforge: https://sourceforge.net/projects/mspgcc/

Now a podman container will be created with this compiler added in. see [mspgcc_pod](./mspgcc_pod)
