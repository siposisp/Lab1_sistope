#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

char* reemplazarCaracter(char *linea, char caracterAntiguo, char caracterNuevo) {
    for (int i = 0; linea[i] != '\0'; i++) {
        if (linea[i] == caracterAntiguo) {
            linea[i] = caracterNuevo;
        }
    }
    //printf(linea);
    return linea;
}



// Entradas : Recibe el archivo de entrada
// Salida :
// Descripción : Recibe un archivo y lo procesa
void procesar_archivo(char* filename, char caracterAntiguo, char caracterNuevo) {
    int contador = 0;
    char linea[1024];

    // Abrir el archivo en modo lectura
    FILE* file = fopen(filename, "r");  
    if (file == NULL) { // Verificar que el archivo se haya abierto correctamente
        printf("Error al ingresar parametro flag -i. \nVerifique que el nombre sea correcto o si el archivo existe \n");
        return;
    }

    //Leer linea por linea el archivo
    while (fgets(linea, sizeof(linea), file)){
        char *uwu = reemplazarCaracter(linea, caracterAntiguo, caracterNuevo);
        printf("%s", uwu);
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
    char *nuevo = NULL;
    char *antiguo = NULL;
    char a;
    char n;

    //Se utiliza geopt para leer las opciones de línea de comandos
    while ((option = getopt(argc, argv, "i:o:s:S:")) != -1) {
        switch (option) {
            case 's':
                if (optarg && optarg[0] != '\0') {
                    //antiguo = optarg[0]; // Obtener el primer carácter
                    a = optarg[0];
                }
                break;
            case 'S':
                if (optarg && optarg[0] != '\0') {
                    //nuevo = optarg[0]; // Obtener el primer carácter
                    n = optarg[0];
                }
                break;
            case 'i':
                archivoentrada = optarg; //Nombre del archivo de entrada
                break;
            case 'o':
                archivosalida = optarg; //Nombre del archivo de salida
                break;
            default:
                fprintf(stderr, "Uso: %s [-i archivoentrada] [-o archivosalida] [-s antiguo] [-S nuevo]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    //Manejo de errores en el archivo
    if (archivoentrada == NULL){
        fprintf(stderr, "Debe ingresar el nombre para el archivo de entrada (-i). \n");
        exit(EXIT_FAILURE);
    }

    procesar_archivo(archivoentrada, a, n);

    printf("*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}
