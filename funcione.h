typedef struct {
    float CO2;
    float SO2;
    float NO2;
    float PM2_5;
    float O3;
    float CO;
}Contaminantes;

typedef struct{
    float temperatura;
    float humedad;
    float velocidadViento;
}FactoresClimaticos;





int leerIntegerRango(int inicio, int fin);
float leerFlotanteRango(float inicio, float fin);