#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "funcionessrep.h"

// Función opciones
// Entradas : Recibe los comandos de entrada
// Salida : void
// Descripción : Recibe los comandos de entrada, [-i archivoentrada] [o- archivosalida][-s] [-S] para realizar la lectura de comandos.
void opciones(int argc, char *argv[], char **archivoentrada, char **archivosalida,char **caracterAntiguo, char **caracterNuevo) {
   int option;
   while ((option = getopt(argc, argv, "i:o:s:S:")) != -1) {
        switch (option) {
            case 's':
                *caracterAntiguo = optarg;  // Strings antiguos a buscar
                break;
            case 'S':
                *caracterNuevo = optarg;  //  Strings nuevos para reemplazar
                break;
            case 'i':
                *archivoentrada = optarg;  // Nombre del archivo de entrada
                break;
            case 'o':
                *archivosalida = optarg;  // Nombre del archivo de salida
                break;
            default:
                fprintf(stderr, "Uso: %s [-i archivoentrada] [-o archivosalida] [-s StringsAntiguos] [-S StringsNuevos]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    //Manejo de errores en el archivo
    if (*archivoentrada == NULL) {
        fprintf(stderr, "Debe ingresar el nombre para el archivo de entrada (-i).\n");
        exit(EXIT_FAILURE);
    }
     if (*archivosalida == NULL) {
        fprintf(stderr, "Debe ingresar el nombre del archivo de salida (-o).\n");
        exit(EXIT_FAILURE);
    }
    if (*caracterAntiguo == NULL || *caracterNuevo == NULL) {
        fprintf(stderr, "Debe ingresar los Strings antiguos (-s) y los Strings nuevos (-S).\n");
        exit(EXIT_FAILURE);
    }

}

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

    FILE* output_file = vaciar_archivo(output_filename); //Se limpia el archivo de salida, si es que existe, sino se crea


    // Leer línea por línea el archivo de entrada
    while (fgets(linea, sizeof(linea), file)) {
        char *linea_nueva= reemplazar_caracter(linea, caracterAntiguo, caracterNuevo);
        fprintf(output_file, "%s", linea_nueva);  
        contador++;
    }
    // Cerrar los archivos
    fclose(file);
    fclose(output_file);

    printf("Archivo procesado....\nSe escribieron %d lineas en el archivo de salida.\n", contador);
}


