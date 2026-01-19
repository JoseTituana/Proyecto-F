#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>

#define ZONAS 5
#define DIAS 30

typedef struct {
    float co2;
    float so2;
    float no2;
    float pm25;
} Contaminacion;

typedef struct {
    float temperatura;
    float viento;
    float humedad;
} Clima;

/* Menú */
void menu();

/* Inicialización */
void cargar_datos_historicos();
void mostrar_zonas();

/* Opciones del menú */
void monitoreo_actual();
void prediccion_futura();
void alertas_preventivas();
void promedios_historicos();
void recomendaciones();
void exportar_datos();

/* Utilidades */
float promedio_ponderado(float datos[], int n);
float factor_climatico(Clima c);

#endif
