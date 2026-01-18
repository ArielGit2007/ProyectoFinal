
typedef struct{
    float temperatura;
    float humedad;
    float velocidadViento;
}FactoresClimaticos;

typedef struct{
    float ICA_PM2_5;
    float ICA_PM10;
    float ICA_NO2;
    float ICA_SO2;
    float ICA_O3;
    float ICA_CO;
    float ICA; // Índice de Calidad del Aire general
}ICA;

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
    Contaminantes contaminantes; // Datos de contaminantes actuales
}Historico;

typedef struct{
    char nombreZona[50];
    Contaminantes NivelesAcual;
    Historico antecedentes;
    ICA ica;  // ICA calculado para esta zona
}Zona;




int leerIntegerRango(int inicio, int fin);
float leerFlotanteRango(float inicio, float fin);
float leerFlotanteSoloMinimo(float inicio);
void DatosActuales();
void GuardarDatosActuales(Zona *zona);
int leerDatosActuales(Zona *zona);
void calcularICAPm2_5();
void calcularICAPm10();
void calcularICANO2();




