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
    char cantidad_lineas = 0;
    char cantidad_caracteres = 0;
    FILE *archivo;

    //Se utiliza geopt para leer las opciones de línea de comandos
    while ((option = getopt(argc, argv, "i:CL")) != -1) {
        switch (option) {
            case 'i':
                archivoentrada = optarg; //Nombre del archivo de entrada
                break;
            case 'C':
                cantidad_caracteres = 1; //Contar el número de caracteres
                break;
            case 'L':
                cantidad_lineas = 1;//Contar el numero de líneas
                break;
            default:
                fprintf(stderr, "Uso: %s [-i archivoentrada] [-L][-C]\n", argv[0]);
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

     // Imprimo los resultados dependiendo de las opciones pasadas
    if (cantidad_lineas && cantidad_caracteres) {
        printf("%d %d\n", lineas, caracteres);  // Si se pasa -L y -C, imprime líneas seguido de caracteres
    } else if (cantidad_lineas) {
        printf("%d\n", lineas);  // Solo líneas si se pasa -L
    } else if (cantidad_caracteres) {
        printf("%d\n", caracteres);  // Solo caracteres si se pasa -C
    }
    printf("\n*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}
