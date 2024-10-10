#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


char* concatenar_caracter(char* palabra, char c) {
    int len = 0;
    while (palabra[len] != '\0') {
        len++;
    }
    
    // Redimensionar la cadena palabra para agregar un carácter extra
    palabra = (char *)realloc(palabra, (len + 2) * sizeof(char));
    palabra[len] = c;
    palabra[len + 1] = '\0';  // Agregar terminador nulo
    return palabra;
}

char** linea_a_arreglo(char* linea) {
    int i = 0, j = 0;
    int capacidad = 1;  // Capacidad inicial del arreglo
    int cantidad = 0;   // Cantidad de palabras
    char** arreglo = NULL;  // Arreglo de cadenas
    char* palabra = NULL;   // Palabra temporal

    // Reservar memoria inicial para el arreglo
    arreglo = (char**)malloc(capacidad * sizeof(char*));
    if (arreglo == NULL) {
        printf("Error al reservar memoria.\n");
        exit(1);
    }

    // Inicializar la primera palabra
    palabra = (char*)malloc(1 * sizeof(char));
    palabra[0] = '\0';  // Inicialmente vacía

    while (linea[i] != '\0') {
        if (linea[i] != ';' && linea[i] != ':') {
            // Concatenar el carácter actual a la palabra
            palabra = concatenar_caracter(palabra, linea[i]);
        } else {
            // Agregar la palabra al arreglo
            if (cantidad == capacidad) {
                capacidad *= 2;  // Aumentar capacidad
                arreglo = (char**)realloc(arreglo, capacidad * sizeof(char*));
                if (arreglo == NULL) {
                    printf("Error al redimensionar memoria.\n");
                    exit(1);
                }
            }

            arreglo[cantidad] = palabra;  // Agregar palabra al arreglo
            cantidad++;

            // Reservar memoria para la siguiente palabra
            palabra = (char*)malloc(1 * sizeof(char));
            palabra[0] = '\0';  // Inicializar nueva palabra
        }
        i++;
    }

    // Agregar la última palabra al arreglo
    if (palabra[0] != '\0') {
        if (cantidad == capacidad) {
            capacidad *= 2;
            arreglo = (char**)realloc(arreglo, capacidad * sizeof(char*));
        }
        arreglo[cantidad] = palabra;
        cantidad++;
    }

    // Agregar un puntero nulo para marcar el final del arreglo
    arreglo = (char**)realloc(arreglo, (cantidad + 1) * sizeof(char*));
    arreglo[cantidad] = NULL;

    return arreglo;
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
    //while (fgets(linea, sizeof(linea), file)){
    //    //char *uwu = reemplazarCaracter(linea, caracterAntiguo, caracterNuevo);
    //    char **uwu = linea_a_arreglo(linea);
        //printf("%s", uwu);
    //    contador++;
    //}

    //Leer linea por linea el archivo
    while (fgets(linea, sizeof(linea), file)) {
        char **uwu = linea_a_arreglo(linea);
        
        // Mostrar el contenido de uwu
        int k = 0;
        while (uwu[k] != NULL) {
            printf("Palabra %d: %s\n", k + 1, uwu[k]);
            k++;
        }

        // Liberar la memoria asignada a uwu
        for (int i = 0; i < k; i++) {
            free(uwu[i]);  // Liberar cada palabra
        }
        free(uwu);  // Liberar el arreglo de punteros

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
