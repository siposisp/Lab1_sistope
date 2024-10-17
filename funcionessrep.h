#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

// Entradas : Recibe los comandos de entrada
// Salida : void
// Descripción : Recibe los comandos de entrada, [-i archivoentrada] [o- archivosalida][-s] [-S] para realizar la lectura de comandos.
void opciones(int argc, char *argv[], char **archivoentrada, char **archivosalida,char **caracterAntiguo, char **caracterNuevo);

// Función para determinar si una subcadena está presente en una línea
int buscar_cadena_caracteres(const char* linea, const char* subcadena, int indice);

// Función para reemplazar subcadenas
char* reemplazar_caracter(char *linea, const char* caracterAntiguo, const char* caracterNuevo);

// Entradas: Recibe un char* correspondiente al nombre del archivo de output
// Salida: Retorna un elemento de tipo FILE correspondiente al archivo de salida
// Descripción: Verifica si el archivo de output existe, si existe lo limpia y si no existe lo crea y lo deja abierto
FILE* vaciar_archivo(char *nombreArchivo);

// Función para procesar el archivo
void procesar_archivo(char* filename, char* output_filename, char* caracterAntiguo, char* caracterNuevo);

