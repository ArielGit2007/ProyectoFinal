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
            // Guardar copia en historico
            GuardarDatosHistoricos(&zona);
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
    else if (co > 4.4 && co <= 9.4)
    {
        zonas->ica.ICA_CO = ((100.0 - 51.0) / (9.4 - 4.5)) * (co - 4.5) + 51.0;
        strcpy(zonas->ica.calidad.nivelCalidadCO, "Moderada");
    }
    else if (co > 9.4 && co <= 12.4)
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
    else if (co > 30.4 && co <= 50.4)
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
        strcpy(zona->calidadAire, "Extrema emergencia");
    }
}

//Prevenciones
void prevenirContaminacion(Zona *zona)
{
    float ica = zona->ica.ICA;
    
    printf("\n=== RECOMENDACIONES DE SALUD ===\n");
    printf("ICA: %.2f - %s\n\n", ica, zona->calidadAire);
    
    if (ica >= 0 && ica <= 50)
    {
        printf("- Calidad del aire satisfactoria\n");
        printf("- Ideal para actividades al aire libre\n");
        printf("- Sin restricciones para ninguna poblacion\n");
    }
    else if (ica >= 51 && ica <= 100)
    {
        printf("- Personas sensibles consideren limitar actividades prolongadas\n");
        printf("- Poblacion general puede realizar actividades normales\n");
        printf("- Monitorear sintomas en grupos vulnerables\n");
    }
    else if (ica >= 101 && ica <= 150)
    {
        printf("- Ninos, ancianos y personas con enfermedades respiratorias/cardiacas\n");
        printf("  deben limitar esfuerzos prolongados al aire libre\n");
        printf("- Poblacion general puede continuar actividades con precaucion\n");
        printf("- Considerar posponer ejercicio intenso al aire libre\n");
    }
    else if (ica >= 151 && ica <= 200)
    {
        printf("- Todos deben limitar esfuerzos prolongados al aire libre\n");
        printf("- Grupos sensibles eviten actividades extenuantes\n");
        printf("- Mantener ventanas cerradas si es posible\n");
        printf("- Considerar uso de mascarilla al salir\n");
    }
    else if (ica >= 201 && ica <= 300)
    {
        printf("- Todos eviten esfuerzos al aire libre\n");
        printf("- Grupos sensibles permanezcan en interiores\n");
        printf("- Usar mascarilla si es necesario salir\n");
        printf("- Mantener ventanas cerradas\n");
        printf("- Usar purificadores de aire si estan disponibles\n");
    }
    else if (ica >= 301 && ica <= 500)
    {
        printf("- ALERTA: Todos permanezcan en interiores\n");
        printf("- Mantener ventanas y puertas cerradas\n");
        printf("- Usar purificadores de aire\n");
        printf("- Evitar cualquier actividad al aire libre\n");
        printf("- Grupos sensibles busquen atencion medica si presentan sintomas\n");
    }
    else
    {
        printf("- EMERGENCIA SANITARIA: Condiciones peligrosas\n");
        printf("- Evacuacion recomendada si es posible\n");
        printf("- Usar equipo de proteccion respiratoria\n");
        printf("- Buscar atencion medica inmediata si presenta sintomas\n");
        printf("- Mantener contacto con autoridades locales\n");
    }
    
    printf("\nGrupos sensibles: ninos, ancianos, mujeres embarazadas,\n");
    printf("personas con asma, EPOC, enfermedades cardiacas.\n");
}

// Reporte y guardado de datos

/* Promedia los últimos 30 registros guardados para una zona dada */

int promedioUltimos30( char *nombreZona,
                      float *pm25, float *pm10, float *no2,
                      float *so2, float *o3, float *co)
{
    FILE *f = fopen("Historico.dat", "rb");
    if (!f) return 0;

    Zona registros[500]; /* ajusta tamaño si necesitas más */
    int total = 0;
    while (fread(&registros[total], sizeof(Zona), 1, f) == 1 && total < 500) {
        total++;
    }
    fclose(f);

    int count = 0;
    *pm25 = *pm10 = *no2 = *so2 = *o3 = *co = 0;

    for (int i = total - 1; i >= 0 && count < 30; i--) {
        if (_stricmp(registros[i].nombreZona, nombreZona) == 0) {
            *pm25 += registros[i].NivelesAcual.PM2_5;
            *pm10 += registros[i].NivelesAcual.PM10;
            *no2  += registros[i].NivelesAcual.NO2;
            *so2  += registros[i].NivelesAcual.SO2;
            *o3   += registros[i].NivelesAcual.O3;
            *co   += registros[i].NivelesAcual.CO;
            count++;
        }
    }
    if (count == 0) return 0;

    *pm25 /= count; *pm10 /= count; *no2 /= count; *so2 /= count; *o3 /= count; *co /= count;
    return count;
}

/* Reporte simple: pide la zona y muestra promedios de los últimos 30 guardados */
void reportePromediosHistoricos()
{
    char nombreZona[50];
    getchar(); /* limpiar buffer */
    printf("Ingrese el nombre de la zona para promediar (ultimos 30):\n");
    fgets(nombreZona, sizeof(nombreZona), stdin);
    nombreZona[strcspn(nombreZona, "\n")] = 0;

    float pm25, pm10, no2, so2, o3, co;
    int usados = promedioUltimos30(nombreZona, &pm25, &pm10, &no2, &so2, &o3, &co);
    if (usados == 0) {
        printf("No hay registros historicos para esa zona.\n");
        return;
    }

    printf("Promedio de los ultimos %d registros para %s:\n", usados, nombreZona);
    printf("PM2.5: %.2f\n", pm25);
    printf("PM10 : %.2f\n", pm10);
    printf("NO2  : %.2f\n", no2);
    printf("SO2  : %.2f\n", so2);
    printf("O3   : %.3f\n", o3);
    printf("CO   : %.2f\n", co);
}

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
        printf("Niveles actuales de contaminantes:\n");
        printf("|%-15s |%-10s |%-10s |%-15s\n", "Contaminante", "Nivel", "ICA", "Calidad");
        printf("----------------------------------------------------------\n");
        printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "PM2.5(ug/m3)", zonaSeleccionada.NivelesAcual.PM2_5, zonaSeleccionada.ica.ICA_PM2_5, zonaSeleccionada.ica.calidad.nivelCalidadPM2_5);
        printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "PM10(ug/m3)", zonaSeleccionada.NivelesAcual.PM10, zonaSeleccionada.ica.ICA_PM10, zonaSeleccionada.ica.calidad.nivelCalidadPM10);
        printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "NO2(ppb)", zonaSeleccionada.NivelesAcual.NO2, zonaSeleccionada.ica.ICA_NO2, zonaSeleccionada.ica.calidad.nivelCalidadNO2);
        printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "SO2(ppb)", zonaSeleccionada.NivelesAcual.SO2, zonaSeleccionada.ica.ICA_SO2, zonaSeleccionada.ica.calidad.nivelCalidadSO2);
        printf("|%-15s |%-10.2f |%-10.3f |%-15s\n", "O3(ppm)", zonaSeleccionada.NivelesAcual.O3, zonaSeleccionada.ica.ICA_O3, zonaSeleccionada.ica.calidad.nivelCalidadO3);
        printf("|%-15s |%-10.2f |%-10.3f |%-15s\n", "CO(ppm)", zonaSeleccionada.NivelesAcual.CO, zonaSeleccionada.ica.ICA_CO, zonaSeleccionada.ica.calidad.nivelCalidadCO);
        printf("----------------------------------------------------------\n");
        printf("Factores climaticos asociados:\n");
        printf("Temperatura: %.2f C\n", zonaSeleccionada.NivelesAcual.factores.temperatura);
        printf("Humedad: %.2f %%\n", zonaSeleccionada.NivelesAcual.factores.humedad);
        printf("Velocidad del viento: %.2f m/s\n", zonaSeleccionada.NivelesAcual.factores.velocidadViento);
        
        // Mostrar recomendaciones
        prevenirContaminacion(&zonaSeleccionada);
        printf("\n");

        /* Mostrar predicción para las próximas 24 horas */
        printf("=== PREDICCION PROXIMAS 24 HORAS ===\n");
        float pm25pred, pm10pred, no2pred, so2pred, o3pred, copred;
        float temppred, humedadpred, vvientopred;
        int usados = prediccionPonderada(zonaSeleccionada.nombreZona, 
                                         &pm25pred, &pm10pred, &no2pred, &so2pred, &o3pred, &copred,
                                         &temppred, &humedadpred, &vvientopred);
        
        if (usados > 0) {
            printf("(basado en ultimos %d registros, ajustados por clima)\n", usados);
            
            // Crear zona temporal con valores predichos para calcular ICA
            Zona zonaPred;
            strcpy(zonaPred.nombreZona, zonaSeleccionada.nombreZona);
            zonaPred.NivelesAcual.PM2_5 = pm25pred;
            zonaPred.NivelesAcual.PM10 = pm10pred;
            zonaPred.NivelesAcual.NO2 = no2pred;
            zonaPred.NivelesAcual.SO2 = so2pred;
            zonaPred.NivelesAcual.O3 = o3pred;
            zonaPred.NivelesAcual.CO = copred;
            zonaPred.NivelesAcual.factores.temperatura = temppred;
            zonaPred.NivelesAcual.factores.humedad = humedadpred;
            zonaPred.NivelesAcual.factores.velocidadViento = vvientopred;
            
            // Calcular ICA predicho usando las mismas funciones
            calcularICAPm2_5(&zonaPred);
            calcularICAPm10(&zonaPred);
            calcularICANO2(&zonaPred);
            calcularICASO2(&zonaPred);
            calcularICAO3(&zonaPred);
            calcularICACO(&zonaPred);
            obtenerICA(&zonaPred);
            calidadDelAire(&zonaPred);
            
            printf("\n*** CALIDAD DEL AIRE PREDICHA: %s (ICA: %.2f) ***\n\n", zonaPred.calidadAire, zonaPred.ica.ICA);
            
            printf("Niveles predichos de contaminantes:\n");
            printf("|%-15s |%-10s |%-10s |%-15s\n", "Contaminante", "Nivel", "ICA", "Calidad");
            printf("----------------------------------------------------------\n");
            printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "PM2.5(ug/m3)", zonaPred.NivelesAcual.PM2_5, zonaPred.ica.ICA_PM2_5, zonaPred.ica.calidad.nivelCalidadPM2_5);
            printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "PM10(ug/m3)", zonaPred.NivelesAcual.PM10, zonaPred.ica.ICA_PM10, zonaPred.ica.calidad.nivelCalidadPM10);
            printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "NO2(ppb)", zonaPred.NivelesAcual.NO2, zonaPred.ica.ICA_NO2, zonaPred.ica.calidad.nivelCalidadNO2);
            printf("|%-15s |%-10.2f |%-10.2f |%-15s\n", "SO2(ppb)", zonaPred.NivelesAcual.SO2, zonaPred.ica.ICA_SO2, zonaPred.ica.calidad.nivelCalidadSO2);
            printf("|%-15s |%-10.2f |%-10.3f |%-15s\n", "O3(ppm)", zonaPred.NivelesAcual.O3, zonaPred.ica.ICA_O3, zonaPred.ica.calidad.nivelCalidadO3);
            printf("|%-15s |%-10.2f |%-10.3f |%-15s\n", "CO(ppm)", zonaPred.NivelesAcual.CO, zonaPred.ica.ICA_CO, zonaPred.ica.calidad.nivelCalidadCO);
            printf("----------------------------------------------------------\n");
            printf("Factores climaticos predichos:\n");
            printf("Temperatura: %.2f C\n", temppred);
            printf("Humedad: %.2f %%\n", humedadpred);
            printf("Velocidad del viento: %.2f m/s\n", vvientopred);
            
            // Alertas preventivas
            printf("\n=== ALERTAS PREVENTIVAS Y RECOMENDACIONES ===\n");
            int hayAlertas = 0;
            
            if (zonaPred.ica.ICA > 100 &&zonaPred.ica.ICA <=150) {
                printf("\n** ALERTA: Calidad del aire NO aceptable **\n");
                printf("El ICA predicho (%.2f) supera el nivel moderado.\n", zonaPred.ica.ICA);
                hayAlertas = 1;
                
                printf("\nMEDIDAS DE PROTECCION PERSONAL:\n");
                printf("- Reducir actividades al aire libre prolongadas\n");
                printf("- Grupos sensibles: ninos, ancianos, asmaticos deben limitar exposicion\n");
                printf("- Mantenerse hidratado\n");
                printf("- Monitorear sintomas respiratorios\n");}
                
            if (zonaPred.ica.ICA > 150 && zonaPred.ica.ICA <= 200) {
                    printf("\n!! ALERTA IMPORTANTE: Nivel INSALUBRE !!\n");
                    printf("\nMEDIDAS INMEDIATAS:\n");
                    printf("- Permanecer en espacios cerrados ventilados\n");
                    printf("- Usar mascarillas N95 o FFP2 si debe salir\n");
                    printf("- Cerrar ventanas durante horas pico de contaminacion\n");
                    printf("- Evitar ejercicio intenso al aire libre\n");
                    printf("- Grupos sensibles: consultar medico si hay sintomas\n");
                    hayAlertas = 1;
                }
                
            if (zonaPred.ica.ICA > 200 && zonaPred.ica.ICA <= 300) {
                    printf("\n!!! ALERTA CRITICA: Nivel MUY INSALUBRE !!!\n");
                    printf("\nMEDIDAS URGENTES:\n");
                    printf("- Permanecer en interiores con ventanas cerradas\n");
                    printf("- Usar purificadores de aire con filtros HEPA\n");
                    printf("- Suspender toda actividad fisica al aire libre\n");
                    printf("- Grupos vulnerables: atencion medica inmediata si hay dificultad respiratoria\n");
                    printf("- Usar mascarilla incluso en interiores si hay infiltracion\n");
                    hayAlertas = 1;
                }
                
            if (zonaPred.ica.ICA > 300 && zonaPred.ica.ICA <= 500) {
                    printf("\n!!!! EMERGENCIA: Nivel PELIGROSO !!!!\n");
                    printf("\nSITUACION DE EMERGENCIA - ACCIONES INMEDIATAS:\n");
                    printf("- TODA la poblacion debe permanecer en interiores\n");
                    printf("- Suspender clases y actividades laborales no esenciales\n");
                    printf("- Sellar puertas y ventanas\n");
                    printf("- Usar purificadores en espacios cerrados\n");
                    printf("- Buscar atencion medica ante cualquier sintoma\n");
                    hayAlertas = 1;
                }
            if(zonaPred.ica.ICA > 500){
                    printf("\n!!!!! EMERGENCIA MAXIMA: Nivel EXTREMO !!!!!\n");
                    printf("\nSITUACION DE EMERGENCIA MAXIMA - ACCIONES URGENTES:\n");
                    printf("- Evacuacion recomendada si es posible\n");
                    printf("- Usar equipo de proteccion respiratoria adecuado\n");
                    printf("- Mantener contacto con autoridades locales\n");
                    printf("- Buscar atencion medica inmediata\n");
                    hayAlertas = 1;

                }
                
                if(hayAlertas==1){
                printf("\nRECOMENDACIONES DE MITIGACION:\n");
                printf("* Autoridades deben:\n");
                printf("  - Implementar restriccion vehicular\n");
                printf("  - Suspender actividades industriales no esenciales\n");
                printf("  - Prohibir quema de residuos y combustibles\n");
                printf("  - Activar plan de contingencia ambiental\n");
                printf("  - Aumentar frecuencia de riego de calles\n");
                printf("* Ciudadania debe:\n");
                printf("  - Evitar uso de vehiculos particulares (usar transporte publico)\n");
                printf("  - No quemar basura ni realizar fogatas\n");
                printf("  - Reducir uso de calefaccion a lena o carbon\n");
                printf("  - Reportar fuentes de contaminacion visibles\n");
                }
            
            
            // Alertas por contaminante específico con recomendaciones
            if (zonaPred.ica.ICA_PM2_5 > 100 || zonaPred.ica.ICA_PM10 > 100) {
                printf("\n[!] MATERIAL PARTICULADO ELEVADO:\n");
                if (zonaPred.ica.ICA_PM2_5 > 100){
                    printf("  - PM2.5: %.2f ug/m3 (ICA: %.2f) - Riesgo respiratorio alto\n", zonaPred.NivelesAcual.PM2_5, zonaPred.ica.ICA_PM2_5);
                    printf("  Medidas de mitigacion:\n");
                    printf("  + Evitar quema de residuos y uso de lena para calefaccion\n");
                    printf("  + Promover transporte publico y vehiculos electricos\n");
                    printf("  + Implementar zonas verdes y arbolado urbano\n");
                    printf("  + Controlar emisiones industriales\n");
                    printf("  + Reducir la circulacion vehicular\n");
                    printf("  + Fomentar uso de mascarillas en dias de alta contaminacion\n");
                    printf("\n");
                }
                if (zonaPred.ica.ICA_PM10 > 100){
                    printf("  - PM10: %.2f ug/m3 (ICA: %.2f) - Riesgo respiratorio\n", zonaPred.NivelesAcual.PM10, zonaPred.ica.ICA_PM10);
                printf("  Medidas de mitigacion:\n");
                printf("  + Usar mascarilla con filtro (N95/FFP2)\n");
                printf("  + Reducir trafico vehicular (principal fuente)\n");
                printf("  + Riego de calles para reducir polvo en suspension\n");
                printf("  + Controlar emisiones industriales\n");
                printf("  + Evitar construcciones sin medidas de control de polvo\n");
                hayAlertas = 1;}
            }
            
            if (zonaPred.ica.ICA_NO2 > 100) {
                printf("\n[!] DIOXIDO DE NITROGENO ELEVADO:\n");
                printf("  - NO2: %.2f ppb (ICA: %.2f)\n", zonaPred.NivelesAcual.NO2, zonaPred.ica.ICA_NO2);
                printf("  - Irrita vias respiratorias, agrava asma y bronquitis\n");
                printf("  Medidas de mitigacion:\n");
                printf("  + Reducir circulacion de vehiculos diesel\n");
                printf("  + Implementar transporte publico electrico\n");
                printf("  + Mantener motores vehiculares en buen estado\n");
                printf("  + Regular emisiones de plantas termicas\n");
                hayAlertas = 1;
            }
            
            if (zonaPred.ica.ICA_SO2 > 100) {
                printf("\n[!] DIOXIDO DE AZUFRE ELEVADO:\n");
                printf("  - SO2: %.2f ppb (ICA: %.2f)\n", zonaPred.NivelesAcual.SO2, zonaPred.ica.ICA_SO2);
                printf("  - Riesgo para enfermedades respiratorias y cardiovasculares\n");
                printf("  Medidas de mitigacion:\n");
                printf("  + Usar combustibles con bajo contenido de azufre\n");
                printf("  + Regular emisiones de industrias y refinerias\n");
                printf("  + Prohibir quema de carbon y combustibles sucios\n");
                printf("  + Implementar desulfuracion en chimeneas industriales\n");
                hayAlertas = 1;
            }
            
            if (zonaPred.ica.ICA_O3 > 100) {
                printf("\n[!] OZONO TROPOSFERICO ELEVADO:\n");
                printf("  - O3: %.3f ppm (ICA: %.2f)\n", zonaPred.NivelesAcual.O3, zonaPred.ica.ICA_O3);
                printf("  - Dano pulmonar, agrava problemas respiratorios\n");
                printf("  Medidas de mitigacion:\n");
                printf("  + Reducir emisiones de NOx y COV (precursores de ozono)\n");
                printf("  + Evitar uso de solventes y pinturas en dias soleados\n");
                printf("  + Reducir trafico vehicular en horas de mayor radiacion solar\n");
                printf("  + Plantar arboles (absorben ozono y precursores)\n");
                printf("  + No realizar ejercicio intenso al aire libre entre 12-18hrs\n");
                hayAlertas = 1;
            }
            
            if (zonaPred.ica.ICA_CO > 100) {
                printf("\n[!] MONOXIDO DE CARBONO ELEVADO:\n");
                printf("  - CO: %.2f ppm (ICA: %.2f)\n", zonaPred.NivelesAcual.CO, zonaPred.ica.ICA_CO);
                printf("  - Riesgo cardiovascular, reduce oxigenacion sanguinea\n");
                printf("  Medidas de mitigacion:\n");
                printf("  + Mejorar combustion vehicular (mantenimiento preventivo)\n");
                printf("  + Ventilar adecuadamente espacios con calefaccion a gas\n");
                printf("  + Regular trafico en zonas congestionadas\n");
                printf("  + Evitar uso de generadores en espacios cerrados\n");
                printf("  + Promover vehiculos electricos e hibridos\n");
                hayAlertas = 1;
            }
            
            if (hayAlertas==0) {
                printf("\nNo se detectan alertas. Calidad del aire dentro de limites aceptables.\n");
            }
        } else {
            printf("No hay suficientes datos historicos para prediccion.\n");
        }
        printf("\n");
    }
}

int prediccionPonderada(char *nombreZona,
                        float *pm25, float *pm10, float *no2,
                        float *so2, float *o3, float *co,
                        float *temperatura, float *humedad, float *velocidadViento)
{
    FILE *f = fopen("Historico.dat", "rb");
    if (!f) return 0;

    Zona registros[500];
    int total = 0;
    while (fread(&registros[total], sizeof(Zona), 1, f) == 1 && total < 500) {
        total++;
    }
    fclose(f);

    Zona ultimos10[10];
    int count = 0;
    
    for (int i = total - 1; i >= 0 && count < 10; i--) {
        if (_stricmp(registros[i].nombreZona, nombreZona) == 0) {
            ultimos10[count] = registros[i];
            count++;
        }
    }

    if (count == 0) return 0;

    float sumaPM25 = 0, sumaPM10 = 0, sumaNO2 = 0, sumaSO2 = 0, sumaO3 = 0, sumaCO = 0;
    float sumaTemp = 0, sumaHumedad = 0, sumaVViento = 0;
    float sumaPesos = 0;

    for (int i = 0; i < count; i++) {
        float peso = count - i;
        
        sumaPM25 += ultimos10[i].NivelesAcual.PM2_5 * peso;
        sumaPM10 += ultimos10[i].NivelesAcual.PM10 * peso;
        sumaNO2  += ultimos10[i].NivelesAcual.NO2 * peso;
        sumaSO2  += ultimos10[i].NivelesAcual.SO2 * peso;
        sumaO3   += ultimos10[i].NivelesAcual.O3 * peso;
        sumaCO   += ultimos10[i].NivelesAcual.CO * peso;
        
        sumaTemp += ultimos10[i].NivelesAcual.factores.temperatura * peso;
        sumaHumedad += ultimos10[i].NivelesAcual.factores.humedad * peso;
        sumaVViento += ultimos10[i].NivelesAcual.factores.velocidadViento * peso;
        
        sumaPesos += peso;
    }

    *pm25 = sumaPM25 / sumaPesos;
    *pm10 = sumaPM10 / sumaPesos;
    *no2  = sumaNO2 / sumaPesos;
    *so2  = sumaSO2 / sumaPesos;
    *o3   = sumaO3 / sumaPesos;
    *co   = sumaCO / sumaPesos;
    
    *temperatura = sumaTemp / sumaPesos;
    *humedad = sumaHumedad / sumaPesos;
    *velocidadViento = sumaVViento / sumaPesos;

    /* AJUSTAR contaminantes por factores climáticos */
    
    /* Factor por viento: viento fuerte dispersa más */
    float factorViento = 1.0;
    if (*velocidadViento > 8.0) {
        factorViento = 0.70; /* 30% menos contaminantes */
    } else if (*velocidadViento > 3.0) {
        factorViento = 0.92;
    } else if (*velocidadViento < 2.0) {
        factorViento = 1.10; /* 10% más si hay poco viento */
    }

    /* Factor por temperatura: temp alta = más dispersión */
    float factorTemp = 1.0;
    if (*temperatura > 24.0) {
        factorTemp = 0.90;
    } else if (*temperatura < 15.0) {
        factorTemp = 1.05;
    }

    /* Factor por humedad: humedad alta = lluvia potencial */
    float factorHumedad = 1.0;
    if (*humedad > 70.0) {
        factorHumedad = 0.88; /* lluvia limpia */
    } else if (*humedad < 40.0) {
        factorHumedad = 1.08; /* aire seco, menos dispersión */
    }

    /* Aplicar ajustes */
    float ajuste = factorViento * factorTemp * factorHumedad;
    
    *pm25 *= ajuste;
    *pm10 *= ajuste;
    *no2  *= ajuste;
    *so2  *= ajuste;
    *o3   *= ajuste;
    *co   *= ajuste;

    return count;
}

void TablaLimitesICA()
{
    printf("=== Tabla de Limites de ICA por Contaminante ===\n");
    printf("| Contaminante | Rango de Concentracion | Rango de ICA | Nivel de Calidad               |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| PM2.5 (ug/m3)| 0.0 - 12.0             | 0 - 50       | Buena                          |\n");
    printf("| PM2.5 (ug/m3)| 12.1 - 35.4            | 51 - 100     | Moderada                       |\n");
    printf("| PM2.5 (ug/m3)| 35.5 - 55.4            | 101 - 150    | Insalubre para grupos sensibles|\n");
    printf("| PM2.5 (ug/m3)| 55.5 - 150.4           | 151 - 200    | Insalubre                      |\n");
    printf("| PM2.5 (ug/m3)| 150.5 - 250.4          | 201 - 300    | Muy insalubre                  |\n");
    printf("| PM2.5 (ug/m3)| 250.5 - 500.4          | 301 - 500    | Peligrosa                      |\n");
    printf("| PM2.5 (ug/m3)| > 500.4                | > 500        | Extrema emergencia             |\n");
    printf("-----------------------------------------------------------------------------------------\n");

    printf("| PM10 (ug/m3) | 0 - 54                 | 0 - 50       | Buena                          |\n");
    printf("| PM10 (ug/m3) | 55 - 154               | 51 - 100     | Moderada                       |\n");
    printf("| PM10 (ug/m3) | 155 - 254              | 101 - 150    | Insalubre para grupos sensibles|\n");
    printf("| PM10 (ug/m3) | 255 - 354              | 151 - 200    | Insalubre                      |\n");
    printf("| PM10 (ug/m3) | 355 - 424              | 201 - 300    | Muy insalubre                  |\n");
    printf("| PM10 (ug/m3) | 425 - 604              | 301 - 500    | Peligrosa                      |\n");
    printf("| PM10 (ug/m3) | > 604                  | > 500        | Extrema emergencia             |\n");
    printf("-----------------------------------------------------------------------------------------\n");  
    printf("| NO2 (ppb)    | 0 - 53                 | 0 - 50       | Buena                          |\n");
    printf("| NO2 (ppb)    | 54 - 100               | 51 - 100     | Moderada                       |\n");
    printf("| NO2 (ppb)    | 101 - 360              | 101 - 150    | Insalubre para grupos sensibles|\n");
    printf("| NO2 (ppb)    | 361 - 649              | 151 - 200    | Insalubre                      |\n");
    printf("| NO2 (ppb)    | 650 - 1249             | 201 - 300    | Muy insalubre                  |\n");
    printf("| NO2 (ppb)    | 1250 - 2049            | 301 - 500    | Peligrosa                      |\n");
    printf("| NO2 (ppb)    | > 2049                 | > 500        | Extrema emergencia             |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| SO2 (ppb)    | 0 - 35                 | 0 - 50       | Buena                          |\n");
    printf("| SO2 (ppb)    | 36 - 75                | 51 - 100     | Moderada                       |\n");
    printf("| SO2 (ppb)    | 76 - 185               | 101 - 150    | Insalubre para grupos sensibles|\n");
    printf("| SO2 (ppb)    | 186 - 304              | 151 - 200    | Insalubre                      |\n");
    printf("| SO2 (ppb)    | 305 - 604              | 201 - 300    | Muy insalubre                  |\n");
    printf("| SO2 (ppb)    | 605 - 1004             | 301 - 500    | Peligrosa                      |\n");
    printf("| SO2 (ppb)    | > 1004                 | > 500        | Extrema emergencia             |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| O3 (ppm)     | 0.0 - 0.054            | 0 - 50       | Buena                          |\n");
    printf("| O3 (ppm)     | 0.055 - 0.070          | 51 - 100     | Moderada                       |\n");
    printf("| O3 (ppm)     | 0.071 - 0.085          | 101 - 150    | Insalubre para grupos sensibles|\n");
    printf("| O3 (ppm)     | 0.086 - 0.105          | 151 - 200    | Insalubre                      |\n");
    printf("| O3 (ppm)     | 0.106 - 0.200          | 201 - 300    | Muy insalubre                  |\n");
    printf("| O3 (ppm)     | 0.201 - 0.404          | 301 - 500    | Peligrosa                      |\n");
    printf("| O3 (ppm)     | > 0.404                | > 500        | Extrema emergencia             |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| CO (ppm)     | 0.0 - 4.4              | 0 - 50       | Buena                          |\n");
    printf("| CO (ppm)     | 4.5 - 9.4              | 51 - 100     | Moderada                       |\n");
    printf("| CO (ppm)     | 9.5 - 12.4             | 101 - 150    | Insalubre para grupos sensibles|\n");
    printf("| CO (ppm)     | 12.5 - 15.4            | 151 - 200    | Insalubre                      |\n");
    printf("| CO (ppm)     | 15.5 - 30.4            | 201 - 300    | Muy insalubre                  |\n");
    printf("| CO (ppm)     | 30.5 - 40.4            | 301 - 500    | Peligrosa                      |\n");
    printf("| CO (ppm)     | > 40.4                 | > 500        | Extrema emergencia             |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("\n");
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