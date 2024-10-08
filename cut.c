#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    printf("****************INICIO DEL PROGRAMA****************\n");

    // Leer argumentos de la línea de comandos
    int option;
    char *archivoentrada = NULL;
    char *archivosalida = NULL;
    char *separador = NULL;
    char *columnas = NULL;

    //Se utiliza geopt para leer las opciones de línea de comandos
    while ((option = getopt(argc, argv, "d:c:i:o:")) != -1) {
        switch (option) {
            case 'd':
                separador = optarg; //carácter separador de la columnas
                break;
            case 'c':
                columnas = optarg; //Indicar la o las columnas OOOOOOOOOJOOOOOOOOOOOOOOOOOO QUE SI NO INDICA DEBEN IMPRIMIRSE TODAS
                break;
            case 'i':
                archivoentrada = optarg; //Nombre del archivo de entrada
                break;
            case 'o':
                archivosalida = optarg; //Nombre del archivo de salida
                break;
            default:
                fprintf(stderr, "Uso: %s [-i archivoentrada] [-o archivosalida] [-d separador] [-c columnas]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    //Manejo de errores en el archivo
    if (archivoentrada == NULL){
        fprintf(stderr, "Debe ingresar el nombre para el archivo de entrada (-i). \n");
        exit(EXIT_FAILURE);
    }

    printf("*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}
