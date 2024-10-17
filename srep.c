#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "funcionessrep.h"

int main(int argc, char *argv[]) {
    printf("****************INICIO DEL PROGRAMA****************\n");

    // Variables locales
    char *archivoentrada = NULL;
    char *archivosalida = NULL;
    char *caracterAntiguo = NULL;
    char *caracterNuevo = NULL;
   
   //Llamado a la funcion opciones
    opciones(argc, argv, &archivoentrada, &archivosalida, &caracterAntiguo, &caracterNuevo);

    //Llamado a la funcion procesar_archivo
    procesar_archivo(archivoentrada, archivosalida, caracterAntiguo, caracterNuevo);

    printf("*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}
