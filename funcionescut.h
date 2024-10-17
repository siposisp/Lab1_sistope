#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

// Entradas: Recibe un char* (una palabra) y un char (un caracter)
// Salida: Retorna un char* (una palabra con el char concatenado)
// Descripción: Agrega un caracter a una palabra Ej: "hol"+ "a" resulta "hola"
char* concatenar_caracter(const char* palabra, char caracter);

// Entradas: Recibe un char* correspondiente a una linea del archivo
// Salida: Retorna un arreglo de char** correspondiente a una linea del archivo
// Descripción: transforma un linea leida del archivo a un arreglo separado por ":"
char** linea_a_arreglo(char* linea, char simbolo);


// Entradas: Recibe un char* correspondiente al nombre del archivo de output
// Salida: No retorna nada
// Descripción: Verifica si el archivo de output existe, si existe lo limpia y si no existe lo crea
void vaciar_archivo(char *nombreArchivo);


// Entradas: Recibe un char* correspondiente al nombre del archivo de output y un char* con el contenido de la linea a guardar en el archivo de salida
// Salida: No retorna nada
// Descripción: Abre el archivo y agrega una linea al final del archivo
void guardar_en_archivo(char *nombreArchivo, char* contenidoLinea);


// Función para verificar si un char está en un arreglo
int buscar_caracter_en_arreglo(char* arreglo, int tamano, char caracter);


void procesar_archivo(char* filename, int* columnas, int largoarreglo, char* archivosalida, char separador);


// Obtiene la cantidad de números que se pasan. Ej: 10,4,3,4,5,6 retorna 6
int cantidad_de_numeros(char* columnas);


//tranforma un arreglo de de numeros que está en formato char* a int* Ej: ["1","2","4"] -> [1,2,4]
int* arreglo_char_to_int(char* lista);


void reimprimir_archivo(char* filename, char* archivosalida);
