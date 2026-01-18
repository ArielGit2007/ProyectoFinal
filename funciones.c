#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void BorrarSaltolinea(char *a)
{
    int len = strlen(a);
    if (len > 0 && a[len - 1] == '\n')
    {                      // se asegura de que la cadena no este vacia y de que el ultimo caracter si sea un salto de linea
        a[len - 1] = '\0'; // De haber un salto de linea, lo cambia por el valor nulo
    }
}

void DatosActuales()
{

    Zona zona;
    getchar(); // Limpiar el buffer de entrada
    printf("Ingrese el nombre de la zona:\n");
    fgets(zona.nombreZona, sizeof(zona.nombreZona), stdin);
    BorrarSaltolinea(zona.nombreZona);
    printf("Ingrese los niveles de contaminantes actuales:\n");
    printf("PM2.5 (ug/m3): ");
    zona.NivelesAcual.PM2_5 = leerFlotanteSoloMinimo(0);
    printf("PM10 (ug/m3): ");
    zona.NivelesAcual.PM10 = leerFlotanteSoloMinimo(0);
    printf("NO2 (ppb): ");
    zona.NivelesAcual.NO2 = leerFlotanteSoloMinimo(0);
    printf("SO2 (ppb): ");
    zona.NivelesAcual.SO2 = leerFlotanteSoloMinimo(0);
    printf("O3 (ppm): ");
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
    // Calcular ICA
    calcularICAPm2_5(&zona);
    calcularICAPm10(&zona);
    calcularICANO2(&zona);
    calcularICASO2(&zona);
    calcularICAO3(&zona);
    calcularICACO(&zona);
    obtenerICA(&zona);
    calidadDelAire(&zona);
    GuardarDatosActuales(&zona);
}

void ingresoDatos()
{

    printf("1. Actualice los datos de una zona existente\n");
    printf("2. Ingrese una nueva zona\n");
    int opcion = leerIntegerRango(1, 2);
    if (opcion == 1)
    {
        FILE *f;
        f = fopen("Contaminacion.dat", "rb+"); // rb+ para lectura Y escritura
        if (f == NULL)
        {
            printf("No hay datos\n");
            return;
        }

        Zona zona;
        char nombreZona[50];
        getchar(); // Limpiar el buffer de entrada
        printf("Ingrese el nombre de la zona a actualizar:\n");
        fgets(nombreZona, sizeof(nombreZona), stdin);
        nombreZona[strcspn(nombreZona, "\n")] = 0; // Eliminar salto de línea

        int encontrado = 0;
        long pos;
        while (fread(&zona, sizeof(Zona), 1, f) == 1)
        {
            if (_stricmp(zona.nombreZona, nombreZona) == 0)
            {
                encontrado = 1;
                pos = ftell(f) - sizeof(Zona);
                break;
            }
        }

        if (encontrado)
        {
            printf("Ingrese los nuevos datos para la zona %s\n", zona.nombreZona);

            // Actualizar directamente la zona encontrada
            printf("PM2.5 (ug/m3): ");
            zona.NivelesAcual.PM2_5 = leerFlotanteSoloMinimo(0);
            printf("PM10 (ug/m3): ");
            zona.NivelesAcual.PM10 = leerFlotanteSoloMinimo(0);
            printf("NO2 (ppb): ");
            zona.NivelesAcual.NO2 = leerFlotanteSoloMinimo(0);
            printf("SO2 (ppb): ");
            zona.NivelesAcual.SO2 = leerFlotanteSoloMinimo(0);
            printf("O3 (ppm): ");
            zona.NivelesAcual.O3 = leerFlotanteSoloMinimo(0);
            printf("CO (ppm): ");
            zona.NivelesAcual.CO = leerFlotanteSoloMinimo(0);
            printf("Ingrese los factores climaticos asociados:\n");
            printf("Temperatura (C): ");
            zona.NivelesAcual.factores.temperatura = leerFlotanteSoloMinimo(-273);
            printf("Humedad (%%): ");
            zona.NivelesAcual.factores.humedad = leerFlotanteRango(0, 100);
            printf("Velocidad del viento (m/s): ");
            zona.NivelesAcual.factores.velocidadViento = leerFlotanteSoloMinimo(0);
            calcularICAPm2_5(&zona);
            calcularICAPm10(&zona);
            calcularICANO2(&zona);
            calcularICASO2(&zona);
            calcularICAO3(&zona);
            calcularICACO(&zona);
            obtenerICA(&zona);
            calidadDelAire(&zona);
            
            // Escribir en la posición correcta
            fseek(f, pos, SEEK_SET);
            fwrite(&zona, sizeof(Zona), 1, f);
            printf("Datos actualizados correctamente.\n");
        }
        else
        {
            printf("Zona no encontrada.\n");
        }
        fclose(f);
    }
    else if (opcion == 2)
    {
        DatosActuales();
    }
}
// Calculos

void calcularICAPm2_5(Zona *zona)
{
    float pm25 = zona->NivelesAcual.PM2_5;
    if (pm25 >= 0 && pm25 <= 12){
        zona->ica.ICA_PM2_5 = (50.0 / 12.0) * pm25;
        strcpy(zona->ica.calidad.nivelCalidadPM2_5, "Buena");}
    else if (pm25 > 12 && pm25 <= 35.4){
        zona->ica.ICA_PM2_5 = ((100.0 - 51.0) / (35.4 - 12.1)) * (pm25 - 12.1) + 51.0;
        strcpy(zona->ica.calidad.nivelCalidadPM2_5, "Moderada");}
    else if (pm25 > 35.4 && pm25 <= 55.4){
        zona->ica.ICA_PM2_5 = ((150.0 - 101.0) / (55.4 - 35.5)) * (pm25 - 35.5) + 101.0;
        strcpy(zona->ica.calidad.nivelCalidadPM2_5, "Insalubre para grupos sensibles");}
    else if (pm25 > 55.4 && pm25 <= 150.4){
        zona->ica.ICA_PM2_5 = ((200.0 - 151.0) / (150.4 - 55.5)) * (pm25 - 55.5) + 151.0;
        strcpy(zona->ica.calidad.nivelCalidadPM2_5, "Insalubre");}
    else if (pm25 > 150.4 && pm25 <= 250.4){
        zona->ica.ICA_PM2_5 = ((300.0 - 201.0) / (250.4 - 150.5)) * (pm25 - 150.5) + 201.0;
        strcpy(zona->ica.calidad.nivelCalidadPM2_5, "Muy insalubre");}
    else if (pm25 > 250.4 && pm25 <= 500.4){
        zona->ica.ICA_PM2_5 = ((500.0 - 301.0) / (500.4 - 250.5)) * (pm25 - 250.5) + 301.0;
        strcpy(zona->ica.calidad.nivelCalidadPM2_5, "Peligrosa");}
    else if (pm25>500.4){
        zona->ica.ICA_PM2_5 = (0-500.0) / (0-500.5) * (pm25 - 500.5) + 500.0;
        strcpy(zona->ica.calidad.nivelCalidadPM2_5, "Extrema emergencia");}
    
    
}
void calcularICAPm10(Zona *zona)
{

    float pm10 = zona->NivelesAcual.PM10;
    if (pm10 >= 0 && pm10 <= 54){
        zona->ica.ICA_PM10 = (50.0 / 54.0) * pm10;
        strcpy(zona->ica.calidad.nivelCalidadPM10, "Buena");}
    else if (pm10 > 54 && pm10 <= 154){
        zona->ica.ICA_PM10 = ((100.0 - 51.0) / (154.0 - 55.0)) * (pm10 - 55.0) + 51.0;
        strcpy(zona->ica.calidad.nivelCalidadPM10, "Moderada");}
    else if (pm10 > 154 && pm10 <= 254){
        zona->ica.ICA_PM10 = ((150.0 - 101.0) / (254.0 - 155.0)) * (pm10 - 155.0) + 101.0;
        strcpy(zona->ica.calidad.nivelCalidadPM10, "Insalubre para grupos sensibles");}
    else if (pm10 > 254 && pm10 <= 354){
        zona->ica.ICA_PM10 = ((200.0 - 151.0) / (354.0 - 255.0)) * (pm10 - 255.0) + 151.0;
        strcpy(zona->ica.calidad.nivelCalidadPM10, "Insalubre");}
    else if (pm10 > 354 && pm10 <= 424){
        zona->ica.ICA_PM10 = ((300.0 - 201.0) / (424.0 - 355.0)) * (pm10 - 355.0) + 201.0;
        strcpy(zona->ica.calidad.nivelCalidadPM10, "Muy insalubre");}
    else if (pm10 > 424 && pm10 <= 604){
        zona->ica.ICA_PM10 = ((500.0 - 301.0) / (604.0 - 425.0)) * (pm10 - 425.0) + 301.0;
        strcpy(zona->ica.calidad.nivelCalidadPM10, "Peligrosa");}
    else{
        zona->ica.ICA_PM10 = ((0 - 500) / (0 - 605)) * (pm10 - 605.0) + 500.0;; // Valor fuera de rango
        strcpy(zona->ica.calidad.nivelCalidadPM10, "Extrema emergencia");
}
}
void calcularICANO2(Zona *zona)
{
    float no2 = zona->NivelesAcual.NO2;
    if (no2 <= 53)
    {
        zona->ica.ICA_NO2 = (50.0 / 53.0) * no2;
        strcpy(zona->ica.calidad.nivelCalidadNO2, "Buena");
    }
    else if (no2 >= 54 && no2 <= 100)
    {
        zona->ica.ICA_NO2 = ((100.0 - 51.0) / (100.0 - 54.0)) * (no2 - 54.0) + 51.0;
        strcpy(zona->ica.calidad.nivelCalidadNO2, "Moderada");
    }
    else if (no2 >= 101 && no2 <= 360)
    {
        zona->ica.ICA_NO2 = ((150.0 - 101.0) / (360.0 - 101.0)) * (no2 - 101.0) + 101.0;
        strcpy(zona->ica.calidad.nivelCalidadNO2, "Insalubre para grupos sensibles");
    }
    else if (no2 > 360 && no2 <= 649)
    {
        zona->ica.ICA_NO2 = ((200.0 - 151.0) / (649.0 - 361.0)) * (no2 - 361.0) + 151.0;
        strcpy(zona->ica.calidad.nivelCalidadNO2, "Insalubre");
    }
    else if (no2 > 649 && no2 <= 1249)
    {
        zona->ica.ICA_NO2 = ((300.0 - 201.0) / (1249.0 - 650.0)) * (no2 - 650.0) + 201.0;
        strcpy(zona->ica.calidad.nivelCalidadNO2, "Muy insalubre");
    }
    else if (no2 >= 1250 && no2 <= 2049)
    {
        zona->ica.ICA_NO2 = ((500.0 - 301.0) / (2049.0 - 1250.0)) * (no2 - 1250.0) + 301.0;
        strcpy(zona->ica.calidad.nivelCalidadNO2, "Peligrosa");
    }
    else
    {
        zona->ica.ICA_NO2 = ((0 - 501.0) / (0 - 2050.0)) * (no2 - 2050.0) + 501.0; // Valor fuera de rango
        strcpy(zona->ica.calidad.nivelCalidadNO2, "Extrema emergencia");
    }
}

void calcularICASO2(Zona *zona)
{

    float so2 = zona->NivelesAcual.SO2;
    if (so2 <= 35)
    {
        zona->ica.ICA_SO2 = (50.0 / 35.0) * so2;
        strcpy(zona->ica.calidad.nivelCalidadSO2, "Buena");
    }
    else if (so2 >= 36 && so2 <= 75)
    {
        zona->ica.ICA_SO2 = ((100.0 - 51.0) / (75.0 - 36.0)) * (so2 - 36.0) + 51.0;
        strcpy(zona->ica.calidad.nivelCalidadSO2, "Moderada");
    }
    else if (so2 >= 76 && so2 <= 185)
    {
        zona->ica.ICA_SO2 = ((150.0 - 101.0) / (185.0 - 76.0)) * (so2 - 76.0) + 101.0;
        strcpy(zona->ica.calidad.nivelCalidadSO2, "Insalubre para grupos sensibles");
    }
    else if (so2 > 185 && so2 <= 304)
    {
        zona->ica.ICA_SO2 = ((200.0 - 151.0) / (304.0 - 186.0)) * (so2 - 186.0) + 151.0;
        strcpy(zona->ica.calidad.nivelCalidadSO2, "Insalubre");
    }
    else if (so2 > 304 && so2 <= 604)
    {
        zona->ica.ICA_SO2 = ((300.0 - 201.0) / (604.0 - 305.0)) * (so2 - 305.0) + 201.0;
        strcpy(zona->ica.calidad.nivelCalidadSO2, "Muy insalubre");
    }
    else if (so2 >= 605 && so2 <= 1004)
    {
        zona->ica.ICA_SO2 = ((500.0 - 301.0) / (1004.0 - 605.0)) * (so2 - 605.0) + 301.0;
        strcpy(zona->ica.calidad.nivelCalidadSO2, "Peligrosa");
    }
    else
    {
        zona->ica.ICA_SO2 = ((0 - 501.0) / (0 - 1005.0)) * (so2 - 1005.0) + 501.0; // Valor fuera de rango
        strcpy(zona->ica.calidad.nivelCalidadSO2, "Extrema emergencia");
    }
}

void calcularICAO3(Zona *zona)
{
    float o3 = zona->NivelesAcual.O3;
    if (o3 <= 0.054)
    {
        zona->ica.ICA_O3 = (50.0 / 0.054) * o3;
        strcpy(zona->ica.calidad.nivelCalidadO3, "Buena");
    }
    else if (o3 >= 0.055 && o3 <= 0.070)
    {
        zona->ica.ICA_O3 = ((100.0 - 51.0) / (0.070 - 0.055)) * (o3 - 0.055) + 51.0;
        strcpy(zona->ica.calidad.nivelCalidadO3, "Moderada");
    }
    else if (o3 > 0.070 && o3 <= 0.085)
    {
        zona->ica.ICA_O3 = ((150.0 - 101.0) / (0.085 - 0.071)) * (o3 - 0.071) + 101.0;
        strcpy(zona->ica.calidad.nivelCalidadO3, "Insalubre para grupos sensibles");
    }
    else if (o3 > 0.085 && o3 <= 0.105)
    {
        zona->ica.ICA_O3 = ((200.0 - 151.0) / (0.105 - 0.086)) * (o3 - 0.086) + 151.0;
        strcpy(zona->ica.calidad.nivelCalidadO3, "Insalubre");
    }
    else if (o3 > 0.105 && o3 <= 0.200)
    {
        zona->ica.ICA_O3 = ((300.0 - 201.0) / (0.200 - 0.106)) * (o3 - 0.106) + 201.0;
        strcpy(zona->ica.calidad.nivelCalidadO3, "Muy insalubre");
    }
    else
    {
        zona->ica.ICA_O3 = -1; // Valor fuera de rango
        strcpy(zona->ica.calidad.nivelCalidadO3, "Extrema emergencia");
    }
}

void calcularICACO(Zona *zonas)
{

    float co = zonas->NivelesAcual.CO;
    if (co >= 0 && co <= 4.4)
    {
        zonas->ica.ICA_CO = (50.0 / 4.4) * co;
        strcpy(zonas->ica.calidad.nivelCalidadCO, "Buena");
    }
    else if (co >= 4.5 && co <= 9.4)
    {
        zonas->ica.ICA_CO = ((100.0 - 51.0) / (9.4 - 4.5)) * (co - 4.5) + 51.0;
        strcpy(zonas->ica.calidad.nivelCalidadCO, "Moderada");
    }
    else if (co >= 9.5 && co <= 12.4)
    {
        zonas->ica.ICA_CO = ((150.0 - 101.0) / (12.4 - 9.5)) * (co - 9.5) + 101.0;
        strcpy(zonas->ica.calidad.nivelCalidadCO, "Insalubre para grupos sensibles");
    }
    else if (co > 12.4 && co <= 15.4)
    {
        zonas->ica.ICA_CO = ((200.0 - 151.0) / (15.4 - 12.5)) * (co - 12.5) + 151.0;
        strcpy(zonas->ica.calidad.nivelCalidadCO, "Insalubre");
    }
    else if (co > 15.4 && co <= 30.4)
    {
        zonas->ica.ICA_CO = ((300.0 - 201.0) / (30.4 - 15.5)) * (co - 15.5) + 201.0;
        strcpy(zonas->ica.calidad.nivelCalidadCO, "Muy insalubre");
    }
    else if (co >= 30.5 && co <= 50.4)
    {
        zonas->ica.ICA_CO = ((500.0 - 301.0) / (50.4 - 30.5)) * (co - 30.5) + 301.0;
        strcpy(zonas->ica.calidad.nivelCalidadCO, "Peligrosa");
    }
    else
    {
        zonas->ica.ICA_CO = ((0 - 501.0) / (0 - 50.5)) * (co - 50.5) + 501.0; // Valor fuera de rango
        strcpy(zonas->ica.calidad.nivelCalidadCO, "Extrema emergencia");
    }
}

void obtenerICA(Zona *zona)
{

    float valores[] = {
        zona->ica.ICA_PM2_5,
        zona->ica.ICA_PM10,
        zona->ica.ICA_NO2,
        zona->ica.ICA_SO2,
        zona->ica.ICA_O3,
        zona->ica.ICA_CO};

    float maximo = valores[0];
    for (int j = 1; j < 6; j++)
    {
        if (valores[j] > maximo)
        {
            maximo = valores[j];
        }
    }
    zona->ica.ICA = maximo;
}

void calidadDelAire(Zona *zona)
{
    float ica = zona->ica.ICA;
    if (ica >= 0 && ica <= 50)
    {
        strcpy(zona->calidadAire, "Buena");
    }
    else if (ica >= 51 && ica <= 100)
    {
        strcpy(zona->calidadAire, "Moderada");
    }
    else if (ica >= 101 && ica <= 150)
    {
        strcpy(zona->calidadAire, "Insalubre para grupos sensibles");
    }
    else if (ica >= 151 && ica <= 200)
    {
        strcpy(zona->calidadAire, "Insalubre");
    }
    else if (ica >= 201 && ica <= 300)
    {
        strcpy(zona->calidadAire, "Muy insalubre");
    }
    else if (ica > 300 && ica <= 500)
    {
        strcpy(zona->calidadAire, "Peligrosa");
    }
    else
    {
        strcpy(zona->calidadAire, "Más allá de la escala/Extrema emergencia");
    }
}
// Reporte y guardado de datos

void reporteZonas()
{
    Zona zonas[100];
    int totalZonas = leerDatosActuales(zonas);
    if (totalZonas == 0)
    {
        printf("No hay datos de zonas disponibles.\n");
    }
    else
    {
        printf("Que zona desea consultar?\n");
        for (int i = 0; i < totalZonas; i++)
        {
            printf("%d. %s\n", i + 1, zonas[i].nombreZona);
        }
        int opcion = leerIntegerRango(1, totalZonas);
        Zona zonaSeleccionada = zonas[opcion - 1];
        printf("Reporte de la zona: %s\n", zonaSeleccionada.nombreZona);
        printf("ICA General de la zona: %.2f\n", zonaSeleccionada.ica.ICA);
        printf("Calidad del aire general: %s\n", zonaSeleccionada.calidadAire);
        printf("Niveles actuales de contaminantes:\n");
        printf("|%-15s |%-10s |%-10s |%-15s\n", "Contaminante", "Nivel", "ICA", "Calidad");
        printf("----------------------------------------------------------\n");
        printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "PM2.5(ug/m3)", zonaSeleccionada.NivelesAcual.PM2_5, zonaSeleccionada.ica.ICA_PM2_5, zonaSeleccionada.ica.calidad.nivelCalidadPM2_5);
        printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "PM10(ug/m3)", zonaSeleccionada.NivelesAcual.PM10, zonaSeleccionada.ica.ICA_PM10, zonaSeleccionada.ica.calidad.nivelCalidadPM10);
        printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "NO2(ppb)", zonaSeleccionada.NivelesAcual.NO2, zonaSeleccionada.ica.ICA_NO2, zonaSeleccionada.ica.calidad.nivelCalidadNO2);
        printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "SO2(ppb)", zonaSeleccionada.NivelesAcual.SO2, zonaSeleccionada.ica.ICA_SO2, zonaSeleccionada.ica.calidad.nivelCalidadSO2);
        printf("|%-15s |%-10.2f |%-10.3f |%-15s\n", "O3(ppm)", zonaSeleccionada.NivelesAcual.O3, zonaSeleccionada.ica.ICA_O3, zonaSeleccionada.ica.calidad.nivelCalidadO3);
        printf("|%-15s |%-10.2f |%-10.3f |%-15s\n", "CO(ppm)", zonaSeleccionada.NivelesAcual.CO, zonaSeleccionada.ica.ICA_CO, zonaSeleccionada.ica.calidad.nivelCalidadCO);
        printf("Factores climaticos asociados:\n");
        printf("Temperatura: %.2f C\n", zonaSeleccionada.NivelesAcual.factores.temperatura);
        printf("Humedad: %.2f %%\n", zonaSeleccionada.NivelesAcual.factores.humedad);
        printf("Velocidad del viento: %.2f m/s\n", zonaSeleccionada.NivelesAcual.factores.velocidadViento);
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
void GuardarDatosHistoricos(Zona *zona)
{

    FILE *f;
    f = fopen("Historico.dat", "ab+");
    if (f == NULL)
    {
        printf("No se puede abrir el archivo\n");
        return;
    }
    fwrite(zona, sizeof(Zona), 1, f);
    fclose(f);
}

int leerDatosActuales(Zona *zonas)
{

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