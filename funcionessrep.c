#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "funcionessrep.h"

// Función para determinar si una subcadena está presente en una línea
int buscar_cadena_caracteres(const char* linea, const char* subcadena, int indice) {
    int i = 0;
    while (subcadena[i] != '\0') {
        if (linea[indice + i] != subcadena[i]) {
            return 0;  // No coincide
        }
        i++;
    }
    return 1;  // Se encontró la subcadena
}

// Función para reemplazar subcadenas
char* reemplazar_caracter(char *linea, const char* caracterAntiguo, const char* caracterNuevo) {
    static char nuevaLinea[1024];  // Buffer para la nueva línea
    int i = 0, j = 0, k;
    int longitudAntigua = 0;
    int longitudNueva = 0;

    // Calcular la longitud del antiguo caracter
    while (caracterAntiguo[longitudAntigua] != '\0') {
        longitudAntigua++;
    }

    // Calcular la longitud del nuevo caracter
    while (caracterNuevo[longitudNueva] != '\0') {
        longitudNueva++;
    }

    // Procesar la línea para buscar y reemplazar la subcadena
    while (linea[i] != '\0') {
        if (buscar_cadena_caracteres(linea, caracterAntiguo, i)) {
            // Copiar la subcadena nueva en la nueva línea
            for (k = 0; k < longitudNueva; k++) {
                nuevaLinea[j++] = caracterNuevo[k];
            }
            // Saltar la longitud del caracter antiguo en la línea original
            i += longitudAntigua;
        } else {
            // Si no se encuentran los caracteres, copiar el carácter original
            nuevaLinea[j++] = linea[i++];
        }
    }
    nuevaLinea[j] = '\0';  // 
    return nuevaLinea;
}

// Entradas: Recibe un char* correspondiente al nombre del archivo de output
// Salida: Retorna un elemento de tipo FILE correspondiente al archivo de salida
// Descripción: Verifica si el archivo de output existe, si existe lo limpia y si no existe lo crea y lo deja abierto
FILE* vaciar_archivo(char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "w");

    // Verificar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
    }

    return archivo;
}

// Función para procesar el archivo
void procesar_archivo(char* filename, char* output_filename, char* caracterAntiguo, char* caracterNuevo) {
    int contador = 0;
    char linea[1024];

    // Abrir el archivo en modo lectura
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de entrada.\n");
        return;
    }

    FILE* output_file;
    if (output_filename != NULL) {
        output_file = fopen(output_filename, "w");
        if (output_file == NULL) {
            printf("Error al abrir el archivo de salida.\n");
            fclose(file);
            return;
        }
    } else {
        output_file = stdout;  // Si no se proporciona archivo, se usa la consola
    }

    // Leer línea por línea el archivo de entrada
    while (fgets(linea, sizeof(linea), file)) {
        char *linea_nueva = reemplazar_caracter(linea, caracterAntiguo, caracterNuevo);
        fprintf(output_file, "%s", linea_nueva);  
        contador++;
    }

    // Cerrar los archivos si es necesario
    fclose(file);
    if (output_file != stdout) {
        fclose(output_file);
    }

    printf("Archivo procesado....\nSe escribieron %d lineas.\n", contador);
}


