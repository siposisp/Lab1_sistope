#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    printf("****************INICIO DEL PROGRAMA***************\n\n");

    // Leer argumentos de la línea de comandos
    int option;
    char *archivoentrada = NULL;
    char *archivosalida = "output.txt";
    char *cantidad_lineas = 0;
    char *cantidad_caracteres = 0;
    FILE *archivo;

    //Se utiliza geopt para leer las opciones de línea de comandos
    while ((option = getopt(argc, argv, "i:C:L:")) != -1) {
        switch (option) {
            case 'i':
                archivoentrada = optarg; //Nombre del archivo de entrada
                break;
            case 'C':
                cantidad_caracteres = optarg; //Contar el número de caracteres
                break;
            case 'L':
                cantidad_lineas = optarg;//Contar el numero de líneas
                break;
            default:
                fprintf(stderr, "Uso: %s [-i archivoentrada] [-o archivosalida] [-d separador] [-c cantidad_caracteres]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    //Manejo de errores en el archivo
    if (archivoentrada == NULL){
        fprintf(stderr, "Debe ingresar el nombre para el archivo de entrada (-i). \n");
        exit(EXIT_FAILURE);
    }

    // Abrir el archivo de entrada
    archivo = fopen(archivoentrada, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo de entrada");
        exit(EXIT_FAILURE);
    }
    
    int caracteres = 0;
    int lineas = 0;
    char c;

    while((c=fgetc(archivo))!=EOF){
        if(cantidad_caracteres){
            caracteres++;
        }
        /*if(cantidad_lineas && c == '\n'){
            lineas++;
        }*/
    }

    while((caracteres=getchar())!=EOF){
        caracteres=cantidad_lineas;
        if(caracteres=='\n'){
            lineas++;
        }
    }


    fclose(archivo);
    //Este no
    if (cantidad_lineas) {
        printf("%d ", lineas);
    }
    //Este funciona
    if (cantidad_caracteres) {
        printf("%d", caracteres);
    }

    printf("\n*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}
