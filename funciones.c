#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
int leerIntegerRango(int inicio, int fin)
{
    int num;
    int val;
    do
    {
        val = scanf("%d", &num);
        if (val != 1 || num < inicio || num > fin)
        {
            printf("El dato ingresado es invalido\n");
            while (getchar() != '\n')
                ;
        }
    } while (val != 1 || num < inicio || num > fin);
    return num;
}
float leerFlotanteRango(float inicio, float fin)
{
    float num;
    int val;
    do
    {
        val = scanf("%f", &num);
        if (val != 1 || num < inicio || num > fin)
        {
            printf("El dato ingresado es invalido\n");
            while (getchar() != '\n')
                ;
        }
    } while (val != 1 || num < inicio || num > fin);
    return num;
}

void DatosActuales(){

    Zona zona;
    printf("Ingrese el nombre de la zona:\n");
    fgets(zona.nombreZona, sizeof(zona.nombreZona), stdin);
}



// ARCHIVOS BINARIOS
void GuardarDatosActuales(Zona *zona)
{
    FILE *f;
    f = fopen("Contaminacion.dat", "ab+");
    if (f == NULL)
    {
        printf("No se puede abrir el archivo\n");
        return;
    }
    fwrite(autos, sizeof(DatosAuto), 1, f);
    fclose(f);
}