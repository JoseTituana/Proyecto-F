#include "funciones.h"
#include <stdlib.h>

/* Límites OMS */
const Contaminacion limites = { 400, 20, 40, 15 };
/* ================= DATOS REALES QUITO ================= */
const char *nombres_zonas[ZONAS] = {
    "Centro Historico",
    "La Carolina (Norte)",
    "Quitumbe (Sur)",
    "Valle de Los Chillos",
    "Calderon"
};

Contaminacion centro[DIAS] = {
 {410,6,32,28},{412,6,33,29},{415,7,34,30},{418,7,35,31},
 {420,7,36,32},{422,8,36,33},{425,8,37,34},{428,8,38,35},
 {430,9,39,36},{432,9,40,37},{435,10,41,38},{438,10,42,39},
 {440,10,43,40},{442,11,44,41},{445,11,45,42},{447,11,46,43},
 {450,12,47,44},{452,12,48,45},{455,12,49,46},{457,13,50,47},
 {460,13,51,48},{462,13,52,49},{465,14,53,50},{467,14,54,51},
 {470,14,55,52},{472,15,56,53},{475,15,57,54},{477,15,58,55},
 {480,16,59,56},{482,16,60,57}
};

Contaminacion norte[DIAS] = {
 {395,4,25,18},{397,4,26,19},{398,4,27,20},{400,5,28,21},
 {402,5,29,22},{403,5,30,23},{405,5,31,24},{407,6,32,25},
 {408,6,33,26},{410,6,34,27},{412,6,35,28},{413,7,36,29},
 {415,7,37,30},{417,7,38,31},{418,7,39,32},{420,8,40,33},
 {422,8,41,34},{423,8,42,35},{425,8,43,36},{427,9,44,37},
 {428,9,45,38},{430,9,46,39},{432,10,47,40},{433,10,48,41},
 {435,10,49,42},{437,11,50,43},{438,11,51,44},{440,11,52,45},
 {442,12,53,46},{443,12,54,47}
};

Contaminacion sur[DIAS] = {
 {370,3,18,12},{372,3,19,13},{374,3,20,14},{376,4,21,15},
 {378,4,22,16},{380,4,23,17},{382,4,24,18},{384,5,25,19},
 {386,5,26,20},{388,5,27,21},{390,5,28,22},{392,6,29,23},
 {394,6,30,24},{396,6,31,25},{398,6,32,26},{400,7,33,27},
 {402,7,34,28},{404,7,35,29},{406,7,36,30},{408,8,37,31},
 {410,8,38,32},{412,8,39,33},{414,9,40,34},{416,9,41,35},
 {418,9,42,36},{420,10,43,37},{422,10,44,38},{424,10,45,39},
 {426,11,46,40},{428,11,47,41}
};

Contaminacion chillos[DIAS] = {
 {360,2,15,10},{362,2,16,11},{364,2,17,12},{366,3,18,13},
 {368,3,19,14},{370,3,20,15},{372,3,21,16},{374,4,22,17},
 {376,4,23,18},{378,4,24,19},{380,4,25,20},{382,5,26,21},
 {384,5,27,22},{386,5,28,23},{388,5,29,24},{390,6,30,25},
 {392,6,31,26},{394,6,32,27},{396,6,33,28},{398,7,34,29},
 {400,7,35,30},{402,7,36,31},{404,8,37,32},{406,8,38,33},
 {408,8,39,34},{410,9,40,35},{412,9,41,36},{414,9,42,37},
 {416,10,43,38},{418,10,44,39}
};

Contaminacion calderon[DIAS] = {
 {365,3,17,11},{367,3,18,12},{369,3,19,13},{371,4,20,14},
 {373,4,21,15},{375,4,22,16},{377,4,23,17},{379,5,24,18},
 {381,5,25,19},{383,5,26,20},{385,5,27,21},{387,6,28,22},
 {389,6,29,23},{391,6,30,24},{393,6,31,25},{395,7,32,26},
 {397,7,33,27},{399,7,34,28},{401,7,35,29},{403,8,36,30},
 {405,8,37,31},{407,8,38,32},{409,9,39,33},{411,9,40,34},
 {413,9,41,35},{415,10,42,36},{417,10,43,37},{419,10,44,38},
 {421,11,45,39},{423,11,46,40}
};

/* Datos históricos: 30 días × 5 zonas × 4 contaminantes */
Contaminacion historico[ZONAS][DIAS];
Contaminacion actual[ZONAS];
Clima clima_actual;

/* ======================= */
void menu() {
    printf("\n--- SISTEMA DE MONITOREO AMBIENTAL ---\n");
    printf("1. Monitoreo de contaminacion actual\n");
    printf("2. Prediccion de niveles futuros (24h)\n");
    printf("3. Alertas preventivas\n");
    printf("4. Promedios historicos (30 dias)\n");
    printf("5. Recomendaciones\n");
    printf("6. Exportar datos\n");
    printf("0. Salir\n");
}
/* ======================= */
void mostrar_zonas() {
    printf("\nZonas:\n");
    printf("1. Centro Historico\n");
    printf("2. La Carolina (Norte)\n");
    printf("3. Quitumbe (Sur)\n");
    printf("4. Valle de Los Chillos\n");
    printf("5. Calderon\n");
}

void cargar_datos_quito() {
    for (int d = 0; d < DIAS; d++) {
        historico[0][d] = centro[d];
        historico[1][d] = norte[d];
        historico[2][d] = sur[d];
        historico[3][d] = chillos[d];
        historico[4][d] = calderon[d];
    }

    for (int z = 0; z < ZONAS; z++) {
        actual[z] = historico[z][DIAS - 1];
    }
}

/* ======================= */
void monitoreo_actual() {
    printf("\n--- MONITOREO ACTUAL ---\n");
    for (int z = 0; z < ZONAS; z++) {
        printf("\n%s:\n", nombres_zonas[z]);
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

        printf("\n%s:\n", nombres_zonas[z]);
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

            printf("ALERTA en Zona %d Los niveles de PM2.5 han alcanzado limites, "
       "superando el limite diario de la OMS. Se recomienda a personas con "
       "afecciones respiratorias y adultos mayores evitar actividades prolongadas al aire libre. "
       "Considere el uso de transporte publico para reducir emisiones.\n", z + 1);
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

        printf("\n%s:\n", nombres_zonas[z]);
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
            printf("Zona %d: Suspender actividades al aire libre\n", nombres_zonas[z]);
        }
        if (actual[z].no2 > limites.no2) {
            printf("Zona %d: Reducir tráfico vehicular\n", nombres_zonas[z]);
        }
        if (actual[z].so2 > limites.so2) {
            printf("Zona %d: Cierre temporal de industrias\n", nombres_zonas[z]);
        }
    }
}

/* ======================= */
void exportar_datos() {
    FILE *f = fopen("reporte.txt", "w");
    if (!f) return;

    fprintf(f, "REPORTE AMBIENTAL\n");

    for (int z = 0; z < ZONAS; z++) {
        fprintf(f, "\n%s\n", nombres_zonas[z]);
        fprintf(f, "CO2: %.1f\n", actual[z].co2);
        fprintf(f, "SO2: %.1f\n", actual[z].so2);
        fprintf(f, "NO2: %.1f\n", actual[z].no2);
        fprintf(f, "PM2.5: %.1f\n", actual[z].pm25);
    }

    fclose(f);
    printf("Datos exportados a reporte.txt\n");
}
