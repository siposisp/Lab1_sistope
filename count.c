#include <funcionescount.c>

int main(int argc, char *argv[])
{
    printf("****************INICIO DEL PROGRAMA****************\n");

    // Leer argumentos de la línea de comandos
    int option;
    char *archivoentrada = NULL;
    char *archivosalida = "output.txt";
    int cantidad_lineas = 0;
    int cantidad_caracteres = 0;
    FILE *archivo;

    //Se utiliza geopt para leer las opciones de línea de comandos
    while ((option = getopt(argc, argv, "i:C:L:")) != -1) {
        switch (option) {
            case 'i':
                archivoentrada = optarg; //Nombre del archivo de entrada
                break;
            case 'C':
                columnas = optarg; //Contar el número de caracteres
                break;
            case 'L':
                cantidad_lineas = optarg;//Contar el numero de líneas
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

    printf("*****************FIN DEL PROGRAMA*****************\n");
    return 0;
}
