#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

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