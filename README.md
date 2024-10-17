Sistemas Operativos: Laboratorios 1

Este repositorio contiene el primer laboratorio del curso de Sistemas Operativos, principalmente enfocado en diferentes aspectos del manejo de procesos en un sistema operativo Linux.

Laboratorio 1: Programación Imperativa en C

Este laboratorio tiene como objetivo aplicar técnicas de programación imperativa mediante lenguaje C, como la recepción de parámetros mediante getopt y compilación mediante Makefile sobre sistema operativo Linux.

Autor: Nicolas Guajardo & Cristian Romero

Fecha: 17-10-2024

Cómo ejecutar este proyecto

Se requiere un sistema operativo linux-based.
Compilar mediante el comando make.
Para ejecutar debes estar conciente de las siguientes definiciones para los flags para los diferentes archivos:

Primer Programa

-i: es el archivo de entrada 
 
-o: es el archivo de salida

-d: es el separador
 
-c: es el indicador de columnas

Ejemplo de comando para ejecutar:

./cout -i input.txt -o ouput.txt -d : -c 2,4

Segundo Programa

-i: es el archivo de entrada 
 
-o: es el archivo de salida

-s: es el caracter original del archivo a modificar
 
-S: es el caracter nuevo que se escribira

Ejemplo de comando para ejecutar:

./srep -i input.txt -o ouput.txt -s root -S hola

Tercer Programa

-i: es el archivo de entrada 
 
-C: es el que cuenta el numero de caracteres
 
-L: es el que cuenta el numero de lineas

Ejemplo de comando para ejecutar:

./count -i input.txt -C -L
./count -i input.txt -L -C
./count -i input.txt -L
./count -i input.txt -C

Obs: El programa está preparado para valores erróneos que puedan ser ingresados.

Excepciones

Segundo Programa

Los comandos separados por ejemplo hola mundo, deben ser escritos entre comillas para realizar el correcto reemplazo.
Ejemplo de compilado correcto:
./srep -i input.txt -o ouput.txt -s root -S "hola mundo"

Lo anterior debido a que el programa reemplaza hasta que lea un espacio en blanco.
Caso de erroneo:
./srep -i input.txt -o ouput.txt -s root -S hola mundo

Se cambiara los root solo por hola y no la palabra completa.

Existen comandos que deben ser escritos doblemente debido a diversos factores en el sistema operativo Linux. Por ejemplo:
"/".
Ejemplo de compilado correcto:
./srep -i input.txt -o ouput.txt -s root -S //

Descripcion

En este laboratorio se implementara algunas funciones simplificadas de las que provienen UNIX, en la que se realizaran distintas manipulaciones de texto sobre los archivos csv entregados. Cada una de estas funciones sera un archivo .c distinto, el cual realizara el simil de la funcion UNIX respectiva. Finalmente, estos archivos se ejecutarn por linea de comando.
Funcion Cut
El programa cut se usa para extraer informaci´on sobre nuestro archivo de entrada .csv o, en caso de no especificar un archivo de entrada, sobre un stdin, con el objetivo de obtener ciertas columnas
de interes.
Funcion Srep
El programa srep (String Replace) realiza un reemplazo del “string objetivo” (el que se encuentra dentro del archivo) por el “string nuevo” (el que ocupara el nuevo lugar dentro del archivo). Este cambio debe realizarse para todas las instancias en el que se encuentre el “string objetivo”. Finalmente se debera guardar la informacion reemplazada en un archivo de salida.
Funcion Count
El programa count se usa para obtener el total de lineas, palabras o bytes contenidos en el archivo csv, siendo en el caso de indicar un archivo de entrada; en caso contrario, la entrada sera por stdin.
