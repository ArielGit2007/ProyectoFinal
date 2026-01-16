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

float leerFlotanteSoloMinimo(float inicio)
{
    float num;
    int val;
    do
    {
        val = scanf("%f", &num);
        if (val != 1 || num < inicio)
        {
            printf("El dato ingresado es invalido\n");
            while (getchar() != '\n')
                ;
        }
    } while (val != 1 || num < inicio);
    return num;
}

void DatosActuales(){

    Zona zona;
    getchar(); // Limpiar el buffer de entrada
    printf("Ingrese el nombre de la zona:\n");
    fgets(zona.nombreZona, sizeof(zona.nombreZona), stdin);
    printf("Ingrese los niveles de contaminantes actuales:\n");
    printf("PM2.5 (ug/m3): ");
    zona.NivelesAcual.PM2_5 = leerFlotanteSoloMinimo(0);
    printf("PM10 (ug/m3): ");
    zona.NivelesAcual.PM10 = leerFlotanteSoloMinimo(0);
    printf("NO2 (ppb): ");
    zona.NivelesAcual.NO2 = leerFlotanteSoloMinimo(0);
    printf("SO2 (ppb): ");
    zona.NivelesAcual.SO2 = leerFlotanteSoloMinimo(0);
    printf("O3 (ppb): ");
    zona.NivelesAcual.O3 = leerFlotanteSoloMinimo(0);
    printf("CO (ppm): ");
    zona.NivelesAcual.CO = leerFlotanteSoloMinimo(0);
    printf("Ingrese los factores climaticos asociados:\n");
    printf("Temperatura (C): ");
    zona.NivelesAcual.factores.temperatura = leerFlotanteSoloMinimo(-273); // Ejemplo de mínimo
    printf("Humedad (%%): ");
    zona.NivelesAcual.factores.humedad = leerFlotanteRango(0, 100);
    printf("Velocidad del viento (m/s): ");
    zona.NivelesAcual.factores.velocidadViento = leerFlotanteSoloMinimo(0);
    GuardarDatosActuales(&zona);
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
    fwrite(zona, sizeof(Zona), 1, f);
    fclose(f);
}

int leerDatosActuales(Zona *zonas){

   FILE *f;
    f = fopen("Contaminacion.dat", "rb");
    if (f == NULL)
    {
        f = fopen("Contaminacion.dat", "ab+");
        if (f != NULL)
            fclose(f);
        return 0;
    }
    int count = 0;
    while (fread(&zonas[count], sizeof(Zona), 1, f) == 1)
    {
        count++;
    }
    fclose(f);
    return count;
}