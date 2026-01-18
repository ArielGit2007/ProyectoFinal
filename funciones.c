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

void calcularICAPm2_5(){

    Zona zonas[100];
    int totalZonas = leerDatosActuales(zonas);
    for (int i = 0; i < totalZonas; i++)
    {
        float pm25 = zonas[i].NivelesAcual.PM2_5;
        if (pm25 >= 0 && pm25 <= 12)
            zonas[i].ica.pm2_5 = (50.0 / 12.0) * pm25;
        else if (pm25 > 12 && pm25 <= 35.4)
            zonas[i].ica.pm2_5 = ((100.0 - 51.0) / (35.4 - 12.1)) * (pm25 - 12.1) + 51.0;
        else if (pm25 > 35.4 && pm25 <= 55.4)
            zonas[i].ica.pm2_5 = ((150.0 - 101.0) / (55.4 - 35.5)) * (pm25 - 35.5) + 101.0;
        else if (pm25 > 55.4 && pm25 <= 150.4)
            zonas[i].ica.pm2_5 = ((200.0 - 151.0) / (150.4 - 55.5)) * (pm25 - 55.5) + 151.0;
        else if (pm25 > 150.4 && pm25 <= 250.4)
            zonas[i].ica.pm2_5 = ((300.0 - 201.0) / (250.4 - 150.5)) * (pm25 - 150.5) + 201.0;
        else if (pm25 > 250.4 && pm25 <= 350.4)
            zonas[i].ica.pm2_5 = ((400.0 - 301.0) / (350.4 - 250.5)) * (pm25 - 250.5) + 301.0;
        else if (pm25 > 350.4 && pm25 <= 500.4)
            zonas[i].ica.pm2_5 = ((500.0 - 401.0) / (500.4 - 350.5)) * (pm25 - 350.5) + 401.0;
        else
            zonas[i].ica.pm2_5 = -1; // Valor fuera de rango
        GuardarDatosActuales(&zonas[i]); // Guardar los datos actualizados
    }
    

}

void calcularICAPm10(){

    Zona zonas[100];
    int totalZonas = leerDatosActuales(zonas);
    for (int i = 0; i < totalZonas; i++)
    {
        float pm10 = zonas[i].NivelesAcual.PM10;
        if (pm10 >= 0 && pm10 <= 54)
            zonas[i].ica.pm10 = (50.0 / 54.0) * pm10;
        else if (pm10 > 54 && pm10 <= 154)
            zonas[i].ica.pm10 = ((100.0 - 51.0) / (154.0 - 55.0)) * (pm10 - 55.0) + 51.0;
        else if (pm10 > 154 && pm10 <= 254)
            zonas[i].ica.pm10 = ((150.0 - 101.0) / (254.0 - 155.0)) * (pm10 - 155.0) + 101.0;
        else if (pm10 > 254 && pm10 <= 354)
            zonas[i].ica.pm10 = ((200.0 - 151.0) / (354.0 - 255.0)) * (pm10 - 255.0) + 151.0;
        else if (pm10 > 354 && pm10 <= 424)
            zonas[i].ica.pm10 = ((300.0 - 201.0) / (424.0 - 355.0)) * (pm10 - 355.0) + 201.0;
        else if (pm10 > 424 && pm10 <= 504)
            zonas[i].ica.pm10 = ((400.0 - 301.0) / (504.0 - 425.0)) * (pm10 - 425.0) + 301.0;
        else if (pm10 > 504 && pm10 <= 604)
            zonas[i].ica.pm10 = ((500.0 - 401.0) / (604.0 - 505.0)) * (pm10 - 505.0) + 401.0;
        else
            zonas[i].ica.pm10 = -1; // Valor fuera de rango
        GuardarDatosActuales(&zonas[i]); // Guardar los datos actualizados
    }
}

void calcularICANO2(){

    Zona zonas[100];
    int totalZonas = leerDatosActuales(zonas);
    for (int i = 0; i < totalZonas; i++)
    {
        float no2 = zonas[i].NivelesAcual.NO2;
        if (no2<=53)
        {
            zonas[i].ica.NO2 = (50.0/53.0)* no2;
        }
        else if (no2>=54 && no2<=100)
        {
            zonas[i].ica.NO2 = ((100.0 - 51.0) / (100.0 - 54.0)) * (no2 - 54.0) + 51.0;
        }
        else if (no2>=101 && no2<=360)
        {
            zonas[i].ica.NO2 = ((150.0 - 101.0) / (360.0 - 101.0)) * (no2 - 101.0) + 101.0;
        }
        else if (no2>=361 && no2<=649)
        {
            zonas[i].ica.NO2 = ((200.0 - 151.0) / (649.0 - 361.0)) * (no2 - 361.0) + 151.0;
        }
        else if (no2>=650 && no2<=1249)
        {
            zonas[i].ica.NO2 = ((300.0 - 201.0) / (1249.0 - 650.0)) * (no2 - 650.0) + 201.0;
        }
        else if (no2>=1250 && no2<=1649)
        {
            zonas[i].ica.NO2 = ((400.0 - 301.0) / (1649.0 - 1250.0)) * (no2 - 1250.0) + 301.0;
        }
        else if (no2>=1650 && no2<=2049)
        {
            zonas[i].ica.NO2 = ((500.0 - 401.0) / (2049.0 - 1650.0)) * (no2 - 1650.0) + 401.0;
        }
        else
        {
            zonas[i].ica.NO2 = -1; // Valor fuera de rango
        }
        
        GuardarDatosActuales(&zonas[i]); // Guardar los datos actualizados
    }
    
}

void calcularICASO2(){

    Zona zonas[100];
    int totalZonas = leerDatosActuales(zonas);
    for (int i = 0; i < totalZonas; i++)
    {
        float so2 = zonas[i].NivelesAcual.SO2;
        // Cálculo del ICA para SO2 (similar a los anteriores)
        // Agregar las condiciones y fórmulas correspondientes aquí

        GuardarDatosActuales(&zonas[i]); // Guardar los datos actualizados
    }
    
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
void GuardarDatosHistoricos(Zona *zona){
    
    FILE *f;
    f= fopen("Historico.dat", "ab+");
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