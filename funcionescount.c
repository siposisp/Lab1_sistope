#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

// Función opciones
// Entradas : Recibe los comandos de entrada
// Salida : void
// Descripción : Recibe los comandos de entrada, [-i archivoentrada] [-L] [-C] para realizar la lectura de comandos.
void opciones(int argc, char *argv[], char **archivoentrada, char *cantidad_caracteres, char *cantidad_lineas) {
    int option;
    while ((option = getopt(argc, argv, "i:CL")) != -1) {
        switch (option) {
            case 'i':
                *archivoentrada = optarg; // Nombre del archivo de entrada
                break;
            case 'C':
                *cantidad_caracteres = 1; // Contar el número de caracteres
                break;
            case 'L':
                *cantidad_lineas = 1; // Contar el número de líneas
                break;
            default:
                fprintf(stderr, "Uso: %s [-i archivoentrada] [-L] [-C]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    //Manejo de errores en el archivo
    if (*archivoentrada == NULL) {
        fprintf(stderr, "Debe ingresar el nombre para el archivo de entrada (-i).\n");
        exit(EXIT_FAILURE);
    }
}

// Función procesar_archivo
// Entradas : Recibe como char el nombre del archivo.
// Salida : archivo.
// Descripción : Funcion que permite abrir un archivo en modo "r".
FILE* procesar_archivo(char *archivoentrada) {
    FILE *archivo = fopen(archivoentrada, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo de entrada");
        exit(EXIT_FAILURE);
    }
    return archivo;
}

// Función calculo
// Entradas : Recibe el archivo, cantidad_caracteres(char), cantidad_lineas(char), caracteres(int), lineas(int)
// Salida : void.
// Descripción : Funcion que calcula la cantidad de caracteres de un archivo y la cantidad de lineas que posee el mismo archivo.
void calculo(FILE *archivo, char cantidad_caracteres, char cantidad_lineas, int *caracteres, int *lineas) {
    char c;
    while ((c = fgetc(archivo)) != EOF) {
        if (cantidad_caracteres) {
            (*caracteres)++;
        }
        if (cantidad_lineas && c == '\n') {
            (*lineas)++;
        }
    }
}

// Función resultados
// Entradas : Recibe como variable: lineas(int), caracteres(int), cantidad_lineas(char), cantidad_caracteres(char)
// Salida : void.
// Descripción : Funcion que imprime los resultados
void resultados(int lineas, int caracteres, char cantidad_lineas, char cantidad_caracteres) {
    if (cantidad_lineas && cantidad_caracteres) {
        printf("%d %d\n", lineas, caracteres);   //Imprimir la cantidad de líneas y caracteres
    } else if (cantidad_lineas) {
        printf("%d\n", lineas); // Imprimir la cantidad de líneas
    } else if (cantidad_caracteres) {
        printf("%d\n", caracteres); // Imprimir la cantidad de caracteres
    }
}