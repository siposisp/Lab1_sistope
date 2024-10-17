#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "funcionescut.h"


int main(int argc, char *argv[])
{
    printf("****************INICIO DEL PROGRAMA****************\n\n");

    // Leer argumentos de la línea de comandos
    int option;
    char *archivoentrada = NULL;
    char *archivosalida = NULL;
    char separador = 't';
    char *columnas = NULL;

    //Se utiliza geopt para leer las opciones de línea de comandos
    while ((option = getopt(argc, argv, "i:o:d:c:")) != -1) {
        switch (option) {
            case 'd':
                separador = optarg[0]; //carácter separador de la columnas
                break;
            case 'c':
                columnas = optarg; //Indicar la o las columnas 
                break;
            case 'i':
                archivoentrada = optarg; //Nombre del archivo de entrada
                break;
            case 'o':
                archivosalida = optarg; //Nombre del archivo de salida
                break;
            default:
                fprintf(stderr, "Uso: %s [-d separador] [-c columnas]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    //Manejo de errores en el archivo
    if (archivoentrada == NULL) {
        // Si no se proporciona un archivo de entrada, pedir al usuario que ingrese el nombre
        char nombre_archivo[256];
        printf("Ingrese el nombre del archivo de entrada: ");
        
        if (fscanf(stdin, "%s", nombre_archivo) == 1) {  // Leer desde stdin
            archivoentrada = strdup(nombre_archivo); // Asignar el nombre del archivo a archivoentrada
        } else {
            fprintf(stderr, "Error al leer el nombre del archivo de entrada.\n");
            exit(EXIT_FAILURE);
        }
    }

    if(archivosalida != NULL){
        vaciar_archivo(archivosalida); //Se limpia el archivo de salida, si es que existe
    }
    

    if(columnas != NULL)
    {
        int cantidad_numeros = cantidad_de_numeros(columnas);
        if(cantidad_numeros==-1){
            exit(1);
        }
        int* arreglo_numeros = arreglo_char_to_int(columnas);

        procesar_archivo(archivoentrada, arreglo_numeros, cantidad_numeros, archivosalida, separador);

        free(arreglo_numeros);
    }
    else{
        reimprimir_archivo(archivoentrada,archivosalida);
    }


    printf("\n*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}
