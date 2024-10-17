FLAGS = -Wall

all: cut count srep

# Regla para cut
cut: cut.o funcionescut.o
	gcc $(FLAGS) -o cut cut.o funcionescut.o

cut.o: cut.c funcionescut.h
	gcc $(FLAGS) -c cut.c

funcionescut.o: funcionescut.c funcionescut.h
	gcc $(FLAGS) -c funcionescut.c

# Regla para count
count: count.o
	gcc $(FLAGS) -o count count.o

count.o: count.c
	gcc $(FLAGS) -c count.c

# Regla para srep
srep: srep.o
	gcc $(FLAGS) -o srep srep.o

srep.o: srep.c
	gcc $(FLAGS) -c srep.c

# Limpiar archivos generados
clear:
	rm -f cut count srep *.o