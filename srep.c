#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

// Entradas : Recibe el archivo de entrada
// Salida :
// Descripción : Recibe un archivo y lo procesa
void procesar_archivo(char* filename) {
    int contador = 0;
    char line[256];

    // Abrir el archivo en modo lectura
    FILE* file = fopen(filename, "r");  
    if (file == NULL) { // Verificar que el archivo se haya abierto correctamente
        printf("Error al ingresar parametro flag -i. \nVerifique que el nombre sea correcto o si el archivo existe \n");
        return;
    }

    //Leer linea por linea el archivo
    while (fgets(line, sizeof(line), file)){
        printf("%s", line);
        contador++;
    }

    printf("\nNúmero total de líneas: %d\n", contador);

    fclose(file);
}

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
    while ((option = getopt(argc, argv, "i:o:s:S:")) != -1) {
        switch (option) {
            case 's':
                separador = optarg; //carácter separador de la columnas
                break;
            case 'S':
                columnas = optarg; //Indicar la o las columnas 
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

    procesar_archivo(archivoentrada);

    printf("*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}
