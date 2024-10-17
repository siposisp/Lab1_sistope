#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

// Entradas: Recibe un char* (una palabra) y un char (un caracter)
// Salida: Retorna un char* (una palabra con el char concatenado)
// Descripción: Agrega un caracter a una palabra Ej: "hol"+ "a" resulta "hola"
char* concatenar_caracter(const char* palabra, char caracter);

// Entradas: Recibe un char* correspondiente a una linea del archivo
// Salida: Retorna un arreglo de char** correspondiente a una linea del archivo
// Descripción: transforma un linea leida del archivo a un arreglo separado por ":"
char** linea_a_arreglo(char* linea, char simbolo);


// Entradas: Recibe un char* correspondiente al nombre del archivo de output
// Salida: No retorna nada
// Descripción: Verifica si el archivo de output existe, si existe lo limpia y si no existe lo crea
void vaciar_archivo(char *nombreArchivo);


// Entradas: Recibe un char* correspondiente al nombre del archivo de output y un char* con el contenido de la linea a guardar en el archivo de salida
// Salida: No retorna nada
// Descripción: Abre el archivo y agrega una linea al final del archivo
void guardar_en_archivo(char *nombreArchivo, char* contenidoLinea);


// Entradas : Recibe un char* correspondiente a un puntero de un arreglo de caracteres con el que se trabajara.
//            Un int correspondiente al tamaño del arreglo.  
//            Un char correspondiente al caracter que se va a buscar dentro del arreglo.  
// Salida : Retorna un entero.
//          Retorna 1 si el char esta dentro del arreglo.
//          Retorna 0 si el char no esta dentro del arreglo.
// Descripción : La funcion busca un caracter dado dentro de un arreglo de caracteres, dependiendo si esta retornara un valor u otro. 
int buscar_caracter_en_arreglo(char* arreglo, int tamano, char caracter);

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
void procesar_archivo(char* filename, int* columnas, int largoarreglo, char* archivosalida, char separador);

// Entradas : Recibe un char* correspondiente a un puntero a una cadena de caracteres que contiene numeros separados por comas Ej: 10,4,3,4,5,6. 
// Salida : Retorna un entero.
//          Si es valido retorna la cantidad de numeros enteros en la cadena.
//          Si encuentra un caracter no valido imprime un mensaje de error y retorna -1
//          Si la cadena contiene un numero que comienza con 0, imprime un error y retorna -1
// Descripción : La funcion verifica la cadena de caracteres (por columnas la veremos) que se entrega para contar los numeros enteros positivos que estan separados por comas.
int cantidad_de_numeros(char* columnas);

// Entradas : Recibe un char* correspondiente a un puntero de una cadena de caracteres que contiene una lista de numeros separados Ej: ["1","2","4"]
// Salida : Retorna un puntero a un arreglo int* quue contiene los numeros convertidos. Ej: ["1","2","4"] -> [1,2,4]
// Descripción : La funcion convierte una lista de numeros que son char* en un arreglo de enteros int*.
int* arreglo_char_to_int(char* lista);

// Entradas : Recibe un char* correspondiente al archivo de entrada y un char* correspondiente al nombre del archivo de salida
// Salida : No retorna nada
// Descripción : La funcion lee el archivo de entrada linea a linea.
//               Escribe su contenido en un archivo de salida especifico.
//               Si no se puede abrir el archivo imprime errores correspondientes. Finalmente muestra el mensaje de archivo procesado y cierra el archivo.
void reimprimir_archivo(char* filename, char* archivosalida);
