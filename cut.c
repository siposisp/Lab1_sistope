#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

// Entradas: Recibe un char* (una palabra) y un char (un caracter)
// Salida: Retorna un char* (una palabra con el char concatenado)
// Descripción: Agrega un caracter a una palabra Ej: "hol"+ "a" resulta "hola"
char* concatenar_caracter(char* palabra, char caracter) {
    int i = 0;
    while (palabra[i] != '\0') {
        i++;
    }
    
    // Redimensionar la cadena palabra para agregar un carácter extra
    palabra = (char *)realloc(palabra, (i + 2) * sizeof(char));
    palabra[i] = caracter;
    palabra[i + 1] = '\0';  // Agregar un caracter nulo al final
    return palabra;
}

// Entradas: Recibe un char* correspondiente a una linea del archivo
// Salida: Retorna un arreglo de char** correspondiente a una linea del archivo
// Descripción: transforma un linea leida del archivo a un arreglo separado por ":"
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
    palabra[0] = '\0';  // Arreglo inicial vacío

    while (linea[i] != '\0') {
        if (linea[i] != ';' && linea[i] != ':') {
            // Concatenar el carácter actual a la palabra
            palabra = concatenar_caracter(palabra, linea[i]);
        } else {
            // Agregar la palabra al arreglo
            if (cantidad == capacidad) {
                capacidad = capacidad * 2;  // Se duplica para no llamar tantas veces a realloc
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

    // Se agregar la última palabra al arreglo
    if (palabra[0] != '\0') {
        if (cantidad == capacidad) {
            capacidad = capacidad + 1;
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


// Entradas: Recibe un char* correspondiente al nombre del archivo de output
// Salida: No retorna nada
// Descripción: Verifica si el archivo de output existe, si existe lo limpia y si no existe lo crea
void vaciar_archivo(char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "w");

    // Verificar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
    }

    // Cerrar el archivo
    fclose(archivo);
}


// Entradas: Recibe un char* correspondiente al nombre del archivo de output y un char* con el contenido de la linea a guardar en el archivo de salida
// Salida: No retorna nada
// Descripción: Abre el archivo y agrega una linea al final del archivo
void guardar_en_archivo(char *nombreArchivo, char* contenidoLinea){
    FILE *archivo = fopen(nombreArchivo, "a");

    // Verificar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
    }

    // Escribir una nueva línea en el archivo
    fprintf(archivo, "%s", contenidoLinea);

    // Cerrar el archivo
    fclose(archivo);
}



// Entradas : 
// Salida : No retorna nada
// Descripción : 
void procesar_archivo(char* filename, char* caracterAntiguo, char* caracterNuevo, char* archivosalida) {
    int contador = 0;
    char linea[1024];

    // Abrir el archivo en modo lectura
    FILE* file = fopen(filename, "r");  
    if (file == NULL) { // Verificar que el archivo se haya abierto correctamente
        printf("Error al ingresar parametro flag -i. \nVerifique que el nombre sea correcto o si el archivo existe \n");
        return;
    }

    //Leer linea por linea el archivo
    while (fgets(linea, sizeof(linea), file)) {
        char **uwu = linea_a_arreglo(linea);
        guardar_en_archivo(archivosalida, linea);
        
        // Mostrar el contenido de uwu por consola
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
    printf("****************INICIO DEL PROGRAMA****************\n\n");

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

    vaciar_archivo(archivosalida); //Se limpia el archivo de salida, si es que existe

    procesar_archivo(archivoentrada, antiguo, nuevo, archivosalida);
    

    printf("\n*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}
