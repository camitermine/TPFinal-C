//Archivo de cabecera donde se declararán las funciones utilizadas y se incluiran las librerias externas, otros archivos correspondientes al programa.
#ifndef LIBRERIA_H_INCLUDED
#define LIBRERIA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define TAM 17

struct clientes{
    int orden;
    char nombre [20];
    char apellido [20];
    float importe;
    char tipoCredito[20];
    int dia;
    int mes;
    char mesL[3];
    int anio;
    int nroCuota;
    float importeCuota;
    float iva;
    float totalCuota;
    int activo;
} typedef cliente;

FILE* abrir_archivo(FILE*archivo,char nombre[], char modoApertura[]);
void cerrar_archivo(FILE*archivo);
void leer_archivo(FILE*archivo, cliente clientes []);
void emitir(cliente clientes []);
void menu(cliente clientes[]);
void menuListarDat(FILE * arch);
void menuBuscar(FILE* arch);
void menuBajaFisicaInactivos(FILE* arch,char nombreCompleto[]);
void migrarDatos(cliente clientes [],FILE* arch);
void emitirBin(cliente clientes [], int tamanio, int filtrarActivo,int filtrarTipoCredito,char filtroCredito[]);
void darAlta(FILE * archivoBin);
void buscar(FILE* arch,int porOrden,char* apellido);
void bajaLogica(FILE* arch);
void bajaFisicaInactivos(FILE* arch,FILE* texto);
void modificar(FILE* arch);
void emitirBinFiltroMes(cliente clientes[],int tamanio);
void normalizarCadena(char* cadena);
int compararFechas(int dia1,int mes1,int anio1,int dia2,int mes2, int anio2);
void convertirMesLetras(int mes,char mesCad[]);
int esAnioBisiesto(int anio);
int esFechaValida(int dia, int mes, int anio);
int esCadenaValida(char* cadena);
int esNumFlotValido(char *cadena);
int esIntValido(char *cadena);



#endif // LIBRERIA_H_INCLUDED


