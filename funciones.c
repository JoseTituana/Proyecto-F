#include "funciones.h"
#include <stdlib.h>

/* Límites OMS */
const Contaminacion limites = { 400, 20, 40, 15 };

/* Datos históricos: 30 días × 5 zonas × 4 contaminantes */
Contaminacion historico[ZONAS][DIAS];
Contaminacion actual[ZONAS];
Clima clima_actual;

/* ======================= */
void menu() {
    printf("\n--- SISTEMA DE MONITOREO AMBIENTAL ---\n");
    printf("1. Monitoreo de contaminación actual\n");
    printf("2. Predicción de niveles futuros (24h)\n");
    printf("3. Alertas preventivas\n");
    printf("4. Promedios históricos (30 días)\n");
    printf("5. Recomendaciones\n");
    printf("6. Exportar datos\n");
    printf("0. Salir\n");
}

/* ======================= */
void cargar_datos_historicos() {
    for (int z = 0; z < ZONAS; z++) {
        for (int d = 0; d < DIAS; d++) {
            historico[z][d].co2  = 350 + rand() % 80;
            historico[z][d].so2  = 10 + rand() % 15;
            historico[z][d].no2  = 20 + rand() % 30;
            historico[z][d].pm25 = 8  + rand() % 10;
        }

        /* Datos actuales = último día */
        actual[z] = historico[z][DIAS - 1];
    }

    /* Clima actual */
    clima_actual.temperatura = 26;
    clima_actual.viento = 3;
    clima_actual.humedad = 65;
}

/* ======================= */
void mostrar_zonas() {
    printf("\nZonas:\n");
    for (int i = 0; i < ZONAS; i++) {
        printf("Zona %d\n", i + 1);
    }
}

/* ======================= */
void monitoreo_actual() {
    printf("\n--- MONITOREO ACTUAL ---\n");
    for (int z = 0; z < ZONAS; z++) {
        printf("\nZona %d:\n", z + 1);
        printf("CO2: %.1f\n", actual[z].co2);
        printf("SO2: %.1f\n", actual[z].so2);
        printf("NO2: %.1f\n", actual[z].no2);
        printf("PM2.5: %.1f\n", actual[z].pm25);
    }
}

/* ======================= */
float promedio_ponderado(float datos[], int n) {
    float suma = 0, peso = 0;
    for (int i = 0; i < n; i++) {
        int w = i + 1; // más peso a días recientes
        suma += datos[i] * w;
        peso += w;
    }
    return suma / peso;
}

/* ======================= */
float factor_climatico(Clima c) {
    return 1 + (c.temperatura / 100) - (c.viento / 20) + (c.humedad / 200);
}

/* ======================= */
void prediccion_futura() {
    printf("\n--- PREDICCIÓN 24 HORAS ---\n");

    float f = factor_climatico(clima_actual);

    for (int z = 0; z < ZONAS; z++) {
        float co2[DIAS], so2[DIAS], no2[DIAS], pm25[DIAS];

        for (int d = 0; d < DIAS; d++) {
            co2[d]  = historico[z][d].co2;
            so2[d]  = historico[z][d].so2;
            no2[d]  = historico[z][d].no2;
            pm25[d] = historico[z][d].pm25;
        }

        printf("\nZona %d:\n", z + 1);
        printf("CO2: %.1f\n", promedio_ponderado(co2, DIAS) * f);
        printf("SO2: %.1f\n", promedio_ponderado(so2, DIAS) * f);
        printf("NO2: %.1f\n", promedio_ponderado(no2, DIAS) * f);
        printf("PM2.5: %.1f\n", promedio_ponderado(pm25, DIAS) * f);
    }
}

/* ======================= */
void alertas_preventivas() {
    printf("\n--- ALERTAS ---\n");

    for (int z = 0; z < ZONAS; z++) {
        if (actual[z].pm25 > limites.pm25 ||
            actual[z].no2  > limites.no2  ||
            actual[z].so2  > limites.so2  ||
            actual[z].co2  > limites.co2) {

            printf("⚠ ALERTA en Zona %d\n", z + 1);
        }
    }
}

/* ======================= */
void promedios_historicos() {
    printf("\n--- PROMEDIOS HISTÓRICOS (30 DÍAS) ---\n");

    for (int z = 0; z < ZONAS; z++) {
        float sum_co2 = 0, sum_so2 = 0, sum_no2 = 0, sum_pm = 0;

        for (int d = 0; d < DIAS; d++) {
            sum_co2 += historico[z][d].co2;
            sum_so2 += historico[z][d].so2;
            sum_no2 += historico[z][d].no2;
            sum_pm  += historico[z][d].pm25;
        }

        printf("\nZona %d:\n", z + 1);
        printf("CO2: %.1f\n", sum_co2 / DIAS);
        printf("SO2: %.1f\n", sum_so2 / DIAS);
        printf("NO2: %.1f\n", sum_no2 / DIAS);
        printf("PM2.5: %.1f\n", sum_pm / DIAS);
    }
}

/* ======================= */
void recomendaciones() {
    printf("\n--- RECOMENDACIONES ---\n");

    for (int z = 0; z < ZONAS; z++) {
        if (actual[z].pm25 > limites.pm25) {
            printf("Zona %d: Suspender actividades al aire libre\n", z + 1);
        }
        if (actual[z].no2 > limites.no2) {
            printf("Zona %d: Reducir tráfico vehicular\n", z + 1);
        }
        if (actual[z].so2 > limites.so2) {
            printf("Zona %d: Cierre temporal de industrias\n", z + 1);
        }
    }
}

/* ======================= */
void exportar_datos() {
    FILE *f = fopen("reporte.txt", "w");
    if (!f) return;

    fprintf(f, "REPORTE AMBIENTAL\n");

    for (int z = 0; z < ZONAS; z++) {
        fprintf(f, "\nZona %d\n", z + 1);
        fprintf(f, "CO2: %.1f\n", actual[z].co2);
        fprintf(f, "SO2: %.1f\n", actual[z].so2);
        fprintf(f, "NO2: %.1f\n", actual[z].no2);
        fprintf(f, "PM2.5: %.1f\n", actual[z].pm25);
    }

    fclose(f);
    printf("Datos exportados a reporte.txt\n");
}
