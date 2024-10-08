# Opciones de compilación
FLAGS = -Wall

# Nombre del ejecutable
TARGET = lab1

# Regla por defecto (la primera)
all: $(TARGET)

# Regla para enlazar el ejecutable
$(TARGET): lab1.c Particle.o funciones.o
	gcc $(FLAGS) -o $(TARGET) lab1.c Particle.o funciones.o -lm

# Regla para compilar los archivos fuente
Particle.o: Particle.c Particle.h
	gcc -c $(FLAGS) Particle.c

funciones.o: funciones.c funciones.h
	gcc -c $(FLAGS) funciones.c

# Regla para limpiar los archivos generados durante la compilación
clean:
	rm -f $(TARGET) *.o out*.txt
