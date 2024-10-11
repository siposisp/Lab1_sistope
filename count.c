#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "funcionescount.c"

//Bloque Principal
int main(int argc, char *argv[]) {
    printf("****************INICIO DEL PROGRAMA****************\n");

    // Variables para almacenar las opciones de línea de comandos
    char *archivoentrada = NULL;
    char cantidad_lineas = 0;
    char cantidad_caracteres = 0;
    int caracteres = 0;
    int lineas = 0;

    // Llamado de la funcion opciones
    opciones(argc, argv, &archivoentrada, &cantidad_caracteres, &cantidad_lineas);

    // Abrir el archivo de entrada
    FILE *archivo = procesar_archivo(archivoentrada);

    // Llamado de la funcion calculo
    calculo(archivo, cantidad_caracteres, cantidad_lineas, &caracteres, &lineas);

    // Cierre de archivo
    fclose(archivo);

    // Llamado de la funcion resultados
    resultados(lineas, caracteres, cantidad_lineas, cantidad_caracteres);

    printf("*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}