//Autor: Camila Denise Términe
//Fecha: 20/06/2023
//Archivos correspondientes : main.c//libreria.h//libreria.c//prestamos.csv//TpFinal.cbp//Manual de Usuario - Camila Términe.pdf
#include "libreria.h"

int main()
{
    //system ("COLOR B" );
    cliente clientes [TAM];
    FILE * pArchivo = NULL;
    char nombre[] = "prestamos.csv";
    pArchivo = abrir_archivo(pArchivo,nombre, "r");
    leer_archivo(pArchivo, clientes);
    cerrar_archivo(pArchivo);
    menu(clientes);
    return 0;
}
