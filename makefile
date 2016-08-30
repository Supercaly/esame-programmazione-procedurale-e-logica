numeri_complessi: programma.o libreria_complessi.o makefile
	gcc -ansi -Wall -O programma.o libreria_complessi.o -o numeri_complessi -lm
programma.o: programma.c makefile
	gcc -ansi -Wall -O -c programma.c 
libreria_complessi.o: libreria_complessi.c makefile
	gcc -ansi -Wall -O -c libreria_complessi.c
clear: programma.o libreria_complessi.o -lm
	rm -f programma.o libreria_complessi.o
clear_all: programma.o libreria_complessi.o numeri_complessi
	rm -f programma.o libreria_complessi.o numeri_complessi
