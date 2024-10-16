#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

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
char** linea_a_arreglo(char* linea, char simbolo) {
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
        if (linea[i] != simbolo) {
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

// Función para verificar si un número está en un arreglo
int buscar_numero_en_arreglo(int* arreglo, int tamano, int numero) {

    for (int i = 0; i < tamano; i++) {
        if (arreglo[i] == numero) {
            return 1;  // El número está en el arreglo
        }
    }
    return 0;  // El número no está en el arreglo
}


// Función para verificar si un char está en un arreglo
int buscar_caracter_en_arreglo(char* arreglo, int tamano, char caracter) {

    for (int i = 0; i < tamano; i++) {
        if (arreglo[i] == caracter) {
            return 1;  // El char está en el arreglo
        }
    }
    return 0;  // El char no está en el arreglo
}


// Entradas : 
// Salida : No retorna nada
// Descripción : 
void procesar_archivo(char* filename, int* columnas, int largoarreglo, char* archivosalida, char separador) {
    int contador = 0;
    char linea[1024];

    // Abrir el archivo en modo lectura
    FILE* file = fopen(filename, "r");  
    if (file == NULL) { // Verificar que el archivo se haya abierto correctamente
        printf("Error al ingresar parametro flag -i. \nVerifique que el nombre sea correcto o si el archivo existe \n");
        return;
    }

    char* concatenado; 
    //Leer linea por linea el archivo
    while (fgets(linea, sizeof(linea), file)) {

        if (buscar_caracter_en_arreglo(linea, strlen(linea), separador))
        {
            char **arreglo_de_linea = linea_a_arreglo(linea, separador); // Es un arreglo con contenido ['hola', 'como', 'estas'] donde 'hola' es un char*
            int posicion = 0; // posicion en el arreglo EJ: [2,4] la posicion 0 es 2 y la posicion 1 es 4
            int i = 0;

            for(i ; i< largoarreglo; i++)
            {
                if ((i+1) == largoarreglo)
                {
                    posicion = columnas[i] - 1;
                    //printf("%s", arreglo_de_linea[posicion]);
                    guardar_en_archivo(archivosalida, arreglo_de_linea[posicion]);

                }
                else{ 
                    posicion = columnas[i] - 1;
                    concatenado = concatenar_caracter(arreglo_de_linea[posicion], separador);
                    //printf("%s", concatenado);
                    guardar_en_archivo(archivosalida,concatenado);
                    
                }

                

            }
            guardar_en_archivo(archivosalida, "\n"); //agregar salto de línea
 

            // Liberar la memoria asignada a uwu
            for (int i = 0; i < posicion; i++) {
                free(arreglo_de_linea[i]);  // Liberar cada palabra
            }
            free(arreglo_de_linea);  // Liberar el arreglo de punteros

            contador++;
        }

        //guardar_en_archivo(archivosalida, linea);
    }

    printf("\nNúmero total de líneas: %d\n", contador);

    fclose(file);
}

// Función para convertir un carácter que representa un dígito a un entero
int char_to_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0'; // Convertir el carácter a entero
    } else {
        // Manejo de error si el carácter no es un dígito
        printf("Error: El carácter '%c' no es un dígito válido.\n", c);
        return -1; // Retorna -1 en caso de error
    }
}

// Obtiene la cantidad de números que se pasan. Ej: 10,4,3,4,5,6 retorna 6
int cantidad_de_numeros(char* columnas) {
    int contador = 0;
    int i = 0;
    int en_numero = 0;  // Indicar si estamos en un número

    // Verificar si la cadena está vacía
    if (columnas == NULL || columnas[0] == '\0') {
        return 0; // Retorna 0 si la cadena es vacía
    }

    while (columnas[i] != '\0') {
        // Si el carácter es un dígito
        if (columnas[i] >= '0' && columnas[i] <= '9') {
            if (en_numero == 0) {  // Si no estamos en un número
                contador++;         // Contamos un número
                en_numero = 1;      // Cambiamos el indicador
            }
        } 
        // Si el carácter es una coma
        else if (columnas[i] == ',') {
            en_numero = 0; // Si es una coma, no estamos en un número
        } 
        // Si encontramos un carácter no válido
        else {
            printf("Error: El carácter '%c' no es válido en la cadena.\n", columnas[i]);
            return -1; // Retorna -1 para indicar un error
        }
        i++;
    }

    return contador; // Retorna la cantidad total de números
}


//tranforma un arreglo de de numeros que está en formato char* a int* Ej: ["1","2","4"] -> [1,2,4]
int* arreglo_char_to_int(char* lista)
{

    char **uwu = linea_a_arreglo(lista, ',');
    
    int cantidad_numeros =  cantidad_de_numeros(lista);
    int* arreglo_numeros = (int*) malloc((cantidad_numeros) * sizeof(int));
    
    int i=0; //para avanzar en el arreglo de char
    //int j=0; //para avanzar en el arreglo de int
    for(i; i < cantidad_numeros; i++)
    {
        arreglo_numeros[i] = atoi(uwu[i]);
    }
    free(uwu);
    return arreglo_numeros;
}



int main(int argc, char *argv[])
{
    printf("****************INICIO DEL PROGRAMA****************\n\n");

    // Leer argumentos de la línea de comandos
    int option;
    char *archivoentrada = NULL;
    char *archivosalida = NULL;
    char separador = '\0';
    char *columnas = NULL;

    //Se utiliza geopt para leer las opciones de línea de comandos
    while ((option = getopt(argc, argv, "i:o:d:c:")) != -1) {
        switch (option) {
            case 'd':
                separador = optarg[0]; //carácter separador de la columnas
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
/*
    int cantidad_numeros =  cantidad_de_numeros(columnas);

    int* arreglo_numeros = (int*) malloc((cantidad_numeros) * sizeof(int));

    arreglo_numeros = arreglo_char_to_int(columnas);
*/

    //procesar_archivo(archivoentrada, arreglo_numeros, cantidad_numeros, archivosalida, separador);
    

    int cantidad_numeros = cantidad_de_numeros(columnas);
    int* arreglo_numeros = arreglo_char_to_int(columnas);

    procesar_archivo(archivoentrada, arreglo_numeros, cantidad_numeros, archivosalida, separador);

    free(arreglo_numeros);

    printf("\n*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}
