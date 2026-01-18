
typedef struct{
    float temperatura;
    float humedad;
    float velocidadViento;
}FactoresClimaticos;
typedef struct{
    char nivelCalidadPM2_5[50];
    char nivelCalidadPM10[50];
    char nivelCalidadNO2[50];
    char nivelCalidadSO2[50];
    char nivelCalidadO3[50];
    char nivelCalidadCO[50];
}CalidadPorContaminante;

typedef struct{
    float ICA_PM2_5;
    float ICA_PM10;
    float ICA_NO2;
    float ICA_SO2;
    float ICA_O3;
    float ICA_CO;
    float ICA; // Índice de Calidad del Aire general
    CalidadPorContaminante calidad;
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
    char nombreZona[50];
    Contaminantes contaminantes; // Datos de contaminantes actuales
}Historico;

typedef struct{
    char nombreZona[50];
    Contaminantes NivelesAcual;
    ICA ica;  // ICA calculado para esta zona
    char calidadAire[100];
}Zona;




int leerIntegerRango(int inicio, int fin);
float leerFlotanteRango(float inicio, float fin);
float leerFlotanteSoloMinimo(float inicio);
void DatosActuales();
void GuardarDatosActuales(Zona *zona);
void GuardarDatosHistoricos(Zona *zona);
int leerDatosActuales(Zona *zona);
void calcularICAPm2_5(Zona *zona);
void calcularICAPm10(Zona *zona);
void calcularICANO2(Zona *zona);
void calcularICASO2(Zona *zona);
void calcularICAO3(Zona *zona);
void calcularICACO(Zona *zona);
void obtenerICA(Zona *zona);
void reporteZonas();
void ingresoDatos();
void calidadDelAire(Zona *zona);
void BorrarSaltolinea(char *cadena);
void prevenirContaminacion(Zona *zona);



