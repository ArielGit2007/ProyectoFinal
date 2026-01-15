typedef struct {
    float PM2_5;    // Partículas finas - CRÍTICO
    float PM10;     // Partículas gruesas
    float NO2;      // Dióxido de nitrógeno - MUY IMPORTANTE
    float SO2;      // Dióxido de azufre
    float O3;       // Ozono troposférico
    float CO;  
    FactoresClimaticos factores; // Factores climáticos asociados     
}Contaminantes;

typedef struct{
    float temperatura;
    float humedad;
    float velocidadViento;
}FactoresClimaticos;

typedef struct{
    Contaminantes contaminantes[30]; // Datos de contaminantes para 30 días
}Historico;

typedef struct{
    char nombreZona[50];
    Contaminantes nivelesAceptables;
    Historico antecedentes;
}Zona;




int leerIntegerRango(int inicio, int fin);
float leerFlotanteRango(float inicio, float fin);