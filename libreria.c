//En este archivo se desarrollarán las funciones declaradas en libreria.h
/*CONTROL DE ERRORES:
Se impide al usuario imprimir el archivo de bajas fisicas xyz sin antes haberlo creado
Se hacen las validaciones correspondientes de tipos de datos. No se pueden ingresar numeros si pido string y visceversa
Se hacen las validaciones correspondientes de fecha. El usuario no puede ingresar una fecha menor al año 2022(minimo del csv) ni mayor
al año actual (en este caso, 2023)
El usuario tampoco puede utilizar las opciones 3 a 10 sin antes haber creado el archivo binario*/

#include "libreria.h"

//funcion que abre un archivo y retorna un puntero al mismo. De parametros recibe un nombre de archivo, modo de apertura y puntero a archivo.
//Si se produce error, envia el mensaje correspondiente.
FILE* abrir_archivo(FILE*archivo,char nombre[], char modoApertura[]){
    archivo = fopen(nombre,modoApertura);
    if(archivo == NULL){
        printf("Error de apertura del archivo. \n");
        return NULL;
    }
    return archivo;
}

//funcion que cierra un archivo
void cerrar_archivo(FILE*archivo){
    fclose(archivo);
}

//funcion que lee un archivo y guarda los datos en una estructura
void leer_archivo(FILE*archivo, cliente clientes []){
    char linea[2000];
    char* campo;
    char* parseNombre;
    int i=0;
    fgets(linea,2000,archivo);
    fgets(linea,2000,archivo);
    while(!feof(archivo)){
        //obtengo los campos del archivo de txt y los cargo en mi array de estructuras cliente. Uso de token ";" que es el separador
        campo = strtok(linea,";");
        clientes[i].orden = atoi(campo);
        campo = strtok(NULL,";");
        //para cargar correctamente los campos nombre y apellido, al no estar separados por ; recorremos el campo hasta encontrar un espacio.
        //Asi ya sabemos que en parseNombre esta el nombre hasta el espacio (que cambiamos por un /0) y en campo queda el apellido.
        parseNombre = campo;
        while(*campo != ' '){
            campo++;
        }
        *campo = '\0';
        campo++;
        strcpy(clientes[i].nombre,parseNombre);
        strcpy(clientes[i].apellido,campo);
        campo = strtok(NULL,";");
        clientes[i].importe = atof(campo);
        campo = strtok(NULL,";");
        strcpy(clientes[i].tipoCredito,campo);
        campo = strtok(NULL,";");
        clientes[i].dia = atoi(campo);
        campo = strtok(NULL,";");
        clientes[i].mes = atoi(campo);
        campo = strtok(NULL,";");
        clientes[i].anio = atoi(campo);
        campo = strtok(NULL,";");
        clientes[i].nroCuota = atoi(campo);
        campo = strtok(NULL,";");
        clientes[i].importeCuota = atof(campo);
        campo = strtok(NULL,";");
        clientes[i].iva = atof(campo);
        campo = strtok(NULL,";");
        clientes[i].totalCuota = atof(campo);
        i++;
        fgets(linea,2000,archivo);
    }
}

//funcion que emite el array de estructuras cargado con datos del archivo de texto.
void emitir(cliente clientes []){
int i;
char cliente[40];
printf("%c", 201);
    for (i=0; i<112; i++){
        printf("%c", 205);
    }
printf("%c\n%cOrden    Cliente          Importe    TipoCredito   Dia   Mes    A%co   NroCuotas   ImporteCuota  IVA  TotalCuota %c\n",187, 186, 164, 186);
    for (i=0; i<TAM; i++){
        sprintf(cliente, "%s %s", clientes[i].nombre, clientes[i].apellido);
        printf("%c %-6d %-17s %-10.2f %12s %4d %4d %8d %5d %17.2f %8.2f %8.2f  %c\n", 186, clientes[i].orden, cliente, clientes[i].importe, clientes[i].tipoCredito, clientes[i].dia, clientes[i].mes, clientes[i].anio, clientes[i].nroCuota, clientes[i].importeCuota, clientes[i].iva, clientes[i].totalCuota,186);
        }

}

//Funcion que migra los datos del array de estructura al archivo binario
void migrarDatos(cliente clientes [],FILE* arch){
int i;
    for (i=0; i<TAM; i++){
        //Llenamos el campo mesL con una cadena de 3 caracteres tomando en cuenta el mes de cada usuario.
        convertirMesLetras(clientes[i].mes,clientes[i].mesL);
     //Asignamos el valor 1 al campo activo por defecto.
        clientes[i].activo = 1;
    }
    //Escribimos el archivo binario
    fwrite(clientes,sizeof (cliente),TAM,arch);

}

//funcion que recibe como parametro un mes y lo convierte a cadena de 3 caracteres
void convertirMesLetras(int mes,char mesCad[]){

    switch(mes){
        case 1: strcpy(mesCad,"ene");
        break;
        case 2: strcpy(mesCad,"feb");
        break;
        case 3: strcpy(mesCad,"mar");
        break;
        case 4: strcpy(mesCad,"abr");
        break;
        case 5: strcpy(mesCad,"may");
        break;
        case 6: strcpy(mesCad,"jun");
        break;
        case 7: strcpy(mesCad,"jul");
        break;
        case 8: strcpy(mesCad,"ago");
        break;
        case 9: strcpy(mesCad,"sep");
        break;
        case 10: strcpy(mesCad,"oct");
        break;
        case 11: strcpy(mesCad,"nov");
        break;
        case 12: strcpy(mesCad,"dic");
    }

}

//Emitimos el contenido del archivo binario
void emitirBin(cliente clientes [], int tamanio, int filtrarActivo,int filtrarTipoCredito,char filtroCredito[]){
    int i;
    char nombreCliente[40];
    printf("Orden    Cliente          Importe    TipoCredito   Dia   Mes    A%co   NroCuotas   ImporteCuota  IVA  TotalCuota Activo \n",164);
    for (i=0; i<tamanio; i++){
//Aca aplicamos los filtros correspondientes: Si quiere filtrar por clientes activos, por tipo de credito, etc.
//utilizamos banderas que mandamos como parametro
        if ((filtrarActivo == 0 || clientes[i].activo == 1) && ( filtrarTipoCredito == 0 || strcmp(clientes[i].tipoCredito,filtroCredito ) == 0)){
            //usamos sprintf para unir nombre+apellido cuando emitimos
            sprintf(nombreCliente, "%s %s", clientes[i].nombre, clientes[i].apellido);
            printf("%-6d %-17s %-10.2f %12s %4d %6s %6d %5d %17.2f %8.2f %8.2f %4d\n",clientes[i].orden, nombreCliente, clientes[i].importe, clientes[i].tipoCredito, clientes[i].dia, clientes[i].mesL, clientes[i].anio, clientes[i].nroCuota, clientes[i].importeCuota, clientes[i].iva, clientes[i].totalCuota,clientes[i].activo);
        }
    }

}

//Menu para seleccionar el tipo de filtro que elija el usuario
void menuListarDat(FILE * arch){

int opcion;
int opcionTipoCredito = 0;
char tipoCredito[20];
int i=0;
cliente aux[1000];
    //aca obtenemos la cantidad total de usuarios que tenemos registrados
    while (!feof(arch)){
        fread(&aux[i],sizeof(cliente),1,arch);
        i++;
    }

    do{
    printf("Ingrese la opci%cn correspondiente:\n",162);
    printf("1. Para listar todos los clientes \n");
    printf("2. Para listar solo el campo activo \n");
    printf("3. Para listar los clientes con tipo de cr%cdito ingresado \n",130);
    printf("4. Clientes correspondientes a determinado periodo de tiempo ingresado \n");
    printf("0. Para volver al menu anterior \n");
    scanf("%d", &opcion);
    //tenemos flags para reutilizar la funcion de emitir. El tercer flag es para listar activo o no
    //el cuarto flag para listar segun tipo de credito)
    //y i-1 nos da la cantidad de clientes registrados
    switch (opcion){
        case 1: emitirBin(aux,i-1,0,0,NULL);
        break;
        case 2: emitirBin(aux, i-1,1,0,NULL);
        break;
        case 3: printf("Ingrese el tipo de cr%cdito a filtrar : \n", 130);
                printf("1. A sola firma\n");
                printf("2. Con Garant%ca \n", 161);
                scanf("%d", &opcionTipoCredito);
                switch(opcionTipoCredito){
                    case 1: strcpy(tipoCredito,"A sola firma");
                    break;
                    case 2: strcpy(tipoCredito,"Con Garantia");
                    break;
                }
                emitirBin(aux,i-1,0,1,tipoCredito);
        break;
        case 4:
                emitirBinFiltroMes(aux,i-1);
        break;
        }
    }while (opcion != 0);


}

//funcion que filtra segun fecha maxima y minima ingresada por el usuario y emite los clientes comprendidos entre esas fechas
void emitirBinFiltroMes(cliente clientes[],int tamanio){
int dia, mes, anio;
int dia2, mes2, anio2;
int i;
char nombreCliente[40];
    do{
        printf("\nIngrese fecha minima en formato dd/mm/aaaa:\n");
        scanf("%d/%d/%d",&dia,&mes,&anio);
    }while(!esFechaValida(dia,mes,anio));

    do{
        printf("\nIngrese fecha maxima en formato dd/mm/aaaa:\n\n");
        scanf("%d/%d/%d",&dia2,&mes2,&anio2);
    }while(!esFechaValida(dia2,mes2,anio2));


printf("Orden    Cliente          Importe    TipoCredito   Dia   Mes    A%co   NroCuotas   ImporteCuota  IVA  TotalCuota Activo \n",164);
    for (i=0; i<tamanio; i++){
    //Aca comparamos la fecha del usuario con la piso y tope. La funcion compararFechas devuelve 1 si la fecha es mayor, -1 si es menor
    //y 0 si es igual. Sabiendo esos valores de retorno podemos identificar aquellas fechas que se encuentren entre las dos especificadas
        if (compararFechas(clientes[i].dia,clientes[i].mes,clientes[i].anio,dia,mes,anio) >= 0 && compararFechas(clientes[i].dia,clientes[i].mes,clientes[i].anio,dia2,mes2,anio2) <= 0){
            sprintf(nombreCliente, "%s %s", clientes[i].nombre, clientes[i].apellido);
            printf("%-6d %-17s %-10.2f %12s %4d %6s %6d %5d %17.2f %8.2f %8.2f %4d\n",clientes[i].orden, nombreCliente, clientes[i].importe, clientes[i].tipoCredito, clientes[i].dia, clientes[i].mesL, clientes[i].anio, clientes[i].nroCuota, clientes[i].importeCuota, clientes[i].iva, clientes[i].totalCuota,clientes[i].activo);
        }
    }

}

//funcion que compara fechas para saber cuál es mas mayor y cuál menor
//retorna 1 si la fecha1 es mayor a la fecha 2
//-1 si es menor y 0 si son iguales
int compararFechas(int dia1,int mes1,int anio1,int dia2,int mes2, int anio2){

    if(anio1 > anio2){
        return 1;
    }else if(anio1 < anio2){
        return -1;
    }else if(mes1 > mes2){
        return 1;
    }else if(mes1 < mes2){
        return -1;
    }else if(dia1 > dia2){
        return 1;
    }else if(dia1 < dia2){
        return -1;
    }

return 0;

}

//funcion que determina si un año es o no bisiesto
int esAnioBisiesto(int anio){

int esBisiesto;
//para que sea bisiesto tiene que ser divisible por 4 y por 400 pero no por 100
    if(anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0)){
        esBisiesto = 1;
    }else{
        esBisiesto = 0;
    }
return esBisiesto;
}

//funcion que recibe una fecha (dia, mes, año) y retorna si es una fecha válida o no.
//para eso evalua que los dias no se excedan en los meses. Ejemplo, que abril no tenga 31 dias, que febrero no tenga 29
//si el año no es bisiesto, etc
int esFechaValida(int dia, int mes, int anio){

int esValida = 1;
int esBisiesto;
time_t fecha;
struct tm* obtenerFecha;
char anioActual[50];
int anioActualEntero;

esBisiesto = esAnioBisiesto(anio);

//aca obtenemos el año actual para evaluar ingresos por encima de ese año no sean validos con la libreria time.h
fecha = time(NULL);

obtenerFecha = localtime(&fecha);

strftime(anioActual, sizeof(anioActual), "%Y", obtenerFecha);

sscanf(anioActual,"%d",&anioActualEntero);

//nos fijamos que el ingreso debe ser mayor o igual a 2022 y no debe exceder el año actual
    if(anio < 2022  || anio > anioActualEntero){
        esValida = 0;
    }else{
        //corroboramos que el mes no sea menor a 0 o mayor a 12
        if(mes <= 0 || mes > 12){
            esValida = 0;
        }else{
            //evaluamos mes a mes que cumpla la cantidad de dias correspondientes
            switch(mes){
            case 1:
                    if( dia <= 0 || dia > 31){
                        esValida = 0;
                    }
                break;
            case 2:
                //contemplamos febrero bisiesto con 29 dias
                    if(esBisiesto){
                        if( dia <= 0 || dia > 29){
                            esValida = 0;
                        }
                    }else{
                        if( dia <= 0 || dia > 28){
                            esValida = 0;
                        }
                    }
                break;
            case 3:
                    if( dia <= 0 || dia > 31){
                        esValida = 0;
                    }
                break;
            case 4:
                    if( dia <= 0 || dia > 30){
                        esValida = 0;
                    }
                break;
            case 5:
                    if( dia <= 0 || dia > 31){
                        esValida = 0;
                    }
                break;
            case 6:
                    if( dia <= 0 || dia > 30){
                        esValida = 0;
                    }
                break;
            case 7:
                    if( dia <= 0 || dia > 31){
                        esValida = 0;
                    }
                break;
            case 8:
                    if( dia <= 0 || dia > 31){
                        esValida = 0;
                    }
                break;
            case 9:
                    if( dia <= 0 || dia > 30){
                        esValida = 0;
                    }
                break;
            case 10:
                    if( dia <= 0 || dia > 31){
                        esValida = 0;
                    }
                break;
            case 11:
                    if( dia <= 0 || dia > 30){
                        esValida = 0;
                    }
                break;
            case 12:
                    if( dia <= 0 || dia > 31){
                        esValida = 0;
                    }
                break;
            }
        }
    }

    if(esValida == 0){
        printf("Fecha invalida.\n");
    }

return esValida;

}

//funcion para dar alta a un nuevo cliente
void darAlta(FILE * arch){
int auxOrden;
cliente auxCliente;
int ultimaPos = 0;
int valido = 0;
int i;
int tipoCred;
char cadAux[50];

//leemos el archivo para saber la ultima posicion
fread(&auxCliente,sizeof(cliente),1,arch);
    while(!feof(arch)){
        ultimaPos++;
        fread(&auxCliente,sizeof(cliente),1,arch);
    }

    do{
        do{
            printf("Ingrese el n%cmero de orden: \n",163);
            fflush(stdin);
            gets(cadAux);
        }while(!esIntValido(cadAux));

        sscanf(cadAux, "%d", &auxOrden);
//aca se fija si el numero de orden ya está escrito por otro usuario (si es menor a ultimapos) o es válido
        if(auxOrden > ultimaPos){
            valido = 1;
        }else{ //tambien revisa si al ser menor a ultimapos, el orden es 0, entonces se puede escribir
            fseek(arch,(auxOrden-1)*(sizeof(cliente)),SEEK_SET);
            fread(&auxCliente,sizeof(cliente),1,arch);
            if(auxCliente.orden == 0){
                valido = 1;
            }
        }

    }while (auxOrden<0 || valido == 0);

//Completo con 0 los campos que no se llenaron entre la ultima posicion y la posicion actual. Ejemplo: si mi ultima pos es la 17
// y pedi la 25, de esta forma lleno con 0 los campos de la 18 a la 24
    if(auxOrden > ultimaPos){
        fseek(arch,0,SEEK_END);
        auxCliente.orden = 0;
        strcpy(auxCliente.nombre,"");
        strcpy(auxCliente.apellido,"");
        auxCliente.dia = 0;
        auxCliente.mes = 0;
        auxCliente.anio = 0;
        strcpy(auxCliente.mesL,"");
        strcpy(auxCliente.tipoCredito,"");
        auxCliente.importe = 0;
        auxCliente.nroCuota = 0;
        auxCliente.importeCuota = 0;
        auxCliente.iva = 0;
        auxCliente.totalCuota = 0;
        auxCliente.activo = 0;
        for(i = 1; i < (auxOrden - ultimaPos); i++){
            fseek(arch,0,SEEK_CUR);
            fwrite(&auxCliente,sizeof(cliente),1,arch);
        }
    }else{
        fseek(arch,(auxOrden-1)*sizeof(cliente),SEEK_SET);
    }

auxCliente.orden = auxOrden;
auxCliente.activo = 1;

//aca con el puntero posicionado segun el numero de orden indicado, comienzo a pedirle los datos al usuario
//tambien llamo a las funciones correspondientes de validacion para garantizar que si o si me ingrese el tipo de dato pedido.
    do{
    printf("Ingrese Nombre:");
    fflush(stdin);
    gets(cadAux);
    }while(!esCadenaValida(cadAux));

//llamo a normalizar cadena para que me quede en el formato correspondiente
normalizarCadena(cadAux);
strcpy(auxCliente.nombre,cadAux);

    do{
    printf("Ingrese Apellido:");
    fflush(stdin);
    gets(cadAux);
    }while(!esCadenaValida(cadAux));

normalizarCadena(cadAux);
strcpy(auxCliente.apellido,cadAux);

    do{
    printf("Ingrese Importe:");
    fflush(stdin);
    gets(cadAux);
    }while(!esNumFlotValido(cadAux));

sscanf(cadAux, "%f", &auxCliente.importe);

    do{
        do{
            printf("Ingrese tipo de credito: 1- A sola firma 2- Con Garantia: \n");
            fflush(stdin);
            gets(cadAux);
        }while(!esIntValido(cadAux));

        sscanf(cadAux, "%d", &tipoCred);
//evaluo que me ingrese si o si los unicos 2 tipos de creditos validos
    }while(tipoCred != 1 && tipoCred != 2);

    if(tipoCred == 1){
        strcpy(auxCliente.tipoCredito,"A sola firma");
    }
    else
    {
        strcpy(auxCliente.tipoCredito,"Con Garantia");
    }

    do{
        printf("Ingrese n%cmero de cuotas:", 163);
        fflush(stdin);
        gets(cadAux);
    }while(!esIntValido(cadAux));

    do{
        printf("\nIngrese fecha en formato dd/mm/aaaa:\n");
        scanf("%d/%d/%d",&auxCliente.dia,&auxCliente.mes,&auxCliente.anio);
    }while(!esFechaValida(auxCliente.dia,auxCliente.mes,auxCliente.anio));

//obtengo el mes en letras para imprimir
convertirMesLetras(auxCliente.mes,auxCliente.mesL);
//calculo los valores segun el importe y numero de cuotas ingresado
sscanf(cadAux, "%d", &auxCliente.nroCuota);
auxCliente.importeCuota = (auxCliente.importe / (float)auxCliente.nroCuota);
auxCliente.iva = auxCliente.importeCuota * 0.21;
auxCliente.totalCuota = auxCliente.importeCuota + auxCliente.iva;
fwrite(&auxCliente,sizeof(cliente),1,arch);
printf ("Alta dada con %cxito.\n", 130);

}


//valido la cadena, comparando que todos los caracteres ingresados esten entre los valores correspondientes de la tabla ascii (los casteo a int)
//y no sean numeros o simbolos

int esCadenaValida(char* cadena){
int esValido = 1;
    while(*cadena != '\0' && esValido == 1){
        if(((int)*cadena < 65 || ((int)*cadena > 90 && (int)*cadena < 97) || (int)*cadena > 122) && *cadena != ' ' ){
            esValido = 0;
            printf("Campo no v%clido.\n", 160);
        }else{
            if(*cadena == ' ' && *(cadena + 1) == ' '){
                    esValido = 0;
                    printf("Campo no v%clido.\n", 160);
                }
            }
        cadena++;
    }
return esValido;
}

//normalizo la cadena poniendo la primer letra en mayuscula y el resto en minuscula. También toma en cuenta apellidos compuestos
void normalizarCadena(char* cadena){
*cadena = toupper(*cadena);
cadena++;
    while(*cadena != '\0'){
        while(*cadena != ' ' && *cadena != '\0'){
            *cadena = tolower(*cadena);
            cadena++;
        }
        if( *cadena != '\0'){
            cadena++;
            *cadena = toupper(*cadena);
            cadena++;
        }
    }
}

//verifico si el numero float ingresado es valido. Lo ingreso como char y me fijo caracter a caracter que sean digitos y en caso de no serlos, que sea punto
//pero tambien tomo en cuenta que no se ingrese mas de un punto
int esNumFlotValido(char *cadena){
int esValido = 1;
char* inicio = cadena;
float flotante;
int excesoPunto = 0;

    if(*cadena == '.'){
        esValido = 0;
    }else{
        while(*cadena != '\0' && esValido == 1){
            if(!isdigit(*cadena)){
                if(*cadena != '.'){
                    esValido = 0;
                }else{
                    if(excesoPunto == 0){
                        excesoPunto = 1;
                    }else{
                        esValido = 0;
                    }
                }
            }
            cadena++;
        }
    }

cadena--;

//me fijo si el ultimo caracter de la cadena es punto. Si lo es, también lo tomo como invalido
    if(*cadena == '.'){
        esValido = 0;
    }else{
        sscanf(inicio, "%f", &flotante);
        if(flotante < 0){
            esValido = 0;
        }
    }


    if(esValido == 0){
        printf("Campo no v%clido.\n", 160);
    }

return esValido;

}

//validacion de un numero entero. Parecido al flotante, lo recorro caracter a caracter fijandome que sean digitos (uso la libreria ctype)
int esIntValido(char *cadena){
int esValido = 1;
int num;
char * inicio = cadena;

    while(*cadena != '\0' && esValido == 1){

        if(!isdigit(*cadena)){
            esValido = 0;
        }
        cadena++;
    }

    sscanf(inicio, "%d", &num);

    if(num <= 0){
        esValido = 0;
    }

    if(esValido == 0){
        printf("Campo no v%clido.\n", 160);
    }

return esValido;

}

//es el menu de busqueda para cuando el usuario ingresa la opcion 4
void menuBuscar(FILE* arch){
int opcion;
int numOrden;
char cadAux[100];
    do{
        printf("Ingrese modo de b%csqueda:\n", 163);
        printf("1- B%csqueda por numero de orden.\n", 163);
        printf("2- B%csqueda por Apellido.\n", 163);
        printf("0- Volver atr%cs.\n", 160);
        scanf("%d",&opcion);
        switch(opcion){
            case 1:
                    do{
                        printf("Ingrese n%cmero de orden a buscar:\n", 163);
                        fflush(stdin);
                        gets(cadAux);
                    }while(!esIntValido(cadAux));

                    sscanf(cadAux, "%d", &numOrden);

                    buscar(arch,numOrden,"");
                break;
            case 2:
                    do{
                        printf("Ingrese apellido a buscar:\n");
                        fflush(stdin);
                        gets(cadAux);
                    }while(!esCadenaValida(cadAux));

                    normalizarCadena(cadAux);

                    buscar(arch,0,cadAux);
                break;
        }
    }while(opcion != 0);

}


//funcion que busca en el archivo los clientes dependiendo si seleccionaron por numero de orden, por apellido o por fecha
void buscar(FILE* arch,int porOrden,char* apellido){
char nombreCliente[40];
cliente clientes;
int encontrado = 0;

fseek(arch,0,SEEK_SET);

    if(porOrden != 0){

        fseek(arch,(porOrden-1)*sizeof(cliente),SEEK_CUR);
        fread(&clientes,sizeof(cliente),1,arch);
        if(!feof(arch) && clientes.orden != 0){
            printf("Orden    Cliente          Importe    TipoCredito   Dia   Mes    A%co   NroCuotas   ImporteCuota  IVA  TotalCuota Activo \n",164);
            sprintf(nombreCliente, "%s %s", clientes.nombre, clientes.apellido);
            printf("%-6d %-17s %-10.2f %12s %4d %6s %6d %5d %17.2f %8.2f %8.2f %4d\n",clientes.orden, nombreCliente, clientes.importe, clientes.tipoCredito, clientes.dia, clientes.mesL, clientes.anio, clientes.nroCuota, clientes.importeCuota, clientes.iva, clientes.totalCuota,clientes.activo);
        }else{
            printf("No hubo coincidencias.\n");
        }

    }else{
    fread(&clientes,sizeof(cliente),1,arch);
        while(!feof(arch)){
            if(strcmp(clientes.apellido,apellido) == 0){
                printf("Orden    Cliente          Importe    TipoCredito   Dia   Mes    A%co   NroCuotas   ImporteCuota  IVA  TotalCuota Activo \n",164);
                sprintf(nombreCliente, "%s %s", clientes.nombre, clientes.apellido);
                printf("%-6d %-17s %-10.2f %12s %4d %6s %6d %5d %17.2f %8.2f %8.2f %4d\n",clientes.orden, nombreCliente, clientes.importe, clientes.tipoCredito, clientes.dia, clientes.mesL, clientes.anio, clientes.nroCuota, clientes.importeCuota, clientes.iva, clientes.totalCuota,clientes.activo);
                encontrado = 1;
            }
            fread(&clientes,sizeof(cliente),1,arch);
        }
        if(encontrado == 0){
            printf("No hubo coincidencias.\n");
            }
        }
}

//funcion que modifica un usuario dando un numero de orden y al cambiar el importe recalcula los otros campos (importe cuota, iva, etc)
void modificar(FILE* arch){
char auxCad[100];
char respuesta;
int numOrden;
int tipoCred;
char nombreCliente[40];
cliente auxCliente, clienteV;


    do{
        printf("Ingrese n%cmero de orden a modificar:\n", 163);
        fflush(stdin);
        gets(auxCad);
    }while(!esIntValido(auxCad));

sscanf(auxCad, "%d", &numOrden);

fseek(arch,(numOrden-1)*sizeof(cliente),SEEK_CUR);
fread(&auxCliente,sizeof(cliente),1,arch);
//guardo el valor del cliente antes de modificarlo
clienteV = auxCliente;
//me fijo mientras el orden del cliente no sea 0 y no sea fin del archivo, modifico en variable auxiliar
    if(!feof(arch) && auxCliente.orden != 0){
        do{
            printf("Ingrese nuevo importe:\n");
            fflush(stdin);
            gets(auxCad);
        }while(!esNumFlotValido(auxCad));

        sscanf(auxCad, "%f", &auxCliente.importe);

        do{
            do{
                printf("Ingrese nuevo tipo de cr%cdito: 1- A sola firma 2- Con Garantia: \n", 130);
                fflush(stdin);
                gets(auxCad);
            }while(!esIntValido(auxCad));

        sscanf(auxCad, "%d", &tipoCred);

        }while(tipoCred != 1 && tipoCred != 2);

        if(tipoCred == 1){
            strcpy(auxCliente.tipoCredito,"A sola firma");
        } else{
        strcpy(auxCliente.tipoCredito,"Con Garantia");
        }
//aca calculo los nuevos importes y cargo la struct auxCliente
        auxCliente.importeCuota = (auxCliente.importe / (float)auxCliente.nroCuota);
        auxCliente.iva = auxCliente.importeCuota * 0.21;
        auxCliente.totalCuota = auxCliente.importeCuota + auxCliente.iva;

        do{
                //imprimo los datos del cliente sin modificar usando la variable auxiliar clienteV, para que el usuario pueda
                //constatar si es ese el cliente que quiere cambiar
            printf("Orden    Cliente          Importe    TipoCredito   Dia   Mes    A%co   NroCuotas   ImporteCuota  IVA  TotalCuota Activo \n",164);
            sprintf(nombreCliente, "%s %s", clienteV.nombre, clienteV.apellido);
            printf("%-6d %-17s %-10.2f %12s %4d %6s %6d %5d %17.2f %8.2f %8.2f %4d\n",clienteV.orden, nombreCliente, clienteV.importe, clienteV.tipoCredito, clienteV.dia, clienteV.mesL, clienteV.anio, clienteV.nroCuota, clienteV.importeCuota, clienteV.iva, clienteV.totalCuota,clienteV.activo);
            printf("%cEsta seguro que desea modificarlo?  S/N\n", 168);
            fflush(stdin);
            scanf("%c",&respuesta);
        }while(toupper(respuesta) != 'S' && toupper(respuesta) != 'N');
//si acepta modificar el cliente, posiciono el puntero en el numero de orden y escribo el archivo con los campos modificados
        if(toupper(respuesta) == 'S'){
            fseek(arch,(numOrden-1)*sizeof(cliente),SEEK_SET);
            fwrite(&auxCliente,sizeof(cliente),1,arch);
            printf("Campo modificado correctamente \n");
        }else{
            printf("Modificaci%cn cancelada.\n", 162);
        }

    }else{
        printf("No se encontr%c el cliente a modificar.\n", 162);
    }

}

//funcion que da de baja a un usuario, poniendo en 0 su campo activo
void bajaLogica(FILE* arch){

char auxCad[100];
cliente clientes;
char nombreCliente[100];
char respuesta;
int numOrden;
cliente aux[1000];
int i=0;

    do{
        printf("Ingrese n%cmero de orden a dar de baja l%cgica:\n\n",163, 162);
        fflush(stdin);
        gets(auxCad);
    }while(!esIntValido(auxCad));

sscanf(auxCad, "%d", &numOrden);

fseek(arch,(numOrden-1)*sizeof(cliente),SEEK_CUR);
fread(&clientes,sizeof(cliente),1,arch);

    if(!feof(arch) && clientes.orden != 0){
        printf("Orden    Cliente          Importe    TipoCredito   Dia   Mes    A%co   NroCuotas   ImporteCuota  IVA  TotalCuota Activo \n",164);
        sprintf(nombreCliente, "%s %s", clientes.nombre, clientes.apellido);
        printf("%-6d %-17s %-10.2f %12s %4d %6s %6d %5d %17.2f %8.2f %8.2f %4d\n",clientes.orden, nombreCliente, clientes.importe, clientes.tipoCredito, clientes.dia, clientes.mesL, clientes.anio, clientes.nroCuota, clientes.importeCuota, clientes.iva, clientes.totalCuota,clientes.activo);
        do{
            printf("\n%cEsta seguro que desea darle de baja l%cgica? S/N\n\n", 168, 162);
            fflush(stdin);
            scanf("%c",&respuesta);
        }while(toupper(respuesta) != 'S' && toupper(respuesta) != 'N');

        if(toupper(respuesta) == 'S'){
            fseek(arch,(numOrden-1)*sizeof(cliente),SEEK_SET);
            clientes.activo = 0;
            printf("Baja realizada correctamente.\n\n");
            printf("Lista de clientes activos: \n\n");
            fwrite(&clientes,sizeof(cliente),1,arch);
            fseek(arch,0,SEEK_SET);
            while (!feof(arch)){
            fread(&aux[i],sizeof(cliente),1,arch);
            i++;
            }
            //emito los clientes con campo activo en 1
            emitirBin(aux, i-1,1,0,NULL);
        }else{
            printf("Baja l%cgica cancelada.\n\n", 162);
        }
    }else{
        printf("Cliente no encontrado.\n\n");
    }

}


//funcion que da de baja a los usuarios inactivos y los agrega a un archivo de texto xyz. Tiene un menu de opciones para
//saber si queres crear el archivo o si simplemente agregar mas bajas a un archivo creado con anterioridad
//de esta forma se toma en cuenta si en el mismo dia se quizo hacer 2 veces bajas logicas y fisicas y no se sobreescribe el archivo.
void menuBajaFisicaInactivos(FILE* arch,char nombreCompleto[]){
int opcion;
FILE* texto = NULL;

    do{
        printf("1- Crear archivo de texto para las bajas fisicas. (PRECAUCION !! Si ya esta creado, sera reemplazado por uno en blanco.)\n");
        printf("2- Dar bajas fisicas(con archivo ya creado).\n");
        printf("0- Volver atr%cs.\n", 160);
        scanf("%d",&opcion);
        switch(opcion){
        case 1: texto = abrir_archivo(texto,nombreCompleto,"wt");
                fprintf(texto, "Orden    Cliente          Importe    TipoCredito   Dia   Mes    A%co   NroCuotas   ImporteCuota  IVA  TotalCuota Activo \n",164);
                printf("Archivo creado con exito.\n\n");
                cerrar_archivo(texto);
            break;
        case 2: texto = abrir_archivo(texto,nombreCompleto,"r+t");
                if(!texto){
                    printf("No se encontr%c el archivo. Intente crearlo primero.\n\n", 162);
                }else{
                    bajaFisicaInactivos(arch,texto);
                    printf("Bajas dadas con exito.\n\n");
                    cerrar_archivo(texto);
                }

        }
    }while(opcion != 0);
}


//funcion que da las bajas fisicas colocando todos los campos en 0
void bajaFisicaInactivos(FILE* arch,FILE* texto){
cliente clientes;
int ordenAnt = 0;
char nombreCliente[100];
char linea[100];

fread(&clientes,sizeof(cliente),1,arch);

fgets(linea,sizeof(linea),texto);       //avanzo el archivo de texto hasta el final.
while(!feof(texto)){
    fgets(linea,sizeof(linea),texto);
}

    while(!feof(arch)){
            if(clientes.orden != 0){
                if(clientes.activo == 0){
                    sprintf(nombreCliente, "%s %s", clientes.nombre, clientes.apellido);
                    fprintf(texto,"%-6d %-17s %-10.2f %12s %4d %6s %6d %5d %17.2f %8.2f %8.2f %4d\n",clientes.orden, nombreCliente, clientes.importe, clientes.tipoCredito, clientes.dia, clientes.mesL, clientes.anio, clientes.nroCuota, clientes.importeCuota, clientes.iva, clientes.totalCuota,clientes.activo);
                    clientes.orden = ordenAnt;
                    clientes.orden = 0;
                    strcpy(clientes.nombre,"");
                    strcpy(clientes.apellido,"");
                    clientes.dia = 0;
                    clientes.mes = 0;
                    clientes.anio = 0;
                    strcpy(clientes.mesL,"");
                    strcpy(clientes.tipoCredito,"");
                    clientes.importe = 0;
                    clientes.nroCuota = 0;
                    clientes.importeCuota = 0;
                    clientes.iva = 0;
                    clientes.totalCuota = 0;
                    clientes.activo = 0;
                    fseek(arch,(ordenAnt-1)*sizeof(cliente),SEEK_CUR);
                    fwrite(&clientes,sizeof(cliente),1,arch);
                    fseek(arch,0,SEEK_CUR);
                    }
                }
                fread(&clientes,sizeof(cliente),1,arch);
        }
}

//funcion que emite el archivo de texto con las bajas
void emitirTxtBajas(FILE* texto){

char linea[1000];

fgets(linea,sizeof(linea),texto);
    while(!feof(texto)){
        printf("%s",linea);
        fgets(linea,sizeof(linea),texto);

    }

}

//Menu principal. En las opciones 3 en adelante verifico la creacion del archivo bin, sino tiro msj de error
void menu(cliente clientes []){
    int opcion;
    FILE * archivoBin = NULL;
    FILE * texto = NULL;
    time_t tiempoActual;
    struct tm* tiempoInfo;
    char fechaActual[15];
    char nombreCompleto[100];

    tiempoActual = time(NULL);

    tiempoInfo = localtime(&tiempoActual);

    strftime(fechaActual, sizeof(fechaActual), "%d-%m-%Y", tiempoInfo);
    snprintf(nombreCompleto, sizeof(nombreCompleto), "%s%s.xyz", "clientes_bajas_", fechaActual);

    do{
        printf("\n\t \t %cBienvenido! \n", 173);
        printf("Ingrese la opci%cn correspondiente : \n", 162);
        printf("1- Emitir planilla de clientes \n");
        printf("2- Crear archivo binario \n");
        printf("3- Migrar los datos de clientes al archivo binario \n");
        printf("4- Emitir el contenido del archivo binario \n");
        printf("5- Alta de cliente \n");
        printf("6- Buscar datos del cliente \n");
        printf("7- Modificar importe y tipo de cr%cdito del cliente \n", 130);
        printf("8- Baja logica de cliente \n");
        printf("9- Baja fisica de clientes inactivos \n");
        printf("10- Lista de datos clientes inactivos \n");
        printf("0- Salir.\n");
        scanf("%d", &opcion);
        switch (opcion){
        case 1: emitir(clientes);
                printf("\n Planilla emitida exitosamente..! \n\n");
            break;
        case 2: archivoBin = abrir_archivo(archivoBin, "creditos.dat", "wb");
                cerrar_archivo(archivoBin);
                printf("\n Archivo creado exitosamente..! \n\n");
            break;
        case 3:
                archivoBin = abrir_archivo(archivoBin,"creditos.dat","r+b");
                if(archivoBin){
                    migrarDatos(clientes,archivoBin);
                    cerrar_archivo(archivoBin);
                    printf("\nMigraci%cn exitosa.! \n\n", 162);
                }else{
                    printf("\nNo se encontr%c el archivo, intente crearlo primero.\n\n", 162);
                }
            break;
        case 4:
                archivoBin = abrir_archivo(archivoBin,"creditos.dat","r+b");
                if(archivoBin){
                    menuListarDat(archivoBin);
                    cerrar_archivo(archivoBin);
                }else{
                    printf("\nNo se encontr%c el archivo, intente crearlo primero.\n\n", 162);
                }
        break;
        case 5:
                archivoBin = abrir_archivo(archivoBin,"creditos.dat","r+b");
                if(archivoBin){
                    darAlta(archivoBin);
                    cerrar_archivo(archivoBin);
                }else{
                    printf("\nNo se encontr%c el archivo, intente crearlo primero.\n\n", 162);
                }
            break;
        case 6:
                archivoBin = abrir_archivo(archivoBin,"creditos.dat","r+b");
                if(archivoBin){
                    menuBuscar(archivoBin);
                    cerrar_archivo(archivoBin);
                }else{
                    printf("\nNo se encontr%c el archivo, intente crearlo primero.\n\n", 162);
                }
            break;
        case 7:
                archivoBin = abrir_archivo(archivoBin, "creditos.dat", "r+b");
                if (archivoBin){
                    modificar(archivoBin);
                    cerrar_archivo(archivoBin);
                }else{
                    printf("\nNo se encontr%c el archivo, intente crearlo primero. \n\n", 162);
                }
            break;
        case 8:
                archivoBin = abrir_archivo(archivoBin, "creditos.dat", "r+b");
                if (archivoBin){
                    bajaLogica(archivoBin);
                    cerrar_archivo(archivoBin);
                }else{
                    printf("\nNo se encont%c el archivo, intente crearlo primero. \n\n", 162);
                }
            break;
        case 9:
                archivoBin = abrir_archivo(archivoBin, "creditos.dat", "r+b");
                if (archivoBin){
                    menuBajaFisicaInactivos(archivoBin,nombreCompleto);
                    cerrar_archivo(archivoBin);
                }else{
                    printf("\nNo se encontr%c el archivo, intente crearlo primero. \n\n", 162);
                }
            break;
        case 10:
                texto = abrir_archivo(texto, nombreCompleto, "rt");
                if (texto){
                    emitirTxtBajas(texto);
                    cerrar_archivo(texto);
                }else{
                    printf("\nNo se encontr%c el archivo, intente crearlo primero. \n\n", 162);
                }
            break;
        }
    }while(opcion != 0);

}


