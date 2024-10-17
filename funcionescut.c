#include "funcionescut.h"


// Entradas: Recibe un char* (una palabra) y un char (un caracter).
// Salida: Retorna un char* (una palabra con el char concatenado).
// Descripción: Agrega un caracter a una palabra Ej: "hol"+ "a" resulta "hola".
char* concatenar_caracter(const char* palabra, char caracter) {
    int longitud = strlen(palabra);  // Obtener la longitud de la cadena original

    // Crear una nueva palabra con espacio adicional para el nuevo carácter y el carácter nulo
    char* nueva_palabra = (char*) malloc((longitud + 2) * sizeof(char)); 

    // Copiar la cadena original a la nueva palabra
    strcpy(nueva_palabra, palabra);

    // Añadir el nuevo carácter al final de la nueva palabra
    nueva_palabra[longitud] = caracter;
    nueva_palabra[longitud + 1] = '\0';

    return nueva_palabra; 
}

// Entradas: Recibe un char* correspondiente a una linea del archivo.
// Salida: Retorna un arreglo de char** correspondiente a una linea del archivo.
// Descripción: transforma un linea leida del archivo a un arreglo separado por ":"
char** linea_a_arreglo(char* linea, char simbolo) {
    int i = 0;
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
    if (palabra == NULL) {
        printf("Error al reservar memoria para la palabra.\n");
        free(arreglo);
        exit(1);
    }
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
                    for (int k = 0; k < cantidad; k++) {
                        free(arreglo[k]);
                    }
                    free(palabra);  // Liberar la palabra actual
                    exit(1);
                }
            }

            arreglo[cantidad] = palabra;  // Agregar palabra al arreglo
            cantidad++;

            // Reservar memoria para la siguiente palabra
            palabra = (char*)malloc(1 * sizeof(char));
            if (palabra == NULL) {
                printf("Error al reservar memoria para la nueva palabra.\n");
                for (int k = 0; k < cantidad; k++) {
                    free(arreglo[k]);
                }
                free(arreglo);
                exit(1);
            }
            palabra[0] = '\0';  // Inicializar nueva palabra
        }
        i++;
    }


    // Se agregar la última palabra al arreglo
    if (palabra[0] != '\0') {
        if (cantidad == capacidad) {
            capacidad = capacidad + 1;
            arreglo = (char**)realloc(arreglo, capacidad * sizeof(char*));
            if (arreglo == NULL) {
                printf("Error al redimensionar memoria para la última palabra.\n");
                for (int k = 0; k < cantidad; k++) {
                    free(arreglo[k]);
                }
                free(palabra);
                exit(1);
            }
        }
        arreglo[cantidad] = palabra;
        cantidad++;
    } else {
        // Si la última palabra está vacía, liberarla
        free(palabra);
    }

    // Agregar un puntero nulo para marcar el final del arreglo
    arreglo = (char**)realloc(arreglo, (cantidad + 1) * sizeof(char*));
    if (arreglo == NULL) {
        printf("Error al redimensionar memoria para el puntero nulo.\n");
        for (int k = 0; k < cantidad; k++) {
            free(arreglo[k]);
        }
        exit(1);
    }
    arreglo[cantidad] = NULL;

    return arreglo;
}


// Entradas: Recibe un char* correspondiente al nombre del archivo de output.
// Salida: No retorna nada.
// Descripción: Verifica si el archivo de output existe, si existe lo limpia y si no existe lo crea.
void vaciar_archivo(char *nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "w");

    // Verificar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
    }

    // Cerrar el archivo
    fclose(archivo);
}


// Entradas: Recibe un char* correspondiente al nombre del archivo de output y un char* con el contenido de la linea a guardar en el archivo de salida.
// Salida: No retorna nada.
// Descripción: Abre el archivo y agrega una linea al final del archivo.
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

// Entradas : Recibe un char* correspondiente a un puntero de un arreglo de caracteres con el que se trabajara.
//            Un int correspondiente al tamaño del arreglo.  
//            Un char correspondiente al caracter que se va a buscar dentro del arreglo.  
// Salida : Retorna un entero.
//          Retorna 1 si el char esta dentro del arreglo.
//          Retorna 0 si el char no esta dentro del arreglo.
// Descripción : La funcion busca un caracter dado dentro de un arreglo de caracteres, dependiendo si esta retornara un valor u otro. 
int buscar_caracter_en_arreglo(char* arreglo, int tamano, char caracter) {

    for (int i = 0; i < tamano; i++) {
        if (arreglo[i] == caracter) {
            return 1;  // El char está en el arreglo
        }
    }
    return 0;  // El char no está en el arreglo
}


// Entradas : Recibe un char* correspondiente al nombre del archivo de entrada.
//            Un int* correspondiente a un arreglo de enteros que indica los indice de las columnas que se extraeran (comando).
//            Un int correspondiente al numero de elementos en el arreglo columnas (largo del arreglo) que indica cuantas se van a extraer. 
//            Un char* correspondiente al nombre del archivo de salida.   
//            Un char correspondiente al caracter que indica como estan separadas las columnas.  
// Salida : No retorna nada
// Descripción : La funcion procesa el archivo linea a linea.
//               Lee el archivo de entrada. Verificando que se ingrese con comando correspondiente y nombre correcto (si existe).
//               Lee linea a linea el archivo almacenando en un buffer de 1024 la linea leida.   
//               Si la linea contiene el separador indicado, la funcion divide las columnas usando otra funcion.
//               Extrae las columnass seleccionadas si se cumple los requisitos previos.
//               Dependiendo de si se proporciona el nombre del archivo de salida o no, se imprime por consola o se guarda en el archivo de salida.
//               Se libera la memoria correspondiente.
//               Se cierra el archivo y se envia mensaje de exito.
void procesar_archivo(char* filename, int* columnas, int largoarreglo, char* archivosalida, char separador) {
    char linea[1024];

    // Abrir el archivo en modo lectura
    FILE* file = fopen(filename, "r");  
    if (file == NULL) { // Verificar que el archivo se haya abierto correctamente
        printf("Error al ingresar parametro flag -i. \nVerifique que el nombre sea correcto o si el archivo existe \n");
        return;
    }

    char* concatenado;
    
    // Leer línea por línea el archivo
    while (fgets(linea, sizeof(linea), file)) {
        if (buscar_caracter_en_arreglo(linea, strlen(linea), separador)) {
            char **arreglo_de_linea = linea_a_arreglo(linea, separador);  // Dividir la línea en columnas

            int num_columnas_disponibles = 0;
            while (arreglo_de_linea[num_columnas_disponibles] != NULL) {
                num_columnas_disponibles++;
            }

            for (int i = 0; i < largoarreglo; i++) {
                int posicion = columnas[i] - 1;  // Convertir de 1-index a 0-index
                
                // Verificar si la posición solicitada está dentro del rango
                if (posicion >= num_columnas_disponibles) {
                    //printf("Advertencia: La columna %d no existe en esta línea.\n", columnas[i]);
                    continue;  // Saltar a la siguiente columna si no existe
                }

                if ((i + 1) == largoarreglo) {  // Última columna
                    if (archivosalida == NULL) {
                        printf("%s", arreglo_de_linea[posicion]);
                    } else {
                        guardar_en_archivo(archivosalida, arreglo_de_linea[posicion]);
                    }
                } else {  // Otras columnas
                    concatenado = concatenar_caracter(arreglo_de_linea[posicion], separador);

                    if (archivosalida == NULL) {
                        printf("%s", concatenado);
                    } else {
                        guardar_en_archivo(archivosalida, concatenado);
                    }

                    free(concatenado);  // Liberar después de usar
                }
            }

            // Agregar salto de línea
            if (archivosalida == NULL) {
                printf("\n");
            } else {
                guardar_en_archivo(archivosalida, "\n");
            }

            // Liberar la memoria asignada
            for (int i = 0; i < num_columnas_disponibles; i++) {
                free(arreglo_de_linea[i]);
            }
            free(arreglo_de_linea);
        }
    }

    printf("Archivo procesado exitosamente\n");

    fclose(file);
}

// Entradas : Recibe un char* correspondiente a un puntero a una cadena de caracteres que contiene numeros separados por comas Ej: 10,4,3,4,5,6. 
// Salida : Retorna un entero.
//          Si es valido retorna la cantidad de numeros enteros en la cadena.
//          Si encuentra un caracter no valido imprime un mensaje de error y retorna -1.
//          Si la cadena contiene un numero que comienza con 0, imprime un error y retorna -1.
// Descripción : La funcion verifica la cadena de caracteres (por columnas la veremos) que se entrega para contar los numeros enteros positivos que estan separados por comas.
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
                // Si el número es '0' y estamos empezando a contar un nuevo número
                if (columnas[i] == '0' && (i == 0 || columnas[i - 1] == ',')) {
                    printf("Error: El carácter '%c' no es válido en la cadena. Solo puede ingresar numeros enteros positivos y mayores a 0\n", columnas[i]);
                    return -1; // Retorna -1 si encontramos un 0
                }
                
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
            printf("Error: El carácter '%c' no es válido en la cadena. Solo puede ingresar numeros enteros positivos y mayores a 0\n", columnas[i]);
            return -1; // Retorna -1 para indicar un error
        }
        i++;
    }

    return contador; // Retorna la cantidad total de números
}

// Entradas : Recibe un char* correspondiente a un puntero de una cadena de caracteres que contiene una lista de numeros separados Ej: ["1","2","4"].
// Salida : Retorna un puntero a un arreglo int* quue contiene los numeros convertidos. Ej: ["1","2","4"] -> [1,2,4].
// Descripción : La funcion convierte una lista de numeros que son char* en un arreglo de enteros int*.
int* arreglo_char_to_int(char* lista){

    char **arreglo_aux = linea_a_arreglo(lista, ',');
    
    int cantidad_numeros =  cantidad_de_numeros(lista);
    int* arreglo_numeros = (int*) malloc((cantidad_numeros) * sizeof(int));
    
    int i; //para avanzar en el arreglo de char
    //int j=0; //para avanzar en el arreglo de int
    for(i = 0; i < cantidad_numeros; i++)
    {
        arreglo_numeros[i] = atoi(arreglo_aux[i]);
    }
    
    for (i = 0; arreglo_aux[i] != NULL; i++) { // Liberar el arreglo de cadenas
    free(arreglo_aux[i]);
    }
    free(arreglo_aux);

    return arreglo_numeros;
}


// Entradas : Recibe un char* correspondiente al archivo de entrada y un char* correspondiente al nombre del archivo de salida.
// Salida : No retorna nada.
// Descripción : La funcion lee el archivo de entrada linea a linea.
//               Escribe su contenido en un archivo de salida especifico.
//               Si no se puede abrir el archivo imprime errores correspondientes. Finalmente muestra el mensaje de archivo procesado y cierra el archivo.
void reimprimir_archivo(char* filename, char* archivosalida) {
    char linea[1024];

    // Abrir el archivo en modo lectura
    FILE* file = fopen(filename, "r");  
    if (file == NULL) { // Verificar que el archivo se haya abierto correctamente
        printf("Error al ingresar parametro flag -i. \nVerifique que el nombre sea correcto o si el archivo existe \n");
        return;
    }

    //Leer linea por linea el archivo
    while (fgets(linea, sizeof(linea), file)) {
        guardar_en_archivo(archivosalida, linea);
    }

    printf("Archivo procesado exitosamente\n");

    fclose(file);
}

