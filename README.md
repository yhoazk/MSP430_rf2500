# MSP430_rf2500
Muestras y POCs con la tarjeta RF2500


#Makefile
En este makefile esta la muestra para compilar y linkear el codigo que
esta en `main.c`.
Genera como salida el archivo `main.elf`
Para cargar este archivo en el uC es necesario usar `mspdebug` pero para 
esto es necesario tener permisos de root, por que se accesa al HW directamente

#main.c
Rutina sencilla para apagar y prender el led que esta en el P1.1

#NOTES
Se necesita especificar en el msp430-gcc el micro especifico, de lo contrario
no linkea bien, aun cuando en el main.c ya este el include con el numero
del micro seleccionado correctamente
